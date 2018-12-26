// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_APPMANAGER_H_
#define LG_LG_APPMANAGER_H_

#include <memory>
#include <string>
#include <vector>

#include "mobvoi/base/mutex.h"
#include "lg/lg_appproxy.h"

namespace mobvoi {
namespace lg {

class LgAppManager {
 public:
  std::shared_ptr<const LgAppProxy> GetAppProxy(const std::string& task,
                                          const std::string& engine_type,
                                          const std::string& locale,
                                          const std::string& platform) const;

  bool UpdateLgAppProxy(const std::string &path);

 private:
  bool AddLgAppProxy(std::shared_ptr<LgAppProxy> lgapp);

 private:
  std::vector<std::shared_ptr<LgAppProxy>> applications_;

  mutable mobvoi::SharedMutex app_locker_;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_APPMANAGER_H_
