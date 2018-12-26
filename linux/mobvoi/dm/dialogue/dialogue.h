// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_DIALOGUE_H_
#define DIALOGUE_DIALOGUE_H_

#include <functional>
#include <string>
#include <memory>

#include "mobvoi/base/mutex.h"
#include "dialogue/context_manager.h"
#include "dialogue/ioadaptor.h"
#include "dialogue/session.h"
#include "dialogue/task_manager.h"

namespace mobvoi {
namespace dialogue {

class Dialogue {
 public:
  typedef std::function<Json::Value(const Json::Value& input,
                                    const Json::Value& session)>
      LGFunction;

  Dialogue();

  int loadTasks(const std::string& config_path);
  int loadTask(const std::string& task_form_path);
  int setIOAdaptor(std::unique_ptr<IOAdaptor> adaptor);
  int registerLG(const LGFunction& generator);

  std::string execute(const std::string& lu_result,
                      const std::string& request_info = "");

  int reset();

  int clear();

 private:
  std::string errorResponse(const std::string& msg) const;

  bool isNonQueryDomain(Input* input, LuResult* lu);

 private:
  mutable mobvoi::SharedMutex     locker_;              // execute locker
  std::unique_ptr<TaskManager>    task_manager_;
  std::unique_ptr<ContextManager> context_manager_;
  std::unique_ptr<IOAdaptor>      io_adaptor_;
  LGFunction                      generator_;
  unsigned int                    max_session_turns_;

 private:
  DISALLOW_COPY_AND_ASSIGN(Dialogue);
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_DIALOGUE_H_
