/*********************************************************************
*
*   File name:
*       ISO8583Implementation.h
*
*   Contents:
*       ISO8583Implementation Class
*
*   Description:
*
*		This header file contains the definitions of the methods to be implemented.
*		This class has implementation for the set, get, validate, serialize methods.
*		The derived classes are to make a call to the methods here for implementation
*
*
*   See Also:
*		ISOStatus.h
*		ISO8583Message.h
*		FieldMapElement.h
*
*
*
*   Created:
*       06/08/01 Shubha Kumar
*
*   Modified:
*		12 June 2001 Shubha Kumar
*			-Added the length parameter to the get, set, serialize and deserialize methods
*
*
**********************************************************************/
#ifndef ISO8583IMPLEMENT_H
#define ISO8583IMPLEMENT_H

#include "STU_platform.h"

//specific inlcudes
#include "ISOStatus.h"
#include "ISO8583Bitmap.h"
#include "ISO8583Message.h"
#include "FieldMapElement.h"
#include "ValidateMessage.h"

/**************************************************************************
 *
 * CLASS NAME:          ISO8583Implementation
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * The ISO8583Implementaion is the derived class for the ISO8583Message class.
 * This class contains the implementaion for all the get and set methods.
 * It also contains the implementaion of some methods like serialize() which also
 * have a common implementation in all the derived classes of this class
 *
 **************************************************************************
 */

 class LINKDLL ISO8583Implementation : public ISO8583Message
 {
	 //Attribute
	private:

    protected:
		//Default Constructor
		ISO8583Implementation();

		//Indicates the type of 8583 Message.
		//Values can be "1100", "1110", "1420", "1430",  "1220", "1230".
		char *m_msgType;

        // ISO1100, etc...
        char *m_className;

	   	// allocate a bitmap instance
	    ISO8583Bitmap *m_bitmap;

		// used by serialize()
	    int m_serializedDataLen;
	    unsigned char *m_serializedData;

		//Will hold reference to the corresponding ValidateMessage object.
		// Uncomment later
		 ValidateMessage *m_validator;

		//Will indicate the size of the ISO8583 Message.
		//Defaulted to 64 but can be extended to 128
		int m_mapSize;

		//An array of FieldMapElement.
		//The size of the array will depend of the "mapSize" attribute
		FieldMapElement *m_fieldMap[64];

    //Constructor and Methods
    public:

		//Constructor
		//The constructor will initialize the msgType and the mapSize attributes
		//with the value supplied in the argument.
		ISO8583Implementation(char* msgTypePtr, int mSize);

		//Destructor
		//The destructor will set the pointer reference to NULL
		~ISO8583Implementation();

        //Methods

		/**************************************************************************
		 *
		 * NAME:                setField
		 *
		 * ARGUMENTS:           int bitPosition, int charType, unsigned char* data, const int dataLen,
		 *						ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will set the field represented by the
		 *						'bitPosition with the 'data' sent in as the pointer to a character array
		 *						in the form of EBCDIC or ASCII as specified by 'charType'. It updates the
		 *						ISOStatus object.
		 *
		 **************************************************************************
		 */
		 bool setField(const int bitPosition, const int charType, const unsigned char *data, const int dataLen, ISOStatus& statusRef);


		/**************************************************************************
		 *
		 * NAME:                getField
		 *
		 * ARGUMENTS:           int bitPosition, int charType, int* dataLen, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        unsigned char*
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will return data set the field represented
		 *						by the 'bitPosition' in the form of EBCDIC or ASCII as specified by 'charType'.
		 *						It updates the ISOStatus object
		 **************************************************************************
		 */
		 unsigned char *getField (int bitPosition, int charType, int* dataLen, ISOStatus& statusRef);


		/**************************************************************************
		 *
		 * NAME:                getField2
		 *
		 * ARGUMENTS:           int bitPosition, int charType, unsigned char *data, int dataLen, int maxDataLen, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        bool
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will return data set the field represented
		 *						by the 'bitPosition' in the form of EBCDIC or ASCII as specified by 'charType'.
		 *						It updates the ISOStatus object
		 **************************************************************************
		 */
		 bool getField2(int bitPosition, int charType, unsigned char *data, int *dataLen, int maxDataLen, ISOStatus& statusRef);


         void releaseFieldData (int bitPosition, unsigned char *data, ISOStatus& statusRef);

		 /**************************************************************************
		 *
		 * NAME:                getMessageType
		 *
		 * ARGUMENTS:           none
		 *
		 * RETURN VALUE:        char*
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will return the character array representing the
		 *						messageType like "1100", "1110", "1420", "1430", "1220" or "1230"
		 **************************************************************************
		 */
		 char* getMessageType();


		 /**************************************************************************
		 *
		 * NAME:                getMapSize
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        int
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will get the Map Size of the
		 *						ISOMessage object
		 **************************************************************************
		 */
		 int getMapSize();


		/**************************************************************************
		 *
		 * NAME:                validate
		 *
		 * ARGUMENTS:           ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will validate the whole message object using the
		 *						corresponding validation class. It updates the ISOStatus object
		 **************************************************************************
		 */
		 bool validate(ISOStatus& statusRef);


		/**************************************************************************
		 *
		 * NAME:                serialize
		 *
		 * ARGUMENTS:           int* dataLen, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        unsigned char*
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will return a pointer to the
		 *						EBCDIC character byte stream formed by serializing the Message Data.
		 *						It updates the ISOStatus object
		 **************************************************************************
		 */
		 unsigned char *serialize (int* dataLen, ISOStatus& statusRef);

		/**************************************************************************
		 *
		 * NAME:                deSerialize
		 *
		 * ARGUMENTS:           unsigned char *data, int* dataLen, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will extract a ASCII character byte stream
		 *						from the EBCDIC character byte stream represented by 'dataPtr'. It updates the
		 *						ISOStatus object
		 **************************************************************************
		 */
		 bool deSerialize (const unsigned char *data, int dataLen, ISOStatus& statusRef);


		/**************************************************************************
		 *
		 * NAME:                writeBinToFile
		 *
		 * ARGUMENTS:           const char *filename, const char *className, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			This method serializes the message field data and
		 *                      writes the data to a file. The name of the class
		 *                      which contained the message field data will be written
		 *                      to the file to allow validation to function
		 *                      (load with proper class).
		 *
		 *                      Format:
		 *                      MessageClassName[CRLF]
         *                      {4 byte msgType}{8 byte bitmap}{field data}
		 **************************************************************************
		 */
		 bool writeBinToFile (const char *filename, const char *className, ISOStatus& statusRef);


		/**************************************************************************
		 *
		 * NAME:                loadBinToFile
		 *
		 * ARGUMENTS:           const char *filename, const char *className, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			This method deSerializes the message field data from
		 *                      a file. The name of the class dictates which class
		 *                      is instanciated to contain the message field data to
		 *                      allow validation to function correctly.
		 *
		 *                      Format:
		 *                      MessageClassName[CRLF]
         *                      {4 byte msgType}{8 byte bitmap}{field data}
		 **************************************************************************
		 */

		 bool loadBinFromFile (const char *filename, const char *className, ISOStatus& statusRef);


		 /**************************************************************************
		 *
		 * NAME:                getResponseType
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        char*
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will return the appropriate
		 *						response message type.
		 **************************************************************************
		 */

		 char* getResponseType();


		 /**************************************************************************
		 *
		 * NAME:                getRequestType
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        char*
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			The implementation of this function will return the appropriate
		 *						request message type.
		 **************************************************************************
		 */

		 char *getRequestType();

         char *getClassName (void);

		 virtual ISO8583Implementation* Make( char *mName, int mapsize = 64 );
};

#endif

