// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef DIALOGUE_RESOLVER_H_
#define DIALOGUE_RESOLVER_H_

#include <string>
#include <iostream>

#include "third_party/jsoncpp/json.h"
#include "dialogue/plugin_loader.h"

namespace mobvoi {
namespace dialogue {

class TcpEngine;

class Resolver {
 public:
  static const char kResolverNameKey[];
  static const char kResolverPathKey[];
  static const char kResolverMethodKey[];

  Resolver();
  int parse(const Json::Value& configure);
  bool check();
  ~Resolver();
  std::string getName();

 protected:
  std::string name_;    // resolver name
  std::string method_;  // resolver method name

 public:
  friend class TcpEngine;
  friend std::ostream& operator<<(std::ostream& os, const Resolver& resolver);
};

std::ostream& operator<<(std::ostream& os, const Resolver& resolver);

}  // namespace dialogue
}  // namespace mobvoi

#endif  // DIALOGUE_RESOLVER_H_
