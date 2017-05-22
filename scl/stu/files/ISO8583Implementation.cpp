/*********************************************************************
*
*   Module:
*       ISO8583Implementation.cpp
*
*   Contents:
*       Implementation of the ISO8583Implementation class constructor and methods
*       
*   Description
*        It has implementation for the set and get field methods for 
*
*   See Also:
*       ISOSVAuthorization.h
*
*
*   Created:
*		21 May 2001 Shubha Kumar
*
*   Modified:
*		12 June 2001 Shubha Kumar
*				-The data to be stored without null termination.
*				-The length parameter to be used to store the actual data length in the set methods of ISOField
*				 and return the same length as out parameters in get, serialize and deserialize methods
*
*		06 July 2001 Shubha Kumar
*				- Added default initialization to the FieldMapElement array in the constructor
*				- getField() - check for isSet value of fieldMap array before a call to the ISOField is made
*                    Lonnie L. Filbrun - reworked most functionality.
*                    Lonnie L. Filbrun - added ability to load/save from/to file (BIN).
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

//Package specific header files
#include "CharUtility.h"
#include "Enumerations.h"
#include "FieldValidation.h"
#include "ISO8583Implementation.h"
#include "ISO8583Bitmap.h"
#include "FieldMapArrayData.h"

//Offset from the message type in the array after the message type is copied in the array
#define OFFSET_MESSAGETYPE 4

using namespace std;

extern int gTrace;
extern int gDebug;
extern int gPackedBCD;

static char obj[] = "ISO8583Implementation";

//Definitions for the ISO8583Implementation Constructor and methods
//Default Constructor
ISO8583Implementation::ISO8583Implementation()
{
	m_msgType = NULL;
    m_className = NULL;
	m_validator = NULL;
	m_mapSize = 0;

	m_serializedData = NULL;
	m_serializedDataLen = 0;

	m_bitmap = NULL;
}

//Definition of the ISO8583Implementation Constructor

/* Constructor Name: ISO8583Implementation
 *  Arguments:
 *   mapSize : The maximum size the bit map can be of
 *
 * Implementation Details:
 *  1. Will initialize the base class by calling the base class constructor
      with "mapSize" argument.
 *  2. Will initialize the "fieldMap" array with respect to the map size.
 *  3. Will customize the "FieldElement" objects in the fieldMap array
 *     to reflect the requirements of the "Authorization" message.
 *  4. Will initialize the "valObjPointer" to refer to the Validation object
 *     required for validating authorization messages.
 *    valObjPointer = new(1100SVValidation)
*/

ISO8583Implementation::ISO8583Implementation(char* msgTypePtr, int mSize)
{
	m_msgType = NULL;
    m_className = NULL;
	m_mapSize = 0;
	m_validator = NULL;

	m_serializedData = NULL;
	m_serializedDataLen = 0;

    //copy the message type to the attribute
	//the length of the char array is the same as the message string + 1 place for the null character
	m_msgType = new char[strlen(msgTypePtr)+1];
	
	if (m_msgType != NULL)
	{
		strcpy (m_msgType, msgTypePtr);
	
		//assign the map size to the attribute
		m_mapSize = mSize;

		if (gDebug)
		   cout << "TYPE: " << m_msgType << " MAP: " << mSize << endl;
	}

	InitFieldMapArray (m_fieldMap);

	// allocate a bitmap instance
	m_bitmap = new ISO8583Bitmap (m_mapSize);

	return;
}


//Definition of the ISO8583Implementation Constructor

/* Destructor Name: ISO8583Implementation
 * Will release the memory occupied by the memebers of the class
 */

ISO8583Implementation::~ISO8583Implementation()
{
	int i=0;

	if (gDebug)
	   cout << "ISO8583Implementation::~ISO8583Implementation" << endl;

	if (m_serializedData != NULL)
	{
	   delete [] m_serializedData;
	   m_serializedData = NULL;
	   m_serializedDataLen = 0;
	}

	if (m_bitmap != NULL)
	{
	   delete m_bitmap;
	   m_bitmap = NULL;
	}

	for (i = 0; i < 64; i++)
	{
	   if (m_fieldMap[i] != NULL) //release the memory occupied by the FieldMapElement array
	   {
	      delete m_fieldMap[i];
		  m_fieldMap[i] = NULL;
	   }
	}

	if (m_validator != NULL)
	{
	   delete m_validator;
	   m_validator = NULL;
	}

	if (m_msgType != NULL)
	{
	   //delete the message type char pointer
	   delete [] m_msgType;
	   m_msgType = NULL;
	}

	return;
}

