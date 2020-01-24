/*********************************************************************
*
*   Module:
*       ISO1804.cpp
*
*   Contents:
*       Implementation of the ISO1804 class constructor and methods
*       
*   Description
*        It insatantiates the 1804 network management message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISO1804.h
*
*
*   Created:
*		19 June 2001 Shubha Kumar
*
*   Modified:
*		26 June 2001 Shubha Kumar
*				- Moved the default initialization of FieldMapElement array to the base class constructor
*				- Added code to reset the value of m_isRequired field of the FieldMapElement
*				  according to the ISO8583 guide for ISO1100 message
*				- Add deSerialize()
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1804.h"
#include "ISO1804Val.h"
#include "ClassFactory.h"

#define ISO1804_CLASS_NAME  "ISO1804"

//Definitions for the ISO1804 Constructor and methods
//Default Constructor
ISO1804 :: ISO1804()
{
}

//Definition of the ISO1804 Constructor

/* Constructor Name: ISO1804
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
 *    valObjPointer = new(ISO1804Val)
*/

ISO1804 :: ISO1804(int mapSize) : ISO8583Implementation("1804", mapSize)
{
    m_className = ISO1804_CLASS_NAME;

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
    
	//Initializing File Position - 24 (Function Code)
	m_fieldMap[23]->m_isRequired = REQUIRED;

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
    
	//Initialize the validation object pointer with the releval Validate Message class
    //For ISO1804 class, the validation object is ISO1804Val
    m_validator = new ISO1804Val ();
}


//Definition of the ISO1804 Constructor

/* Destructor Name: ISO1804
 * Will release the meory occupied by the memebers of the class
 */

ISO1804 :: ~ISO1804()
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

char *ISO1804::getResponseType ()
{
	return "ISO1814";
}

char *ISO1804::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1804::getStaticRequestType ()
{
	return "ISO1804";
}

ISO8583Implementation *ISO1804::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;

/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval =  new ISO1804 (mapSize);
	}
*/

	if (strcmp (mName, ISO1804_CLASS_NAME) == 0)
	{
		retval =  new ISO1804 (mapSize);
	}

    return retval;
}

static ISO1804 *exemplar1804 = 
	(ISO1804 *)ISO8583ClassFactory().addClass (new ISO1804 (64));
