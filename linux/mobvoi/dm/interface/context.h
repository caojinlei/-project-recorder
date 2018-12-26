// Copyright 2018 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_CONTEXT_H_
#define INTERFACE_CONTEXT_H_

#include "interface/input.h"

namespace mobvoi {

struct Context {
 public:
  Context();
  const Input* input;
};

}  // namespace mobvoi

#endif  // INTERFACE_CONTEXT_H_
