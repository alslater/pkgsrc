/*********************************************************************
*
*   File name:
*       ISO1110.h
*
*   Contents:
*       ISO1110
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
*        ISO1110.cpp
*
*
*   Created:
*       04 June 2001  Arun G.
*
*   Modified:
*		08 June 2001  Shubha Kumar
*					-Removed the attributes to the ISO8583Implementation class
*					-The implementation of the get and set methods moved to the base class
*		12 June 2001 Shubha Kumar
*					-Added the length argument to the get, set and deserialize methods
*
*       22 June 2001 Lonnie L. Filbrun
*                    Added the ability of serializing.
*
***************************************************************************/
#ifndef ISO1110_H
#define ISO1110_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ISO8583Implementation.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1110
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1110 represents the lowest level object that holds the
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


 class ISO1110 : public ISO8583Implementation
 {
	private:
		//Default Constructor
		ISO1110();

    //Constructor, Destructor and Methods
    public:

		//Constructor
       //The constructor will initialize the the base class with the "mapSize"
       //It is aslo responsible for initializing the FieldMapElement array
       ISO1110(int mapSize);

	   //Destructor
	   //This destrcutor will release the memory occupied by FieldMapElement array
	   ~ISO1110();

       //Methods

	   	char *getResponseType ();

		char *getRequestType ();

		static char *getStaticRequestType ();

		ISO8583Implementation *Make (char *mName, int mapSize);

};

#endif

