/*********************************************************************
*
*   File name:
*       ISO1220Val.cpp
*
*   Contents:
*       ISO1220Val class functions
*
*   Description
*
*        This file contains the implementations of the functions in ISO1220Val
*        class. These functions validate the ISO1220SVMessage.
*
*
*   See Also:
*        ISO1220Val.h   
*        
*
*   Created:
*       11 June 2001 Arun G.
*
*   Modified:
*		19 June 2001 Shubha Kumar
*			- Added new function codes - 420, 421, 430, 431.
*
*	    21 June 2001 Shubha K
*			-Added checkPOSData().
*			-No date check with bits 35 & 45
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
#include "ISO1220Val.h"


//Default Constructor
ISO1220Val::ISO1220Val()
{	}
	
//Destructor
ISO1220Val::~ISO1220Val()
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
 *		5. checkMerchantType()
 *		6. checkCurrencyCode()
 *		7. checkFunctionCode()
 *		8. checkPOSData()
 *		9. checkAcceptorBusinessCode()
 *		10. checkSEN()
 *		11. checkTransCurrencyCode()
 *		 							  
 *
 */
bool ISO1220Val::performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	/*//check required fields
	status = checkRequiredFields(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}*/

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


	//check Merchant Type
	status = checkMerchantType(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Currency Code
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
 *		Checks if the following bit positions are set: Bit-2, Bit-3, Bit-4,Bit-11, Bit-12, Bit-22, 
 *		Bit-24,Bit-26, Bit-42, and Bit-49. If all the bits are set, return TRUE.  Else return FALSE 
 *		with the ISOStatus object updated to reflect the failure.
 *	
 */	
bool ISO1220Val::checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i=0;
	//check each fieldMap array element
	for(i = 1;i < mapSize; i++)
	{
		//Check the bit positions 2,3,4,11,12,22,24,26,42 and 49.
		//the index position of the array starts from 0
		switch(i)
		{
			case 1:
			case 2:
			case 3:
			case 10:
			case 11:
			case 21:
			case 23:
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

		//check if any of the required fields is not filled
		if(status == false)
		{
			statusRef.setStatus(false);
			statusRef.setResultCode(VALIDATION_FAILED);

			//error message string.
			char errMsg[] = "Falilure - Required/Mandatory Fields Not Set";

			//call the method to append the bit position to the error message string.
			char* newErrMsg = NULL;
			newErrMsg = CharUtility::createErrMessage(i+1,errMsg);

			if(newErrMsg != NULL)
			{
				//set this new message to the ISOStatus object
				statusRef.setResultDesc(newErrMsg);

				//delete the local pointer to free the memory allocated in the createErrMessage method.
				delete newErrMsg;
			}
			else
			{
				status = false;
				statusRef.update (false, ENOMEM, "Failure - 1220 Message validate- Insufficient memory");
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
bool ISO1220Val::checkPAN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  
 *		Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		Checks the bit position 3 which can have only one value: 210099
 *			
 *		If the processing code is valid, return TRUE else return FALSE with the ISOStatus
 *		object updated to reflect the failure
 *
 */
bool ISO1220Val::checkProcessingCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	//check if Null value
	if(fieldMap[2]->m_fieldPointer==NULL)
	{
		status= false;

		statusRef.update (false, VALIDATION_FAILED, "Failure - Processing Code - Field not set");
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
			statusRef.update (false, VALIDATION_FAILED, "Failure - Processing Code - Insufficient memory");
		}
		else
		{
			//get the data from the field
			//memory released at the end of this function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[2]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);
			
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
					case FUNDING:
						status = true;
						break;
					default:
						status=false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Processing Code");

						break;
				}
			}

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
 *		1. Check for Requirend field (Bit-4).  
 *		2. Determine decimal point by the transaction currency code field (Bit-49).
 *		3. If both conditions are satisfied, return TRUE.  Else return FALSE with the 
 *		   ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1220Val::checkTransAmount(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{

	bool status = false;
	//pointer for data
	unsigned char* dataPtr = NULL; 
	//counter variable
	int i=0;	
	//Check if Null value for bit 3
	if(fieldMap[3]->m_fieldPointer!=NULL)
	{
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;
		
		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction amount - Insufficient memory");
		}
		else
		{
			//get the data from the field position 4
			//memory released at the end of this function
			dataPtr=NULL;
			dataPtr = fieldMap[3]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction amount - No field data retrieved");
			}
			// if the value at bit position 4 is set
			else 
			{
				//get the length of transaction amount data
				int len = *dataLen;
				
				//check bit 49 for the decimal point for currency code
				//by calling the hash function
				//memory released at the end of this function
				unsigned char* bit49data=NULL;
				bit49data=fieldMap[48]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);
				
				if(bit49data==NULL)
				{
					status = false;
					statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction amount - No field data retrieved");
				}
				else
				{
					//allocate memory for a null terminated string for the currency code
					//memory released at the end of the function
					unsigned char* tempData = NULL;
					tempData = new unsigned char[len+1];
							
					if(tempData != NULL)
					{
						memset(tempData, 0, len+1);

						//copy the data received from bit 49 to the temp pointer
						for(i=0; i<*dataLen; i++)
						{
							tempData[i] = bit49data[i];
						}
						//append the null character
						tempData[i] = '\0';

						//call the hash function
						//const IsoCurrencyCode* currencyCode = NULL;
						const IsoCurrencyCode* currencyCode = isoCurrencyLookup((char *)tempData,3);

						//check if currency code is available
						if(currencyCode==NULL)
						{
							status=false;
							statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Currency Type");
						}
						else
						{
							//get the maximum allowed decimal digits
							int maxDecPoints = currencyCode->decimalPoint;
							
							//store the number of 0s used for left padding the data
							int zeroCount = 0;

							//check for the number of left padded 0s in transaction amount data
							//at bit positon 4 - to the length of deimal digits less from total length
							for(i=0; i<len-maxDecPoints; i++)
							{
								if(dataPtr[i] == '0')
									zeroCount++;
							}

							//check if the complete data is zero padded till the allowed decimal digits position
							if(zeroCount == (len-maxDecPoints))
							{
								status=false;
								statusRef.update (false, VALIDATION_FAILED, "Failure - Currency Type - Invalid data");
							}
							else
								status = true;

						}//end of currencyCode if-else

						//release memory allocated to the temp array for a null terminated string
						delete [] tempData;
					}
					else
					{
						statusRef.update (false, ENOMEM, "Failure - Insufficient Memory");
					}//end of tempData if-else
				}//end of bit49data if-else
			}//end of dataPtr if-else
			
			//release memory allocated to the out parameter pointer for length
			delete dataLen;

		}//end of dataLen if-else
	}
	else	
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Transaction Amount");
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
bool ISO1220Val::checkDate(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	//return (ValidateMessage::checkDate(fieldMap, mapSize, statusRef));
	return true;
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
bool ISO1220Val::checkMerchantType(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1220Val::checkCountryCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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

bool ISO1220Val::checkPOSData(FieldMapElement *fieldMap[],int mapSize,ISOStatus &statusRef)
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
 *		2. The following are the only valid values for 1220 message type: 440,441
 *		3. If the validation is correct, return TRUE.  Else return FALSE with the ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1220Val::checkFunctionCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	//boolean for status os operations	
	bool status = false;
	//counter variable
	int i=0;
	//array of valid function codes
	//release memory at the end of this function
	char funCode[][4] ={	"440",
							"441",
							"420",
							"421",
							"430",
							"431",
						};
	//length of the function code array
	int funCodeArray = 6;

	//check if Null value
	if(fieldMap[23]->m_fieldPointer==NULL)
	{
		status = false;
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
			status=false;
			statusRef.update (false, VALIDATION_FAILED, "Failure - Function code - Insufficient memory");
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
				//memory deleted at the end of the function
				unsigned char* tempPtr = NULL;
				tempPtr = new unsigned char[*dataLen+1];

				if(tempPtr!=NULL)
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
					
					if(!status)
					{
						status=false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Function code");
					}

					//release memory allocated to tempPtr for null terminated string
					delete [] tempPtr;
				}
				else
				{
					status = false;
					statusRef.update (false, ENOMEM, "Failure - Function code - Insufficient Memory");
				}//end of tempPtr
			}//end of dataPtr

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
bool ISO1220Val::checkAcceptorBusinessCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i=0;	
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
			statusRef.update (false, ENOMEM, "Failure - Acceptor Business Code - Insuffiecient memory");
		}
		else
		{
			//get the data from the field
			//memory released at the end of this function
			unsigned char* dataPtr= NULL;
			dataPtr = fieldMap[25]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status=false;
				statusRef.update (false, ENOMEM, "Failure - Acceptor Business Code - No field data retrieved");
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
					
					for(i=0; i<*dataLen; i++)
					{
						tempPtr[i] = dataPtr[i];
					}
					tempPtr[i] = '\0';
					
					//call the hash function to check if data is valid
					const char* merchantCode=isoMerchantTypeIsValid((char *)tempPtr,4);
					if(merchantCode==NULL)
					{
						status=false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Acceptor Business Code");
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
					statusRef.update (false, ENOMEM, "Failure - Acceptor Business Code - Insufficient Memory");
				}
			}//end of dataPtr if-else

			//release memory allocated to the out parameter for length
			delete dataLen;
		}//end of dataLen if-else
	}

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
bool ISO1220Val::checkSEN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
bool ISO1220Val::checkTransCurrencyCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return (ValidateMessage::checkTransCurrencyCode(fieldMap, mapSize, statusRef));
}	
