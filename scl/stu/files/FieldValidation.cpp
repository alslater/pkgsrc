/**************************************************************************** 
Program : FieldValidation.cpp
Function: Field validation functions.Implements FieldValidation.h
Written : 22 May 2001
Author  : Subbu G Gowreddy
Modified :
		13 June 2001
			- Remove the chartype argument, as all data sent is in the ASCII fomat
			- The data received is no more null terminated, hence the methods
			  receive the length of the char array
     
****************************************************************************/

//standard includes
#include <string.h>
#include <stdlib.h>
#include "FieldValidation.h"

//specific includes
#include "Enumerations.h"
#include "CharUtility.h"

/****************************************************************************
* Function : checkPackedBCDData
* Desc     : checks whether the data passed to it is PackedBCD.
* Input    : char* value, int dataLen, ISOStatus& statusRef
* Returns  : boolean. True if the Data is, false if not.
* Scope    : public
******************************************************************************/
bool FieldValidation::checkPackedBCDData(const unsigned char* value,int dataLen, ISOStatus & statusRef)
{
	//boolean variable for keeping track of the status of operations
	bool result = false;

	// Allowed 0-9 in high nibble and low nibble.
	for (size_t i=0; i < dataLen; i++)
	{
		if ((value[i] & 0xf0) > 0x90)
		{
			result = false;
			break;
		}
		if ((value[i] & 0xf) > 9)
		{
			result = false;
			break;
		}
		result = true;
	}

	//set the status codes
	if(!result)
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Only PackedBCD data is allowed");

		result = false;
	}
	return result;
}

/****************************************************************************
* Function : checkNumericData
* Desc     : checks whether the data passed to it is Numeric.
* Input    : char* value, int dataLen, ISOStatus& statusRef
* Returns  : boolean. True if the Data is, false if not.
* Scope    : public
* implementation : 1.check if the string is EBCDIC if so convert to ASCII
*				   2.check if the data is valid by checking the ascii value of 
*					each character in the string.
*				   3.Return true if the data is valid else return false. Set the 
*				    status codes accordingly.
******************************************************************************/
bool FieldValidation::checkNumericData(const char* value,int dataLen, ISOStatus & statusRef)
{
	//boolean variable for keeping track of the status of operations
	bool result = false;

	//data whithin the ASCII values 48 and 57 is numeric
	for(int i=0; i<dataLen; i++)
	{
		if((value[i]) >= 48 && (value[i]) <= 57)
		{
			result = true;
		}
		else
		{
			result = false;
			break;
		}
	}
	//set the status codes
	if(!result)
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Only Numeric data is allowed");

		result = false;
	}
	return result;
}

/****************************************************************************
* Function : checkDateTime
* Desc     : checks whether the data passed to it is a valid date.
* Input    : char* value, int dataLen, ISOStatus& statusRef
* Returns  : boolean. True if the Data is, false if not.
* Scope    : public
* implementation : 1.check if the string is EBCDIC if so convert to ASCII
*				   2.check if the data is numeric by checking the ascii value of 
*					each character in the string.
*				   3.If numeric check the length of the data passed and call the 
*                    respective function.
*				   4.Return true if the data is valid else return false. Set the 
*				    status codes accordingly.
******************************************************************************/

bool FieldValidation::checkDateTime(const char* value, int dataLen, ISOStatus & statusRef)
{
	//boolean value for the status of operations
	bool result = false;
	
	//check if the data sent is numeric or not
	for(int i=0; i<dataLen; i++)
	{
		//data whithin the ASCII values 48 and 57 is numeric
		if((value[i]) >=48 && (value[i]) <= 57)
		{ 
			result=true; 
		}
		else
		{
			result=false;
			break;
		}
	}

	//do a check for valid date and time field data
	if(result)
	{
		switch(dataLen)
		{
			//check for date - YYMM
			case 4:
				result = checkDateTime4(value);
				break;
			//check for data - 	MMDDhhmmss
			case 10:
				result = checkDateTime10(value);
				break;
			//check for date - YYMMDDhhmmss
			case 12:
				result = checkDateTime12(value);
				break;
			//no other format allowed
			default:
				result=false;
		}
        //set the status codes
		if(!result)
		{ 
			statusRef.update (false, VALIDATION_FAILED, "Failure - Invalid Date");

			result = false;
		}

	}
	else
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Only Numeric data is allowed.");

		result = false;
	}
	return result;
}

