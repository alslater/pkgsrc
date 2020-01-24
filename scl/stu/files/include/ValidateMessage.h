/*********************************************************************
*
*   Module:
*       ValidateMessage.h
*
*   Contents:
*       ValidateMessage.class
*
*   Description
*
*       This header file contains the ValidateMessage class
*
*   See Also:
*
*
*
*   Created:
*		22 May 2001	Arun G.
*
*   Modified:
*		11 June 2001 Shubha Kumar
*			- performValidation and checkRequiredFields to be pure virtual
*			- All the other method sto have implementation here
*			- The methods specific to a class will have implementation there
*			   and methods which check specific values like the processing code,
*			   will override the base class implementation, if there is any.
*
*
*
**********************************************************************/

#ifndef VALIDATEMESSAGE_H
#define VALIDATEMESSAGE_H

#include "STU_platform.h"

//specific header fields
#include "ISOStatus.h"
#include "FieldMapElement.h"

class LINKDLL ValidateMessage
{

/***************************************************************************
 * CLASS NAME:          ValidateMessage
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * The class ValidateMessage is a base class providing function signatures
 * for the validation methods. The Derived class should implement all the
 * virtual methods and give their own implemention for the validation appropriate
 * to the message type.
 *
 **************************************************************************
 */
public:

	//constructor
	/*  Name: ValidateMessage
	 *  Arguments:
	 *
	 *  Return Type:
	 */

	ValidateMessage();

	//desstructor
	/*  Name: ~ValidateMessage
	 *  Arguments:
	 *
	 *  Return Type:
	 */

	virtual ~ValidateMessage();


	//public functions

	/*  Name: performValidation - this is a pure virtual function
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: boolean
	 */
	virtual bool performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef) = 0;


protected:
	//pure virtual functions
	/*  Name: checkRequiredFields - this is a pure virtual function
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	virtual bool checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef) = 0;


	//implemented functions

	/*  Name: checkProcessingCode - this is a pure virtual function
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkProcessingCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);


	/*  Name: checkTransAmount - this is a pure virtual function
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkTransAmount(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);


	/*  Name: checkFunctionCode - this is a pure virtual function
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkFunctionCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);



	/*  Name: checkPAN
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkPAN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);


	/*  Name: checkDate
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkDate(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);



	/*  Name: checkTransCurrencyCode
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkTransCurrencyCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);


	/*  Name: checkSEN
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkSEN(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);


	/*  Name: checkMerchantType
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type:
	 */
	bool checkMerchantType(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);


	/*  Name: checkCountryCode
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkCountryCode(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);


	/*  Name: checkPOSData
	 *  Arguments:
	 *		fieldMap[]: points to FieldMapElement object
	 *		mapSize: indicates size of the fieldMap[] array
	 *		statusRef: reference to the ISOStatus object
	 *
	 *   Return Type: bool
	 */
	bool checkPOSData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef);
};

#endif



