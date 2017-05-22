/*********************************************************************
*
*   File name:
*       FieldValidation.h
*
*   Contents:
*       FieldValidation class.
*
*   Description
*
*          This header file contains the definitions for the FieldValidation
*		   class, which contains method signatures to validate the data.
*
*   See Also:
*
*
*
*   Created:
*       05/21/01 Subbu G Gowreddy
*
*   Modified:
*		13 June 2001 Shubha Kumar
*			-The methods to take a not null terminated char array
*			 along with the length of the same.
*
*
**********************************************************************/




#ifndef FIELDVALIDATION_H
#define FIELDVALIDATION_H

//specific includes
#include "ISOStatus.h"

/**************************************************************************
 *
 * CLASS NAME:          FieldValidation
 *
 * SCOPE:               All methods are of public scope except for three methods
 *						which are used to validate different length date strings.
 *						These three are private by scope. These are called by a
 *						public method which validates date. All are static.
 *
 * DESCRIPTION:			Contains method signatures to validate data sent to it.
 *
 **************************************************************************
 */


class FieldValidation
{
public:
	/************************************************************
	* Function : checkPackedBCDData
	* Desc     : checks whether the data passed to it is PackedBCD.
	* Input    : char* value, int dataLen, ISOStatus& statusRef
	* Returns  : boolean. True if the Data is valid , false if not.
	*
	*
	**************************************************************/
	static bool checkPackedBCDData(const unsigned char*,int ,ISOStatus &);

	/************************************************************
	* Function : checkNumericData
	* Desc     : checks whether the data passed to it is Numeric.
	* Input    : char* value, int dataLen, ISOStatus& statusRef
	* Returns  : boolean. True if the Data is valid , false if not.
	*
	*
	**************************************************************/
	static bool checkNumericData(const char*,int ,ISOStatus &);

	/********************************************************************
	* Function : checkDateTime
	* Desc     : checks whether the data passed to it is a valid DateTime.
	*			 This calls the private static methods checkDateTime4 or
	*            checkDateTime10 or checkDateTime12 depending upon the
	*            length of the DateTime string passed.
	* Input    : char* value, int dataLen, ISOStatus& statusRef
	* Returns  : boolean. True if the Data is valid, false if not.
	*
	*
	**********************************************************************/
	static bool checkDateTime(const char*,int ,ISOStatus &);


	/**********************************************************************
	* Function : checkAlphaNumeric
	* Desc     : checks whether the data passed to it is AlphaNumeric.
	* Input    : char* value, int dataLen, ISOStatus& statusRef
	* Returns  : boolean. True if the Data is a valid, false if not.
	*
	*
	************************************************************************/
	static bool checkAlphaNumeric(const char*,int , ISOStatus &);


	/*****************************************************************************
	* Function : checkAlphaNumericS
	* Desc     : checks whether the data passed to it is AlphaNumeric.
	*			 It can contain special characters.
	* Input    : char* value, int dataLen, ISOStatus& statusRef
	* Returns  : boolean. True if the Data is valid, false if not.
	*
	*
	*******************************************************************************/
	static bool checkAlphaNumericS(const char*,int , ISOStatus &);


	/*******************************************************************************
	* Function : checkAlphaNumericP
	* Desc     : checks whether the data passed to it is AlphaNumeric.
	*            It can contain spaces.
	* Input    : char* value, int dataLen, ISOStatus& statusRef
	* Returns  : boolean. True if the Data is valid, false if not.
	*
	*
	*********************************************************************************/
	static bool checkAlphaNumericP(const char*,int , ISOStatus &);

	/*******************************************************************************
	* Function : checkBinaryData
	* Desc     : checks whether the data passed to it is binary.
	* Input    : char* value, int dataLen, ISOStatus& statusRef
	* Returns  : boolean. True if the Data is valid, false if not.
	*
	*
	********************************************************************************/
	static bool checkBinaryData(const char*,int , ISOStatus &);
private:

	/********************************************************************
	* Function : checkDateTime4
	* Desc     : checks whether the data passed to it is a valid DateTime.
	*			 This function takes a datetime string of length 4 only and
	*            it checks for a valid year in the first two bytes and a
	*            valid month in the next two bytes.
	* condition: Year should be between 0 and 99, month should be between
	*            1 and 12.
	* Input    : char* value
	* Returns  : boolean. True if the Data is valid, false if not.
	*
	*
	**********************************************************************/
	static bool checkDateTime4(const char*);

	/**********************************************************************
	* Function : checkDateTime10
	* Desc     : checks whether the data passed to it is a valid DateTime.
	*			 This function takes a datetime string of length 10 only and
	*            it checks for a valid month in the first two bytes, a
	*            valid date in the next two bytes, valid hour in the 5th and 6th
	*            bytes, valid minute in 7th and 8th bytes, valid second in the
	*            last two bytes.
	* condition: Month should be between 1 and 12.
	*            Date should be between  0 and 31.
	*            Hour should be between 0 and 23.
	*            Minute should be between 0 and 59.
	*            Second should be between 0 and 59.
	* Input    : char* value
	* Returns  : boolean. True if the Data is valid, false if not.
	*
	*
	**********************************************************************/
	static bool checkDateTime10(const char*);

	/**********************************************************************
	* Function : checkDateTime12
	* Desc     : checks whether the data passed to it is a valid DateTime.
	*			 This function takes a datetime string of length 12 only and
	*            it checks for a valid Year in the first two bytes, a
	*            valid month in the next two bytes, valid Date in the 5th and 6th
	*            bytes, valid Hour in 7th and 8th bytes, valid Minute in the
	*            9th and 10th bytes, valid second in the last two bytes.
	* condition: Year should be between 0 and 99.
	*            Month should be between 1 and 12.
	*            Date should be between  0 and 31.
	*            Hour should be between 0 and 23.
	*            Minute should be between 0 and 59.
	*            Second should be between 0 and 59.
	* Input    : char* value
	* Returns  : boolean. True if the Data is valid, false if not.
	*
	*
	**********************************************************************/
	static bool checkDateTime12(const char*);

};

#endif

