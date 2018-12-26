// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TURN_H_
#define DIALOGUE_TURN_H_

#include <memory>
#include <string>
#include <vector>

#include "mobvoi/base/macros.h"
#include "dialogue/task_instance.h"
#include "interface/action.h"
#include "interface/input.h"
#include "interface/lg_result.h"
#include "interface/lu_result.h"
#include "interface/semantic_frame.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {

using dialogue::TaskInstance;

struct Turn {
 public:
  Input*                                  input;      // user input
  LuResult*                               luResult;   // LU Result

  std::vector<SemanticFrame*>             relatedSF;  // related SemanticFrame
  std::shared_ptr<dialogue::TaskInstance> task;       // task details

  Json::Value                             knowledge;  // task knowledge
  LgResult*                               lgResult;   // LG Result
  std::vector<Action>                     actions;    // final actions

  ~Turn();
};

}  // namespace mobvoi

#endif  // DIALOGUE_TURN_H_
