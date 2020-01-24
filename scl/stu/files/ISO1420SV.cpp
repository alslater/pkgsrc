/*********************************************************************
*
*   Module:
*       ISO1420SV.cpp
*
*   Contents:
*       Implementation of the ISO1420SV class constructor and methods
*       
*   Description
*        It insatantiates the 1420 Stored values message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISO1420SV.h
*
*
*   Created:
*		30 May 2001 Arun G
*
*   Modified:
*		14 June 2001 Shubha Kumar
*			-Add length parameter to set, get, serialize methods
*
*       22 June 2001 Lonnie L. Filbrun
*                    Added the ability of deSerializing.
*
*
*		06 July 2001 Shubha Kumar
*				- Moved the default initialization of FieldMapElement array to the base class constructor
*				- Added code to reset the value of m_isRequired field of the FieldMapElement
*				  according to the SV guide for ISO1420 message
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1420SV.h"
#include "ISO1420SVVal.h"
#include "ClassFactory.h"

#define ISO1420SV_CLASS_NAME  "ISO1420SV"

//Definitions for the ISO1420SV Constructor and methods
//Default Constructor
ISO1420SV::ISO1420SV()
{
}

//Definition of the ISO1420SV Constructor

/* Constructor Name: ISO1420SV
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
 *     with "mapSize" argument and the constant string for the message tyepe.
 *  2. Will initialize the "m_fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the m_fieldMap array
 *     to reflect the requirements of the "Authorization" message.
 *  4. Will initialize the "valObjPointer" to refer to the Validation object
 *     required for validating authorization messages.
 *    valObjPointer = new(1420SVValidation)
*/

ISO1420SV::ISO1420SV(int mapSize) : ISO8583Implementation("1420", mapSize)
{
    m_className = ISO1420SV_CLASS_NAME;

	//set the m_isRequired field of all the supported bits 
	//with the option specific to this message
	//Bit positions 0 and 1 are reserved

	//[0]

    //Setting File Position - 2 (Primary Account Number)
	m_fieldMap[1]->m_isRequired = REQUIRED;

    //Setting File Position - 3 (Processing Code)
	m_fieldMap[2]->m_isRequired = REQUIRED;

    //Setting File Position - 4 (Transaction Amount)
	m_fieldMap[3]->m_isRequired = REQUIRED;

	//[4]
	//[5]
	//[6]
	//[7]
	//[8]
	//[9]

    //Setting File Position - 11 (Systems Trace Audit Number)
	m_fieldMap[10]->m_isRequired = REQUIRED;

    //Setting File Position - 12 (Local Transmission Date and Time)
	m_fieldMap[11]->m_isRequired = REQUIRED;

	//Setting File Position - 13 (Card Effective date)
	m_fieldMap[12]->m_isRequired = OPTIONAL;

	//Setting File Position - 14 (Card expiration date)
	m_fieldMap[13]->m_isRequired = OPTIONAL;

	//[14]
	//[15]
	//[16]
	
	//Setting File Position - 18 (Merchant Type)
	m_fieldMap[17]->m_isRequired = OPTIONAL;

	//Setting File Position - 19 (Acquiring Institution country code)
	m_fieldMap[18]->m_isRequired = OPTIONAL;

	//[19]
	//[20]

	//Setting File Position - 22 (Point of Service Data code)
	m_fieldMap[21]->m_isRequired = OPTIONAL;

	//[22]

    //Setting File Position - 24 (Function Code)
	m_fieldMap[23]->m_isRequired = REQUIRED;

    //Setting File Position - 25 (Message Reason Code)
	m_fieldMap[24]->m_isRequired = OPTIONAL;

	//Setting File Position - 26 (Card Acceptor Business Code)
	m_fieldMap[25]->m_isRequired = OPTIONAL;

	//[26]
	//[27]
	//[28]
	//[29]
	//[30]

    //Setting File Position - 32 (Acquiring Institution Identification Code)
	m_fieldMap[31]->m_isRequired = OPTIONAL;

	//[32]
	//[33]

	//Setting File Position - 35 (Track 2 Data)
	m_fieldMap[34]->m_isRequired = OPTIONAL;

	//[35]

    //Setting File Position - 37 (Retrieval Reference Number)
	m_fieldMap[36]->m_isRequired = OPTIONAL;

    //Setting File Position - 38 (Approval Code)
	m_fieldMap[37]->m_isRequired = OPTIONAL;

	//[38]
	//[39]

	//Setting File Position - 41 (Card Acceptor Terminal Identification)
	m_fieldMap[40]->m_isRequired = OPTIONAL;

    //Setting File Position - 42 (Card Acceptor Identification Code)
	m_fieldMap[41]->m_isRequired = REQUIRED;

    //Setting File Position - 43 (Card Acceptor Name/Location)
	m_fieldMap[42]->m_isRequired = OPTIONAL;

	//[43]

	//Setting File Position - 45 (Track - 1  Data)
	m_fieldMap[44]->m_isRequired = OPTIONAL;

	//[45]
	//[46]
	//[47]

	//Setting File Position - 49 (Transaction Currency Code)
	m_fieldMap[48]->m_isRequired = REQUIRED;

	//[49]
	//[50]
	//[51]
	//[52]
	//[53]
	//[54]

    //Setting File Position - 56 (Transaction Currency Code)
	m_fieldMap[55]->m_isRequired = REQUIRED;

	//[56]
	//[57]
	//[58]
	//[59]
	//[60]

    //Setting File Position - 62 (Private Use Data)
	m_fieldMap[61]->m_isRequired = OPTIONAL;

	//[62]
	//[63]

    //Initialize the validation object pointer with the releval Validate Message class
    //For ISO1420SV class, the validation object is ISO1420SVVal
    m_validator = new ISO1420SVVal ();
}


//Definition of the ISO1420SV Constructor

/* Destructor Name: ISO1420SV
 * Will release the memory occupied by the members of the class
 */

ISO1420SV::~ISO1420SV()
{
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

char *ISO1420SV::getResponseType ()
{
	return "ISO1430";
}

char *ISO1420SV::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1420SV::getStaticRequestType ()
{
	return "ISO1420SV";
}

ISO8583Implementation *ISO1420SV::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;

/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1420SV (mapSize);
	}
*/

	if (strcmp (mName, ISO1420SV_CLASS_NAME) == 0)
	{
		retval = new ISO1420SV (mapSize);
	}

    return retval;
}

static ISO1420SV *exemplar1420SV = 
	(ISO1420SV *)ISO8583ClassFactory().addClass (new ISO1420SV (64));
