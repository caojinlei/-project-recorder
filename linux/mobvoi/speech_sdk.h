// Copyright 2017 Mobvoi Inc. All Rights Reserved.

#ifndef LINUX_SPEECH_SDK_H_
#define LINUX_SPEECH_SDK_H_

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _mobvoi_hotword_handler_vtable {
  /**
   * 旧版本热词触发回调方法。
   */
  void (*on_hotword_detected)();
} mobvoi_hotword_handler_vtable;

// TODO(lj): replace old api when customer updated
typedef struct _mobvoi_hotword_handler_vtable_ext {
  /**
   * 新版本热词触发回调方法，支持多热词，参数为触发本次唤醒的热词。
   */
  void (*on_hotword_detected)(const char* hotword);
} mobvoi_hotword_handler_vtable_ext;

typedef struct _mobvoi_recognizer_handler_vtable {
  /**
   * 在检测到有人说话后回调。
   */
  void (*on_speech_detected)();

  /**
 　* 在检测到本地语音之后，又检测到本地静音时回调。
 　*/
  void (*on_local_silence_detected)();
  /**
   * 服务器端检测到静音（说话人停止说话）后回调。
   */
  void (*on_remote_silence_detected)();

  /**
   * 语音识别部分结果返回，比如“今天天气怎么样”，会按顺序返回“今天”，“今天天气”。
   *
   * @param result 识别到的部分结果字符串。
   */
  void (*on_partial_transcription)(const char* result);

  /**
   * 关键词识别结果返回。 参考MOBVOI_RECOGNIZER_KEYWORDS|MOBVOI_RECOGNIZER_PSM
   *
   * @param result 识别结果字符串。
   */
  void (*on_keyword)(const char* result);

  /**
   * 语音识别最终结果返回，比如“今天天气怎么样”，会按顺序返回“今天”，“今天天气”，
   * “今天天气怎么样”，最后一个就是Final Transcription。
   *
   * @param result 最终认为用户说的完整字符串。
   */
  void (*on_final_transcription)(const char* result);

  /**
   * 语音搜索结果返回, 为JSON格式字符串。
   *
   * @param result 语音搜索结果json。
   */
  void (*on_result)(const char* result);

  /**
   * 计算得到输入语音片断的声压（SPL）值时，回调该方法。
   *
   * @param volume 根据语音的能量算出，取值范围：[0.0, 1.0]。
   */
  void (*on_volume)(float volume);

  /**
   * 当执行出错时会回调。
   *
   * @param error_code 错误码。
   */
  void (*on_error)(int error_code);

  /**
   * 识别器在oneshot场景下检查到热词后回调。
   */
  void (*on_oneshot_hotword_detected)();
} mobvoi_recognizer_handler_vtable;

typedef struct _mobvoi_nlu_handler_vtable {
  /**
   * DM结果返回, 为JSON格式字符串。
   *
   * @param result DM结果json。
   */

  void (*on_dm_result)(const char* result);

  /**
   * LU结果返回, 为JSON格式字符串。
   *
   * @param result LU结果json。
   */
  void (*on_lu_result)(const char* result);
} mobvoi_nlu_handler_vtable;

typedef struct _mobvoi_tts_handler_vtable {
  void (*on_done)();
} mobvoi_tts_handler_vtable;

typedef struct _mobvoi_text_search_handler_vtable {
  /**
   * 当文本请求出错时会回调。
   */
  void (*on_error)();

  /**
   * 文本搜索结果返回, 为JSON格式字符串。
   *
   * @param result 文本搜索结果json。
   */
  void (*on_result)(const char* result);
} mobvoi_text_search_handler_vtable;

typedef struct _mobvoi_ecnr_vtable {
  /**
   * 当文本请求出错时会回调。
   */
  bool (*is_wakeup_expected)();
} mobvoi_ecnr_vtable;

