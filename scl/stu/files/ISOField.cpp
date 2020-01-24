/*********************************************************************
*
*   File name:
*       ISOField.cpp
*   Contents:
*       Implementation of the Constructors and the methods described in the
*       header file for ISOFieldFixed, ISOFieldLLVar, ISOFieldLLLVar classes
*
*       
*   Description
*
*          This source code file contains the implementation of the setField(),
*          getField(), serialize() methods for these derived classes and also
*          for the constructor.
*
*
*   See Also:
*        Char_Util.h
*        Enumerations.h
*        ISOStatus.h
*        FieldMapElement.h
*		 ISOField.h
*
*
*   Created:
*       05/18/01 Shubha Kumar
*
*   Modified:
*		12 June 2001 Shubha Kumar	
*				-Implement the length argument. Update the "size" attribute with the data in the length argument.
*				-Add a method getSize to return the actual data length stored in the "size" attribute
*
*		06 July 2001 Shubha Kumar
*				-Modify the setField() for all the field types to do all operations on a copy of the data
*				 sent in by the user and not the orignal
*				-Remove macros to define length of prefix for LLVar and ISOFieldLLLVar when serializing
*				 as added in the Enumerations.h
*				-Fixed the memory leaks in setField(), getField() and serialize() 
*				 methods of all the classes.
*       14 September 2001 Lonnie L. Filbrun
*		        re-wrote the set and get field methods to fix problems with returned
*               memory and copying data multiple times. setField allocates a copy, getField
*               just returns a pointer to the data that the field contains.
*       21 September 2001 Lonnie L. Filbrun
*               Modified class names to be more consistent.
*
**********************************************************************/

//Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <malloc.h>

//Package specific header files
#include "CharUtility.h"
#include "Enumerations.h"
#include "ISOField.h"
#include "FieldValidation.h"

//macro to check minimum of two integers
#define mininum(a,b)    (((a) < (b)) ? (a) : (b))

extern int gPackedBCD;

//Default constructor
ISOField :: ISOField()
{
	m_asciiDataPointer = NULL;
	m_ebcdicDataPointer = NULL;

	m_size = 0;
}

//Definitions of the ISOField constructor and destructor
//Definition of the ISOField Constructor
/* Will initialize the base class by calling the base class constructor
   with argument that represents the data type and the maximum data length.
*/

ISOField :: ISOField(int data, int maxLen)
{
	//assign the data type value
	m_dataType = data;

	//assign the maximum data length allowed for this field
	m_maxDataLen = maxLen;

	// The data is stored here in BOTH places!
	m_asciiDataPointer = NULL;
	m_ebcdicDataPointer = NULL;

	m_size = 0;
}

//Definition of the ISOField Destructor
/* Will release the memory occupied by the member attributes
*/

ISOField :: ~ISOField()
{
	//release the memory occupied by char data pointer
	if (m_asciiDataPointer != NULL)
	{
		delete [] m_asciiDataPointer;
		m_asciiDataPointer = NULL;
	}

	if (m_ebcdicDataPointer != NULL)
	{
		delete [] m_ebcdicDataPointer;
		m_ebcdicDataPointer = NULL;
	}
}

/* Method Name: isPackedBCDField
 *  Return Type: 
 *   boolean : Indicates whether we're using PackedBCD and if so, whether this field would be packed.
*/
bool ISOField::isPackedBCDField() const
{
	return gPackedBCD && (m_fieldType == FIXEDLENGTH) && (m_dataType == NUMERIC);
}

/* Method Name: setField
 *  Arguments:
 *   cType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *              The data will be stored in the specified  encoding format.
 *   data : The actual data to be stored in the bit-field.
 *         Data is represented as a character array.
 *   dataLen : Actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *             the status of operation.  Previous data will be overwritten.
 *
 *
 *  Return Type:
 *   boolean : Indicates status of operation.
 *             TRUE(1) indicates success and FALSE(0) indicates failure.
 *             Client App will have to check the ISOStatus object for
 *             more details in case if the return value is FALSE(0).
 *
 * Implementation Details:
 *  1. Initialize the "charType" attribute with ASCII - data is always stored in this format.
 *	2. Check if the length of data sent in as argument is same as that set in "maxDataLength".
 *	3. Check if the data sent is in the ASCII format - if not convert it to the ASCII before any validation.
 *  4. Check the type of the data in the "dataType" attribute.
 *      Depending on the type call the appropriate method on the "FieldValidation" object.  
 *		If success initialize the "dataPtr" attribute and the "size" attribute.
 *	5. Update the ISOStatus object accordingly.
*/

