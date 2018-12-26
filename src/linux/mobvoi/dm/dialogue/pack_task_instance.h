// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_PACK_TASK_INSTANCE_H_
#define DIALOGUE_PACK_TASK_INSTANCE_H_

#include <memory>
#include <string>

#include "dialogue/pack_task.h"
#include "dialogue/task_instance.h"

namespace mobvoi {

class Serializer;

namespace dialogue {

class PackEngine;

class PackTaskInstance : public TaskInstance {
 public:
  static const char kClassName[];

 public:
  explicit PackTaskInstance(std::shared_ptr<const PackTask> task_form);

  bool isActive(std::shared_ptr<const TaskBase> task_form) const;

  std::string className() const;
  ~PackTaskInstance();

 protected:
  PackTaskInstance();

 public:
  friend class PackEngine;
  friend class mobvoi::Serializer;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_PACK_TASK_INSTANCE_H_
