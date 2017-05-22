/*********************************************************************
*
*   File name:
*       ISO1430.h
*
*   Contents:
*       ISO1430
*
*   Description
*
*        This header file contains the class definitions and function declarations
*        for derived class for the ISO1430 object. The 1430 message is used
*		 to transmit reversal advice acknowledgement.
*		 The instantiation is done through the ISO8583Reversal class only.
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
*        ISO1430.cpp
*
*
*   Created:
*       19 June 2001  Shubha Kumar
*
*   Modified:
*

*
***************************************************************************/
#ifndef ISO1430_H
#define ISO1430_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ISO8583Implementation.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1430
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1430 represents the lowest level object that holds the
 * actual message pertaining to the authorization reversal/card status
 * reversal/funding void Advice of the ISO8583 message.
 * The class is concrete and instantiable. It is always instantiated
 * through the 8583 base class pointer and never directly.
 * Each bit supported by this message type is set as an element of the
 * FieldMapElement array.
 * The field and the message validations are taken care of through the respectives
 * classes.
 *
 **************************************************************************
 */

 class ISO1430 : public ISO8583Implementation
 {
	//Constructor, Destructor and Methods
	public:

		//Default Constructor
		ISO1430();

		//Constructor
		//The constructor will initialize the the base class with the "mapSize"
		//It is aslo responsible for initializing the FieldMapElement array
		ISO1430(int mapSize);

		//Destructor
		//This destrcutor will release the memory occupied by FieldMapElement array
		~ISO1430();

		//Methods

		char *getResponseType ();

		char *getRequestType ();

		static char *getStaticRequestType ();

		ISO8583Implementation *Make (char *mName, int mapSize);

};

#endif

