/*********************************************************************
*
*   File name:
*       ISORequest.h
*
*   Contents:
*       ISORequest
*
*   Description
*
*        This header file contains the class definitions and function declarations
*        for derived class for the authorization message request object.
*        The class is instantiated when a specific authorization request message
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
*        ISORequest.cpp
*
*   Created:
*		21 June 2001 Lonnie Filbrun
*
***************************************************************************/
#ifndef ISOREQUEST_H
#define ISOREQUEST_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ISO8583Implementation.h"



/**************************************************************************
 *
 * CLASS NAME:          ISORequest
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISORequest represents the lowest level object that holds the
 * actual message pertaining to the Authorization request of the ISO8583 message.
 * The class is concrete and instantiable. It is always instantiated
 * through the base class pointer and never directly.
 * Each bit supported by this message type is set as an element of the
 * FieldMapElement array.
 * The field and the message validations are taken caer of through the respectives
 * classes.
 * The objects will also be able to serialize the data they hold into
 * an EBCDIC byte stream and also de-serialize the EBCDIC byte stream to extract
 * the data pertaining to the object. The serialized message would look like this:
 * | Message_Type | Bit_Map | Message Data |
 *
 **************************************************************************
 */


 class ISORequest : public ISO8583Implementation
 {

	//Constructor, Destructor and Methods

	private:
		//Default Constructor
		ISORequest();

	public:
		//Constructor
		//The constructor will initialize the the base class with the "mapSize"
		ISORequest(int mapSize);

		ISORequest(char *msgType, int mapSize);

		//Destructor
		//This destrcutor will release the memory occupied by FieldMapElement array
		~ISORequest();

		//Methods
		//most of the methods call the base class methods for implementation

		char* getResponseType();

		char* getRequestType();

		static char* getStaticRequestType();

		ISO8583Implementation * Make( char *mName, int mapSize );

};

#endif

