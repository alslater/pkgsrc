/*********************************************************************
*
*   File name:
*       ISO1804Val.cpp
*
*   Contents:
*       ISO1804Val class functions
*
*   Description
*
*        This file contains the implementations of the functions in ISO1804Val
*        class. These functions validate the ISO1804NetworkMgmt message.
*
*
*   See Also:
*        ISO1804Val.h   
*
*   Created:
*       19 June 2001 Arun G.
*
*   Modified:
*		26 June 2001 Shubha Kumar
*			-Cleaned up the code for pointers and memory allocation
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
#include "ISO1804Val.h"


//Default Constructor
ISO1804Val::ISO1804Val()
{	}
	
//Destructor
ISO1804Val::~ISO1804Val()
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
 *		2. checkProcessingCode()
 *		3. checkFunctionCode()
 *
 */
bool ISO1804Val::performValidation(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	
	//check required fields
	status = checkRequiredFields(fieldMap,mapSize,statusRef);
	//check for the status and return if false
	if(status == 0)
	{
		return status;
	}

	//check Processing code
	status = checkProcessingCode(fieldMap,mapSize,statusRef);
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
 *		Checks if the following bit positions are set: Bit-3, Bit-11 and Bit 24
 *		If all the bits are set, return TRUE.  Else return FALSE 
 *		with the ISOStatus object updated to reflect the failure.
 *	
 */	
bool ISO1804Val::checkRequiredFields(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//counter variable
	int i = 0;

	//check each fieldMap array element
	for(i = 1;i < mapSize; i++)
	{
		//Check the bit positions 3,11 and 24.
		//the index position of the array starts from 0
		switch(i)
		{
			case 2:
			case 10:
			case 23:
				//if the field has not been set, return false
				if(fieldMap[i]->m_fieldPointer == NULL)
					status = false;
				else
					status=fieldMap[i]->m_isSet;
				break;
			default:
				//all other cases return true
				status = true;

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

			if(newErrMsg == NULL)
			{
				statusRef.setResultCode(VALIDATION_FAILED);
				statusRef.setResultDesc("Failure - Check reuired fields - Insufficient memory");
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
 *		Checks the bit position 3 which can have the value: 000000
 *		If the processing code is valid, return TRUE else return FALSE with the ISOStatus
 *		object updated to reflect the failure
 *
 */
bool ISO1804Val::checkProcessingCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
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
					case COMMUNICATION_VERIFICATION:
						status=true;
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
 *		2. The following is the only valid value for 1804 message type: 831
 *		3. If the validation is correct, return TRUE.  Else return FALSE with the ISOStatus object updated to reflect the failure.
 *
 */
bool ISO1804Val::checkFunctionCode(FieldMapElement* fieldMap[],int mapSize,ISOStatus &statusRef)
{
	bool status = false;
	//array of valid function codes
	//release memory allocated at the end of the function
	char funCode[] = "831";
	//counter variable
	int i = 0;
	
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
			//initialize dataLen
			*dataLen = 0;

			//get the data from the field
			//memory is released at the end of the function
			unsigned char* dataPtr=NULL;
			dataPtr = fieldMap[23]->m_fieldPointer->getFieldInt (ASCII,dataLen,statusRef);

			if(dataPtr==NULL)
			{
				status = false;
				statusRef.update (false, VALIDATION_FAILED, "Failure - Function Code - Field data not retrieved");
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
					statusRef.update (false, ENOMEM, "Failure - Function Code - Insufficient memory");
				}
				else
				{
					//set each position to null
					memset(tempPtr, 0, *dataLen+1);

					//copy data to null terminated temp buffer for comparison
					for(i=0; i<*dataLen; i++)
					{
						tempPtr[i] = dataPtr[i];
					}
										
					//check for valid processing code
					if(strcmp((char *)tempPtr, funCode) == 0)
					    status = true;
					else
					{
						status = false;
						statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Function Code");
					}
					
					//release memory allocated to tempPtr 
					delete [] tempPtr;

				}//end of tempPtr if-else
			}
			
			//release memory allocated to out parameter pointer for length
			delete dataLen;		
		}//end of dataLen if-else
	}//end of fieldMap if-else
	
	return status;
}
