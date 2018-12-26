// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: diai@mobvoi.com (Ai Di)

#ifndef DIALOGUE_PLUGIN_LOADER_H_
#define DIALOGUE_PLUGIN_LOADER_H_

#include <string>
#include <unordered_map>

#include "mobvoi/base/macros.h"
#include "interface/plugin.h"
#include "interface/pack_plugin.h"

namespace mobvoi {
namespace dialogue {

class PluginLoader {
 public:
  static PluginLoader* getInstance();

  Plugin* load(const std::string& path);
  void unload(const std::string& path);
  void unload(Plugin* plugin);

  PackPlugin* loadPlugin(const std::string& path);
  void unloadPlugin(PackPlugin* plugin);

 private:
  PluginLoader() = default;
  std::unordered_map<std::string, Plugin*>      plugin_list_;
  std::unordered_map<std::string, PackPlugin*>  plugins_;

  DISALLOW_COPY_AND_ASSIGN(PluginLoader);
};

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_PLUGIN_LOADER_H_
