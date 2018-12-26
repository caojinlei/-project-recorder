// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_LG_RESULT_H_
#define INTERFACE_LG_RESULT_H_

#include <string>
#include <vector>
#include <unordered_map>

namespace mobvoi {
namespace lg {

class LgResult {
 public:
  LgResult();

 public:
  bool                      success;
  std::string               display_text;
  std::string               spoken_ssml;
  std::vector<std::string>  hints;

  std::unordered_map<std::string, std::string> extras;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_LG_RESULT_H_
