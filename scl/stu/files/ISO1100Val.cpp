/*********************************************************************
*
*   File name:
*       ISO1100Val.cpp
*
*   Contents:
*       ISO1100Val class functions
*
*   Description
*
*        This file contains the implementations of the functions in ISO1100Val
*        class. These functions validate the ISO1100 message.
*
*
*   See Also:
*        ISO1100Val.h   
*        
*
*   Created:
*       21 June 2001 Arun G.
*
*   Modified:
*		26 June 2001 Shubha Kumar
*			- Cleaned up the pointers
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
#include "ISO1100Val.h"


//Default Constructor
ISO1100Val::ISO1100Val()
{	}
	
//Destructor
ISO1100Val::~ISO1100Val()
{	}

//Methods

/*	Name	:	performValidation
 *
 * 	Arguments:
 * 		fieldMap[] : Pointer to the field map array.
 *		size :	The size of the bit map.  (64 or 128).
 *		statusRef: [Pass By Reference] ISOStatus parameter will be updated with the status of operation.  
 *					Previous data will be overwritten. 
 *
 *	Return Type: 
 *	boolean : Indicates status of operation.  TRUE (1) indicates success and FALSE (0) indicates
 *			  failure.  Client App will have to check the ISOStatus object for more details in case 
 *			  if the return value is FALSE (0).
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
 *		9. checkFunctionCode()
 *		10. checkMessageReasonCode()
 *		11. checkAcceptorBusinessCode()
 *		12. checkSEN()
 * 		13. checkTransCurrencyCode()
 *		14. checkCtrlInfo()
 *		15. checkPrivateData()
 *
 */
