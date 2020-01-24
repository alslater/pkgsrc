/*********************************************************************
*
*   File name:
*       ValidateMessage.cpp
*
*   Contents:
*       ValidateMessage class functions
*
*   Description
*
*        This file contains the implementations of the functions in ValidateMessage
*        class. These functions validate the request message.
*
*
*   See Also:
*        ValidateMessage.h   
*        
*
*   Created:
*       11 June 2001 Shubha Kumar
*
*   Modified:
*		21 June 2001 Shubha K
*			-Added checkPOSData() - for bit 22 validation
*
*		22 June 2001 Shubha K
*			-Debugging for memory leaks and pointer intializations
***************************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//C header file
extern "C" 
{ 
	#include "ISOHash.h"
} 

//define a macro for SEN maxLength 
#define SEN_LEN 10


//specific header files
#include "CharUtility.h"
#include "Enumerations.h"
#include "FieldValidation.h"
#include "ValidateMessage.h"


//Default Constructor
ValidateMessage::ValidateMessage()
{	}
	
//Destructor
ValidateMessage::~ValidateMessage()
{	}


//Methods

/*	Name :
 *		checkPAN(FieldMapElement* fieldMap, int mapSize, ISOStatus* statusRef) 
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
 *		This is a check for bit position 2 - Permanent account number.
 *		The check digit is the last digit from the right of the PAN.
 *		1. Do not include the check digit (last number to the right) in the calculation.
 *		2. Starting with the last digit to the right, and working right to left, multiply 
 *			every other digit by two.						
 *		3. If any product of Step 4 is a two-digit number, add the two digits of the product.
 *		4. Add the products produced in Step 3. 	      
 *		5. Add all the digits not used in Step 2.		
 *		6. Add the results of Steps 4 and 5.			
 *		7. If the result of Step 6 is a multiple of 10, the check digit is zero (0). If the 
 *			result of Step 6 is not a multiple of 10, subtract the result from the next 
 *			higher multiple of 10. The new result is the calculated check digit.
 *		8. If the calculated check digit matches the given check digit, the Service Establishment 
 *			number is valid.
 *		9. If the check digits do not match, the SE number is invalid and must be flagged as invalid.
 *		If the account numbers is valid, return TRUE.  Else return FALSE with the ISOStatus object updated to reflect the failure.
 *
 */	
bool ValidateMessage::checkPAN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	int i=0,j=0;
	//check if Null value
	if(fieldMap[1]->m_fieldPointer==NULL)
	{
		status= false;

		statusRef.update (false, VALIDATION_FAILED, "Failure - PAN Validation - Field not set");
	}
	else
	{	
		//length pointer
		//memory released at the end of this function
		int* dataLen = NULL;
		dataLen = new int;
	
		//check if memory for the int allocated
		if(dataLen == NULL)
		{
			statusRef.update (false, ENOMEM, "Failure - Insufficient memory");

			status = false;
		}//end of dataLen if

		else
		{
			//get the data from the field
			//memory released at the end of this function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[1]->m_fieldPointer->getFieldInt (ASCII,dataLen, statusRef);

			//return false if the data could not be retrieved
			if(dataPtr==NULL)
			{
				status=false;

				statusRef.update (false, VALIDATION_FAILED, "Failure - PAN Validation - No field data retrieved");
			}
			else
			{
				int sum1=0,sum2=0,total=0,checkDigit=0,tempProduct=0;
							
				//variable used to assign each digit into a character array
				//memory released at the end of this function
				char* digitValue=NULL;
				digitValue = new char[2];

				if(digitValue == NULL)
				{
					statusRef.update (false, VALIDATION_FAILED, "Failure - PAN Validation - Insufficient memory");

					status = false;
				}//end digitValue if
				else
				{
					memset(digitValue, 0, 2);

					//initialize the array to null at the 0 index
					digitValue[1]='\0';
					
					//Start from the last digit from the right and proceed to the left
					//mulitplying every alternate digit by 2 and get a sum of all the products
					//Starting from second digit from the right, proceeding left
					//add the alternate digits
					for(i=(*dataLen)-2,j=(*dataLen)-3; i>=0;i-=2,j-=2)
					{
						//multiply every other digit by 2
						digitValue[0]=dataPtr[i];
						tempProduct=atoi(digitValue)*2;

						//If the product is a 2 digit number, add the 2 digits of the product.
						if(tempProduct>9)
							tempProduct=(int)tempProduct/10 + tempProduct%10;
						//store the sum of the products
						sum1=sum1+tempProduct;
						
						if(j>=0)
						{
							//add the other digits 
							digitValue[0]=dataPtr[j];
							sum2=sum2+atoi(digitValue);
						}
					}

					//find the total of the two sums
					total=sum1+sum2;

					//If 'total' is a multiple of 10, then check digit is 0. 
					//Else subtract 'total' from its next higher multiple of 10. 
					//The new result is the calculated check digit.
					if(total%10==0)
						checkDigit=0;
					else
					{
						//get the next higher multiple of the total
						//get the quotient
						int quotient = total / 10;
						//get the next higher multiple
						int multiple = (quotient + 1) * 10;
						//get the check digit
						checkDigit = multiple - total;

					}
					
					//check if the calculated checkdigit is the same as 
					//the check digit in the data
					digitValue[0]=dataPtr[(*dataLen)-1];
					if(checkDigit!=atoi(digitValue))
					{
						status = false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Number");
					}
					else
						status = true;

					//release memory allocated for converting ascii to int
					delete digitValue;
				}//end of digitValue if-else
			}//end of dataPtr if-else

			//release memory allocated to the out parameter pointer for length
			delete dataLen;
		}//end of dataLen if-else
	}//end of fieldMap if-else

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
 *		Each message implements its own version of  this method as the processing code differs for each.
 *
 */