/****************************************************************************
* Function : checkAlphaNumeric
* Desc     : checks whether the data passed to it is AlphaNumeric.
* Input    : char* value, int dataLen, ISOStatus& statusRef
* Returns  : boolean. True if the Data is, false if not.
* Scope    : public
* implementation : 1.check if the string is EBCDIC if so convert to ASCII
*				   2.check if the data is valid by checking the ascii value of 
*					each character in the string.
*				   3.Return true if the data is valid else return false. Set the 
*				    status codes accordingly.
******************************************************************************/

bool FieldValidation::checkAlphaNumeric(const char* value,int dataLen, ISOStatus & statusRef)
{
	bool result=false;

	for(int i=0; i<dataLen; i++)
	{
		// Data with in Ascii values 48 and 57 is numeric
		//data whithin the ASCII values 65 and 90 is A to Z
		//data whithin the ASCII values 97 and 112 is a to z
		if((value[i]) >= 48 && (value[i]) <= 57 || (value[i]) >= 65 && (value[i]) <= 90 || (value[i]) >= 97 && (value[i]) <= 122)
		{
			result = true;
		}
		else
		{
			result = false;
			break;
		}
	}
	//set the status codes
	if(!result)
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Only Alphanumeric data is allowed");

		result = false;
	}
		
	return result;
}

/****************************************************************************
* Function : checkAlphaNumericS
* Desc     : checks whether the data passed to it is AlphaNumeric and special characters.
* Input    : char* value, int dataLen, ISOStatus& statusRef
* Returns  : boolean. True if the Data is, false if not.
* Scope    : public
* implementation : 1.check if the string is EBCDIC if so convert to ASCII
*				   2.check if the data is valid by checking the ascii value of 
*					each character in the string.
*				   3.Return true if the data is valid else return false. Set the 
*				    status codes accordingly.
******************************************************************************/

bool FieldValidation::checkAlphaNumericS(const char* value,int dataLen, ISOStatus & statusRef)
{
	bool result = false;

	//all data between 33 and 126 is valid - 
	//it includes alphabets, numbers and special characters
	for(int i=0; i<dataLen; i++)
	{
		if(((value[i]) >= 32 && (value[i]) <= 126) || value[i] == 9)
		{
			result = true;
		}
		else
		{
			result=false;
			break;
		}
	}
	if(!result)
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Only Alphanumeric data with special characters is allowed");

		result = false;
	}

	return result;
	
}

/****************************************************************************
* Function : checkAlphaNumericP
* Desc     : checks whether the data passed to it is AlphaNumeric. Spaces are allowed
* Input    : char* value, int dataLen, ISOStatus& statusRef
* Returns  : boolean. True if the Data is, false if not.
* Scope    : public
* implementation : 1.check if the string is EBCDIC if so convert to ASCII
*				   2.check if the data is valid by checking the ascii value of 
*					each character in the string.
*				   3.Return true if the data is valid else return false. Set the 
*				    status codes accordingly.
******************************************************************************/

