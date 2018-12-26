// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_CLIENT_INFO_H_
#define INTERFACE_CLIENT_INFO_H_

#include <string>

namespace mobvoi {
using std::string;

struct ClientInfo {
 public:
  std::string   platform;   // the platform name
  std::string   version;    // the version of the platform
  std::string   locale;     // the locale
  std::string   deviceid;   // the device Id

 public:
  ClientInfo();
  ~ClientInfo();

  ClientInfo& operator=(const ClientInfo& that);
};

}  // namespace mobvoi

#endif  // INTERFACE_CLIENT_INFO_H_
