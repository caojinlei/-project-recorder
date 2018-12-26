// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_SLOT_H_
#define INTERFACE_SLOT_H_

#include <string>

namespace mobvoi {

struct Slot {
 public:
  Slot();

  std::string   name;     // slot name
  std::string   value;    // raw value
  std::string   normal;   // normalized value
  unsigned int  turnId;   // turn id in which turn the slot is created, from '0'
};

}  // namespace mobvoi

#endif  // INTERFACE_SLOT_H_
