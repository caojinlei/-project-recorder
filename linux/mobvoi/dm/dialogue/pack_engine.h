// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_PACK_ENGINE_H_
#define DIALOGUE_PACK_ENGINE_H_

#include <memory>
#include <vector>

#include "dialogue/pack_task_instance.h"
#include "dialogue/session.h"
#include "interface/input.h"
#include "interface/lu_result.h"
#include "interface/semantic_frame.h"

namespace mobvoi {
namespace dialogue {

class PackEngine {
 public:
  static bool isTriggered(
      std::shared_ptr<const PackTaskInstance> instance,
      std::shared_ptr<const PackTask> task,
      const Input* input,
      const LuResult* luResult,
      std::vector<SemanticFrame*>* related_sfs);

  static int dryRun(
      std::shared_ptr<const PackTask> task,
      const Input* input,
      const std::vector<SemanticFrame*>* related_sfs,
      std::shared_ptr<const Session> session,
      std::shared_ptr<PackTaskInstance> instance,
      Json::Value* knowledge,
      LgResult* lg_result,
      std::vector<Action>* actions);

 private:
  DISALLOW_COPY_AND_ASSIGN(PackEngine);
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_PACK_ENGINE_H_
