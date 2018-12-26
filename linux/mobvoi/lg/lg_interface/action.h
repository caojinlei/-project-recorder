// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_ACTION_H_
#define INTERFACE_ACTION_H_

#include <map>
#include <string>

namespace mobvoi {
namespace lg {

using std::multimap;
using std::string;

enum class ActionStatus {
  kSuccess = 0,
  kTimeout,
  kFailed,
  kNone,
};

// Structure for dialogue action.
struct Action {
 public:
  bool                      inner;
  std::string               name;
  std::string               cmd;
  std::string               version;
  multimap<string, string>  params;

  ActionStatus              status;
  std::string               message;

 public:
  Action();
  ~Action();
  Action& operator=(const Action& that);
  std::string Status() const;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_ACTION_H_