/*  Method Name: setField
 *  Arguments:
 *    bitPosition : The bit-position of the data.
 *                  Should be greater than 1 and less than or equal to 64 for a 64-bit bit map.
 *    charType	  : The data encoding scheme.  Can be ASCII or EBCDIC.
 *                  The data will be stored in the specified encoding format.
 *    data        : The actual data to be stored in the bit-field.
 *                  Data is represented as a character array.
 *    dataLen	  : Actual length of the data sent.
 *	  statusRef   : [Pass By Reference] parameter will be updated with the status of operation.
 *                  Previous data will be overwritten.
 *
 *    
 *   Return Type:
 *    bool : Indicates status of operation.
 *           true(1) indicates success and FALSE(0) indicates failure.
 *           Client App will have to check the ISOStatus object for more details
 *           in case if the return value is FALSE(0).
 *
 *
 *   Implementation Details:
 *
 *	 1. Check for the bitPosition value. If the value is either 0 or 1 
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *	 2. Check for the bitPosition value. If the value is greater than fieldMapSize
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *	 3. Check for the bitPosition value. If the value is one among Unsupported bits
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *	 4. If the bitPosition value is valid. Call the set field on specific ISOField,
 *      set "isSet" attribute to true and return success
 */

bool ISO8583Implementation::setField(const int bitPosition, const int charType, const unsigned char *data, const int dataLen, ISOStatus& statusRef)
{
	char txt[255 + 1]= "";

    statusRef.update (true, 0, "method returned success.");

	//check for the valid bit positions between 2 and "mapSize" only - all other positions are false
	//first check is for the reserved bit poistions

	bool result = false;

	//The client application will send in absolute bit positions.
	//Subtract the absolute bit position by one to get the array position, 
	//because array positions starts from zero.
	if (bitPosition-1 == 0)
	{
		//set the ISOStatus object with the error code and the description
		statusRef.update (false, INVALID_BIT_POSITION, "Failure - Bit Position 1 is reserved");

		result = false;
	}
	//check if the bit position is greater than the "mapSize" requested
	else if (bitPosition-1 > m_mapSize - 1)
	{
		//set the ISOStatus object with the error code and the description
		sprintf (txt,
			"Failure - Bit Position %d is not supported",
			   bitPosition);
		statusRef.update (false, INVALID_BIT_POSITION, txt);
		
		result = false;
	}
	//check if the bit position is supported for ISO8583Implementation message type
	else if (m_fieldMap[bitPosition-1] == NULL)
	{
		//set the ISOStatus object with the error code and the description
		sprintf (txt,
			"Failure - Bit Position %d is not supported",
			   bitPosition);
		statusRef.update (false, INVALID_BIT_POSITION, txt);
		
		result = false;
	}
	//for a valid, supported bit position write the data at the specified position
	else
	{
		//set the data in the relevant ISOField object through it's setField method
		bool status = m_fieldMap[bitPosition-1]->m_fieldPointer->setField (charType, data, dataLen, statusRef);

		//if the data is successfully set in the field, set the ISOStatus object
		//and the "isSet" attribute of FieldMapElement object
		if (status)
		{
			m_fieldMap[bitPosition-1]->m_isSet = true;

			statusRef.update (true, VALID, "Success - Field Initialized");

			result = true;
		}
		else 
		{
			//retrieve description of error message already set 
			sprintf (txt,
				"Failure - setField returned %d - %s.\n",
				   statusRef.getResultCode (),
				   statusRef.getResultDesc ());

			statusRef.update (false, statusRef.getResultCode (), txt);
		}
	}

	return result;
}

/*  Method Name: getField
 *  Arguments:
 *    bitPosition : The bit-position of the data.  Should be greater than 1 and
 *                   less than or equal to 64 for a 64-bit bit map.
 *    charType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *                The data will be retrieved in the specified encoding format.
 *	  dataLen  : Out parameter - has the actual length of the data - number of bytes in the data
 *    statusRef: [Pass By Reference] parameter will be updated with the status of operation.
 *               Previous data will be overwritten.
 *
 *    
 *   Return Type:  unsigned char *
 *			Points to the field data which is stored as a character array.
 *          In case of error it points to NULL.
 *
 *   Implementation Details:
 *
 *	 1. Check for the bitPosition value. If the value is either 0 or 1 
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *	 2. Check for the bitPosition value. If the value is greater than fieldMapSize
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *	 3. Check for the bitPosition value. If the value is one among Unsupported bits
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *   4. If bitPosition is not provided return NULL. and update the ISOStatus Object 
 *		with an appropriate message
 *	 5. If the bitPosition value is valid. Call the getField on specific ISOField object
 *		and return the data array corresponding to that bitPosition
 */