bool ISOField :: setField(const int cType, const unsigned char *data, const int dataLen, ISOStatus& statusRef)
{
	//counter variable
	int i = 0;

	//to store the status of the field validation performed on the data
	bool status = false;

	//check if the data has been received or not before any validation is done
	if (data == NULL)
	{
		//set the ISOStatus object with no data status code and description
		statusRef.update (false, NO_DATA, "Failure - No data");

		//set the status to false
		status = false;
		return status;
	}//end of null data check

	bool packed(false);
	if (isPackedBCDField() && (dataLen == m_maxDataLen))
	{
		m_size = CharUtility::PackedBCDSize(m_maxDataLen);
		packed = true;
	}
	else if ((m_fieldType == FIXEDLENGTH)
		&& (dataLen == m_maxDataLen)) // FIXED
	{
		//set the actual data length
		m_size = dataLen;
	}
	else if ((m_fieldType != FIXEDLENGTH)
		&& (dataLen > 0)
		&& (dataLen <= m_maxDataLen)) // VARIABLE
	{
		//set the actual data length
		m_size = dataLen;
	}
	else
	{
		//set the ISOStatus object with invalid length of data
		statusRef.update (false, INVALID, "Failure - Invalid length of data");

		//set the status to false
		status = false;
		return status;
	}

	// If the data field already holds
	// data delete it
	if (m_asciiDataPointer != NULL)
	{
		delete [] m_asciiDataPointer;
		m_asciiDataPointer = NULL;
	}

	if (m_ebcdicDataPointer != NULL)
	{
		delete [] m_ebcdicDataPointer;
		m_ebcdicDataPointer = NULL;
	}

	if (packed)
	{
		// do packedBCD stuff

		int actualLen = m_size;

		// Now re-allocate a chunk of memory to
		// hold the new data
		m_asciiDataPointer = new unsigned char [m_maxDataLen + 1];
		if (m_asciiDataPointer == NULL)
		{
			//update the ISOStatus object with the no data code and description
			statusRef.update (false, ENOMEM, "Failure - Insufficient memory");

			status = false;
			return status;
		}

		// Clear out, copy data, and add NUL.
		memset (m_asciiDataPointer, 0, m_maxDataLen + 1);

		// Now re-allocate a chunk of memory to
		// hold the new data
		m_ebcdicDataPointer = new unsigned char [m_maxDataLen + 1];
		if (m_ebcdicDataPointer == NULL)
		{
			//update the ISOStatus object with the no data code and description
			statusRef.update (false, ENOMEM, "Failure - Insufficient memory");

			status = false;
			return status;
		}

		// Clear out and set data
		memset (m_ebcdicDataPointer, 0, m_maxDataLen + 1);

		if (cType == ASCII)
		{
			// if user calling with ASCII we're setting the data so it 
			// won't be packed yet.

			memcpy (m_asciiDataPointer, data, dataLen);
			m_asciiDataPointer[dataLen] = 0;

			CharUtility::toPackedBCDInplace(m_asciiDataPointer, dataLen);

			// Copy to ebcdic array and convert in place
			memcpy(m_ebcdicDataPointer, m_asciiDataPointer, m_size);

			CharUtility::toEbcdicStrInplace (m_ebcdicDataPointer, m_size);
		}

		if (cType == EBCDIC)
		{
			// if user calling with EBCDIC we've received it and it's 
			// already packed. So convert back to ASCII.

			memcpy (m_asciiDataPointer, data, dataLen);
			m_asciiDataPointer[dataLen] = 0;

			CharUtility::toAsciiStrInplace (m_asciiDataPointer, dataLen);

			memcpy (m_ebcdicDataPointer, data, dataLen);
			m_ebcdicDataPointer[dataLen] = 0;
		}

	}
	else
	{
		// Now re-allocate a chunk of memory to
		// hold the new data
		m_asciiDataPointer = new unsigned char [dataLen+1];

		if (m_asciiDataPointer == NULL)
		{
			//update the ISOStatus object with the no data code and description
			statusRef.update (false, ENOMEM, "Failure - Insufficient memory");

			status = false;
			return status;
		}

		// Clear out, copy data, and add NUL.
		memset (m_asciiDataPointer, 0, dataLen+1);

		// Now re-allocate a chunk of memory to
		// hold the new data
		m_ebcdicDataPointer = new unsigned char [dataLen+1];

		if (m_ebcdicDataPointer == NULL)
		{
			//update the ISOStatus object with the no data code and description
			statusRef.update (false, ENOMEM, "Failure - Insufficient memory");

			status = false;
			return status;
		}

		// Clear out, copy data, and add NUL.
		memset (m_ebcdicDataPointer, 0, dataLen+1);

		// at this point we have both buffers full of either ASCII or
		// EBCDIC data.
		// based on the passed in cType convert the data.

		if (cType == ASCII)
		{
			// if user calling with ASCII we need to
			// convert the data in m_ebcdicDataPointer to EBCDIC.

			memcpy (m_ebcdicDataPointer, data, dataLen);
			m_ebcdicDataPointer[dataLen] = 0;

			CharUtility::toEbcdicStrInplace (m_ebcdicDataPointer, dataLen);
			m_ebcdicDataPointer[dataLen] = 0;

			memcpy (m_asciiDataPointer, data, dataLen);
			m_asciiDataPointer[dataLen] = 0;
		}

		if (cType == EBCDIC)
		{
			// if user calling with EBCDIC we need to
			// convert the data in m_asciiDataPointer to ASCII.

			memcpy (m_asciiDataPointer, data, dataLen);
			m_asciiDataPointer[dataLen] = 0;

			CharUtility::toAsciiStrInplace (m_asciiDataPointer, dataLen);
			m_asciiDataPointer[dataLen] = 0;

			memcpy (m_ebcdicDataPointer, data, dataLen);
			m_ebcdicDataPointer[dataLen] = 0;
		}
	}

	//field level validations
	switch (m_dataType)
	{
		//numeric data
	case NUMERIC:
		if (packed)
			status = FieldValidation::checkPackedBCDData(m_asciiDataPointer, m_size, statusRef);
		else
			status = FieldValidation::checkNumericData((char *)m_asciiDataPointer, dataLen, statusRef);
		break;

		//alphanumeric data
	case ALPHANUMERIC:
		status = FieldValidation::checkAlphaNumeric((char *)m_asciiDataPointer, dataLen, statusRef);
		break;

		//alphanumeric data with special characters
	case ALPHANUMERICs:
		status = FieldValidation::checkAlphaNumericS((char *)m_asciiDataPointer, dataLen, statusRef);
		break;

		//alphanumeric data with spaces (pad)
	case ALPHANUMERICp:
		status = FieldValidation::checkAlphaNumericP((char *)m_asciiDataPointer, dataLen, statusRef);
		break;

		//binary data - treat COMPLEX as if it was all binary
	case BINARY:
	case COMPLEX: 
		status = FieldValidation::checkBinaryData((char *)m_asciiDataPointer, dataLen, statusRef);
		break;

		//date and time data
	case DATETIME:
		status = FieldValidation::checkDateTime((char *)m_asciiDataPointer, dataLen, statusRef);
		break;

	}//end of switch(dataType)

	//return the status of the entire function
	return status;
}

