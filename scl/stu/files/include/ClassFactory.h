/**************************************************************************
 * File Name :        ClassFactory.h
 * 
 * Contents:		  ClassFactory class
 *
 * Description :	  This header file contains the class called ClassFactory which is used to 
 *					  instantiate the appropriate message objects as needed by the client application
 *
 * Author :           Arun G
 *
 * Date Created :     05/21/2001
 *
 * Modified :
 *
 *     
 **************************************************************************
 */

//specific includes
#ifndef CLASSFACTORY_H
#define CLASSFACTORY_H

#include "STU_platform.h"

#include "ISO8583Implementation.h"
#include "ISOStatus.h"
#include "linklist.h" 
#include "MessageFactory.h"


/**************************************************************************
 *
 * CLASS NAME:          ClassFactory
 *
 * SCOPE:               public 
 *
 * DESCRIPTION:			ClassFactory is a static class used to create Message objects at run-time. The identity  
 *						of the class to be created is given as the argument by the client application. ClassFactory
 *						will instantiate the class and return the object.
 *
 **************************************************************************
 */

class LINKDLL ClassFactory : public MessageFactory
 {

	private:
	   int m_initialized;

	public:

	//Constructor
	ClassFactory();

	//Destructor
	~ClassFactory();

	void Init();

	void UnInit (void);

	//Function
	/******************************************************************************************
	 *
	 * NAME:                createMessage
	 *
	 * ARGUMENTS:           int MessageType - Specifies the type of object to be created 
	 *						int mapSize - Indicates the number of fields in the ISO8583 message 
	 *						ISOStatus& statusRef - Holds the status of operation
	 *                                   
	 * RETURN VALUE:        ISO8583Message* - An active pointer reference to the newly instantiated class 
	 *										  (NULL in case of exceptions.)
	 *
	 * SCOPE:               public
	 *
	 * DESCRIPTION:			This function creates a ISOMessage object as per the messageType argument
	 *						and returns the base pointer with the bit map size provided as the argument
	 * 
	 ******************************************************************************************
	 */
     ISO8583Message* createMessage (const char *, const int, ISOStatus& );

	/******************************************************************************************
	 *
	 * NAME:                deleteMessage
	 *
	 * ARGUMENTS:           ISO8583Message *message - Specifies the message to destroy.
	 *                                   
	 * RETURN VALUE:        void
	 *
	 * SCOPE:               public
	 *
	 * DESCRIPTION:			This function destroys an ISOMessage object.
	 * 
	 ******************************************************************************************
	 */
	 void deleteMessage (ISO8583Message *message);

	 //Insertion of classes into the factory list
	 ElemLst<ISO8583Implementation>  classList;
	 ISO8583Implementation * addClass( ISO8583Implementation * newM );
	 ISO8583Implementation * newMessage( const char * mName, const int mapSize );
	
	 void setTrace (int trace);
	 void setDebug (int debug);
	 void setPackedBCD(int packedBCD);

     char *getApiVersion (void);
     char *getApiBuildInfo (void);
 
};
 
/**************************************************************************
 *
 * CLASS NAME:          NONE
 *
 * SCOPE:               global
 *
 * DESCRIPTION:			This function returns a reference to a global
 *                      ClassFactory instance.
 *
 *                      This function is used internaly to the API and
 *                      should also be used by any client code that wishes
 *                      to construct ISO8583 messages.
 *
 **************************************************************************
 */
LINKDLL ClassFactory & ISO8583ClassFactory ();

#endif

