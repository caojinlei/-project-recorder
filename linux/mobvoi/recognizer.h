// Copyright 2018 Mobvoi Inc. All Rights Reserved.

#ifndef LINUX_INTERFACE_RECOGNIZER_H_
#define LINUX_INTERFACE_RECOGNIZER_H_

#include <string>

namespace mobvoi {
namespace sdk {

class RecognizerListener {
 public:
  /**
   * 在检测到有人说话后回调。
   */
  virtual void OnSpeechDetected() = 0;

  /**
  　* 在检测到本地语音之后，又检测到本地静音时回调。
  　*/
  virtual void OnLocalSilenceDetected() = 0;

  /**
   * 服务器端检测到静音（说话人停止说话）后回调。
   */
  virtual void OnRemoteSilenceDetected() = 0;

  /**
   * 语音识别部分结果返回，比如“今天天气怎么样”，会按顺序返回“今天”，“今天天气”。
   *
   * @param result 识别到的部分结果字符串。
   */
  virtual void OnPartialTranscription(const std::string &result) = 0;

  /**
   * 语音识别最终结果返回，比如“今天天气怎么样”，会按顺序返回“今天”，“今天天气”，
   * “今天天气怎么样”，最后一个就是Final Transcription。
   *
   * @param result 最终认为用户说的完整字符串。
   */
  virtual void OnFinalTranscription(const std::string &result) = 0;

  /**
   * 关键词识别结果返回。 参考MOBVOI_RECOGNIZER_KEYWORDS|MOBVOI_RECOGNIZER_PSM
   *
   * @param result 识别结果字符串。
   */
  virtual void OnKeyword(const std::string &result) = 0;

  /**
   * 语音搜索结果返回, 为JSON格式字符串。
   *
   * @param result 语音搜索结果json。
   */
  virtual void OnResult(const std::string &result, double cost) = 0;

  /**
   * 计算得到输入语音片断的声压（SPL）值时，回调该方法。
   *
   * @param volume 根据语音的能量算出，取值范围：[0.0, 1.0]。
   */
  virtual void OnVolume(float volume) = 0;

  /**
   * 当执行出错时会回调。
   *
   * @param error_code 错误码。
   */
  virtual void OnError(int error_code, double cost) = 0;

  /**
   * DM结果返回, 为JSON格式字符串。
   *
   * @param result DM结果json。
   */
  virtual void OnDMResult(const std::string &result) = 0;

  /**
   * LU结果返回, 为JSON格式字符串。
   *
   * @param result LU结果json。
   */
  virtual void OnLUResult(const std::string &result) = 0;

  /**
   * (可选)
   * 识别器在oneshot场景下检查到热词后回调。
   */
  virtual void OnOneshotHotwordDetected() {}
};

class Recognizer : public RecognizerListener {
 public:
  enum RecognizerType {
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
    * 混合在线和离线的语音识别，不包括NLU和DM。
    */
    MOBVOI_RECOGNIZER_MIX_GENERAL_ASR = 12,
    /**
     * 增强后的页面文字识别，例如加入ASR二次验证
     */
    MOBVOI_RECOGNIZER_ENHANCED_PSM = 13,
    /**
     * 增强后的关键词识别，例如加入ASR二次验证
     */
    MOBVOI_RECOGNIZER_ENHANCED_KEYWORDS = 13,
  };

  enum ErrorCode {
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

  Recognizer();

  virtual ~Recognizer();

  enum Status {
    STATUS_READY,
    STATUS_STARTED,
    STATUS_STOPPED,
    STATUS_CANCELED,
    STATUS_ERROR
  };

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
  void SetAppData(const char* json_path, const char* json_data, int flag);

  /**
   * 发送语音数据给SDK，要求格式为16k采样，16bit位深的小端(Little-Endian)
   * 单声道PCM数据。
   *
   * @param frame 发送数据的缓冲区。
   * @param size  发送数据缓冲区长度。
   *
   * @return SDK真正收到的数据长度，返回-1表示参数有误。
   */
  int SendSpeechFrame(const char *frame, int size);

  /**
   * 开启一个语音识别任务。
   *
   * @param recognizer_type 参照mobvoi_recognizer_type。
   *
   * @return 0表示成功, -1表示失败。
   */
  int Start(RecognizerType type);

  /**
   * 停止目前正在进行的语音识别任务，并且等待结果的返回。
   * @return　0表示成功, -1表示失败。
   */
  int Stop();

  /**
   * 取消目前正在进行的语音识别任务，不会有后续结果返回。
   *
   * @return 0表示成功, -1表示失败。
   */
  int Cancel();

 private:
  void *inner_;
};  // class Recognizer

}  // namespace sdk
}  // namespace mobvoi

#endif  // LINUX_INTERFACE_RECOGNIZER_H_
