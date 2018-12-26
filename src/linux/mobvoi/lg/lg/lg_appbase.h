// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_APPBASE_H_
#define LG_LG_APPBASE_H_

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "lg/lg_context.h"
#include "lg_interface/semanticframe.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace lg {

class LgAppBase {
 public:
  static const char kNULLValue[];

  LgAppBase();

  std::string ResolveKnowlege(const LgContext& context,
                              const std::string& jpath) const;

  std::string GetSlot(const LgContext& context,
                      const std::string& slotname) const;

  std::string GetRawSlot(const LgContext& context,
                         const std::string& slotname) const;

  std::string GetCanonicalSlot(const LgContext& context,
                               const std::string& slotname) const;

  std::string Platform(const LgContext& context) const;

  std::string Domain(const LgContext& context) const;

  std::string Intent(const LgContext& context) const;

  std::string TaskName(const LgContext& context) const;

  std::string ActionName(const LgContext& context) const;

  std::string Locale(const LgContext& context) const;

  std::string GetDetailLevel(const LgContext& context) const;

  std::string InvokeMethod(const std::string& method,
                           const LgContext& context) const;

  std::string GetResource(const LgContext& context,
                          const std::string& id) const;

  static std::string ParseUnixTime(const LgContext& context,
                                  const time_t& tick);

  static std::string FormatTime(const LgContext& context,
                                  int hour, int min);

  static std::string ReadableHour(const LgContext& context,
                                            int hour);

  virtual ~LgAppBase();

 private:
  static const char kDetailLevelKey[];

  typedef std::string (*LgCallbackFunction)(const LgContext&);

  std::map<std::string, LgCallbackFunction> callbacks_;

 protected:
  std::string ResolveJPath(const Json::Value& root,
                           const std::string& jpath) const;

  static double ResolveJPath(const Json::Value& root,
                             const std::string& jpath,
                             const double defVal);

  static int CountByJPath(const Json::Value &root,
                   const std::string &jpath);

  static std::vector<std::shared_ptr<Slot>> FindSlots(
      const LgContext& context,
      const std::string& slotname);

  static std::shared_ptr<Slot> FindSlot(
      const LgContext& context,
      const std::string& slotname);

  bool RegisterCallback(std::string name, LgCallbackFunction function);

#define REGISTER_CALLBACK(func) RegisterCallback(#func, func);
};

#define REGISTER_CLASS(classname) \
        extern "C" { mobvoi::lg::LgAppBase* CreateLgApp(); } \
        mobvoi::lg::LgAppBase* CreateLgApp() { return new classname(); }

}  // namespace lg
}  // namespace mobvoi
#endif  // LG_LG_APPBASE_H_
