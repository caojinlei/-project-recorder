// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_SEMANTIC_FRAME_H_
#define INTERFACE_SEMANTIC_FRAME_H_

#include <string>
#include <vector>

#include "interface/slot.h"

namespace mobvoi {

struct SemanticFrame {
 public:
  static const char* DOMAIN_NON_QUERY;
  static const char* DOMAIN_OTHER;

  std::string       domain;   // domain name
  std::string       intent;   // the intent
  double            score;    // the score of this semantic frame, [0, 1]
  std::vector<Slot> slots;    // the list of slot

 public:
  SemanticFrame* clone() const;
};

}  // namespace mobvoi

#endif  // INTERFACE_SEMANTIC_FRAME_H_
