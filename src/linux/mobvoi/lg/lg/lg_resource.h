// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef LG_LG_RESOURCE_H_
#define LG_LG_RESOURCE_H_

#include <memory>
#include <string>
#include <vector>

namespace mobvoi {
namespace lg {

class LgResource {
 public:
  static const char kTypeValue[];

 public:
  LgResource();

  virtual ~LgResource();

  virtual std::string Type() const;

  explicit LgResource(const std::string& rstring);

  int Parse(const std::string& rstring);

  int Parse(const std::string& rstring, std::string* pmsg);

 public:
  std::string raw;

  std::string content;

  std::vector<std::shared_ptr<LgResource>> items;
};

class LgRsConst : public LgResource {
 public:
  static const char kTypeValue[];

 public:
  LgRsConst();

  std::string Type() const;

  static LgRsConst* Parse(const std::string& rstring, int* pcur,
                          std::string* pmsg);
};

class LgRsVariable : public LgResource {
 public:
  static LgRsVariable* Parse(const std::string& rstring, int* pcur,
                             std::string* pmsg);

  static const char kTypeValue[];
 public:
  std::string Type() const;

 public:
  std::string name;
};

class LgRsChunk : public LgResource {
 public:
  static LgRsChunk* Parse(const std::string& rstring, int* pcur,
                          std::string* pmsg);

  static const char kTypeValue[];
 public:
  std::string Type() const;

 public:
  std::string name;
};

}  // namespace lg
}  // namespace mobvoi

#endif  // LG_LG_RESOURCE_H_
