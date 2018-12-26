// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_HOST_H_
#define LG_LG_HOST_H_

#include <string>
#include <vector>

#include "lg/lg_appmanager.h"
#include "lg/lg_engine.h"
#include "lg/lg_input.h"
#include "lg/lg_manifest.h"
#include "lg_interface/lg_result.h"

namespace mobvoi {
namespace lg {

class LgHost {
 private:
  int Initialize(const std::vector<std::string> &applist);

 public:
  LgHost();

  explicit LgHost(const std::vector<std::string> &applist);

  int UpdateLgApps(const std::string& path);

  LgResult Generate(const LgInput& input) const;

 private:
  LgContext BuildContext(const LgInput& input) const;

 private:
  LgEngine engine_;

  LgAppManager app_manager_;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_HOST_H_
