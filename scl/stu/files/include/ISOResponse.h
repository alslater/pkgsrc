/*********************************************************************
*
*   File name:
*       ISOResponse.h
*
*   Contents:
*       ISOResponse
*
*   Description
*
*        This header file contains the class definitions and function declarations
*        for derived class for the authorization message response object. The class
*        is instantiated for a specific authorization response message by the client
*        application. The instantiation is done through the ISO8583Message class only.
*
*
*   See Also:
*        Char_Util.h
*        Enumerations.h
*        ISO8583Message.h
*        ISO8583Implementation.h
*        ISOStatus.h
*        FieldMapElement.h
*        ISOResponse.cpp
*
*   Created:
*		21 June 2001 Lonnie Filbrun
*
***************************************************************************/
#ifndef ISORESPONSE_H
#define ISORESPONSE_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ISO8583Implementation.h"


/**************************************************************************
 *
 * CLASS NAME:          ISOResponse
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISOResponse represents the lowest level object that holds the
 * actual message pertaining to the Authorization response of the ISO8583 message.
 * The class is concrete and instantiable. It is always instantiated
 * through the base class pointer and never directly.
 * Each bit supported by this message type is set as an element of the
 * FieldMapElement array.
 * The field and the message validations are taken care of through the respectives
 * classes.
 * The objects will also be able to de-serialize the EBCDIC byte stream to extract
 * the data pertaining to the object.
 *
 **************************************************************************
 */


 class ISOResponse : public ISO8583Implementation
 {
	private:
		//Default Constructor
		ISOResponse();

    //Constructor, Destructor and Methods
    public:

		//Constructor
       //The constructor will initialize the the base class with the "mapSize"
       ISOResponse(int mapSize);

	   ISOResponse(char *msgType, int mapSize);

	   //Destructor
	   //This destrcutor will release the memory occupied by FieldMapElement array
	   ~ISOResponse();

       //Methods

   	   char* getResponseType();

	   char* getRequestType();

	   static char* getStaticRequestType();

	   ISO8583Implementation * Make( char *mName, int mapSize );

};

#endif

