///////////////////////////////////////////////////////////////////////////////
//!\file   ISpeechAdapter.h
//!\brief  Header file for ISpeechAdapter.
//!\author Tang Wei wei.tang@preh.cn
//!
//!Copyright (c) 2017 Joyson Preh Car Connect
//!All rights reserved
///////////////////////////////////////////////////////////////////////////////

#ifndef _SPEECH_ADAPTER_H_
#define _SPEECH_ADAPTER_H_

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include "SpeechTypes.h"
#include "SpeechErrorID.h"
#include "ISpeechSDS.h"
#include "ISpeechTTS.h"

namespace speech
{
class ISpeechAdapter; /* Forward declaration */
/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/
/**
 * Create a ISpeechAdapter instance.
 */
extern "C"  SPEECH_API_PORT ISpeechAdapter *SpeechCreateAdapter();
/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
/**
 * ISpeechAdapter interface class.
 */
class ISpeechAdapter
{
public:
    /**
     * Initialize the adapter instance.
     * @param[in]  pUser: SDS engine id.
     * @return:    SpeechErrorID
     */
    virtual SpeechErrorID Create(const void* pUser) = 0;
    /**
     * Un-initialize the adapter instance.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID Destroy() = 0;

    /**
     * Register a SDS instance to adapter.
     * @param[in]  pSds:Pointer of the SDS instance.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID RegisterSDSInstance(ISpeechSDS *pSds) = 0;

    /**
     * Get the SDS instance.
     * @param[in]  pSds:Pointer of the SDS instance.
     * @return: SpeechErrorID
     */
     virtual ISpeechSDS* GetSDSInstance() = 0;

    /**
     * Register the callback function to adapter that used to create the TTS instance.
     * @param[in]  pCreateTTS: Callback .
     * @return:    SpeechErrorID
     */
    virtual SpeechErrorID RegisterTTSInstanceCreator(SpeechCreateTTSCB pCreateTTS) = 0;

    /**
     * Get the callback function that used to create the TTS instance.
     * @return:    SpeechCreateTTSCB
     */
    virtual SpeechCreateTTSCB GetTTSInstanceCreator() = 0;

    /**
     * Request the adapter to get the data of the 3rd application,e.g. search poi data, media metadata, phone contact, favorite list.
     * @param[in]  param: Parameter, a json string, the detail information refers to the interface document.
     *                    e.g:{"domain": "domain", "dialogID": "OpenAirCleaner", "dataType": "OpenAirCleaner", "dataParameter": { Request parameter }, "dataResult": null, "userData": "user Data"}
     * @param[out]  result: Synchronous response, a json string, the detail information refers to the interface document
     *                      e.g:{"domain": "domain", "dialogID": "OpenAirCleaner", "dataType": "OpenAirCleaner", "dataParameter": { Request parameter }, "dataResult": { Request result }, "userData": "user Data"}
     * @return: SpeechErrorID, Returns the ERR_ASYN represents the response will be replied by ISpeechSDS::RequestDataAsynResult() method.
     */
    virtual SpeechErrorID RequestData(const std::string &param, std::string &result) = 0;

    /**
     * Get the version
     */
    virtual const char* GetVersion() = 0;

public:
    ISpeechAdapter() {}
    virtual ~ISpeechAdapter() {}
};
} //namespace speech

#endif //_SPEECH_ADAPTER_H_