/* Method Name: getField
 *  Arguments:
 *   charType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *             The data will be stored in the specified  encoding format.
 *   dataLen  : Out parameter - to have the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *             the status of operation.  Previous data will be overwritten.
 *
 *  Return Type:
 *   unsigned char * : Field Data as a character array.
 *           Will be NULL in case of error conditions.
 *
 *  Implementation Details:
 *   1. Check the encoding format of the data.
 *   2. If the format is of the same type of the argument, return the data as stored.
 *   3. If data is stored in a different format than required,
 *      convert the stored data to the specified encoding format and return the data.
 *	 4. Update the out parameter with the data in the "size" attribute.
*/
unsigned char *ISOField :: getField(int cType, int* dataLen, ISOStatus& statusRef)
{
	unsigned char *returnPtr = NULL;
	unsigned char *fieldDataPtr = NULL;

	returnPtr = new unsigned char[m_size+1];

	//check if memory allocated	to "returnPtr"
	if (returnPtr == NULL)
	{
	   statusRef.update (false, ENOMEM, "Failure - Insufficient memory");
	}
	else 
	{
	   memset (returnPtr, 0, m_size + 1);

	   fieldDataPtr = getFieldInt (cType, dataLen, statusRef);

	   if (statusRef.getStatus () == false)
	   {
	      delete [] returnPtr;
		  returnPtr = NULL;
	   }
	   else
	   {
	      memcpy (returnPtr, fieldDataPtr, *dataLen);
	      returnPtr[*dataLen] = 0;
	   }
	}

	return returnPtr;
}

/* Method Name: getFieldInt
 *  Arguments:
 *   charType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *             The data will be stored in the specified  encoding format.
 *   dataLen  : Out parameter - to have the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *             the status of operation.  Previous data will be overwritten.
 *
 *  Return Type:
 *   unsigned char * : Field Data as a character array.
 *           Will be NULL in case of error conditions.
 *
 *  Implementation Details:
 *   1. Check the encoding format of the data.
 *   2. If the format is of the same type of the argument, return the data as stored.
 *   3. If data is stored in a different format than required,
 *      convert the stored data to the specified encoding format and return the data.
 *	 4. Update the out parameter with the data in the "size" attribute.
*/
unsigned char *ISOField :: getFieldInt(int cType, int* dataLen, ISOStatus& statusRef)
{
	char txt[255+1] = "";

	//initialize the out parameter "dataLen" with 0
	*dataLen = 0;

	//check if the encoding scheme of the data stored is the same as requested
	if (cType == ASCII)
	{
	   if (m_asciiDataPointer == NULL)
	   {
	      //update the ISOStatus object with the valid code and description
	      statusRef.update (false, INVALID, "Failure - No field data retrieved");

	      return NULL;
	   }
	   else
	   {
	      //update the ISOStatus object with the valid code and description
		  sprintf (txt,
			       "Success - %d bytes of data retrieved.",
				      m_size);
	      statusRef.update (true, VALID, txt);

	      //set the out parameter with the data length in "size"
	      *dataLen = m_size;

	      return m_asciiDataPointer;
	   }
	}

	if (cType == EBCDIC)
	{
	   if (m_ebcdicDataPointer == NULL)
	   {
	      //update the ISOStatus object with the valid code and description
	      statusRef.update (false, INVALID, "Failure - No field data retrieved");

	      return NULL;
	   }
	   else
	   {
	      //update the ISOStatus object with the valid code and description
		  sprintf (txt,
			       "Success - %d bytes of data retrieved.",
				      m_size);
	      statusRef.update (true, VALID, txt);

	      //set the out parameter with the data length in "size"
	      *dataLen = m_size;

	      return m_ebcdicDataPointer;
	   }
	}

	return NULL;
}

