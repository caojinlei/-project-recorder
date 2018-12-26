// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_PACK_TASK_H_
#define DIALOGUE_PACK_TASK_H_

#include <memory>
#include <string>
#include <vector>

#include "dialogue/task_base.h"
#include "dialogue/trigger.h"
#include "dialogue/plugin_loader.h"
#include "third_party/jsoncpp/json.h"
#include "utils/json_validator.h"

namespace mobvoi {
namespace dialogue {

class PackEngine;
class PackTaskInstance;

class PackTask : public TaskBase {
 public:
  static const char kClassName[];
  static int initialize(const std::string& schema);

 private:
  static std::unique_ptr<const JsonValidator> validator_;

 public:
  static const char kSoftCompleteKey[];
  static const char kBreakableKey[];
  static const char kReturnableKey[];
  static const char kPluginPathKey[];
  static const char kTriggersKey[];
  static const char kEnableSCOKey[];

 public:
  PackTask();
  virtual ~PackTask();

  int parse(TaskHeader* header, const Json::Value& form);
  bool isReturnable() const;
  bool enableSCO() const;
  int build(const std::string& basePath);
  std::string className() const;

 protected:
  bool          soft_complete_;   // indicate whether the task is soft complete.
  bool          breakable_;       // indicate whether the task is breakable.
  bool          returnable_;      // indicate whether the task is returnable.
  bool          enable_sco_;      // indicate whether enable sco.
  std::string   plugin_path_;     // the path to the plugin

  PackPlugin*              plugin_;      // task plugin instance
  std::vector<Trigger*>    triggers_;    // task trigger

 public:
  friend class PackEngine;
  friend class PackTaskInstance;
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_PACK_TASK_H_
