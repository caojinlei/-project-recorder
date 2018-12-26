// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_ACTION_H_
#define INTERFACE_ACTION_H_

#include <string>
#include <unordered_map>

namespace mobvoi {

enum class ListenMode {
  kNormal = 0,      // default mode, active word is required for inputing
  kAutoListen,      // micphone opened, active word is not required; auto=true
  kMultiKeywords,   // multi keyword is accepted without active word;
};

std::string ListenMode2String(ListenMode mode);

ListenMode String2ListenMode(const std::string& str);

struct Action {
 public:
  Action();

  std::string  name;        // action name
  std::string  cmd;         // action command
  ListenMode   listenMode;  // linsten mode
  bool         inner;       // indentified whether is executed from server side.

  // action parameters
  std::unordered_multimap<std::string, std::string> parameters;
};

}  // namespace mobvoi

#endif  // INTERFACE_ACTION_H_
