// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TASK_HEADER_H_
#define DIALOGUE_TASK_HEADER_H_

#include <string>

#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace dialogue {

class TaskHeader {
 protected:
  static const char kNameKey[];
  static const char kVersionKey[];
  static const char kDescriptionKey[];
  static const char kEngineTypeKey[];
  static const char kEngineVersionKey[];
  static const char kPriorityKey[];

 public:
  int parse(const Json::Value& configure);

 public:
  std::string name_;            // task name
  std::string version_;         // task version
  std::string desc_;            // task description
  std::string engine_;          // task engine type, default: TCP
  std::string engineVersion_;   // task engine version, default: 1.0
  int         priority_;        // task priority, default: normal(0)
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_TASK_HEADER_H_
