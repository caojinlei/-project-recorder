// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_LU_RESULT_H_
#define INTERFACE_LU_RESULT_H_

#include <vector>

#include "lg_interface/semanticframe.h"

namespace mobvoi {
namespace lg {

using std::vector;

enum class LuStatus {
  kSuccess = 0,
  kFailed,
  kNone,
};

class LuResult {
 public:
  LuStatus              status;           // LU executing status
  vector<SemanticFrame> semanticframes;   // Semantic frames (likely ordered)

 public:
  LuResult();

  LuResult(const LuResult& result);

  ~LuResult();

  LuResult& operator=(const LuResult& that);

  SemanticFrame BestSemanticFrame();

  bool IsOrdered() const;

  void SortSemanicFrames(bool descending = true);

  // check order of semantic frames
  // @return 0 if not ordered; -1 in descending order; 1 in ascending order
  int CheckOrder() const;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_LU_RESULT_H_
