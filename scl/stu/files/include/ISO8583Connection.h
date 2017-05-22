/*********************************************************************
*
*   Module:
*       ISO8583Connection.h
*
*   Contents:
*       Implementation of the ISO8583Connection class constructor
*       and methods
*
*   Description
*
*   This class implements a socket-based TCP/IP network connectivity
*   object for sending and receiving ISO8583 (ISO8583Message *)
*   message objects to the American Express SSL Gateway via SSL
*   and the commdaemon.
*   Note that the commdaemon provides a message multiplexing scheme
*   allowing many client connections to connect to the commdaemon
*   and simultaneously transmit/receive ISO8583 request/responses
*   over one secure, authenticated SSL V3.0 connection to the
*   SSL Gateway. The STAN or "system trace audit number" field is
*   used by the commdaemon to route response messages to the proper
*   client.
*
*   See Also:
*       ISO8583Connection.cpp
*
*
*   Created:
*		19 May 2001 Lonnie L. Filbrun
*
*   Modified:
*       09 July 2001 LLF - fixed includes/ifdefs for UNIX.
*
*
**********************************************************************/
#ifndef ISO8583CONNECTION_H
#define ISO8583CONNECTION_H

// Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Package specific header files
#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stddef.h>
#include <time.h>
#else
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#endif /* _WIN32 */

#ifdef _WIN32
//#define  errno (int)WSAGetLastError()
#endif

#include "STU_platform.h"

#include "ISOStatus.h"
#include "CharUtility.h"
#include "MsgManager.h"
#include "ISOMsgHandler.h"

#include "MessageFactory.h"

/* typedef for return codes */

typedef enum { AMEX_OK=10,                    /* ok */
               AMEX_UNKNOWN_ADDR,             /* unknown byte ordering convention */
               AMEX_NULL_PTR,                 /* null input pointer */
               AMEX_LOW_MEM,                  /* malloc error */
               AMEX_TMOUT,                    /* request timed out */
               AMEX_NOMATCH,                  /* response had no matching request */
               AMEX_NO_AMEX_HOST_INFO,        /* AMEX server details not available */
               AMEX_NO_LOCAL_HOST_INFO,       /* local server details not avlbl */
               AMEX_SELECT_FAIL,              /* error in select */
               AMEX_COMM_AMEX_FAIL,           /* error in commn. with AMEX */
               AMEX_COMM_LOCAL_FAIL,          /* error in interserver commn. */
               AMEX_COMM_DISCONNECT,          /* connection closed by peer */
               AMEX_BAD_REQUEST,              /* wrong request message */
               AMEX_BAD_RESPONSE,             /* wrong response message */
               AMEX_ACCEPT_FAIL,              /* error in accept  */
               AMEX_PROXY_ERROR,              /* received error from proxy  */
               AMEX_CONNECTED,                /* connected to AMEX */
               AMEX_DISCONNECTED,             /* disconnected from AMEX */
               AMEX_COMM_AMEX_BUSY,	      /* Amex is overloaded with msgs and is busy now */
               AMEX_OTHER_FAIL
             } ConnectionInfo ;


#define ISO_UID_SZ    (6)
#define ISO_RC_SZ     (2)

#define ISO_TMOUT_SZ  (4)
#define ISO_MSGLEN_SZ (3)

// length of unique id bit of messages
#define AMEX_MSGID_LEN    (ISO_UID_SZ)
#define AMEX_MSGHDR_SZ    (ISO_RC_SZ)

// The mode argument will be used in future releases to support
// the receiption of messages
#define API_SENDER			0
#define API_RECEIVER		1

// forward declarations
class MsgManager;

class LINKDLL ISO8583Connection
{
	private:
	    int m_iSd;
		int m_iMode;
		int m_iByteOrder;	/* 0 for little endian; 1 for big endian */
	    bool m_bConnected;

		bool m_use_timeouts;
		int m_local_connect_timeout;
		int m_local_send_timeout;
		int m_local_receive_timeout;
		struct timeval m_connect_tv;
		struct timeval m_send_tv;
		struct timeval m_receive_tv;
		struct timeval m_debug_timeout;

	    struct sockaddr_in m_myAddr;
	    struct sockaddr_in m_daemonAddr;

#ifdef _WIN32
        WSADATA m_wsaData;
#endif

	    void setConnected (bool connected);

		int getByteOrdering (void);

		void set_non_blocking(int m_Sock);
		void set_local_timeout(int local_timeout_value, int type);
		void set_local_timeouts(int local_connect_timeout, int local_send_timeout, int local_receive_timeout);
		int connect_with_timeout(int m_Sock, const sockaddr* name, int namelen, bool& timed_out, int& last_error);
		int send_with_timeout(int m_Sock, const char* buf, int len, int flags, bool& timed_out, int& last_error);
		int recv_with_timeout(int m_Sock, char* buf, int len, int flags, bool& timed_out, int& last_error);

	protected:

        MsgManager *m_msgMgr;

        ISOMsgHandler *m_msgHandler;

		bool sendMsg (ISO8583Message *message,
			          const int iTimeout,
					  ISOStatus& statusRef);

		bool sendBin (ISO8583Message *message,
					     ISOStatus& statusRef);

        ISO8583Message *receiveMsg (char *strMsgType,
						            int iBitmapSize,
						            ISOStatus& statusRef);

		unsigned char *receiveBin (char *strMsgType,
						           size_t *msgLen,
						           ISOStatus& statusRef);

    public:

		ISO8583Connection ();
		~ISO8583Connection ();

		bool open (const char *strDnsName,
			       const char *strIpAddr,
				   const char *strPort,
			       const int iMode,
				   ISOStatus& statusRef, int local_connect_timeout = 0,
		           int local_send_timeout = 0, int local_receive_timeout = 0);

		void close (void);

        // API_SENDER mode (client) only
		ISO8583Message *processMessage (ISO8583Message *request, int iTimeout, ISOStatus& statusRef);

        // API_RECEIVER mode (server) only
        bool addMsgMapping (char *strMsgType, char *strClassName, ISOStatus& statusRef);

        // API_RECEIVER mode (server) only
        ISO8583Message *awaitRequest (char *strMsgType, ISOStatus& statusRef);

        // API_RECEIVER mode (server) only
        bool sendResponse (ISO8583Message *response, ISOStatus& statusRef);

	    bool isConnected (void);

        void setMode (int iMode);
        int getMode (void);
};

#endif

