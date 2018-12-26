// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_SESSION_H_
#define INTERFACE_SESSION_H_

#include <vector>
#include <stack>

#include "lg_interface/turn.h"

namespace mobvoi {
namespace lg {

struct Session {
 public:
  std::vector<Turn> history;
  Turn              cur_turn;
  std::stack<Turn>  activity;

 public:
  Session();

  Session& operator=(const Session& that);
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_SESSION_H_
