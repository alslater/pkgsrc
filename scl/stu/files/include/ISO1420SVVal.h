/*********************************************************************
*
*   File name:
*       ISO1420SVVal.h
*
*   Contents:
*       ISO1420SVVal class
*
*   Description
*
*        This header file contains the class definition and function declarations
*        for the derived class of ValidateMessage class, the ISO1100AuthValidation.
*        The class is instantiated when an ISO1100SVAuthorization message is
*		 validated.
*
*
*   See Also:
*        ISO8583Message.h
*        ISOStatus.h
*        FieldMapElement.h
*        ValidateMessage.h
*		 ISO1420SV.h
*        ISO1420SVVal.cpp
*
*
*   Created:
*       11 June 2001 Arun G.
*
*   Modified:
*
*
*
***************************************************************************/
#ifndef ISO1420SVVAL_H
#define ISO1420SVVAL_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ValidateMessage.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1420SVVal
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1420SVVal is the class used for validating the ISO1420SV message.
 * It contains functions to perform validations on individual fields of the
 * message object.
 *
 **************************************************************************
 */

 class ISO1420SVVal : public ValidateMessage
 {

    //Constructor, Destructor and Methods
    public:

        //Default Constructor
		ISO1420SVVal();

		//Destructor
		~ISO1420SVVal();

		//Method
      	bool performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef);

	//Private methods
	private :

		bool checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPAN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkSEN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkTransCurrencyCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkDate(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkFunctionCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkCountryCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkMerchantType(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPOSData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);
};

#endif

