// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_LU_RESULT_H_
#define INTERFACE_LU_RESULT_H_

#include <vector>

#include "interface/semantic_frame.h"

namespace mobvoi {

class LuResult : public std::vector<SemanticFrame*> {
};

}  // namespace mobvoi

#endif  // INTERFACE_LU_RESULT_H_
