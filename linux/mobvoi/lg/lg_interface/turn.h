// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_TURN_H_
#define INTERFACE_TURN_H_

#include "lg_interface/hypothesis.h"
#include "lg_interface/lg_result.h"
#include "lg_interface/lu_result.h"
#include "lg_interface/turn_input.h"

namespace mobvoi {
namespace lg {


// Structure for turn context in conversation session
struct Turn {
 public:
  TurnInput     input;       // input of current turn
  LuResult      luresult;    // LU result
  Hypothesis    hypothesis;  // dialogue hypothesis
  LgResult      lgresult;    // LG result

 public:
  Turn();

  Turn& operator=(const Turn& that);

  int TurnId() const;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_TURN_H_
