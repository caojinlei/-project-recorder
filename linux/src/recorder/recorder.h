// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#ifndef LINUX_SRCS_RECORDER_RECORDER_H_
#define LINUX_SRCS_RECORDER_RECORDER_H_

#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>

#include <fstream>

#include "platform/jpcc/inc/ISpeechAudioStream.h"

#include "recorder/events.h"

namespace Speech {
namespace Recorder {

struct Stopped;
struct Recorder : boost::statechart::state_machine<Recorder, Stopped> {
  Recorder(const std::string& file_path, const std::string& query_name);
  ~Recorder() final;

  static int AudioDataCb(const void* pData, uint32_t iSize, uint32_t* iGetSize,
                         const void* pUser);

  static void AudioMsgCB(const void* pUser, speech::AS_MESSAGE eMsg,
                         uint32_t wParam, int32_t lParam);

  std::ofstream pcm_fstream_;
  std::ofstream before_ecnr_fstream_;
  std::string query_name_;
  std::string file_path_;
  bool recorder_flag_;
  static speech::ISpeechAudioStream* audio_stream_;
};  // struct Recorder

struct Recording;
struct Stopped : boost::statechart::simple_state<Stopped, Recorder> {
  typedef boost::statechart::custom_reaction<EvStartRecord> reactions;

  Stopped();
  ~Stopped() final;

  boost::statechart::result react(const EvStartRecord& ev_start_record);
};  // struct NotInit

struct Recording : boost::statechart::simple_state<Recording, Recorder> {
  typedef boost::statechart::custom_reaction<EvStopRecord> reactions;

  Recording();
  ~Recording() final;

  boost::statechart::result react(const EvStopRecord& EvStopRecord);
};

}  // namespace Recorder
}  // namespace Speech

#endif  // LINUX_SRCS_RECORDER_RECORDER_H_