unsigned char *ISO8583Implementation::getField(int bitPosition, int charType, int* dataLen, ISOStatus& statusRef)
{
	char txt[255 + 1]= "";

    statusRef.update (true, 0, "method returned success.");

	//check for the valid bit positions between 2 and "mapSize" only - all other positions are false
	//first check is for the reserved bit poistions
	bool result= true;	
	unsigned char *dataPtr = NULL;

	//The client application will send in absolute bit positions.
	//Subtract the absolute bit position by one to get the array position, 
	//because array positions starts from zero.
	if (bitPosition-1 == 0)
	{
	   //set the ISOStatus object with the error code and the description
	   statusRef.update (false, INVALID_BIT_POSITION, "Failure - Bit Position 1 is reserved");

	   result = false;
	}
	//check if the bit position is greater than the "mapSize" requested
	else if ((bitPosition-1 > m_mapSize - 1) || (bitPosition-1 <0))
	{
		//set the ISOStatus object with the error code and the description
		sprintf (txt,
			"Failure - Bit Position %d is not supported",
			   bitPosition);
		statusRef.update (false, INVALID_BIT_POSITION, txt);
		
		result = false;
	}
	//check if the bit position is supported for ISO8583Implementation message type
	else if (m_fieldMap[bitPosition-1] == NULL)
	{
		sprintf (txt,
			"Failure - Bit Position %d is not supported",
			   bitPosition);
		statusRef.update (false, INVALID_BIT_POSITION, txt);
		
		result = false;
	}
	//for a valid, supported bit position get the data from the specified position
	else
	{
		//get the data from the specified position through the relevant ISOField object
		//memory allocated here will be released by the calling function
		if (m_fieldMap[bitPosition-1]->m_isSet == true)
		{
			dataPtr = m_fieldMap[bitPosition-1]->m_fieldPointer->getField (charType, dataLen, statusRef);
			
			result = true;
		}
		else
		{
			statusRef.update (false, NO_DATA, "Failure - 8583 Implementation getField() - Field data not set");

			result = false;
		}
	}

	if (result)
	  return dataPtr;
	else
	{
	   //retrieve description of error message already set 
	   sprintf (txt,
				"Failure - getField returned %d - %s.\n",
				   statusRef.getResultCode (),
				   statusRef.getResultDesc ());

	   statusRef.update (false, statusRef.getResultCode (), txt);

	   return NULL;
	}
}

/*  Method Name: getField2
 *  Arguments:
 *    bitPosition : The bit-position of the data.  Should be greater than 1 and
 *                   less than or equal to 64 for a 64-bit bit map.
 *    charType : The data encoding scheme.  Can be ASCII or EBCDIC.
 *                The data will be retrieved in the specified encoding format.
 *    data	   : In/Out input data pointer, modified by getField2.
 *	  dataLen  : Out parameter - has the actual length of the data - number of bytes in the data
 *    maxDataLen : In parameter - instructs the API the max number of bytes it can write to data.
 *    statusRef: [Pass By Reference] parameter will be updated with the status of operation.
 *               Previous data will be overwritten.
 *
 *    
 *   Return Type:  bool
 *			status of getField request.
 *
 *   Implementation Details:
 *
 *	 1. Check for the bitPosition value. If the value is either 0 or 1 
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *	 2. Check for the bitPosition value. If the value is greater than fieldMapSize
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *	 3. Check for the bitPosition value. If the value is one among Unsupported bits
 *		return FALSE and update the ISOStatus Object with an appropriate message
 *   4. If bitPosition is not provided return NULL. and update the ISOStatus Object 
 *		with an appropriate message
 *	 5. If the bitPosition value is valid. Call the getField on specific ISOField object
 *		and return the data array corresponding to that bitPosition
 */

bool ISO8583Implementation::getField2 (int bitPosition, int charType, unsigned char *data, int *dataLen, int maxDataLen, ISOStatus& statusRef)
{
	char txt[255 + 1]= "";

    *dataLen = 0;

    statusRef.update (true, 0, "method returned success.");

	if (data == NULL)
	{
       statusRef.update (false, INVALID, "getField2: data should not be NULL.");
	}

	//check for the valid bit positions between 2 and "mapSize" only - all other positions are false
	//first check is for the reserved bit poistions

	//The client application will send in absolute bit positions.
	//Subtract the absolute bit position by one to get the array position, 
	//because array positions starts from zero.
	if ((bitPosition-1) == 0)
	{
	   //set the ISOStatus object with the error code and the description
		sprintf (txt,
			"Failure - Bit Position %d is reserved",
			   bitPosition);

	   statusRef.update (false, INVALID_BIT_POSITION, txt);

	   return false;
	}
	//check if the bit position is greater than the "mapSize" requested
	else if ((bitPosition-1 > m_mapSize - 1) || (bitPosition-1 <0))
	{
		//set the ISOStatus object with the error code and the description
		sprintf (txt,
			"Failure - Bit Position %d is not supported",
			   bitPosition);

		statusRef.update (false, INVALID_BIT_POSITION, txt);
		
		return false;
	}
	//check if the bit position is supported for ISO8583Implementation message type
	else if (m_fieldMap[bitPosition-1] == NULL)
	{
		sprintf (txt,
			"Failure - Bit Position %d is not supported",
			   bitPosition);

		statusRef.update (false, INVALID_BIT_POSITION, txt);
		
		return false;
	}
	//for a valid, supported bit position get the data from the specified position
	else
	{
		//get the data from the specified position through the relevant ISOField object
		//memory allocated here will be released by the calling function
		if (m_fieldMap[bitPosition-1]->m_isSet == true)
		{
			return m_fieldMap[bitPosition-1]->m_fieldPointer->getField2 (charType, data, dataLen, maxDataLen, statusRef);
		}
		else
		{
		   sprintf (txt,
		      "Failure - Bit Position %d, field data not set",
	             bitPosition);

		   statusRef.update (false, NO_DATA, txt);

	       return false;
		}
	}

	return false;
}

