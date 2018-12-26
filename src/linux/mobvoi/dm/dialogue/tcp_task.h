// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_TCP_TASK_H_
#define DIALOGUE_TCP_TASK_H_

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "dialogue/parameter.h"
#include "dialogue/resolver.h"
#include "dialogue/response.h"
#include "dialogue/task_base.h"
#include "dialogue/trigger.h"
#include "dialogue/plugin_loader.h"
#include "third_party/jsoncpp/json.h"
#include "utils/json_validator.h"

namespace mobvoi {
namespace dialogue {

class TcpEngine;
class TcpTaskInstance;

class TcpTask : public TaskBase {
 public:
  static const char kClassName[];
  static int initialize(const std::string& schema);

 protected:
  static const char kSoftCompleteKey[];
  static const char kBreakableKey[];
  static const char kReturnableKey[];
  static const char kPluginPathKey[];
  static const char kTriggersKey[];
  static const char kParametersKey[];
  static const char kFinalActionKey[];
  static const char kResolversKey[];
  static const char kResponsesKey[];
  static const char kDialogActKey[];
  static const char kActionKey[];
  static const char kActionPathKey[];

  static const char kFinalActionName[];

 private:
  static std::unique_ptr<const JsonValidator> validator_;

 public:
  TcpTask();
  int parse(const std::string& config_path);
  int parse(TaskHeader* header, const Json::Value& form);
  bool isReturnable() const;
  bool check() const;
  int build(const std::string& base_path);

  std::string className() const;

  virtual ~TcpTask();

 protected:
  bool          soft_complete_;   // indicate whether the task is soft complete.
  bool          breakable_;       // indicate whether the task is breakable.
  bool          returnable_;      // indicate whether the task is returnable.
  std::string   plugin_path_;     // the path to the plugin

  Plugin*                  plugin_;      // task plugin instance
  std::vector<Trigger*>    triggers_;    // task trigger
  std::vector<Parameter*>  parameters_;  // task parameters

  std::unordered_map<std::string, size_t>     paramIndex_;  // parameter index
  std::unordered_map<std::string, Resolver*>  resolvers_;   // Resolvers
  std::unordered_map<std::string, Response*>  responses_;   // Responses

  // final action dialog acts
  Parameter   final_;
  // std::unordered_map<std::string, std::string>  dialogActs_;

  friend class TcpEngine;
  friend class TcpTaskInstance;
  friend std::ostream& operator<<(std::ostream& os, const TcpTask& tcp);
};

std::ostream& operator<<(std::ostream& os, const TcpTask& tcp);

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_TCP_TASK_H_
