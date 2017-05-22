/*********************************************************************
*
*   File name:
*       ISO1230.h
*
*   Contents:
*       ISO1230
*
*   Description
*
*        This header file contains the class definitions and function declarations
*        for derived class for the ISO1230 object. The 1230 message is
*		 the financial funding acknowledgement. The instantiation is done through
*		 the ISO8583Message class only.
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
*        ISO1230.cpp
*
*
*   Created:
*       05 June 2001 Arun G.
*
*   Modified:
*		08 June 2001  Shubha Kumar
*					-Moved the attributes to the ISO8583Implementation class
*					-The implementation of teh get and set methods moved to the base class
*
*		14 June 2001 Arun G.
*					-Added the length argument to the get, set and deserialize methods
*
*       22 June 2001 Lonnie L. Filbrun
*                    Added the ability of serializing.
*
***************************************************************************/
#ifndef ISO1230_H
#define ISO1230_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ISO8583Implementation.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1230
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1230 represents the lowest level object that holds the
 * actual message pertaining to the Financial Funding Aknowledge of the ISO8583 message.
 * The class is concrete and instantiable. It is always instantiated
 * through the base class pointer and never directly.
 * Each bit supported by this message type is set as an element of the
 * FieldMapElement array.
 * The field and the message validations are taken care of through the respectives
 * classes.
 *
 **************************************************************************
 */


 class ISO1230 : public ISO8583Implementation
 {
	//Constructor, Destructor and Methods
	public:

		//Default Constructor
		ISO1230 ();

		//Constructor
		//The constructor will initialize the the base class with the "mapSize"
		//It is aslo responsible for initializing the FieldMapElement array
		ISO1230 (int mapSize);

		//Destructor
		//This destrcutor will release the memory occupied by FieldMapElement array
		~ISO1230 ();

		//Methods

		char *getResponseType ();

		char *getRequestType ();

		static char *getStaticRequestType ();

		ISO8583Implementation *Make (char *mName, int mapSize);

};

#endif