/* Method Name: getField2
 *  Arguments:
 *   charType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *             The data will be stored in the specified  encoding format.
 *   data	  : In/Out data parameter.
 *   dataLen  : Out parameter - to have the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *             the status of operation.  Previous data will be overwritten.
 *
 *  Return Type:
 *   bool	  : returns the status of this method.
 *
 *  Implementation Details:
 *   1. Check the encoding format of the data.
 *   2. If the format is of the same type of the argument, return the data as stored.
 *   3. If data is stored in a different format than required,
 *      convert the stored data to the specified encoding format and return the data.
 *	 4. Update the out parameter with the data in the "size" attribute.
*/
bool ISOField :: getField2 (int cType, unsigned char *data, int *dataLen, int maxDataLen, ISOStatus& statusRef)
{
    int tmpDataLen = 0;

    *dataLen = 0;

	if (data == NULL)
	{
	   statusRef.update (false, INVALID, "Failure: data cannot be NULL.");

	   return false;
	}
	else
	{
       // clear out callers buffer
	   memset (data, 0, maxDataLen);

       // Get the field data.
	   unsigned char *fieldDataPtr = getFieldInt (cType, &tmpDataLen, statusRef);

       // check getField worked.
	   if (statusRef.getStatus () == false)
	   {
		  return false;
	   }

       // check for null pointer return
       if (fieldDataPtr == NULL)
       {
          return false;
       }

	   // copy data into callers buffer.
       if (tmpDataLen < maxDataLen)
       {
	      memcpy (data, fieldDataPtr, tmpDataLen);
	      data[tmpDataLen] = 0;

          *dataLen = tmpDataLen;

          return true;
       }
       else
       {
          return false;
       }
	}

	return false;
}

void ISOField::releaseFieldData (unsigned char *fieldData)
{
    if (fieldData != NULL)
    {
       delete [] fieldData;
       fieldData = NULL;
    }

    return;
}

/* Method Name : getSize
 * Arguments:
 *
 * Return Type:
 *   int : actual data length in "size" attribute
 *
 * Implementation Details:
 *   1. The method returns the length stored in the "size" attribute.
 */
int ISOField :: getSize (void)
{
      return m_size;
}

/* Method Name : getMaxSize
 * Arguments:
 *
 * Return Type:
 *   int : max data length you can store in "size" attribute
 *
 * Implementation Details:
 *   1. The method returns the length stored in the "maxDataLen" attribute.
 */
int ISOField :: getMaxSize (void)
{
      return m_maxDataLen;
}

int ISOField::getDataType (void)
{
	return m_dataType;
}

FieldType ISOField::getFieldType (void)
{
	return m_fieldType;
}

/*
 * ********************************************************************
 */

//Definitions for the FixISOVar Constructor, Destructor and methods

//Definition of the FixISOVar Constructor
/* Will initialize the base class by calling the base class constructor
 * with argument that represents the data type and the maximum data length.
*/

ISOFieldFixed :: ISOFieldFixed (int dataType, int maxDataLen) : ISOField(dataType, maxDataLen)
{
	m_fieldType = FIXEDLENGTH;

	return;
}

//Definition of the ISOFieldFixed Destructor
/* Will release the memory occupied by the member attributes of the class
*/

ISOFieldFixed :: ~ISOFieldFixed() 
{
}

//Definition of the ISOFieldFixed methods

/* Method Name : serialize
 * Arguments:
 *	 dataLen  : Out parameter - to have the actual dataLength
 *   statusRef: [Pass By Reference] parameter will be updated with
 *              the status of operation.  Previous data will be overwritten.
 *
 * Return Type:
 *   unsigned char * : Pointer to the EBCDIC character byte stream.
 *
 * Implementation Details:
 *   1. Call the "getField" method with the ASCII format,
 *		out parameter for data length and the ISOStatus object as arguments.
 *   2. The method returns the data in the ASCII byte stream.
 */
unsigned char *ISOFieldFixed :: serialize (int* dataLen, ISOStatus& statusRef)
{
	int encoding = EBCDIC;
	unsigned char *returnPtr = NULL;
	unsigned char *fieldDataPtr = NULL;

	if (m_dataType == BINARY)
	   encoding = ASCII;

	// All fields except BINARY are EBCDIC encoded.

	fieldDataPtr = getFieldInt (encoding, dataLen, statusRef);

	if (fieldDataPtr != NULL)
	{
	   returnPtr = new unsigned char[*dataLen+1];

	   if (returnPtr == NULL)
	   {
	      //update the ISOStatus object with the no data code and description
	      statusRef.update (false, ENOMEM, "Failure - Insufficient memory");

	      return NULL;
	   }

	   memset (returnPtr, 0, *dataLen+1);

	   memcpy (returnPtr, fieldDataPtr, *dataLen);
	   returnPtr[*dataLen] = 0;
	}

	return returnPtr;
}

/* Method Name : deSerialize
 * Arguments:
 *	 dataPtr  :	EBCDIC data
 *	 dataLen  : the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *              the status of operation.  Previous data will be overwritten.
 *
 *   Return Type: 
 *   bool:  Indicates status of operation.  true(1) indicates success and FALSE(0) indicates failure.
 *          Client App will have to check the ISOStatus object for more details
 *          in case if the return value is FALSE(0).
 *
 * Implementation Details:
 *		To be given later
 *
 */
bool ISOFieldFixed :: deSerialize (const unsigned char *data, const int dataLen, ISOStatus& statusRef)
{
	int encoding = EBCDIC;

	if (m_dataType == BINARY)
	   encoding = ASCII;

	// All fields except BINARY are EBCDIC encoded.

	return (setField (encoding, data, dataLen, statusRef));
}

//Definitions for the ISOFieldVar Constructor, Destructor and methods

//Definition of the ISOFieldVar Constructor
/* Will initialize the base class by calling the base class constructor
 * with argument that represents the data type and the maximum data length.
 */

ISOFieldVar :: ISOFieldVar (int dataType, int maxDataLen) : ISOField(dataType, maxDataLen)
{
}

