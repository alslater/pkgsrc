/*********************************************************************
*
*   Module:
*       ISOMsgHandler.h
*
*   Contents:
*       Implementation of the ISOMsgHandler class constructor
*       and methods
*       
*   Description
*        
*   This class implements a linked-list based message mapping
*   functionality. The API caller can specify which class instance
*   will be created for each 4-byte ISO message type identifier.
*   If the API caller sets up a entry with "****" this will
*   be considered the default and if no specific match is found
*   the "****" map entry will be used.
*
*   See Also:
*       ISOMsgHandler.cpp
*
*   Created:
*		21 Mar 2002 Lonnie L. Filbrun
*
*   Modified:
*       21 Mar 2002 LLF - New for private payments functionality.
*
*
**********************************************************************/

#include "ISOMsgHandler.h"

ISOMsgHandler::ISOMsgHandler ()
{ 
    return;
}

ISOMsgHandler::~ISOMsgHandler ()
{
}

ISO8583Message *ISOMsgHandler::vendMsg (char *strMsgType, ISOStatus & statusRef)
{
    int iBitmapSize = 64;
    MSG_MAP *msgMap = NULL;
    ISO8583Message *newMessage = NULL;

    // Lookup a message class name based on the message type.
    msgMap = msgMapFind (strMsgType);

    if (msgMap != NULL)
    {
       // Construct a new message instance.
       newMessage = ISO8583MessageFactory ().createMessage (msgMap->m_strClassName,
                                                            iBitmapSize,
                                                            statusRef);
    }

    return newMessage;
}

// add a message mapping into the mapping list
MSG_MAP *ISOMsgHandler::msgMapAdd (char *strMsgType, char *strClassName)
{
    MSG_MAP *newMsgMap = NULL;

    newMsgMap = new MSG_MAP;

	if (newMsgMap != NULL)
    {
       strcpy (newMsgMap->m_strMsgType, strMsgType);
       strcpy (newMsgMap->m_strClassName, strClassName);

       m_msgMapList.Add (newMsgMap);
    }
    
	return newMsgMap;
}

// locate a message based on the ISO 4-byte type
// and return a message mapping.
// If the default map is set ("****") it will be
// used if no specific match is made, defaulting to
// the className specified in the mapping.
MSG_MAP *ISOMsgHandler::msgMapFind (char *strMsgType)
{
	MSG_MAP *msgMap = NULL;
    MSG_MAP *returnedMsgMap = NULL;
	ElemLstIterator<MSG_MAP> *iter = NULL;

    // Get a list iterator
	iter = m_msgMapList.getIter ();

	if (iter != NULL)
    {
       // get the list head
	   msgMap = iter->getThis ();

	   while (msgMap)
       {
          // if you find it return a match
          if (strcmp (msgMap->m_strMsgType, strMsgType) == 0)
          {
             returnedMsgMap = msgMap;
             break;
          }

          // get the next entry on the list
	      msgMap = iter->getNext ();
       }

       // free the list iterator
	   delete iter;
    }

    if (returnedMsgMap == NULL)
    {
       // Do the default mapping.
//       returnedMsgMap = msgMapFind ("****");
    }

    return returnedMsgMap;
}

