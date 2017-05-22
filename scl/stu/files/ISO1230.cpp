/*********************************************************************
*
*   Module:
*       ISO1230.cpp
*
*   Contents:
*       Implementation of the ISO1230 class constructor and methods
*       
*   Description
*        It instantiates the 1230 Stored values message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISO1230.h
*
*
*   Created:
*		05 June 2001 Arun G
*
*   Modified:
*		14 June 2001 Arun G.
*				-Added the length argument to the get, set and deserialize methods
*
*       22 June 2001 Lonnie L. Filbrun
*                    Added the ability of serializing.
*
*
*		06 July 2001 Shubha Kumar
*				- Moved the default initialization of FieldMapElement array to the base class constructor
*				- Added code to reset the value of m_isRequired field of the FieldMapElement
*				  according to the SV guide for ISO1230 message
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1230.h"
#include "ClassFactory.h"

#define ISO1230_CLASS_NAME  "ISO1230"

//Definitions for the ISO1230 Constructor and methods
//Default Constructor
ISO1230::ISO1230()
{
}

//Definition of the ISO1230 Constructor

/* Constructor Name: ISO1230
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
 *     with "mapSize" argument and the constant string for the message type.
 *  2. Will initialize the "m_fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the m_fieldMap array
 *     to reflect the requirements of the "Authorization" message.
 *  4. Will initialize the "valObjPointer" to refer to the Validation object
 *     required for validating authorization messages.
 *    valObjPointer = new(1230Validation)
*/

ISO1230::ISO1230(int mapSize) : ISO8583Implementation("1230", mapSize)
{
    m_className = ISO1230_CLASS_NAME;

	//set the m_isRequired field of all the supported bits 
	//with the option specific to this message
	//Bit positions 0 and 1 are reserved

	//[0]

    //Initializing File Position - 2 (Primary Account Number)
	m_fieldMap[1]->m_isRequired = ECHO;

    //Initializing File Position - 3 (Processing Code)
	m_fieldMap[2]->m_isRequired = ECHO;

    //Initializing File Position - 4 (Transaction Amount)
	m_fieldMap[3]->m_isRequired = ECHO;

	//[4]
	//[5]

	//Setting File Position - 7 (Transmission Date and Time)
	m_fieldMap[6]->m_isRequired = ECHO;

	//[7]
	//[8]
	//[9]

    //Setting File Position - 11 (Systems Trace Audit Number)
	m_fieldMap[10]->m_isRequired = ECHO;

    //Setting File Position - 12 (Local Transmission Date and Time)
	m_fieldMap[11]->m_isRequired = ECHO;

	//[12]
	//[13]
	//[14]
	//[15]
	//[16]
	//[17]
	//[18]
	//[19]
	//[20]
	//[21]
	//[22]
	//[23]
	//[24]
	//[25]
	//[26]
	//[27]
	//[28]
	//[29]
	//[30]

    //Setting File Position - 32 (Acquiring Institution Identification Code)
	m_fieldMap[31]->m_isRequired = ECHO;

	//[32]
	//[33]
	//[34]
	//[35]

    //Setting File Position - 37 (Retrieval Reference Number)
	m_fieldMap[36]->m_isRequired = ECHO;

    //Setting File Position - 38 (Approval Code)
	m_fieldMap[37]->m_isRequired = CONDITIONAL;

    //Setting File Position - 39 (Action Code)
	m_fieldMap[38]->m_isRequired = REQUIRED;

	//[39]
	//[40]

    //Setting File Position - 42 (Card Acceptor Identification Code)
	m_fieldMap[41]->m_isRequired = ECHO;

	//[42]
	//[43]
	//[44]
	//[45]
	//[46]
	//[47]

    //Setting File Position - 49 (Transaction Currency Code)
	m_fieldMap[48]->m_isRequired = ECHO;

	//[49]
	//[50]
	//[51]
	//[52]
	
    //Setting File Position - 54 (Addtional Amount)
	m_fieldMap[53]->m_isRequired = CONDITIONAL;

	//[54]
	//[55]
	//[56]
	//[57]
	//[58]
	//[59]
	//[60]
	//[61]
	//[62]
	//[63]

}


//Definition of the ISO1230 Constructor

/* Destructor Name: ISO1230
 * Will release the memory occupied by the members of the class
 */

ISO1230::~ISO1230()
{
}

char *ISO1230::getResponseType ()
{
	return "ISO1220";
}

char *ISO1230::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1230::getStaticRequestType ()
{
	return "ISO1230";
}

ISO8583Implementation *ISO1230::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;

/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1230 (mapSize);
	}
*/

	if (strcmp (mName, ISO1230_CLASS_NAME) == 0)
	{
		retval = new ISO1230 (mapSize);
	}

	return retval;
}

static ISO1230 *exemplar1230 = 
	(ISO1230 *)ISO8583ClassFactory().addClass (new ISO1230 (64));