//Definition of the ISOFieldVar Destructor
/* Will release the memoruy occupied by the member attributes of the class
 */

ISOFieldVar :: ~ISOFieldVar() 
{
}

//Definitions for the LLVar constructor and methods

//Definition of the ISOFieldLLVar Constructor
/* Will initialize the base class by calling the base class constructor
 *   with argument that represents the data type and the maximum data length.
 */

ISOFieldLLVar :: ISOFieldLLVar(int dataType, int maxDataLen) : ISOField(dataType, maxDataLen) // lfil was ISOFieldVar
{
	m_fieldType = LLVARLENGTH;

	return;
}

//Definition of the ISOFieldLLVar Destructor
/* Will release the memory occupied by member attributes
 */

ISOFieldLLVar :: ~ISOFieldLLVar()
{
}

//Definition of the ISOFieldLLVar methods
/* Method Name: setField
 *  Arguments:
 *   cType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *             The data will be stored in the specified  encoding format.
 *   data : The actual data to be stored in the bit-field.
 *         Data is represented as a character array.
 *   dataLen  : Actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *             the status of operation.  Previous data will be overwritten.
 *
 *
 *  Return Type:
 *   Boolean : Indicates status of operation.
 *             TRUE(1) indicates success and FALSE(0) indicates failure.
 *             Client App will have to check the ISOStatus object for
 *             more details in case if the return value is FALSE(0).
 *
 *  Implementation Details:
 *  1. Initialize the "charType" attribute with ASCII - data is always stored in this format.
 *	2. Check if the length of data sent in as argument is less than or equal to that set in "maxDataLength".
 *	3. Check if the data sent is in the ASCII format - if not convert it to the ASCII before any validation.
 *  4. Check the type of the data in the "dataType" attribute.
 *      Depending on the type call the appropriate method on the "FieldValidation" object.  
 *		If success initialize the "dataPtr" attribute and the "size" attribute.
 *	5. Update the ISOStatus object accordingly.
 */

//bool ISOFieldLLVar :: setField(const int cType, const unsigned char *data, const int dataLen, ISOStatus& statusRef)
//{
//	return (ISOField::setField (cType, data, dataLen, statusRef));
//}

/* Method Name: getField
 *  Arguments:
 *   cType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *              The data will be stored in the specified  encoding format.
 *   dataLen  : Out parameter - to have the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *             the status of operation.  Previous data will be overwritten.
 *
 *  Return Type:
 *   unsigned char * : Field Data as a character array.
 *            Will be NULL in case of error conditions.
 *
 *  Implementation Details:
 *   1. Check the encoding format of the data.
 *   2. If the format is of the same type of the argument, return the data as stored.
 *   3. If data is stored in a different format than required,
 *      convert the stored data to the specified encoding format and return the data.
 *	 4. Update the out parameter with the data in the "size" attribute.
 */
//unsigned char *ISOFieldLLVar :: getField(int cType, int* dataLen, ISOStatus& statusRef)
//{
//	return (ISOField::getField (cType, dataLen, statusRef));
//}

/* Method Name: getFieldInt
 *  Arguments:
 *   charType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *             The data will be stored in the specified  encoding format.
 *   dataLen  : Out parameter - to have the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *             the status of operation.  Previous data will be overwritten.
 *
 *  Return Type:
 *   unsigned char * : Field Data as a character array.
 *           Will be NULL in case of error conditions.
 *
 *  Implementation Details:
 *   1. Check the encoding format of the data.
 *   2. If the format is of the same type of the argument, return the data as stored.
 *   3. If data is stored in a different format than required,
 *      convert the stored data to the specified encoding format and return the data.
 *	 4. Update the out parameter with the data in the "size" attribute.
*/
//unsigned char *ISOFieldLLVar :: getFieldInt(int cType, int* dataLen, ISOStatus& statusRef)
//{
//	return (ISOField::getFieldInt (cType, dataLen, statusRef));
//}

/* Method Name: serialize
 * Arguments:
 *   dataLen  : Out parameter - to have the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *              the status of operation.  Previous data will be overwritten.
 *
 * Return Type:
 *   unsigned char * : Pointer to the EBCDIC character byte stream.
 *
 * Implementation Details:
 *   1. Call the "getField" method with the ASCII format,
 *		out parameter for data length and the ISOStatus object as arguments. 
 *   2. Convert the length to ASCII and prefix to data being returned.
 *   3. Update the out parameter with the data in the "size" attribute.
 *	 4. The method returns the data in the ASCII byte stream with data length prefixed.
 *
 */
