// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_PARAMETER_H_
#define DIALOGUE_PARAMETER_H_

#include <set>
#include <string>
#include <vector>
#include <unordered_map>

#include "dialogue/boolean_expression.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace dialogue {

class TcpTask;
class TcpTaskInstance;
class TcpEngine;

class Parameter {
 public:
  static const char* kParameterTypeValue[];
  static const char kParameterNameKey[];
  static const char kParameterTypeKey[];
  static const char kParameterRequiredKey[];
  static const char kParameterSingleKey[];
  static const char kParameterPageSizeKey[];
  static const char kParameterResolverKey[];
  static const char kParameterSlotsKey[];
  static const char kParameterParametersKey[];
  static const char kParameterDialogActKey[];
  static const char kParameterImplicitConfirmKey[];
  static const char kParameterSkipProcessKey[];

  enum class DataType {
    kString = 0,
    kBool,
    kInteger,
    kFloat,
    kJson,
  };

  enum class DialogActType {
    kRequire = 0,
    kInformFailure,
    kAskSelect,
    kAskConfirm,
    kInformReject,
  };

 public:
  int Parse(const Json::Value& configure);
  Parameter();
  ~Parameter();

 protected:
  std::string name_;          // parameter name
  DataType    dataType_;      // parameter data type
  std::string typeName_;      // parameter type name if type is json
// bool        optional_;     // indicate whether the parameter is optional
  std::string required_;      // required condition string
  std::string confirm_;       // implicit confirm condition string
  std::string skip_;          // skip process if optional
  bool        single_;        // indicate whether the parameter is single
  int         page_size_;     // the item count per page
  std::string resolver_;      // parameter resolver name

  BooleanExpression*  required_condition_;  // required condition
  BooleanExpression*  implicit_confirm_;    // implicit confirm
  BooleanExpression*  skip_condition_;      // skip process condition

  std::vector<std::string>  slots_;       // related slot names
  std::vector<std::string>  parameters_;  // related parameter names

  std::set<std::string>   dependence_;    // dependent parameter names

  // dialog acts
  std::unordered_map<std::string, std::string>  dialogActs_;

 public:
  friend class TcpEngine;
  friend class TcpTask;
  friend class TcpTaskInstance;
  friend std::ostream& operator<<(std::ostream& os, const Parameter& parameter);
};

std::ostream& operator<<(std::ostream& os, const Parameter& parameter);

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_PARAMETER_H_
