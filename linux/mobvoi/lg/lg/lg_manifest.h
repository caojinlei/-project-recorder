// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_MANIFEST_H_
#define LG_LG_MANIFEST_H_

#include <string>
#include <map>
#include <utility>
#include <vector>

#include "lg/xml_parser.h"

namespace mobvoi {
namespace lg {

class LgManifest {
 public:
  static int SetParserPath(const std::string &path);

  static LgManifest* Parse(const std::string& path);

 public:
  std::string name;
  std::string id;
  std::string version;
  std::string publisher;
  std::string locales;
  std::string default_locale;
  std::string platforms;
  std::string tasks;
  std::string task_types;

  std::string library_path;
  std::vector<std::pair<std::string, std::string>> resources;

  std::map<std::string, std::string> xmls;

 private:
  static XmlParser parser_;

  static LgManifest* Parse(xmlDocPtr xml_doc);
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_MANIFEST_H_
