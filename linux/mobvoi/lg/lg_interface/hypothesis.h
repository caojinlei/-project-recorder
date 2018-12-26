// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_HYPOTHESIS_H_
#define INTERFACE_HYPOTHESIS_H_

#include <map>
#include <string>
#include <vector>

#include "lg_interface/taskframe.h"
#include "lg_interface/semanticframe.h"

namespace mobvoi {
namespace lg {

using std::string;
using std::vector;

enum class HypothesisStatus {
  kSuccess = 0,
  kFailed,
  kNone,
};

struct Hypothesis {
 public:
  HypothesisStatus      status;
  vector<SemanticFrame> semanticframes;
  TaskFrame             taskframe;

 public:
  Hypothesis();

  Hypothesis& operator=(const Hypothesis& that);
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_HYPOTHESIS_H_
