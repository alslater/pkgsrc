/*********************************************************************
*
*   Module:
*       ISO1100.cpp
*
*   Contents:
*       Implementation of the ISO1100 class constructor and methods
*       
*   Description
*        It insatantiates the 1100 Stored values message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISO1100.h
*
*
*   Created:
*		20th June 2001 Subbu G Gowreddy
*
*   Modified:
*		26 June 2001 Shubha Kumar
*				- Moved the default initialization of FieldMapElement array to the base class constructor
*				- Added code to reset the value of isRequired field of the FieldMapElement
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
#include "ISO1100.h"
#include "ISO1100Val.h"
#include "ClassFactory.h"

#define ISO1100_CLASS_NAME  "ISO1100"

//Definitions for the ISO1100 Constructor and methods
//Default Constructor
ISO1100 :: ISO1100()
{
}

//Definition of the ISO1100 Constructor

/* Constructor Name: ISO1100
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
 *     with "mapSize" argument.
 *  2. Will initialize the "m_fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the m_fieldMap array
 *     to reflect the requirements of the "Authorization" message.
 *  4. Will initialize the "valObjPointer" to refer to the Validation object
 *     required for validating authorization messages.
 *    valObjPointer = new(1100SVValidation)
*/

ISO1100 :: ISO1100(int mapSize) : ISO8583Implementation("1100", mapSize)
{
    m_className = ISO1100_CLASS_NAME;

	//set the isRequired field of all the supported bits 
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

    //Initializing File Position - 7 (Transmission Date and Time)
	m_fieldMap[6]->m_isRequired = OPTIONAL;

    //[7]
	//[8]
	//[9]

	//Initializing File Position - 11 (Systems Trace Audit Number)
	m_fieldMap[10]->m_isRequired = REQUIRED;

    //Initializing File Position - 12 (Local Transmission Date and Time)
	m_fieldMap[11]->m_isRequired = OPTIONAL;

    //Initializing File Position - 13 (Card Effective Date)
	m_fieldMap[12]->m_isRequired = CONDITIONAL;

    //Initializing File Position - 14 (Card Expiration Date)
	m_fieldMap[13]->m_isRequired = CONDITIONAL;

    //[14]
	//[15]
	//[16]

	//Initializing File Position - 18 (Merchant Type)
	m_fieldMap[17]->m_isRequired = REQUIRED;

    //Initializing File Position - 19 (Acquiring Institution Country Code)
	m_fieldMap[18]->m_isRequired = REQUIRED;

    //[19]
	//[20]

	//Initializing File Position - 22 (Point of Service Data)
	m_fieldMap[21]->m_isRequired = REQUIRED;

    //[22]

	//Initializing File Position - 24 (Function Code)
	m_fieldMap[23]->m_isRequired = CONDITIONAL;

	//Initializing File Position - 25
	m_fieldMap[24]->m_isRequired = CONDITIONAL;

    //Initializing File Position - 26 (Card Acceptior Business Code)
	m_fieldMap[25]->m_isRequired = REQUIRED;

	//Initializing File Position - 27 
	m_fieldMap[26]->m_isRequired = OPTIONAL;

    //[27]
	//[28]
	//[29]
	//[30]

	//Initializing File Position - 32 (Acquiring Institution Identification Code)
	m_fieldMap[31]->m_isRequired = OPTIONAL;

	//Initializing File Position - 33
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

    //Initializing File Position - 43 (Card Acceptor Name/Location)
	m_fieldMap[42]->m_isRequired = CONDITIONAL;

    //[43]

	//Initializing File Position - 45 (Track 1 Data)
	m_fieldMap[44]->m_isRequired = CONDITIONAL;

    //[45]
	//[46]

	//Initializing File Position - 48 (Addtional Demographic Data)
	m_fieldMap[47]->m_isRequired = CONDITIONAL;

    //Initializing File Position - 49 (Transaction Currency Code)
	m_fieldMap[48]->m_isRequired = REQUIRED;

    //[49]
	//[50]
	//[51]

	//Initializing File Position - 53 (Security Related Control Information)
	m_fieldMap[52]->m_isRequired = CONDITIONAL;

    //[53]

	//Initializing File Position - 55 (Additional Amount)
	m_fieldMap[54]->m_isRequired = OPTIONAL;

    //[55]
	//[56]
	//[57]
	//[58]
	//[59]
	//[60]

	//Initializing File Position - 62 (Private Use Data)
	m_fieldMap[61]->m_isRequired = CONDITIONAL;

    //Initializing File Position - 63 (Private Data)
	m_fieldMap[62]->m_isRequired = CONDITIONAL;

    //[63]

	//Initializa the validation object pointer with the releval Validate Message class
    //For ISO1100 class, the validation object is ISO1100Val
    m_validator = new ISO1100Val ();
}


//Definition of the ISO1100 Constructor

/* Destructor Name: ISO1100
 * Will release the meory occupied by the memebers of the class
 */

ISO1100 :: ~ISO1100()
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

char *ISO1100::getResponseType ()
{
	return "ISO1110";
}

char *ISO1100::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1100::getStaticRequestType ()
{
	return "ISO1100";
}

ISO8583Implementation *ISO1100::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;
	
/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1100 (mapSize);
	}
*/
	if (strcmp (mName, m_className) == 0)
	{
		retval = new ISO1100 (mapSize);
	}

	return retval;
}

static ISO1100 *exemplar1100 = 
	(ISO1100 *)ISO8583ClassFactory().addClass (new ISO1100 (64));
