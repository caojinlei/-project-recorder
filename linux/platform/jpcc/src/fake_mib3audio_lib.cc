// Copyright 2017 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#include <iostream>
#include <boost/core/ignore_unused.hpp>

#include "platform/jpcc/inc/ISpeechAudioStream.h"

class SpeechAudioStream : public speech::ISpeechAudioStream {
 public:
  speech::SpeechErrorID Open(speech::AS_MODE eMode,
                             speech::SpeechAudioStreamDataCB funcDataCB,
                             speech::SpeechAudioStreamMsgCB funcMsgCB,
                             const void* pUser) final {
    boost::ignore_unused(eMode, funcDataCB, funcMsgCB, pUser);
    return ERR_SUCCESS;
  }
  speech::SpeechErrorID Close() final { return ERR_SUCCESS; }

  speech::SpeechErrorID Start() final { return ERR_SUCCESS; }

  speech::SpeechErrorID Stop() final { return ERR_SUCCESS; }

  speech::SpeechErrorID Pause() final { return ERR_SUCCESS; }

  speech::SpeechErrorID Resume() final { return ERR_SUCCESS; }

  const char* GetVersion() final { return nullptr; }

 public:
  SpeechAudioStream() {}
  ~SpeechAudioStream() final {}

};  // class SpeechAudioStream

#ifdef __cplusplus
extern "C" {
#endif
SPEECH_API_PORT speech::ISpeechAudioStream* SpeechCreateAudioStream(
    speech::AS_TYPE eType) {
  eType = speech::AS_OUTPUT;

  speech::ISpeechAudioStream* audio_stream = new SpeechAudioStream();

  return audio_stream;
}
#ifdef __cplusplus
}
#endif