enum mobvoi_recognizer_error_code {
  /**
   * 无错误。不会回调on error。
   */
  MOBVOI_RECOGNIZER_NO_ERROR = 0,
  /**
   * 服务器错误。
   */
  MOBVOI_RECOGNIZER_SERVER_ERROR = 1,
  /**
   * 网络错误。
   */
  MOBVOI_RECOGNIZER_NETWORK_ERROR = 2,
  /**
   * 识别语音内容为空。即认为没有人说话。
   */
  MOBVOI_RECOGNIZER_NO_SPEECH = 4,
  /**
   * 无法识别当前语音内容。
   */
  MOBVOI_RECOGNIZER_GARBAGE = 5,
  /**
   * 内部错误。
   */
  MOBVOI_RECOGNIZER_INTERNAL_ERROR = 6,
  /**
   * sdk初始化错误。
   */
  MOBVOI_RECOGNIZER_SDK_INIT_ERROR = 7,
  /**
   * oneshot hotword 二次验证失败。
   */
  MOBVOI_RECOGNIZER_HOTWORD_VERIFY_FAIL = 8,
  /**
   * 识别器启动过程中被突然中止。
   */
  MOBVOI_RECOGNIZER_START_ABORT = 9,
};

enum mobvoi_recognizer_type {
  /**
   * 在线语音识别，返回语音识别结果。
   */
  MOBVOI_RECOGNIZER_ONLINE_ASR = 0,
  /**
   * 在线语音识别和语义理解，返回语音识别和语义理解结果。
   */
  MOBVOI_RECOGNIZER_ONLINE_SEMANTIC = 1,
  /**
   * 在线语音识别和垂直搜索，返回语音识别和垂直搜索结果。
   */
  MOBVOI_RECOGNIZER_ONLINE_ONEBOX = 2,
  /**
   * 离线语音识别。
   */
  MOBVOI_RECOGNIZER_OFFLINE = 3,
  /**
   * 混合在线和离线的语音识别。
   */
  MOBVOI_RECOGNIZER_MIX = 4,
  /**
   * 多关键词识别。
   */
  MOBVOI_RECOGNIZER_KEYWORDS = 5,
  /**
   * 联系人识别。
   */
  MOBVOI_RECOGNIZER_CONTACT_ONLY = 6,
  /**
   * 页面相关文字识别。
   */
  MOBVOI_RECOGNIZER_PSM = 7,
  /**
   * 页面相关文字识别混合离线在线识别
   */
  MOBVOI_RECOGNIZER_PSM_MIX = 8,
  /**
   * 页面相关文字识别混合离线在线识别（并行处理）
   */
  MOBVOI_RECOGNIZER_CONCURRENT_PSM_MIX = 9,
  /**
   * 页面相关文字识别和Oneshot。
   */
  MOBVOI_RECOGNIZER_PSM_ONESHOT = 10,
  /**
   * 页面相关文字识别和Oneshot和混合离线在线识别。
   */
  MOBVOI_RECOGNIZER_PSM_ONESHOT_MIX = 11,
  /**
   * 混合在线和离线的语音识别，不包含NLU和DM。
   */
  MOBVOI_RECOGNIZER_MIX_GENERAL_ASR = 12,
  /**
   * 增强后的关键词识别，例如加入ASR二次验证
   */
  MOBVOI_RECOGNIZER_ENHANCED_KEYWORDS = 13,
};

