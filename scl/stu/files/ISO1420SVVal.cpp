/*********************************************************************
*
*   File name:
*       ISO1420SVVal.cpp
*
*   Contents:
*       ISO1420SVVal class functions
*
*   Description
*
*        This file contains the implementations of the functions in ISO1420SVVal
*        class. These functions validate the ISO1420SV.
*
*
*   See Also:
*        ISO1420SVVal.h   
*        
*
*   Created:
*       11 June 2001 Arun G.
*
*   Modified:
*	    21 June 2001 Shubha K
*			-Added checkPOSData().
*			-remove checkDate() form performValidation()
*
*		06 July 2001 Arun G
*			-Modified performValidation function to check for PAN validation alone
*			-Added a length check of 15 for PAN validation
*
***************************************************************************/

//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//C header file
extern "C" 
{ 
	#include "ISOHash.h"
} 

//specific header files
#include "CharUtility.h"
#include "Enumerations.h"
#include "FieldValidation.h"
#include "ISO1420SVVal.h"


//Default Constructor
ISO1420SVVal::ISO1420SVVal()
{	}
	
//Destructor
ISO1420SVVal::~ISO1420SVVal()
{	}

//Methods

/*	Name	:	performValidation
 *
 * 	Arguments:
 * 		fieldMap[] : Pointer to the field map array.
 *		size :	The size of the bit map.  (64 or 128).
 *		statusRef: [Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *	boolean : Indicates status of operation.  TRUE (1) indicates success and FALSE (0) indicates failure.  Client App will have to check the ISOStatus object for more details in case if the return value is FALSE (0).
 *
 *  Implementation Details:
 *  - Call the private methods in a sequence as specified in the business rules.
 *  - Check the status of the call to each private method.  If any of the private validation method fails return error status.
 *  - Return success status if all the private validation methods return success as specified in the business rules.
 *  - The sequence of call to the private methods are as follows:  
 *		1. checkRequiredFields()
 *		2. checkPAN()
 *		3. checkMerchantType()
 *		4. checkCountryCode()
 *		5. checkPOSData()
 *		6. checkSEN()
 *		7. checkTransCurrencyCode()
 *		8. checkDate()
 *		9. checkFunctionCode()
 *
 */
bool ISO1420SVVal::performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	/*
	//check required fields
	status = checkRequiredFields(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}
	*/

	//check Permanent Account Number
	status = checkPAN(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	/*
	//check Merchant Type
	status = checkMerchantType(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Country Code
	status = checkCountryCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check POS data
	status = checkPOSData(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Service Establishment Number
	status = checkSEN(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Currency code
	status = checkTransCurrencyCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}
	
	//check Function code
	status = checkFunctionCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}
	*/
	
	return status;
}


/*	Name :
 *		checkRequiredFields(FieldMapElement* fieldMap[], int mapSize, ISOStatus* statusRef) 
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  
 *					Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		Checks if the following bit positions are set: Bit-2, Bit-3,Bit-11, Bit-12, Bit-24, 
 *		Bit-42, Bit-49 and Bit-56. If all the bits are set, return TRUE.  Else return FALSE 
 *		with the ISOStatus object updated to reflect the failure.
 *	
 */	
bool ISO1420SVVal::checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i=0;
	//check each fieldMap array element
	for(i = 1;i < mapSize; i++)
	{
		//Check the bit positions 2,3,11,12,24,42,49,56.
		//the index position of the array starts from 0
		switch(i)
		{
			case 1:
			case 2:
			case 10:
			case 11:
			case 23:
			case 41:
			case 48:
			case 55:
				//if the field has not been set, return false
				if(fieldMap[i]->m_fieldPointer == NULL)
					status = false;
				else
					status=fieldMap[i]->m_isSet;
				break;

		}//end of switch
		if(status == false)
		{
			statusRef.setStatus(false);
			statusRef.setResultCode(VALIDATION_FAILED);

			//error message string.
			char errMsg[] = "Falilure - Required/Mandatory Field Not Set";

			//call the method to append the bit position to the error message string.
			char* newErrMsg = NULL;
			newErrMsg = CharUtility::createErrMessage(i+1,errMsg);
			
			if(newErrMsg!=NULL)
			{
				//set this new message to the ISOStatus object
				statusRef.setResultDesc(newErrMsg);


				//delete the local pointer to free the memory allocated in the createErrMessage method.
				delete newErrMsg;
				break;
			}
			else
			{
				status = false;
				statusRef.update (false, ENOMEM, "Failure - 1420 Message validate - Insufficient Memory");
			}
		}
	}// end of for

	return status;
}


/*	Name :
 *		checkPAN(FieldMapElement* fieldMap[], int mapSize, ISOStatus* statusRef) 
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		Call the base class method for implementation.
 *
 */	
