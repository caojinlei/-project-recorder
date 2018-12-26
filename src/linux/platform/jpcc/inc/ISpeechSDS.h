///////////////////////////////////////////////////////////////////////////////
//!\file   ISpeechSDS.h
//!\brief  Header file for ISpeechSDS
//!\author Tang Wei wei.tang@preh.cn
//!
//!Copyright (c) 2017 Joyson Preh Car Connect
//!All rights reservied
///////////////////////////////////////////////////////////////////////////////
#ifndef _SPEECH_SDS_H_
#define _SPEECH_SDS_H_

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include "SpeechTypes.h"
#include "SpeechErrorID.h"
#include "ISpeechTTS.h"

namespace speech
{
class ISpeechSDS; /* Forward declaration */
/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/
/**
 * Language
 */
#define SPEECH_SDS_LANGUAGE  "SdsLanguage"  /* It can be used as the first parameter of the ISpeechSDS::SetParameter method. */
#define SPEECH_SDS_LANGUAGE_MANDARIN "Mandarin"
#define SPEECH_SDS_LANGUAGE_ENGLISH  "English"
#define SPEECH_SDS_LANGUAGE_CANTONESE "Cantonese"

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/

/**
 * The callback used to create a sds instance.
 * Must call the ISpeechSDS::Destroy() method before delete it.
 * Because the system just support a single SDS instance, the sds instance created by SDS engine, so DO NOT USE IT.
 */
typedef ISpeechSDS *(* SpeechCreateSDSCB)();
/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/
/**
 * Create a ISpeechSDS instance.
 * Deprecated.
 */
extern "C"  SPEECH_API_PORT ISpeechSDS *SpeechCreateSDS();
/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/
/**
 * SDS interface class, it is implemented by SDS supplier.
 */
class ISpeechSDS
{

public:
    /**
     * Initialize the SDS instance.
     * @param[in] szResPath: SDS resource path.
     * @param[in] eLang: SDS language.
     * @param[in] pUser: SDS user ID, it will be used in ISpeechAdapter::SdsMessage.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID Create(const std::string &language, const void* pUser) = 0;

    /**
     * Un-initialize the SDS instance.
     */
    virtual SpeechErrorID Destory() = 0;

    /**
     * Set the variable parameter, e.g. customized WuW, language, dialet language, alwayson, beamforming, and so on.
     * @param[in] key: the detail information refers to the interface document.
     * @param[in] value: the detail information refers to the interface document.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID SetParameter(const std::string &key, const std::string &value) = 0;

    /**
     * Get the variable parameter.
     * @param[in] key: the detail information refers to the interface document.
     * @param[in] value: the detail information refers to the interface document.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID GetParameter(const std::string &key, std::string &value) = 0;

    /**
     * Upload the dynamic data(list show data, media metadata, phone contact, app list, smarthome device list and so on) to SDS.
     * @param[in] dynamicData: A JSON string,the detail information refers to the interface document.
     *                   e.g.{"domain": "media", "dataID": "646fda12-f747-5a7c-afc1-d917b9710022", "dataType": "musicMetadata", "data": [ Data array ]}
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID UploadDynamicData(const std::string &dynamicData) = 0;

    /**
     * Remove the uploaded dynamic data.
     * @param[in] dynamicData: A JSON string,the detail information refers to the interface document.
     *                        e.g.{"domain": "media", "dataID": "646fda12-f747-5a7c-afc1-d917b9710022", "dataType": "musicMetadata", "data": []}.
     * @return: SpeechErrorID
     */

    virtual SpeechErrorID RemoveDynamicData(const std::string &dynamicData) = 0;

    /**
     * Adapter actively push data to SDS, e.g. hard key event, user screen events, and so on.
     * @param[in] data: A JSON string,the detail information refers to the interface document.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID PushData(const std::string &data) = 0;

    /**
     * Adapter actively get data from SDS,e.g: SDS dialogue status, engine status, and so on.
     * @param[in] data: A JSON string, the detail information refers to the interface document.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID GetData(const std::string &data) = 0;

    /**
     * Asynchronous reply the ISpeechAdapter::RequestData() method.
     * @param[in] result:A JSON string,the detail information refers to the interface document.
     * @return: SpeechErrorID
     */
    virtual SpeechErrorID RequestDataAsynResult(const std::string &result) = 0;

    /**
     * Get the version.
     */
    virtual std::string GetVersion() = 0;

    /**
     * Test interface, Used by engineering mode.
     * @param[in] param: A string or Json string, the detail information refers to the interface document.
     * @param[out] result: A string or Json string, the detail information refers to the interface document.
     */
    virtual SpeechErrorID TestData(const std::string &param, std::string &result) = 0;

public:
    ISpeechSDS() {}
    virtual ~ISpeechSDS() {}
};
}//namespace speech

#endif //_SPEECH_SDS_H_
