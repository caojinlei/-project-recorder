// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_XML_PARSER_H_
#define LG_XML_PARSER_H_

#include <string>

#include "third_party/xml2/libxml/parser.h"
#include "third_party/xml2/libxml/valid.h"
#include "third_party/xml2/libxml/xmlschemas.h"

namespace mobvoi {
namespace lg {

class XmlParser {
 public:
  static void Free(const xmlDocPtr& doc);

 public:
  XmlParser();

  explicit XmlParser(const std::string& xsd_path);

  ~XmlParser();

  xmlDocPtr Parse(const std::string& path, std::string* pmsg) const;

  int Validate(const std::string& path, std::string* pmsg) const;

  int Validate(const xmlDocPtr doc, std::string* pmsg) const;

  int SetSchema(const std::string& xsd_path);

  int Clear();

  inline bool IsValid() const {
    return this->valid_;
  }

  inline bool HasValidater() const {
    return validater_ != nullptr;
  }

 public:
  static std::string GetStringContent(const xmlNodePtr node);

  static std::string GetAttriByName(const xmlNodePtr node,
                                    const std::string& name);

  static void ErrorHandler(void* ctx, const char* msg, ...);

  static void WarningHandler(void* ctx, const char* msg, ...);

 private:
  xmlSchemaParserCtxtPtr parser_;

  xmlSchemaPtr schema_;

  xmlSchemaValidCtxtPtr validater_;

  bool valid_;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_XML_PARSER_H_
