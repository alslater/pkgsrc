/*********************************************************************
*
*   Module:
*       salib.cpp
*
*   Contents:
*       salib API functions
*       
*   Description
*
*       This source file contains the functions exposed as a dll
*       or shared object.
*       This file implements all the interface functions.
*		Note that they are extern "C" functions.
*       Also note that this interface is used to provide a single
*       library or DLL (Win32) that is used to provide
*       "C", "VB", "Java" interfaces
*
*   See Also:
*		saclib.h
*
*
*   Created:
*	   30 July 2001	Lonnie L. Filbrun
*
*   Modified:
*  06 May 2002 Lonnie L. Filbrun - renamed from SADLLAPI or SADLL32 to
*              saclib for consistency across platforms.
*
*
**********************************************************************/

#include <stdio.h>
#include <iostream>

#include "salib.h"

#include "MessageFactory.h"
#include "Enumerations.h"
#include "ISOStatus.h"
#include "ISO8583Message.h"
#include "ISO8583Connection.h"

using namespace std;

extern int gTrace;
extern int gDebug;

#ifndef _WIN32
#ifndef BOOL
#define BOOL int
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#endif
#endif

ISOStatus *gStatusTable[STATUS_MAX+1];
ISO8583Message *gMessageTable[MESSAGE_MAX+1];
ISO8583Connection *gConnectionTable[CONNECTION_MAX+1];

static int MessageOpen (const char *strClassName, int iBitmapSize, int iStatusId);
static void MessageClose (int iMessageId);
static BOOL MessageValidate (int iMessageId);

static int ConnectionOpen (void);
static void ConnectionClose (int iConnectionId);
static BOOL ConnectionValidate (int iConnectionId);

static int StatusOpen (void);
static void StatusClose (int iStatusId);
static BOOL StatusValidate (int iStatusId);

static int StatusOpen (void)
{
    int slot = 0;
    int rval = STATUS_ERROR;

    for (slot = 1; slot < STATUS_MAX+1; slot++)
    {
       if (gStatusTable[slot] == NULL)
       {
          gStatusTable[slot] = new ISOStatus();

          rval = slot;

          break;
       }
    }

    return rval;
}

static void StatusClose (int iStatusId)
{
    if ((iStatusId < 1)
     || (iStatusId > STATUS_MAX+1))
       return;

    if (gStatusTable[iStatusId] != NULL)
    {
       delete gStatusTable [iStatusId];
       gStatusTable[iStatusId] = NULL;
    }

    return;
}

static BOOL StatusValidate (int iStatusId)
{
    if ((iStatusId < 1)
     || (iStatusId > STATUS_MAX+1))
       return FALSE;

    if (gStatusTable[iStatusId] != NULL)
    {
       return TRUE;
    }

    return FALSE;
}

static int MessageOpen (const char *strClassName, int iBitmapSize, int iStatusId)
{
    int slot = 0;
    int rval = MESSAGE_ERROR;

    if ((rval = StatusValidate (iStatusId)) == FALSE)
       return rval;

    for (slot = 1; slot < MESSAGE_MAX+1; slot++)
    {
       if (gMessageTable[slot] == NULL)
       {
          gMessageTable[slot] = ISO8583MessageFactory ().createMessage (strClassName,
                                                                        iBitmapSize,
                                                                        *gStatusTable[iStatusId]);

          rval = slot;

          break;
       }
    }

    return rval;
}

static void MessageClose (int iMessageId)
{
    if ((iMessageId < 1)
     || (iMessageId > MESSAGE_MAX+1))
       return;

    if (gMessageTable[iMessageId] != NULL)
    {
       ISO8583MessageFactory ().deleteMessage (gMessageTable[iMessageId]);
       gMessageTable[iMessageId] = NULL;
    }

    return;
}

static BOOL MessageValidate (int iMessageId)
{
    if ((iMessageId < 1)
     || (iMessageId > MESSAGE_MAX+1))
       return FALSE;

    if (gMessageTable[iMessageId] != NULL)
    {
       return TRUE;
    }

    return FALSE;
}

static int ConnectionOpen (void)
{
    int slot = 0;
    int rval = CONNECTION_ERROR;

    for (slot = 1; slot < CONNECTION_MAX+1; slot++)
    {
       if (gConnectionTable[slot] == NULL)
       {
          gConnectionTable[slot] = new ISO8583Connection ();

          rval = slot;

          break;
       }
    }

    return rval;
}

static void ConnectionClose (int iConnectionId)
{
    if ((iConnectionId < 1)
     || (iConnectionId > CONNECTION_MAX+1))
       return;

    if (gConnectionTable[iConnectionId] != NULL)
    {
       delete gConnectionTable [iConnectionId];
       gConnectionTable[iConnectionId] = NULL;
    }

    return;
}

static BOOL ConnectionValidate (int iConnectionId)
{
    if ((iConnectionId < 1)
     || (iConnectionId > CONNECTION_MAX+1))
       return FALSE;

    if (gConnectionTable[iConnectionId] != NULL)
    {
       return TRUE;
    }

    return FALSE;
}

