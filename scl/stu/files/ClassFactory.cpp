/**************************************************************************
 * File Name :        ClassFactory.cpp
 * 
 * Contents:		  Function createMessage 
 *
 * Description :	  This file contains the implementation of the function createMessage() of the  
 *					  ClassFactory class which is used to instantiate the appropriate message objects 
 *					  as needed by the client application
 *
 * Author :           Arun G
 *
 * Date Created :     05/21/2001
 *
 * Modified :
 * 06/22/2001 Lonnie L. Filbrun adding ISORequest and ISOResponse classes for testing.
 * 06/26/2001 Sunil K Natraj Checking if Message Type argument is NULL and adding appropriate status message 
 **************************************************************************
 */
#include "ClassFactory.h"

//Standard includes
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "linklist.h"
#include "ISO8583Implementation.h"

#include "Enumerations.h"

#include "ISO1100.h"
#include "ISO1100SV.h"

#include "ISO1110.h"

#include "ISO1220.h"
#include "ISO1220SV.h"

#include "ISO1230.h"

#include "ISO1420.h"
#include "ISO1420SV.h"

#include "ISO1430.h"

#include "ISO1804.h"

#include "ISO1814.h"

#include "ISORequest.h"
#include "ISOResponse.h"

#include "DefaultManager.h"

using namespace std;

#ifdef _DEBUG
      char gConfigInfo[] = "debug";
#else
      char gConfigInfo[] = "release";
#endif

static char gVersionInfo[] = "3.0";
static char gBuildInfo[] = "2/15/2002";

int gDebug = 0;
int gTrace = 0;
int gPackedBCD = 0;

static char *arrMessageString[] = 
{
	"ISO1100",
	"ISO1100SV",
	"ISO1110",
	"ISO1220",
	"ISO1220SV",
	"ISO1230",
	"ISO1420",
	"ISO1420SV",
	"ISO1430",
	"ISO1804",
	"ISO1814",
	"ISORequest",
	"ISOResponse",
	NULL	
};

static DefaultManager *gDefaultManager = NULL;

//Default Constructor
ClassFactory::ClassFactory()
{
	if (!m_initialized)
    {
	   Init ();
    }
    
	return;
}

//Destructor
ClassFactory::~ClassFactory()
{ 
	if (m_initialized)
	   UnInit ();

	return;
}

void ClassFactory::Init ()
{
	m_initialized = 1;

	if (gDefaultManager == NULL)
	{
	   gDefaultManager = new DefaultManager (true, ".\\db");
	}

	return;
}

void ClassFactory::UnInit (void)
{
	m_initialized = 0;

	if (gDefaultManager != NULL)
	{
	   delete gDefaultManager;
	   gDefaultManager = NULL;
	}

	return;
}

void ClassFactory::setTrace (int trace)
{
	gTrace = trace;

	return;
}

void ClassFactory::setDebug (int debug)
{
	gDebug = debug;

	return;
}

void ClassFactory::setPackedBCD(int packedBCD)
{
	gPackedBCD = packedBCD;
}

char *ClassFactory::getApiVersion (void)
{
    return gVersionInfo;
}

char *ClassFactory::getApiBuildInfo (void)
{
    return gBuildInfo;
}

