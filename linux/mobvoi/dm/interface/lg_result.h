// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_LG_RESULT_H_
#define INTERFACE_LG_RESULT_H_

#include <string>
#include <vector>

namespace mobvoi {

struct LgResult {
 public:
  std::string               spoken;   // spken ssml
  std::string               display;  // display text
  std::vector<std::string>  hints;    // list of hint text
};

}  // namespace mobvoi

#endif  // INTERFACE_LG_RESULT_H_
