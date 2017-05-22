/*********************************************************************
*
*   File name:
*       ISO1100Val.h
*
*   Contents:
*       ISO1100Val class
*
*   Description
*
*        This header file contains the class definition and function declarations
*        for the derived class of ValidateMessage class, the ISO1100Val.
*        The class is instantiated when an ISO1100 message is
*		 validated.
*
*
*   See Also:
*        ISO8583Message.h
*        ISOStatus.h
*        FieldMapElement.h
*        ValidateMessage.h
*		 ISO1100.h
*        ISO1100Val.cpp
*
*
*   Created:
*       21 June 2001 Arun G.
*
*   Modified:
*
*
*
***************************************************************************/
#ifndef ISO1100VAL_H
#define ISO1100VAL_H


//specific inlcudes
#include "ISOStatus.h"
#include "FieldMapElement.h"
#include "ValidateMessage.h"


/**************************************************************************
 *
 * CLASS NAME:          ISO1100Val
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * An ISO1100Val is the class used for validating the ISO1100
 * message. It contains functions to perform validations on individual fields of the
 * message object.
 *
 **************************************************************************
 */

 class ISO1100Val : public ValidateMessage
 {

    //Constructor, Destructor and Methods
    public:

        //Default Constructor
		ISO1100Val();

		//Destructor
		~ISO1100Val();

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

		bool checkFunctionCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkMessageReasonCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkAcceptorBusinessCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkSEN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkCtrlInfo(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);

		bool checkPrivateData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);


};

#endif

