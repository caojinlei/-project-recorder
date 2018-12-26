// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_IOADAPTOR_H_
#define DIALOGUE_IOADAPTOR_H_

#include <string>
#include <vector>

#include "dialogue/turn.h"
#include "interface/input.h"
#include "interface/lu_result.h"
#include "interface/semantic_frame.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace dialogue {

class IOAdaptor {
 public:
  virtual bool Parse(const std::string& lu_result_json,
                     Input* input,
                     LuResult* lu_result,
                     unsigned int turn_id = 0) const;

  virtual bool Parse(const std::string& lu_result_json,
                     const std::string& request_info,
                     Input* input,
                     LuResult* lu_result,
                     unsigned int turn_id = 0) const;

  virtual bool ParseInput(const Json::Value& root,
                          Input* input,
                          unsigned int turn_id = 0) const;

  virtual bool ParseLuResult(const Json::Value& root,
                             LuResult* lu_result,
                             unsigned int turn_id = 0) const;

  virtual bool ParseSemanticFrame(const Json::Value& root,
                                  SemanticFrame* semantic_frame,
                                  unsigned int turn_id = 0) const;

  virtual bool Generate(const Turn* turn, std::string* response) const;

  virtual bool GenerateNonQueryResponse(const Turn* turn,
                                        std::string* response) const;

  virtual ~IOAdaptor();
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_IOADAPTOR_H_
