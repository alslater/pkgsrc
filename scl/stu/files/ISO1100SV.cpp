/*********************************************************************
*
*   Module:
*       ISO1100SV.cpp
*
*   Contents:
*       Implementation of the ISO1100SV class constructor and methods
*       
*   Description
*        It insatantiates the 1100 Stored values message in the relevant bit
*        positions. The set and get fields work on the FieldMapElement array
*        to write the data to the actual ISOField derived classes.
*        The serialize methods converts the data in the fields to EBCDIC byte
*        stream.
*
*   See Also:
*       ISO1100SV.h
*
*
*   Created:
*		21 May 2001 Shubha Kumar
*
*   Modified:
*		08 June 2001 Shubha
*				-This now inherits form the ISO8583Implementation class.
*				-Changed the constructor to remove the mapsize initialization to the base class.
*				-All the implemented methods moved to the base class.
*				-The only method implemented is the getResponseType().
*
*
*       22 June 2001 Lonnie L. Filbrun
*                    Added the ability of deSerializing.
*
*
*		06 July 2001 Shubha Kumar
*				- Moved the default initialization of FieldMapElement array to the base class constructor
*				- Added code to reset the value of isRequired field of the FieldMapElement
*				  according to the SV guide for ISO1100 message
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "Enumerations.h"
#include "ISO1100SV.h"
#include "ISO1100SVVal.h"
#include "ClassFactory.h"

#define ISO1100SV_CLASS_NAME  "ISO1100SV"

//Definitions for the ISO1100SV Constructor and methods
//Default Constructor
ISO1100SV :: ISO1100SV()
{
}

//Definition of the ISO1100SV Constructor

/* Constructor Name: ISO1100SV
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

ISO1100SV :: ISO1100SV(int mapSize) : ISO8583Implementation("1100", mapSize)
{
    m_className = ISO1100SV_CLASS_NAME;

	//set the isRequired field of all the supported bits 
	//with the option specific to this message
	//Bit positions 0 and 1 are reserved
	//The bit position 0 for the message starts from the secondary bit map

    //[0]
		
	//Setting File Position - 2 (Primary Account Number)
	m_fieldMap[1]->m_isRequired = REQUIRED;	

    //Setting File Position - 3 (Processing Code)
	m_fieldMap[2]->m_isRequired = REQUIRED;

    //Initializing File Position - 4 (Transaction Amount)
	m_fieldMap[3]->m_isRequired = CONDITIONAL;

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
	m_fieldMap[12]->m_isRequired = CONDITIONAL;

    //Setting File Position - 14 (Card Expiration Date)
	m_fieldMap[13]->m_isRequired = CONDITIONAL;

	//[14]
	//[15]
	//[16]

    //Setting File Position - 18 (Merchant Type)
	m_fieldMap[17]->m_isRequired = OPTIONAL;

    //Setting File Position - 19 (Acquiring Institution Country Code)
	m_fieldMap[18]->m_isRequired = OPTIONAL;

	//[19]
	//[20]

    //Setting File Position - 22 (Point of Service Data)
	m_fieldMap[21]->m_isRequired = REQUIRED;

	//[22]

    //Setting File Position - 24 (Function Code)
	m_fieldMap[23]->m_isRequired = REQUIRED;

	//[24]

    //Setting File Position - 26 (Card Acceptior Business Code)
	m_fieldMap[25]->m_isRequired = REQUIRED;

	//[25]
	//[26]
	//[27]
	//[28]

    //Setting File Position - 30 (Original Amounts)
	m_fieldMap[29]->m_isRequired = OPTIONAL;

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

    //Setting File Position - 39 (Action Code)
	m_fieldMap[38]->m_isRequired = OPTIONAL;

	//[39]

    //Setting File Position - 41 (Card Acceptor Terminal Identification)
	m_fieldMap[40]->m_isRequired = OPTIONAL;

    //Setting File Position - 42 (Card Acceptor Identification Code)
	m_fieldMap[41]->m_isRequired = REQUIRED;

    //Setting File Position - 43 (Card Acceptor Name/Location)
	m_fieldMap[42]->m_isRequired = OPTIONAL;

    //Setting File Position - 44 (Additional Reaponse Data)
	m_fieldMap[43]->m_isRequired = OPTIONAL;

    //Setting File Position - 45 (Track 1 Data)
	m_fieldMap[44]->m_isRequired = OPTIONAL;

	//[45]
	//[46]

    //Setting File Position - 48 (Addtional Demographic Data)
	m_fieldMap[47]->m_isRequired = OPTIONAL;

    //Setting File Position - 49 (Transaction Currency Code)
	m_fieldMap[48]->m_isRequired = REQUIRED;

	//[49]
	//[50]
	//[51]

    //Setting File Position - 53 (Security Related Control Information)
	m_fieldMap[52]->m_isRequired = CONDITIONAL;

    //Setting File Position - 54 (Additional Amount)
	m_fieldMap[53]->m_isRequired = OPTIONAL;

	//[54]
    //[55]
	//[56]
	//[57]
	//[58]
	//[59]
	//[60]

    //Setting File Position - 62 (Private Use Data)
	m_fieldMap[61]->m_isRequired = OPTIONAL;

    //Setting File Position - 63 (Private Data)
	m_fieldMap[62]->m_isRequired = CONDITIONAL;

	//[63]

    //Initialize the validation object pointer with the releval Validate Message class
    //For ISO1100SV class, the validation object is ISO1100SVVal
    m_validator = new ISO1100SVVal ();
}


//Definition of the ISO1100SV Constructor

/* Destructor Name: ISO1100SV
 * Will release the memory occupied by the memebers of the class
 */

 ISO1100SV :: ~ISO1100SV()
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

char *ISO1100SV::getResponseType ()
{
	return "ISO1110";
}

char *ISO1100SV::getRequestType ()
{
	return getStaticRequestType ();
}

char *ISO1100SV::getStaticRequestType ()
{
	return "ISO1100SV";
}

ISO8583Implementation *ISO1100SV::Make (char *mName, int mapSize)
{
	ISO8583Implementation *retval = 0;
	
/*
	if (strcmp (mName, getStaticRequestType ()) == 0)
	{
		retval = new ISO1100SV (mapSize);
	}
*/

	if (strcmp (mName, m_className) == 0)
	{
		retval = new ISO1100SV (mapSize);
	}

    return retval;
}

static ISO1100SV *exemplar1100SV = 
	(ISO1100SV *)ISO8583ClassFactory().addClass (new ISO1100SV (64));

