// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TASK_BASE_H_
#define DIALOGUE_TASK_BASE_H_

#include <string>

#include "dialogue/task_header.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace dialogue {

class TaskBase {
 public:
  static const char kClassName[];

 public:
  virtual int parse(TaskHeader* header, const Json::Value& configure);
  virtual std::string className() const;
  virtual ~TaskBase();

  TaskBase(): header_(nullptr) {}

  inline std::string getName() const {
    if (nullptr != header_) {
      return header_->name_;
    } else {
      return "";
    }
  }

  inline std::string getVersion() const {
    if (nullptr != header_) {
      return header_->version_;
    } else {
      return "";
    }
  }

  inline std::string getDescription() const {
    if (nullptr != header_) {
      return header_->desc_;
    } else {
      return "";
    }
  }

  inline std::string getEngineName() const {
    if (nullptr != header_) {
      return header_->engine_;
    } else {
      return "";
    }
  }

  inline std::string getEngineVersion() const {
    if (nullptr != header_) {
      return header_->engineVersion_;
    } else {
      return "";
    }
  }

  inline int getPriority() const {
    if (nullptr != header_) {
      return header_->priority_;
    } else {
      return 0;
    }
  }

 protected:
  TaskHeader* header_;      // task header definition;
};

}  // namespace dialogue
}  // namespace mobvoi



#endif  // DIALOGUE_TASK_BASE_H_