bool FieldValidation::checkAlphaNumericP(const char* value,int dataLen, ISOStatus & statusRef)
{
	bool result=false;
	
	//used to count the number of spaces and tab characters inserted in the string.
	int spaceCnt = 0;

	for(int i=0; i<dataLen; i++)
	{
		// Data with in Ascii values 48 and 57 is numeric
		//data whithin the ASCII values 65 and 90 is A to Z
		//data whithin the ASCII values 97 and 112 is a to z
        //data whithin the ASCII values 9 and 13 represent all kinds of spaces.
		//data whithin the ASCII value 32 denotes the spacebar(space)
		if((value[i]) >= 48 && (value[i]) <= 57 || (value[i]) >= 65 && (value[i]) <= 90 || (value[i]) >= 97 && (value[i]) <= 122 || (value[i]) >= 9 && (value[i]) <= 13 || (value[i]) == 32)
		{
			if((value[i]) == 32 || ((value[i]) >=9 && (value[i]) <= 13))
			{
				spaceCnt++;
			}				
			result = true;
		}
		else
		{
			result = false;
			break;
		}
	}
	//set the status codes.
	if(result)
	{
		if(dataLen==spaceCnt)
		{
			statusRef.update (false, VALIDATION_FAILED, "Failure - Data contains only white spaces");

			result = false;
		}				
	}
	else
	{
		statusRef.update (false, VALIDATION_FAILED, "Failure - Only Alphanumeric data with white spaces is allowed");

		result = false;
	}

	return result;
}

/****************************************************************************
* Function : checkDateTime4
* Desc     : checks whether the data passed to it is a valid date.
* Input    : const char* datVal
* Returns  : boolean. True if the Data is, false if not.
* Scope    : private
* implementation : 1.split the string in to year and month strings and store it 
*				    in local string variables.
*				   2.check if the data is valid by converting each string to int 
*					 and checking the limits.
*				   3.delete the local string pointers.
*				   4.Return true if the data is valid else return false. Set the 
*				    status codes accordingly.

******************************************************************************/

bool FieldValidation::checkDateTime4(const char* dateVal)
{
	int i = 0;
	bool result;

	//Declare two local string pointers to hold the values of year and month values 
	//after splitting the string passed to the function.
	char year[3];
	char month[3];
	//Initialize the pointer to char with NULL
	memset(year,0, 3);
	memset(month,0, 3);

	//split the main string and copy in to the respective year and month arrays
	while(i<2)
	{
		year[i]= *(dateVal+i);
		month[i] = *(dateVal+i+2);
		i++;
	}

	int yearToCheck  = atoi(year);
	int monthToCheck = atoi(month);


    //check if the values are valid
	if(yearToCheck >=0 && yearToCheck <= 99 && monthToCheck >=1 && monthToCheck <=12)
		result = true;
	else
		result = false;

	return result;
}

/****************************************************************************
* Function : checkDateTime10
* Desc     : checks whether the data passed to it is a valid date.
* Input    : const char* dateVal
* Returns  : boolean. True if the Data is, false if not.
* Scope    : private
* implementation : 1.split the string in to year and month strings and store it 
*				    in local string variables.
*				   2.check if the data is valid by converting each string to int 
*					 and checking the limits.
*				   3.delete the local string pointers.
*				   4.Return true if the data is valid else return false. Set the 
*				    status codes accordingly.

******************************************************************************/


bool FieldValidation::checkDateTime10(const char* dateVal)
{
	int i = 0;
	bool result;
    //Declare five local string pointers to hold the values of day,month,hour,minute and
	//second values after splitting the string passed to the function.
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char seconds[3];

	//Initialize the pointer to char with NULL
	memset(month,0, 3);
	memset(day,0, 3);
	memset(hour,0, 3);
	memset(minute,0, 3);
	memset(seconds,0, 3);
	

	//split the main string and copy the values in to the respective arrays
	while(i<2)
	{
		month[i]   = *(dateVal+i);
		day[i]     = *(dateVal+i+2);
		hour[i]    = *(dateVal+i+4);
		minute[i]  = *(dateVal+i+6);
		seconds[i] = *(dateVal+i+8);
		i++;
	}
	
	//Local variables to hold the month,date,hour,minute and second values after 
	//converting from ascii to int

	int monthToCheck = atoi(month);
	int dateToCheck  = atoi(day );
	int hourToCheck  = atoi(hour );
	int minuteToCheck = atoi(minute );
	int secondToCheck = atoi(seconds );

	int dateLimit;

	
	//set the date limits for each month.

	switch (monthToCheck )
	{

	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		 dateLimit = 31;
		 break;

	case 4:
	case 6:
	case 9:
	case 11:
		 dateLimit = 30;
		 break;

	case 2:
		 dateLimit = 29;
		 break;
	default:
		dateLimit = 31;
	}


    //check if the values are valid
	if(monthToCheck>=1 && monthToCheck <= 12 && dateToCheck >=1 && dateToCheck <=dateLimit && hourToCheck >=0 && hourToCheck <= 23 && minuteToCheck >=0 && minuteToCheck <= 59 && secondToCheck >=0 && secondToCheck <= 59)
		result = true;
	else
		result = false;
	
	return result;

}

