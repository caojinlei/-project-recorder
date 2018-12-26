// Copyright 2018 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_PLUGIN_HELPER_H_
#define INTERFACE_PLUGIN_HELPER_H_

#include <string>

namespace mobvoi {

class PluginHelper {
 public:
  static std::string LCS(const std::string& str1, const std::string& str2);
};

}  // namespace mobvoi

#endif  // INTERFACE_PLUGIN_HELPER_H_