bool ISO1420SVVal::checkPAN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	//status variable
	bool status = false;

	//check for the field - if set
	if(fieldMap[1] == NULL)
	{
		status = false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - PAN - Field not set");
	}
	else
	{
		//check if data has been set
		if(fieldMap[1]->m_isSet == false)
		{
			status = false;
			statusRef.update (false, VALIDATION_FAILED, "Failure - PAN - Field data not set");
		}
		else
		{
			//call the base class implementation if the length of the field is 15
			if(fieldMap[1]->m_fieldPointer->getSize() == 15)
				status = ValidateMessage::checkPAN(fieldMap, mapSize, statusRef);
			else
				status = true;
		}
	}

	return status;
}



/*
 *	Name :
 *		checkMerchantType(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		1. Check Bit-18. Use the Merchant type hash method. 
 *		2. Call the base class method for implementation.
 *
 */
bool ISO1420SVVal::checkMerchantType(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkMerchantType(fieldMap, mapSize, statusRef));
}


/*
 *	Name :
 *		checkCountryCode(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  
 *					Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		1. Check Bit-19. Use the Country Code hash method.
 *		2. Call the base class method for implementation.
 *
 */
bool ISO1420SVVal::checkCountryCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkCountryCode(fieldMap, mapSize, statusRef));

}


/*
 *	Name :
 *		checkPOSData(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		1. Check Bit-22. 
 *		2. Call the base class method for implementation
 *
 */

bool ISO1420SVVal::checkPOSData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return ValidateMessage::checkPOSData(fieldMap, mapSize, statusRef);
}


/*
 *	Name :
 *		checkSEN(FieldMapElement* fieldMap[], int mapSize, ISOStatus* statusRef) 
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		1. This is a check for bit position 42 - Service Establishment number.
 *		2. Call the base class method for implementation		
 *
 */
bool ISO1420SVVal::checkSEN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkSEN(fieldMap, mapSize, statusRef));
}



/*
 *	Name :
 *		checkTransCurrencyCode(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		1. Check Bit-49. Use the currency type hash method. 
 *		2. Call the base class method for implementation.
 *
 */
bool ISO1420SVVal::checkTransCurrencyCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkTransCurrencyCode(fieldMap, mapSize, statusRef));
}	



/*
 *	Name :
 *		checkDate(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		1. Check Bit-13 and Bit-14.  
 *		2. Both bits required if Track-2 data is not available.
 *		3. If the validation is correct, return TRUE.  Else return FALSE with the 
 *		   ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1420SVVal::checkDate(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	//return ValidateMessage::checkCountryCode(fieldMap, mapSize, statusRef);
	return true;
}



/*
 *	Name :
 *		checkFunctionCode(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
 *
 *	Arguments:
 *		fieldMap[] :	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		1. Check Bit-24. 
 *		2. The following are the only valid values for 1420 message type: 400,444
 *		3. If the validation is correct, return TRUE.  Else return FALSE with the ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1420SVVal::checkFunctionCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i=0;
	//array of valid function codes
	char funCode[][4] ={ "400",
						 "444",
						};
		
	//length of the function code array
	int funCodeArray = 2;

	//check if Null value
	if(fieldMap[23]->m_fieldPointer==NULL)
	{
		status= false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Function Code Not Set");
	}
	else
	{
		//length pointer
		//memory is released at the end of the function
		int* dataLen = new int;

		if(dataLen==NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Function Code - Insufficient Memory");
		}
		else
		{
			//get the data from the field
			//memory is released at the end of the function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[23]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				//assume the default function code of 100
				status = true;
			}
			else
			{
				//append a null character to the data for checking in a temp array
				//memory deleted at the ned of the function
				unsigned char* tempPtr = NULL;
				tempPtr = new unsigned char[*dataLen+1];
				
				if(tempPtr == NULL)
				{
					status = false;
					statusRef.update (false, ENOMEM, "Failure - Function Code - Insufficient Memory");
				}
				else
				{
					memset(tempPtr, 0, *dataLen+1);
					for(i=0; i<*dataLen; i++)
					{
						tempPtr[i] = dataPtr[i];
					}
					tempPtr[i] = '\0';
					
					//check for valid processing codes from the array
					for(i=0; i<funCodeArray; i++)
					{
						if(strcmp((char *)tempPtr, funCode[i]) == 0)
						{
							status = true;
							break;
						}
					}

					if(status==false)
					{
						statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Function Code");
					}
					
					//release memory allocated to tempPtr for null terminated string
					delete [] tempPtr;
				}
			}
			//release memory allocated to out parameter pointer for length
			delete dataLen;
		}
	}

	return status;
}