void ISO8583Implementation::releaseFieldData (int bitPosition, unsigned char *data, ISOStatus& statusRef)
{
	char txt[255 + 1] = "";

    statusRef.update (true, 0, "method returned success.");

	//check for the valid bit positions between 2 and "mapSize" only - all other positions are false
	//first check is for the reserved bit poistions

	//The client application will send in absolute bit positions.
	//Subtract the absolute bit position by one to get the array position, 
	//because array positions starts from zero.
	if (bitPosition-1 == 0)
	{
	   //set the ISOStatus object with the error code and the description
	   sprintf (txt,
           "Failure - Bit Position %d is reserved",
			   bitPosition);
	   statusRef.update (false, INVALID_BIT_POSITION, txt);
	}
	//check if the bit position is greater than the "mapSize" requested
	else if ((bitPosition-1 > m_mapSize - 1) || (bitPosition-1 <0))
	{
		//set the ISOStatus object with the error code and the description
		sprintf (txt,
			"Failure - Bit Position %d is not supported",
			   bitPosition);
		statusRef.update (false, INVALID_BIT_POSITION, txt);
	}
	//check if the bit position is supported for ISO8583Implementation message type
	else if (m_fieldMap[bitPosition-1] == NULL)
	{
		sprintf (txt,
			"Failure - Bit Position %d is not supported",
			   bitPosition);
		statusRef.update (false, INVALID_BIT_POSITION, txt);
	}
	//for a valid, supported bit position get the data from the specified position
	else
	{
        m_fieldMap[bitPosition-1]->m_fieldPointer->releaseFieldData (data);
	}
    
    return;
}


/*  Method Name: validate
 *  Arguments:
 *	  dataLen  : Out parameter - has the actual length of the data - number of bytes in the data
 *   statusRef: [Pass By Reference] parameter will be updated with the status of operation.
 *              Previous data will be overwritten.
 *    
 *   Return Type:  bool
 *			This indicates the status of the operation	
 *          true(1) indicates success and FALSE(0) indicates failure.
 *          Client App will have to check the ISOStatus object for more details
 *          in case if the return value is FALSE(0).
 *
 *   Implementation Details:
 *
 *	 1. Calls the ISO1100SVValidation object to validate the 1100 message.
 */


bool ISO8583Implementation::validate(ISOStatus& statusRef)
{
    statusRef.update (true, 0, "method returned success.");

	//return the success or failure received from the relevant ValidateMessage object
	if (m_validator != NULL)
      return (m_validator->performValidation (m_fieldMap, m_mapSize, statusRef));
	else
	  return true;
}

/*  Method Name: serialize
 *  Arguments:
 *   statusRef: [Pass By Reference] parameter will be updated with the status of operation.
 *              Previous data will be overwritten.
 *    
 *   Return Type:  unsigned char *
 *			Points to the EBCDIC character byte stream.
 *
 *   Implementation Details:
 *
 *    1. The serialized byte stream is composed with the following parts:
 *          | Message_Type | Bit_Map | Message Data |
 *    2. The return byte stream should be composed in the above format and
 *       the encoding format should be EBCDIC.
 *    3. Since the Message object does not hold the data, it's the responsibility
 *       of the individual ISOField object to serialize the data they hold and
 *       the Message object will be responsible for calling the "serialize()"
 *       method on each of the ISOField object and concatenating the returned data from each ISOField object.
 *    4. Since the Message object knows about the message type and the bit map,
 *       it's the responsibility of the message object to serialize the appropriate data.
 *    5. Allocate memory for 68 bytes (4 Bytes for Message Type + 64 Bytes for Bit Map)
 *    6. Serialize the Message Type.
 *    7. Serialize the Bit Map.
 *    8. Call the "serialize" method on each ISOField object to get back the serialized EBCDIC field data.
 *    9. Concatenate the individual field data to the ByteStream array.
 *   10. If any of the ISOField object fails to serialize, then discard the entire byte stream and return NULL.
 */

