// Copyright 2017 Mobvoi Inc. All Rights Reserved.
// Author: jxli@mobvoi.com (Jiaxiang Li)
//         congfu@mobvoi.com (Cong Fu)

#ifndef SDK_PIPELINE_MOBVOI_DSP_H_
#define SDK_PIPELINE_MOBVOI_DSP_H_

#ifdef __cplusplus
extern "C" {
#endif

enum mobvoi_dsp_error_code {
  MOB_DSP_ERROR_NONE = 0,
  MOB_DSP_ERROR_CONFIG = 1,
  MOB_DSP_ERROR_RESULT = 2,
};

typedef enum {
  SET_UPLINK_CONFIG_DIR = 0,
  GET_UPLINK_CONFIG_DIR,
  SET_DELAY_ESTIMATION,
  GET_DELAY_ESTIMATION,
  SET_ECHO_CANCELATION,
  GET_ECHO_CANCELATION,
  SET_ECHO_SUPPRESSION,
  GET_ECHO_SUPPRESSION,
  SET_NOISE_ESTIMATION,
  GET_NOISE_ESTIMATION,
  SET_NOISE_REDUCTION,
  GET_NOISE_REDUCTION,
  SET_AUTOMATIC_GAIN_CONTROL,
  GET_AUTOMATIC_GAIN_CONTROL,
  SET_DIRECTION_OF_ARRIVAL,
  GET_DIRECTION_OF_ARRIVAL,
  SET_BEAMFORMING,
  GET_BEAMFORMING,
  SET_BF_POST_PROCESS,
  GET_BF_POST_PROCESS,
  SET_UPLINK_DYNAMIC_RANGE_CONPRESSION,
  GET_UPLINK_DYNAMIC_RANGE_CONPRESSION,
  SET_UPLINK_PARAM,
  GET_UPLINK_PARAM,
  STOP_DOA_SMOOTH,
  UPLINK_CTRL_MAX
} mob_uplink_ctrl;

typedef enum {
  SET_DOWNLINK_CONFIG_DIR = 0,
  GET_DOWNLINK_CONFIG_DIR,
  SET_DOWNLINK_DYNAMIC_RANGE_CONPRESSION,
  GET_DOWNLINK_DYNAMIC_RANGE_CONPRESSION,
  SET_EQUALIZER,
  GET_EQUALIZER,
  SET_EQUALIZER_EXT,
  GET_EQUALIZER_EXT,
  SET_DOWNLINK_PARAM,
  GET_DOWNLINK_PARAM,
  DOWNLINK_CTRL_MAX
} mob_downlink_ctrl;

typedef enum {
  FORMAT_BLOCK = 0,   // AAABBBCCC
  FORMAT_CROSS        // ABCABCABC
} AudioFormat;

typedef struct {
  int mic_fix_gain;
  int spk_fix_gain;
  AudioFormat mic_in_format;
  AudioFormat spk_in_format;
  AudioFormat mic_out_format;
} mob_uplink_param;

typedef struct {
  AudioFormat in_format;
  AudioFormat out_format;
} mob_downlink_param;

typedef struct {
  int echo_len;
  float nu_nlms;
} mob_aec_param;

typedef enum { DOA_LINEAR = 1, DOA_CIRCLE = 2 } DOAType;

typedef struct {
  DOAType doa_type;
  int segment_len;
  int num_src_detect;
  float smooth_factor;
  float mic_interval;
  float pre_angle;
} mob_doa_param;

typedef struct {
  int offset;
  float angle;
} mob_doa_result;

typedef struct {
  int history_size;
  int lookahead;
  int use_fixed_delay;
} mob_de_param;

typedef enum { ES_LEVEL_1 = 1, ES_LEVEL_2, ES_LEVEL_3 } ESLevel;

typedef struct {
  ESLevel level;
  int flag_pre_converge; // 0 for ASR, 1 for bluetooth
  int flag_noise_fill;
} mob_es_param;

typedef enum { NR_LEVEL_1 = 1, NR_LEVEL_2, NR_LEVEL_3 } NRLevel;

typedef struct {
  NRLevel level;
} mob_nr_param;

typedef enum { MEAN = 1, FIXED_BEAM = 2, MULTI_FIXED_BEAM = 3, GSC = 4 } BFType;

typedef struct {
  BFType bf_type;
  int   weights_num;
  int   enable;
  float tolerance;
  int   block_mat_size;
  float select_angle;
  float snr_filter;
  float mu;
  float gama;
  float beam_width;
  float* angles;
  float* weights;
  float* block_mat_weights;
} mob_bf_param;

typedef struct {
  float init_gain;
  float target_gain_min;
  float target_gain_max;
} mob_bf_post_pro_param;

typedef struct {
  float init_gain;
  float target_level;
  int min_frame_count;
  int min_energy_count;
} mob_agc_param;

typedef struct {
  float gain;
  float full_gain_pos;
  float threshold;
  float limit;
} mob_drc_param;

typedef struct {
  int bands_num;
  float* freqs;
  float* gain_db;
} mob_eq_param;

typedef struct {
  int coeff_weight_len;
  float* coeff_weight;
} mob_eq_param_ext;

/**
 * Mobvoi dsp uplink processor initialization function.
 * @param frame_len: The frame len.
 * @param mic_sample_rate: The mic speech sample rate.
 * @param mic_num: micphone number.
 * @param spk_sample_rate: The reference speech sample rate.
 * @param spk_num: Reference signal number for aec.
 * @return  The dsp processor instance.
 */
void* mobvoi_uplink_init(int frame_len,
                         int mic_sample_rate,
                         int mic_num,
                         int spk_sample_rate,
                         int spk_num);

/**
 * Mobvoi dsp uplink processor cleanup function.
 * @param instance: The dsp uplink processor instance.
 */
void mobvoi_uplink_cleanup(void* instance);

/**
 * Set or get the uplink algorithm parameters, if you have not set the
 * algorithm related parameter, the algorithm would be disabled.
 * @param instance: The dsp uplink processor instance.
 * @param type: The dsp uplink algorithm type.
 * @param ptr: The dsp uplink algorithm parameter.
 * @return  0 for success, others for error.
 */
int mobvoi_uplink_process_ctl(void* instance,
                              mob_uplink_ctrl type,
                              void* ptr);

/**
 * Pause the aec algorithm.
 * @param instance: The dsp processor instance.
 * @param type: Type 0, mic pause; type 1, speaker pause.
 */
void mobvoi_uplink_aec_pause(void* instance, int type);

/**
 * Pause the aec algorithm.
 * @param instance: The dsp processor instance.
 * @param type: Type 0, mic pause; type 1, speaker pause.
 */
void mobvoi_uplink_aec_resume(void* instance, int type);

/**
 * Get aec algorithm enabled status.
 * @param instance: The dsp processor instance.
 * @return 0, disabled; 1, enabled.
 */
int mobvoi_uplink_aec_is_enabled(void* instance);

/**
 * Send reference frames to aec processor.
 * @param instance: The dsp processor instance.
 * @param ref: The input speech data buffer. AAAABBBB mode for multi refs.
 * @param size: Buffer size in short.
 * @param channel_num: Channel number of the buffer.
 * @param spk_delay: The delay between reference signal and speaker hardware.
 * @return The actually sent speech data size.
 */
int mobvoi_uplink_send_ref_frames(void* instance,
                                  const short* ref,
                                  int size,
                                  int channel_num,
                                  int spk_delay_frame_num);

/**
 * Uplink frames processing by enabled uplink algorithms.
 * @param instance: The dsp uplink processor instance.
 * @param in: The input speech data buffer. AAAABBBB mode for multi mics.
 * @param size: Buffer size in short.
 * @param channel_num: Channel number of the buffer.
 * @param mic_delay_frame_num: The delay between reference and mic signal.
 * @param out: The processed data buffer.
 * @param out_channel_num: Channel number of the output buffer.
 * @return The actually sent speech data size.
 */
int mobvoi_uplink_process(void* instance,
                          const short* in,
                          int size,
                          int channel_num,
                          int mic_delay_frame_num,
                          short* out,
                          int out_channel_num);

/**
 * Mobvoi dsp downlink processor initialization function.
 * @param frame_len: The frame len.
 * @param sample_rate: The speech sample rate.
 * @param channel_num: The number of channels to process.
 * @return  The dsp downlink processor instance.
 */
void* mobvoi_downlink_init(int frame_len, int sample_rate, int channel_num);

/**
 * Set or get the downlink algorithm parameters, if you have not set the
 * algorithm related parameter, the algorithm would be disabled.
 * @param instance: The dsp downlink processor instance.
 * @param type: The dsp downlink algorithm type.
 * @param ptr: The dsp downlink algorithm parameter.
 * @return  0 for success, others for error.
 */
int mobvoi_downlink_process_ctl(void* instance,
                                mob_downlink_ctrl type,
                                void* ptr);

/**
 * Downlink frames processing by enabled uplink algorithms.
 * @param instance: The dsp downlink processor instance.
 * @param in: The input speech data buffer.
 * @param size: Buffer size in short.
 * @param channel_num: Channel number of the buffer.
 * @param out: The processed data buffer.
 * @param out_channel_num: Channel number of the output buffer.
 * @return The actually sent speech data size
 */
int mobvoi_downlink_process(void* instance,
                            const short* in,
                            int size,
                            int channel_num,
                            short* out,
                            int out_channel_num);

/**
 * Mobvoi dsp downlink processor cleanup function.
 * @param instance: The dsp downlink processor instance.
 */
void mobvoi_downlink_cleanup(void* instance);

#ifdef __cplusplus
}
#endif

#endif  // SDK_PIPELINE_MOBVOI_DSP_H_
