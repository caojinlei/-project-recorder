// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_TASKFRAME_H_
#define INTERFACE_TASKFRAME_H_

#include <map>
#include <string>
#include <vector>

#include "lg_interface/action.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace lg {

using std::multimap;
using std::string;

// enumerate task status.
enum class TaskStatus {
  kProcessing,
  kComplete,
  kError,
  kNone,
};

struct TaskFrame {
 public:
  string                    provider;
  string                    version;
  string                    taskname;
  string                    taskid;
  TaskStatus                status;
  Json::Value               knowledge;
  std::vector<Action>       actions;
  multimap<string, string>  data;

  Json::Value               details;

 public:
  TaskFrame();
  TaskFrame& operator=(const TaskFrame& that);
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_TASKFRAME_H_
