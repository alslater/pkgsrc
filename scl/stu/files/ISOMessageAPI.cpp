/*********************************************************************
*
*   Module:
*       ISOMessageAPI.cpp
*
*   Contents:
*       ISOMessageAPI - Java JNI to "C" functions
*       
*   Description
*
*       This source file contains the functions exposed to the Java client.
*       This file implements all the interface functions.
*		Note that they are extern "C" functions.
*		All parameters  to the JNI methods are input parameters.
*		All return values are returned across the JNI interface .
*
*   See Also:
*		ISOMessageAPI.h
*
*
*   Created:
*		2 July 2001	Shubha Kumar & Subbu G.
*
*   Modified:
*
*      14 July 2001 Lonnie L. Filbrun - fixed Java_ISOMessageAPI_ISOStatusGetResultCode and Java_ISOMessageAPI_ISOStatusGetResultDesc (values returned did not match declared types)
*      14 July 2001 Lonnie L. Filbrun - changed timeout from size_t to int.
*      18 July 2001 Lonnie L. Filbrun - modified to expose byte[] array setField/getField.
*      09 April 2002 Lonnie L. Filbrun - added severmode methods and fixed some bugs.
*
*
**********************************************************************/


#include <stdio.h>
#include <string.h>
#include <iostream>

#include "salib.h"
#include "ISOMessageAPI.h"

extern int gTrace;
extern int gDebug;

