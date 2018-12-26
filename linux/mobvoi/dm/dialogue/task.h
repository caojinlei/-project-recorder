// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TASK_H_
#define DIALOGUE_TASK_H_

#include <memory>
#include <string>
#include <vector>

#include "dialogue/session.h"
#include "dialogue/task_base.h"
#include "dialogue/task_instance.h"
#include "interface/action.h"
#include "interface/input.h"
#include "interface/lu_result.h"
#include "interface/semantic_frame.h"

namespace mobvoi {
namespace dialogue {

class Task {
 public:
  Task(): taskForm_(nullptr) {}

  int parse(const std::string& formPath);

  bool isTriggered(std::shared_ptr<const TaskInstance> instance,
        const Input* input,
        const LuResult* lu_result,
        std::vector<SemanticFrame*>* related_sfs) const;

  bool isActive(std::shared_ptr<const TaskInstance> instance) const;

  bool isReturnable() const;

  TaskInstance* createInstance(const Input* input,
      const LuResult* lu_result,
      std::vector<SemanticFrame*>* related_sfs) const;

  int dryRun(const Input* input,
      const std::vector<SemanticFrame*>* related_sfs,
      std::shared_ptr<const Session> session,
      std::shared_ptr<TaskInstance> task_instance,
      Json::Value* knowledge,
      LgResult* lg_result,
      std::vector<Action>* actions) const;

  inline std::string getName() const {
    if (taskForm_) {
      return taskForm_->getName();
    } else {
      return "";
    }
  }

  inline std::string getVersion() const {
    if (taskForm_) {
      return taskForm_->getVersion();
    } else {
      return "";
    }
  }

  inline std::string getDescription() const {
    if (taskForm_) {
      return taskForm_->getDescription();
    } else {
      return "";
    }
  }

  inline int getPriority() const {
    if (taskForm_) {
      return taskForm_->getPriority();
    } else {
      return 0;
    }
  }

 protected:
  std::shared_ptr<TaskBase> taskForm_;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_TASK_H_
