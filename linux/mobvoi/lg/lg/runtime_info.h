// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_CORE_RUNTIME_INFO_H_
#define LG_CORE_RUNTIME_INFO_H_

#include <string>

namespace mobvoi {

using std::string;

// Structure for storing runtime information and passing between modules
class RuntimeInfo {
 public:
  RuntimeInfo();

 public:
  string logid;  // log id for one request
};

}  // namespace mobvoi

#endif  // LG_CORE_RUNTIME_INFO_H_