bool ValidateMessage::checkProcessingCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	return true;
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
 *		2. Both bits required if Track-1 or Track-2 data is not available.
 *		3. If the validation is correct, return TRUE.  Else return FALSE with the 
 *		   ISOStatus object updated to reflect the failure.
 *
 */
bool ValidateMessage::checkDate(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	if(fieldMap[34]->m_isSet == false && fieldMap[44]->m_isSet == false)
	{
		// check if both bit 13 and bit 14 are set
		status = fieldMap[12]->m_isSet && fieldMap[13]->m_isSet ;
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
 *		2. If the validation is correct, return TRUE. 
 *         Else return FALSE with the ISOStatus object updated to reflect the failure
 *
 */
bool ValidateMessage::checkTransCurrencyCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	int i=0;	
	//Check if Null value
	if(fieldMap[48]->m_fieldPointer==NULL)
	{
		status= false;
		statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction amount - Field not set");

	}
	else
	{
		//length pointer
		//release memroy allocated at the end of function
		int* dataLen = NULL;
		dataLen = new int;
		
		//check if memory for the int allocated
		if(dataLen == NULL)
		{
			statusRef.update (false, ENOMEM, "Failure - Transaction amount - Insufficient memory");

			status = false;
		}//end of dataLen if
		else
		{
			//get the data from the field
			//release memory allocated at the end of function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[48]->m_fieldPointer->getFieldInt (ASCII,dataLen, statusRef);

			if(dataPtr==NULL)
			{
				status=false;

				statusRef.update (false, VALIDATION_FAILED, "Failure - Transaction amount - No field data retrieved");
			}
			else
			{
				//append a null character to the data for checking in a temp array
				//memory release at the end of the function
				char* tempPtr = NULL;
				tempPtr = new char[*dataLen+1];

				if(tempPtr != NULL)
				{
					memset(tempPtr, 0, *dataLen+1);
					
					//copy data to temp pointer
					for(i=0; i<*dataLen; i++)
					{
						tempPtr[i] = dataPtr[i];
					}
					tempPtr[i] = '\0';
					
					//call the hash function to check if data is valid
					const IsoCurrencyCode* currencyCode = NULL;
					currencyCode = isoCurrencyLookup(tempPtr,3);

					if(currencyCode==NULL)
					{
						status=false;

						statusRef.update (false, INVALID, "Failure - Transaction amount - Invalid Currency Type");
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
					status=false;

					statusRef.update (false, ENOMEM, "Failure - Transaction amount - Insufficient memory");
				}//end of tempPtr if-else
			} //end of dataPtr if-else

			//release memory for the out parameter for length
			delete dataLen;
		}//end of dataLen if-else	
	}//end of fieldMap if-else

	//update the ISOStatus object
	if(status==false)
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Currency - No field data retrieved");
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
 *		This is a check for bit position 42 - Service Establishment number.
 *		
 *		1.	Do not include the check digit (last number to the right)
 *			in the calculation.
 *		2.	If the first three digits of the number are less than 930 or 
 *			greater than 939, replace the first digit to the left with zero (0).
 *		3.	Starting with the second digit from the left, add together every other digit.
 *		4.	Starting with the first digit from the left, multiply every other digit by 2.                  
 * 	    5.	If any product of Step 4 is a two-digit number, add the two digits of the product.
 *		6.	Add the products produced in Step 5. 	  
 *		7.	Add the results of Steps 3 and 6. 	
 *		8.	If the result of Step 7 is a multiple of 10, the check digit is zero (0). 
 *			If the result of Step 7 is not a multiple of 10, subtract the result from
 *			the next higher multiple of 10. The new result is the calculated check digit.
 *			If the calculated check digit matches the given	check digit, the Service 
 *			Establishment number is valid.
 *		9.	If the check digits do not match, the SE number	is invalid and must be flagged 
 *			as invalid.
 *
 *		If the service establishment numbers is valid, return TRUE.  Else return FALSE with the 
 *		ISOStatus object updated to reflect the failure.
 *
 */
bool ValidateMessage::checkSEN(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	int i=0,j=0;
	//check if Null value
	if(fieldMap[41]->m_fieldPointer==NULL)
	{
		status= false;

		statusRef.update (false, INVALID, "Failure - SEN Validation - Field not set");
	}
	else
	{
		//length pointer
		//release memory allocated at the end of function
		int* dataLen = NULL;
		dataLen = new int;

		//check if memory for the int allocated
		if(dataLen == NULL)
		{
			statusRef.update (false, ENOMEM, "Failure - SEN Validation - Insufficient memory");

			status = false;
		}//end of dataLen if
		else
		{		
			//get the data from the field.
			//release memory allocated at the end of function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[41]->m_fieldPointer->getFieldInt (ASCII,dataLen, statusRef);

			if(dataPtr==NULL)
			{
				statusRef.update (false, VALIDATION_FAILED, "Failure - SEN Validation - No field data retrieved");

				status = false;
			}
			else
			{
				//If the first 3 digits are less than 930 or greater than 939, 
				//replace the first digit to the left with zero (0) 
				//release memory allocated at the end of function
				char* first3digit = NULL;
				first3digit = new char[4];  
				
				if(first3digit == NULL)
				{
					statusRef.update (false, ENOMEM, "Failure - SEN Validation - Insufficient memory");

					status = false;
				}
				else
				{				
					memset(first3digit, 0, 4);
					
					//copy the first 3 digits
					for(int k=0;k<3;k++)
						first3digit[k]=dataPtr[k];
					
					
					//convert to integer
					int tempVal = atoi(first3digit);
					
					//check if it is in the range of values allowed
					//else set to 0
					if(tempVal<930 || tempVal>939)
						dataPtr[0]='0';

					//variable used to assign each digit into a character array
					//release memroy allocated at the end of function
					char* digitValue=NULL;
					digitValue = new char[2];
					
					if(digitValue == NULL)
					{
						statusRef.update (false, ENOMEM, "Failure - SEN Validation - Insufficient memory");

						status = false;
					}			
					else
					{
						memset(digitValue, 0, 2);

						//set the first character to NULL
						digitValue[1]='\0';
					
						int sum1=0,sum2=0,total,checkDigit,tempProduct;
						
						//Start from the left and proceed to the right
						for(i=0,j=1;i<SEN_LEN;i+=2,j+=2)
						{
							if(j< SEN_LEN-1)
							{
								//starting from 2nd digit add every other digit
								digitValue[0]=dataPtr[j];
								sum1=sum1+atoi(digitValue);
							}				
							
							//starting from 1st digit multiply every other digit by 2
							digitValue[0]=dataPtr[i];
							tempProduct=(atoi(digitValue))*2;

							//If the product is a 2 digit number, add the 2 digits of the product.
							if(tempProduct>9)
								tempProduct=(int)tempProduct/10 + tempProduct%10;

							//sum of the products
							sum2=sum2+tempProduct;
						}

						//find the total
						total=sum1+sum2;

						//If 'total' is a multiple of 10, then check digit is 0. 
						//Else subtract 'total' from its next higher multiple of 10. 
						//The new result is the calculated check digit.
						if(total%10==0)
							checkDigit=0;
						else
						{
							//get the next higher multiple of the total
							//get the quotient
							int quotient = total / 10;
							//get the next higher multiple
							int multiple = (quotient + 1) * 10;
							//get the check digit
							checkDigit = multiple - total;
						}
						
						digitValue[0]=dataPtr[SEN_LEN-1];
						if(checkDigit!=atoi(digitValue))
						{
							status = false;

							statusRef.update (false, VALIDATION_FAILED, "Failure - SEN Validation failed");
						}
						else 
							status = true;

						//release memory allocated for converting ascii to int for each digit
						delete digitValue;

					}//end of digitValue if-else

					//release memory allocated to get the first three digits of SEN
					delete first3digit;
				
				}//end of first3digit if-else		
			}//dataPtr if-else
		
			//release memory allocated for the out parameter for length
			delete dataLen;
		}//end of dataLen if-else

	}//fieldMap if-else

	return status;
}


/*
 *	Name :
 *		checkMerchantType(FieldMapElement* fieldMap[], int mapSize, ISOStatus &statusRef)
 *
 *	Arguments:
 *		fieldMap[]:	Pointer to the field map array.
 *		size	:	The size of the bit map.  (64 or 128).
 *		statusRef:	[Pass By Reference] ISOStatus parameter will be updated with the status of operation.  Previous data will be overwritten. 
 *
 *	Return Type: 
 *		boolean :	Indicates status of operation.  TRUE (1) indicates success and FALSE (0) 
 *					indicates failure. Client App will have to check the ISOStatus object for 
 *					more details in case if the return value is FALSE (0).
 *
 *	Implementation Details:
 *		Check Bit-18. Use the Merchant type hash method. If the validation is correct,
 *		return TRUE. Else return FALSE with the ISOStatus object updated to reflect the failure
 *
 */
bool ValidateMessage::checkMerchantType(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	int i=0;	
	//Check if Null value
	if(fieldMap[17]->m_isSet==false)
	{
		status = true;

		statusRef.update (false, VALIDATION_FAILED, "Failure - Merchant Type - Field not set");
	}
	else
	{
		//length pointer
		//memory is released at the end of the function
		int* dataLen = NULL;
		dataLen = new int;

		//check if memory for the int allocated
		if(dataLen == NULL)
		{
			statusRef.update (false, ENOMEM, "Failure - Insufficient memory");

			status = false;
		}//end of dataLen if
		else
		{
			//get the data from the field
			//memory is released at the end of the function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[17]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status=false;

				statusRef.update (false, VALIDATION_FAILED, "Failure - Merchant Type - nO FIELD DATA RETRIEVED");
			}
			else
			{
				//append a null character to the data for checking in a temp array
				//memory released at the end of the function
				char* tempPtr = NULL;
				tempPtr = new char[*dataLen+1];
				
				if(tempPtr != NULL)
				{
					memset(tempPtr, 0, *dataLen+1);

					//copy  the data
					for(i=0; i<*dataLen; i++)
					{
						tempPtr[i] = dataPtr[i];
					}
					tempPtr[i] = '\0';
					
					//call the hash function to check if data is valid
					const char* merchantCode=NULL;
					merchantCode = isoMerchantTypeIsValid(tempPtr,4);
					if(merchantCode==NULL)
					{
						statusRef.update (false, VALIDATION_FAILED, "Failure - Merchant Type Not Valid");

						status=false;
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
					statusRef.update (false, ENOMEM, "Failure - Merchant Type - Insufficient memory");

					status=false;
				}//end of tempPtr if-else
			}//end of dataPtr if-else

			//delete memory allocated for the out parameter for length
			delete dataLen;
		}//end of dataLen if-else
	}//end of fieldMap if-else

	return status;
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
 *		Check Bit-19. Use the Country Code hash method.If the validation is correct, 
 *		return TRUE. Else return FALSE with the ISOStatus object updated to reflect the failure
 *
 */
bool ValidateMessage::checkCountryCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	int i=0;
	//Check if Null value
	if(fieldMap[18]->m_isSet==false)
	{
		status= true;
	}
	else
	{
		//length pointer
		//memory is released at the end of the function
		int* dataLen = NULL;
		dataLen = new int;

		//check if memory for the int allocated
		if(dataLen == NULL)
		{
			statusRef.update (false, ENOMEM, "Failure - Country Code - Insufficient memory");

			status = false;
		}//end of dataLen if
		else
		{
			//get the data from the field
			//memory is released at the end of the function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[18]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);
			
			if(dataPtr==NULL)
			{
				statusRef.update (false, VALIDATION_FAILED, "Failure - Country Code - No field data retrieved");

				status=false;
			}
			else
			{
				//append a null character to the data for checking in a temp array
				//memory deleted at the ned of the function
				char* tempPtr = NULL;
				tempPtr = new char[*dataLen+1];

				if(tempPtr != NULL)
				{
					memset(tempPtr, 0, *dataLen+1);				
					
					//copy the data
					for(i=0; i<*dataLen; i++)
					{
						tempPtr[i] = dataPtr[i];
					}
					tempPtr[i] = '\0';

					//call the hash function to check if data is valid
					const char* countryCode=NULL;
					countryCode = isoCountryIsValid(tempPtr,3);

					if(countryCode==NULL)
					{
						status=false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Country Code Not Valid");
					}
					else
					{
						status=true;
					}
					
					//release memory allocated to the temp array
					delete [] tempPtr;
				}
				else
				{
					statusRef.update (false, ENOMEM, "Failure - Country Code - Insufficient memory");

					status = false;

				}//end of tempPtr if-else
			}//end of dataPtr if-else
			
			//delete memory allocated for the out parameter for length
			delete dataLen;
		}//end of dataLen if-else
	}

	return status;
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
 *		Check Bit-22.
 *		The value for this bit position defines the method that was used 
 *		to enter the cardmember's number at the Point of Sale. Values in each 
 *		byte in this field must be in the ISO data code table as expressed
 *      below in the comments for each field. Otherwise return false with
 *		the ISOStatus object updated to reflect the failure
 */
bool ValidateMessage::checkPOSData(FieldMapElement* fieldMap[],int mapSize,ISOStatus& statusRef)
{
	bool status = false;

	//Check if bit is set 
	status = fieldMap[21]->m_isSet;
	
	if (status!=false)
	{
		//length pointer
		//memory is released at the end of the function
		int* dataLen = NULL;
		dataLen = new int;

		if(dataLen == NULL)
		{
			status = false;
			statusRef.update (false, ENOMEM, "Failure - POS data - Insufficient memory");
		}
		else
		{
			//get the data from the field
			//memory is released at the end of the function
			unsigned char* posDataCode=NULL;
			posDataCode = fieldMap[21]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if (posDataCode==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - POS Data Code - No field data retrieved");
			}
			else
			{
				//Check the individual bytes of the POS Data

				/**************************************************************************
				* Byte 1 - Card Data Input Capability
				*    This byte indicates the maximum capability of the device used to 
				*    originate this transaction...
				* 
				*    0 - Unknown
				*    1 - Manual, no terminal
				*    2 - Magnetic stripe read
				*    5 - ICC, chipcard capable terminal
				*    6 - Key entered
				**************************************************************************/
				switch (posDataCode[0])
				{
					case '0':
					case '1':
					case '2':
					case '5':
					case '6':
						status = true;
		    			break;
  					default:
						status = false;
				} // posDataCode[0] 

				/**************************************************************************
				* Byte 2 - Cardholder Authentication Capability
				*    This byte indicates the primary means used to verify the cardholder's 
				*    identity at this terminal. When no order of priorities can be made,
				*    the value '6' must be used.
				* 
				*    0 - No electronic authentication, or unknown
				*    2 - Electronic signature analysis (NOT TO BE USED CURRENTLY)
				*    6 - Other
				**************************************************************************/
				if (status == true)
				{
					switch (posDataCode[1])
					{
						case '0':
						case '6':
							status = true;
							break;
						
						case '2':
						default:
						  status = false;
					}
				}// posDataCode[1] 


				/**************************************************************************
				* Byte 3 - Card Capture Capability
				*    This byte indicates if the terminal is capable of capturing card data.
				* 
				*    0 - None or unknown
				*    1 - Capture
				**************************************************************************/
				if (status == true)
				{
					switch (posDataCode[2])
					{
					  case '0':
					  case '1':
							status = true;
							break;
					  default:
							status = false;
					}
				} // posDataCode[2] 


				/**************************************************************************
				* Byte 4 - Operating Environment
				*    This byte indicates the terminal's location and if it is attended
				*    by the card acceptor
				* 
				*    0 - No terminal used or unknown
				*    1 - On  premises of Card Acceptor,   attended
				*    2 - On  premises of Card Acceptor, unattended
				*    3 - Off premises of Card Acceptor,   attended
				*    4 - Off premises of Card Acceptor, unattended
				*    5 - On  premises of Cardholder,    unattended
				*    9 - Internet originated, delivery mode unknown, unspecified
				*    S - Internet originated, electronic delivery of product
				*    T - Internet originated, physical delivery of product
				*    U - RESERVED FOR AMEX USE
				**************************************************************************/
				if (status == true)
				{	
				   switch (posDataCode[3])
				   {
					  case '0':
					  case '1':
					  case '2':
					  case '3':
					  case '4':
					  case '5':
					  case '9':
					  case 'S':
					  case 'T':
						  status = true;
						  break;

					  case 'U':
					  default:
						  status = false;
				   }
				} // posDataCode[3] 


				/**************************************************************************
				* Byte 5 - Cardholder Present
				*    This byte indicates if the Cardholder is present at Point of Service,
				*    and if not, why...
				* 
				*    0 - Cardholder present
				*    1 - Cardholder not present, unspecified, unknown
				*    2 - Cardholder not present, mailorder
				*    3 - Cardholder not present, telephone
				*    4 - Cardholder not present, standing authorization
				*    5 - Cardholder not present, electronic transaction
				*        RESERVED BY AMEX FOR FUTURE USE...
				*    9 - Cardholder not present, recurrent billing
				**************************************************************************/
				if (status == true)
				{
					switch (posDataCode[4])
					{
					  case '0':
					  case '1':
					  case '2':
					  case '3':
					  case '4':
					  case '9':
						  status = true;
						  break;

					  case '5':
					  default:
						 status = false;
					}
				} // posDataCode[4]


				/**************************************************************************
				* Byte 6 - Card Present
				*    This byte indicates if the card is present at the point of service.
				* 
				*    0 - Card not present
				*    1 - Card present
				*    S - SET Transaction, Not Certificated - equivalent to card not present
				*    T - SET Transaction, Certificated     - equivalent to card present
				*    U - Internet, no security
				*    V - Internet, SSL security
				**************************************************************************/
				if (status == true)
				{
					switch (posDataCode[5])
					{
						  case '0':
						  case '1':
						  case 'S':
						  case 'T':
						  case 'U':
						  case 'V':
							  status = true;
							  break;

						  default:
					  			status = false;
					}
				} // posDataCode[5] 


				/**************************************************************************
				* Byte 7 - Card Data Input Mode
				*    This byte indicates the method used to capture information from card.
				* 
				*    0 - Unspecified, unknown, track reconstructed
				*    1 - Manual, no terminal
				*    2 - Magnetic stripe read (Byte 7 = 2 only if this tx contains intact
				*        track 1 or track 2 data captured from the magnetic stripe.
				*    5 - ICC (Transaction involving chip read)
				*    6 - Key entered, terminal
				*    S - AMEX RESERVED USE, CID read from mag stripe, Field 53 must exist
				*        and be correctly formatted
				*    T - AMEX RESERVED USE, Manual entry CID, Field 53 must exist and be 
				*        correctly formatted
				*    W - Combination of codes '2' and 'S'; indicates track 1 & 2 data
				*        and manually entered CID (Field 53) are present in this tx.
				**************************************************************************/
				if(status == true)
				{
					switch (posDataCode[6])
					{
						  case '0':
						  case '1':
						  case '5':
						  case '6':
						  case 'S':
						  case 'T':
						  case 'W':
								status = true;
								break;

						  case '2':
					  			if(fieldMap[34] != NULL)
								{
									if(fieldMap[44] != NULL)
									{
										status = fieldMap[34]->m_isSet || fieldMap[44]->m_isSet;
									}
									else
									{
										status = fieldMap[34]->m_isSet;
									}
								}
								else if(fieldMap[44] != NULL)
								{
									status = fieldMap[44]->m_isSet;
								}
								else
									status = false;
								break;

						  default:
								status = false;
					}  
				}// posDataCode[6]


				/**************************************************************************
				* Byte 8 - Cardholder Authentication Method
				*    This byte indicates the method for verifying the cardholder ident
				* 
				*    0 - Not authenticated, unknown
				*    1 - PIN
				*    S - Electronic Ticket Environment
				*    T - SET Certification entity is AMEX
				**************************************************************************/
				if (status == true)
				{
					switch (posDataCode[7])
					{
						  case '0':
						  case '1':
						  case 'S':
						  case 'T':
							  status = true;
							  break;

						  default:
					  			status = false;
					}
				} // posDataCode[7] 


				/**************************************************************************
				* Byte 9 - Cardholder Authentication Entity
				*    This byte indicates the entity verifying the cardholder identity
				* 
				*    0 - Not authenticated, unknown
				*    1 - By Merchant
				*    2 - Other
				**************************************************************************/
				if (status == true)
				{
					switch (posDataCode[8])
					{
						  case '0':
						  case '1':
						  case '2':
							  status = true;
							  break;

						  default:
					  			status = false;
					}
				} // posDataCode[8] 


				/**************************************************************************
				* Byte 10 - Card Data Output Capability
				*    This byte indicates the ability of the terminal to update the card.
				* 
				*    0 - Unknown
				*    1 - None
				**************************************************************************/
				if (status == true)
				{
					   switch (posDataCode[9])
					   {
						  case '0':
						  case '1':
							  status = true;
							  break;

						  default:
								status = false;
					   } // posDataCode[9] 

				}


				/**************************************************************************
				* Byte 11 - Terminal Output Capability
				*    This byte indicates the ability of the terminal to print and/or 
				*    display messages
				* 
				*    0 - Unknown
				*    1 - None
				*    2 - Printing
				*    3 - Display
				*    4 - Printing and Display
				**************************************************************************/
				if (status == true)
				{
					switch (posDataCode[10])
					{
						  case '0':
						  case '1':
						  case '2':
						  case '3':
						  case '4':
							  status = true;
							  break;

						  default:
								status = false;
					}
				} // posDataCode[10] 


				/**************************************************************************
				* Byte 12 - PIN Capture Capability
				*    This byte indicates the PIN length that the terminal is capable of
				*    capturing
				* 
				*    0 - No PIN capture capability
				*    1 - Unknown
				**************************************************************************/
				if (status == true)
				{
					   switch (posDataCode[11])
					   {
						  case '0':
						  case '1':
							  status = true;
							  break;

						  default:
							 status = false;
					   }
				} // posDataCode[11] 
				
				if(status == false)
				{
					statusRef.update (false, VALIDATION_FAILED, "Failure - POS Data Code invalid");
				}
			}//end of posDataCode if-else
		
			//release memory allocated to dataLen 
			delete dataLen;
		}//end of dataLen if-else
	}
 	else
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - POS Data Code - Field not set");
	}

 	return status;
}
