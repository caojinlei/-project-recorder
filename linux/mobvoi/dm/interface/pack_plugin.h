// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_PACK_PLUGIN_H_
#define INTERFACE_PACK_PLUGIN_H_

#include <string>
#include <vector>

#include "interface/action.h"
#include "interface/input.h"
#include "interface/lg_result.h"
#include "interface/semantic_frame.h"
#include "interface/slot.h"

namespace mobvoi {

template<class T_>
struct ClassInfo {
  typedef T_* (*CreateInstanceFunc)();
  typedef void (*DestroyInstanceFunc)(T_*);

  std::string           _name_;
  std::string           _version_;
  CreateInstanceFunc    _create_instance_;
  DestroyInstanceFunc   _destroy_instance_;
};

namespace dialogue {
class PluginLoader;
}

class PackPlugin {
 public:
  PackPlugin();
  virtual ~PackPlugin() = default;

  // initialize task environment
  virtual int initialize() = 0;

  // execute the task by turn
  virtual int dryRun(const Input* input,             // IN: dialogue input
      const std::vector<SemanticFrame*>* relatedSF,  // IN: related LU result
      std::string* knowledge,                        // OUT: knowledge data
      std::string* knowledgeType,                    // OUT: knowledge type
      LgResult* lgResult,                            // OUT: LG result
      std::vector<Action>* actions,                  // OUT: action list
      bool* complete) = 0;                           // OUT: true: task done

  // reset the contexts
  virtual int reset() = 0;

  // deinitialize task environment
  virtual int deinitialize() = 0;

 private:
  std::string           path_;
  void*                 handler_;
  ClassInfo<PackPlugin> pluginInfo_;

 public:
  friend class mobvoi::dialogue::PluginLoader;
};

#define CHECK_DRYRUN_PARAM() \
  if (nullptr == input || nullptr == relatedSF || relatedSF->empty()) { \
    LOG(ERROR) << "unexpected input is given!"; \
    return -1; \
  } \
\
  if (nullptr == actions || nullptr == lgResult) { \
    LOG(ERROR) << "unexpected container is given!"; \
    return -1; \
  } \
\
  if (nullptr == relatedSF->at(0)) { \
    LOG(ERROR) << "null semantic frame is given"; \
  return 0; \
  }

#define REGISTER_PLUGIN(classType, version)               \
  extern "C" {                                            \
    mobvoi::classType* macro_new##classType() {           \
      return new classType();                             \
    }                                                     \
                                                          \
    void macro_del##classType(mobvoi::classType* inst) {  \
      if (nullptr != inst) delete inst;                   \
    }                                                     \
                                                          \
    mobvoi::ClassInfo<classType> PluginInfo() {           \
      mobvoi::ClassInfo<classType> info = {               \
        #classType,                                       \
        version,                                          \
        macro_new##classType,                             \
        macro_del##classType,                             \
      };                                                  \
                                                          \
      return info;                                        \
    }                                                     \
  }

}  // namespace mobvoi

#endif  // INTERFACE_PACK_PLUGIN_H_
