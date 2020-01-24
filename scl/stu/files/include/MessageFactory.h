#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H

#include "STU_platform.h"

#include "ISO8583Message.h"

class LINKDLL MessageFactory
{

	public:

	//Constructor
	MessageFactory();

	//Destructor
	virtual ~MessageFactory();

	virtual void Init()=0;

	virtual void UnInit (void)=0;

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
     virtual ISO8583Message* createMessage (const char *, const int, ISOStatus& )=0;

	 virtual void deleteMessage (ISO8583Message *message)=0;

	 virtual void setPackedBCD (int packedBCD) = 0;
	 virtual void setDebug (int debug) = 0;
	 virtual void setTrace (int trace) = 0;

     virtual char *getApiVersion (void) = 0;
     virtual char *getApiBuildInfo (void) = 0;

};

/**************************************************************************
 *
 * CLASS NAME:          NONE
 *
 * SCOPE:               global
 *
 * DESCRIPTION:			This function returns a reference to a global
 *                      MessageFactory instance.
 *
 *                      This function is used internaly to the API and
 *                      should also be used by any client code that wishes
 *                      to construct ISO8583 messages.
 *
 **************************************************************************
 */
extern LINKDLL MessageFactory & ISO8583MessageFactory ();

#endif