/******************************************************************************************
 *
 * METHOD NAME:         createMessage
 *
 * ARGUMENTS:           int MessageType - Specifies the type of object to be created 
 *						int mapSize - Indicates the number of fields in the ISO8583 message 
 *						ISOStatus& statusRef - Holds the status of operation
 *                                   
 * RETURN VALUE:        ISO8583Message* - An active pointer reference to the newly instantiated class 
 *										  (NULL in case of exceptions.)
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This function creates a ISOMessage object as per the messageType argument
 *						and returns the base pointer
 * 
 * IMPLEMENTATION:		1. Create a base pointer to ISO8583Message.
 *						2. Create a Message Object as per the 'messageType' argument with specified 'mapSize'.
 *						3. Assign the base pointer to the newly created object and return it.
 *						4. If the object is successfully instantiated, will update the ISOStatus reference argument 
 *						   "statusPtr" to the following values: 
 *							resultCode = 1
 *							resultDesc = "ClassFacotry::SUCCESS.  Specified Message Type Created"
 *						5. Map Size > 64:
 *						   resultCode = 5
 *						   resultDesc = "ClassFactory::ERROR. Map Size cannot exceed 64 for the Stored Value Cards message type."
 *						6. Invalid Message Type : The specified message type is not supported.
 *                         resultCode = 5
 *                         resultDesc = "ClassFactory::ERROR. Specified Message Type not supported."
 *						7. Class Not Found:
 *						   resultCode = 5
 *						   resultDesc = "ClassFactory::RUN-TIME ERROR. Class not found in the namespace."
 *						8. Initialization Error:
 *						   resultCode = 5
 *						   resultDesc = "ClassFactory::RUN-TIME ERROR. Specified Message Type failed to initialize."

 *
 ******************************************************************************************
 */

 ISO8583Message *ClassFactory::createMessage (const char* messageType, const int mapSize, ISOStatus& statusRef)
 {
	//memory allocated will be released in the client class
	ISO8583Message *messagePtr = NULL;

	messagePtr = newMessage (messageType, mapSize);

	if (messagePtr)
	{
	   //set the ISOStatus object with the valid code
	   statusRef.update (true, VALID, "ClassFactory::SUCCESS - Specified Message Type Created");
	}
	else
	{
	   //set the ISOStatus object with the valid code
	   statusRef.update (true, VALID, "ClassFactory::FAILURE - Class not found in the namespace");
	}

	// If we found and constructed the message dynamically return
	if (messagePtr)
	   return messagePtr;	

	// If we did not find and construct the message dynamically
	// we need to attempt to construct the message explicitly.
	// The issue is that on some platforms the messages are not
	// initialized in the classfactory due to initialization order.
	// ie if the classfactory is not initalized first the global list
	// of messages will not be initalized.

	int objType;
	//check the mapsize
	if(mapSize > 0 && mapSize <= 64)
	{
		//If message type is not null
		if(messageType != NULL)
		{
			// New code
			objType = 0;

			//check if the messageType exists
			while(arrMessageString[objType] != NULL )
			{
				//if the messageType exists break from the loop
				if( strcmp(arrMessageString[objType], messageType ) == 0 )
					break;

				//increment the index messageType array index
				objType++;
			}

			//instantiate the appropriate MessageType class
			switch (objType)
			{
				case 0:
					//create a class for ISO1100 class
					messagePtr = new ISO1100 (mapSize);
					break;

				case 1:
					//create a class for ISO1100SV class
					messagePtr = new ISO1100SV (mapSize);
					break;

				case 2:
					//create a class for ISO1110 class
					messagePtr = new ISO1110 (mapSize);
					break;

				case 3:
					//create a class for ISO1220 class
					messagePtr = new ISO1220 (mapSize);
					break;

				case 4:
					//create a class for ISO1220SV class
					messagePtr = new ISO1220SV (mapSize);
					break;

				case 5:
					//create a class for ISO1230 class
					messagePtr = new ISO1230 (mapSize);
					break;

				case 6:
					//create a class for ISO1420 class
					messagePtr = new ISO1420 (mapSize);
					break;

				case 7:
					//create a class for ISO1420SV class
					messagePtr = new ISO1420SV (mapSize);
					break;

				case 8:
					//create a class for ISO1430 class
					messagePtr = new ISO1430 (mapSize);
					break;

				case 9:
					//create a class for ISO1804 class
					messagePtr = new ISO1804 (mapSize);
					break;

				case 10:
					//create a class for ISO1814 class
					messagePtr = new ISO1814 (mapSize);
					break;
				
				case 11:
					//create a class for ISOResponse class 
					messagePtr = new ISORequest (mapSize);
					break;
					
				case 12:
					//create a class for ISOResponse class 
					messagePtr = new ISOResponse (mapSize);
					break;

				default:
					// handle the error
					//set the ISOStatus object with the invalid map size code and description
					statusRef.update (false, INVALID, "ClassFactory::ERROR. Requested Message type is not supported");

					//goto is required to ensure that there is only one exit point 
					//in the entire code.
					goto _Exit_Point_;
			}

			//The respective message class could not be found then
			//set error message
			if(messagePtr == NULL )
			{
				statusRef.update (false, INVALID, "ClassFactory::RUN-TIME ERROR. Class not found in the namespace");
			}
			//The message class is found.. set the status to true
			else
			{
				//set the ISOStatus object with the valid code
				statusRef.update (true, VALID, "ClassFactory::SUCCESS.  Specified Message Type Created");
			}
		}
		//If the Message type argument is NULL
		//Modified by Sunil on 06/26/2001
		else
		{
			//set the ISOStatus object with the valid code
			statusRef.update (false, NO_DATA, "ClassFactory::ERROR. Message Type argument cannot be NULL");
		}
	}
	//bit map size greater than 64 is not supported for the Stored Value Cards
	else
	{
		//set the ISOStatus object with the invalid map size code and description
		statusRef.update (false, INVALID, "ClassFactory::ERROR. Map Size cannot exceed 64 for the Stored Value Cards message");
	}

_Exit_Point_:

	return messagePtr;
 }

/******************************************************************************************
 *
 * NAME:                deleteMessage
 *
 * ARGUMENTS:           ISO8583Message *message - Specifies the message to destroy.
 *                                   
 * RETURN VALUE:        void
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This function destroys an ISOMessage object.
 * 
 ******************************************************************************************
 */
 void ClassFactory::deleteMessage (ISO8583Message *message)
 {
	if (message != NULL)
	{
	   delete message;
	   message = NULL;
	}

	return;
 }

/**************************************************************************
 *
 * CLASS NAME:          NONE
 *
 * SCOPE:               global
 *
 * DESCRIPTION:			This function returns a reference to a global
 *                      ClassFactory instance.
 *
 *                      This function is used internaly to the API and
 *                      should also be used by any client code that wishes
 *                      to construct ISO8583 messages.
 *
 **************************************************************************
 */

ClassFactory & ISO8583ClassFactory ()
{
	// global classfactory reference
	static ClassFactory oneAndOnlyClassFactory;

	return oneAndOnlyClassFactory;
}

ISO8583Implementation *ClassFactory::addClass (ISO8583Implementation *newM)
{
	if (newM != NULL)
	{
	   if (gDebug)
	      cout << "ClassFactory::addClass - dynamically registering class " << newM->getRequestType ()  << " msgType: " << newM->getMessageType () << "." << endl;

	   classList.Add (newM);
	}

	return newM;
}

ISO8583Implementation *ClassFactory::newMessage (const char *mName, const int mapSize)
{
	ISO8583Implementation *retval = 0;
	ISO8583Implementation *msg = NULL;
	ElemLstIterator<ISO8583Implementation> *iter = NULL;

	iter = classList.getIter ();
	
	if (iter == NULL)
	   return NULL;

	msg = iter->getThis ();

	if (mName == NULL)
       return NULL;

	while (msg && !(retval = msg->Make ((char *)mName, (int)mapSize)))
	{
		msg = iter->getNext ();
	}

	delete iter;

	return retval;
}

