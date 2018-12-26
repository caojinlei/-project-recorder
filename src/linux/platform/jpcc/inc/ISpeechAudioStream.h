///////////////////////////////////////////////////////////////////////////////
//!\file   ISpeechAudioStream.h
//!\brief  Header file for ISpeechAudioStream
//!\author JTang Wei wei.tang@preh.cn
//!
//!Copyright (c) 2017 Joyson Preh Car Connect
//!All rights reservied
///////////////////////////////////////////////////////////////////////////////

#ifndef _SPEECH_AUDIOSTREAM_H_
#define _SPEECH_AUDIOSTREAM_H_

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include "SpeechTypes.h"
#include "SpeechErrorID.h"

namespace speech
{
class ISpeechAudioStream; /* Forward declaration */
/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/
/**
 * Audio stream direction type
 */
typedef enum SPEECH_AUDIOSTREAM_TYPE
{
    AS_OUTPUT, /* TTS output */
    AS_INPUT,  /* MIC input */
} AS_TYPE;
/**
 * Audio stream mode, that also identities the audio connection type of the voice output.
 * xxx_CONT are the mixed audio channel.
 */
typedef enum SPEECH_AUDIOSTREAM_MODE
{
    AS_OUTPUT_SDS_MENU = 0,
    AS_OUTPUT_SDS,             /* Speech Dialogue */
    AS_OUTPUT_SDS_CONT,
    AS_OUTPUT_TTS_READOUT,     /* Default Text-to-Speech */
    AS_OUTPUT_TTS_READOUT_CONT,
    AS_OUTPUT_TTS_TRAFFIC,     /* Traffic information */
    AS_OUTPUT_TTS_WARNING,
    AS_OUTPUT_NAV_MENU,
    AS_OUTPUT_NAV,             /* Navi guidance */
    AS_OUTPUT_NAV_HIGH,
    AS_OUTPUT_NAV_TRAFFIC_HIGH,

    AS_INPUT_SDS_NORMAL = 200,  /* MIC input for normal usecase. */
    AS_INPUT_SDS_WUW            /* MIC input for Wake-up usecase. */
} AS_MODE;

/**
 * AudioStream state of the SDS engine
 */
typedef enum SPEECH_AUDIOSTREAM_MESSAGE
{
    AS_OUTPUT_START = 1001,         /* Starting the audio output stream, active state. */
    AS_OUTPUT_STOP = 1002,          /* Stopped the audio output stream, active state  */
    AS_OUTPUT_COMPLETED = 1005,     /* Completed the audio output stream, active state. */

    AS_OUTPUT_BE_PAUSE = 1101,      /* Audio output stream was paused by some reasons, passive state. */
    AS_OUTPUT_BE_RESUME = 1102,     /* Audio output stream was resumed by some reasons, passive state. */
    AS_OUTPUT_BE_STOP = 1103,       /* Audio output stream was stopped by some reasons, passive state. */
    AS_OUTPUT_BE_CLOSE = 1104,      /* Audio output stream was closed by some reasons, passive state. */

    AS_INPUT_START = 2001,          /* Starting the audio input stream, active state. */
    AS_INPUT_STOP = 2002,           /* Stopped the audio input stream, active state. */

    AS_INPUT_BE_STOP = 2101,        /* Audio input stream was stopped by some reasons, passive state. */
} AS_MESSAGE, AS_STATUS;

/**
*  Callback of the audio stream of the speech dialog system, The audio adapter calls this callback to get the tts output stream from SDS
*  and set the mic stream input stream to SDS.
*  @param[in]  pData: Data buffer.
*  @param[in]  iSize: Size of the data buffer.
*  @param[out] iGetSize: Actually set/get size.
*  @param[in]  pUser: Sds audio stream id, set by ISpeechAudioStream::Open().
*  @return:    0, OK; -1, ERROR; 1, tts synthesis completed.
*/
typedef int (* SpeechAudioStreamDataCB)(const void* pData,
                                     uint32_t iSize,
                                     uint32_t *iGetSize,
                                     const void* pUser);

/**
*  @brief  Callback of the state of the speech dialog system.
*  @param[in]  pUser: Sds audio stream id, set by ISpeechAudioStream::Open().
*  @param[in]  eMsg: Refers to AS_MESSAGE.
*  @param[in]  wParam: Reserved.
*  @param[in]  lParam: Reserved.
*/
typedef void (* SpeechAudioStreamMsgCB)(const void* pUser,
                                     AS_MESSAGE eMsg,
                                     uint32_t wParam,
                                     int32_t lParam);

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/
/**
 * Create an audio stream instance.
 * @param[in]  eType: Refers to AS_TYPE.
 * @return: A ISpeechAudioStream instance.
 */
extern "C"  SPEECH_API_PORT ISpeechAudioStream *SpeechCreateAudioStream(AS_TYPE eType);
/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
/**
 * Audio stream interface class
 */
class ISpeechAudioStream
{
public:
    /**
     * Open an audio stream channel. Must be called before the starting of dialogue.
     * @param[in]  eType: Refers to AS_TYPE.
     * @param[in]  eMode: Refers to AS_MODE.
     * @param[in]  funcDataCB: Callback of the audio stream.
     * @param[in]  funcMsgCB: Callback of the state of the SDS engine.
     * @param[in]  pUser: Sds audio stream id.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID Open(AS_MODE eMode,
                            SpeechAudioStreamDataCB funcDataCB,
                            SpeechAudioStreamMsgCB funcMsgCB,
                            const void* pUser) = 0;
    /**
     * Close an audio stream channel.Must be called after a dialogue ended.
     */
    virtual SpeechErrorID Close() = 0;

    /**
     * Start to get/set the audio input/output stream.
     */
    virtual SpeechErrorID Start() = 0;
    /**
     * Stop the audio input/output stream.
     */
    virtual SpeechErrorID Stop() = 0;
    /**
     * Pause the audio input/output stream.
     */
    virtual SpeechErrorID Pause() = 0;
    /**
     * Resume the audio input/output stream.
     */
    virtual SpeechErrorID Resume() = 0;
    /**
     * Get the version.
     */
    virtual const char* GetVersion() = 0;

public:
    ISpeechAudioStream() {}
    virtual ~ISpeechAudioStream() {}
}; //class ISpeechAudioStream
}//namespace speech

#endif //_SPEECH_AUDIOSTREAM_H_