unsigned char *ISOFieldLLVar::serialize (int *dataLen, ISOStatus& statusRef)
{
	//allocate memory to the return pointer with 2 spaces for the length indicator	
	//memory to be released by the calling function
	int i = 0;
	unsigned char *returnPtr = NULL;
	size_t llfieldlength;
	if (gPackedBCD)
		llfieldlength = 1;
	else
		llfieldlength = LLVARLENGTH;

	returnPtr = new unsigned char[llfieldlength+m_size+1];

	//check if memory allocated
	if (returnPtr != NULL)
	{
		memset (returnPtr, 0, llfieldlength+m_size+1);

		//convert the length in the "dataLen" to ascii/character
		//append the converted length to the data being returned
		//memory to be released at the end of the function
		unsigned char *sizeBuffer = NULL;
		if (gPackedBCD)
		{
			sizeBuffer = new unsigned char[1];
			if (sizeBuffer != NULL)
				*sizeBuffer = static_cast<unsigned char>(m_size);
		}
		else
			sizeBuffer = CharUtility::itoa_pad(m_size, llfieldlength);	

		if (sizeBuffer != NULL)
		{
			// BINARY field length is EBCDIC encoded (data is not)
			CharUtility::toEbcdicStrInplace((unsigned char*)sizeBuffer, llfieldlength);

			//copy the size buffer to the "returnPtr"
			returnPtr[0] = sizeBuffer[0];
			if (!gPackedBCD)
				returnPtr[1] = sizeBuffer[1];

			//get the data from the field in a temp buffer
			//memory to be released at the end of the function
			unsigned char *fieldDataPtr = NULL;
			unsigned char *tempBuffer = NULL;

			// get field returns a pointer!
			fieldDataPtr = getFieldInt (ASCII, dataLen, statusRef);

			if (fieldDataPtr != NULL)
			{
				tempBuffer = new unsigned char [*dataLen+1];

				if (tempBuffer != NULL)
				{
					memset (tempBuffer, 0, *dataLen+1);
					memcpy (tempBuffer, fieldDataPtr, *dataLen);
					tempBuffer[*dataLen] = 0;
				}
			}

			if (tempBuffer != NULL)
			{
				if (m_dataType != BINARY)
				{
					// Field data except BINARY are EBCDIC encoded
					CharUtility::toEbcdicStrInplace((unsigned char*)tempBuffer, *dataLen);
				}

				//append the data from "tempBuffer" to the "returnPtr"
				memcpy (&returnPtr[llfieldlength], tempBuffer, m_size);
				returnPtr[llfieldlength+m_size] = 0;

				//set the "dataLen" with the "size"
				*dataLen = (llfieldlength + m_size);

				//release memory allocated to the temp array through a call to getField
				if (tempBuffer != NULL)
				{
					delete [] tempBuffer;
					tempBuffer = NULL;
				}
			}
			else
			{
				//update the ISOStatus object with the valid code and description
				statusRef.update (false, INVALID, "Failure - No field data retrieved");

				delete [] returnPtr;
				returnPtr = NULL;
			}//end of tempBuffer if-else

			//release memory allocated to the size buffer for ascii string
			delete [] sizeBuffer;
			sizeBuffer = NULL;
		}
		else
		{
			//update the ISOStatus object with the valid code and description
			statusRef.update (false, INVALID, "Failure - ISOFieldLLVar: Length indicator conversion falied");

			delete [] returnPtr;
			returnPtr = NULL;
		}//end of sizeBuffer if-else
	}
	else
	{
		//update the ISOStatus object with the no data code and description
		statusRef.update (false, ENOMEM, "Failure - Insufficient memory");

	}//end of returnPtr if-else

	//return the data prefixed with the length indicator
	return returnPtr;
}


/* Method Name : deSerialize
 * Arguments:
 *	 dataPtr  :	EBCDIC data
 *	 dataLen  : the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *              the status of operation.  Previous data will be overwritten.
 *
 *   Return Type: 
 *   bool:  Indicates status of operation.  true(1) indicates success and FALSE(0) indicates failure.
 *          Client App will have to check the ISOStatus object for more details
 *          in case if the return value is FALSE(0).
 *
 * Implementation Details:
 *		To be given later
 *
 */
bool ISOFieldLLVar :: deSerialize(const unsigned char *dataPtr, const int dataLen, ISOStatus& statusRef)
{
	int encoding = EBCDIC;

	// We need to strip the two length bytes off the data
	// then use setField.
	if (dataPtr == NULL)
	{
		statusRef.update (false, INVALID, "ISOFieldLLVar::deSerialize failure - dataPtr is NULL");

		return false;
	}

	size_t llfieldlength;
	if (gPackedBCD)
		llfieldlength = 1;
	else
		llfieldlength = LLVARLENGTH;

	if (dataLen < llfieldlength)
	{
		statusRef.update (false, INVALID, "ISOFieldLLVar::deSerialize failure - Invalid length of data");

		return false;
	}

	int tmpDataLen;
	unsigned char tmpLen[3] = "";
	tmpLen[0] = dataPtr[0];
	tmpLen[1] = dataPtr[1];
	tmpLen[2] = 0;

	// length is always in EBCDIC
	CharUtility::toAsciiStrInplace (tmpLen, llfieldlength);

	if (gPackedBCD)
	{
		tmpDataLen = *tmpLen;
	}
	else
	{
		tmpDataLen = atoi ((char *)tmpLen);

		if ((tmpDataLen < 0)
			|| (tmpDataLen > 99))
		{
			statusRef.update (false, INVALID, "ISOFieldLLVar::deSerialize failure - ISOFieldLLVar = 0 - 99 data bytes");

			return false;
		}
	}
	if (m_dataType == BINARY)
	{
		// Binary field data is raw ASCII not EBCDIC encoded.
		encoding = ASCII;
	}
	else
	{
		// All other are EBCDIC encoded.
		encoding = EBCDIC;
	}

	return (setField (encoding, &dataPtr[llfieldlength], tmpDataLen, statusRef));
}


//Definitions for the ISOFieldLLLVar constrcutor and methods

//Definition of the ISOFieldLLLVar Constructor
/* Will initialize the base class by calling the base class constructor
 *  with argument that represents the data type and the maximum data length.
 */

