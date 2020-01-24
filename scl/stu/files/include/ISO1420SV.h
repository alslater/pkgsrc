/*********************************************************************
*
*   File name:
*       ISO1420SV.h
*
*   Contents:
*       ISO1420SV
*
*   Description
*
*        This header file contains the class definitions and function declarations
*        for derived class for the ISO1420SV object. The 1420 message is used
*		 by the client application to transmit authorization reversal/card status
*		 reversal/funding void advice.
*		 The instantiation is done through the ISO8583Message class only.
*
*
*   See Also:
*        Char_Util.h
*        Enumerations.h
*        ISO8583Message.h
*        ISO8583Implementation.h
*        ISOStatus.h
*		 ISOField.h
*        FieldMapElement.h
*        ISO1420SV.cpp
*        ISO1420SVVal.h
*
*
*   Created:
*       31 May 2001 Arun G.
*
*   Modified:
*		08 June 2001  Shubha Kumar
*					-Moved the attributes to the ISO8583Implementation class
*					-The implementation of the get and set methods moved to the base class
*		14 June 2001 Shubha Kumar
*					-Added the length argument to get, set, and serialize, methods
*
*       22 June 2001 Lonnie L. Filbrun
*                    Added the ability of deSerializing.
*
***************************************************************************/
#ifndef ISO1420SV_H
#define ISO1420SV_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ISO8583Implementation.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1420SV
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1420SV represents the lowest level object that holds the
 * actual message pertaining to the authorization reversal/card status
 * reversal/funding void Advice of the ISO8583 message.
 * The class is concrete and instantiable. It is always instantiated
 * through the base class pointer and never directly.
 * Each bit supported by this message type is set as an element of the
 * FieldMapElement array.
 * The field and the message validations are taken care of through the respectives
 * classes.
 * The objects will also be able to serialize the data they hold into
 * an EBCDIC byte stream and also de-serialize the EBCDIC byte stream to extract
 * the data pertaining to the object. The serialized message would look like this:
 * | Message_Type | Bit_Map | Message Data |
 *
 **************************************************************************
 */


 class ISO1420SV : public ISO8583Implementation
 {

	//Constructor, Destructor and Methods
	private:

		//Default Constructor
		ISO1420SV();

	public:
		//Constructor
		//The constructor will initialize the the base class with the "mapSize"
		//It is aslo responsible for initializing the FieldMapElement array
		ISO1420SV(int mapSize);

		//Destructor
		//This destrcutor will release the memory occupied by FieldMapElement array
		~ISO1420SV();

		//Methods

		char *getResponseType ();

		char *getRequestType ();

		static char *getStaticRequestType ();

		ISO8583Implementation *Make (char *mName, int mapSize);

};

#endif

