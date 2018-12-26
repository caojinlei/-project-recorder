///////////////////////////////////////////////////////////////////////////////
//!\file   SpeechTypes.h
//!\brief  Header file for types definition.
//!\author Tang Wei wei.tang@preh.cn
//!
//!Copyright (c) 2017 Joyson Preh Car Connect
//!All rights reserved
///////////////////////////////////////////////////////////////////////////////

#ifndef _SPEECH_TRACE_H_
#define _SPEECH_TRACE_H_

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/
#define FILENAME(x) (strrchr(x, '/') ? strrchr(x, '/') + 1 : x)

#if 1
static inline unsigned long ms_now()
{
    struct timespec ts = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

#define LOG(type, format, ...) printf("[%ld][ SPEECH ] [%s] [%s] [%d] [%s]: " format "\n",ms_now(), FILENAME(__FILE__), __FUNCTION__, __LINE__, type,  ##__VA_ARGS__)
#define LOG_D(format, ...)  LOG("---DEBUG---", format, ##__VA_ARGS__)
#define LOG_I(format, ...)  LOG("===INFOR===", format, ##__VA_ARGS__)
#define LOG_W(format, ...)  LOG("***WARNG***", format, ##__VA_ARGS__)
#define LOG_E(format, ...)  LOG("***ERROR***", format, ##__VA_ARGS__)
#else
#define LOG(type, format, ...)
#define LOG_D(format, ...)  LOG("---DEBUG---", format, ##__VA_ARGS__)
#define LOG_I(format, ...)  LOG("===INFOR===", format, ##__VA_ARGS__)
#define LOG_W(format, ...)  LOG("***WARNG***", format, ##__VA_ARGS__)
#define LOG_E(format, ...)  LOG("***ERROR***", format, ##__VA_ARGS__)
#endif
#define FUNCIN() LOG_D("Entering...")
#define FUNCOUT() LOG_D("Leaving...")

/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * GLOBAL VARIABLE DECLARATIONS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * CLASS DECLARATIONS
 *---------------------------------------------------------------------------*/

#endif //_SPEECH_TRACE_H_