enum mobvoi_audio_dump_level {
  /**
   * 不存在音频文件。
   */
  MOBVOI_AUDIO_DUMP_NONE            = 0X00000000,
  /**
   * mobvoi_recognizer_type = MOBVOI_RECOGNIZER_ONLINE_ASR时保存音频文件。
   */
  MOBVOI_AUDIO_DUMP_ONLINE_ASR      = 0X00000001,
  /**
   * mobvoi_recognizer_type = MOBVOI_RECOGNIZER_ONLINE_SEMANTIC时保存音频文件。
   */
  MOBVOI_AUDIO_DUMP_ONLINE_SEMANTIC = 0X00000002,
  /**
   * mobvoi_recognizer_type = MOBVOI_RECOGNIZER_ONLINE_ONEBOX时保存音频文件。
   */
  MOBVOI_AUDIO_DUMP_ONLINE_ONEBOX   = 0X00000004,
  /**
   * mobvoi_recognizer_type = MOBVOI_RECOGNIZER_OFFLINE时保存音频文件。
   */
  MOBVOI_AUDIO_DUMP_OFFLINE         = 0X00000008,
  /**
   * 保存TTS音频文件。
   */
  MOBVOI_AUDIO_DUMP_TTS             = 0X00000010,
  /**
   * mobvoi_recognizer_type = MOBVOI_RECOGNIZER_KEYWORDS时保存音频文件。
   */
  MOBVOI_AUDIO_DUMP_KEYWORDS        = 0X00000020,
  /**
   * mobvoi_recognizer_type = MOBVOI_RECOGNIZER_CONTACT_ONLY时保存音频文件。
   */
  MOBVOI_AUDIO_DUMP_CONTACT_ONLY    = 0X00000040,
  /**
   * mobvoi_recognizer_type = MOBVOI_RECOGNIZER_PSM时保存音频文件。
   */
  MOBVOI_AUDIO_DUMP_PSM             = 0X00000080,
  /**
   * 保存传给SDK的原始音频。
   */
  MOBVOI_AUDIO_DUMP_ORIGIN          = 0X00000100,
  /**
   * 保存Hotword识别过程音频文件。
   */
  MOBVOI_AUDIO_DUMP_HOTWORD         = 0X00001000,
  /**
   * 保存以上所有过程音频文件。
   */
  MOBVOI_AUDIO_DUMP_ALL             = 0X000010FF,
};

enum mobvoi_tts_type {
  /**
   * NO TTS。
   */
  MOBVOI_NO_TTS = 0,
  /**
   * 在线TTS。
   */
  MOBVOI_TTS_ONLINE = 1,
  /**
   * 离线TTS。
   */
  MOBVOI_TTS_OFFLINE = 2,
  /**
   * 混合TTS。
   */
  MOBVOI_TTS_MIX = 3,
};

enum mobvoi_recognizer_offline_data_type {
  /**
   * 需要离线识别的应用名称。
   */
  MOBVOI_RECOGNIZER_OFFLINE_DATA_APPS = 0,
  /**
   * 需要离线识别的联系人名称。
   */
  MOBVOI_RECOGNIZER_OFFLINE_DATA_CONTACTS = 1,
  /**
   * 需要离线识别的艺术家。
   */
  MOBVOI_RECOGNIZER_OFFLINE_DATA_ARTISTS = 2,
  /**
   * 需要离线识别的歌曲名。
   */
  MOBVOI_RECOGNIZER_OFFLINE_DATA_SONGS = 3,
  /**
   * 需要离线识别的唱片名。
   */
  MOBVOI_RECOGNIZER_OFFLINE_DATA_ALBUMS = 4,
  /**
   * 需要离线识别的视频名。
   */
  MOBVOI_RECOGNIZER_OFFLINE_DATA_VIDEOS = 5,
  /**
   * 需要离线识别的热词名。(可用于offline oneshot)
   */
  MOBVOI_RECOGNIZER_OFFLINE_DATA_HOTWORDS = 6,

  /**
   * 类型最大值。
   */
  MOBVOI_RECOGNIZER_OFFLINE_DATA_MAX
};

enum mobvoi_init_type {
  /**
   * 需要初始化离线识别操作。
   * 当使用混合识别时，离线识别初始化也是默认需要的。
   */
  MOBVOI_INIT_OFFLINE_RECOGNIZER = 0x1,
  /**
   * 需要初始化TTS。
   */
  MOBVOI_INIT_TTS                = 0x2,
};

enum mobvoi_nlu_datagraph_type {
  /**
   * 指定音乐相关的数据关系。
   */
  MOBVOI_NLU_DATAGRAPH_MUSIC = 0,

  /**
   * 类型最大值。
   */
  MOBVOI_NLU_DATAGRAPH_TYPE_MAX
};

