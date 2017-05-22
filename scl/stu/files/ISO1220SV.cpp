/*********************************************************************
*
*   Module:
*       ISO1220SV.cpp
*
*   Contents:
*       Implementation of the ISO1220SV class constructor and methods
*       
*   Description
*        It insatantiates the 1220 Stored values message in the relevant bit
*        positions. The set, get, serialize and other methods call the base 
*		 class implementation of these methods.
*
*   See Also:
*       ISO1220SV.h
*
*
*   Created:
*		30 May 2001 Arun G
*
*   Modified:
*		11 June 2001 Shubha Kumar
*			-Added the length parameter to the arguments
*
*       22 June 2001 Lonnie L. Filbrun
*                    Added the ability of deSerializing.
*
*
*		06 July 2001 Shubha Kumar
*				- Moved the default initialization of FieldMapElement array to the base class constructor
*				- Added code to reset the value of m_isRequired field of the FieldMapElement
*				  according to the SV guide for ISO1220 message
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1220SV.h"
#include "ISO1220SVVal.h"
#include "ClassFactory.h"

#define ISO1220SV_CLASS_NAME  "ISO1220SV"

//Definitions for the ISO1220SV Constructor and methods
//Default Constructor
ISO1220SV::ISO1220SV()
{
}

//Definition of the ISO1220SV Constructor

/* Constructor Name: ISO1220SV
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of 64 or 128 bits
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
 *     with "mapSize" argument and the constant string for the message type.
 *  2. Will initialize the "m_fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the m_fieldMap array
 *     to reflect the requirements of the "Authorization" message.
 *  4. Will initialize the "valObjPointer" to refer to the Validation object
 *     required for validating authorization messages.
 *    valObjPointer = new(1220SVValidation)
*/

ISO1220SV::ISO1220SV(int mapSize) : ISO8583Implementation("1220", mapSize)
{
    m_className = ISO1220SV_CLASS_NAME;

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

	//Setting File Position - 7 (Transmission Date and Time)
	m_fieldMap[6]->m_isRequired = OPTIONAL;

	//[7]
	//[8]
	//[9]

    //Setting File Position - 11 (Systems Trace Audit Number)
	m_fieldMap[10]->m_isRequired = REQUIRED;

    //Setting File Position - 12 (Local Transmission Date and Time)
	m_fieldMap[11]->m_isRequired = REQUIRED;

    //Setting File Position - 13 (Card Effective Date)
	m_fieldMap[12]->m_isRequired = OPTIONAL;

    //Setting File Position - 14 (Card Expiration Date)
	m_fieldMap[13]->m_isRequired = OPTIONAL;

	//[14]
	//[15]
	//[16]

    //Setting File Position - 18 (Merchant Type)
	m_fieldMap[17]->m_isRequired = OPTIONAL;

	//Setting File Position - 19 (Aquiring Institution country code)
	m_fieldMap[18]->m_isRequired = OPTIONAL;

	//[19]
	//[20]

    //Setting File Position - 22 (Point of Service Data)
	m_fieldMap[21]->m_isRequired = REQUIRED;

	//[22]

    //Setting File Position - 24 (Function Code)
	m_fieldMap[23]->m_isRequired = REQUIRED;

	//[24]

    //Setting File Position - 26 (Card Acceptor Business Code)
	m_fieldMap[25]->m_isRequired = REQUIRED;

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
	m_fieldMap[34]->m_isRequired = CONDITIONAL;

	//[35]

    //Setting File Position - 37 (Retrieval Reference Number)
	m_fieldMap[36]->m_isRequired = OPTIONAL;

	//[37]
	//[38]
	//[39]

	//Setting File Position - 41 (Card Acceptor Terminal Identification)
	m_fieldMap[40]->m_isRequired = OPTIONAL;

    //Setting File Position - 42 (Card Acceptor Identification Code)
	m_fieldMap[41]->m_isRequired = REQUIRED;

    //Setting File Position - 43 (Card Acceptor Name/Location)
	m_fieldMap[42]->m_isRequired = OPTIONAL;

	//[43]

    //Setting File Position - 45 (Track 1 Data)
	m_fieldMap[44]->m_isRequired = CONDITIONAL;

	//[45]
	//[46]

    //Setting File Position - 48 (Addtional Demographic Data)
	m_fieldMap[47]->m_isRequired = OPTIONAL;

    //Setting File Position - 49 (Transaction Currency Code)
	m_fieldMap[48]->m_isRequired = REQUIRED;

	//[49]
	//[50]
	//[51]
	//[52]
	//[53]
	//[54]
	//[55]
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
    //For ISO1220SV class, the validation object is ISO1220SVValidation
    m_validator = new ISO1220SVVal ();
}


//Definition of the ISO1220SV Constructor

/* Destructor Name: ISO1220SV
 * Will release the memory occupied by the members of the class
 */

ISO1220SV::~ISO1220SV()
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


char *ISO1220SV::getResponseType ()
{
	return "ISO1230";
}

char *ISO1220SV::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1220SV::getStaticRequestType ()
{
	return "ISO1220SV";
}

ISO8583Implementation *ISO1220SV::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;
	
/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1220SV( mapSize);
	}
*/

	if (strcmp (mName, ISO1220SV_CLASS_NAME) == 0)
	{
		retval = new ISO1220SV( mapSize);
	}

    return retval;
}

static ISO1220SV *exemplar1220SV = 
	(ISO1220SV *)ISO8583ClassFactory().addClass (new ISO1220SV (64));
