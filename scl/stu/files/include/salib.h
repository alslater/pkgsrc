
/***************************************************************
 *
 * saclib.h    - This library provides a flat "c" style
 *               interface to the "C++" secure authorization API.
 *               It provides functions to invoke that manipulate
 *               C++ instances via "C" stype function calls.
 *               This layer is shared by "C", "VB", "Java".
 *
 ***************************************************************/

#ifndef SACLIB_H
#define SACLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "STU_platform.h"

#include "Enumerations.h"

typedef char CHAR;
typedef CHAR *LPSTR;

#define STATUS_MAX          32
#define STATUS_ERROR        -3

#define MESSAGE_MAX         128
#define MESSAGE_ERROR       -4

#define CONNECTION_MAX      32
#define CONNECTION_ERROR    -5

#ifdef _WIN32
/*
 * These declarations allow the 'c' API interface to work
 * on WIN32 platforms
 */
LINKDLL void STDCALL ISO8583APISetTrace (const int iTrace);
LINKDLL void STDCALL ISO8583APISetDebug (const int iDebug);

LINKDLL int STDCALL ISO8583APIGetVersion (LPSTR strVersion, int *iVersionLen, int iMaxVersionLen);
LINKDLL int STDCALL ISO8583APIGetBuildInfo (LPSTR strInfo, int *iInfoLen, int iMaxInfoLen);

LINKDLL int STDCALL ISO8583MessageCreate (const char *strMsgType, const int iBitmapSize, int iStatusId);
LINKDLL int STDCALL ISO8583MessageSetField (int iMsgId, int iBitPosition, int iCharType, const unsigned char *strData, int iDataLen, int iStatusId);
LINKDLL int STDCALL ISO8583MessageGetField (int iMsgId, const int iBitPosition, int iCharType, LPSTR strData, int *iDataLen, int iMaxDataLen, int iStatusId);
LINKDLL void STDCALL ISO8583MessageReleaseFieldData (long lFieldData);

LINKDLL int STDCALL ISO8583MessageGetFieldLength (int iMsgId, int iBitPosition, int *iFieldDataLen, int iStatusId);
LINKDLL int STDCALL ISO8583MessageGetMessageType (int iMsgId, LPSTR strMsgType, int *iMsgTypeLen, int iMaxMsgTypeLen);
LINKDLL int STDCALL ISO8583MessageGetMapSize (int iMsgId);
LINKDLL int STDCALL ISO8583MessageGetResponseType (int iMsgId, LPSTR strResponseType, int *iResponseTypeLen, int iMaxResponseTypeLen);
LINKDLL int STDCALL ISO8583MessageGetRequestType (int iMsgId, LPSTR strRequestType, int *iRequestTypeLen, int iMaxRequestTypeLen);
LINKDLL int STDCALL ISO8583MessageGetClassName (int iMsgId, LPSTR strClassName, int *iClassNameLen, int iMaxClassNameLen);

LINKDLL int STDCALL ISO8583MessageSerialize (int iMsgId, LPSTR strData, int *iDataLen, int iMaxDataLen, int iStatusId);
LINKDLL void STDCALL ISO8583MessageReleaseSerializeData (long lSerializeData);
LINKDLL int STDCALL ISO8583MessageDeSerialize (int iMsgId, const unsigned char *strData, const int iDataLen, int iStatusId);
LINKDLL int STDCALL ISO8583MessageValidate (int iMsgId, int iStatusId);
LINKDLL void STDCALL ISO8583MessageDestroy (int iMsgId);

LINKDLL int STDCALL ISO8583ConnectionCreate (void);
LINKDLL void STDCALL ISO8583ConnectionDestroy (int iConnectionId);
LINKDLL int STDCALL ISO8583ConnectionOpen (int iConnectionId, const char *strDnsName, const char *strIpAddr, const char *strPort, const int iMode, int iStatusId);
LINKDLL void STDCALL ISO8583ConnectionClose (int iConnectionId);
LINKDLL int STDCALL ISO8583ConnectionProcessMessage (int iConnectionId, int iMsgId, int iTimeout, int iStatusId);
LINKDLL void STDCALL ISO8583ConnectionAddMsgMapping (int iConnectionId, char *strMsgType, char *strMsgClassName, int iStatusId);
LINKDLL int STDCALL ISO8583ConnectionAwaitRequest (int iConnectionId, int iStatusId);
LINKDLL int STDCALL ISO8583ConnectionSendResponse (int iConnectionId, int iResponseMsgId, int iStatusId);
LINKDLL int STDCALL ISO8583ConnectionIsConnected (int iConnectonId);

