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

#ifndef ISO_MSGHANDLER_H
#define ISO_MSGHANDLER_H

#include <stdio.h>
#include <string.h>

//project specific header includes
#include "ISOStatus.h"
#include "MessageFactory.h"
#include "CharUtility.h"
#include "linklist.h"

typedef struct
{
	char m_strMsgType[4+1];
	char m_strClassName[64+1];
    int iBitmapSize;
} MSG_MAP;

class ISOMsgHandler
{
private:
    ISOStatus m_isoStatus;

	ElemLst<MSG_MAP>  m_msgMapList;

public:
    ISOMsgHandler ();

    ~ISOMsgHandler ();

private:
    MSG_MAP *msgMapFind (char *strMsgType);

public:
    MSG_MAP *msgMapAdd (char *strMsgType, char *strClassName);

    ISO8583Message *vendMsg (char *strMsgType, ISOStatus & statusRef);

};

#endif