ISOFieldLLLVar :: ISOFieldLLLVar(int dataType, int maxDataLen)	: ISOField(dataType, maxDataLen) // lfil was ISOFieldVar
{
	m_fieldType = LLLVARLENGTH;

	return;
}

//Definition of the ISOFieldLLLVar Destructor
/* Will release the memory occupied by member attributes
 */

ISOFieldLLLVar :: ~ISOFieldLLLVar()
{
}

//Definition of the ISOFieldLLLVar methods
/* Method Name: setField
 *  Arguments:
 *   cType   : The data encoding scheme.  Can be ASCII or EBCDIC.
 *				  The data will be stored in the specified  encoding format.
 *   data       : The actual data to be stored in the bit-field.
 *                Data is represented as a character array.
 *   dataLen    : Actual data length
 *   statusRef  : [Pass By Reference] parameter will be updated with
 *                the status of operation.  Previous data will be overwritten.
 *
 *
 *  Return Type:
 *   Boolean : Indicates status of operation.
 *             TRUE(1) indicates success and FALSE(0) indicates failure.
 *             Client App will have to check the ISOStatus object for
 *             more details in case if the return value is FALSE(0).
 *
 *  Implementation Details:
 *  1. Initialize the "charType" attribute with ASCII - data is always stored in this format.
 *	2. Check if the length of data sent in as argument is less than or equal to that set in "maxDataLength".
 *	3. Check if the data sent is in the ASCII format - if not convert it to the ASCII before any validation.
 *  4. Check the type of the data in the "dataType" attribute.
 *      Depending on the type call the appropriate method on the "FieldValidation" object.  
 *		If success initialize the "dataPtr" attribute and the "size" attribute.
 *	5. Update the ISOStatus object accordingly.
 */

//bool ISOFieldLLLVar :: setField(const int cType, const unsigned char *data, const int dataLen, ISOStatus& statusRef)
//{
//	return (ISOField::setField (cType, data, dataLen, statusRef));
//}

/* Method Name: getField
 *  Arguments:
 *   cType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *              The data will be stored in the specified  encoding format.
 *   dataLen  : Out parameter - to have the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *              the status of operation.  Previous data will be overwritten.
 *
 *  Return Type:
 *   unsigned char *   : Field Data as a character array.
 *              Will be NULL in case of error conditions.
 *
 *  Implementation Details:
 *   1. Check the encoding format of the data.
 *   2. If the format is of the same type of the argument, return the data as stored.
 *   3. If data is stored in a different format than required,
 *      convert the stored data to the specified encoding format and return the data.
 *	 4. Update the out parameter with the data in the "size" attribute.
 */
//unsigned char *ISOFieldLLLVar :: getField(int cType, int* dataLen, ISOStatus& statusRef)
//{
//	return (ISOField::getField (cType, dataLen, statusRef));
//}

/* Method Name: getFieldInt
 *  Arguments:
 *   charType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *             The data will be stored in the specified  encoding format.
 *   dataLen  : Out parameter - to have the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *             the status of operation.  Previous data will be overwritten.
 *
 *  Return Type:
 *   unsigned char * : Field Data as a character array.
 *           Will be NULL in case of error conditions.
 *
 *  Implementation Details:
 *   1. Check the encoding format of the data.
 *   2. If the format is of the same type of the argument, return the data as stored.
 *   3. If data is stored in a different format than required,
 *      convert the stored data to the specified encoding format and return the data.
 *	 4. Update the out parameter with the data in the "size" attribute.
*/
//unsigned char *ISOFieldLLLVar :: getFieldInt (int cType, int* dataLen, ISOStatus& statusRef)
//{
//	return (ISOField::getFieldInt (cType, dataLen, statusRef));
//}

/* Method Name: serialize
 * Arguments:
 *   StatusRef: [Pass By Reference] parameter will be updated with
 *              the status of operation.  Previous data will be overwritten.
 *
 * Return Type:
 *   unsigned char * : Pointer to the EBCDIC character byte stream.
 *
 * Implementation Details:
 *   1. Call the "getField" method with the ASCII format,
 *		out parameter for data length and the ISOStatus object as arguments.
 *   2. Convert the length to ASCII and prefix to data being returned.
 *   3. Update the out parameter with th edata in the "size" attribute.
 *	 4. The method returns the data in the ASCII byte stream with data length prefixed.
 *
 */
