/*********************************************************************
*
*   Module:
*       ISOResponse.cpp
*
*   Contents:
*       Implementation of the ISOResponse class constructor and methods
*       
*   Description
*        It insatantiates the 1110 Stored values message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The deserialize methods converts the EBCDIC byte stream into character data.
*
*   See Also:
*       ISOResponse.h
*
*   Created:
*		21 June 2001 Lonnie Filbrun
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
#include "ISOResponse.h"
#include "ClassFactory.h"

using namespace std;

extern int gTrace;
extern int gDebug;

//Definitions for the ISOResponse Constructor and methods
//Default Constructor
ISOResponse :: ISOResponse()
{
}

//Definition of the ISOResponse Constructor

/* Constructor Name: ISOResponse
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of 128
 */

ISOResponse :: ISOResponse(int mapSize) : ISO8583Implementation("1110", mapSize)
{
	//Initialize the validation object pointer with the Validate Message class
    //For ISOResponse class, the validation object is ISOResponseValidation
//    valObjPointer = new ISOResponseValidation ();	
}

ISOResponse :: ISOResponse(char *msgType, int mapSize) : ISO8583Implementation(msgType, mapSize)
{
	//Initialize the validation object pointer with the Validate Message class
    //For ISOResponse class, the validation object is ISOResponseValidation
//    valObjPointer = new ISOResponseValidation ();	
}

/* Destructor Name: ISOResponse
 * Will release the meory occupied by the memebers of the class
 */

ISOResponse :: ~ISOResponse()
{
	if (gDebug)
	   cout << "ISOResponse::~ISOResponse" << endl;
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

char* ISOResponse::getResponseType()
{
       return "ISORequest";
}

char* ISOResponse::getRequestType()
{
		return getStaticRequestType ();
}

char* ISOResponse::getStaticRequestType()
{
		return "ISOResponse";
}

ISO8583Implementation * ISOResponse::Make( char *mName, int mapSize )
{
	ISO8583Implementation *retval = 0;

	if( strcmp( mName, getStaticRequestType() ) == 0 )
	{
		retval =  new ISOResponse( mapSize);
	}

	return retval;
}

static ISOResponse * exemplarResponse = 
	(ISOResponse*)ISO8583ClassFactory().addClass( new ISOResponse(64) );
