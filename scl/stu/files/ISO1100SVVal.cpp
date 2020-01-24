/*********************************************************************
*
*   File name:
*       ISO1100SVVal.cpp
*
*   Contents:
*       ISO1100SVVal class functions
*
*   Description
*
*        This file contains the implementations of the functions in ISO1100SVVal
*        class. These functions validate the ISO1100SVAuthorization message.
*
*
*   See Also:
*        ISO1100SVVal.h   
*        
*
*   Created:
*       07 June 2001 Arun G.
*
*   Modified:
*	    21 June 2001 Shubha K
*			-Added checkPOSData().
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
#include "ISO1100SVVal.h"


//Default Constructor
ISO1100SVVal::ISO1100SVVal()
{	}
	
//Destructor
ISO1100SVVal::~ISO1100SVVal()
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
 *		9. checkFunctionCode()
 *		10. checkAcceptorBusinessCode()
 *		11. checkSEN()
 * 		12. checkTransCurrencyCode()
 *		13. checkCtrlInfo()
 *		14. checkPrivateData()
 *
 */
bool ISO1100SVVal::performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status=false;
	
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
	//check Processing code
	status = checkProcessingCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}
	
	//check Transaction amount
	status = checkTransAmount(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Effective and Expiry dates
	status = checkDate(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Merchant type code
	status = checkMerchantType(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Country code
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

	//check Function code
	status = checkFunctionCode(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Acceptor Business code
	status = checkAcceptorBusinessCode(fieldMap,mapSize,statusRef);
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

	//check security related control information data
	status = checkCtrlInfo(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check private data
	status = checkPrivateData(fieldMap,mapSize,statusRef);
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
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		Checks if the following bit positions are set: Bit-2, Bit-3, Bit-11, Bit-12, Bit-22, 
 *		Bit-26, Bit-42, and Bit-49. If all the bits are set, return TRUE.  Else return FALSE 
 *		with the ISOStatus object updated to reflect the failure.
 *	
 */	
bool ISO1100SVVal::checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i=0;		
	//check each fieldMap array element
	for(i = 1;i < mapSize; i++)
	{
		//Check the bit positions 2,3,11,12,22,26,42 and 49.
		//the index position of the array starts from 0
		switch(i)
		{
			case 1:
			case 2:
			case 10:
			case 11:
			case 21:
			case 25:
			case 41:
			case 48:
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
				statusRef.setStatus(false);
				statusRef.setResultCode(ENOMEM);
				statusRef.setResultDesc("Failure - 1100 Message validate - Insufficient memory");
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
bool ISO1100SVVal::checkPAN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
 *		Checks the bit position 3 which can have only one of the following values:
 *			1. 004099 = Authorization Debit (redemption)
 *			2. 004899 = Debit and Address Verification Combo
 *			3. 204099 = Authorization Credit (return)
 *			4. 174899 = Address Verification Only
 *		If the processing code is valid, return TRUE else return FALSE with the ISOStatus
 *		object updated to reflect the failure
 *
 */
bool ISO1100SVVal::checkProcessingCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	//check if Null value
	if(fieldMap[2]->m_fieldPointer==NULL)
	{
		status= false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Processing Code - Field data not set");
	}
	else
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;

		if (dataLen!=NULL)
		{	
			//get the data from the field
			//memory released at the end of this function
			unsigned char* dataPtr = NULL;
			dataPtr=fieldMap[2]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status=false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Processing Code - No field data retrieved");
			}
			else
			{
				//check for valid processing codes
				long processCode=atol((char *)dataPtr);
				switch(processCode)
				{
					case ADDRESS_VERIFICATION:
					case AUTHORIZATION_DEBIT:
					case DEBIT_ADDRESS_VERIFICATION:
					case AUTHORIZATION_CREDIT:
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
		}
		else
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Processing Code - Insufficient memory");
		}//end of dataLen if-else
	}
	
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
bool ISO1100SVVal::checkTransAmount(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//pointer for data
	unsigned char* dataPtr = NULL; 
	//counter variable
	int i=0;	
	//Check if Null value for bit 3
	if(fieldMap[2]->m_fieldPointer!=NULL)
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;
		
		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Transaction Amount - Insufficient memory");
		}
		else
		{
			//get the data from the field position 3
			//memory released at the end of this function
			dataPtr = fieldMap[2]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - No data retrieved");
			}
			// if the value at bit position 3 is "004099", "204099" or "004899" then check if bit 4 is set.
			else 
			{
				//check for valid processing codes
				//allocate memory for a temp null terminated string
				//memory released at the end of the function
				unsigned char *tempData = NULL;
				tempData = new unsigned char[*dataLen+1];

				if(tempData == NULL)
				{
					status = false;
					statusRef.update (false, ENOMEM, "Failure - Transaction Amount - Insufficient memory");
				}
				else
				{
					memset(tempData, 0, *dataLen+1);

					//copy the data to the temp pointer
					for(i=0; i<*dataLen; i++)
					{
						tempData[i] = dataPtr[i];
					}
					//append a null character
					tempData[*dataLen] = '\0';

					//convert the ascii data to long data type
					long processCode=atol((char *)tempData);

					//release memory allocated to the temp null terminated string
					delete tempData;

					switch(processCode)
					{
						case AUTHORIZATION_DEBIT:
						case DEBIT_ADDRESS_VERIFICATION:
						case AUTHORIZATION_CREDIT:
							//check if the bit position 4 has been set
							if(fieldMap[3]->m_fieldPointer== NULL)
							{
								status = false;
								statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Transaction Amount");
							}
							else
								status=fieldMap[3]->m_isSet;
								break;
						default:
							//if no data set for bit 4, then no check to be performed for currency format
							if(fieldMap[3]->m_isSet== false)
							{
								delete dataLen;

								return true;
							}
							else
								status = true;
					}//end of switch
					
					
					if(status == true)
					{
						//check bit 49 for the decimal point for currency code
						//by calling the hash function
						//memory released at the end of this function
						unsigned char* bit49data=NULL;
						bit49data = fieldMap[48]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

						if(bit49data==NULL)
						{
							status=false;
							statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - No field 49 data retrieved");
						}
						else
						{
							//get the length of the currency code
							int len = *dataLen;

							//get the data from the field - bit position 4
							//memory is released at the end of this function
							dataPtr = NULL;
							dataPtr=fieldMap[3]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

							if(dataPtr != NULL)
							{
								//allocate memory for a null terminated string for the currency code
								//memory released at the end of the function
								tempData = NULL;
								tempData = new unsigned char[len+1];
								
								if(tempData != NULL)
								{
									memset(tempData, 0, len+1);

									//copy the data received from bit 49 to the temp pointer
									for(i=0; i<len; i++)
									{
										tempData[i] = bit49data[i];
									}
									//append the null character
									tempData[i] = '\0';

									//call the hash function
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
										int maxDecPoints = currencyCode->decimalPoint;
								
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

									} //end of currency code if-else

									//release memory allocated to the temp array for a null terminated string
									delete tempData;
								}
								else
								{
									status = false;
									statusRef.update (false, ENOMEM, "Failure - Transaction Amount - Insufficient memory");
								}//end of tempData if-else
							}
							else
							{
								status = false;
								statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - No field data retrieved");
							}//end of inner dataPtr if-else
						}//end of bit49data if-else

						if(status==false)
						{
							statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Currency Code");
							return status;
						}
						
					}//end of status if-else

				}//end of tempData if-else

			}//end of dataPtr if-else

			//release memory allocated to the out parameter pointer for length
			delete dataLen;

		}//end of dataLen if-else
	}
	else
	{
		status = false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction Amount - Field not set");
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
bool ISO1100SVVal::checkDate(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1100SVVal::checkMerchantType(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1100SVVal::checkCountryCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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

bool ISO1100SVVal::checkPOSData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return ValidateMessage::checkPOSData(fieldMap, mapSize, statusRef);
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
 *		2. The following are the only valid values for 1100 message type:
 *			1. 100 = Debit authorization with or without partial support
 *			2. 108 = Credit authorization
 *			3. no value sent = 100 
 *		3. If the validation is correct, return TRUE.  Else return FALSE with the ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1100SVVal::checkFunctionCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i=0;
	//array of valid function codes
	//release memory allocated at the end of the function
	char funCode[][4] = { "100",
					  "181",
					  "108",
					  "302"
					};
	
	//length of the function code array
	int funCodeArray = 4;

	//check if Null value
	if(fieldMap[23]->m_fieldPointer==NULL)
	{
		status= false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Function Code - Field not set");
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
			statusRef.update (false, ENOMEM, "Failure - Function Code - Insufficient memory");
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
					statusRef.update (false, ENOMEM, "Failure - Function Code - Insufficient memory");
				}
				else
				{
					memset(tempPtr, 0, *dataLen+1);

					//copy the data to the temp pointer
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

					//release memory allocated to tempPtr for null terminated string
					delete [] tempPtr;
				}//end of tempPtr if-else
			}//end of dataPtr if-else
			
			//release memory allocated to out parameter pointer for length
			delete dataLen;
		}//end of dataLen if-else
	}
	
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
bool ISO1100SVVal::checkAcceptorBusinessCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i=0;	

	//Check if Null value
	if(fieldMap[25]->m_fieldPointer==NULL)
	{
		status= false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Acceptor Business Code - Field data not set");
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
			//get the data from the field
			//memory released at the end of this function
			unsigned char* dataPtr = NULL;
			dataPtr = fieldMap[25]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status=false;
			}
			else
			{
				//append a null character to the data for checking in a temp array
				//memory deleted at the end of the function
				unsigned char* tempPtr = NULL;
				tempPtr = new unsigned char[*dataLen+1];
				
				if(tempPtr != NULL)
				{
					memset(tempPtr, 0, *dataLen+1);

					//copy the data to teh temp pointer
					for(i=0; i<*dataLen; i++)
					{
						tempPtr[i] = dataPtr[i];
					}
					tempPtr[i] = '\0';
					
					//call the hash function to check if data is valid
					const char* merchantCode=NULL;
					merchantCode = isoMerchantTypeIsValid((char *)tempPtr,4);

					if(merchantCode==NULL)
					{
						status=false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Acceptor Business Code ");
					}
					else
					{
						status=true;
					}
	
					//release memory allocated to the temp array
					delete tempPtr;
				}
				else
				{
					statusRef.update (false, ENOMEM, "Failure - Acceptor Business Code - Insufficient memory");
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
bool ISO1100SVVal::checkSEN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1100SVVal::checkTransCurrencyCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1100SVVal::checkCtrlInfo(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	//Check if Null value for bit 22
	if(fieldMap[21]->m_fieldPointer!=NULL)
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;

		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Control Info - Insufficient memory");
		}
		else
		{
			//get the data from the field position 22
			//memory released at the end of this function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[21]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Acceptor Business Code - No field data set");
			}
			//if the value of byte-7 in Bit Field-22 is set to "S" or "T" then 
			//check if bit 53 is set.
			else if(dataPtr[6]=='S'||dataPtr[6]=='T')
			{
				if(fieldMap[52]->m_fieldPointer== NULL)
				{
					status = false;
					statusRef.update (false, VALIDATION_FAILED, "Failure - Acceptor Business Code not set");
				}
				else
					status=fieldMap[52]->m_isSet;
			}
			else
			{
				status = true;
			}
			
			//release memory allocated to out parameter pointer for length
			delete dataLen;
		}//end of dataLen if-else
	}
	else	
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Control Info Data - Bit 22 not set");
	}

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
bool ISO1100SVVal::checkPrivateData(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i=0;	

	//Check if Null value for bit 3
	if(fieldMap[2]->m_fieldPointer!=NULL)
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;		

		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - Private Data - Insufficient memory");
		}
		else
		{
			//get the data from the field position 3
			//memory released at the end of this function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[2]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);
			
			if(dataPtr==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Private Data - No field data retrieved");
			}
			else
			{
				//allocate memory for a null terminated temp array
				//memory released at the end of the method
				unsigned char* tempData = NULL;
				tempData = new unsigned char[*dataLen+1];
			
				if(tempData != NULL)
				{
					memset(tempData, 0, *dataLen+1);

					//copy the data retrived from the ISOField to the temp array
					for(i=0; i<*dataLen; i++)
					{
						tempData[i] = dataPtr[i];
					}
					//append the null character
					tempData[*dataLen] = '\0';
					
					//check if the data contains the required value
					if(strcmp((char *)tempData, "174899") == 0)
					{
						if(fieldMap[62]->m_fieldPointer== NULL)
						{
							status = false;
							statusRef.update (false, ENOMEM, "Failure - Private data not set");
						}
						else
							status=fieldMap[62]->m_isSet;
					}
					else
						status = true;

					//release memory allocated to temp pointer
					delete tempData;
				}
				else
				{
					status = false;
					statusRef.update (false, ENOMEM, "Failure - Private data - Insufficient memory");
				}//end of tempData if-else
			}//end of dataPtr if-else

			//release memory allocated to out parameter pointer for length
			delete dataLen;
		}//end of dataLen if-else
	}
	else	
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Private data - Bit 3 not set");
	}	

	return status;
}
