// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_CONDITIONS_H_
#define LG_LG_CONDITIONS_H_

#include <string>
#include <vector>

#include "lg/xml_parser.h"

namespace mobvoi {
namespace lg {

class LgConditionBase {
 public:
  static const char kTypeValue[];

 public:
  virtual ~LgConditionBase();

  virtual std::string Type() const {
    return kTypeValue;
  }
};

enum class LogicalOperatorType {
  kAnd = 0,
  kOr,
  kNot,
};

enum class OperatorType {
  kEQ = 0,         // ==, =, <>
  kNE,             // !=
  kGT,             // >
  kLT,             // <
  kGE,             // >=
  kLE,             // <=
  kContains,       // [
  kContainedBy,    // ]
};

class LgConditions : public LgConditionBase {
 public:
  static const char kTypeValue[];

  static LgConditions* Parse(xmlNodePtr node);

 public:
  LgConditions();

  ~LgConditions();

  inline std::string Type() const {
    return kTypeValue;
  }

 public:
  std::vector<LgConditionBase*> conditions;

  LogicalOperatorType op;
};

class LgCondition : public LgConditionBase {
 public:
  static const char kTypeValue[];

  static LgCondition* Parse(xmlNodePtr node);

 public:
  LgCondition();

  ~LgCondition();

  inline std::string Type() const {
    return kTypeValue;
  }

 public:
  std::string   slot;
  std::string   function;
  std::string   jpath;

  std::string   slotValueType;
  std::string   expected;

  OperatorType  op;

  bool          is_numeric;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_CONDITIONS_H_