unsigned char *ISO8583Implementation::serialize(int* dataLen, ISOStatus& statusRef)
{
	int bp = 0;
	int totalLen = 0;
	bool status = false;
	ISOField *aField = NULL;
	unsigned char *returnPtr = NULL;

	*dataLen = 0;

    statusRef.update (true, 0, "method returned success.");

	// I dont like the two times through the loop...
	
	if (m_serializedData != NULL)
	{
	   delete [] m_serializedData;
	   m_serializedData = NULL;
	   m_serializedDataLen = 0;
	}
	
	// walk all fields and determine totalLength while
	// setting up bitmap;
	// if field type is FIXED add maxLen.
	// if field type is VARIABLE query field for real length.
	
	for (bp = 0; bp < 64; bp++)
	{
	   if (m_fieldMap[bp]->m_isSet == true)
	   {
		  // set the proper bit for this position.
	      m_bitmap->setBit (bp+1);

	      aField = m_fieldMap[bp]->m_fieldPointer;
	      
	      if (aField != NULL)
	      {
			  if (aField->getFieldType () == FIXEDLENGTH)
			  {
				  if (aField->isPackedBCDField())
					  totalLen += aField->getSize();
				  else
					  // fixed length fields have no length indicator
					  // to add!
					  totalLen += aField->getMaxSize ();
			  }
			  else
			  {
				  // data length
				  totalLen += aField->getSize ();

				  // field type =  0(FIXED) - 2(LL) or 3(LLL)
				  totalLen += aField->getFieldType ();
			  }
		  }
	   }	   
	}

	// account for the 4 bytes of msg type and 8 bytes of bitmap.
	size_t msgtype_size;
	if (gPackedBCD)
		msgtype_size = 2;
	else
		msgtype_size = 4;
	totalLen += (msgtype_size + 8);

	m_serializedData = new unsigned char [totalLen + 1];
	
	if (m_serializedData != NULL)
	{
	   memset (m_serializedData, 0, totalLen + 1);
	   m_serializedDataLen = totalLen;

	   // serialize the Message Type.
	   memcpy (&m_serializedData[0], m_msgType, 4);
	   m_serializedData[4] = 0;
	   if (gPackedBCD)
	   {
		   if (!CharUtility::toPackedBCDInplace(&m_serializedData[0],4))
		   {
			   if (m_serializedData != NULL)
			   {
				   delete [] m_serializedData;
				   m_serializedData = NULL;

				   m_serializedDataLen = 0;
			   }

			   statusRef.update (false, INVALID, "Failure - 8583 Implementation Serialize - Failed to pack BCD data");
			   return NULL;
		   }
	   }
	   //convert to EBCDIC
	   CharUtility::toEbcdicStrInplace(m_serializedData, msgtype_size);

	   unsigned long dataLength = 0;

       // serialize the bitmap bytes.
       m_bitmap->serialize (&m_serializedData[msgtype_size], &dataLength);

	   int offset = (msgtype_size + dataLength);

	   for (bp = 0; bp < 64; bp++)
	   {
	      if (m_fieldMap[bp]->m_isSet == true)
	      {
	         aField = m_fieldMap[bp]->m_fieldPointer;

	         if (aField != NULL)
	         {
				int fieldDataLen = 0;
	            unsigned char *fieldData = NULL;

	            fieldData = aField->serialize (&fieldDataLen, statusRef);
	      
	            if (fieldData != NULL)
	            {
	               memcpy (&m_serializedData[offset], fieldData, fieldDataLen);
	               m_serializedData[offset+fieldDataLen] = 0;
	         
	               offset += fieldDataLen;

				   delete [] fieldData;
				   fieldData = NULL;

				   status = true;
	            }
				else
				{
				   status = false;
				   break;
				}
	         }
	      }
	   }
	}

	if (status == true)
	{
	   returnPtr = new unsigned char [totalLen + 1];

	   if (returnPtr == NULL)
	   {
	      statusRef.update (false, ENOMEM, "Failure - 8583 Implementation Serialize - Insufficient memory");
		  return NULL;
	   }

	   *dataLen = totalLen;
       statusRef.update (true, 0, "method returned success.");

	   // clear out return buffer
	   memset (returnPtr, 0, totalLen + 1);

	   // copy from serialized data to return ptr
	   memcpy (returnPtr, m_serializedData, totalLen+1);

	   //NUL terminate
	   returnPtr[totalLen] = 0;
	}
	else
	{
	   if (m_serializedData != NULL)
	   {
	      delete [] m_serializedData;
		  m_serializedData = NULL;

		  m_serializedDataLen = 0;
	   }

	   statusRef.update (false, ENOMEM, "Failure - 8583 Implementation Serialize - Insufficient memory");
	   return NULL;
	}

	return returnPtr;
}

/*  Name: deSerialize
 *  Arguments:
 *	 dataPtr: Points to the EBCDIC data in the form of a byte stream
 *	  dataLen  : Out parameter - has the actual length of the data - number of bytes in the data
 *   statusRef : Has a reference to the isostatus object.
 *    
 *   Return Type:  bool
 *          Indicates status of operation.  true(1) indicates success and FALSE(0) indicates failure.
 *          Client App will have to check the ISOStatus object for more details
 *          in case if the return value is FALSE(0).
 *
 *   Implementation Details:
 *
 *	 1. For Request object there is no implemention for this method.
 */

