// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#include "recorder/events.h"

#include "log/log.h"

namespace Speech {
namespace Recorder {

static const char* const kTag = "Recorder Event";

EvStartRecord::EvStartRecord() { LOGD(kTag) << "Construct EvStartRecord"; }

EvStartRecord::~EvStartRecord() { LOGD(kTag) << "Destruct EvStartRecord"; }

EvStopRecord::EvStopRecord() { LOGD(kTag) << "Construct EvStopRecord"; }

EvStopRecord::~EvStopRecord() { LOGD(kTag) << "Destruct EvStopRecord"; }

}  // namespace Recorder
}  // namespace Speech