enum mobvoi_set_app_data_flag {
  /**
   * 设定app data下一轮识别生效。
   */
  MOBVOI_SET_APP_DATA_FLAG_NEXT_TURN = 0x0000,
  /**
   * 设定app data本轮nlu、dm和下一轮识别都生效。
   */
  MOBVOI_SET_APP_DATA_FLAG_BOTH_TURN = 0x0001,
};

typedef unsigned int tts_handle;

/******************* global *********************/
/**
 * SDK初始化。
 *
 * @param path     SDK的 .mobvoi 配置目录所在的路径，即 .mobvoi 的父目录。
 * @param init_cfg 需要初始化的模块，取值为mobvoi_init_type枚举类型的按位或。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_sdk_init(const char* path, unsigned init_cfg);

/**
 * SDK初始化。
 *
 * @param ro_path  SDK的 .mobvoi 只读配置目录所在的路径。
 * @param rw_path  SDK的 .mobvoi_rw 可写配置目录所在的路径。
 * @param init_cfg 需要初始化的模块，取值为mobvoi_init_type枚举类型的按位或。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_sdk_init_ext(const char* ro_path,
                        const char* rw_path,
                        unsigned init_cfg);

/**
 * 释放SDK资源。
 */
void mobvoi_sdk_cleanup();

/**
 * 发送语音数据给SDK，要求格式为16k采样，16bit位深的小端(Little-Endian)
 * 单声道PCM数据。
 *
 * @param frame 发送数据的缓冲区。
 * @param size  发送数据缓冲区长度。
 *
 * @return SDK真正收到的数据长度，返回-1表示参数有误。
 */
int mobvoi_send_speech_frame(const char* frame, int size);

/**
 * 设置verbose log级别。
 *
 * @param level 按照log详细程度在[1,3]中取值, 若level=3, 对录音数据进行dump。
 */
void mobvoi_set_vlog_level(int level);

/**
 * 获取verbose log级别。
 *
 * @return 按照verbose log详细程度在[1,3]中取值。
 */
int mobvoi_get_vlog_level();

/**
 * 设置log级别。当取值为"WARNING"及以上级别时，vlog不会输出。
 *
 * @param level 日志级别。取值"INFO", "WARNING", "ERROR", "FATAL"。
 */
void mobvoi_set_log_level(const char* level);

/**
 * 获取log级别。
 *
 * @return 日志级别。取值"INFO", "WARNING", "ERROR", "FATAL"。
 */
const char* mobvoi_get_log_level();

/**
 * 设置保存音频的级别。
 *
 * @param level 取值为mobvoi_audio_dump_level。
 */
void mobvoi_set_audio_dump_level(mobvoi_audio_dump_level level);

/**
 * 获取保存音频的级别。
 *
 * @return 取值为mobvoi_audio_dump_level。
 */
mobvoi_audio_dump_level mobvoi_get_audio_dump_level();

/******************* hotword *********************/

/**
 * 添加热词回调。
 *
 * @param handlers 热词回调实例。
 */
void mobvoi_hotword_add_handler(mobvoi_hotword_handler_vtable* handler);

/**
 * 添加热词回调，支持多热词版本。
 *
 * @param handlers 热词回调实例。
 */
// TODO(lj): replace old api when customer updated
void mobvoi_hotword_add_handler_ext(
  mobvoi_hotword_handler_vtable_ext* handler);

/**
 * 移除之前设置的热词回调。
 *
 * @param handlers 热词回调实例。
 */
void mobvoi_hotword_remove_handler(mobvoi_hotword_handler_vtable* handler);

/**
 * 移除之前设置的热词回调，支持多热词版本。
 *
 * @param handlers 热词回调实例。
 */
// TODO(lj): replace old api when customer updated
void mobvoi_hotword_remove_handler_ext(
  mobvoi_hotword_handler_vtable_ext* handler);

/**
 * 开始监听热词，使用默认的模型或者由mobvoi_hotword_set_keywords指定的关键词。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_hotword_start();

/**
 * 开始监听热词，指定热词模型，若传入的参数为空指针或空字符串，则使用默认值。
 *
 * @param model_name 指定热词模型的名称。
 *
 * @return 0表示成功, -1表示失败。
 */
