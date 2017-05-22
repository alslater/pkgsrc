/*********************************************************************
*
*   File name:
*       ISOField.h
*
*   Contents:
*       ISOField virtual class, fixed length and variable length derived
*       classes.
*
*   Description
*
*          This header file contains the virtual base class for the data field
*          for the field elements. It contains the derived classes for the fixed
*          length and the two variable length fields. All the class declaration
*          and definitions is also available here.
*
*   See Also:
*        Char_Util.h
*        Enumerations.h
*        ISOStatus.h
*        FieldMapElement.h
*
*
*
*   Created:
*       05/23/01 Shubha Kumar
*
*   Modified:
*		12 June 2001 Shubha Kumar
*				-Added the length argument to set, get, serialize and deserialize methods
*				-Add a getSize method to return the actual data length stored in the "size" attribute
*       11/21/2001 Lonnie Filbrun
*               Modified class naming to be more consistent.
*
*
**********************************************************************/
#ifndef ISOFIELD_H
#define ISOFIELD_H

//specific includes

#include "Enumerations.h"
#include "ISOStatus.h"

/**************************************************************************
 *
 * CLASS NAME:          ISOField
 *
 * SCOPE:               public and virtual
 *
 * DESCRIPTION:
 *
 * An ISO Field represents the lowest level object that holds the actual data
 * pertaining to that field of the ISO8583 message.
 * Each ISOField object uniquely represents a specific field of the ISO8583 message.
 * The Class is also extensible to cater to the fact that the field can be fixed
 * length or variable length.
 * The ISOField objects will also be able to serialize the data they hold into
 * an EBCDIC byte stream and also de-serialize the EBCDIC byte stream to extract
 * the data pertaining to the object.
 *
 **************************************************************************
 */

 class ISOField
 {
	private:
		//Default Constructor
		ISOField();

	 //Attributes
    protected:

       //stores the pointer to the character array with the data
       unsigned char *m_asciiDataPointer;
       unsigned char *m_ebcdicDataPointer;

	   // Indicates the type of field
	   // FIXEDLENGTH=0,
	   // LLVARLENGTH=2,
	   // LLLVARLENGTH=3
	   FieldType m_fieldType;

       //Indicates the type of data that this field will represent
       //Values can be Numeric(1), Alphanumeric(2), Binary(3) taken from the
       //FieldEnum.h
       int m_dataType;

       //Indicates the length of the actual data size stored in the ISOField object
       int m_size;

       //Indicates the maximum length of data that this field can hold
       int m_maxDataLen;

    //Constructor, Destructor and Methods
    public:

       //Constructor
       //The constructor will initialize the dataType and maxDataLen attributes
       //with the values supplied in the arguments
       ISOField (int dataType, int maxLen);

       //Destructor
       //The destructor will release the memory occupied by the attributes of the class
       virtual ~ISOField () = 0;

       //Methods - all are pure virtual methods to be implemented in the derived classes

       //This method is will set the field with the data sent in as the
       //pointer to a character array in the form of EBCDIC or ASCII as specified
       //by charType. It updates the ISOStatus object overwriting the previous data
	   //and the size attribute with the length of data sent as "dataLength"
       virtual bool setField (const int charType, const unsigned char *data, const int dataLen, ISOStatus& statusRef);

       //This method is supposed to return the data stored in the filed in the
       //form of a pointer to a character array according to the charType mentioned
       //- EBCDIC/ASCII and update the ISOStatus object overwriting the previous data
	   //sends the actual data length in the out parameter "dataLen"
       virtual unsigned char *getField (int charType, int *dataLen, ISOStatus& statusRef);

       //This method is supposed to return the data stored in the filed in the
       //form of a pointer to a character array according to the charType mentioned
       //- EBCDIC/ASCII and update the ISOStatus object overwriting the previous data
	   //sends the actual data length in the out parameter "dataLen"
       virtual unsigned char *getFieldInt (int charType, int *dataLen, ISOStatus& statusRef);

       //This method is supposed to return the data stored in the filed in the
       //form of a pointer to a character array according to the charType mentioned
       //- EBCDIC/ASCII and update the ISOStatus object overwriting the previous data
	   //sends the actual data length in the out parameter "dataLen"
       virtual bool getField2 (int charType, unsigned char *data, int *dataLen, int maxDataLen, ISOStatus& statusRef);

       void releaseFieldData (unsigned char *fieldData);

       //This method will serialize the data in the field to the EBCDIC form
       //and return the pointer to the character array and overwrite the
       //previous data of the ISOStatus object
	   //sends the actual data length in the out parameter "dataLen"
       virtual unsigned char *serialize (int *dataLen, ISOStatus& statusRef) = 0;

       //This method will deserialize the data in the field to the ASCII form
       //and update the pointer to the character array and overwrite the
       //previous data of the ISOStatus object
	   //sends the actual data length in the out parameter "dataLen"
       virtual bool deSerialize (const unsigned char *data, const int dataLen, ISOStatus& statusRef) = 0;

	   //This method returns the data length stored in the "size" attribute
	   virtual int getSize (void);

	   //This method returns the max data length that can be stored in the "size" attribute
	   virtual int getMaxSize (void);

	   virtual int getDataType (void);

	   virtual FieldType getFieldType (void);

	   bool isPackedBCDField() const;
};