/****************************************************************************
* Function : checkDateTime12
* Desc     : checks whether the data passed to it is a valid date.
* Input    : const char* dateVal
* Returns  : boolean. True if the Data is, false if not.
* Scope    : private
* implementation : 1.split the string in to year and month strings and store it 
*				    in local string variables.
*				   2.check if the data is valid by converting each string to int 
*					 and checking the limits.
*				   3.delete the local string pointers.
*				   4.Return true if the data is valid else return false. Set the 
*				    status codes accordingly.

******************************************************************************/


bool FieldValidation::checkDateTime12(const char* dateVal)
{
	int i = 0;
	bool result;

    //Declare five local string pointers to hold the values of year,month,day,hour,minute and
	//second values after splitting the string passed to the function.
	char year[3];
	char month[3];
	char day[3];
	char hour[3];
	char minute[3];
	char seconds[3];

	//Initialize the pointer to char with NULL
	memset(year,0, 3);
	memset(month,0, 3);
	memset(day,0, 3);
	memset(hour,0, 3);
	memset(minute,0, 3);
	memset(seconds,0, 3);

	//split the main string and copy the values in to the respective arrays
	while(i<2)
	{
		year[i]    = *(dateVal+i);
		month[i]   = *(dateVal+i+2);
		day[i]     = *(dateVal+i+4);
		hour[i]    = *(dateVal+i+6);
		minute[i]  = *(dateVal+i+8);
		seconds[i] = *(dateVal+i+10);
		i++;
	}
	
	//Local variables to hold the year,month,date,hour,minute and second values 
	//after converting from ascii to int

	int yearToCheck  = atoi(year);
	int monthToCheck = atoi(month);
	int dateToCheck  = atoi(day);
	int hourToCheck  = atoi(hour);
	int minuteToCheck = atoi(minute);
	int secondToCheck = atoi(seconds);

	//to check the datelimit of each month
	int dateLimit;

     //set the date limits for each month.
	switch (monthToCheck )
	{

	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		 dateLimit = 31;
		 break;

	case 4:
	case 6:
	case 9:
	case 11:
		 dateLimit = 30;
		 break;

	case 2:
		 //check for leap year
		 if(yearToCheck % 4 == 0)
		 {
			if(yearToCheck % 100 == 0)
			{
				if(yearToCheck % 400 == 0)
					dateLimit = 29;
				else
					dateLimit = 28;
			}
			else
				dateLimit = 29;
		 }
		 else
			dateLimit = 28;
		 break;

	default:
		dateLimit = 31;
	}

    //check if the values are valid
	if(yearToCheck >= 0 && yearToCheck <= 99 && monthToCheck>=1 && monthToCheck <= 12 && dateToCheck >=1 && dateToCheck <=dateLimit && hourToCheck >=0 && hourToCheck <= 23 && minuteToCheck >=0 && minuteToCheck <= 59 && secondToCheck >=0 && secondToCheck <= 59)
		result = true;
	else
		result = false;

	return result;

}


/*************************************************************************
* Function : checkBinaryData
* Desc     : checks whether the data passed to it is binary.
* Input    : char* value, int charType, ISOStatus& statusRef
* Returns  : boolean. True if the Data is valid, false if not.
* Note	   : To be defined later
* 
***************************************************************************/
bool FieldValidation::checkBinaryData(const char* vlaue,int charType, ISOStatus & statusRef)
{
	return true;
}
