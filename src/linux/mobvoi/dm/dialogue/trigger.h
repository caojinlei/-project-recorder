// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TRIGGER_H_
#define DIALOGUE_TRIGGER_H_

#include <string>
#include <set>
#include <iostream>

#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace dialogue {

class PackEngine;
class TcpEngine;

class Trigger {
 public:
  enum class Type {
    kNew = 0,   // New task
    kContinue,  // Continue incomplete task
    kAppend,    // Append a soft-completed task
    kMax
  };

 public:
  int parse(const Json::Value& configure);
  ~Trigger();

 protected:
  static const char* kTypeValue[];
  static const char kTriggerTypeKey[];
  static const char kTriggerDomainKey[];
  static const char kTriggerIntentsKey[];

  Type                   type_;        // trigger type
  std::string            domain_;      // trigger domain
  std::set<std::string>  intents_;     // trigger intents (or)
  std::set<std::string>  slot_names_;  // trigger slot names (or)

 public:
  friend class TcpEngine;
  friend class PackEngine;
  friend std::ostream& operator<<(std::ostream& os, const Trigger& trigger);
};

std::ostream& operator<<(std::ostream& os, const Trigger& trigger);

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_TRIGGER_H_