unsigned char *ISOFieldLLLVar :: serialize (int* dataLen, ISOStatus& statusRef)
{
	//allocate memory to the return pointer with 3 spaces for the length indicator	
	//memory to be released by the calling function
	int i = 0;
	unsigned char *returnPtr = NULL;

	size_t lllfieldlength;
	if (gPackedBCD)
		lllfieldlength = 2;
	else
		lllfieldlength = LLLVARLENGTH;

	returnPtr = new unsigned char[lllfieldlength+m_size+1];

	//check if memory allocated
	if (returnPtr != NULL)
	{
		memset (returnPtr, 0, lllfieldlength+m_size+1);

		//convert the length in the "dataLen" to ascii/character
		//append the converted length to the data being returned
		//memorry to be released at the end of the function
		unsigned char *sizeBuffer = NULL;

		if (gPackedBCD)
		{
			sizeBuffer = new unsigned char[2];
			if (sizeBuffer != NULL)
			{
				sizeBuffer[1] = (m_size & 0xff);
				sizeBuffer[0] = ((m_size >> 8) & 0xff);
			}
		}
		else
			sizeBuffer = CharUtility::itoa_pad(m_size, lllfieldlength);	

		if (sizeBuffer != NULL)
		{
			// BINARY field length is EBCDIC encoded (data is not)
			CharUtility::toEbcdicStrInplace((unsigned char*)sizeBuffer, lllfieldlength);

			//copy the size buffer to the "returnPtr"
			returnPtr[0] = sizeBuffer[0];
			returnPtr[1] = sizeBuffer[1];
			if (!gPackedBCD)
				returnPtr[2] = sizeBuffer[2];

			//get the data form the field in a temp buffer
			//memory to be released at the end of the function
			unsigned char *fieldDataPtr = NULL;
			unsigned char *tempBuffer = NULL;

			// get field returns a pointer!
			fieldDataPtr = getFieldInt (ASCII, dataLen, statusRef);

			if (fieldDataPtr != NULL)
			{
				tempBuffer = new unsigned char [*dataLen+1];

				if (tempBuffer != NULL)
				{
					memset (tempBuffer, 0, *dataLen+1);
					memcpy (tempBuffer, fieldDataPtr, *dataLen);
					tempBuffer[*dataLen] = 0;
				}
			}

			if (tempBuffer != NULL)
			{
				if (m_dataType != BINARY)
				{
					// Field data except BINARY are EBCDIC encoded
					CharUtility::toEbcdicStrInplace((unsigned char*)tempBuffer, *dataLen);
				}

				//append the data from "tempBuffer" to the "returnPtr"
				memcpy (&returnPtr[lllfieldlength], tempBuffer, m_size);
				returnPtr[lllfieldlength+m_size] = 0;

				//set the "dataLen" with the "size"
				*dataLen = (lllfieldlength + m_size);

				//release memory allocated to the temp array through a call to getField
				if (tempBuffer != NULL)
				{
					delete [] tempBuffer;
					tempBuffer = NULL;
				}
			}
			else
			{
				//update the ISOStatus object with the no data code and description
				statusRef.update (false, INVALID, "Failure - No field data retrieved");

				delete [] returnPtr;
				returnPtr = NULL;
			}//end of tempBuffer if-else

			//release memory allocated to the size buffer for ascii string
			delete [] sizeBuffer;
		}
		else
		{
			//update the ISOStatus object with the no data code and description
			statusRef.update (false, INVALID, "Failure - ISOFieldLLLVar: Length indicator conversion failed");

			delete [] returnPtr;
			returnPtr = NULL;
		}//end of sizeBuffer if-else
	}
	else
	{
		//update the ISOStatus object with the no data code and description
		statusRef.update (false, ENOMEM, "Failure - Insufficient memory");
	}//end of returnPtr if-else

	//return the data prefixed with the length indicator
	return returnPtr;
}

/* Method Name : deSerialize
 * Arguments:
 *	 dataPtr  :	EBCDIC data
 *	 dataLen  : the actual data length
 *   statusRef: [Pass By Reference] parameter will be updated with
 *              the status of operation.  Previous data will be overwritten.
 *
 *   Return Type: 
 *   bool:  Indicates status of operation.  true(1) indicates success and FALSE(0) indicates failure.
 *          Client App will have to check the ISOStatus object for more details
 *          in case if the return value is FALSE(0).
 *
 * Implementation Details:
 *		To be given later
 *
 */
bool ISOFieldLLLVar :: deSerialize(const unsigned char *dataPtr, const int dataLen, ISOStatus& statusRef)
{
	int encoding = EBCDIC;

	// We need to strip the three length bytes off the data
	// then use setField.
	if (dataPtr == NULL)
	{
		statusRef.update (false, INVALID, "ISOFieldLLLVar::deSerialize failure - dataPtr is NULL");

		return false;
	}

	size_t lllfieldlength;
	if (gPackedBCD)
		lllfieldlength = 2;
	else
		lllfieldlength = LLLVARLENGTH;

	if (dataLen < lllfieldlength)
	{
		statusRef.update (false, INVALID, "ISOFieldLLLVar::deSerialize failure - Invalid length of data");

		return false;
	}

	int tmpDataLen;
	unsigned char tmpLen[4] = "";
	tmpLen[0] = dataPtr[0];
	tmpLen[1] = dataPtr[1];
	tmpLen[2] = dataPtr[2];
	tmpLen[3] = 0;

	// length is always in EBCDIC
	CharUtility::toAsciiStrInplace (tmpLen, lllfieldlength);

	if (gPackedBCD)
	{
		unsigned short s = *(reinterpret_cast<unsigned short *>(tmpLen));
#ifdef _WIN32
		s = _byteswap_ushort(s);
#endif
		tmpDataLen = s;
	}
	else
	{
		tmpDataLen = atoi ((char *)tmpLen);

		if ((tmpDataLen < 0)
			|| (tmpDataLen > 999))
		{
			statusRef.update (false, INVALID, "ISOFieldLLLVar::deSerialize failure - ISOFieldLLLVar = 0 - 999 data bytes");

			return false;
		}
	}
	if (m_dataType == BINARY)
	{
		// Binary field data is raw ASCII not EBCDIC encoded.
		encoding = ASCII;
	}
	else
	{
		// All other are EBCDIC encoded.
		encoding = EBCDIC;
	}

	return (setField (encoding, &dataPtr[lllfieldlength], tmpDataLen, statusRef));
}

