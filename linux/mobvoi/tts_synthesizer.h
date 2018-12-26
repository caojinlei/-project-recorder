// Copyright 2018 Mobvoi Inc. All Rights Reserved.

#ifndef LINUX_INTERFACE_TTS_SYNTHESIZER_H_
#define LINUX_INTERFACE_TTS_SYNTHESIZER_H_

namespace mobvoi {
namespace sdk {

class TtsSynthesizer {
 public:
  enum TtsType {
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

  TtsSynthesizer();

  virtual ~TtsSynthesizer();

  /**
   * 开始TTS合成。
   *
   * @param text 需要合成的字符串。
   * @param type TtsType。
   *
   * @return 0表示成功, -1表示失败。
   */
  int Start(const char* text, TtsType type);

  /**
   * 读取合成后的音频数据，格式为16k采样，16bit位深的小端(Little-Endian)
   * 单声道PCM数据。
   *
   * @param buffer 输出缓冲区。
   * @param size   缓冲区大小。
   *
   * @return 真正读到的字节数, -1表示读完。
   */
  int Read(char* buffer, int size);

  /**
   * 取消上次的TTS合成。
   */
  void Cancel();

 private:
  void* inner_;
};

}  // namespace sdk
}  // namespace mobvoi

#endif  // LINUX_INTERFACE_TTS_SYNTHESIZER_H_