/**************************************************************************
 *
 * CLASS NAME:          ISOFieldFixed
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * A ISOFieldFixed represents the fixed length fields - lowest level object that
 * holds the actual data pertaining to that field of the ISO8583 message.
 * Each ISOFieldFixed inherits from the ISOField class and gives the implementation
 * details for the field object.
 * ISOFieldFixed is concrete and instantiable.
 * The ISOFieldFixed objects will also be able to serialize the data they hold into
 * an EBCDIC byte stream and also de-serialize the EBCDIC byte stream to extract
 * the data pertaining to the object.
 *
 **************************************************************************
 */

class ISOFieldFixed : public ISOField
{

 //Constructor, Destructor and Methods
 public:
        //Constructor
        //Will initialize the base class by calling the base class constructor
        //with argument that represents the data type and the maximum data length.
        ISOFieldFixed (int dataType, int maxDataLen);

		//Destructor
        //Will release the memory occupied by the members of this class
        ~ISOFieldFixed ();

        //Methods
        //This method sets the field with the data sent as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //and the size attribute with the length of data sent as "dataLength"
//        bool setField (const int charType, const unsigned char *data, const int dataLen, ISOStatus& statusRef);

        //This method gets the data from the field as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //sends the actual data length in the out parameter "dataLen"
//        unsigned char *getField (int charType, int *dataLen, ISOStatus& statusRef);

        //This method gets the data from the field as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //sends the actual data length in the out parameter "dataLen"
//        unsigned char *getFieldInt (int charType, int *dataLen, ISOStatus& statusRef);

        //This method serializes the data in the field to the EBCDIC byte stream
        //and returns a pointer to character array containing the data
	    //sends the actual data length in the out parameter "dataLen"
        unsigned char *serialize (int *dataLen, ISOStatus& statusRef);

        //This method will deserialize the data in the field to the ASCII form
        //and update the pointer to the character array and overwrite the
        //previous data of the ISOStatus object
	    //sends the actual data length in the out parameter "dataLen"
        bool deSerialize (const unsigned char *data, const int dataLen, ISOStatus& statusRef);
};

/**************************************************************************
 *
 * CLASS NAME:          VarISOField
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * A FixISOVar represents the fixed length fields - lowest level object that
 * holds the actual data pertaining to that field of the ISO8583 message.
 * Each FixISOVar inherits from the ISOField class and gives the implementation
 * details for the field object.
 * FixISOField is concrete and instantiable.
 * The FixISOVar objects will also be able to serialize the data they hold into
 * an EBCDIC byte stream and also de-serialize the EBCDIC byte stream to extract
 * the data pertaining to the object.
 *
 **************************************************************************
 */

class ISOFieldVar : public ISOField
{
 //Attributes

 //Constructor, Destructor and Methods
 public:
        //Constructor
        //Will initialize the base class by calling the base class constructor
        //with argument that represents the data type and the maximum data length.
        ISOFieldVar (int dataType, int maxDataLen);

        //Destructor
        //Will release the memory occupied by the members of this classs
        ~ISOFieldVar ();

       //Methods - all are pure virtual methods to be implemented in the derived classes

       //This method is will set the field with the data sent in as the
       //pointer to a character array in the form of EBCDIC or ASCII as specified
       //by charType. It updates the ISOStatus object overwriting the previous data
	   //and the size attribute with the length of data sent as "dataLength"
//       virtual bool setField (const int charType, const unsigned char *data, const int dataLen, ISOStatus & statusRef) = 0;

       //This method is supposed to return the data stored in the filed in the
       //form of a pointer to a character array according to the charType mentioned
       //- EBCDIC/ASCII and update the ISOStatus object overwriting the previous data
	   //sends the actual data length in the out parameter "dataLen"
//       virtual unsigned char *getField (int charType, int *dataLen, ISOStatus & statusRef) = 0;

       //This method gets the data from the field as the pointer to character array
       //in the encoding format mentioned in "charType"
       //and overwrites the ISOStatus object with the new data
	   //sends the actual data length in the out parameter "dataLen"
//       virtual unsigned char *getFieldInt (int charType, int *dataLen, ISOStatus& statusRef) = 0;

       //This method will serialize the data in the field in the EBCDIC form
       //and return the pointer to the character array and overwrite the
       //previous data of the ISOStatus object
	   //sends the actual data length in the out parameter "dataLen"
//       virtual unsigned char *serialize (int *dataLen, ISOStatus& statusRef) = 0;

       //This method will deserialize the data in the field to the ASCII form
       //and update the pointer to the character array and overwrite the
       //previous data of the ISOStatus object
	   //sends the actual data length in the out parameter "dataLen"
//       virtual bool deSerialize (const unsigned char *data, const int dataLen, ISOStatus& statusRef) = 0;
};

