// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TCP_TASK_INSTANCE_H_
#define DIALOGUE_TCP_TASK_INSTANCE_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include "dialogue/parameter_instance.h"
#include "dialogue/task_instance.h"
#include "dialogue/tcp_task.h"

namespace mobvoi {

class CountVar;
class KnowledgeVar;
class ResolverVar;
class Serializer;

namespace dialogue {

class TcpEngine;

class TcpTaskInstance : public TaskInstance {
 public:
  static const char kClassName[];

 public:
  explicit TcpTaskInstance(std::shared_ptr<const TcpTask> task_form);

  bool isActive(std::shared_ptr<const TaskBase> taskForm) const;

  std::string invoke(const std::string& name,
                     const std::string& param,
                     const std::map<std::string, const Slot*>& slots,
                     const std::string& def) const;

  std::string className() const;
  ~TcpTaskInstance();

 protected:
  TcpTaskInstance();

 protected:
  std::string       focus_;

  std::unordered_map<std::string, ParameterInstance*> parameters_;

  static bool IsRequired(Parameter* parameter,
                         std::shared_ptr<TcpTaskInstance> instance,
                         const std::map<std::string, const Slot*>& slots,
                         bool def);

  static bool NeedConfirm(const Parameter* parameter,
                          std::shared_ptr<TcpTaskInstance> instance,
                          const std::map<std::string, const Slot*>& slots,
                          bool def);

  static bool IsSkipProcess(const Parameter* parameter,
                            std::shared_ptr<TcpTaskInstance> instance,
                            const std::map<std::string, const Slot*>& slots,
                            bool def);

 public:
  friend class CountVar;
  friend class KnowledgeVar;
  friend class ResolverVar;
  friend class TcpEngine;
  friend class mobvoi::Serializer;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_TCP_TASK_INSTANCE_H_