// TODO(lj): replace old api when customer updated
int mobvoi_hotword_start_ext(const char* model_name);

/**
 * 停止监听热词。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_hotword_stop();

/**
 * 设置监听的热词关键词。
 *
 * @param keywors 关键字字符串，可以使用逗号分隔符来传入多个关键词。
 */
void mobvoi_hotword_set_keywords(const char* keywords);

/**
 * 上传应用名和联系人名到云端。用于在线的相关语音识别。
 *
 * @param apps         应用列表。
 * @param apps_num     应用数量。
 * @param contacts     联系人列表。
 * @param contacts_num 联系人数量。
 */
void mobvoi_recognizer_upload_user_info(const char* apps[],
                                        int apps_num,
                                        const char* contacts[],
                                        int contacts_num);

/**
 * 设置语音识别的回调。
 *
 * @param handlers 语音识别回调。
 */
void mobvoi_recognizer_set_handler(mobvoi_recognizer_handler_vtable* handlers);

/**
 * 设置NLU/DM的回调。
 *
 * @param handlers NLU/DM回调。
 */
void mobvoi_nlu_set_handler(mobvoi_nlu_handler_vtable* handlers);

/**
 * 设置识别任务参数。
 *
 * @param key 参考识别参数表。
 *
 * ------------------------------------------------------------------------------------
 * parameter name         : example value
 * ------------------------------------------------------------------------------------
 * "user_id"              : "12345678"
 * "location"             : "中国,北京市,北京市,海淀区,苏州街,3号,39.989602,116.316568"
 * "remote_start_silence" : "5000"(ms)
 * "remote_end_silence"   : "1000"(ms)
 * "local_start_silence"  : "60"(ms)
 * "local_end_silence"    : "1000"(ms)
 * "offline_model"        : "general"
 * "language"             : "0" - cn / "1" - en / "2" - yue
 * "navi_coord_system"    : "wgs84" / gcj02" / "bd09"
 * "addr_coord_system"    : "wgs84" / gcj02" / "bd09"
 * "audio_gain"           : "0.0"
 * "host_url"             : "m.mobvoi.com"
 * "homophone_on"         : "true" / "false"
 * "download_folder"      : "/tmp/mobvoi
 * "cbeam"                : "10.0"
 * "sdk_version"          : "41000"
 * "device_id"            : "6368756d656e77656e77656e2e636f6d"
 *
 * @param value 参考识别参数表。
 */
void mobvoi_recognizer_set_params(const char* key, const char* value);

/**
 * 获取参数。
 *
 * @param key 参考识别参数表。
 * -----------------------------------------------------------------------------
 * parameter name            : example value
 * -----------------------------------------------------------------------------
 * "user_id"                 : "12345678"
 * "app_key"                 : "1234567890ABCDEF1234567890ABCDEF" (32 bytes)
 * "remote_start_silence"    : "5000"(ms)
 * "remote_end_silence"      : "1000"(ms)
 * "local_start_silence"     : "60"(ms)
 * "local_end_silence"       : "1000"(ms)
 * "language"                : "0" - cn / "1" - en
 * "release_version"         : "project.platform.x.x.x.Release\nYYmmdd_HHMMSS"
 * "host_url"                : "m.mobvoi.com"
 * "audio_gain"              : "0.0"
 * "homophone_on"            : "true" / "false"
 * "download_folder"         : "/tmp/mobvoi
 * "hotword_model"           : "/mobvoi/nihaowenwen"
 * "cbeam"                   : "10.0"
 * "available_hotword_models : "nihaowenwen_wear,oktico_wear"
 * "sdk_version"             : "41000"
 * "device_id"               : "6368756d656e77656e77656e2e636f6d"
 *
 * @param value 参考识别参数表。
 * @param length value的长度。
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_recognizer_get_params(const char* key, char* value, int length);

/**
 * 设置应用名称列表，用于离线识别应用名。
 *
 * @param type 需要设置的数据类型，参考mobvoi_recognizer_offline_data_type。
 * @param num  数据字符串的数量。
 * @param data 某种类型对应的字符串列表，如APPS对应的是["支付宝", "微信"]。
 *
 * 注意：数据设置不会立即生效，需调用mobvoi_recogizer_build_data。
 */
