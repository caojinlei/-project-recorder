// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_FILLED_RESPONSE_H_
#define LG_LG_FILLED_RESPONSE_H_

#include <string>
#include <utility>
#include <vector>

#include "lg/lg_context.h"
#include "lg/lg_responses.h"

namespace mobvoi {
namespace lg {

class LgTag {
 public:
  std::string tag;
  std::vector<std::pair<std::string, std::string>> attributes;
};

class LgFilledPhrase {
 public:
  LgFilledPhrase();

  ~LgFilledPhrase();

  std::string ToString();

  xmlNodePtr ToXml(const LgContext& context, xmlNodePtr parent);

 public:
  bool valid;

  std::string content;

  std::string name;

  std::vector<LgFilledPhrase*> items;

  std::vector<LgTag*> tags;
};

class LgFilledChunk {
 public:
  LgFilledChunk();

  ~LgFilledChunk();

  std::string ToString();

  xmlNodePtr ToXml(const LgContext& context, xmlNodePtr parent);

 public:
  std::string                  id;
  std::string                  resourceId;
  std::vector<LgFilledPhrase*> phrases;
};

class LgFilledResponse {
 public:
  LgFilledResponse();

  ~LgFilledResponse();

  bool Valid() const;

  std::string ToString();

  std::string ToSsmlString(const LgContext& context);

  xmlNodePtr ToXml(const LgContext& context);

  std::string getChunkIds(const std::string& separator = "+") const;

  std::string getResourceIds(const std::string& separator = "+") const;

 public:
  std::vector<LgFilledChunk*> chunks;

  std::string id;
  std::string pairId;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_FILLED_RESPONSE_H_
