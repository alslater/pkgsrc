/*********************************************************************
*
*   Module:
*       ISO1110.cpp
*
*   Contents:
*       Implementation of the ISO1110 class constructor and methods
*       
*   Description
*        It insatantiates the 1110 Stored values message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The deserialize methods converts the EBCDIC byte stream into character data.
*
*   See Also:
*       ISO1110.h
*
*
*   Created:
*		04 June 2001 Arun G.
*
*   Modified:
*		12 June 2001 Shubha Kumar
*			-Added the length argument to the get, set, serialize and deserialize methods
*
*       22 June 2001 Lonnie L. Filbrun
*                    Added the ability of serializing.
*
*
*		06 July 2001 Shubha Kumar
*				- Moved the default initialization of FieldMapElement array to the base class constructor
*				- Added code to reset the value of m_isRequired field of the FieldMapElement
*				  according to the SV guide for ISO1110 message
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1110.h"
#include "ClassFactory.h"

#define ISO1110_CLASS_NAME  "ISO1110"

//Definitions for the ISO1110 Constructor and methods
//Default Constructor
ISO1110 :: ISO1110()
{
}

//Definition of the ISO1110 Constructor

/* Constructor Name: ISO1110
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of 128
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
 *     with "mapSize" argument.
 *  2. Will initialize the "m_fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the m_fieldMap array
 *     to reflect the requirements of the "Authorization" message.
 *  4. Will initialize the "valObjPointer" to refer to the Validation object
 *     required for validating authorization messages.
 *    valObjPointer = new(ISO1110Validation)
*/

ISO1110 :: ISO1110(int mapSize) : ISO8583Implementation("1110", mapSize)
{
    m_className = ISO1110_CLASS_NAME;
	
	//set the m_isRequired field of all the supported bits 
	//with the option specific to this message
	//Bit positions 0 and 1 are reserved

	//[0]

    //Setting File Position - 2 (Primary Account Number)
	m_fieldMap[1]->m_isRequired = ECHO;

    //Setting File Position - 3 (Processing Code)
	m_fieldMap[2]->m_isRequired = ECHO;

    //Setting File Position - 4 (Transaction Amount)
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

    //Setting File Position - 30 (Original Amounts)
	m_fieldMap[29]->m_isRequired = OPTIONAL;

	//Setting File Position - 31 (Acquirer reference data)
	m_fieldMap[30]->m_isRequired = CONDITIONAL;

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

    //Setting File Position - 41 (Card Acceptor Terminal Identification)
	m_fieldMap[40]->m_isRequired = ECHO;

    //Setting File Position - 42 (Card Acceptor Identification Code)
	m_fieldMap[41]->m_isRequired = ECHO;

	//[42]

    //Setting File Position - 44 (Additional Reaponse Data)
	m_fieldMap[43]->m_isRequired = CONDITIONAL;

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
	
    //Setting File Position - 54 (Additional Amount)
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



/* Destructor Name: ISO1110
 * Will release the meory occupied by the memebers of the class
 */

ISO1110 :: ~ISO1110()
{
}

char *ISO1110::getResponseType ()
{
	return "ISO1100";
}

char *ISO1110::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1110::getStaticRequestType ()
{
	return "ISO1110";
}

ISO8583Implementation *ISO1110::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;
	
/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1110 (mapSize);
	}
*/

	if (strcmp (mName, ISO1110_CLASS_NAME) == 0)
	{
		retval = new ISO1110 (mapSize);
	}

	return retval;
}

static ISO1110 *exemplar1100 =
	(ISO1110 *)ISO8583ClassFactory().addClass (new ISO1110 (64));




