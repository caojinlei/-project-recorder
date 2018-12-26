// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#include <dirent.h>
#include <sys/stat.h>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <ostream>

#include "log/log.h"
#include "recorder/recorder.h"
#include "utils/config/speech_config.h"

using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>
namespace websocket =
    boost::beast::websocket;  // from <boost/beast/websocket.hpp>

static const char* const kTag = "Calliope";

#define BOOST_ASIO_ENABLE_OLD_SERVICES

//------------------------------------------------------------------------------

void transfer_file(websocket::stream<tcp::socket>& ws,
                   std::string& recorder_file) {
  /***********send ECNR Process Audio*******************/

  std::string path = recorder_file + ".wav";

  LOGD(kTag) << __FUNCTION__ << " transfer file name = " << path;

  boost::filesystem::path new_file_path = path;

  if (!boost::filesystem::is_regular_file(new_file_path)) {
    ws.write(boost::asio::buffer("Restart Recorder"));
    LOGD(kTag) << "Recorder File Path Is  Error";
    return;
  }

  boost::uint32_t length =
      static_cast<boost::uint32_t>(boost::filesystem::file_size(new_file_path));

  // char* buf = reinterpret_cast<char*>(&length);

  // std::vector<boost::uint8_t> binary_buf(buf, buf + sizeof(length));

  ws.text(false);

  // TODO (jlcao) send file size
  //  ws.write(boost::asio::buffer(std::to_string(length)));

  FILE* fp = fopen(new_file_path.c_str(), "rb");
  if (nullptr == fp) {
    LOGD(kTag) << "ECNR PROCESS Audio Handle nullptr";
    return;
  }
  std::vector<boost::uint8_t> binary_filebuf(length);
  fread(binary_filebuf.data(), 1, length, fp);
  ws.write(boost::asio::buffer(binary_filebuf));

  fclose(fp);
}

void mv_recorder_file_to_disk(
    boost::shared_ptr<Speech::Recorder::Recorder> recorder,
    const std::string& recorder_file_path) {
  std::string tmp_recorder_file_path = recorder->file_path_;
  std::string query_name = recorder->query_name_;
  std::string ecnr_file_name = query_name + ".wav";
  std::string original_file_name =
      std::string("Original_") + query_name + ".wav";

  std::string mv_ecnr_before_file = "mv " + tmp_recorder_file_path +
                                    ecnr_file_name + " " + recorder_file_path;
  LOGD(kTag) << __FUNCTION__
             << "  : mv_ecnr_before_file = " << mv_ecnr_before_file;
  std::string mv_ecnr_after_file = "mv " + tmp_recorder_file_path +
                                   original_file_name + " " +
                                   recorder_file_path;
  LOGD(kTag) << __FUNCTION__
             << "  : mv_ecnr_after_file = " << mv_ecnr_after_file;
  system(mv_ecnr_before_file.c_str());
  system(mv_ecnr_after_file.c_str());
  sync();
  return;
}

// Echoes back all received WebSocket messages
void do_session(tcp::socket& socket, std::string& recorder_file_path,
                std::string& query_file_path) {
  try {
    // Construct the stream by moving in the socket
    websocket::stream<tcp::socket> ws{std::move(socket)};

    // Accept the websocket handshake
    ws.accept();

    /*************************Send Query List***************************/

    LOGD(kTag) << __FUNCTION__
               << " : recorder_file_path = " << recorder_file_path
               << " : query_file_path = " << query_file_path;

    boost::filesystem::path new_file_path = query_file_path;

    if (!boost::filesystem::is_regular_file(new_file_path)) return;

    boost::uint32_t length = static_cast<boost::uint32_t>(
        boost::filesystem::file_size(new_file_path));

    ws.text(false);

    FILE* fp = fopen(new_file_path.c_str(), "rb");
    if (nullptr == fp) {
      LOGD(kTag) << "send query list handler nullptr";
      return;
    }
    std::vector<boost::uint8_t> binary_filebuf(length);
    fread(binary_filebuf.data(), 1, length, fp);

    LOGD(kTag) << __FUNCTION__ << " : file size = " << length;

    ws.write(boost::asio::buffer(binary_filebuf));
    fclose(fp);

    LOGD(kTag) << "send query list success";

    /************************Monitor recording command**********************/
    boost::shared_ptr<Speech::Recorder::Recorder> recorder = nullptr;
    std::string query_name = "";
    std::string tmp_recorder_file_path = "/tmp/recorder/";
    for (;;) {
      // This buffer will hold the incoming message
      boost::beast::multi_buffer buffer;

      // Read a message
      ws.read(buffer);

      LOGD(kTag) << "########################recording command = "
                 << boost::beast::buffers(buffer.data())
                 << "#########################";

      {
        std::string client_cmd = boost::beast::buffers_to_string(buffer.data());

        if ("Start" == client_cmd) {
          if (nullptr == recorder) {
            boost::beast::multi_buffer query_name_buffer;
            ws.read(query_name_buffer);
            query_name.clear();
            query_name =
                boost::beast::buffers_to_string(query_name_buffer.data());
            LOGD(kTag) << " query name = " << query_name;

            recorder = boost::make_shared<Speech::Recorder::Recorder>(
                tmp_recorder_file_path, query_name);
            recorder->initiate();
          }
          recorder->process_event(Speech::Recorder::EvStartRecord());
        } else if ("Stop" == client_cmd) {
          if (recorder != nullptr) {
            recorder->process_event(Speech::Recorder::EvStopRecord());
            while (!recorder->terminated()) {
              sleep(1);
            }
          }
          std::string tmp_recorder_file = tmp_recorder_file_path + query_name;
          transfer_file(ws, tmp_recorder_file);
          mv_recorder_file_to_disk(recorder, recorder_file_path);
          recorder = nullptr;
        }
      }
    }
  } catch (boost::system::system_error const& se) {
    // This indicates that the session was closed
    // if (se.code() != websocket::error::closed)
    LOGE(kTag) << "Error: " << se.code().message();
  } catch (std::exception const& e) {
    LOGE(kTag) << "Error: " << e.what();
  }
}

