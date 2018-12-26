// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_SESSION_H_
#define DIALOGUE_SESSION_H_

#include <memory>
#include <string>
#include <vector>

#include "dialogue/task_instance.h"
#include "dialogue/turn.h"

namespace mobvoi {

using dialogue::TaskInstance;

struct Session {
 public:
  std::string                                 session_id;
  std::vector<std::shared_ptr<Turn>>          history;
  std::vector<std::shared_ptr<TaskInstance>>  active_tasks;
};

}  // namespace mobvoi

#endif  // DIALOGUE_SESSION_H_