/**************************************************************************
 *
 * CLASS NAME:          ISOFieldLLVar
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * A ISOFieldLLVar represents the variable length fields - lowest level object that
 * holds the actual data pertaining to that field of the ISO8583 message.
 * Each LLVar inherits from the ISOField class and gives the implementation
 * details for the field object.
 * ISOFieldLLVar field holds the size of the data in an array of length 2.
 * The maximum length of data can go up 99. Hence, if the length is to be 7,
 * the array stores it as 09 in the first and the second positions, respectively.
 * ISOFieldLLVar is concrete and instantiable.
 * The ISOFieldLLVar objects will also be able to serialize the data they hold into
 * an EBCDIC byte stream and also de-serialize the EBCDIC byte stream to extract
 * the data pertaining to the object.
 *
 **************************************************************************
 */

class ISOFieldLLVar : public ISOField  // lfil - was VarISOField
{
 //Attributes

 //Constructor, Destructor and Methods
 public:
        //Constructor
        //Will initialize the base class by calling the base class constructor
        //with argument that represents the data type and the maximum data length.
        ISOFieldLLVar (int dataType, int maxDataLen);

        //Destructor
        //Will release the memory occupied by the member attributes
        ~ISOFieldLLVar ();

        //Methods
        //This method sets the field with the data sent as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //and the size attribute with the length of data sent as "dataLength"
//        bool setField (const int charType, const unsigned char *data, const int dataLen, ISOStatus& statusRef);

        //This method gets the data from the field as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //sends the actual data length in the out parameter "dataLen"
//        unsigned char *getField (int charType, int *dataLen, ISOStatus& statusRef);

        //This method gets the data from the field as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //sends the actual data length in the out parameter "dataLen"
//        unsigned char *getFieldInt (int charType, int *dataLen, ISOStatus& statusRef);

        //This method serializes the data in the field to the EBCDIC byte stream
        //and returns a pointer to character array containing the data
	    //sends the actual data length in the out parameter "dataLen"
        unsigned char *serialize (int *dataLen, ISOStatus& statusRef);

        //This method will deserialize the data in the field to the ASCII form
        //and update the pointer to the character array and overwrite the
        //previous data of the ISOStatus object
	    //sends the actual data length in the out parameter "dataLen"
        bool deSerialize (const unsigned char *data, const int dataLen, ISOStatus& statusRef);
};

/**************************************************************************
 *
 * CLASS NAME:          ISOFieldLLLVar
 *
 * SCOPE:               public
 *
 * DESCRIPTION:
 *
 * A ISOFieldLLLVar represents the variable length fields - lowest level object that
 * holds the actual data pertaining to that field of the ISO8583 message.
 * Each ISOFieldLLLVar inherits from the ISOField class and gives the implementation
 * details for the field object.
 * ISOFieldLLLVar field holds the size of the data in an array of length 3.
 * The maximum data length can be upto 999. So if the maximum length is to be 27,
 * the array stores it as 027 in the first, the second and the third positions, respectively.
 * ISOFieldLLLVar is concrete and instantiable.
 * The ISOFieldLLLVar objects will also be able to serialize the data they hold into
 * an EBCDIC byte stream and also de-serialize the EBCDIC byte stream to extract
 * the data pertaining to the object.
 *
 **************************************************************************
 */

class ISOFieldLLLVar : public ISOField // lfil - was VarISOField
{
 //Attributes
 private:

 //Constructor, Destructor and Methods
 public:
        //Constructor
        //Will initialize the base class by calling the base class constructor
        //with argument that represents the data type and the maximum data length.
        ISOFieldLLLVar (int dataType, int maxDataLen);

        //Destructor
        //Will release the memory occupied by the member attributes
        ~ISOFieldLLLVar ();

        //Methods
        //This method sets the field with the data sent as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //and the size attribute with the length of data sent as "dataLength"
//        bool setField (const int charType, const unsigned char *data, const int dataLen, ISOStatus& statusRef);

        //This method gets the data from the field as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //sends the actual data length in the out parameter "dataLen"
//        unsigned char *getField (int charType, int *dataLen, ISOStatus& statusRef);

        //This method gets the data from the field as the pointer to character array
        //in the encoding format mentioned in "charType"
        //and overwrites the ISOStatus object with the new data
	    //sends the actual data length in the out parameter "dataLen"
//        unsigned char *getFieldInt (int charType, int *dataLen, ISOStatus& statusRef);

        //This method serializes the data in the field to the EBCDIC byte stream
        //and returns a pointer to character array containing the data
	    //sends the actual data length in the out parameter "dataLen"
        unsigned char *serialize (int *dataLen, ISOStatus& statusRef);

        //This method will deserialize the data in the field to the ASCII form
        //and update the pointer to the character array and overwrite the
        //previous data of the ISOStatus object
	    //sends the actual data length in the out parameter "dataLen"
        bool deSerialize (const unsigned char *data, const int dataLen, ISOStatus& statusRef);
};

#endif