void mobvoi_recognizer_set_data(mobvoi_recognizer_offline_data_type type,
                                int num, const char* data[]);

/**
 * 设置语音快词列表。
 *
 * @param num        语音快词数量。
 * @param keywords   语音快词列表。
 * @param model_name 语音快词模型的名称。
 *
 * 注意：快词设置不会立即生效，需调用mobvoi_recogizer_build_keywords。
 */
void mobvoi_recognizer_set_keywords(int num, const char* keywords[],
                                    const char* model_name);

/**
 * 设置页面相关数据。
 * 此接口是为设置MOBVOI_RECOGNIZER_PSM类型的recognizer，参数所指定数据将在调用
 * mobvoi_recognizer_start时即时编译，以达到识别其中任意单词的目的。
 *
 * @param options_num   页面数据选项数量。
 * @param options       页面数据选项列表。
 * @param keywords_num  语音快词数量。
 * @param keywords      语音快词列表。
 *
 * 示例：
 *  <<c synopsis>>
 *  #define COUNT_ARR(array) (sizeof(array) / sizeof(array[0]))
 *
 *  //　所有页面数据的字符串数组列表
 *  const char* options[] = {"拿渡麻辣香锅",
 *                           "必胜客宅急送",
 *                           "陶然四季涮肉",
 *                           "白家大院中关村",
 *                           "娃哈哈江南赋九号餐厅"};
 *
 * 　//　同时可以设定快词
 *  const char* keywords[] = {"第一个","第二个","第三个"，"第四个", "第五个"};
 *
 *  mobvoi_recognizer_set_psm_data(COUNT_ARR(options), options,
 *                                 COUNT_ARR(keywords), keywords);
 *  <<c synopsis>>
 */
void mobvoi_recognizer_set_psm_data(int options_num, const char* options[],
                                    int keywords_num, const char* keywords[]);

/**
 * 离线语音识别模型数据编译。
 * 数据设置请参考mobvoi_recognizer_set_data。
 */
void mobvoi_recognizer_build_data();

/**
 * 离线语音识别模型关键词编译。
 * 关键词设置请参考mobvoi_recognizer_set_keywords。
 *
 * @param model_name 语音快词模型的名称。
 */
void mobvoi_recognizer_build_keywords(const char* model_name);

/**
 * 设置应用相关数据供dm、lu模块进行特殊处理。如跨domain信息，途经点信息等。
 *
 * @param json_path   数据对应的json路径。
 * @param json_data   应用数据。
 * @param flag        暂时未使用。
 *
 * 示例：
 * ------------------------------------------------------------------------------------
 * json_path       :     json_data
 * ------------------------------------------------------------------------------------
 * control_param   :   {
 *                       "data":{
 *                         "running_apps":[
 *                           {
 *                             "task_name":"public.navigation",
 *                             "app_name":"kuwo",
 *                             "to":"五道口(地铁站)::,,,,,,39.99855111136873,116.34438004753852"
 *                           }
 *                         ]
 *                       }
 *                     }
 *
 * qa_control_param:  {
 *                      "type":"dialogue.fdt.multi_selection",
 *                      "data":{
 *                        "sel_index_phrase":[
 *                          [
 *                            "跳转",
 *                            "确定"
 *                          ],
 *                          [
 *                            "不跳转",
 *                            "取消",
 *                            "不要"
 *                          ],
 *                          [
 *                            "电影三",
 *                            "星球大战7",
 *                            "星球大战"
 *                          ]
 *                        ]
 *                      }
 *                    }
 */
void mobvoi_recognizer_set_app_data(const char* json_path,
                                    const char* json_data,
                                    mobvoi_set_app_data_flag flag);


/**
 * 设置热词关键词字符串
 *
 * @param hotword_str 热词关键词名字，可以逗号分隔以支持多个热词名字
 *
 *
 * 注意：该方法目前仅支持MOBVOI_RECOGNIZER_PSM_MIX_ONESHOT类型
 */
