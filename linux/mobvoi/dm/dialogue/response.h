// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_RESPONSE_H_
#define DIALOGUE_RESPONSE_H_

#include <string>
#include <vector>
#include <iostream>

#include "dialogue/language_generator.h"
#include "interface/action.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace dialogue {

class TcpEngine;

class Response {
 public:
  static const char kResponseNameKey[];
  static const char kResponsePromptsKey[];
  static const char kResponseSpokenKey[];
  static const char kResponseDisplayKey[];
  static const char kResponseHintsKey[];
  static const char kResponseActionKey[];
  static const char kActionNameKey[];
  static const char kActionCmdKey[];
  static const char kActionListenModeKey[];
  static const char kActionInnerKey[];

  int parse(const Json::Value& configure);
  Response();
  ~Response();
  std::string getName();

 protected:
  std::string       name_;          // response name

  std::vector<LanguageGenerator*> lgSpoken_;   // LG spoken template
  std::vector<LanguageGenerator*> lgDisplay_;  // LG display template
  std::vector<LanguageGenerator*>  lgHints_;   // LG hint templates

  bool        action_enabled_;
  std::string action_name_;
  std::string action_cmd_;
  ListenMode  action_listen_mode_;
  bool        action_inner_;

 public:
  friend class TcpEngine;
  friend std::ostream& operator<<(std::ostream& os, const Response& response);
};

std::ostream& operator<<(std::ostream& os, const Response& response);

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_RESPONSE_H_
