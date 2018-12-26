// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_INPUT_H_
#define INTERFACE_INPUT_H_

#include <set>
#include <string>

#include "mobvoi/base/types.h"
#include "third_party/jsoncpp/json.h"

namespace mobvoi {

struct Geocode {
 public:
  Geocode();

  double  latitude;
  double  longitude;
};

struct Location {
 public:
  std::string   country;
  std::string   province;
  std::string   city;
  std::string   district;
  std::string   street;
  std::string   premises;
  Geocode       geocode;
};

struct ControlParam {
 public:
  ControlParam();

  bool parse(const Json::Value& control_param);

  bool domainShouldIgnore(const std::string& domain);

 private:
  bool enableWhiteList;
  std::set<std::string> domainWhiteList;
};

struct Input {
 public:
  Input();

  std::string   query;         // user query.
  std::string   sessionId;     // session id, uuid.
  unsigned int  turnId;        // turn id, start from '0'.
  std::string   locale;        // language in format "zh-CN", "en-US", ignore now
  Location      location;      // user current location.
  std::string   clientData;    // client data
  int64_t       timestampMs;   // client query unix epoch in milliseconds
  ControlParam  controlParam;  // client control data, like white list
};

}  // namespace mobvoi

#endif  // INTERFACE_INPUT_H_
