// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_CHUNKS_H_
#define LG_LG_CHUNKS_H_

#include <string>
#include <utility>
#include <vector>

#include "lg/lg_variable.h"
#include "lg/xml_parser.h"

namespace mobvoi {
namespace lg {

class LgChunkPhrase;
class LgMarkupPhrase;

class LgChunkBase {
 public:
  virtual std::string Type() const = 0;
  virtual ~LgChunkBase();
};

class LgChunks {
 public:
  static LgChunks* Parse(xmlNodePtr node);

 public:
  LgChunks();
  ~LgChunks();

 public:
  std::vector<LgChunkBase*> chunks;
};

class LgChunk : public LgChunkBase {
 public:
  static LgChunk* Parse(xmlNodePtr node);

  static const char kTypeValue[];
 public:
  LgChunk();
  ~LgChunk();

  std::string Type() const;
 public:
  std::string id;

  std::string resource_id;

  std::vector<LgVariable*> variables;

  std::vector<LgChunkPhrase*> chunk_phrases;

  std::vector<LgMarkupPhrase*> markup_phrases;
};

class LgOneOf : public LgChunkBase {
 public:
  static LgOneOf* Parse(xmlNodePtr node);

  static const char kTypeValue[];
 public:
  LgOneOf();
  ~LgOneOf();

  std::string Type() const;
 public:
  std::string id;
  std::vector<LgChunk*> chunks;
};

class LgChunkPhrase {
 public:
  static LgChunkPhrase* Parse(xmlNodePtr node);

 public:
  LgChunkPhrase();

 public:
  std::string id;

  bool optional;
};

class LgPhraseRule {
 public:
  static LgPhraseRule* Parse(xmlNodePtr node);

 public:
  std::vector<std::pair<std::string, std::string>> attributes;

  std::string name;
};

class LgMarkupPhrase {
 public:
  static LgMarkupPhrase* Parse(xmlNodePtr node);

 public:
  LgMarkupPhrase();
  ~LgMarkupPhrase();

 public:
  std::vector<LgPhraseRule*> rules;

  std::string id;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_CHUNKS_H_
