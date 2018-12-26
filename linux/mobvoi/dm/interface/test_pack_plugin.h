// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_TEST_PACK_PLUGIN_H_
#define INTERFACE_TEST_PACK_PLUGIN_H_

#include <string>
#include <vector>

#include "interface/pack_plugin.h"

namespace mobvoi {

class PackPluginTest : public mobvoi::PackPlugin {
 public:
  int initialize();
  int dryRun(const Input* input, const std::vector<SemanticFrame*>* relatedSF,
      std::string* knowledge, std::string* knowledgeType, LgResult* lgResult,
      std::vector<Action>* actions, bool* complete);
  int reset();
  int deinitialize();
};

}  // namespace mobvoi

#endif  // INTERFACE_TEST_PACK_PLUGIN_H_
