/*********************************************************************
*
*   File name:
*       ISO1420Val.cpp
*
*   Contents:
*       ISO1420Val class functions
*
*   Description
*
*        This file contains the implementations of the functions in ISO1420Val
*        class. These functions validate the ISO1420Reversal message.
*
*
*   See Also:
*        ISO1420Val.h   
*        
*
*   Created:
*       20 June 2001 Arun G.
*
*   Modified:
*		26 June 2001 Arun G
*			-Cleaned up code for pointers and memory allocation
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
#include "ISO1420Val.h"


//Default Constructor
ISO1420Val::ISO1420Val()
{	}
	
//Destructor
ISO1420Val::~ISO1420Val()
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
 *		3. checkProcessingCode()
 *		4. checkTransAmount()
 *		5. checkDate()
 *		6. checkMerchantType()
 *		7. checkCountryCode()
 *		8. checkPOSData()
 *		9. checkSEN()
 * 		10. checkTransCurrencyCode()
 *
 */
bool ISO1420Val::performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	//1. check required fields
	status = checkRequiredFields(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//2. check Permanent Account Number
	status = checkPAN(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//3. check Processing code
	status = checkProcessingCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//4. check Transaction amount
	status = checkTransAmount(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//5. check Effective and Expiry dates
	status = checkDate(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//6. check Merchant type code
	status = checkMerchantType(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//7. check Country code
	status = checkCountryCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//8. check POS Data code
	status = checkPOSData(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//9. check Service Establishment Number
	status = checkSEN(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//10. check Currency code
	status = checkTransCurrencyCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

return status;

}


/*	Name :
 *		checkRequiredFields(FieldMapElement* fieldMap[], int mapSize, ISOStatus* statusRef) 
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
 *		Checks if the following bit positions are set: 2,3,4,11,12,19,22,42,49 and 56 
 *		If all the bits are set, return TRUE.  Else return FALSE with the ISOStatus 
 *		object updated to reflect the failure.
 *	
 */	
bool ISO1420Val::checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i = 0;

	//check each fieldMap array element
	for(i = 1;i < mapSize; i++)
	{
		//Check the bit positions 2,3,4,11,12,19,22,42,49 and 56
		//the index position of the array starts from 0
		switch(i)
		{
			case 1:
			case 2:
			case 3:
			case 10:
			case 11:
			case 18:
			case 21:
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
			char errMsg[] = "Failure - Required/Mandatory Field Not Set";

			//call the method to append the bit position to the error message string.
			char* newErrMsg = NULL;
			newErrMsg = CharUtility::createErrMessage(i+1,errMsg);

			if(newErrMsg == NULL)
			{
				statusRef.setResultCode(ENOMEM);
				statusRef.setResultDesc("Failure - Check Required Fields - Insufficient memory");
			}
			else
			{
				//set this new message to the ISOStatus object
				statusRef.setResultDesc(newErrMsg);

				//delete the local pointer to free the memory allocated in the createErrMessage method.
				delete newErrMsg;
			}

			break;
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
bool ISO1420Val::checkPAN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkPAN(fieldMap, mapSize, statusRef));
}



/*
 *	Name :
 *		checkProcessingCode(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
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
 *		Checks the bit position 3 which can have only one of the values: 004000
 *		If the processing code is valid, return TRUE else return FALSE with the ISOStatus
 *		object updated to reflect the failure
 *
 */
bool ISO1420Val::checkProcessingCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	//check if Null value
	if(fieldMap[2]->m_fieldPointer==NULL)
	{
		status = false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Processing Code - Field not set");
	}
	else
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;

		if (dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Processing Code - Insufficient memory");
		}
		else
		{
			//initialize dataLen
			*dataLen = 0;

			//get the data from the field
			//memory released at the end of this function
			unsigned char* dataPtr=NULL;
			dataPtr=fieldMap[2]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Processing Code - No field data retrieved");
			}
			else
			{
				//check for valid processing codes
				long processCode = 0;
				processCode = atol((char *)dataPtr);
				switch(processCode)
				{
					case AUTHORIZATION_REQUEST_REVERSAL:
						status = true;
						break;
					default:
						status = false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Processing Code");
						break;
				}
			}//end of dataPtr if-else

			//release memory allocated to the out parameter of length
			delete dataLen;

		}//end of dataLen if-else
	}//end of fieldMap if-else

	return status;
}


/*
 *	Name :
 *		checkTransAmount(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
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
 *		1. Check for Mandatory field (Bit-4).  
 *		2. Determine decimal point by the transaction currency code field (Bit-49).
 *		3. If both conditions are satisfied, return TRUE.  Else return FALSE with the 
 *		   ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1420Val::checkTransAmount(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i = 0;
	

	if(fieldMap[3]->m_fieldPointer== NULL)
	{
		status = false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - Field not set");
	}
	else
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;

		//check for the bit position 4 
		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Transaction Amount - Insufficient Memory");
		}
		else
		{
			//initialize dataLen
			*dataLen = 0;

			//check bit 49 for the decimal point for currency code
			//by calling the hash function
			//memory released at the end of this function
			unsigned char* bit49data=NULL;
			bit49data = fieldMap[48]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);
			
			if(bit49data==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - No field data retrieved for bit position 49");
			}
			else
			{
				//get the length of the currency code
				int len = *dataLen;
				unsigned char* dataPtr = NULL; 

				//get the data from the field - bit position 4
				//memory is released at the end of this function
				*dataLen = 0;
				dataPtr=fieldMap[3]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

				if(dataPtr == NULL)
				{
					status = false;
					statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - No field data retrieved for bit position 4");
				}
				else
				{
					//allocate memory for a null terminated string for the currency code
					//memory released at the end of the function
					unsigned char * tempData = NULL;
					tempData = new unsigned char[len+1];
					
					if(tempData == NULL)
					{
						status = false;
						statusRef.update (false, ENOMEM, "Failure - Transaction Amount - Insufficient Memory");
					}
					else
					{
						//set each position to null
						memset(tempData, 0, len+1);

						//copy the data received from bit 49 to the temp pointer
						for(i=0; i<len; i++)
						{
							tempData[i] = bit49data[i];
						}

						//call the hash function
						//memory to be released at the end of the function
						const IsoCurrencyCode* currencyCode = NULL;
						currencyCode = isoCurrencyLookup((char *)tempData,3);

						//check if currency code is available
						if(currencyCode==NULL)
						{	
							status = false;
							statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - Invalid currency code");
						}
						else
						{
							//get the maximum allowed decimal digits
							int maxDecPoints = 0;
							maxDecPoints = currencyCode->decimalPoint;
					
							//store the number of 0s used for left padding the data
							int zeroCount = 0;

							//check for the number of left padded 0s
							for(i=0; i<*dataLen-maxDecPoints; i++)
							{
								if(dataPtr[i] == '0')
									zeroCount++;
							}

							//check if the complete data is zero padded till the allowed decimal digits position
							if(zeroCount == (*dataLen-maxDecPoints))
							{
								status = false;
								statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Transaction Amount");
							}
							else
								status = true;
						}//end of currencyCode if-else

						//release memory allocated to the temp array for a null terminated string
						delete tempData;
					}// end of tempData if-else
				}//end of dataPtr if-else
			}//end of bit49data if-else

			//release memory allocated to the out parameter pointer for length
			delete dataLen;	
		}// end of dataLen if-else
	}//end of fieldMap if-else

	return status;		
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
 *		1. Check for bit 14 only.
 *		2. The data is optional if Track 1 or Track 2 data is present
 *
 */
bool ISO1420Val::checkDate(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	if(fieldMap[34]->m_isSet == false && fieldMap[44]->m_isSet == false)
	{
		// check if both bit 13 and bit 14 are set
		status = fieldMap[13]->m_isSet ;
	}			
	else
		status = true;

	//update the ISOStatus object
	if(status==false)
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Date Validation - Bits 13 or 14 not set.");
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
bool ISO1420Val::checkMerchantType(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1420Val::checkCountryCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  
 *					Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		1. Check Bit-22. 
 *		2. Call the base class method for implementation.
 *
 */
bool ISO1420Val::checkPOSData(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkPOSData(fieldMap, mapSize, statusRef));

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
bool ISO1420Val::checkSEN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1420Val::checkTransCurrencyCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkTransCurrencyCode(fieldMap, mapSize, statusRef));
}	


