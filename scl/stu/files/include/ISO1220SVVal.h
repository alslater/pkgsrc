/*********************************************************************
*
*   File name:
*       ISO1220SVVal.h
*
*   Contents:
*       ISO1220SVVal class
*
*   Description
*
*        This header file contains the class definition and function declarations
*        for the derived class of ValidateMessage class, the ISO1220SVVal.
*        The class is instantiated when an ISO1220SV is validated.
*
*
*   See Also:
*        ISO8583Message.h
*        ISOStatus.h
*        FieldMapElement.h
*        ValidateMessage.h
*		 ISO1220SV.h
*        ISO1220SVVal.cpp
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
#ifndef ISO1220SVVAL_H
#define ISO1220SVVAL_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ValidateMessage.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1220SVVal
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1220SVVal is the class used for validating the ISO1220SVMessage object.
 * It contains functions to perform validations on individual fields of the
 * message object.
 *
 **************************************************************************
 */

 class ISO1220SVVal : public ValidateMessage
 {

    //Constructor, Destructor and Methods
    public:

        //Default Constructor
		ISO1220SVVal();

		//Destructor
		~ISO1220SVVal();

		//Method
      	bool performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef);

	//Private methods
	private :

		bool checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPAN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkProcessingCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkTransAmount(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkFunctionCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkDate(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkTransCurrencyCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkAcceptorBusinessCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkSEN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkCountryCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkMerchantType(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPOSData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);
};

#endif

