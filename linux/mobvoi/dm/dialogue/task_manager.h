// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TASK_MANAGER_H_
#define DIALOGUE_TASK_MANAGER_H_

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "mobvoi/base/macros.h"
#include "mobvoi/base/mutex.h"
#include "dialogue/task.h"
#include "dialogue/turn.h"

namespace mobvoi {
namespace dialogue {

class TaskManager {
 public:
  TaskManager();
  int registTask(const std::string& formPath);
  std::shared_ptr<const Task> getTaskByName(const std::string& name,
      const std::string& version) const;

  std::shared_ptr<const Task> triggerTask(const Turn* turn,
      std::vector<SemanticFrame*>* related_sfs) const;

  typedef std::vector<SemanticFrame*> SFList;
  typedef std::shared_ptr<const Task> PCTask;
  int triggerTasks(const Turn* turn,
      std::vector<std::pair<PCTask, SFList*>>* triggered_tasks) const;

  ~TaskManager();

 private:
  std::map<std::string, std::shared_ptr<Task>>  tasks_;         // tasks
  mutable mobvoi::SharedMutex                   task_locker_;   // task locker

 private:
  DISALLOW_COPY_AND_ASSIGN(TaskManager);
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_TASK_MANAGER_H_