extern "C"
{
#ifdef _WIN32
	LINKDLL void STDCALL ISO8583APISetTrace
#else
    void ISO8583APISetTrace
#endif
	(const int iTrace)
	{
	   // this enables tracing in the API layer
	   ISO8583MessageFactory ().setTrace (iTrace);

	   // this enabled tracing in this layer (DLL)
	   gTrace = iTrace;

	   return;
	}
	
#ifdef _WIN32
	LINKDLL void STDCALL ISO8583APISetDebug
#else
	void ISO8583APISetDebug
#endif
	(const int iDebug)
	{
	   // this enables debugging in the API layer
	   ISO8583MessageFactory ().setDebug (iDebug);

	   // this enables debugging in this layer (DLL)
	   gDebug = iDebug;

	   return;
	}

#ifdef _WIN32
    LINKDLL int STDCALL ISO8583APIGetVersion
#else
    int ISO8583APIGetVersion
#endif
    (LPSTR strVersion, int *iVersionLen, int iMaxVersionLen)
    {
       int rval = 0;
       int tmpVersionLen = 0;
       char *tmpVersion = NULL;

       *iVersionLen = 0;

	   // this returns the version.
	   tmpVersion = ISO8583MessageFactory ().getApiVersion ();

       if (tmpVersion == NULL)
          return rval;

       tmpVersionLen = strlen (tmpVersion);

       if (iMaxVersionLen > tmpVersionLen)
       {
          memcpy (strVersion, tmpVersion, tmpVersionLen);

          *iVersionLen = tmpVersionLen;

          rval = TRUE;
       }
       else
       {
          rval = FALSE;
       }

       return rval;
    }

#ifdef _WIN32
    LINKDLL int STDCALL ISO8583APIGetBuildInfo
#else
    int ISO8583APIGetBuildInfo
#endif
    (LPSTR strInfo, int *iInfoLen, int iMaxInfoLen)
    {
       int rval = 0;
       int tmpInfoLen = 0;
       char *tmpInfo = NULL;

       *iInfoLen = 0;

	   // this returns the build date.
	   tmpInfo = ISO8583MessageFactory ().getApiBuildInfo ();

       if (tmpInfo == NULL)
          return rval;

       tmpInfoLen = strlen (tmpInfo);

       if (iMaxInfoLen > tmpInfoLen)
       {
          memcpy (strInfo, tmpInfo, tmpInfoLen);

          *iInfoLen = tmpInfoLen;

          rval = TRUE;
       }
       else
       {
          rval = FALSE;
       }

       return rval;
    }

    /*	Name :
	 *		ISO8583MessageCreate (char *, int, int) 
	 *
	 *	Arguments:
	 *		strMsgType		:	The type of message class to be instantiated.
	 *		iBitmapSize		:	The size of the bit map to be created for this message type
	 *		iStatusId    	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten. 
	 *
	 *	Return Type: 
	 *		int		:	Returns the pointer to the message object created
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the MessageFactory to create the specific message requested.
	 *		2. The pointer to the message object returned by the ClassFactory is returned as an integer to the JNI
	 *	
	 */	


#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageCreate
#else
	int ISO8583MessageCreate
#endif
	(const char *strMsgType, const int iBitmapSize, int iStatusId)
	{
        int rval = 0;
        int iMsgId = MESSAGE_ERROR;
       
	    if (gDebug)
		   cout << "Inside ISO8583MessageCreate..." << endl;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

        iMsgId = MessageOpen (strMsgType, iBitmapSize, iStatusId);

		if (gDebug)
		{
		   cout << "Leaving ISO8583MessageCreate - msgType: " << strMsgType << " bitmapSize: " << iBitmapSize << " returning: " << iMsgId << "." << endl;
	       cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
		}

		return iMsgId;
	}



	/*	Name :
	 *		ISO8583MessageSetField (int, int, int, unsigned char *, int, int) 
	 *
	 *	Arguments:
	 *		iMsgId			:	The pointer to the message object
	 *		iBitPosition	:	The bit position to be set
	 *		iCharType		:	The encoding format - ASCII/EBCDIC
	 *		strData			:	The data sent by the client to be set in the field
	 *		iDataLen		:	Length of the data sent
	 *		iStatusId		:	The pointer to the ISOStatus object.
	 *							ISOStatus parameter will be updated with the status of operation.  
	 *							Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		int	:	Returns the success or failure of the operation
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the setField() of the message type through the pointer.
	 *		2. The success or failure of the operation returned by the setField() of the message type
	 *		   is returned to VB as bool.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageSetField
#else
	int ISO8583MessageSetField
#endif
	(int iMsgId, int iBitPosition, int iCharType, const unsigned char *strData, const int iDataLen, int iStatusId)
	{
	    int rval = MESSAGE_ERROR;

		if (gDebug)
		   cout << "Inside ISO8583MessageSetField - BP: " << iBitPosition << endl;

        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

		rval = gMessageTable[iMsgId]->setField (iBitPosition, iCharType, strData, iDataLen, *gStatusTable[iStatusId]);

		if (gDebug)
		{
		   cout << "Leaving ISO8583MessageSetField - BP: " << iBitPosition << " returning: " << rval << " " << gStatusTable[iStatusId]->getStatus () << "." << endl;
	       cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
		}

		return rval;
	}


	/*	Name :
	 *		ISO8583MessageGetField (int, int, int, unsigned char *, int*, int, int) 
	 *
	 *	Arguments:
	 *		iMsgId			:	The pointer to the message object
	 *		iBitPosition	:	The bit position to be set
	 *		iCharType		:	The encoding format - ASCII/EBCDIC
     *      strData         :   the returned data
 	 *		iDataLen		:	Length of the data sent
     *      iMaxDataLen  	:   Max size of data to be written to data.
	 *		iStatusId		:	The pointer to the ISOStatus object.
	 *							ISOStatus parameter will be updated with the status of operation.  
	 *							Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		int		    :	
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getField() of the message type through the pointer.
	 *		2. The data returned by the getField() of the message type is returned to VB as char *.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageGetField
#else
	int ISO8583MessageGetField
#endif	
	(int iMsgId, int iBitPosition, int iCharType, LPSTR strData, int *iDataLen, int iMaxDataLen, int iStatusId)
	{
       int rval = 0;
	   unsigned char *tmpData = NULL;

       *iDataLen = 0;

	   if (gDebug)
	      cout << "Inside ISO8583MessageGetField - BP: " << iBitPosition << endl;

       if ((rval = MessageValidate (iMsgId)) == FALSE)
          return rval;

       if ((rval = StatusValidate (iStatusId)) == FALSE)
          return rval;

	   tmpData = gMessageTable[iMsgId]->getField (iBitPosition, iCharType, iDataLen, *gStatusTable[iStatusId]);

       if (tmpData == NULL)
          return MESSAGE_ERROR;

       if (iMaxDataLen > *iDataLen)
       {
          memset (strData, 0, iMaxDataLen);

          memcpy (strData, tmpData, *iDataLen);

          rval = 1;
       }
       else
       {
          rval = 0;
       }

       if (tmpData != NULL)
       {
          delete [] tmpData;
          tmpData = NULL;
       }

 	   if (gDebug)
	   {
	      cout << "Leaving ISO8583MessageGetField - BP: " << iBitPosition << " returning: " << gStatusTable[iStatusId]->getStatus () << "." << endl;
	      cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
	   }

	   return rval;
	}

#ifdef _WIN32
	LINKDLL void STDCALL ISO8583MessageReleaseFieldData
#else
	void ISO8583MessageReleaseFieldData
#endif	
	(long lFieldData)
	{
	   unsigned char *intFieldData = NULL;
	   
	   intFieldData = ((unsigned char *)lFieldData);

	   if (gDebug)
	 	  cout << "Inside ISO8583MessageReleaseFieldData" << endl;

	   if (intFieldData != NULL)
	   {
	      delete [] intFieldData;
		  intFieldData = NULL;
	   }

	   if (gDebug)
	   {
	      cout << "Leaving ISO8583MessageReleaseFieldData returning." << endl;
	   }

	   return;
	}

	/*	Name :
	 *		ISO8583MessageGetFieldLength (int, int, int *fieldDataLen, int) 
	 *
	 *	Arguments:
	 *		iMsgId			:	The pointer to the message object
	 *		iBitPosition	:	The bit position to be set
     *      iFieldDataLen	:   OUT - modified to reflect the length of the data in the specified field.
	 *		iStatusId		:	The pointer to the ISOStatus object.
	 *							ISOStatus parameter will be updated with the status of operation.  
	 *							Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		int		:	The length of data retrieved from the particular bit position
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getSize() of the particular field set for the message type through the pointer.
	 *		2. The data returned by the getSize() of the message type is returned to VB as int.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageGetFieldLength
#else
	int ISO8583MessageGetFieldLength
#endif	
	(int iMsgId, int iBitPosition, int *iFieldDataLen, int iStatusId)
	{
        int rval = MESSAGE_ERROR;
        int tmpDataLen = 0;
        unsigned char *tmpData = NULL;
		
        *iFieldDataLen = 0;

		if (gDebug)
		   cout << "Inside ISO8583MessageGetFieldLength - BP: " << iBitPosition << "." << endl;
	
        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

		tmpData = gMessageTable[iMsgId]->getField (iBitPosition, 1, &tmpDataLen, *gStatusTable[iStatusId]);

        if (tmpData != NULL)
        {
           *iFieldDataLen = tmpDataLen;

           rval = TRUE;
        }
        else
        {
           rval = FALSE;
        }

        if (tmpData != NULL)
        {
           delete [] tmpData;
           tmpData = NULL;
        }

		if (gDebug)
		   cout << "Leaving ISO8583MessageGetFieldLength - BP: " << iBitPosition << " returning: " << iFieldDataLen << "." << endl;

		return rval;
	}



	/*	Name :
	 *		ISO8583MessageGetMessageType (int, LPSTR, int *, int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
     *      int
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getMessageType() of the message type through the pointer.
	 *		2. The data returned by the getMessageType() of the message is returned to VB as char *.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageGetMessageType
#else
	int ISO8583MessageGetMessageType
#endif
	(int iMsgId, LPSTR strMsgType, int *iMsgTypeLen, int iMaxMsgTypeLen)
	{
        int rval = 0;
        int tmpMsgTypeLen = 0;
	    char *tmpMsgType = NULL;

        *iMsgTypeLen = 0;

		if (gDebug)
		   cout << "Inside ISO8583MessageGetMessageType..." << endl;

        if ((rval = MessageValidate (iMsgId)) < 0)
           return rval;

		tmpMsgType = gMessageTable[iMsgId]->getMessageType ();

        if (tmpMsgType == NULL)
           return MESSAGE_ERROR;

        tmpMsgTypeLen = strlen (tmpMsgType);

        if (iMaxMsgTypeLen > tmpMsgTypeLen)
        {
           memset (strMsgType, 0, iMaxMsgTypeLen);

           memcpy (strMsgType, tmpMsgType, tmpMsgTypeLen);

           *iMsgTypeLen = tmpMsgTypeLen;

           rval = TRUE;
        }
        else
        {
           rval = FALSE;
        }

        if (gDebug)
		{
		   if (strMsgType == NULL)
		      cout << "Leaving ISO8583MessageGetMessageType - returning strMsgType: >NULL<." << endl;
	       else
		      cout << "Leaving ISO8583MessageGetMessageType - returning strMsgType: >" << strMsgType << "<." << endl;
		}

		return rval;
	}



	/*	Name :
	 *		ISO8583MessageGetMapSize (int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
	 *		int		:	The size of the bit map of the message type.
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getMapSize() of the message type through the pointer.
	 *		2. The data returned by the getMapSize() of the message is returned to VB as int.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageGetMapSize
#else
	int ISO8583MessageGetMapSize
#endif
	(int iMsgId)
	{
		int mapSize = 0;
        int rval = MESSAGE_ERROR;

		if (gDebug)
	       cout << "Inside ISO8583MessageGetMapSize..." << endl;

        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

		mapSize = gMessageTable[iMsgId]->getMapSize ();
	    
		if (gDebug)
		   cout << "Leaving ISO8583MessageGetMapSize - returning mapSize: >" << mapSize << "<." << endl;

		return mapSize;
	}


	/*	Name :
	 *		ISO8583MessageValidate (int, int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		int	:	The status of the validation done on the message
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the validate() of the for the message through the pointer.
	 *		2. The status of the operations returned by the validate() of the message is returned to VB as bool.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageValidate
#else
	int ISO8583MessageValidate
#endif
	(int iMsgId, int iStatusId)
	{
	    int rval = MESSAGE_ERROR;

		if (gDebug)
		   cout << "Inside ISO8583MessageValidate..." << endl;

        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

		rval = gMessageTable[iMsgId]->validate (*gStatusTable[iStatusId]);
	    
		if (gDebug)
		{
		   cout << "Leaving ISO8583MessageValidate - returning: >" << rval << "<." << endl;
	       cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
		}

		return rval;
	}


	/*	Name :
	 *		ISO8583MessageGetResponseType (int, LPSTR, *int, int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type:
     *     int
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getResponseType() of the message type through the pointer.
	 *		2. The data returned by the getResponseType() of the message is returned to VB as char *.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageGetResponseType
#else
	int ISO8583MessageGetResponseType
#endif	
	(int iMsgId, LPSTR strResponseType, int *iResponseTypeLen, int iMaxResponseTypeLen)
	{
        int rval = MESSAGE_ERROR;
        int tmpResponseTypeLen = 0;
	    char *tmpResponseType = NULL;

        *iResponseTypeLen = 0;

		if (gDebug)
		   cout << "Inside ISO8583MessageGetResponseType..." << endl;

        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

		tmpResponseType = gMessageTable[iMsgId]->getResponseType ();

        if (tmpResponseType == NULL)
           return MESSAGE_ERROR;

        tmpResponseTypeLen = strlen (tmpResponseType);

        if (iMaxResponseTypeLen > tmpResponseTypeLen)
        {
           memset (strResponseType, 0, iMaxResponseTypeLen);

           memcpy (strResponseType, tmpResponseType, tmpResponseTypeLen);

           *iResponseTypeLen = tmpResponseTypeLen;

           rval = TRUE;
        }
        else
        {
           rval = FALSE;
        }

		if (gDebug)
		{
		   if (strResponseType == NULL)
		      cout << "Leaving ISO8583MessageGetResponseType - returning: >NULL<." << endl;
	       else
		      cout << "Leaving ISO8583MessageGetResponseType - returning: >" << strResponseType << "<." << endl;
		}

		return rval;
	}



	/*	Name :
	 *		ISO8583MessageGetRequestType (int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
     *      int
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getRequestType() of the message type through the pointer.
	 *		2. The data returned by the getResponseType() of the message is returned to VB as char *.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageGetRequestType
#else
	int ISO8583MessageGetRequestType
#endif
	(int iMsgId, LPSTR strRequestType, int *iRequestTypeLen, int iMaxRequestTypeLen)
	{
        int rval = MESSAGE_ERROR;
        int tmpRequestTypeLen = 0;
		char *tmpRequestType = NULL;

        *iRequestTypeLen = 0;

		if (gDebug)
		   cout << "Inside ISO8583MessageGetRequestType..." << endl;

        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

		tmpRequestType = gMessageTable[iMsgId]->getRequestType ();

        if (tmpRequestType == NULL)
           return MESSAGE_ERROR;

        tmpRequestTypeLen = strlen (tmpRequestType);

        if (iMaxRequestTypeLen > tmpRequestTypeLen)
        {
           memset (strRequestType, 0, iMaxRequestTypeLen);

           memcpy (strRequestType, tmpRequestType, tmpRequestTypeLen);

           *iRequestTypeLen = tmpRequestTypeLen;

           rval = TRUE;
        }
        else
        {
           rval = FALSE;
        }

		if (gDebug)
		{
		   if (strRequestType == NULL)
		      cout << "Leaving ISO8583MessageGetRequestType - returning: >NULL<." << endl;
	       else
		      cout << "Leaving ISO8583MessageGetRequestType - returning: >" << strRequestType << "<." << endl;
		}

		return rval;
	}


	/*	Name :
	 *		ISO8583MessageGetClassName (int, LPSTR, int *, int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
     *      int
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getClassName() of the message type through the pointer.
	 *		2. The data returned by getClassName() of the message is returned to VB as char *.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageGetClassName
#else
	int ISO8583MessageGetClassName
#endif	
	(int iMsgId, LPSTR strClassName, int *iClassNameLen, int iMaxClassNameLen)
	{
        int tmpClassNameLen = 0;
	    int rval = MESSAGE_ERROR;
		char *tmpClassName = NULL;
        
		if (gDebug)
		   cout << "Inside ISO8583MessageGetClassName..." << endl;

        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

		tmpClassName = gMessageTable[iMsgId]->getClassName ();
	    
        if (tmpClassName == NULL)
           return MESSAGE_ERROR;

        tmpClassNameLen = strlen (tmpClassName);

        if (iMaxClassNameLen > tmpClassNameLen)
        {
           memset (strClassName, 0, iMaxClassNameLen);

           memcpy (strClassName, tmpClassName, tmpClassNameLen);

           *iClassNameLen = tmpClassNameLen;

           rval = TRUE;
        }
        else
        {
           rval = FALSE;
        }

		if (gDebug)
		{
		   if (strClassName == NULL)
		      cout << "Leaving ISO8583MessageGetClassName - returning: >NULL<." << endl;
	       else
		      cout << "Leaving ISO8583MessageGetClassName - returning: >" << strClassName << "<." << endl;
		}

		return rval;
	}

	/*	Name :
	 *		ISO8583MessageSerialize (int, LPSTR, int *, int, int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
     *      int
	 *
	 *
	 *	Implementation Details:
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageSerialize
#else
	int ISO8583MessageSerialize
#endif	
	(int iMsgId, LPSTR strData, int *iDataLen, int iMaxDataLen, int iStatusId)
	{
        int rval = 0;
	    unsigned char *tmpData = NULL;

        *iDataLen = 0;

		if (gDebug)
		   cout << "Inside ISO8583MessageSerialize..." << endl;

        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

		tmpData = gMessageTable[iMsgId]->serialize (iDataLen, *gStatusTable[iStatusId]);

        if (tmpData == NULL)
           return MESSAGE_ERROR;

        if (iMaxDataLen > *iDataLen)
        {
           memset (strData, 0, iMaxDataLen);

           memcpy (strData, tmpData, *iDataLen);

           rval = TRUE;
        }
        else
        {
           rval = FALSE;
        }

	    if (tmpData != NULL)
		{
	       delete [] tmpData;
		   tmpData = NULL;
		}

		if (gDebug)
		{
		   if (strData == NULL)
		      cout << "Leaving ISO8583MessageSerialize - returning: >NULL<." << endl;
	       else
		      cout << "Leaving ISO8583MessageSerialize - returning: >" << strData << "<." << endl;
		}

		return rval;
	}


	/*	Name :
	 *		ISO8583MessageReleaseSerializeData (long) 
	 *
	 *	Arguments:
	 *		lSerializedData		:	The pointer to the data
	 *
	 *
	 *	Return Type: 
     *      void
	 *
	 *
	 *	Implementation Details:
	 *	
	 */	

#ifdef _WIN32
	LINKDLL void STDCALL ISO8583MessageReleaseSerializeData
#else
	void ISO8583MessageReleaseSerializeData
#endif	
	(long lSerializeData)
	{
	    unsigned char *intSerializeData = NULL;
	   
	    intSerializeData = ((unsigned char *)lSerializeData);

	    if (gDebug)
	 	   cout << "Inside ISO8583MessageReleaseSerializeData" << endl;

	    if (intSerializeData != NULL)
		{
	       delete [] intSerializeData;
		   intSerializeData = NULL;
		}

	    if (gDebug)
		{
	       cout << "Leaving ISO8583MessageReleaseSerializeData returning." << endl;
		}

	    return;
	}


	/*	Name :
	 *		ISO8583MessageDeSerialize (int, LPSTR, int, int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
     *      int
	 *
	 *
	 *	Implementation Details:
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583MessageDeSerialize
#else
	int ISO8583MessageDeSerialize
#endif	
	(int iMsgId, const unsigned char *strData, const int iDataLen, int iStatusId)
	{
	    int status = 0;
        int rval = MESSAGE_ERROR;

		if (gDebug)
		   cout << "Inside ISO8583MessageDeSerialize..." << endl;

        if ((rval = MessageValidate (iMsgId)) == FALSE)
           return rval;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

		status = gMessageTable[iMsgId]->deSerialize (strData, iDataLen, *gStatusTable[iStatusId]);
	  
		if (gDebug)
		{
		   cout << "Leaving ISO8583MessageDeSerialize - returning: >" << status << "<." << endl;
		}

		return status;
	}


	/*	Name :
	 *		ISO8583MessageDestroy (int) 
	 *
	 *	Arguments:
	 *		iMsgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
	 *		void		
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the destructor of the message type through the pointer.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL void STDCALL ISO8583MessageDestroy
#else
	void ISO8583MessageDestroy
#endif		
	(int iMsgId)
	{
		if (gDebug)
		   cout << "Inside ISO8583MessageDestroy..." << endl;
		
        if (MessageValidate (iMsgId) == FALSE)
           return;

        MessageClose (iMsgId);

		if (gDebug)
		   cout << "ISO8583Message destroyed..." << endl;

		return;
	}



	/*	Name :
	 *		ISO8583ConnectionCreate (void) 
	 *
	 *	Arguments:
     *      none
	 *
	 *
	 *	Return Type: 
	 *		int		:	The pointer to the Connection object is returned		
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the create method of the Connection class.
	 *		2. Returns the pointer to the connection object returned.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583ConnectionCreate
#else
	int ISO8583ConnectionCreate
#endif
	(void)
	{
        int iConnectionId = CONNECTION_ERROR;

		if (gDebug)
		   cout << "Inside ISO8583ConnectionCreate..." << endl;

        iConnectionId = ConnectionOpen ();

		if (gDebug)
		{
		   cout << "Leaving ISO8583ConnectionCreate - returning: >" << iConnectionId << "<." << endl;
		}

		return iConnectionId;
	}



	/*	Name :
	 *		ISO8583ConnectionDestroy (int) 
	 *
	 *	Arguments:
	 *		iConnectionId   :	The pointer to the connection object
	 *
	 *
	 *	Return Type: 
	 *		void				
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the destructor of Connection class.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL void STDCALL ISO8583ConnectionDestroy
#else
	void ISO8583ConnectionDestroy
#endif	
	(int iConnectionId)
	{
		if (gDebug)
		   cout << "Inside ISO8583ConnectionDestroy..." << endl;

        if (ConnectionValidate (iConnectionId) == FALSE)
           return;

        ConnectionClose (iConnectionId);
        
		if (gDebug)
		   cout << "ISO8583Connection destroyed..." << endl;
		
		return;
	}

	/*	Name :
	 *		ISO8583ConnectionOpen (int, char *, char *, char *, int, int) 
	 *
	 *	Arguments:
	 *		iConnectionId	:	The pointer to the connection object
	 *		strDnsName		:	The DNS Name of the server
	 *		strIpAddr		:	The IP address of the server
	 *		strPort		    :	The port number of the server
	 *		iMode		    :	The mode in which the connection is to be opened
	 *		iStatusId	    :	The pointer to the ISOStatus object.
	 *						    ISOStatus parameter will be updated with the status of operation.  
	 *						    Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		bool	:	The status - success/faliure - of the operation				
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the method to open a connection of Connection class.
	 *		2. Returns the success/failure of the operation as returned by the called function
	 *										   
	 */	


#ifdef _WIN32
	LINKDLL int STDCALL ISO8583ConnectionOpen
#else
	int ISO8583ConnectionOpen
#endif		
	(int iConnectionId, const char *strDnsName, const char *strIpAddr, const char *strPort, const int iMode, int iStatusId)
	{
		int rval = CONNECTION_ERROR;

		if (gDebug)
		   cout << "Inside ISO8583ConnectionOpen..." << endl;

        if ((rval = ConnectionValidate (iConnectionId)) == FALSE)
           return rval;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

        rval = gConnectionTable[iConnectionId]->open (strDnsName,
	                                                  strIpAddr,
	                                                  strPort,
	                                                  iMode,
	                                                  *gStatusTable[iStatusId]);

		if (gDebug)
		{
		   cout << "Leaving ISO8583ConnectionOpen - returning: >" << rval << "<." << endl;
	       cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
		}

		return rval;
	}



	/*	Name :
	 *		ISO8583ConnectionClose (int) 
	 *
	 *	Arguments:
	 *		iConnectionId		:	The pointer to the connection object
	 *
	 *
	 *	Return Type: 
	 *		void				
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to close the connection - of Connection class.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL void STDCALL ISO8583ConnectionClose
#else
	void ISO8583ConnectionClose
#endif			
	(int iConnectionId)
	{
		if (gDebug)
		   cout << "Inside ISO8583ConnectionClose..." << endl;

        if (ConnectionValidate (iConnectionId) == FALSE)
           return;

		gConnectionTable[iConnectionId]->close ();
	    
		if (gDebug)
		{
		   cout << "Leaving ISO8583ConnectionClose." << endl;
		}

		return;
	}



	/*	Name :
	 *		ISO8583ConnectionProcessMessage (int, int, int, int) 
	 *
	 *	Arguments:
	 *		iConnectionId	:	The pointer to the connection object
	 *		iRequestMsgId	:	The pointer to the message object to be processed
	 *		iTimeout		:	The time limit for timeout of teh connection
	 *		iStatusId       :	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		int		:	The pointer to the response message object
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to process the request message.
	 *		2. Returns the pointer to the deserialized response message object
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583ConnectionProcessMessage
#else
	int ISO8583ConnectionProcessMessage
#endif
	(int iConnectionId, int iRequestMsgId, int iTimeout, int iStatusId)
	{
        int slot = 0;
        int rval = CONNECTION_ERROR;
        ISO8583Message *responseMsgPtr = NULL;

		if (gDebug)
		   cout << "Inside ISO8583ConnectionProcessMessage..." << endl;

        if ((rval = ConnectionValidate (iConnectionId)) == FALSE)
           return rval;

        if ((rval = MessageValidate (iRequestMsgId)) == FALSE)
           return rval;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

		responseMsgPtr = gConnectionTable[iConnectionId]->processMessage (gMessageTable[iRequestMsgId],
		                                                                  iTimeout,
												                          *gStatusTable[iStatusId]);
	    
        if (responseMsgPtr != NULL)
        {
           for (slot = 1; slot < MESSAGE_MAX+1; slot++)
           {
              if (gMessageTable[slot] == NULL)
              {
                 gMessageTable[slot] = responseMsgPtr;

                 rval = slot;
                 break;
              }
           }
        }

		if (gDebug)
		{
		   cout << "Leaving ISO8583ConnectionProcessMessage - returning: >" << rval << "<." << endl;
	       cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
		}

		return rval;
	}

	/*	Name :
	 *		ISO8583ConnectionAddMsgMapping (int, char *, char *, int) 
	 *
	 *	Arguments:
	 *		iConnectionId		:	The pointer to the connection object
	 *		strMsgType          :	The ISO message type.
	 *		strMsgClassName     :	The API class to instanciate.
	 *      iStatusId           :           The status reference
	 *
	 *
	 *	Return Type: 
	 *		none	:
     *
	 *
	 *	Implementation Details:
	 *										   
	 */	
	
#ifdef _WIN32
    LINKDLL void STDCALL ISO8583ConnectionAddMsgMapping
#else
    void ISO8583ConnectionAddMsgMapping
#endif
	(int iConnectionId, char *strMsgType, char *strMsgClassName, int iStatusId)
	{
		if (gDebug)
		   cout << "Inside ISO8583ConnectionAddMsgMapping..." << endl;

        if ((ConnectionValidate (iConnectionId)) == FALSE)
           return;

        if ((StatusValidate (iStatusId)) == FALSE)
           return;

		gConnectionTable[iConnectionId]->addMsgMapping (strMsgType, strMsgClassName, *gStatusTable[iStatusId]);

		if (gDebug)
		{
		   cout << "Leaving ISO8583ConnectionAddMsgMapping - msgType: " << strMsgType << ", msgMap: " << strMsgClassName << "." << endl;
	       cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
		}

		return;
	}


    /*	Name :
	 *		ISO8583ConnectionAwaitRequest(int, int) 
	 *
	 *	Arguments:
	 *		iConnection		:	The pointer to the connection object
	 *		iStatusId	    :	The pointer to the ISOStatus object.
	 *						    ISOStatus parameter will be updated with the status of operation.  
	 *						    Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		int		:	The pointer to the request message object
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to wait for the request message.
	 *		2. Returns the pointer to the deserialized request message object
	 *	
	 */	

#ifdef _WIN32
    LINKDLL int STDCALL ISO8583ConnectionAwaitRequest
#else
    int ISO8583ConnectionAwaitRequest
#endif
    (int iConnectionId, int iStatusId)
	{
        int slot = 0;
        char strMsgType[64+1] = "";
        int rval = CONNECTION_ERROR;
		ISO8583Message *requestMsgPtr = NULL;
        
		if (gDebug)
		   cout << "Inside ISO8583ConnectionAwaitRequest..." << endl;

        if ((ConnectionValidate (iConnectionId)) == FALSE)
           return CONNECTION_ERROR;

        if ((StatusValidate (iStatusId)) == FALSE)
           return STATUS_ERROR;
        
		requestMsgPtr = gConnectionTable[iConnectionId]->awaitRequest (strMsgType, *gStatusTable[iStatusId]);

        if (requestMsgPtr != NULL)
        {
           for (slot = 1; slot < MESSAGE_MAX+1; slot++)
           {
              if (gMessageTable[slot] == NULL)
              {
                 gMessageTable[slot] = requestMsgPtr;

                 rval = slot;
                 break;
              }
           }
        }

		if (gDebug)
		{
		   cout << "Leaving ISO8583ConnectionAwaitRequest - returning type: " << strMsgType << ": >" << requestMsgPtr << "<." << endl;
	       cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
		}

		return rval;
	}


	/*	Name :
	 *		ISO8583ConnectionSendResponse(int, int, int) 
	 *
	 *	Arguments:
	 *		iConnectionId		:	The pointer to the connection object
	 *		iResponseMsgId		:	The pointer to the message object to be processed
	 *		iStatusId	        :	The pointer to the ISOStatus object.
	 *						        ISOStatus parameter will be updated with the status of operation.  
	 *						        Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		int		: returnes true or false.
     *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to process the request message.
	 *		2. Returns the pointer to the deserialized response message object
	 *	
	 */	

#ifdef _WIN32
    LINKDLL int STDCALL ISO8583ConnectionSendResponse
#else
    int ISO8583ConnectionSendResponse
#endif
	(int iConnectionId, int iResponseMsgId, int iStatusId)
	{
        BOOL status = false;
        int rval = CONNECTION_ERROR;

		if (gDebug)
		   cout << "Inside ISO8583ConnectionSendResponse..." << endl;

        if ((rval = ConnectionValidate (iConnectionId)) == FALSE)
           return rval;

        if ((rval = MessageValidate (iResponseMsgId)) == FALSE)
           return rval;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

		status = gConnectionTable[iConnectionId]->sendResponse (gMessageTable[iResponseMsgId], *gStatusTable[iStatusId]);
	
		if (gDebug)
		{
		   cout << "Leaving ISO8583ConnectionSendResponse - returning: >" << status << "<." << endl;
	       cout << "CODE: " << gStatusTable[iStatusId]->getResultCode () << " TEXT: >" << gStatusTable[iStatusId]->getResultDesc () << "<." << endl;
		}

		return status;
	}


	/*	Name :
	 *		ISO8583ConnectionIsConnected (int) 
	 *
	 *	Arguments:
	 *		iConnectionId		:	The pointer to the connection object
	 *
	 *
	 *	Return Type: 
	 *		int	:	Retruns the success/failure of teh operation - if the connection is alive/not				
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to check if the connection is still open.
	 *	
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISO8583ConnectionIsConnected
#else
	int ISO8583ConnectionIsConnected
#endif
	(int iConnectionId)
	{
		int rval = CONNECTION_ERROR;
                
		if (gDebug)
		   cout << "Inside ISO8583ConnectionIsConnected..." << endl;

        if ((rval = ConnectionValidate (iConnectionId)) == FALSE)
           return rval;

		rval = gConnectionTable[iConnectionId]->isConnected ();

		if (gDebug)
		{
		   cout << "Leaving ISO8583ConnectionIsConnected - returning: >" << rval << "<." << endl;
		}

		return rval;
	}



	/*	Name :
	 *		ISOStatusCreate (void)
	 *
	 *	Arguments:
	 *      void
	 *		
	 *
	 *	Return Type: 
	 *		int		:	returns the pointer to the ISOStatus object
	 *
	 *
	 *	Implementation Details:
	 *		
	 */

#ifdef _WIN32
	LINKDLL int STDCALL ISOStatusCreate
#else
	int ISOStatusCreate
#endif
	(void)
	{
        int iStatusId = STATUS_ERROR;

		if (gDebug)
		   cout << "Inside ISOStatusCreate..." << endl;

        iStatusId = StatusOpen ();

		if (gDebug)
		{
		   cout << "Leaving ISOStatusCreate - returning: >" << iStatusId << "<." << endl;
		}

		return iStatusId;
	}




	/*	Name :
	 *		ISOStatusGetStatus (int)
	 *
	 *	Arguments:
	 *		iStatusId   :   The pointer to the ISOStatus Object
	 *
	 *	Return Type: 
	 *		int	        :	The status indicating whether the method returned successfully or not
	 *
	 *
	 *	Implementation Details:
	 *		
	 */

#ifdef _WIN32
	LINKDLL int STDCALL ISOStatusGetStatus
#else
	int ISOStatusGetStatus
#endif
	(int iStatusId)
	{
        int rval = STATUS_ERROR;
		
		if (gDebug)
		   cout << "Inside ISOStatusGetStatus..." << endl;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

		rval = gStatusTable[iStatusId]->getStatus ();

		if (gDebug)
		{
		   cout << "Leaving ISOStatusGetStatus - returning: >" << rval << "<." << endl;
		}

		return rval;
	}




	/*	Name :
	 *		ISOStatusGetResultCode (int)
	 *
	 *	Arguments:
	 *		iStatusId   :   The pointer to the ISOStatus Object
	 *
	 *	Return Type: 
	 *		int		:	Returns the Result code stored in the ISOStatus object at that point of time.
	 *
	 *
	 *	Implementation Details:
	 *		
	 */

#ifdef _WIN32
	LINKDLL int STDCALL ISOStatusGetResultCode
#else
	int ISOStatusGetResultCode
#endif
	(int iStatusId)
	{
        int rval = STATUS_ERROR;

		if (gDebug)
		   cout << "Inside ISOStatusGetResultCode..." << endl;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;
        
		rval = gStatusTable[iStatusId]->getResultCode ();

		if (gDebug)
		{
		   cout << "Leaving ISOStatusGetResultCode - returning: >" << rval << "<." << endl;
		}

		return rval;
	}



    /*	Name :
	 *		ISOStatusGetResultDesc (int, LPSTR, int*, int)
	 *
	 *	Arguments:
	 *		iStatusId       :   The pointer to the ISOStatus Object
     *      LPSTR desc      :   Variable that receives description text.
     *      int iDataLen    :   data Len
     *      int iMaxLen     :   Max length of passed in storage.
	 *
	 *	Return Type: 
	 *		int		:       true if successful, false if failure
     *
     *  Gets the Result Desc stored in the ISOStatus object at that point of time.
	 *
	 *	Implementation Details:
	 *		
	 */	

#ifdef _WIN32
	LINKDLL int STDCALL ISOStatusGetResultDesc
#else
	int ISOStatusGetResultDesc
#endif
    (int iStatusId, LPSTR strDesc, int *iLen, int iMaxLen)
	{
        int rval = 0;
        int tmpLen = 0;
        char *resultDesc = NULL;

        *iLen = 0;

		if (gDebug)
		   cout << "Inside ISOStatusGetResultDesc..." << endl;

        if ((rval = StatusValidate (iStatusId)) == FALSE)
           return rval;

        resultDesc = gStatusTable[iStatusId]->getResultDesc ();

        if (resultDesc == NULL)
           return FALSE;

        tmpLen = strlen (resultDesc);

        if (iMaxLen > tmpLen)
        {
           memset (strDesc, 0, iMaxLen);

           memcpy (strDesc, resultDesc, iMaxLen);

           *iLen = tmpLen;

           rval = TRUE;
        }
        else
        {
           rval = FALSE;
        }

		if (gDebug)
		{
		   if (resultDesc == NULL)
		      cout << "Leaving ISOStatusGetResultDesc - returning: >NULL<." << endl;
	       else
		      cout << "Leaving ISOStatusGetResultDesc - returning: >" << resultDesc << "<." << endl;
		}

		return rval;
	}


	/*	Name :
	 *		ISOStatusDestroy (int)
	 *
	 *	Arguments:
	 *		iStatusId   :   The pointer to the ISOStatus Object
	 *
	 *	Return Type: 
	 *		
	 *
	 *	Implementation Details:
	 *		
	 */	

#ifdef _WIN32
	LINKDLL void STDCALL ISOStatusDestroy
#else
	void ISOStatusDestroy
#endif
    (int iStatusId)
	{
		if (gDebug)
		   cout << "Inside ISOStatusDestroy..." << endl;

        if (StatusValidate (iStatusId) == FALSE)
           return;

        StatusClose (iStatusId);
			
		if (gDebug)
		   cout << "ISOStatus destroyed..." << endl;

		return;
	}
};
