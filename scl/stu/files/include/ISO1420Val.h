/*********************************************************************
*
*   File name:
*       ISO1420Val.h
*
*   Contents:
*       ISO1420Val class
*
*   Description
*
*        This header file contains the class definition and function declarations
*        for the derived class of ValidateMessage class, the ISO1420Val.
*        The class is instantiated when an ISO1420Reversal message is validated.
*
*
*   See Also:
*        ISO8583Message.h
*        ISOStatus.h
*        FieldMapElement.h
*        ValidateMessage.h
*		 ISO1420.h
*        ISO1420Val.cpp
*
*
*   Created:
*       20 June 2001 Arun G.
*
*   Modified:
*
*
*
***************************************************************************/
#ifndef ISO1420VAL_H
#define ISO1420VAL_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ValidateMessage.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1420Val
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1420Val is the class used for validating the ISO1420 message.
 * It contains functions to perform validations on individual fields of the message object.
 *
 **************************************************************************
 */

 class ISO1420Val : public ValidateMessage
 {

    //Constructor, Destructor and Methods
    public:

        //Default Constructor
		ISO1420Val();

		//Destructor
		~ISO1420Val();

		//Method
      	bool performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef);

	//Private methods
	private :

		bool checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPAN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkProcessingCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkTransAmount(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkDate(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkTransCurrencyCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkMerchantType(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkCountryCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPOSData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkSEN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

};

#endif

