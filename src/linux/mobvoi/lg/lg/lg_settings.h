// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_SETTINGS_H_
#define LG_LG_SETTINGS_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "lg/xml_parser.h"

namespace mobvoi {
namespace lg {

class LgSettings {
 public:
  static int SetParserPath(const std::string &path);

  static LgSettings* Parse(const std::string &path);

 public:
  std::map<std::string, std::string> items;

  std::vector<std::string> index_fallbacks;

  std::vector<std::pair<std::string, std::string>> normalization_rules;

 private:
  static XmlParser parser_;

  static LgSettings* Parse(xmlDocPtr xml_doc);
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_SETTINGS_H_
