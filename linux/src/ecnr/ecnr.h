// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author:

#ifndef LINUX_ECNR_ECNR_H_
#define LINUX_ECNR_ECNR_H_

#include <stdio.h>
#include <iostream>

#include "mobvoi/mobvoi_dsp.h"
#include "mobvoi/speech_sdk.h"

namespace speech {

#define kDriverModeAngle (-45)
#define kPassengerModeAngle (45)
#define kInvalidAngle (720)
#define kSampleRate (16000)

class Ecnr {
 public:
  typedef enum {
    kAdaptiveMode,
    kDriverMode,
    kPassengerMode,
    kOffMode
  } BeamformingMode;

 public:
  static Ecnr* p_ecnr_instance_;

 public:
  static Ecnr* GetInstance() {
    if (p_ecnr_instance_ == nullptr) p_ecnr_instance_ = new Ecnr();

    return p_ecnr_instance_;
  }

  virtual ~Ecnr() {
    if (dsp_instance_ != nullptr) {
      mobvoi_uplink_cleanup(dsp_instance_);
    }
    if (mic_buffer_ != nullptr) {
      delete[] mic_buffer_;
    }
    if (ref_buffer_ != nullptr) {
      delete[] ref_buffer_;
    }
    if (out_buffer_ != nullptr) {
      delete[] out_buffer_;
    }
  }

  const char* process(const char* data, int size, int* out_size);
  void EventAlwaysOnEnter();
  void EventDialogExit();
  void EventPTTClicked();
  void EventSDSClicked();
  void EventWakeup();
  bool IsWakeupExpected();
  int SetBeamformingMode(BeamformingMode mode);
  void SetRestartFlag(bool value);

 private:
  Ecnr() {}

  int DisableBeamforming();
  int EnableBeamforming(float angle);
  int GetDoaAngle(float& angle);
  void InitDSP();
  int SetBeamformingParameters(bool enable, int angle = kDriverModeAngle);

 private:
  void* dsp_instance_ = nullptr;

  int mic_num_ = 2;
  int ref_num_ = 1;

  short* mic_buffer_ = nullptr;
  short* ref_buffer_ = nullptr;
  short* out_buffer_ = nullptr;

  int doa_offset_ = 0;
  int last_wakeup_angle_ = kInvalidAngle;
  bool need_restart_ = true;
  bool debugging_ = false;
  bool discard_unexpected_wakeup_ = true;

  // default OffMode
  BeamformingMode beamforming_mode_ = kOffMode;
  BeamformingMode last_mode_ = kOffMode;

  mobvoi_ecnr_vtable ecnr_handler_;
};  // class Ecnr

}  // namespace speech

#endif  // LINUX_ECNR_ECNR_H_
