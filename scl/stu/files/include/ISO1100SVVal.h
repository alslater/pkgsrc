/*********************************************************************
*
*   File name:
*       ISO1100SVVal.h
*
*   Contents:
*       ISO1100SVVal class
*
*   Description
*
*        This header file contains the class definition and function declarations
*        for the derived class of ValidateMessage class, the ISO1100SVVal.
*        The class is instantiated when an ISO1100SV message is
*		 validated.
*
*
*   See Also:
*        ISO8583Message.h
*        ISOStatus.h
*        FieldMapElement.h
*        ValidateMessage.h
*		 ISO1100SV.h
*        ISO1100SVVal.cpp
*
*
*   Created:
*       07 June 2001 Arun G.
*
*   Modified:
*
*
*
***************************************************************************/
#ifndef ISO1100SVVAL_H
#define ISO1100SVVAL_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ValidateMessage.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1100SVVal
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1100SVVal is the class used for validating the ISO1100SV
 * message. It contains functions to perform validations on individual fields of the
 * message object.
 *
 **************************************************************************
 */

 class ISO1100SVVal : public ValidateMessage
 {

    //Constructor, Destructor and Methods
    public:

        //Default Constructor
		ISO1100SVVal();

		//Destructor
		~ISO1100SVVal();

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

		bool checkFunctionCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkAcceptorBusinessCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkSEN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkCtrlInfo(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPrivateData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPOSData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

};

#endif

