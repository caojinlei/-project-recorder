// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_RULES_H_
#define LG_LG_RULES_H_

#include <string>
#include <vector>

#include "lg/lg_conditions.h"
#include "lg/lg_responses.h"
#include "lg/xml_parser.h"

namespace mobvoi {
namespace lg {

class LgRule;

class LgRules {
 public:
  static int SetParserPath(const std::string &path);

  static LgRules* Parse(const std::string &path);

 public:
  LgRules();

  ~LgRules();

 public:
  std::vector<LgRule*> rules;

  std::string name;
  std::string lang;
  std::string default_typename;

 private:
  static XmlParser parser_;

  static LgRules* Parse(xmlDocPtr doc);
};

class LgRule {
 public:
  static LgRule* Parse(xmlNodePtr node);

 public:
  LgRule();

  ~LgRule();

 public:
  LgConditions* conditions;

  std::vector<LgResponses*> responses;

  std::string id;
  bool pair;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_RULES_H_