bool ISO8583Implementation::deSerialize(const unsigned char *data, int dataLen, ISOStatus& statusRef)
{
	int offset = 0;	
    short bitPos = 0;
	int tmpDataLen = 0;
	char txt[255 + 1]= "";
	unsigned char *tmpData = NULL;

    statusRef.update (true, 0, "method returned success.");

	if (data == NULL)
    {
	   statusRef.update (false, INVALID, "Error: no bytestream data");

	   return false;
    }
    else
    {
	   if (dataLen < 4)
	   {
	      statusRef.update (false, INVALID, "Error: not enough bytestream data for message type.");

		  return false;
	   }

	   // deSerialize the Message Type.
	   // First four bytes will be the message type.
	   char tmpMsgType[4+1] = "";
	   memcpy (tmpMsgType, data, 4);

	   // NUL terminate
	   tmpMsgType[4] = 0;

	   offset = 4;

	   // The bytestream contains EBCDIC so convert the msgType
	   CharUtility::toAsciiStrInplace ((unsigned char *)tmpMsgType, 4);

	   // We don't want to load a bytestream that was serialized
	   // by a different msgType
//	   if (strcmp (m_msgType, tmpMsgType) != 0)
//	   {
//	      sprintf (txt,
//				"Error: not an ISO%s bytestream.\n",
//				   m_msgType);
//
//	      statusRef.update (false, INVALID, txt);
//
//	      return false;
//	   }

	   // check to see that we have more data past the msgType
	   if (dataLen < 12)
	   {
	      statusRef.update (false, INVALID, "Error: not enough bytestream data for bitmap.");

	      return false;	      
	   }

	   int numBytes = (m_mapSize / 8);

	   // deSerialize the bitmap.
	   // Next eight or sixteen bytes will be the bitmap.
	   unsigned char tmpBitmap[16] = "";

	   memset (tmpBitmap, 0, 16);

	   memcpy (tmpBitmap, &data[offset], numBytes);

	   offset += numBytes;

	   // deSerialize the bitmap

	   int j=0;
	   if (m_bitmap != NULL)
	   {
		  // numBytes should be 8 or 16
			m_bitmap->deSerialize (tmpBitmap, numBytes);


	   // Setup the fieldmap "isSet" flag for use later.
			for (j = 0; j < m_mapSize; j++)
			{
			  if (m_bitmap->isBitSet (j+1) == true)
			  {
				 if ((m_fieldMap[j] != NULL)
				  && (m_fieldMap[j]->m_isSupported == true))
				 {
					m_fieldMap[j]->m_isSet = true;

					if (gDebug)
					   cout << "Bit" << (j+1) << " is set." << endl;
				 }
			  }
		   }
	   }

	   // check to see that we have more data past the msgType
//	   if (dataLen < 12)
//	   {
//	      statusRef.update (false, INVALID, "Error: not enough bytestream data for data fields.");
//
//	      return false;	      
//	   }

	   // Now lets start deSerializing all the fields that were received.
       for (j = 0; j < m_mapSize; j++)
	   {
	      if (m_fieldMap[j] != NULL)
		  {
	         if (m_fieldMap[j]->m_isSet == true)
			 {
				tmpDataLen = m_fieldMap[j]->m_maxDataLength;

				tmpData = new unsigned char[tmpDataLen+1];

				if (tmpData == NULL)
				{
				   statusRef.update (false, ENOMEM, "Failure - deSerialize - Insufficient memory");

				   return false;
				}
				else
				{
				   memset (tmpData, 0, tmpDataLen+1);
			       memcpy (tmpData, &data[offset], tmpDataLen);
                   tmpData[tmpDataLen] = 0;

	               // deSerialize each field.
				   // Note that we dont know the length of each field, but we do know the
				   // max length. I pass max length as the length, but deserialize on the
				   // field expects 2(LLVar) or 3(LLLVar) bytes of length prepended to
				   // the data.
	               if ((m_fieldMap[j]->m_fieldPointer != NULL)
				    && (m_fieldMap[j]->m_fieldPointer->deSerialize (tmpData,
					                                                tmpDataLen,
															        statusRef) == true))
				   {
				      // since we didn't know the length we need to take into account the
				      // real length of data extracted by the field.
	                  offset += m_fieldMap[j]->m_fieldPointer->getSize ();

				      // Now based on the field type we add the number of length bytes
				      // so the next time around the loop we are positioned at the start
				      // of the next field.
				      // The value for fieldType in the fieldMap is set to
				      // the proper length 0=FIXEDLENGTH,2=LLVARLENGTH,3=LLLVARLENGTH.

				      if (m_fieldMap[j]->m_fieldType == FIXEDLENGTH)
					  {
	                     offset += FIXEDLENGTH; // Fixed 
					  }
				      else if (m_fieldMap[j]->m_fieldType == LLVARLENGTH)
					  {
	                     offset += LLVARLENGTH; // LLVar
						 if (gPackedBCD)
							 offset--;
					  }
				      else if (m_fieldMap[j]->m_fieldType == LLLVARLENGTH)
					  {
	                     offset += LLLVARLENGTH; // LLLVar
						 if (gPackedBCD)
							 offset--;
					  }
				   }

				   delete [] tmpData;
				   tmpData = NULL;
				}
			 }//end of isSet
		  }//end of m_fieldMap[j]
	   }//end of for

	   // should call validate here!

	   return true;

	}//end of data
	
	//if an error occurs in the process of deSerialization return false.
	return false;
}


