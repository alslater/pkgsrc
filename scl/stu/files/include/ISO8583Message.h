/*********************************************************************
*
*   File name:
*       ISO8583Message.h
*
*   Contents:
*       ISO8583Message Class
*
*   Description:
*
*		This header file contains the virtual base class for all the message types,
*		i.e, ISO8583Message. All the ISO messages derived from this class implement the
*		virtual functions in this class.
*
*   See Also:
*
*
*
*   Created:
*       05/21/01 Arun G.
*
*   Modified:
*		08 June 2001 Shubha Kumar
*				-Moved the attribute msgType to the derived class - ISO8583Implementation
*				-Removed the overloaded constructor
*		12 June 2001 Shubha Kumar
*				-Added the length argument to get, set, serialize and deserialize fields.
*
**********************************************************************/
#ifndef ISO8583MESSAGE_H
#define ISO8583MESSAGE_H

#include "STU_platform.h"

//specific inlcudes
#include "ISOStatus.h"

/**************************************************************************
 *
 * CLASS NAME:          ISO8583Message
 *
 * SCOPE:               public and pure virtual
 *
 * DESCRIPTION:
 *
 * The ISO8583Message is the base class for all the ISO8583 messages. This is a
 * virtual base class and all the message categories derived from this class
 * should be providing implementation for all the virtual functions of this class.
 * The appropriate function from the derived classes are called depending on which
 * class the base class pointer points to:
 *
 **************************************************************************
 */

 class LINKDLL ISO8583Message
 {
	private:

	//Constructor and Methods
    public:

		//Default Constructor
		ISO8583Message ();

		//Destructor
		//The destructor will set the pointer reference to NULL
		virtual ~ISO8583Message();

        //Methods - all are pure virtual methods to be implemented in the derived classes


		/**************************************************************************
		 *
		 * NAME:                setField
		 *
		 * ARGUMENTS:           int bitPosition, int charType, unsigned char *data, const int dataLen
		 *						ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will set the field represented by the
		 *						'bitPosition with the 'data' sent in as the pointer to a character array
		 *						in the form of EBCDIC or ASCII as specified by 'charType'. It updates the
		 *						ISOStatus object.
		 *
		 **************************************************************************
		 */
		 virtual bool setField(const int bitPosition, const int charType, const unsigned char *data, const int dataLen, ISOStatus& statusRef) = 0;


		/**************************************************************************
		 *
		 * NAME:                getField
		 *
		 * ARGUMENTS:           int bitPosition, int charType, int* dataLen, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        unsigned char *
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will return data set the field represented
		 *						by the 'bitPosition' in the form of EBCDIC or ASCII as specified by 'charType'.
		 *						It updates the ISOStatus object
		 **************************************************************************
		 */
		 virtual unsigned char *getField(int bitPosition, int charType, int* dataLen, ISOStatus& statusRef) = 0;


		/**************************************************************************
		 *
		 * NAME:                getField2
		 *
		 * ARGUMENTS:           int bitPosition, int charType, unsigned char *data, int dataLen, int maxDataLen ISOStatus& statusRef
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
		 virtual bool getField2(int bitPosition, int charType, unsigned char *data, int *dataLen, int maxDataLen, ISOStatus& statusRef) = 0;


         virtual void releaseFieldData (int bitPosition, unsigned char *data, ISOStatus& statusRef) = 0;

		 /**************************************************************************
		 *
		 * NAME:                getMessageType
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        char*
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will return the character array representing the
		 *						messageType like "1100", "1110", "1420", "1430", "1220" or "1230"
		 **************************************************************************
		 */
		 virtual char* getMessageType() = 0;


		 /**************************************************************************
		 *
		 * NAME:                getMapSize
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        int
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will get the Map Size of the
		 *						ISOMessage object
		 **************************************************************************
		 */
		 virtual int getMapSize() = 0;


		/**************************************************************************
		 *
		 * NAME:                validate
		 *
		 * ARGUMENTS:           ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will validate the whole message object using the
		 *						corresponding validation class. It updates the ISOStatus object
		 **************************************************************************
		 */
		 virtual bool validate(ISOStatus& statusRef) = 0;


		/**************************************************************************
		 *
		 * NAME:                serialize
		 *
		 * ARGUMENTS:           int* dataLen, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        unsigned char*
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will return a pointer to the
		 *						EBCDIC character byte stream formed by serializing the Message Data.
		 *						It updates the ISOStatus object
		 **************************************************************************
		 */
		 virtual unsigned char *serialize(int* dataLen, ISOStatus& statusRef) = 0;


		/**************************************************************************
		 *
		 * NAME:                deSerialize
		 *
		 * ARGUMENTS:           unsigned char *responsePtr, int dataLen, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will extract a ASCII character byte stream
		 *						from the EBCDIC character byte stream represented by 'dataPtr'. It updates the
		 *						ISOStatus object
		 **************************************************************************
		 */
		 virtual bool deSerialize(const unsigned char *data, int dataLen, ISOStatus& statusRef) = 0;


		/**************************************************************************
		 *
		 * NAME:                writeBinToFile
		 *
		 * ARGUMENTS:           const char *filename, const char *className, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public and pure virtual
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
		 virtual bool writeBinToFile (const char *filename, const char *className, ISOStatus& statusRef) = 0;


		/**************************************************************************
		 *
		 * NAME:                loadBinToFile
		 *
		 * ARGUMENTS:           const char *filename, const char *className, ISOStatus& statusRef
		 *
		 * RETURN VALUE:        boolean
		 *
		 * SCOPE:               public and pure virtual
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
		 virtual bool loadBinFromFile (const char *filename, const char *className, ISOStatus& statusRef) = 0;


		 /**************************************************************************
		 *
		 * NAME:                getResponseType
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        char*
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will return the appropriate
		 *						response message type.
		 **************************************************************************
		 */
		 virtual char* getResponseType() = 0;


		 /**************************************************************************
		 *
		 * NAME:                getRequestType
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        char*
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will return the appropriate
		 *						request message type.
		 **************************************************************************
		 */
		 virtual char* getRequestType() = 0;


		 /**************************************************************************
		 *
		 * NAME:                getClassName
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        char*
		 *
		 * SCOPE:               public and pure virtual
		 *
		 * DESCRIPTION:			The implementation of this function will return the appropriate
		 *						request message class name.
		 **************************************************************************
		 */
         virtual char *getClassName (void) = 0;

};

#endif

