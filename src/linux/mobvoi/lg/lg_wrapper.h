// Copyright 2018 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LGWRAPPER_LGWRAPPER_H_
#define LGWRAPPER_LGWRAPPER_H_

#include <memory>
#include <string>

#include "mobvoi/base/mutex.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace lg {

class LgHost;

class LgWrapper {
 public:
  static int SetLgDataPath(const std::string& lg_path);
  static int Initialize(const std::string& config_path);
  static void SetLgHost(LgHost* host);
  static Json::Value LgResultCallback(const Json::Value& turn,
                                      const Json::Value& session);

 private:
  static std::unique_ptr<LgHost> host_;
  static mobvoi::SharedMutex locker_;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LGWRAPPER_LGWRAPPER_H_