/* Name:                writeBinToFile
 *
 * Arguments:           const char *filename, const char *className, ISOStatus& statusRef
 *                                   
 * Return type:         boolean
 *
 * Scope:               public
 *
 * Implementation Details: 	This method serializes the message field data and
 *                      writes the data to a file. The name of the class
 *                      which contained the message field data will be written
 *                      to the file to allow validation to function
 *                      (load with proper class).
 *                      
 *                      Format:
 *                      MessageClassName[| pipe]
 *                      {4 byte msgType}{8 byte bitmap}{field data}
*/
bool ISO8583Implementation::writeBinToFile (const char *filename, const char *className, ISOStatus& statusRef)
{
	FILE *fp = NULL;
	char txt[255+1] = "";
	char hdr[128+1] = "";
	int serializedMsgDataLen = 0;
	unsigned char *serializedMsgData = NULL;

	// must have a valid filename.
	if ((filename == NULL)
     || ((strcmp (filename, "") == 0)))
	{
	   if (gTrace)
	      cout << "ISO8583Implementation::writeBinToFile - filename must be specified." << endl;
	 
	   statusRef.update (false, INVALID, "filename must be specified.");

	   return false;
	}

	// open the output file.
	fp = fopen (filename, "wb");

	if (fp == NULL)
	{
	   if (gTrace)
	      cout << "ISO8583Implementation::writeBinToFile - error opening file: " << filename << "." << endl;

	   sprintf (txt,
		   "error opening file: %s.",
		      filename);

	   statusRef.update (false, INVALID, txt);

	   return false;
	}

	// serialize the instance data to a bytestream.
	serializedMsgData = serialize (&serializedMsgDataLen, statusRef);

	if (statusRef.getStatus () == false)
	{
	   if (gTrace)
	         cout << "ISO8583Implementation::writeBinToFile - serialize returned: " << statusRef.getResultCode () << " " << statusRef.getResultDesc () << "." << endl;

	   sprintf (txt,
			  "deSerialize returned: %d >%s<",
						statusRef.getResultCode (),
						statusRef.getResultDesc ());

	   statusRef.update (false, INVALID, txt);

	   return false;
	}

	if (serializedMsgData == NULL)
	{
	   if (gTrace)
	      cout << "ISO8583Implementation::writeBinToFile - error allocating serializedMsgData." << endl;

	   sprintf (txt,
		   "error allocating serializedMsgData.");

	   statusRef.update (false, ENOMEM, txt);

	   return false;
	}

	if (serializedMsgDataLen > 0)
	{
	   if (gTrace)
	      cout << "ISO8583Implementation::writeBinToFile - writing " << serializedMsgDataLen << " bytes to file." << endl;

	   sprintf (txt,
		   "writing %d bytes to file.",
		      serializedMsgDataLen);

	   statusRef.update (true, VALID, txt);

	   if ((className != NULL)
		&& (strcmp (className, "") != 0))
	   {
		  // create the hdr if the class name was passed in.
	      sprintf (hdr,
		     "%s|",
		        className);

	      // write the header to disk.
	      fwrite (hdr, strlen (hdr), sizeof (char), fp);
	   }

	   // write the serialized ISO message data to disk.
	   fwrite (serializedMsgData, serializedMsgDataLen, sizeof (unsigned char), fp);
	}

	// close the output file.
	fclose (fp);

	if (serializedMsgData != NULL)
	{
	   delete [] serializedMsgData;
	   serializedMsgData = NULL;
	}

	return true;
}


/* Name:                loadBinFromFile
 *
 * Arguments:           const char *filename, const char *className, ISOStatus& statusRef
 *                                   
 * Return Value:        boolean
 *
 * Scope:               public
 *
 * Implelementation Details:	This method deSerializes the message field
 *                      data from a file. The name of the class dictates which
 *                      class is instanciated to contain the message field data to
 *                      allow validation to function correctly.
 *                      
 *                      Format:
 *                      MessageClassName[| pipe]
 *                      {4 byte msgType}{8 byte bitmap}{field data}
 */

