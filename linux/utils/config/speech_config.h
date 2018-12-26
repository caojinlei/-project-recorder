// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: jlcao_ext@vw-mobvoi.com (jinlei cao)

#ifndef SRC_CONFILE_SPEECH_CONFIG_H_
#define SRC_CONFILE_SPEECH_CONFIG_H_

#include <pthread.h>

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/program_options.hpp>

#include "utils/log/log.h"

namespace Selene {

class SpeechConfig : public boost::noncopyable {
 public:
  static SpeechConfig* GetInstance();
  ~SpeechConfig();
  bool Parse();
  unsigned int MicphoneNumber();
  std::string MobvoiModelDir();
  unsigned int GetIpPort();
  std::string GetIpAddress();

 private:
  class DeleteInstance {
   public:
    ~DeleteInstance() {
      if (SpeechConfig::_instance) delete _instance;
    }
  };

 private:
  static void init() { _instance = new SpeechConfig(); }
  static pthread_once_t ponce_;

 private:
  SpeechConfig();
  static SpeechConfig* _instance;
  static DeleteInstance m_delete_instance_;
  unsigned int micphone_num_;
  unsigned int port_;
  std::string mobvoi_model_dir_;
  std::string ip_address_;
};  // class SpeechConfig
}  // namespace Selene

#endif  // SRC_CONFILE_SPEECH_CONFIG_H_
