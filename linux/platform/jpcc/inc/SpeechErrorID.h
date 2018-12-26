///////////////////////////////////////////////////////////////////////////////
//!\file   SpeechErrorID.h
//!\brief  Header file for ErrorID
//!\author Tang Wei wei.tang@preh.cn
//!
//!Copyright (c) 2017 Joyson Preh Car Connect
//!All rights reservied
///////////////////////////////////////////////////////////////////////////////

#ifndef _SPEECH_ERRORID_H_
#define _SPEECH_ERRORID_H_

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include "SpeechTypes.h"

namespace speech
{
/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/
#define ERR_SUCCESS 0
#define ERR_FAILED -1

#define ERR_ASYN             10001
#define ERR_INVALIDPARAM     10002
#define ERR_INVALIDCALL      10003
#define ERR_OUTOFMEMORY      10004
#define ERR_INVALIDRESOURCE  10005
#define ERR_FILENOTFOUND     10006
#define ERR_UNSUPPORTED      10007
#define ERR_OUTOFRANGE       10008
#define ERR_NOTINIT          10009
#define ERR_TTSPLAYER_STOPPED 10010
#define ERR_PENDING          10011
#define ERR_STATEERROR       10012
#define ERR_NOPERMIT         10013
#define ERR_AUDIOCONNECTFAILED 10014
#define ERR_AUDIOCONNECTDENIED 10015
#define ERR_AUDIOCONNECTTIMEOUT 10016

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/
typedef int32_t  SpeechErrorID;
/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/

}//namespace

#endif //_SPEECH_ERRORID_H_
