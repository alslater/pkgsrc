/*********************************************************************
*
*   Module:
*       ISO1430.cpp
*
*   Contents:
*       Implementation of the ISO1430 class constructor and methods
*       
*   Description
*        It insatantiates the 1430 Stored values message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISO1430.h
*
*
*   Created:
*		19 June 2001 Shubha Kumar
*
*   Modified:
*		26 June 2001 Arun G
*				- Added code to reset the value of m_isRequired field of the FieldMapElement
*				  according to the field definitions for ISO1430 message
*				- Added function serialize()
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1430.h"
#include "ClassFactory.h"

#define ISO1430_CLASS_NAME  "ISO1430"

//Definitions for the ISO1430 Constructor and methods
//Default Constructor
ISO1430::ISO1430()
{
}

//Definition of the ISO1430 Constructor

/* Constructor Name: ISO1430
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
 *     with "mapSize" argument.
 *  2. Will initialize the "m_fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the m_fieldMap array
 *     to reflect the requirements of the "Authorization" message.
*/

ISO1430::ISO1430(int mapSize) : ISO8583Implementation("1430", mapSize)
{
    m_className = ISO1430_CLASS_NAME;

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
	//[31]

    //Initializing File Position - 32 (Acquiring Institution Identification Code)
	m_fieldMap[31]->m_isRequired = OPTIONAL;

	//[32]
	//[33]
	//[34]
	//[35]

    //Initializing File Position - 37 (Retrieval Reference Number)
	m_fieldMap[36]->m_isRequired = OPTIONAL;

	//[37]

    //Initializing File Position - 39 (Approval Code)
	m_fieldMap[38]->m_isRequired = REQUIRED;

	//[39]
	//[40]

    //Initializing File Position - 42 (Card Acceptor Identification Code)
	m_fieldMap[41]->m_isRequired = REQUIRED;

	//[42]
	//[43]
	//[44]
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


//Definition of the ISO1430 Destructor

/* Destructor Name: ISO1430
 * Will release the memory occupied by the members of the class
 */

ISO1430::~ISO1430()
{
}

char *ISO1430::getResponseType ()
{
	return "ISO1420";
}

char *ISO1430::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1430::getStaticRequestType ()
{
	return "ISO1430";
}

ISO8583Implementation *ISO1430::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;

/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1430 (mapSize);
	}
*/
    
	if (strcmp (mName, ISO1430_CLASS_NAME) == 0)
	{
		retval = new ISO1430 (mapSize);
	}

    return retval;
}

static ISO1430 *exemplar1430 = 
	(ISO1430 *)ISO8583ClassFactory().addClass (new ISO1430 (64));