void mobvoi_recognizer_set_oneshot_hotword(const char* hotword_str);

/**
 * 添加额外的Http请求信息，需要云端支持，仅针对online语音识别任务。
 *
 * @param key 自定义key。
 * @param value 自定义value。
 *
 * 支持列表：
 * ------------------------------------------------------------------------------------
 * Key name         : example value
 * ------------------------------------------------------------------------------------
 * "hotword_str"    : "你好问问"  (可用于online oneshot)
 */
void mobvoi_recognizer_add_app_header(const char* key, const char* value);

/**
 * 开启一个语音识别任务。
 *
 * @param recognizer_type 参照mobvoi_recognizer_type。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_recognizer_start(mobvoi_recognizer_type recognizer_type);

/**
 * 开启一个热词检测加语音识别任务，在检测到热词之后，立刻进行语音识别。
 *
 * @param recognizer_type    参照mobvoi_recognizer_type。
 * @param hotword_model_name 指定热词模型的名称。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_recognizer_oneshot_start(mobvoi_recognizer_type recognizer_type,
                                    const char* hotword_model_name);

/**
 * 开启一个热词检测加语音识别任务，在检测到热词之后，立刻进行语音识别。
 *
 * @param recognizer_type    参照mobvoi_recognizer_type。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_recognizer_oneshot_start_ext(mobvoi_recognizer_type recognizer_type);

/**
 * 停止目前正在进行的语音识别任务，并且等待结果的返回。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_recognizer_stop();

/**
 * 取消目前正在进行的语音识别任务，不会有后续结果返回。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_recognizer_cancel();

/**
 * 返回语音识别消耗的时间。
 */
double mobvoi_recognizer_cost();

/**
 * 设置TTS参数。
 *
 * @param key 参考TTS参数表。
 * -------------------------------------------------------------------
 * |"language"             |"English" or "Mandarin" or "Cantonese"   |
 * -------------------------------------------------------------------
 * |"speed"                |0.5(slow) - 2.0(fast)                    |
 * -------------------------------------------------------------------
 * |"mandarin_speaker"     |"lucy", "cissy", "tina", "billy"         |
 * -------------------------------------------------------------------
 * |"english_speaker"      |"angela", "cissy"                        |
 * -------------------------------------------------------------------
 * |"cantonese_speaker"    |"dora"                                   |
 * -------------------------------------------------------------------
 * @param value 参考TTS参数表。
 */
void mobvoi_tts_set_params(const char* key, const char* value);

/**
 * 设置TTS播报的回调。
 *
 * @param handlers TTS播放回调。
 */
void mobvoi_tts_set_handler(mobvoi_tts_handler_vtable* handlers);

/**
 * 开始TTS合成。
 *
 * @param type 参考mobvoi_tts_type。
 * @param text 需要合成的字符串。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_tts_start_synthesis(mobvoi_tts_type type, const char* text);

/**
 * 取消上次的TTS合成。
 *
 * @return 0表示成功, -1表示失败。
 */
int mobvoi_tts_cancel_synthesis();

/**
 * 读取合成后的音频数据，格式为16k采样，16bit位深的小端(Little-Endian)
 * 单声道PCM数据。
 *
 * @param data   输出缓冲区。
 * @param length 缓冲区大小。
 *
 * @return 真正读到的字节数, -1表示读完。
 */
int mobvoi_tts_read_data(char* data, int length);

/**
 * 创建一个tts_handle表示的实例用于语音合成。可以反复使用。
 *
 * @return 0表示失败, 否则返回tts_handle用于语音合成。
 */
tts_handle mobvoi_tts_handle_create();

/**
 * 参见mobvoi_tts_set_params。
 */
void mobvoi_tts_handle_set_params(tts_handle handle,
                                  const char* key, const char* value);

/**
 * 参见mobvoi_tts_start_synthesis。
 */
int mobvoi_tts_handle_start_synthesis(tts_handle handle,
                                      mobvoi_tts_type type, const char* text);

/**
 * 参见mobvoi_tts_read_data。
 */
