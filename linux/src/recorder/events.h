// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author: qinhuang@vw-mobvoi.com (Qin Huang)

#ifndef LINUX_SRCS_RECORDER_EVENTS_H_
#define LINUX_SRCS_RECORDER_EVENTS_H_

#include <boost/statechart/event.hpp>

namespace Speech {
namespace Recorder {

class EvStartRecord : public boost::statechart::event<EvStartRecord> {
 public:
  EvStartRecord();
  ~EvStartRecord() final;
};  // class EvStartRecord

class EvStopRecord : public boost::statechart::event<EvStopRecord> {
 public:
  EvStopRecord();
  ~EvStopRecord() final;
};  // class EvStartRecord

}  // namespace Recorder
}  // namespace Speech

#endif  // LINUX_SRCS_RECORDER_EVENTS_H_
