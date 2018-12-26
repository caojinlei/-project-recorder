// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#include "recorder/recorder.h"

#include <boost/core/ignore_unused.hpp>

#include "ecnr/ecnr.h"
#include "log/log.h"

namespace Speech {
namespace Recorder {

static const char* const kTag = "Recorder";

static const char* const kAudioFile = "/tmp/1.pcm";
static const char* const kOriginalAudioFile = "/tmp/audio.pcm";

static const int kEcnrVoiceLength = 1280;

speech::ISpeechAudioStream* Recorder::audio_stream_ =
    speech::SpeechCreateAudioStream(speech::AS_INPUT);

Recorder::Recorder(const std::string& file_path, const std::string& query_name)
    : query_name_(query_name), file_path_(file_path), recorder_flag_(false) {
  ENTER_FUNC(kTag);

  if ((audio_stream_ == nullptr) ||
      (ERR_SUCCESS !=
       audio_stream_->Open(speech::AS_INPUT_SDS_NORMAL, AudioDataCb, AudioMsgCB,
                           this))) {
    LOGE(kTag) << "Audio Stream Open Failed!";
    exit(-1);
  }
  EXIT_FUNC(kTag);
}

Recorder::~Recorder() {
  ENTER_FUNC(kTag);
  EXIT_FUNC(kTag);
}

static std::string left_buffer;

int Recorder::AudioDataCb(const void* pData, uint32_t iSize, uint32_t* iGetSize,
                          const void* pUser) {
  boost::ignore_unused(pData, iSize, iGetSize, pUser);

  if (nullptr == pData || iGetSize == nullptr || pUser == nullptr) return -1;

  Recorder* recorder = reinterpret_cast<Recorder*>(const_cast<void*>(pUser));
  // while (true) {
  if (recorder->before_ecnr_fstream_.is_open()) {
    if (!recorder->before_ecnr_fstream_.write((char*)pData, iSize))
      LOGE(kTag) << "  : Write ECNR Befroe Audio ERROR!";
  }

// do ecnr here
#ifdef ARCH_AARCH64
  speech::Ecnr* ecnr_ptr = speech::Ecnr::GetInstance();

  std::string new_buffer((char*)pData, iSize);
  if (left_buffer.length() > 0) {
    new_buffer = left_buffer + new_buffer;
    left_buffer.clear();
  }
  int stream_size = 0;
  const char* stream_ptr = nullptr;
  if (new_buffer.length() >= kEcnrVoiceLength) {
    new_buffer.length() / kEcnrVoiceLength;
    int left_size = new_buffer.length() % kEcnrVoiceLength;
    stream_ptr =
        ecnr_ptr->process(reinterpret_cast<const char*>(new_buffer.data()),
                          new_buffer.length() - left_size, &stream_size);

    if (nullptr == stream_ptr || stream_size <= 0) {
      LOGE(kTag) << __FUNCTION__ << "MOBVOI_DSP process return null";
      //*get_size = iSize;
      return -1;
    }

    if (left_size > 0) {
      left_buffer = std::string(
          new_buffer.data() + new_buffer.length() - left_size, left_size);
    }
  } else {
    left_buffer = new_buffer;
    //*get_size = iSize;
    return 0;
  }
#else
  const char* stream_ptr = (const char*)pData;
  int stream_size = iSize;
#endif
  // up is ecnr

  if (recorder->pcm_fstream_.is_open()) {
    if (!recorder->pcm_fstream_.write(stream_ptr, stream_size))
      LOGE(kTag) << "  : Write ECNR After Audio ERROR!";
  }
  return 0;
}

void Recorder::AudioMsgCB(const void* pUser, speech::AS_MESSAGE eMsg,
                          uint32_t wParam, int32_t lParam) {
  boost::ignore_unused(pUser, eMsg, wParam, lParam);

  LOGE(kTag) << __FUNCTION__;
}

Stopped::Stopped() { LOGD(kTag) << "Enter State: Stopped"; }

Stopped::~Stopped() { LOGD(kTag) << "Exit State: Stopped"; }

boost::statechart::result Stopped::react(const EvStartRecord& ev_start_record) {
  LOGD(kTag) << "Stopped::react(const EvStartRecord& ev_start_record)";

  boost::ignore_unused(ev_start_record);

  if (context<Recorder>().pcm_fstream_.is_open())
    context<Recorder>().pcm_fstream_.close();
  if (context<Recorder>().before_ecnr_fstream_.is_open())
    context<Recorder>().before_ecnr_fstream_.close();

  std::string recorder_file_path = context<Recorder>().file_path_;
  std::string query_name = context<Recorder>().query_name_;
  std::string ecnr_file_name = recorder_file_path + query_name + ".wav";
  std::string original_file_name =
      recorder_file_path + std::string("Original_") + query_name + ".wav";

  for (int i = 0; i < 5; ++i) {
    LOGD(kTag) << __FUNCTION__
               << " Original file name = " << original_file_name;
    context<Recorder>().before_ecnr_fstream_.open(
        original_file_name, std::ios::out | std::ios::binary | std::ios::trunc);
    LOGD(kTag) << __FUNCTION__ << " ECNR file name = " << ecnr_file_name;

    context<Recorder>().pcm_fstream_.open(
        ecnr_file_name, std::ios::out | std::ios::binary | std::ios::trunc);

    if (!context<Recorder>().pcm_fstream_.is_open() ||
        !context<Recorder>().before_ecnr_fstream_.is_open()) {
      LOGD(kTag) << __FUNCTION__ << " Create Recorder File  Failed  ";
      // return terminate();
    } else {
      context<Recorder>().pcm_fstream_.seekp(0, std::ios::beg);
      context<Recorder>().before_ecnr_fstream_.seekp(0, std::ios::beg);
      break;
    }
  }

  if (!context<Recorder>().pcm_fstream_.is_open() ||
      !context<Recorder>().before_ecnr_fstream_.is_open()) {
    LOGD(kTag) << __FUNCTION__
               << " Create Recorder File  Failed  return terminate";
    return terminate();
  }

  if (ERR_SUCCESS != context<Recorder>().audio_stream_->Start()) {
    LOGE(kTag) << "Audio Stream Open Failed!";
    return terminate();
  }

  return transit<Recording>();
}

Recording::Recording() { LOGD(kTag) << "Enter State: Recording"; }

Recording::~Recording() { LOGD(kTag) << "Exit State: Recording"; }

boost::statechart::result Recording::react(const EvStopRecord& ev_stop_record) {
  LOGD(kTag) << "Recording::react(const EvStopRecord& ev_stop_record)";

  boost::ignore_unused(ev_stop_record);

  context<Recorder>().audio_stream_->Stop();
  context<Recorder>().audio_stream_->Close();
  if (context<Recorder>().pcm_fstream_.is_open())
    context<Recorder>().pcm_fstream_.close();
  else
    LOGD(kTag) << "Recording  Stop Command But ECNR after handle is close";

  if (context<Recorder>().before_ecnr_fstream_.is_open())
    context<Recorder>().before_ecnr_fstream_.close();
  else
    LOGD(kTag) << "Recording  Stop Command But Original handle is close";

  return terminate();
}

}  // namespace Recorder
}  // namespace Speech