int mobvoi_tts_handle_read_data(tts_handle handle, char* data, int length);

/**
 * 参见mobvoi_tts_cancel_synthesis。
 */
void mobvoi_tts_handle_cancel_synthesis(tts_handle handle);

/**
 * 释放tts_handle表示的实例。
 */
void mobvoi_tts_handle_destroy(tts_handle handle);

/**
 * 加载Dialogue Manager任务配置文件。
 *
 * @param task_config 配置文件路径。
 */
void mobvoi_dialogue_config_load(const char* task_config);

/**
 * 执行Dialogue Manager引擎。
 *
 * @param nlu NLU字符串。
 *
 * @return 对话分析结果。
 */
const char* mobvoi_dialogue_process(const char* nlu);

/**
 * 释放mobvoi_dialogue_process结果的存储空间。
 *
 * @param ptr 字符串指针，由mobvoi_dialogue_process返回。
 */
void mobvoi_dialogue_free(const char* ptr);

/**
 * 重置Dialogue Manager上下文。
 *
 * @param recognizer_type 参照mobvoi_recognizer_type。
 *
 * 目前支持的reset type如下：
 *
 *   MOBVOI_RECOGNIZER_ONLINE_ONEBOX
 *   MOBVOI_RECOGNIZER_OFFLINE
 *   MOBVOI_RECOGNIZER_MIX
 */
void mobvoi_dialogue_reset(mobvoi_recognizer_type recognizer_type);

/**
 * 卸载Dialogue Manager任务配置，同时上下文会被重置，见mobvoi_dialogue_reset。
 */
void mobvoi_dialogue_config_unload();

/**
 * 设置NLU数据关系图。
 *
 * @param type 数据关系图类型。见mobvoi_nlu_datagraph_type。
 * @param data 目前只支持音乐类型，其数据格式如下：
 *
 * [
 *  { "song": "song1", "artist": "artist1", "album": "album1" },
 *  { "song": "song2", "artist": "artist2", "album": "album2" }
 * ]
 *
 */
void mobvoi_nlu_set_datagraph(mobvoi_nlu_datagraph_type type, const char* data);

/**
 * 执行语义分析。
 *
 * @param query  指定语义分析目标字符串。
 * @param domain 指定语义分析相关的domain。
 *
 * @return 语义分析结果。
 */
const char* mobvoi_nlu_process(const char* query, const char* domain);

/**
 * 释放语义分析结果的存储空间。
 *
 * @param ptr 字符串指针，由mobvoi_nlu_process返回。
 */
void mobvoi_nlu_free(const char* ptr);

/**
 * 加载Language Generator任务配置文件。
 *
 * @param lg_config 配置文件路径。
 */
void mobvoi_lg_config_load(const char* lg_config);

/**
 * 卸载Language Generator任务配置, 释放相关资源。
 */
void mobvoi_lg_config_unload();

/**
 * 在线的文本搜索。
 *
 * @param query            指定文本搜索字符串。
 * @param location         为空字符串时，
 *                         使用mobvoi_recognizer_set_params中设置的location。
 * @param qa_control_param 对话控制参数字符串。
 * @param handler          搜索回调实例。
 */
void mobvoi_text_search_process(const char* query,
                                const char* location,
                                const char* qa_control_param,
                                mobvoi_text_search_handler_vtable* handler);

/**
 * 在线的文本分析，仅提供语义分析没有搜索结果。
 *
 * @param query   指定语义分析字符串。
 * @param handler 语义分析回调实例。
 */
void mobvoi_text_semantic_process(const char* query,
                                  mobvoi_text_search_handler_vtable* handler);

/**
 * 同步返回在线的文本搜索结果。
 *
 * @param query            指定文本搜索字符串。
 */
std::string mobvoi_onebox_search(const char* query);

/**
 * 设置音频处理相关接口。
 *
 * @param handler          接口函数指针。
 */
void mobvoi_set_ecnr_handler(mobvoi_ecnr_vtable* handler);

#ifdef __cplusplus
}
#endif

#endif  // LINUX_SPEECH_SDK_H_
