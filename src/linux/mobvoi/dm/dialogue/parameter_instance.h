// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_PARAMETER_INSTANCE_H_
#define DIALOGUE_PARAMETER_INSTANCE_H_

#include <string>
#include <vector>

#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace dialogue {

enum class ParameterStatus {
  kMissed = 0,
  kResolveSuccess,
  kResolveFailed,
  kDisambiguated,
  kNeedSelectConfirmed,
  kNeedConfirmed,
  kConfirmFailured,
  kCancelled,
  kSelectFailed,
};

std::string ParamStatus2DialogAct(const ParameterStatus& status);
bool DialogAct2ParamStatus(const std::string& str, ParameterStatus* status);

struct ParameterInstance {
 public:
  unsigned int              turnId;     // last updated turn Id
  std::string               name;       // parameter name
  ParameterStatus           status;     // parameter status
  int                       code;       // parameter code
  std::vector<Json::Value>  values;     // parameter values
  int                       selectId;   // parameter select Id
  int                       selectPage;  // parameter select page, start from 0
  int                       pageCount;  // parameter page count
  int                       pageItemCount;  // parameter page item count

  ParameterInstance();
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_PARAMETER_INSTANCE_H_