extern "C"
{
	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583SetDebug(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		debug		:	The debug value
	 *
	 *	Return Type: 
	 *		void		:	Returns void
	 *
	 *	Implementation Details:
	 *	
	 */


	JNIEXPORT void JNICALL Java_ISOMessageAPI_ISO8583APISetDebug
	(JNIEnv *jEnv, jclass jObj, jint debug)
	{
        ISO8583APISetDebug (debug);

		return;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583APISetTrace(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		trace		:	The trace value
	 *
	 *	Return Type: 
	 *		void		:	Returns void
	 *
	 *	Implementation Details:
	 *	
	 */


	JNIEXPORT void JNICALL Java_ISOMessageAPI_ISO8583APISetTrace
	(JNIEnv *jEnv, jclass jObj, jint trace)
	{
        ISO8583APISetTrace (trace);

		return;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageCreate(JNIEnv *, jclass, jstring, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgType		:	The type of message class to be instantiated.
	 *		mapSize		:	The size of the bit map to be created for this message type
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten. 
	 *
	 *	Return Type: 
	 *		jint		:	Returns the pointer to the message object created
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the ClassFactory to create the specific message requested.
	 *		2. The pointer to the message object returned by the ClassFactory is returned as an integer to the JNI
	 *	
	 */	

	
	JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISO8583MessageCreate
	(JNIEnv *jEnv, jclass jObj, jstring strMsgType, jint iBitmapSize, jint iStatusId)
	{
        jint iMessageId = 0;
		jboolean val = true;
		jboolean *iscopy = &val;
        char *strClassName = NULL;

		if (gDebug)
		   cout << "Inside JNIISO8583MessageCreate..." << endl;
		
        strClassName = (char *)jEnv->GetStringUTFChars (strMsgType, iscopy);

	    iMessageId = ISO8583MessageCreate (strClassName, iBitmapSize, iStatusId);

        jEnv->ReleaseStringUTFChars (strMsgType, strClassName);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

		   cout << "Leaving JNIISO8583MessageCreate - msgType: " << strMsgType << " bitmapSize: " << iBitmapSize << " messageId: " << iMessageId << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return iMessageId;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageSetField(JNIEnv *, jclass, jint, jint, jint, jstring, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *		bitPosition	:	The bit position to be set
	 *		charType	:	The encoding format - ASCII/EBCDIC
	 *		data		:	The data sent by the client to be set in the field
	 *		dataLen		:	Length of the data sent
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jboolean	:	Returns the success or failure of the operation
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the setField() of the message type through the pointer.
	 *		2. The success or failure of the operation returned by the setField() of the message type
	 *		   is retruned to the JNI as jboolean.
	 *	
	 */	

	
	JNIEXPORT jboolean JNICALL Java_ISOMessageAPI_ISO8583MessageSetField
	(JNIEnv *jEnv, jclass jObj, jint iMsgId, jint iBitPosition, jint iCharType, jstring strData, jint iDataLen, jint iStatusId)
	{
		jboolean val = true;
		jboolean *iscopy = &val;
		jboolean result = false;
        unsigned char *lStrData = NULL;

		if (gDebug)
		   cout << "Inside JNIISO8583MessageSetField... bit position: " << iBitPosition << endl;

        lStrData = (unsigned char *)jEnv->GetStringUTFChars (strData, iscopy);

        result = ISO8583MessageSetField (iMsgId, iBitPosition, iCharType, lStrData, iDataLen, iStatusId);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

		   cout << "Leaving JNIISO8583MessageSetField - BP: " << iBitPosition << " returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

        jEnv->ReleaseStringUTFChars (strData, (char *)lStrData);

		return result;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageSetFieldBinary(JNIEnv *, jclass, jint, jint, jint, jbyteArray, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *		bitPosition	:	The bit position to be set
	 *		charType	:	The encoding format - ASCII/EBCDIC
	 *		data		:	The BINARY data sent by the client to be set in the field
	 *		dataLen		:	Length of the data sent
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jboolean	:	Returns the success or failure of the operation
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the setField() of the message type through the pointer.
	 *		2. The success or failure of the operation returned by the setField() of the message type
	 *		   is retruned to the JNI as jboolean.
	 *	
	 */	

	
	JNIEXPORT jboolean JNICALL Java_ISOMessageAPI_ISO8583MessageSetFieldBinary
	(JNIEnv *jEnv, jclass jObj, jint iMsgId, jint iBitPosition, jint iCharType, jbyteArray aData, jint iDataLen, jint iStatusId)
	{
		jboolean val = true;
		jboolean result = false;
		jboolean *iscopy = &val;
		jsize inSize;
		jbyte *pBytesToConvert = NULL;

		if (gDebug)
		   cout << "Inside JNIISO8583MessageSetFieldBinary...bit position: " << iBitPosition << endl;

		// Get the byte array to convert
		pBytesToConvert = jEnv->GetByteArrayElements (aData, NULL);

		// Get the array length.
		inSize = jEnv->GetArrayLength (aData);

		// Invoke API setField.
        result = ISO8583MessageSetField (iMsgId, iBitPosition, iCharType, (unsigned char *)pBytesToConvert, iDataLen, iStatusId);

		// We are done.
		jEnv->ReleaseByteArrayElements (aData, pBytesToConvert, 0);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

           cout << "Leaving JNIISO8583MessageSetFieldBinary - BP: " << iBitPosition << " returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return result;
	}

	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageGetField(JNIEnv *, jclass, jint, jint, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *		bitPosition	:	The bit position to be set
	 *		charType	:	The encoding format - ASCII/EBCDIC
	 *		dataLen		:	Length of the data sent
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jstring		:	The data retrieved from the particular bit position
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getField() of the message type through the pointer.
	 *		2. The data returned by the getField() of the message type is retruned to the JNI as jstring.
	 *	
	 */	

	
	JNIEXPORT jstring JNICALL Java_ISOMessageAPI_ISO8583MessageGetField
	(JNIEnv *jEnv, jclass jObj, jint iMsgId, jint iBitPosition, jint iCharType, jint iDataLen, jint iStatusId)
	{
        int result = 0;
		jstring newJString;
        static int iTmpFieldDataLen = 0;
		unsigned char strFieldData[1024+1] = "";

		if (gDebug)
		   cout << "Inside JNIISO8583MessageGetField... bit position: " << iBitPosition << endl;

        ISO8583MessageGetField (iMsgId,
                                         iBitPosition,
                                         iCharType,
                                         (char *)strFieldData,
                                         &iDataLen,
                                         (int)1024,
                                         iStatusId);
        
        if (strFieldData != NULL)
        {
		   newJString = jEnv->NewStringUTF((const char *)strFieldData);
        }
        else
        {
		   newJString = jEnv->NewStringUTF((const char *)"");
        }

/*
 *	    *iDataLen = iTmpFieldDataLen;
 */
	    	    
		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

           cout << "Leaving JNIISO8583MessageGetField - BP: " << iBitPosition << " returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

        return newJString;
	}

	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageGetField2(JNIEnv *, jclass, jint, jint, jint, jstring, jint, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *		bitPosition	:	The bit position to be set
	 *		charType	:	The encoding format - ASCII/EBCDIC
	 *      data        :   Where to return the field data.
	 *		dataLen		:	Length of the field data.
	 *      maxDataLen  :   Max length of data to put in the field.
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jstring		:	The data retrieved from the particular bit position
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getField2() of the message type through the pointer.
	 *		2. The data returned by the getField() of the message type is retruned to the JNI as jstring.
	 *	
	 */	

	
	JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISO8583MessageGetField2
	(JNIEnv *jEnv, jclass jObj, jint iMsgId, jint iBitPosition, jint iCharType, jstring strData, jint iDataLen, jint iMaxDataLen, jint iStatusId)
	{
		int rval = 0;
        int result = 0;
        int iTmpDataLen = 0;
		unsigned char strTmpData[1024+1] = "";

		if (gDebug)
		   cout << "Inside JNIISO8583MessageGetField2... bit position: " << iBitPosition << endl;

        iDataLen = 0;

        result = ISO8583MessageGetField (iMsgId,
                                iBitPosition,
                                iCharType,
                                (char *)strTmpData,
                                &iTmpDataLen,
                                (int)1024,
                                iStatusId);

        if (strTmpData == NULL)
        {
           rval = 0;
        }
        else
        {
           if (iMaxDataLen > iTmpDataLen)
           {
              memset (strData, 0, iMaxDataLen);

              memcpy (strData, strTmpData, iTmpDataLen);

              iDataLen = iTmpDataLen;

              rval = 1;
           }
           else
           {
              rval = 0;
           }
        }
		
		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

           cout << "Leaving JNIISO8583MessageGetField2 - BP: " << iBitPosition << " returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return rval;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageGetFieldBinary(JNIEnv *, jclass, jint, jint, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *		bitPosition	:	The bit position to be set
	 *		charType	:	The encoding format - ASCII/EBCDIC
	 *		dataLen		:	Length of the data sent
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 	 jbyteArray	:	The BINARY data retrieved from the particular bit position
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getField() of the message type through the pointer.
	 *		2. The data returned by the getField() of the message type is retruned to the JNI as jstring.
	 *	
	 */	

	
	JNIEXPORT jbyteArray JNICALL Java_ISOMessageAPI_ISO8583MessageGetFieldBinary
	(JNIEnv *jEnv, jclass jObj, jint iMsgId, jint iBitPosition, jint iCharType, jint iDataLen, jint iStatusId)
	{
		jsize outSize;
        int result = 0;
	    jbyteArray jBytesConverted;
        int iTmpFieldDataLen = 0;
		unsigned char strTmpFieldData[1024+1] = "";

		if (gDebug)
		   cout << "Inside JNIISO8583MessageGetFieldBinary...bit position: " << iBitPosition << endl;

		// Get the data and the data length from the API.
        result = ISO8583MessageGetField (iMsgId,
                                iBitPosition,
                                iCharType,
                                (char *)strTmpFieldData,
                                &iTmpFieldDataLen,
                                (int)1024,
                                iStatusId);

		// Set the new arry length the same as the data length.
		outSize = iDataLen = iTmpFieldDataLen;

		// Get a new byteArray
        jBytesConverted = jEnv->NewByteArray (outSize);

		// Associate the returned data to the new byteArray
#ifdef _WIN32
	        jEnv->SetByteArrayRegion (jBytesConverted, 0, outSize, (signed char *)strTmpFieldData);
#else
	        jEnv->SetByteArrayRegion (jBytesConverted, 0, outSize, (char *)strTmpFieldData);
#endif

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

           cout << "Leaving JNIISO8583MessageGetFieldBinary - BP: " << iBitPosition << " returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		// return the new byteArray
		return jBytesConverted;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageGetFieldLength(JNIEnv *, jclass, jint, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *		bitPosition	:	The bit position to be set
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jint		:	The length of data retrieved from the particular bit position
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getSize() of the particular field set for the message type through the pointer.
	 *		2. The data returned by the getSize() of the message type is retruned to the JNI as jint.
	 *	
	 */	

	
	JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISO8583MessageGetFieldLength
	(JNIEnv *jEnv, jclass jObj, jint iMsgId, jint iBitPosition, jint iStatusId)
	{
        int result = 0;
        int iTmpFieldDataLen = 0;
        unsigned char strTmpFieldData[1024+1] = "";

		if (gDebug)
		   cout << "Inside JNIISO8583MessageGetFieldLength..." << endl;
		
        result = ISO8583MessageGetField (iMsgId,
                                         iBitPosition,
                                         ASCII,
                                         (char *)strTmpFieldData,
                                         &iTmpFieldDataLen,
                                         (int)1024,
                                         iStatusId);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

           cout << "Leaving JNIISO8583MessageGetFieldLength - BP: " << iBitPosition << " returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return iTmpFieldDataLen;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageGetMessageType(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
	 *		jstring		:	The name of the message as stored by the class.
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getMessageType() of the message type through the pointer.
	 *		2. The data returned by the getMessageType() of the message is retruned to the JNI as jstring.
	 *	
	 */	

	
	JNIEXPORT jstring JNICALL Java_ISOMessageAPI_ISO8583MessageGetMessageType
	(JNIEnv *jEnv, jclass jObj, jint iMsgId)
	{
		jstring newJString;
        int iTmpMsgTypeLen = 0;
		char strTmpMsgType[255+1] = "";

		if (gDebug)
		   cout << "Inside JNIISO8583MessageGetMessageType..." << endl;
		
        ISO8583MessageGetMessageType (iMsgId, strTmpMsgType, &iTmpMsgTypeLen, 255);
        
		newJString = jEnv->NewStringUTF(strTmpMsgType);

		if (gDebug)
		{
		   cout << "Leaving JNIISO8583MessageGetMessageType - returning: " << strTmpMsgType << "." << endl;
		}

		return newJString;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageGetMapSize(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
	 *		jint		:	The size of the bit map of the message type.
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getMapSize() of the message type through the pointer.
	 *		2. The data returned by the getMapSize() of the message is retruned to the JNI as jint.
	 *	
	 */	

	
	JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISO8583MessageGetMapSize
	(JNIEnv *jEnv, jclass jObj, jint iMsgId)
	{
		int iBitmapSize = 0;

		if (gDebug)
		   cout << "Inside JNIISO8583MessageGetMapSize..." << endl;

        iBitmapSize = ISO8583MessageGetMapSize (iMsgId);

		if (gDebug)
		{
		   cout << "Leaving JNIISO8583MessageGetMapSize - returning: " << iBitmapSize << "." << endl;
		}

		return iBitmapSize;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageValidate(JNIEnv *, jclass, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jboolean	:	The status of the validation done on the message
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the validate() of the for the message through the pointer.
	 *		2. The status of the operations returned by the validate() of the message is retruned to the JNI as jboolean.
	 *	
	 */	

	
	JNIEXPORT jboolean JNICALL Java_ISOMessageAPI_ISO8583MessageValidate
	(JNIEnv *jEnv, jclass jObj, jint iMsgId, jint iStatusId)
	{
		jboolean result;

		if (gDebug)
		   cout << "Inside JNIISO8583MessageValidate..." << endl;

        result = ISO8583MessageValidate (iMsgId, iStatusId);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

           cout << "Leaving JNIISO8583MessageValidate - returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return result;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageGetResponseType(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *
	 *
	 *	Return Type: 
	 *		jstring		:	The response message type of this request message type.
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the getResponseType() of the message type through the pointer.
	 *		2. The data returned by the getResponseType() of the message is retruned to the JNI as jint.
	 *	
	 */	

	
	JNIEXPORT jstring JNICALL Java_ISOMessageAPI_ISO8583MessageGetResponseType
	(JNIEnv *jEnv, jclass jObj, jint iMsgId)
	{
        int result = 0;
		jstring newJString;
        int iMsgTypeLen = 0;
		char strMsgType[255+1] = "";

		if (gDebug)
		   cout << "Inside JNIISO8583MessageGetResponseType..." << endl;
				
        result = ISO8583MessageGetResponseType (iMsgId, strMsgType, &iMsgTypeLen, 255);

		newJString = jEnv->NewStringUTF(strMsgType);

		if (gDebug)
		{
		   cout << "Leaving JNIISO8583MessageGetResponseType - returning: " << strMsgType << "." << endl;
		}

		return newJString;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageSerialize(JNIEnv *, jclass, jint, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *      dataLen     :   The pointer to the dataLenth
	 *      ISOStatus   :   The pointer to the ISOStatus reference
	 *
	 *
	 *	Return Type: 
	 *		jbyteArray	:	The serialized representation of the message.
	 *
	 *
	 *	Implementation Details:
	 *	
	 */	


	JNIEXPORT jbyteArray JNICALL Java_ISOMessageAPI_ISO8583MessageSerialize
    (JNIEnv *jEnv, jclass jObj, jint iMsgId, jint iDataLen, jint iStatusId)
	{
		jsize outSize;
        int result = 0;
	    jbyteArray jBytesConverted;
        int iMsgDataLen = 0;
		unsigned char aMsgData[16384+1] = "";

		if (gDebug)
		   cout << "Inside JNIISO8583MessageSerialize..." << endl;

        result = ISO8583MessageSerialize (iMsgId, (char *)aMsgData, &iMsgDataLen, 16384, iStatusId);

		// Set the new arry length the same as the data length.
		outSize = iMsgDataLen;

		// Get a new byteArray
        jBytesConverted = jEnv->NewByteArray (outSize);

		// Associate the returned data to the new byteArray
#ifdef _WIN32
        jEnv->SetByteArrayRegion (jBytesConverted, 0, outSize, (signed char *)aMsgData);
#else
	    jEnv->SetByteArrayRegion (jBytesConverted, 0, outSize, (char *)aMsgData);
#endif

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

           cout << "Leaving JNIISO8583MessageSerialize - returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		// return the new byteArray
		return jBytesConverted;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageDeSerialize(JNIEnv *, jclass, jint, jByteArray, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
	 *      data        :   The pointer to the data
	 *      dataLen     :   The pointer to the dataLenth
	 *      ISOStatus   :   The pointer to the ISOStatus reference
	 *
	 *
	 *	Return Type: 
	 *		jbyteArray	:	The serialized representation of the message.
	 *
	 *
	 *	Implementation Details:
	 *	
	 */
	

	JNIEXPORT jboolean JNICALL Java_ISOMessageAPI_ISO8583MessageDeSerialize
	(JNIEnv *jEnv, jclass jObj, jint iMsgId, jbyteArray aData, jint iDataLen, jint iStatusId)
	{
	    jsize inSize;
	    jboolean result = false;
        int iTmpDataLen = 0;
		jbyte *pBytesToConvert = NULL;

		if (gDebug)
		   cout << "Inside JNIISO8583MessageDeSerialize..." << endl;

		// Get the byte array to convert
		pBytesToConvert = jEnv->GetByteArrayElements (aData, NULL);

		// Get the array length.
		inSize = jEnv->GetArrayLength (aData);

		// Invoke API
        result = ISO8583MessageDeSerialize (iMsgId,
                                            (unsigned char *)pBytesToConvert,
                                            iTmpDataLen,
                                            iStatusId);

        iDataLen = iTmpDataLen;

		// We are done.
		jEnv->ReleaseByteArrayElements (aData, pBytesToConvert, 0);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

           cout << "Leaving JNIISO8583MessageDeSerialize - returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return result;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583MessageDestroy(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		msgId		:	The pointer to the message object
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

	
	JNIEXPORT void JNICALL Java_ISOMessageAPI_ISO8583MessageDestroy
	(JNIEnv *jEnv, jclass jObj, jint iMsgId)
	{
		if (gDebug)
		   cout << "Inside JNIISO8583MessageDestroy..." << endl;
		
        ISO8583MessageDestroy (iMsgId);

		if (gDebug)
		{
		   cout << "Leaving JNIISO8583MessageDestroy." << endl;
		}
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionCreate(JNIEnv *, jclass) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *
	 *
	 *	Return Type: 
	 *		jint		:	The pointer to the Connection object is returned		
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the create method of the Connection class.
	 *		2. Returns the pointer to the connection object returned.
	 *	
	 */	

	
	JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISO8583ConnectionCreate
	(JNIEnv *jEnv, jclass jObj)
	{
        int iConnectionId = 0;

		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionCreate..." << endl;

        iConnectionId = ISO8583ConnectionCreate ();

		if (gDebug)
		{
           cout << "Leaving JNIISO8583ConnectionCreate - connectionId: " << iConnectionId << "." << endl;
		}

		return iConnectionId;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionDestroy(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		connId		:	The pointer to the connection object
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

	
	JNIEXPORT void JNICALL Java_ISOMessageAPI_ISO8583ConnectionDestroy
	(JNIEnv *jEnv, jclass jObj, jint iConnectionId)
	{
		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionDestroy..." << endl;

        ISO8583ConnectionDestroy (iConnectionId);

		if (gDebug)
		{
		   cout << "Leaving JNIISO8583ConnectionDestroy." << endl;
		}

        return;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionOpen(JNIEnv *, jclass, jint, jstring, jstring, jstring, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		connId		:	The pointer to the connection object
	 *		dnsName		:	The DNS Name of the server
	 *		ipAddr		:	The IP address of the server
	 *		port		:	The port number of the server
	 *		mode		:	The mode in which the connection is to be opened
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jboolean	:	The status - success/faliure - of the operation				
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the method to open a connection of Connection class.
	 *		2. Returns the success/failure of the operation as returned by the called function
	 *										   
	 */	

	
	JNIEXPORT jboolean JNICALL Java_ISOMessageAPI_ISO8583ConnectionOpen
	(JNIEnv *jEnv, jclass jObj, jint iConnectionId, jstring strDnsName, jstring strIpAddr, jstring strPort,	jint iMode, jint iStatusId)
	{
		jboolean val = true;
		jboolean *iscopy = &val;
	    jboolean result = false;
        char *lStrDnsName = NULL;
        char *lStrIpAddr = NULL;
        char *lStrPort = NULL;

		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionOpen..." << endl;
	
        lStrDnsName = (char *)jEnv->GetStringUTFChars (strDnsName, iscopy);
        lStrIpAddr = (char *)jEnv->GetStringUTFChars (strIpAddr, iscopy);
        lStrPort = (char *)jEnv->GetStringUTFChars (strPort, iscopy);

        result = ISO8583ConnectionOpen (iConnectionId, lStrDnsName, lStrIpAddr, lStrPort, iMode, iStatusId);

        jEnv->ReleaseStringUTFChars (strDnsName, lStrDnsName);
        jEnv->ReleaseStringUTFChars (strIpAddr, lStrIpAddr);
        jEnv->ReleaseStringUTFChars (strPort, lStrPort);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

		   cout << "Leaving JNIISO8583ConnectionOpen - returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return result;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionClose(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		connId		:	The pointer to the connection object
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

	
	JNIEXPORT void JNICALL Java_ISOMessageAPI_ISO8583ConnectionClose
	(JNIEnv *jEnv, jclass jObj, jint iConnectionId)
	{
		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionClose..." << endl;

        ISO8583ConnectionClose (iConnectionId);

		if (gDebug)
		   cout << "Leaving JNIISO8583ConnectionClose." << endl;

        return;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionProcessMessage(JNIEnv *, jclass, jint, jint, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		connId		:	The pointer to the connection object
	 *		msgId		:	The pointer to the message object to be processed
	 *		timeout		:	The time limit for timeout of teh connection
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jint		:	The pointer to the response message object
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to process the request message.
	 *		2. Returns the pointer to the deserialized response message object
	 *	
	 */	

	
	JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISO8583ConnectionProcessMessage
	(JNIEnv *jEnv, jclass jObj, jint iConnectionId, jint iRequestMsgId, jint iTimeout, jint iStatusId)
	{
        int iResponseMsgId = 0;

		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionProcessMessage..." << endl;

        iResponseMsgId = ISO8583ConnectionProcessMessage (iConnectionId,
                                                          iRequestMsgId,
                                                          iTimeout,
                                                          iStatusId);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

		   cout << "Leaving JNIISO8583ConnectionProcessMessage - responseMsgId: " << iResponseMsgId << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return iResponseMsgId;
	}


    /*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionAddMsgMapping (JNIEnv *, jclass, jint, jstring, jstring, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
     *      connId      :   The connection reference.
     *      strMsgType  :   The ISO message type.
     *      strMsgClassName :   The class name to instanciate.
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		void		:	returns nothing.
     *
	 *
	 *	Implementation Details:
	 *	
	 */	

    JNIEXPORT void JNICALL Java_ISOMessageAPI_ISO8583ConnectionAddMsgMapping
	(JNIEnv *jEnv, jclass jObj, jint iConnectionId, jstring strMsgType, jstring strMsgClassName, jint iStatusId)
	{
		jboolean val = true;
		jboolean *iscopy = &val;
        char *lStrMsgType = NULL;
        char *lStrMsgClassName = NULL;

		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionAddMsgMap..." << endl;

        lStrMsgType = (char *)jEnv->GetStringUTFChars (strMsgType, iscopy);
        lStrMsgClassName = (char *)jEnv->GetStringUTFChars (strMsgClassName, iscopy);

        ISO8583ConnectionAddMsgMapping (iConnectionId, lStrMsgType, lStrMsgClassName, iStatusId);

        jEnv->ReleaseStringUTFChars (strMsgType, lStrMsgType);
        jEnv->ReleaseStringUTFChars (strMsgClassName, lStrMsgClassName);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

		   cout << "Leaving JNIISO8583ConnectionAddMsgMap - added msgType: " << strMsgType << " msgMap: " << strMsgClassName << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionAwaitRequest(JNIEnv *, jclass, jint, jint, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		connId		:	The pointer to the connection object
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jint		:	The pointer to the request message object
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to wait for the request message.
	 *		2. Returns the pointer to the deserialized request message object
	 *	
	 */	


    JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISO8583ConnectionAwaitRequest
	(JNIEnv *jEnv, jclass jObj, jint iConnectionId, jint iStatusId)
	{
        int iRequestMsgId = 0;
        char strMsgType[64+1] = "";

		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionAwaitRequest..." << endl;

        iRequestMsgId = ISO8583ConnectionAwaitRequest (iConnectionId, iStatusId);

		if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

		   cout << "Leaving JNIISO8583ConnectionAwaitRequest - requestMsgId: " << iRequestMsgId << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return iRequestMsgId;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionSendResponse(JNIEnv *, jclass, jint, jint, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		connId		:	The pointer to the connection object
	 *		msgId		:	The pointer to the message object to be processed
	 *		ISOStatus	:	The pointer to the ISOStatus object.
	 *						ISOStatus parameter will be updated with the status of operation.  
	 *						Previous data will be overwritten.
	 *
	 *
	 *	Return Type: 
	 *		jboolean		: returnes true or false.
     *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to process the request message.
	 *		2. Returns the pointer to the deserialized response message object
	 *	
	 */	

    JNIEXPORT jboolean JNICALL Java_ISOMessageAPI_ISO8583ConnectionSendResponse
	(JNIEnv *jEnv, jclass jObj, jint iConnectionId, jint iResponseMsgId, jint iStatusId)
	{
        int result = 0;

		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionSendResponse..." << endl;

        result = ISO8583ConnectionSendResponse (iConnectionId,
                                                iResponseMsgId,
                                                iStatusId);

        if (gDebug)
		{
           int iDescLen = 0;
           char strDesc[255+1] = "";
           
           ISOStatusGetResultDesc (iStatusId, strDesc, &iDescLen, 255);

		   cout << "Leaving JNIISO8583ConnectionSendResponse - returning: " << result << "." << endl;
           cout << "CODE: " << ISOStatusGetResultCode (iStatusId) << " TEXT: >" << strDesc << "<." << endl;
		}

		return result;
	}


	/*	Name :
	 *		Java_ISOMessageAPI_ISO8583ConnectionIsConnected(JNIEnv *, jclass, jint) 
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		connId		:	The pointer to the connection object
	 *
	 *
	 *	Return Type: 
	 *		jboolean	:	Retruns the success/failure of teh operation - if the connection is alive/not				
	 *
	 *
	 *	Implementation Details:
	 *		1. Calls the function to check if the connection is still open.
	 *	
	 */	

	
	JNIEXPORT jboolean JNICALL Java_ISOMessageAPI_ISO8583ConnectionIsConnected
	(JNIEnv *jEnv, jclass jObj, jint iConnectionId)
	{
		jboolean isConnected = false;

		if (gDebug)
		   cout << "Inside JNIISO8583ConnectionIsConnected..." << endl;

        isConnected = ISO8583ConnectionIsConnected (iConnectionId);

		if (gDebug)
		   cout << "Leaving JNIISO8583ConnectionIsConnected - isConnected: " << isConnected << "." << endl;

		return isConnected;
	}



	/*	Name :
	 *		Java_ISOMessageAPI_ISOStatusCreate(JNIEnv *, jclass)
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		
	 *
	 *	Return Type: 
	 *		jint		:	returns the pointer to the ISOStatus object
	 *
	 *
	 *	Implementation Details:
	 *		
	 */

	JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISOStatusCreate
	(JNIEnv *jEnv, jclass jObj)
	{
        int iStatusId = 0;

		if (gDebug)
		   cout << "Inside JNIISOStatusCreate..." << endl;
				
        iStatusId = ISOStatusCreate ();

		if (gDebug)
		   cout << "Leaving JNIISOStatusCreate - statusId: " << iStatusId << "." << endl;

		return iStatusId;
	}




	/*	Name :
	 *		Java_ISOMessageAPI_ISOStatusGetStatus(JNIEnv *, jclass, jint)
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		ISOStatus   :   The pointer to the ISOStatus Object
	 *
	 *	Return Type: 
	 *		jboolean	:	The status indicating whether the method returned successfully or not
	 *
	 *
	 *	Implementation Details:
	 *		
	 */
	
	JNIEXPORT jboolean JNICALL Java_ISOMessageAPI_ISOStatusGetStatus
	(JNIEnv *jEnv, jclass jObj, jint iStatusId)
	{
		int result = 0;

		if (gDebug)
		   cout << "Inside JNIISOStatusGetStatus..." << endl;

        result = ISOStatusGetStatus (iStatusId);

		if (gDebug)
		   cout << "Leaving JNIISOStatusGetStatus." << endl;

		return result;
	}




	/*	Name :
	 *		Java_ISOMessageAPI_ISOStatusGetResultCode(JNIEnv *jEnv, jclass jObj, jint resultCode)
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		ISOStatus   :   The pointer to the ISOStatus Object
	 *
	 *	Return Type: 
	 *		jint		:	Returns the Result code stored in the ISOStatus object at that point of time.
	 *
	 *
	 *	Implementation Details:
	 *		
	 */
	
	JNIEXPORT jint JNICALL Java_ISOMessageAPI_ISOStatusGetResultCode
	(JNIEnv *jEnv, jclass jObj, jint iStatusId)
	{
		jint resultCode = 0;

		if (gDebug)
		   cout << "Inside JNIISOStatusGetResultCode..." << endl;
		
        resultCode = ISOStatusGetResultCode (iStatusId);

		if (gDebug)
		   cout << "Leaving JNIISOStatusGetResultCode." << endl;

		return resultCode;
	}




	/*	Name :
	 *		Java_ISOMessageAPI_ISOStatusGetResultDesc(JNIEnv *jEnv, jclass jObj, jint ISOStatus)
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		ISOStatus   :   The pointer to the ISOStatus Object
	 *
	 *	Return Type: 
	 *		jstirng		:	Returns the Result Desc stored in the ISOStatus object at that point of time.
	 *
	 *
	 *	Implementation Details:
	 *		
	 */	

	JNIEXPORT jstring JNICALL Java_ISOMessageAPI_ISOStatusGetResultDesc
    (JNIEnv *jEnv, jclass jObj, jint iStatusId)
	{
		jstring newJString;
        int iTmpFieldDataLen = 0;
        char strTmpFieldData[255+1] = "";

		if (gDebug)
		   cout << "Inside JNIISOStatusGetResultDesc..." << endl;

        ISOStatusGetResultDesc (iStatusId, strTmpFieldData, &iTmpFieldDataLen, 255);

		newJString = jEnv->NewStringUTF (strTmpFieldData);

		if (gDebug)
		   cout << "Leaving JNIISOStatusGetResultDesc." << endl;

		return newJString;
	}




	/*	Name :
	 *		Java_ISOMessageAPI_ISOStatusDestroy(JNIEnv *jEnv, jclass jObj, jint ISOStatus)
	 *
	 *	Arguments:
	 *		*jEnv		:	Pointer to the JNI environment
	 *		jObj		:	The reference to the object where the method is defined
	 *		ISOStatus   :   The pointer to the ISOStatus Object
	 *
	 *	Return Type: 
	 *		
	 *
	 *	Implementation Details:
	 *		
	 */	

	JNIEXPORT void JNICALL Java_ISOMessageAPI_ISOStatusDestroy
    (JNIEnv *jEnv, jclass jObj, jint iStatusId)
	{
		if (gDebug)
		   cout << "Inside JNIISOStatusDestroy..." << endl;

        ISOStatusDestroy (iStatusId);
		
		if (gDebug)
		   cout << "Leaving JNIISOStatusDestroy." << endl;

        return;
	}
};