bool ISO1100Val::performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	// 1.check required fields
	status = checkRequiredFields(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 2.check Permanent Account Number
	status = checkPAN(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 3.check Processing code
	status = checkProcessingCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 4.check Transaction amount
	status = checkTransAmount(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 5.check Effective and Expiry dates
	status = checkDate(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 6.check Merchant type code
	status = checkMerchantType(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 7.check Country code
	status = checkCountryCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 8.check POS Data code
	status = checkPOSData(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 9.check Function code
	status = checkFunctionCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}
	
	// 10.check Message Reason code
	status = checkMessageReasonCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 11.check Acceptor Business code
	status = checkAcceptorBusinessCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 12.check Service Establishment Number
	status = checkSEN(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 13.check Currency code
	status = checkTransCurrencyCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 14.check security related control information data
	status = checkCtrlInfo(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	// 15.check private data
	status = checkPrivateData(fieldMap,mapSize,statusRef);
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
 *		Checks if the following bit positions are set: 2, 3, 4, 11, 18, 19, 22, 26, 42,
 *		43, 49 and 63. If all the bits are set, return TRUE.  Else return FALSE 
 *		with the ISOStatus object updated to reflect the failure.
 *	
 */	
bool ISO1100Val::checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i = 0;

	//check each fieldMap array element
	for(i = 1;i < mapSize; i++)
	{
		//Check the bit positions 2,3,4,11,18,19,22,26,42,43,49,63
		//the index position of the array starts from 0
		switch(i)
		{
			case 1:
			case 2:
			case 3:
			case 10:
			case 17:
			case 18:
			case 21:
			case 25:
			case 41:
			case 42:
			case 48:
			case 62:
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
bool ISO1100Val::checkPAN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
 *		Checks the bit position 3 which can have one of the following values:
 *			004000 = Card Authorization Request or Reversal
 *			004800 = Combination Address Verification and Authorization
 *			034000 = AMEX Emergency Check Cashing
 *			044000 = Check Guarantee request - NPC (formerly JBS),
 *					 TeleCheck, or Equifax (formerly TeleCredit)
 *			064000 = AMEX Travelers Check Encashment
 *			104000 = AMEX Sight Draft
 *			174800 = Transaction for Address Verification Only
 *		If the processing code is valid, return TRUE else return FALSE with the ISOStatus
 *		object updated to reflect the failure
 *
 */
bool ISO1100Val::checkProcessingCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	//check if Null value
	if(fieldMap[2]->m_fieldPointer==NULL)
	{
		status= false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Processing Code - No field data set");
	}
	else
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;

		if(dataLen == NULL)
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
				status=false;
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
					case ADDRESS_VERIFICATION_AUTHORIZATION:
					case AMEX_EMERGENCY_CHECK_CASHING:
					case CHECK_GUARANTEE_REQUEST:
					case AMEX_TRAVELERS_CHECK_ENCASHMENT:
					case AMEX_SIGHT_DRAFT:
					case TRANSACTION_ADDRESS_VERIFICATION:
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
 *		1. Check for Conditional field (Bit-4).  
 *		2. If Bit-3 is set to "004099", "204099" or "004899", then Bit-4 is required. 
 *		3. Determine decimal point by the transaction currency code field (Bit-49).
 *		4. If both conditions are satisfied, return TRUE.  Else return FALSE with the 
 *		   ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1100Val::checkTransAmount(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	unsigned char* dataPtr = NULL;
	//counter variable
	int i = 0; 
	
	//check for the bit position 4 
	if(fieldMap[3]->m_fieldPointer== NULL)
	{
		status = false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - Field data not set");
	}
	else
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;

		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Transaction Amount- Insufficient memory");
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
				status=false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount- No data retrieved from bit position 49");
			}
			else
			{
				//get the length of the currency code
				int len = *dataLen;

				//get the data from the field - bit position 4
				//memory is released at the end of this function
				*dataLen = 0;
				dataPtr = NULL;
				dataPtr=fieldMap[3]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

				if(dataPtr == NULL)
				{
					status = false;
					statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount- No data retrieved from bit position 4");
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
						statusRef.update (false, ENOMEM, "Failure - Transaction Amount- Insufficient memory");
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
							status=false;
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
						}//end of currency code if-else
			
						//release memory allocated to the temp array for a null terminated string
						delete tempData;
					}//end of tempData if-else
				}//end of dataPtr if-else
			}//end of bit49data if-else
			
			//release memory allocated to the out parameter pointer for length
			delete dataLen;
		
		}//end of dataLen if-else
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
 *		Call the base class method for implementation
 *
 */
bool ISO1100Val::checkDate(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkDate(fieldMap, mapSize, statusRef));
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
bool ISO1100Val::checkMerchantType(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1100Val::checkCountryCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1100Val::checkPOSData(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkPOSData(fieldMap, mapSize, statusRef));

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
 *		2. The following is the only valid values for 1100 message type: 180
 *		3. If the validation is correct, return TRUE.  Else return FALSE with the ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1100Val::checkFunctionCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i = 0;

	if(fieldMap[23]->m_isSet==false)
		status = true;
	else
	{
		//check if Null value
		if(fieldMap[23]->m_fieldPointer==NULL)
		{
			status= false;
			statusRef.update (false, VALIDATION_FAILED, "Failure - Function Code - Field not set");
		}
		else
		{

			//valid function code
			char funCode[]="180";
			//length pointer
			//memory is released at the end of the function
			int* dataLen = NULL;
			dataLen = new int;

			if(dataLen == NULL)
			{
				status = false;
				statusRef.update (false, ENOMEM, "Failure - Function Code - Insufficient memory");
			}
			else
			{
				//initialize dataLen
				*dataLen = 0;

				//get the data from the field
				//memory is released at the end of the function
				unsigned char* dataPtr=NULL;
				dataPtr = fieldMap[23]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

				if(dataPtr==NULL)
				{
					//since field is optional
					status = true;
				}
				else
				{
					//append a null character to the data for checking in a temp array
					//memory released at the end of the function
					unsigned char *tempPtr = NULL;
					tempPtr = new unsigned char[*dataLen+1];

					if(tempPtr == NULL)
					{
						status = false;
						statusRef.update (false, ENOMEM, "Failure - Function Code - Insufficient memory");
					}
					else
					{					
						//initialize all positions with null character
						memset(tempPtr, 0, *dataLen+1);

						//copy data to a null terminated string for comparison
						for(i=0; i<*dataLen; i++)
						{
							tempPtr[i] = dataPtr[i];
						}
												
						//check for valid function code
						if(strcmp((char *)tempPtr, funCode) == 0)
						{
							status = true;
						}
						else
						{
							status = false;
							statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Function Code");
						}
								
						//release memory allocated to tempPtr for null terminated string
						delete [] tempPtr;
					}//end of tempPtr if-else				
				}//end of dataPtr if-else

				//release memory allocated to out parameter pointer for length
				delete dataLen;
			}//end of dataLen if-else
		}//end of fieldMap inner if-else
	}//end of fieldMap outer if-else
	
	return status;
}


/*
 *	Name :
 *		checkMessageReasonCode(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
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
 *		1. Check Bit-25. 
 *		2. The following is the only valid values for 1100 message type: 180
 *		3. If the validation is correct, return TRUE.  Else return FALSE with the ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1100Val::checkMessageReasonCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i = 0;

	//valid function code
	char msgReasonCode[]="1506";
	
	//field is optional
	if(fieldMap[24]->m_isSet==false)
		status = true;
	else
	{
		//check if Null value
		if(fieldMap[24]->m_fieldPointer==NULL)
		{
			status= false;
			statusRef.update (false, VALIDATION_FAILED, "Failure - Message Reason Code - Field data not set");
		}
		else
		{
			//length pointer
			//memory is released at the end of the function
			int* dataLen = NULL;
			dataLen = new int;

			if(dataLen == NULL)
			{
				status = false;
				statusRef.update (false, ENOMEM, "Failure - Message Reason Code - Insufficient memory");
			}
			else
			{
				//initialize dataLen
				*dataLen = 0;

				//get the data from the field
				//memory is released at the end of the function
				unsigned char* dataPtr=NULL;
				dataPtr = fieldMap[24]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

				if(dataPtr==NULL)
				{
					//since field is optional
					status = true;
				}
				else
				{
					//append a null character to the data for checking in a temp array
					//memory deleted at the end of the function
					unsigned char* tempPtr = NULL;
					tempPtr = new unsigned char[*dataLen+1];

					if(tempPtr == NULL)
					{
						status = false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Message Reason Code - Insufficient memory");
					}
					else
					{
						//initialize each position with null character
						memset(tempPtr, 0, *dataLen+1);

						//copy data to temp buffer for comparison
						for(i=0; i<*dataLen; i++)
						{
							tempPtr[i] = dataPtr[i];
						}
											
						//check for valid message reason code
						if(strcmp((char *)tempPtr, msgReasonCode) == 0)
						{
							status = true;
						}
						else 
						{
							status = false;
							statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Message Reason Code");
						}

						//release memory allocated to tempPtr for null terminated string
						delete [] tempPtr;

					}//end of tempPtr if-else
				}//end of dataPtr if-else

				//release memory allocated to out parameter pointer for length
				delete dataLen;
			
			}//end of dataLen if-else
		}//end of inner fieldMap if-else
	}//end of outer fieldMap if-else
	
	return status;
}


/*
 *	Name :
 *		checkAcceptorBusinessCode(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
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
 *		1. Check Bit-26. Use the Merchant type hash method. 
 *		2. If the validation is correct, return TRUE. Else return FALSE with 
 *		   the ISOStatus object updated to reflect the failure
 *
 */
bool ISO1100Val::checkAcceptorBusinessCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i = 0;
	
	//Check if Null value
	if(fieldMap[25]->m_fieldPointer==NULL)
	{
		status= false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Acceptor Business Code - Field not set");
	}
	else
	{
		//length pointer
		//release the memory at the end of the function
		int* dataLen = NULL;
		dataLen = new int;

		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Acceptor Business Code - Insufficient memory");
		}
		else
		{
			//initialize dataLen
			*dataLen = 0;

			//get the data from the field
			//memory released at the end of this function
			unsigned char* dataPtr=NULL; 
			dataPtr = fieldMap[25]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);
			
			if(dataPtr==NULL)
			{
				status=false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Acceptor Business Code - Field data not retrieved");
			}
			else
			{
				//append a null character to the data for checking in a temp array
				//memory deleted at the end of the function
				unsigned char* tempPtr = NULL;
				tempPtr = new unsigned char[*dataLen+1];

				if(tempPtr == NULL)
				{
					status = false;
					statusRef.update (false, ENOMEM, "Failure - Acceptor Business Code - Insufficient memory");
				}
				else
				{
				    //initialoze each position to null
					memset(tempPtr, 0, *dataLen +1);

					//copy data to a temp buffer for comparison
					for(i=0; i<*dataLen; i++)
					{
						tempPtr[i] = dataPtr[i];
					}
										
					//call the hash function to check if data is valid
					const char* merchantCode=isoMerchantTypeIsValid((char *)tempPtr,4);
					if(merchantCode==NULL)
					{
						status=false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Acceptor Business Code - Invalid merchant code");
					}
					else
					{
						status=true;
					}
					
					//release memory allocated to the temp array
					delete tempPtr;

				}//end of tempPtr if-else
			}//end of dataPtr if-else
		
			//release memory allocated to the out parameter for length
			delete dataLen;
		}//end of dataLen if-else
	}//end of fieldMap if-else

	return status;
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
bool ISO1100Val::checkSEN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1100Val::checkTransCurrencyCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkTransCurrencyCode(fieldMap, mapSize, statusRef));
}	



/*
 *	Name :
 *		checkCtrlInfo(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
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
 *		Check for Bit-53.  Required if byte-7 in Bit Field-22 is set to "S" or "T".  
 *		If Bit-22 byte-7 has any other value, then Bit-53 is optional. If all the bits are 
 *		set, return TRUE.  Else return FALSE with the ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1100Val::checkCtrlInfo(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	//Check if Null value for bit 22
	if(fieldMap[21]->m_fieldPointer==NULL)
	{
		status = false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Control Info - Field not set at bit position 22");
	}
	else
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;

		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, VALIDATION_FAILED, "Failure - Control Info - Insufficient memory");
		}
		else
		{
			//initialize dataLen
			*dataLen = 0;

			//get the data from the field position 22
			//memory released at the end of this function
			unsigned char* dataPtr=NULL;
			dataPtr=fieldMap[21]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Control Info - No data retrieved from bit position 22");
			}
			//if the value of byte-7 in Bit Field-22 is set to "S" or "T" then 
			//check if bit 53 is set.
			else if(dataPtr[6]=='S'||dataPtr[6]=='T'||dataPtr[6]=='W')
			{
				if(fieldMap[52]->m_fieldPointer== NULL)
				{
					status = false;
					statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Control Info - Field not set");
				}
				else
					status=fieldMap[52]->m_isSet;
			}
			else
			{
				status = true;
			}//end of dataPtr if-else
			
			//release memory allocated to out parameter pointer for length
			delete dataLen;

		}//end of dataLen if-else
	}//end of fieldMap if-else

	return status;
}


/*
 *	Name :
 *		checkPrivateData(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
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
 *		Check Bit-63. Required if Bit-3 is set to "174899" - address verification. 
 *		If all the bits are set, return TRUE.  Else return FALSE with the ISOStatus object 
 *		updated to reflect the failure.
 *
 */
bool ISO1100Val::checkPrivateData(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i = 0;
	
	//Check if Null value for bit 3
	if(fieldMap[2]->m_fieldPointer==NULL)
	{
		status = false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Private Info - Field 3 not set");
	}
	else
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;	
		
		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Private Info - Insufficient memory");
		}
		else
		{
			//initialize dataLen
			*dataLen = 0;

			//get the data from the field position 3
			//memory released at the end of this function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[2]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Private Info - Field 3 data not retrieved");
			}
			else
			{
				//allocate memory for a null terminated temp array
				//memory released at the end of the method
				unsigned char* tempData = NULL;
				tempData = new unsigned char[*dataLen+1];
			
				if(tempData == NULL)
				{
					status = false;
					statusRef.update (false, ENOMEM, "Failure - Private Info - Insufficient memory");
				}
				else
				{
					//initialize each field to null
					memset(tempData, 0, *dataLen+1);

					//copy the data retrived from the ISOField to the temp array
					for(i=0; i<*dataLen; i++)
					{
						tempData[i] = dataPtr[i];
					}

					//check if the data contains the required value
					if(strcmp((char *)tempData, "174800") == 0||strcmp((char *)tempData, "004800") == 0||strcmp((char *)tempData, "044000") == 0)
					{
						if(fieldMap[62]->m_fieldPointer== NULL)
						{
							status = false;
							statusRef.update (false, VALIDATION_FAILED, "Failure - Private Info - Private data not set");
						}
						else
							status=fieldMap[62]->m_isSet;
					}
					else
						status = true;

					//release memory allocated to temp pointer
					delete tempData;

				}//end of tempData if-else
			}//end of dataPtr if-else

			//release memory allocated to out parameter pointer for length
			delete dataLen;
		}//end of dataLen if-else
	}//end of fieldMap if-else

	return status;
}
