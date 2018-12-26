// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_CONTEXT_H_
#define LG_LG_CONTEXT_H_

#include <map>
#include <string>
#include <vector>
#include <stack>

#include "lg/logger.h"
#include "lg_interface/hypothesis.h"
#include "lg_interface/turn_input.h"
#include "lg_interface/turn.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {
namespace lg {

using std::string;

class LgContext {
 public:
  LgContext();

 public:
  std::vector<Turn>   history;          // session history
  std::stack<Turn>    activity;         // active tasks
  TurnInput           input;            // current turn input
  Hypothesis          hypo;             // hypothesis
  Logger              logger;           // runtime logger

  std::multimap<string, string> data;   // runtime data

 public:
  std::string Locale() const;

  std::string GetResource(const string& id) const;

  void SetResource(const std::map<string, string>* res);

 private:
  static const char kDefaultResourceValue[];

  const std::map<string, string>* resource_;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_CONTEXT_H_
