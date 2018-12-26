// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TASK_INSTANCE_H_
#define DIALOGUE_TASK_INSTANCE_H_

#include <memory>
#include <string>
#include <vector>

#include "dialogue/task_base.h"
#include "interface/semantic_frame.h"

namespace mobvoi {

class Serializer;

namespace dialogue {

class TaskInstance {
 public:
  static const char kClassName[];

  enum class Status {
    kNone = 0,    // not set
    kInProcess,   // task is in processing, also means active
    kComplete,    // task is completed success
    kFailed,      // task is failed while processing or take final action
    kCancelled,   // task is cancelled
  };

 public:
  explicit TaskInstance(std::shared_ptr<const TaskBase> task_form);

  virtual bool isActive(std::shared_ptr<const TaskBase> task_form) const;
  virtual std::string className() const;
  virtual ~TaskInstance();

  inline std::string getId() const {
    return taskId_;
  }

  inline std::string getName() const {
    return name_;
  }

  inline std::string getVersion() const {
    return version_;
  }

  inline std::string getDesc() const {
    return desc_;
  }

  inline std::string getEngine() const {
    return engine_;
  }

  inline std::string getEngineVersion() const {
    return engineVersion_;
  }

  inline Status getStatus() const {
    return status_;
  }

  inline std::string getStatusName() const {
    switch (status_) {
      case Status::kCancelled:
        return "Cancelled";

      case Status::kComplete:
        return "Complete";

      case Status::kFailed:
        return "Failed";

      case Status::kInProcess:
        return "InProcess";

      case Status::kNone:
        return "None";

      default:
        return "-";
    }
  }

  inline Status convert2Status(const std::string& name) const {
    if (name == "Cancelled") {
      return Status::kCancelled;
    } else if (name == "Complete") {
      return Status::kComplete;
    } else if (name == "Failed") {
      return Status::kFailed;
    } else if (name == "InProcess") {
      return Status::kInProcess;
    } else {
      return Status::kNone;
    }
  }

  inline void setStatus(const Status& status) {
    status_ = status;
  }

 protected:
  TaskInstance();

 protected:
  std::string taskId_;          // task UUID
  std::string name_;            // task name
  std::string version_;         // task version
  std::string desc_;            // task description
  std::string engine_;          // task engine type
  std::string engineVersion_;   // task engine version
  Status      status_;          // task status
  size_t      updateTurnId_;    // last update turn id;

  std::vector<SemanticFrame*>   relatedSF;  // related SemanticFrames

 public:
  friend class mobvoi::Serializer;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_TASK_INSTANCE_H_
