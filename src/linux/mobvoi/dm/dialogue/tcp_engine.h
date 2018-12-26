// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TCP_ENGINE_H_
#define DIALOGUE_TCP_ENGINE_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "dialogue/session.h"
#include "dialogue/tcp_task.h"
#include "dialogue/tcp_task_instance.h"
#include "interface/input.h"
#include "interface/lu_result.h"
#include "interface/semantic_frame.h"

namespace mobvoi {
namespace dialogue {

class TcpEngine {
 public:
  static bool isTriggered(
      std::shared_ptr<const TcpTaskInstance> instance,
      std::shared_ptr<const TcpTask> task,
      const Input* input,
      const LuResult* lu_result,
      std::vector<SemanticFrame*>* related_sfs);

  static int dryRun(std::shared_ptr<const TcpTask> task,
      const Input* input,
      const std::vector<SemanticFrame*>* related_sfs,
      std::shared_ptr<const Session> session,
      std::shared_ptr<TcpTaskInstance> instance,
      Json::Value* knowledge,
      LgResult* lgResult,
      std::vector<Action>* actions);

 private:
  static bool CheckAndProcessCancel(std::shared_ptr<TcpTaskInstance> instance,
                                    const std::vector<SemanticFrame *> *related_sfs);

  static std::string ProcessParams(const Input *input,
                                   std::shared_ptr<const TcpTask> task,
                                   std::shared_ptr<TcpTaskInstance> instance,
                                   const std::map<std::string,const Slot *> &all_slots);

  static bool CheckAndProcessFinalAction(std::shared_ptr<const TcpTask> task,
                                         std::shared_ptr<TcpTaskInstance> instance,
                                         Action *action);

  static bool CheckAndProcessDialogAction(std::shared_ptr<const TcpTask> task,
                                          std::shared_ptr<TcpTaskInstance> instance,
                                          Action *action);

  /*
  static bool ProcessSelect(const std::vector<SemanticFrame*>* relatedSF,
                            ParameterInstance* instance);
   */

  static bool ProcessSelect(const std::vector<SemanticFrame *> *related_sfs,
                            const Input *input, ParameterInstance *instance,
                            const Parameter *param);

  static bool RandomSelectAndClean(std::vector<std::string> *list,
                                   size_t count = 1);

  DISALLOW_COPY_AND_ASSIGN(TcpEngine);
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_TCP_ENGINE_H_
