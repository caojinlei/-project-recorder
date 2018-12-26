///////////////////////////////////////////////////////////////////////////////
//!\file   ISpeechTTS.h
//!\brief  Header file for ISpeechTTS
//!\author Tang Wei wei.tang@preh.cn
//!
//! Copyright (c) 2017 Joyson Preh Car Connect
//! All rights reservied
///////////////////////////////////////////////////////////////////////////////
#ifndef _SPEECH_TTS_H_
#define _SPEECH_TTS_H_

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/

#include <string>

#include "ISpeechAudioStream.h"
#include "SpeechErrorID.h"
#include "SpeechTypes.h"

namespace speech {
class ISpeechTTS; /* Forward declaration */
/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/
/**
 * State of the TTS engine
 */
typedef enum SpeechTTSMsg {
  TM_ERROR = 10001, /* Error*/
  TM_START,         /* Starting to play.*/
  TM_PROGRESS,      /* Playing, wParam is the progress of playing. */
  TM_COMPLETED,     /* Completed */
  TM_PAUSED,        /* Paused */
  TM_STOPPED        /* Stopped */
} TTS_MSG;

/**
   *  ISpeechTTS callback function.
   *  @param[in] pUser: User identifier.
   *  @param[in] eMsg: TTS engine status.
   *  @param[in] wParam: Additional parameter.
   *  @param[in] lParam: Additional parameter.
   *  @return:SpeechErrorID
 */
typedef void (*SpeechTTSMsgCB)(const void *pUser, TTS_MSG eMsg, uint32_t wParam,
                               int32_t lParam);

/**
 * The callback used to create a tts instance.
 * Must call the ISpeechTTS::Destroy() method before delete it.
 */
typedef ISpeechTTS *(*SpeechCreateTTSCB)();
/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/

/**
 * Create a tts instance.
 * Deprecated.
 */
extern "C" SPEECH_API_PORT ISpeechTTS *SpeechCreateTTS();
/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
/**
 * TTS interface class, it is implemented by SDS supplier.
 * Sequence:
 * Adapter                                           TTSEngine
 *  |                                                   |
 *  -------------------initialize------------------------
 *  |                                                   |
 *  |        ISpeechTTS* inst = SpeechCreateTTS()       |
 *  |-------------------------------------------------->|
 *  |                                                   |
 *  |               inst->Create()                      |
 *  |-------------------------------------------------->|
 *  |                                                   |
 *  |              inst->SetParameter()                 |
 *  |-------------------------------------------------->|
 *  |                                                   |
 *  ---------------------play a tts----------------------
 *  |                                                   |
 *  |               inst->OpenAudioStream()             |
 *  |-------------------------------------------------->|
 *  |                                                   |
 *  |            inst->Start/Stop/Pause/Resume()        |
 *  |-------------------------------------------------->|
 *  |                                                   |
 *  |                SpeechTTSMsgCB()                   |
 *  |<--------------------------------------------------|
 *  |                                                   |
 *  |              inst->CloseAudioStream()             |
 *  |-------------------------------------------------->|
 *  |                                                   |
 *  -------------------de-initialize---------------------
 *  |                                                   |
 *  |                 inst->Destroy()                   |
 *  |-------------------------------------------------->|
 *  |                                                   |
 *  |                   delete inst                     |
 *  |---------------------------------------------------|
 *  |                                                   |
 */
class ISpeechTTS {
 public:
  /**
   * Initialize the tts instance.
   * @param[in] szResPath: Resource path.
   * @param[in] eMode: TTS synthesis mode, that also identities the audio
   * connection type of the voice output, as the first paramter of
   * ISpeechAudioStream::Open method.
   * @param[in] funcMsgCB: Used to notify the tts engine status.
   * @param[in] pUser:As the first parameter of the funcMsgCB.
   * @return: SpeechErrorID
   */
  virtual SpeechErrorID Create(AS_MODE eMode, SpeechTTSMsgCB funcMsgCB,
                               const void *pUser) = 0;

  /**
   * Un-initialize the tts instance.
   */
  virtual SpeechErrorID Destroy() = 0;

  /**
   * Set the variable parameter, e.g: language, speaker, speaking speed, voice
   * volume, voice pitch, and so on.
   * @param[in] key: the detail information refers to the interface document.
   * @param[in] value: the detail information refers to the interface document.
   * @return: SpeechErrorID
   */
  virtual SpeechErrorID SetParameter(const std::string &key,
                                     const std::string &value) = 0;

  /**
   * Get the variable parameter.
   * @param[in] key: the detail information refers to the interface document.
   * @param[in] value: the detail information refers to the interface document.
   * @return: SpeechErrorID
   */
  virtual SpeechErrorID GetParameter(const std::string &key,
                                     std::string &value) = 0;

  /**
   * Open audio stream.It will be called before Start(), TTS engine must keep
   * the audio stream is opening until CloseAudioStream() is called.
   * This is a synchronous method, this means OpenAudioStream will return until
   * TTS engine calls ISpeechAudioStream::Open method has returned.
   */
  virtual SpeechErrorID OpenAudioStream() = 0;

  /**
   * Close audio stream.
   * This is a synchronous method, this means CloseAudioStream will return until
   * TTS engine calls ISpeechAudioStream::Close method has returned.
   */
  virtual SpeechErrorID CloseAudioStream() = 0;

  /**
   * Play a Text.
   * @param[in] text: Text content.
   * @return: SpeechErrorID
   */
  virtual SpeechErrorID Start(const std::string &text) = 0;

  /**
   * Stop a playing tts.
   */
  virtual SpeechErrorID Stop() = 0;

  /**
   * Pause a playing tts.
   */
  virtual SpeechErrorID Pause() = 0;

  /**
   * Resume a paused tts.
   */
  virtual SpeechErrorID Resume() = 0;

  /**
   * Get the version.
   */
  virtual std::string GetVersion() = 0;

  /**
   * Test interface, Used by engineering mode.
   * @param[in] param: A string or Json string, the detail information refers to
   * the interface document.
   * @param[out] result: A string or Json string, the detail information refers
   * to the interface document.
   */
  virtual SpeechErrorID TestData(const std::string &param,
                                 std::string &result) = 0;

 public:
  ISpeechTTS() {}
  virtual ~ISpeechTTS() {}
};  // class ISpeechTTS
}  // namespace speech
#endif  //_SPEECH_TTS_H_
