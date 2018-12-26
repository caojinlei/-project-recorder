// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_INPUT_H_
#define LG_LG_INPUT_H_

#include <map>
#include <string>
#include <vector>

#include "lg_interface/session.h"

namespace mobvoi {
namespace lg {


class LgInput {
 public:
  Session session;

  // runtime control params
  std::multimap<std::string, std::string> extras;

 public:
  std::string GetTaskName() const;
  std::string GetTaskType() const;
  std::string GetLocale() const;
  std::string GetPlatform() const;
  std::string GetRequestId() const;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_INPUT_H_
