// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_RESPONSES_H_
#define LG_LG_RESPONSES_H_

#include <string>
#include <vector>

#include "lg/lg_chunks.h"
#include "lg/lg_conditions.h"
#include "lg/xml_parser.h"

namespace mobvoi {
namespace lg {

class LgResponse;

class LgResponses {
 public:
  static LgResponses* Parse(xmlNodePtr node);

 public:
  LgResponses();

  ~LgResponses();

 public:
  std::string               type;
  std::string               markup_style;
  int                       max_count;
  std::vector<LgResponse*>  response_list;
};

class LgResponse {
 public:
  static LgResponse* Parse(xmlNodePtr node);

 public:
  LgResponse();

  ~LgResponse();

 public:
  LgConditions* conditions;
  LgChunks*     chunks;
  std::string   id;
  std::string   pairId;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_RESPONSES_H_
