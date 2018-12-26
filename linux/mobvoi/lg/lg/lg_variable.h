// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_VARIABLE_H_
#define LG_LG_VARIABLE_H_

#include <string>

#include "lg/xml_parser.h"

namespace mobvoi {
namespace lg {

enum class CapitalType {
  kNone = 0,
  kFirst,
  kEachFirst,
  kAll,
  kAllLower,
};

class LgVariable {
 public:
  static LgVariable* Parse(xmlNodePtr node);

 public:
  LgVariable();

 public:
  std::string name;
  std::string slot;
  std::string function;
  std::string jpath;
  std::string slotValueType;
  CapitalType capital;
  std::string tag;
  std::string attributes;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_VARIABLE_H_
