// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: diai@mobvoi.com (Ai Di)

#ifndef INTERFACE_PLUGIN_H_
#define INTERFACE_PLUGIN_H_

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "dialogue/parameter_instance.h"
#include "interface/action.h"
#include "interface/context.h"
#include "interface/slot.h"

namespace mobvoi {

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;
using std::placeholders::_4;

namespace dialogue {
class PluginLoader;
}

// Virtual plugin interface.
class Plugin {
 public:
  friend class mobvoi::dialogue::PluginLoader;

  Plugin();
  virtual ~Plugin() = default;
  virtual int initialize() = 0;
  virtual int execute(const std::vector<const Slot*>& slots,
      const std::vector<const dialogue::ParameterInstance*>& parameters,
      Action* action) const = 0;
  virtual int deinitialize() = 0;

  int invokeMethod(const std::string& method,
      const Context& context,
      const std::vector<const Slot*>& slots,
      const std::vector<const dialogue::ParameterInstance*>& parameters,
      std::vector<std::string>* values) const;

 protected:
#define REGISTER_CALLBACK(classType, func) \
  registerResolver(#func, std::bind(&classType::func, this, _1, _2, _3, _4));

  typedef std::function<int(
          const Context& context,
          const std::vector<const Slot*>& slots,
          const std::vector<const dialogue::ParameterInstance*>& parameters,
          std::vector<std::string>* values)>
          ResolveFunction;

  bool registerResolver(std::string name, const ResolveFunction& func);

 private:
  std::string                             library_path_;
  void*                                   library_handle_;
  struct PluginDetails*                   details_;
  std::map<std::string, ResolveFunction>  resolvers_;
};

typedef Plugin* (*CreatePluginFunc)();
typedef void (*DestroyPluginFunc)(Plugin*);

// Plugin details structure.
struct PluginDetails {
  const char*       fileName;
  const char*       className;
  const char*       pluginVersion;
  CreatePluginFunc  initializeFunc;
  DestroyPluginFunc deinitializeFunc;
};

#define REGISTER_CLASS(classType, pluginVersion)           \
  extern "C" {                                             \
    mobvoi::Plugin* createPlugin()                         \
    {                                                      \
      return new classType();                              \
    }                                                      \
    void destroyPlugin(mobvoi::Plugin* plugin)             \
    {                                                      \
      if (nullptr != plugin) delete plugin;                \
    }                                                      \
    mobvoi::PluginDetails exports =                        \
    {                                                      \
      __FILE__,                                            \
      #classType,                                          \
      pluginVersion,                                       \
      createPlugin,                                        \
      destroyPlugin,                                       \
    };                                                     \
  }

}  // namespace mobvoi

#endif  // INTERFACE_PLUGIN_H_