bool ISO8583Implementation::loadBinFromFile (const char *filename, const char *className, ISOStatus& statusRef)
{
	FILE *fp = NULL;
	int numRead = 0;
	size_t len = 0;
	char txt[255+1] = "";
	char hdr[128+1] = "";
	size_t fileLength = 0;
	int serializedMsgDataLen = 0;
	unsigned char *serializedMsgData = NULL;

	// must have a valid filename.
	if ((filename == NULL)
	 || (strcmp (filename, "") == 0))
	{
	   if (gTrace)
	      cout << "ISO8583Implementation::loadBinFromFile - filename must be specified." << endl;
	 
	   statusRef.update (false, INVALID, "filename must be specified.");
	   
	   return false;
	}

	// open the input file.
	fp = fopen (filename, "rb");

	if (fp == NULL)
	{
	   if (gTrace)
	      cout << "ISO8583Implementation::loadBinFromFile - error opening file: " << filename << "." << endl;

	   sprintf (txt,
		   "error opening file: %s.",
		      filename);

	   statusRef.update (false, INVALID, txt);
	   
	   return false;
	}

	// seek to end of file test get binary file length.
	fseek (fp, 0, SEEK_END);
	fileLength = ftell (fp);

	// go back to the begining.
	fseek (fp, 0, SEEK_SET);

	serializedMsgDataLen = fileLength;

	serializedMsgData = new unsigned char[fileLength + 1];

	if (serializedMsgData == NULL)
	{
	   if (gTrace)
	      cout << "ISO8583Implementation::loadBinFromFile - error allocating serializedMsgData." << endl;

	   sprintf (txt,
		   "error allocating serializedMsgData.");

	   statusRef.update (false, ENOMEM, txt);

	   return false;
	}

	memset (serializedMsgData, 0, fileLength + 1);

	// read the header.
	numRead = fscanf (fp,
		         "%[^|]",
				    hdr);

	if (strcmp (hdr, "") != 0)
	{
	   if (gTrace)
	      cout << "Found class hdr: " << hdr << "." << endl;
	      
	   len = (fileLength - (strlen (hdr) + 1));
	   
	   // read the pipe symbol and discard
	   numRead = fread (serializedMsgData,
	                    sizeof (unsigned char),
	                    1,
	                    fp);
	}
	else
	{
	   if (gTrace)
	      cout << "No class hdr found." << endl;

	   len = fileLength;
	}
	
	// read the bytestream off disk.
	numRead = fread (serializedMsgData,
	                 sizeof (unsigned char),
					 len,
					 fp);
    
	serializedMsgDataLen = len;

	// deSerialize the instance data from the bytestream.
	deSerialize (serializedMsgData, serializedMsgDataLen, statusRef);

	if (statusRef.getStatus () == false)
	{
	   if (gTrace)
	      cout << "ISO8583Implementation::loadBinFromFile - deSerialize returned: " << statusRef.getResultCode () << " " << statusRef.getResultDesc () << "." << endl;

	   sprintf (txt,
	      "deSerialize returned: %d >%s<",
						statusRef.getResultCode (),
						statusRef.getResultDesc ());

	   statusRef.update (false, INVALID, txt);
	}

	if (gTrace)
	   cout << "ISO8583Implementation::loadBinFromFile - loaded " << serializedMsgDataLen << " bytes from file." << endl;

	sprintf (txt,
		   "read %d bytes from file.",
		      serializedMsgDataLen);

	statusRef.update (true, VALID, txt);

	delete [] serializedMsgData;
	serializedMsgData = NULL;
	
	// close the input file.
	fclose (fp);

	return true;
}

/*  Method Name: getMessageType
 *  Arguments: none
 *    
 *  Return Type:  char *
 *			Character array representing this message type.
 *			For 1100Message value "1100" will be returned.
 *
 *   Implementation Details:
 *
 *	 1. This method retrieves the msgType attribute and returns the value.
 */


char* ISO8583Implementation::getMessageType()
{
       return m_msgType;
}


/*  Method Name: getMapSize
 *  Arguments: none
 *    
 *  Return Type:  int
 *         This method retrieves the "mapSize" attribute and returns it.
 *         The value could be anythong between 64 to 128.
 *
 *   Implementation Details:
 *
 *	 1. This method retrieves the "mapSize" attribute and returns the value.
 */

int ISO8583Implementation::getMapSize()
{
       return m_mapSize;
}



/*  Method Name: getResponseType
 *  Arguments: none
 *    
 *  Return Type:  char *
 *                Returns the response type for this object
 *
 *
 *   Implementation Details:
 *
 *	 1. This method returns the response type for this message.
 */


char* ISO8583Implementation::getResponseType ()
{
       return NULL;
}

/*  Method Name: getRequestType
 *  Arguments: none
 *    
 *  Return Type:  char *
 *                Returns the request type for this object
 *
 *
 *   Implementation Details:
 *
 *	 1. This method returns the request type for this message.
 */


char *ISO8583Implementation::getRequestType ()
{
       return NULL;
}

char *ISO8583Implementation::getClassName (void)
{
    return m_className;
}

ISO8583Implementation *ISO8583Implementation::Make (char * mName, int mapsize)
{
	return 0;
}