bool GetQueryListFile(std::string* recorder_file_path,
                      std::string* query_file_path) {
  bool ret_flag = false;
  if (recorder_file_path == nullptr || query_file_path == nullptr)
    return ret_flag;

  struct dirent* file_handle = NULL;
  std::string file_path = "/media";
  DIR* pDir = opendir(file_path.c_str());
  if (pDir == NULL) return ret_flag;

  while (NULL != (file_handle = readdir(pDir))) {
    if (file_handle->d_type == 8) {
      // file
      continue;
    } else {
      if (strcmp(file_handle->d_name, ".") == 0 ||
          strcmp(file_handle->d_name, "..") == 0)
        continue;
      // directory

      std::string tmp_path(file_handle->d_name);
      file_path = file_path + "/" + tmp_path;
      std::string recorder_file = file_path + "/recorder/";
      std::string tmp_recorder_file = "/tmp/recorder/";
      if (0 != access(recorder_file.c_str(), 0)) {
        mkdir(recorder_file.c_str(), 0755);
      }
      if (0 != access(tmp_recorder_file.c_str(), 0)) {
        mkdir(tmp_recorder_file.c_str(), 0755);
      }
      *recorder_file_path = recorder_file;
      ret_flag = true;
      break;
    }
  }
  file_path.append("/QueryList.txt");
  *query_file_path = file_path;
  LOGD(kTag) << " : file_path = " << file_path
             << "  : recorder_file_path = " << *recorder_file_path;
  return ret_flag;
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) {
  try {
    // Check command line arguments.
    //    if (argc != 3) {
    //      std::cerr << "Usage: cns_recorder <address> <port>\n"
    //                << "Example:\n"
    //                << "    cns_recorder 0.0.0.0 55555\n";
    //      return EXIT_FAILURE;
    //    }

    system("iptables -P INPUT ACCEPT");
    system("iptables -P OUTPUT ACCEPT");
    system("ip6tables -P INPUT ACCEPT");
    system("ip6tables -P OUTPUT ACCEPT");

    LOGD(kTag) << __FUNCTION__ << " close Firewall";

    Selene::SpeechConfig::GetInstance()->Parse();
    LOGD(kTag) << __FUNCTION__ << " Parse Config File";

    std::string ip_address =
        Selene::SpeechConfig::GetInstance()->GetIpAddress();
    unsigned int ports = Selene::SpeechConfig::GetInstance()->GetIpPort();
    LOGD(kTag) << __FUNCTION__ << " ip_address  = " << ip_address
               << " :ports = " << ports;

    auto const address = boost::asio::ip::make_address(ip_address.c_str());
    auto const port = static_cast<unsigned short>(ports);

    // The io_context is required for all I/O
    boost::asio::io_context ioc{1};

    // The acceptor receives incoming connections
    tcp::acceptor acceptor{ioc, {address, port}};
    LOGD(kTag) << __FUNCTION__
               << " ##########acceptor build success###########";
    for (;;) {
      // This will receive the new connection
      tcp::socket socket{ioc};

      // Block until we get a connection
      acceptor.accept(socket);

      LOGD(kTag) << "Net Session Connected!";
      std::string recorder_file_path;
      std::string query_file_path;
      if (!GetQueryListFile(&recorder_file_path, &query_file_path)) {
        std::cerr << "Error: "
                  << " U disk path is cant identification" << std::endl;
        return EXIT_FAILURE;
      }

      // Launch the session, transferring ownership of the socket
      std::thread{std::bind(&do_session, std::move(socket), recorder_file_path,
                            query_file_path)}
          .join();
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
