// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_SERIALIZER_H_
#define DIALOGUE_SERIALIZER_H_

#include <string>

#include "mobvoi/base/macros.h"
#include "dialogue/pack_task_instance.h"
#include "dialogue/session.h"
#include "dialogue/task_instance.h"
#include "dialogue/tcp_task_instance.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {

class Serializer {
 public:
  static const char kClassTypeKey[];

 public:
  static Json::Value serialize(const Session& session);
  static Json::Value serialize(const Turn& turn);
  static Json::Value serialize(const Input& input);
  static Json::Value serialize(const Location& location);
  static Json::Value serialize(const LuResult& lu_result);
  static Json::Value serialize(const SemanticFrame& sf);
  static Json::Value serialize(const TaskInstance& instance);
  static Json::Value serialize(const dialogue::TcpTaskInstance& instance);
  static Json::Value serialize(const dialogue::ParameterInstance param);
  static Json::Value serialize(const dialogue::PackTaskInstance& instance);
  static Json::Value serialize(const LgResult& lg_result);
  static Json::Value serialize(const Action& action);
  static Json::Value serialize(const Slot& slot);

  static bool deserialize(const Json::Value& root, Session* session);
  static bool deserialize(const Json::Value& root, Turn* turn);
  static bool deserialize(const Json::Value& root, Input* input);
  static bool deserialize(const Json::Value& root, Location* location);
  static bool deserialize(const Json::Value& root, LuResult* lu_result);
  static bool deserialize(const Json::Value& root, SemanticFrame* sf);
  static bool deserialize(const Json::Value& root, TaskInstance* instance);
  static bool deserialize(const Json::Value& root,
      dialogue::TcpTaskInstance* instance);
  static bool deserialize(const Json::Value& root,
      dialogue::ParameterInstance* param);
  static bool deserialize(const Json::Value& root,
      dialogue::PackTaskInstance* instance);
  static bool deserialize(const Json::Value& root, LgResult* lg_result);
  static bool deserialize(const Json::Value& root, Action* action);
  static bool deserialize(const Json::Value& root, Slot* slot);

 private:
  DISALLOW_COPY_AND_ASSIGN(Serializer);
};

}  // namespace mobvoi

#endif  // DIALOGUE_SERIALIZER_H_
