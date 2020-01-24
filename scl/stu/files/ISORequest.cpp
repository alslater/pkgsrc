/*********************************************************************
*
*   Module:
*       ISORequest.cpp
*
*   Contents:
*       Implementation of the ISORequest class constructor and methods
*       
*   Description
*        It insatantiates the ISO message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISORequest.h
*
*
*   Created:
*		21 June 2001 Lonnie Filbrun
*
*   Modified:
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "CharUtility.h"
#include "Enumerations.h"
#include "FieldValidation.h"
#include "ISORequest.h"
#include "ClassFactory.h"

using namespace std;

extern int gTrace;
extern int gDebug;

//Definitions for the ISORequest Constructor and methods
//Default Constructor
ISORequest :: ISORequest()
{
}

//Definition of the ISORequest Constructor

/* Constructor Name: ISORequest
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of
 */

ISORequest :: ISORequest(int mapSize) : ISO8583Implementation("1100", mapSize)
{
	//Initialize the validation object pointer with the Validate Message class
    //For ISORequest class, the validation object is ISORequestValidation
//    valObjPointer = new ISORequestValidation ();
}

ISORequest :: ISORequest(char *msgType, int mapSize) : ISO8583Implementation(msgType, mapSize)
{
	//Initialize the validation object pointer with the Validate Message class
    //For ISORequest class, the validation object is ISORequestValidation
//    valObjPointer = new ISORequestValidation ();
}


//Definition of the ISORequest Constructor

/* Destructor Name: ISORequest
 * Will release the meory occupied by the memebers of the class
 */

ISORequest :: ~ISORequest()
{
	if (gDebug)
	   cout << "ISORequest::~ISORequest" << endl;
}

/*  Method Name: getResponseType
 *  Arguments: none
 *    
 *  Return Type:  char *
 *                Returns the response type for this object
 *
 *
 *   Implementation Details:
 *
 *	 1. This method returns the response type for this message.
 */

char* ISORequest::getResponseType()
{
       return "ISOResponse";
}

char* ISORequest::getRequestType()
{
		return getStaticRequestType ();
}

char* ISORequest::getStaticRequestType()
{
		return "ISORequest";
}

ISO8583Implementation * ISORequest::Make( char *mName, int mapSize )
{
	ISO8583Implementation *retval = 0;

	if( strcmp( mName, getStaticRequestType() ) == 0 )
	{
		retval =  new ISORequest( mapSize);
	}

	return retval;
}

static ISORequest * exemplarRequest = 
	(ISORequest*)ISO8583ClassFactory().addClass( new ISORequest(64) );