LINKDLL int STDCALL ISOStatusCreate (void);
LINKDLL int STDCALL ISOStatusGetStatus (int iStatusId);
LINKDLL int STDCALL ISOStatusGetResultCode (int iStatusId);
LINKDLL int STDCALL ISOStatusGetResultDesc (int iStatusId, LPSTR strDesc, int *iLen, int iMaxLen);
LINKDLL void STDCALL ISOStatusDestroy (int iStatusId);
#else
/*
 * These declarations allow the 'c' API interface to work
 * on NON WIN32 platforms (UNIX)
 */
void ISO8583APISetTrace (const int iTrace);
void ISO8583APISetDebug (const int iDebug);

int ISO8583APIGetVersion (LPSTR strVersion, int *iVersionLen, int iMaxVersionLen);
int ISO8583APIGetBuildInfo (LPSTR strInfo, int *iInfoLen, int iMaxInfoLen);

int ISO8583MessageCreate (const char *strMsgType, const int iBitmapSize, int iStatusId);
int ISO8583MessageSetField (int iMsgId, int iBitPosition, int iCharType, const unsigned char *strData, int iDataLen, int iStatusId);
int ISO8583MessageGetField (int iMsgId, const int iBitPosition, int iCharType, LPSTR strData, int *iDataLen, int iMaxDataLen, int iStatusId);
void ISO8583MessageReleaseFieldData (long lFieldData);

int ISO8583MessageGetFieldLength (int iMsgId, int iBitPosition, int *iFieldDataLen, int iStatusId);
int ISO8583MessageGetMessageType (int iMsgId, LPSTR strMsgType, int *iMsgTypeLen, int iMaxMsgTypeLen);
int ISO8583MessageGetMapSize (int iMsgId);
int ISO8583MessageGetResponseType (int iMsgId, LPSTR strResponseType, int *iResponseTypeLen, int iMaxResponseTypeLen);
int ISO8583MessageGetRequestType (int iMsgId, LPSTR strRequestType, int *iRequestTypeLen, int iMaxRequestTypeLen);
int ISO8583MessageGetClassName (int iMsgId, LPSTR strClassName, int *iClassNameLen, int iMaxClassNameLen);

int ISO8583MessageSerialize (int iMsgId, LPSTR strData, int *iDataLen, int iMaxDataLen, int iStatusId);
void ISO8583MessageReleaseSerializeData (long lSerializeData);
int ISO8583MessageDeSerialize (int iMsgId, const unsigned char *strData, const int iDataLen, int iStatusId);
int ISO8583MessageValidate (int iMsgId, int iStatusId);
void ISO8583MessageDestroy (int iMsgId);

int ISO8583ConnectionCreate (void);
void ISO8583ConnectionDestroy (int iConnectionId);
int ISO8583ConnectionOpen (int iConnectionId, const char *strDnsName, const char *strIpAddr, const char *strPort, const int iMode, int iStatusId);
void ISO8583ConnectionClose (int iConnectionId);
int ISO8583ConnectionProcessMessage (int iConnectionId, int iMsgId, int iTimeout, int iStatusId);
void ISO8583ConnectionAddMsgMapping (int iConnectionId, char *strMsgType, char *strMsgClassName, int iStatusId);
int ISO8583ConnectionAwaitRequest (int iConnectionId, int iStatusId);
int ISO8583ConnectionSendResponse (int iConnectionId, int iResponseMsgId, int iStatusId);
int ISO8583ConnectionIsConnected (int iConnectonId);

int ISOStatusCreate (void);
int ISOStatusGetStatus (int iStatusId);
int ISOStatusGetResultCode (int iStatusId);
int ISOStatusGetResultDesc (int iStatusId, LPSTR strDesc, int *iLen, int iMaxLen);
void ISOStatusDestroy (int iStatusId);
#endif

#ifdef __cplusplus
}
#endif

#endif

