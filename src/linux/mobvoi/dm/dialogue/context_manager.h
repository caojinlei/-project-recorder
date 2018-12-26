// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_CONTEXT_MANAGER_H_
#define DIALOGUE_CONTEXT_MANAGER_H_

#include <memory>
#include <string>

#include "mobvoi/base/macros.h"
#include "dialogue/session.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace dialogue {

class ContextManager {
 public:
  ContextManager();

  int initialize();
  int reset();

  std::shared_ptr<Session> getContext();
  int setContext(std::shared_ptr<Session> context);

  std::string getContextAsJson() const;
  int setContextAsJson(const std::string& context);

 protected:
  int clear();

 protected:
  std::shared_ptr<Session>    context_;         // session context

 private:
  DISALLOW_COPY_AND_ASSIGN(ContextManager);
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_CONTEXT_MANAGER_H_
