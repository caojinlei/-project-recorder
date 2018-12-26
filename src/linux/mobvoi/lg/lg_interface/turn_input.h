// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: liangzhao@mobvoi.com (Liang Zhao)

#ifndef INTERFACE_TURN_INPUT_H_
#define INTERFACE_TURN_INPUT_H_

#include <stdint.h>

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "lg_interface/address.h"
#include "lg_interface/client_info.h"
#include "lg_interface/date_time.h"
#include "lg_interface/geocoding.h"

namespace mobvoi {
namespace lg {

using std::multimap;
using std::string;
using std::vector;

// enumerate input methods.
enum class InputMethod {
  kSpeech = 0,     // input through speaking speech.
  kText,           // input through typing text.
  kController,     // input through physical/page controller.
  kNone,           // not set input method
};

// enumerate gender.
enum class Gender {
  kFemale = 0,     // female
  kMale,           // male
  kNone,           // not set
};

// Structure for storing input information of turn
class TurnInput {
 public:
  static TurnInput EmptyInput(InputMethod method = InputMethod::kNone);

 public:
  TurnInput();

  TurnInput(const TurnInput& input);

  ~TurnInput();

  TurnInput& operator=(const TurnInput& that);

  inline string GetRawQuery() const {
    return raw_text;
  }

  inline string GetNormalizedQuery() const {
    return normal_text;
  }

 public:
  string            requestid;        // request id.
  string            sessionid;        // session id.
  int               turnid;           // turn id, started from 0.

  InputMethod       type;             // input method.
  string            raw_text;         // raw query text.
  string            normal_text;      // normalized query text.
  vector<string>    words;            // word broken query text.
  double            sr_score;         // SR score for best result.
  string            controller;       // controller name.
  vector<string>    control_params;   // controller parameters.

  Geocoding         geocoding;        // user geocoding information.
  Address           address;          // user address information.

  DateTime          usertime;         // user (client) time.
  int64_t           tmoffsets;        // offsets of user timezone, in seconds.

  string            userid;           // user id.
  string            username;         // user formal name.
  string            nickname;         // user nick name.
  Gender            usergender;       // user gender

  ClientInfo        client_info;      // client information.

  multimap<string, string> params;    // extra input parameters.
};

}  // namespace lg
}  // namespace mobvoi

#endif  // INTERFACE_TURN_INPUT_H_
