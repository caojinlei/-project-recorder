// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_APPPROXY_H_
#define LG_LG_APPPROXY_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "lg/lg_appbase.h"
#include "lg/lg_rules.h"
#include "lg/lg_settings.h"

namespace mobvoi {
namespace lg {

class LgAppProxy {
 public:
  static LgAppProxy* CreateInstance(const std::string& manifest);

  ~LgAppProxy();

  std::string GetResource(const std::string& id,
                          const std::string& locale) const;

  std::string Invoke(const std::string& method,
                     const LgContext& context) const;

  std::string ResolveKnowlege(const LgContext& context,
                              const std::string& jpath) const;

  std::string GetSlot(const LgContext& context,
                      const std::string& slotname) const;

  std::string GetRawSlot(const LgContext& context,
                         const std::string& slotname) const;

  std::string GetCanonicalSlot(const LgContext& context,
                               const std::string& slotname) const;

  const std::map<std::string, std::string>* GetResources(
      const std::string& locale) const;

  const LgRules* GetRules() const;

  const LgSettings* GetSettings() const;

  bool MatchProxy(const std::string& task,
                  const std::string& engine_type,
                  const std::string& locale,
                  const std::string& platform) const;

  inline std::string AppName() const {
    return this->name_;
  }

  inline std::string AppId() const {
    return this->id_;
  }

  inline double GetWeight() const {
    return weight_;
  }

  inline std::string GetPath() const {
    return path_;
  }

 private:
  LgAppProxy();

  bool LoadApp(const std::string& app_path);

  bool MatchProxy(const std::string& task,
                  const std::string& locale,
                  const std::string& platform) const;

 private:
  double        weight_;
  std::string   path_;

  std::string   name_;
  std::string   id_;
  std::string   version_;
  std::string   publisher_;
  void*         handler_;
  LgAppBase*    application_;
  LgRules*      ruleset_;
  LgSettings*   settings_;
  std::string   default_locale_;

  std::vector<std::string> supported_platforms_;
  std::vector<std::string> supported_locales_;
  std::vector<std::string> supported_task_types_;
  std::vector<std::string> supported_tasks_;

  std::map<std::string, std::map<std::string, std::string>*> resources_;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_APPPROXY_H_
