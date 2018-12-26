// Copyright 2018 VW-Mobvoi Inc. All Rights Reserved.
// Author:

#include "ecnr/ecnr.h"

#include <iostream>

#include <stdlib.h>
#include <string.h>

#include "config/speech_config.h"

namespace speech {

#define kTag " MOBVOI_DSP BF "
Ecnr* Ecnr::p_ecnr_instance_ = nullptr;

static const char* mode_to_str(Ecnr::BeamformingMode mode) {
  switch (mode) {
    case Ecnr::BeamformingMode::kAdaptiveMode:
      return "Adaptive";
    case Ecnr::BeamformingMode::kDriverMode:
      return "Driver";
    case Ecnr::BeamformingMode::kPassengerMode:
      return "Passenger";
    case Ecnr::BeamformingMode::kOffMode:
      return "Off";
    default:
      return "Unknown";
  }
}

static short* prepare_buffer(int size, short** buffer) {
  if (*buffer == NULL) {
    *buffer = (short*)calloc(sizeof(short) * size + sizeof(int), 1);
    *((int*)*buffer) = size;
  } else if (*((int*)*buffer) < size) {
    free(*buffer);
    *buffer = (short*)calloc(sizeof(short) * size + sizeof(int), 1);
    *((int*)*buffer) = size;
  }

  return *buffer + sizeof(int) / sizeof(short);
}

static bool WakeupExpected() { return Ecnr::GetInstance()->IsWakeupExpected(); }

const char* Ecnr::process(const char* data, int size, int* out_size) {
  if (nullptr == data || size <= 0) return nullptr;

  if (need_restart_) {
    InitDSP();
    need_restart_ = false;
  }

  // mmrr
  int block_size = size / 8;
  int mic_size = block_size * mic_num_;
  int ref_size = block_size * ref_num_;

  const short* raw = (const short*)data;

  short* mic_buffer = prepare_buffer(mic_size, &mic_buffer_);
  short* ref_buffer = prepare_buffer(ref_size, &ref_buffer_);

  // ABCDABCDABCD -> AAABBB CCCDDD
  for (int i = 0; i < block_size; i++) {
    mic_buffer[i] = raw[i * 4];

    if (mic_num_ > 1) {
      mic_buffer[block_size + i] = raw[i * 4 + 1];
    }

    ref_buffer[i] = raw[i * 4 + 2];

    if (ref_num_ > 1) {
      ref_buffer[block_size + i] = raw[i * 4 + 3];
    }
  }

  int delay = 0;
  mobvoi_uplink_send_ref_frames(dsp_instance_, (const short*)ref_buffer,
                                ref_size, ref_num_, delay);

  short* out_buffer = prepare_buffer(block_size, &out_buffer_);
  int temp = mobvoi_uplink_process(dsp_instance_, (const short*)mic_buffer,
                                   mic_size, mic_num_, 0, out_buffer, 1);

  *out_size = temp * 2;
  return (const char*)out_buffer;
}

void Ecnr::EventAlwaysOnEnter() {
  // LOG(INFO) << kTag << __FUNCTION__;
  if (mic_num_ < 2) {
    return;
  }

  if (last_wakeup_angle_ != kInvalidAngle) {
    EnableBeamforming(last_wakeup_angle_);
    int dur = 1000;
    mobvoi_uplink_process_ctl(dsp_instance_, STOP_DOA_SMOOTH, &dur);
  }
}

void Ecnr::EventDialogExit() {
  // LOG(INFO) << kTag << __FUNCTION__;
  if (mic_num_ < 2) {
    return;
  }

  SetBeamformingMode(beamforming_mode_);
}

void Ecnr::EventPTTClicked() {
  // LOG(INFO) << kTag << __FUNCTION__;
  if (mic_num_ < 2) {
    return;
  }

  EnableBeamforming(kDriverModeAngle);

  int dur = 1000;
  mobvoi_uplink_process_ctl(dsp_instance_, STOP_DOA_SMOOTH, &dur);
}

void Ecnr::EventSDSClicked() {
  // LOG(INFO) << kTag << __FUNCTION__;
  if (mic_num_ < 2) {
    return;
  }

  DisableBeamforming();
}

void Ecnr::EventWakeup() {
  if (mic_num_ < 2) {
    return;
  }

  if (beamforming_mode_ == kDriverMode) {
    int dur = 1000;
    mobvoi_uplink_process_ctl(dsp_instance_, STOP_DOA_SMOOTH, &dur);
  } else if (beamforming_mode_ == kAdaptiveMode) {
    float angle = 0;
    int ret_get = GetDoaAngle(angle);
    // LOG(INFO) << kTag << __FUNCTION__ << " ret_get=" << ret_get
    //<< " angle=" << angle;

    if (ret_get == 0) {
      last_wakeup_angle_ = angle > 0 ? kPassengerModeAngle : kDriverModeAngle;
      int ret_set = EnableBeamforming(last_wakeup_angle_);

      std::cout << kTag << __FUNCTION__ << " EnableBeamforming, angle=" << angle
                << "ret_set = " << ret_set << std::endl;

      int dur = 1000;
      mobvoi_uplink_process_ctl(dsp_instance_, STOP_DOA_SMOOTH, &dur);
    }
  }
}

bool Ecnr::IsWakeupExpected() {
  if (mic_num_ < 2 || last_mode_ == kOffMode) {
    return true;
  }

  float angle = 0;
  int ret_get = GetDoaAngle(angle);

  std::cout << kTag << __FUNCTION__ << "last mode=" << mode_to_str(last_mode_)
            << " ret_get=" << ret_get << " angle=" << angle;

  // LOG(INFO) << kTag << __FUNCTION__ << "last mode=" <<
  // mode_to_str(last_mode_)
  //          << " ret_get=" << ret_get << " angle=" << angle;

  if (ret_get != 0) {
    // LOG(INFO) << kTag << __FUNCTION__ << "Unexpected wakeup";
    if (!discard_unexpected_wakeup_) {
      // LOG(INFO) << kTag << __FUNCTION__ << "Discard unexpected wakeup
      // DISABLED";
      return true;
    }

    return false;
  }

  BeamformingMode mode = angle > 0 ? kPassengerMode : kDriverMode;
  if (last_mode_ != mode) {
    // LOG(INFO) << kTag << __FUNCTION__
    //          << "Unexpected wakeup: last mode=" << mode_to_str(last_mode_)
    //          << " mode=" << mode_to_str(mode);
    if (!discard_unexpected_wakeup_) {
      // LOG(INFO) << kTag << __FUNCTION__ << "Discard unexpected wakeup
      // DISABLED";
      return true;
    }

    return false;
  }

  return true;
}

int Ecnr::SetBeamformingMode(BeamformingMode mode) {
  if (debugging_) {
    // LOG(INFO) << kTag << __FUNCTION__ << " Discard mode setting in debug
    // mode";
    return 0;
  }

  beamforming_mode_ = mode;
  // LOG(INFO) << kTag << __FUNCTION__ << " mode=" << mode_to_str(mode);
  if (kDriverMode == beamforming_mode_) {
    last_wakeup_angle_ = kInvalidAngle;
    return EnableBeamforming(kDriverModeAngle);
  } else if (kPassengerMode == beamforming_mode_) {
    last_wakeup_angle_ = kInvalidAngle;
    return EnableBeamforming(kPassengerModeAngle);
  } else if (kAdaptiveMode == beamforming_mode_) {
    return DisableBeamforming();
  } else if (kOffMode == beamforming_mode_) {
    last_wakeup_angle_ = kInvalidAngle;
    return DisableBeamforming();
  } else {
    return mobvoi_dsp_error_code::MOB_DSP_ERROR_CONFIG;
  }
}

void Ecnr::SetRestartFlag(bool value) { need_restart_ = value; }

int Ecnr::DisableBeamforming() {
  last_mode_ = kOffMode;
  // LOG(INFO) << kTag << __FUNCTION__ << " last_mode=" <<
  // mode_to_str(last_mode_)
  //          << " now";
  return SetBeamformingParameters(false);
}

int Ecnr::EnableBeamforming(float angle) {
  int ret = SetBeamformingParameters(true, angle);
  if (ret == 0) {
    last_mode_ = angle > 0 ? kPassengerMode : kDriverMode;
  } else {
    // LOG(INFO) << kTag << __FUNCTION__
    //          << " last_mode=" << mode_to_str(last_mode_)
    //          << " not changed due to SetBeamformingParameters error";
  }

  return ret;
}

int Ecnr::GetDoaAngle(float& angle) {
  mob_doa_result p;

  p.offset = doa_offset_;
  int ret =
      mobvoi_uplink_process_ctl(dsp_instance_, GET_DIRECTION_OF_ARRIVAL, &p);
  if (0 == ret) {
    angle = p.angle;
  }

  // LOG(INFO) << kTag << __FUNCTION__ << "  angle=" << angle
  //          << " mode=" << mode_to_str(beamforming_mode_) << " ret=" << ret;
  return ret;
}

void Ecnr::InitDSP() {
  mic_num_ = Selene::SpeechConfig::GetInstance()->MicphoneNumber();

  ref_num_ = 1;

  if (dsp_instance_ != nullptr) {
    mobvoi_uplink_cleanup(dsp_instance_);
  }

  dsp_instance_ =
      mobvoi_uplink_init(10, kSampleRate, mic_num_, kSampleRate, ref_num_);

#if 1
  std::string contact_dir =
      Selene::SpeechConfig::GetInstance()->MobvoiModelDir();
  contact_dir.append("dsp_config");
  std::cout << __FUNCTION__ << " dsp confile file path = " << contact_dir
            << std::endl;
  mobvoi_uplink_process_ctl(dsp_instance_, SET_UPLINK_CONFIG_DIR,
                            const_cast<char*>(contact_dir.c_str()));
#endif
  FILE* fp = fopen("/var/bf_mode", "rb");
  if (fp) {
    int mode = 0;
    int discard = 0;
    int doa_offset = 0;
    int n = fscanf(fp, "%d %d %d", &mode, &discard, &doa_offset);
    if (n == 3) {
      if (mode <= 3 && mode >= 0) {
        SetBeamformingMode((BeamformingMode)mode);
        debugging_ = true;
      }

      discard_unexpected_wakeup_ = discard != 0;
      // LOG(INFO) << kTag << __FUNCTION__
      //          << "discard flag: " << discard_unexpected_wakeup_;

      doa_offset_ = doa_offset;
      // LOG(INFO) << kTag << __FUNCTION__ << "doa_offset: " << doa_offset_;
    }
    fclose(fp);
  }

  mobvoi_uplink_aec_resume(dsp_instance_, 0);
  mobvoi_uplink_aec_resume(dsp_instance_, 1);

  ecnr_handler_.is_wakeup_expected = WakeupExpected;
  mobvoi_set_ecnr_handler(&ecnr_handler_);
}

int Ecnr::SetBeamformingParameters(bool enable, int angle) {
  mob_bf_param p;

  // 0 disable; 1 enable.
  p.enable = enable ? 1 : 0;
  p.select_angle = angle;
  p.angles = NULL;
  p.weights = NULL;
  p.block_mat_weights = NULL;
  int ret = mobvoi_uplink_process_ctl(dsp_instance_, SET_BEAMFORMING, &p);

  //  LOG(INFO) << kTag << __FUNCTION__ << " enable=" << enable
  //            << " angle=" << angle << " ret=" << ret;
  return ret;
}
}
