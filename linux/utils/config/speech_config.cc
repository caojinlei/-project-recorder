// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: jlcao_ext@vw-mobvoi.com (jinlei cao)

#include "config/speech_config.h"

#include <sstream>

namespace Selene {

#ifdef OS_EMBEDDED_LINUX
#define CONFIG_FILE_PATH "/usr/bin/recorder/simulator/parameter_config.conf"
#else
#define CONFIG_FILE_PATH "/usr/bin/recorder/simulator/parameter_config.conf"
#endif

namespace po = boost::program_options;

static const char* const kTag = "SpeechConfig: ";

static const char* const kShowHelp = "help";
static const char* const kMicphoneNumber = "mic-num";
static const char* const kMobvoiModelsDir = "mobvoi-models-dir";
static const char* const kIpAddress = "ip";
static const char* const kPort = "port";
static const char* kConfigFilePath =
    "/usr/bin/recorder/simulator/parameter_config.conf";

SpeechConfig* SpeechConfig::_instance = nullptr;
SpeechConfig::DeleteInstance SpeechConfig::m_delete_instance_;
pthread_once_t SpeechConfig::ponce_ = PTHREAD_ONCE_INIT;

SpeechConfig::SpeechConfig() {}

SpeechConfig::~SpeechConfig() {}

bool SpeechConfig::Parse() {
  LOGD(kTag) << kTag << __FUNCTION__
             << " : parse File Path = " << kConfigFilePath;
  try {
    std::ifstream config_file(kConfigFilePath);

    po::options_description speech_options("sds options");

    unsigned int micphone_num;
    std::string mobvoi_models_dir;
    unsigned int port;
    std::string ip_address;

    speech_options.add_options()(kShowHelp, "show useage")(
        kMicphoneNumber, po::value<unsigned int>(&micphone_num),
        "set micphone number")(kMobvoiModelsDir,
                               po::value<std::string>(&mobvoi_models_dir),
                               "set mobvoi model dir")(
        kIpAddress, po::value<std::string>(&ip_address), "set ip address ")(
        kPort, po::value<unsigned int>(&port), "set port");

    po::variables_map vm;
    po::store(po::parse_config_file(config_file, speech_options), vm);
    po::notify(vm);

    if (vm.count(kShowHelp)) return false;

    micphone_num_ = 1;
    mobvoi_model_dir_ = "/usr/bin/recorder/simulator";
    ip_address_ = "0.0.0.0";
    port_ = 55555;
  } catch (std::exception& e) {
    LOGD(kTag) << __FUNCTION__ << " : Read Config File Is fail " << e.what();
    return false;
  }
  return true;
}

std::string SpeechConfig::MobvoiModelDir() { return mobvoi_model_dir_ + "/"; }

unsigned int SpeechConfig::MicphoneNumber() { return micphone_num_; }

unsigned int SpeechConfig::GetIpPort() { return port_; }
std::string SpeechConfig::GetIpAddress() { return ip_address_; }

SpeechConfig* SpeechConfig::GetInstance() {
  pthread_once(&ponce_, SpeechConfig::init);
  return _instance;
}

}  // namespace Selene
