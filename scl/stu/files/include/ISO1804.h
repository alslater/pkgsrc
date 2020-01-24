/*********************************************************************
*
*   File name:
*       ISO1804.h
*
*   Contents:
*       ISO1804
*
*   Description
*
*        This header file contains the class definitions and function declarations
*        for derived class for the network management message request object.
*        The class is instantiated when a specific network management request message
*        is received from the client application. The instantiation is done through
*        the ISO8583Message class only.
*
*
*   See Also:
*        Char_Util.h
*        Enumerations.h
*        ISO8583Message.h
*        ISOStatus.h
*        FieldMapElement.h
*        ISO1804.cpp
*        ISO1804Val.h
*
*
*   Created:
*       19 June Shubha Kumar
*
*   Modified:
*		26 June Shubha Kumar
*			-Add deSerialize()
*
***************************************************************************/
#ifndef ISO1804_H
#define ISO1804_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ISO8583Implementation.h"



/**************************************************************************
 *
 * CLASS NAME:          ISO1804
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1804 represents the lowest level object that holds the
 * actual message pertaining to the network management request of the ISO8583 message.
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


 class ISO1804 : public ISO8583Implementation
 {

	//Constructor, Destructor and Methods

	private:
		//Default Constructor
		ISO1804();

	public:
		//Constructor
		//The constructor will initialize the the base class with the "mapSize"
		//It is aslo responsible for initializing the FieldMapElement array
		ISO1804(int mapSize);

		//Destructor
		//This destrcutor will release the memory occupied by FieldMapElement array
		~ISO1804();

		//Methods
		//most of the methods call the base class methods for implementation

		char *getResponseType ();

		char *getRequestType ();

		static char *getStaticRequestType ();

		ISO8583Implementation *Make (char *mName, int mapSize);

};

#endif

