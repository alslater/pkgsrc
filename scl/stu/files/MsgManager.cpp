
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "MsgManager.h"

using namespace std;

extern int gTrace;
extern int gDebug;

MsgManager::MsgManager ()
{
	if (gDebug)
	   cout << "MsgManager::MsgManager()." << endl;
	
	init ();

	return;
}

MsgManager::MsgManager (MSG_ENTRY *aMsgTable, int count)
{
	if (gDebug)
	   cout << "MsgManager::MsgManager(aMsgTable)." << endl;
	
	init ();

	setMsgTable (aMsgTable, count);

	return;
}

MsgManager::~MsgManager ()
{
	if (gDebug)
	   cout << "MsgManager::~MsgManager()." << endl;
	
	return;
}

void MsgManager::init (void)
{
	if (gDebug)
	   cout << "MsgManager::init()." << endl;
	
	m_msgTable = NULL;
	m_msgTableCount = 0;

	return;
}

void MsgManager::setMsgTable (MSG_ENTRY *aMsgTable, int msgTableCount)
{
	m_msgTable = aMsgTable;

	m_msgTableCount = msgTableCount;

	return;
}

int MsgManager::getMsgIndex (int code)
{
	register int low = 0;
    register int mid = 0;
    register int high = m_msgTableCount;
	// (sizeof (*msgTable) / sizeof (MSG_ENTRY) - 1);

    while (low <= high)
    {
       mid = (low + high) / 2;

       if (code < m_msgTable[mid].code)
       {
          high = mid - 1;
       }
       else if (code > m_msgTable[mid].code)
       {
          low = mid + 1;
       }
       else
          return mid;  /* found, returns index in array */

    } /*end  while */

    return -1; /* not found */
}

char *MsgManager::getMsgFormat (int code, char *level)
{
	int index = 0;
	MSG_ENTRY *me = NULL;

	index = getMsgIndex (code);

	if (index == -1)
	{
	   return NULL;
	}

	*level = m_msgTable[index].level;

	return m_msgTable[index].format;
}

void MsgManager::logMsg (int code, ...)
{
    va_list marker;
	time_t timer;
	int month = 0;
	int year = 0;
	FILE *fp = NULL;
	char logMsg[512+1] = "Unknown Message Format.\n";
	char logFile[255+1] = "";
	char level = '\0';
    struct tm localTime;
		struct tm * localTime_ptr;
    char currentTime[10] = "";
	char *format = NULL;

	// if global trace == 0 DONT trace!
	if (gTrace == 0)
	   return;

	// get the format replacement string.
	format = getMsgFormat (code, &level);

	if (format != NULL)
	{
		// replace variable args in .
		va_start (marker, code);
		vsprintf (logMsg, format, marker);
		va_end (marker);
	}

	// Get the current time
    time (&timer);

    // Convert to local time
#ifdef _WIN32
	localTime_ptr = localtime(&timer);
#else
	// (Use POSIX function localtime_r() for thread safety) 
    localtime_r(&timer, &localTime);
	localTime_ptr = &localTime;
#endif

	month = (localTime_ptr->tm_mon + 1);		

	if (localTime_ptr->tm_year < 100)
	   year = localTime_ptr->tm_year;
	else
	   year = (localTime_ptr->tm_year - 100);

	// Setup the log filename
    sprintf (logFile,
             "trace%.2i%.2i%.2i.%s",
	            month,
	            localTime_ptr->tm_mday,
	            year,
	            "log");

	fp = fopen (logFile, "a+");

	if (fp != NULL)
	{
	   // Output format:
	   //  
	   // HH:MM:SS: {logMsg}
	   //

	   // Setup the timestamp
       sprintf (currentTime,
                "%.2i:%.2i:%.2i",
                   localTime_ptr->tm_hour,
                   localTime_ptr->tm_min,
                   localTime_ptr->tm_sec);

	   // write it to the log file
	   fprintf (fp,
		        "%s %c %d: %s",
		        currentTime,
				level,
				code,
				logMsg);

	   // close the log file.
	   fclose (fp);
	}

	return;
}
