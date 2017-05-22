/*********************************************************************
*
*   Module:
*       ISO1420.cpp
*
*   Contents:
*       Implementation of the ISO1420 class constructor and methods
*       
*   Description
*        It insatantiates the 1420 reversal advice message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISO1420.h
*
*
*   Created:
*		19 June 2001 Shubha Kumar
*
*   Modified:
*		25 June 2001 Arun G.
*				- Added code to reset the value of m_isRequired field of the FieldMapElement
*				  according to the field definitions for ISO1420 message
*				- Added function deSerialize()
*
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1420.h"
#include "ISO1420Val.h"
#include "ClassFactory.h"

#define ISO1420_CLASS_NAME  "ISO1420"

//Definitions for the ISO1420 Constructor and methods
//Default Constructor
ISO1420 :: ISO1420()
{
}

//Definition of the ISO1420 Constructor

/* Constructor Name: ISO1420
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
 *     with "mapSize" argument.
 *  2. Will initialize the "m_fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the m_fieldMap array
 *     to reflect the requirements of the "Network Management" message.
 *  4. Will initialize the "valObjPointer" to refer to the Validation object
 *     required for validating authorization messages.
 *    valObjPointer = new(ISO1420Val)
*/

ISO1420 :: ISO1420(int mapSize) : ISO8583Implementation("1420", mapSize)
{
    m_className = ISO1420_CLASS_NAME;

	//set the m_isRequired field of all the supported bits 
	//with the option specific to this message
	//Bit positions 0 and 1 are reserved

	//[0]

    //Initializing File Position - 2 (Primary Account Number)
	m_fieldMap[1]->m_isRequired = REQUIRED;

    //Initializing File Position - 3 (Processing Code)
	m_fieldMap[2]->m_isRequired = REQUIRED;

    //Initializing File Position - 4 (Transaction Amount)
	m_fieldMap[3]->m_isRequired = REQUIRED;

	//[4]
	//[5]
	//[6]
	//[7]
	//[8]
	//[9]

    //Initializing File Position - 11 (Systems Trace Audit Number)
	m_fieldMap[10]->m_isRequired = REQUIRED;

    //Initializing File Position - 12 (Local Transmission Date and Time)
	m_fieldMap[11]->m_isRequired = REQUIRED;

	//Initializing File Position - 13 (Card Effective date)
	m_fieldMap[12]->m_isRequired = CONDITIONAL;

	//Initializing File Position - 14 (Card expiration date)
	m_fieldMap[13]->m_isRequired = CONDITIONAL;

	//[14]
	//[15]
	//[16]

	//Initializing File Position - 18 (Merchant Type)
	m_fieldMap[17]->m_isRequired = OPTIONAL;

	//Initializing File Position - 19 (Acquiring Institution country code)
	m_fieldMap[18]->m_isRequired = REQUIRED;

	//[19]
	//[20]

	//Initializing File Position - 22 (Point of Service Data code)
	m_fieldMap[21]->m_isRequired = REQUIRED;

	//[22]
	//[23]
	//[24]
	//[25]
	//[26]
	//[27]
	//[28]
	//[29]
	//[30]

    //Initializing File Position - 32 (Acquiring Institution Identification Code)
	m_fieldMap[31]->m_isRequired = OPTIONAL;

    //Initializing File Position - 33 (Forwarding Institution Identification Code)
	m_fieldMap[32]->m_isRequired = OPTIONAL;

	//[33]

	//Initializing File Position - 35 (Track 2 Data)
	m_fieldMap[34]->m_isRequired = CONDITIONAL;

	//[35]

    //Initializing File Position - 37 (Retrieval Reference Number)
	m_fieldMap[36]->m_isRequired = OPTIONAL;

	//[37]
	//[38]
	//[39]

    //Initializing File Position - 41 (Card Acceptor Terminal Identification)
	m_fieldMap[40]->m_isRequired = CONDITIONAL;

    //Initializing File Position - 42 (Card Acceptor Identification Code)
	m_fieldMap[41]->m_isRequired = REQUIRED;

	//[42]
	//[43]
	
    //Initializing File Position - 45 (Track 1 Data)
	m_fieldMap[44]->m_isRequired = CONDITIONAL;

	//[45]
	//[46]
	//[47]

	//Initializing File Position - 49 (Transaction Currency Code)
	m_fieldMap[48]->m_isRequired = REQUIRED;

	//[49]
	//[50]
	//[51]
	//[52]
	//[53]
	//[54]

    //Initializing File Position - 56 (Transaction Currency Code)
	m_fieldMap[55]->m_isRequired = REQUIRED;

	//[56]
	//[57]
	//[58]
	//[59]
	//[60]

    //Initializing File Position - 62 (Private Use Data)
	m_fieldMap[61]->m_isRequired = OPTIONAL;

	//[62]
	//[63]

    //Initialize the validation object pointer with the releval Validate Message class
    //For ISO1420 class, the validation object is ISO1420Val
    m_validator = new ISO1420Val ();
}


//Definition of the ISO1420 Constructor

/* Destructor Name: ISO1420
 * Will release the meory occupied by the memebers of the class
 */

ISO1420 :: ~ISO1420()
{

}

/*  Method Name: removeDecPoint
 *  Arguments: 
 *		dataPtr : unsigned char * - the data with the decimal delimiter
 *		dataLen : length of the data
 *    
 *  Return Type:  unsigned char *
 *                Returns the data without the decimal point
 *
 *
 *   Implementation Details:
 *
 *	 1. This method returns the data without the decimal point
 */

unsigned char* ISO1420::removeDecPoint(unsigned char* dataPtr, int dataLen, ISOStatus& statusRef)
{
	//return data Pointer
	//memory allocated to be released by the calling method
	unsigned char* returnPtr = NULL;

	//allocate memory to the return data pointer
	returnPtr = new unsigned char[dataLen];

	//counter variable
	int i, j;
	
	//check if memory has been allocated
 	if(returnPtr != NULL)
	{
		//add 1 leading 0 to replace the decimal point to be removed
		returnPtr[0] = '0';
		//copy the rest of the data to the return pointer skipping the decimal point
		for(i=1, j=0; j<dataLen; i++, j++)
		{
			if(dataPtr[j] == '.')
				j++;

			returnPtr[i] = dataPtr[j];
		}
	}
	else
	{
		//set the ISOStatus object with the error code and the description
		statusRef.setStatus(false);
		statusRef.setResultCode(ENOMEM);
		statusRef.setResultDesc("Failure - Insufficient memory");
	}
	return returnPtr;
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


char *ISO1420::getResponseType ()
{
	return "ISO1430";
}

char *ISO1420::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1420::getStaticRequestType ()
{
	return "ISO1420";
}

ISO8583Implementation *ISO1420::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;
	
/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1420 (mapSize);
	}
*/

	if (strcmp (mName, ISO1420_CLASS_NAME) == 0)
	{
		retval = new ISO1420 (mapSize);
	}

    return retval;
}

static ISO1420 *exemplar1420 = 
	(ISO1420 *)ISO8583ClassFactory().addClass (new ISO1420 (64));
