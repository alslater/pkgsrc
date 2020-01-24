/*********************************************************************
*
*   Module:
*       ISO1814.cpp
*
*   Contents:
*       Implementation of the ISO1814 class constructor and methods
*       
*   Description
*        It insatantiates the 1814 network management response message in the 
*        relevant bit positions. The set and get fields work on the FieldMapElement 
*        array to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISO1814.h
*
*
*   Created:
*		19 June 2001 Shubha Kumar
*
*   Modified:
*		26 June 2001 Shubha Kumar
*				- Moved the default initialization of FieldMapElement array to the base class constructor
*				- Added code to reset the value of m_isRequired field of the FieldMapElement
*				  according to the ISO8583 guide for ISO1110 message
*				- Add serialize()
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1814.h"
#include "ClassFactory.h"

#define ISO1814_CLASS_NAME  "ISO1814"

//Definitions for the ISO1814 Constructor and methods
//Default Constructor
ISO1814 :: ISO1814()
{
}

//Definition of the ISO1814 Constructor

/* Constructor Name: ISO1814
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
 *     with "mapSize" argument.
 *  2. Will initialize the "m_fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the m_fieldMap array
 *     to reflect the requirements of the "Authorization" message.
 *
*/

ISO1814 :: ISO1814(int mapSize) : ISO8583Implementation("1814", mapSize)
{
    m_className = ISO1814_CLASS_NAME;

	//set the m_isRequired field of all the supported bits 
	//with the option specific to this message
	//Bit positions 0 and 1 are reserved

    //[0]
    //[1]

    //Initializing File Position - 3 (Processing Code)
	m_fieldMap[2]->m_isRequired = REQUIRED;

    //[3]
    //[4]
    //[5]
    //[6]
    //[7]
    //[8]
    //[9]

    //Initializing File Position - 11 (Systems Trace Audit Number)
	m_fieldMap[10]->m_isRequired = REQUIRED;

	//[11]
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
    //[32]
    //[33]
    //[34]
    //[35]
    //[36]
    //[37]
    //[38]
    //[39]
    //[40]
    //[41]
    //[42]
    //[43]
    //[44]
    //[45]
    //[46]
    //[47]
    //[48]
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


//Definition of the ISO1814 Constructor

/* Destructor Name: ISO1814
 * Will release the meory occupied by the memebers of the class
 */

ISO1814 :: ~ISO1814()
{
}

char *ISO1814::getResponseType ()
{
	return "ISO1804";
}

char *ISO1814::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1814::getStaticRequestType ()
{
	return "ISO1814";
}

ISO8583Implementation *ISO1814::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;

/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1814 (mapSize);
	}
*/

	if (strcmp (mName, ISO1814_CLASS_NAME) == 0)
	{
		retval = new ISO1814 (mapSize);
	}

    return retval;
}

static ISO1814 *exemplar1814 = 
	(ISO1814 *)ISO8583ClassFactory().addClass (new ISO1814 (64));
