/*********************************************************************
*
*   Module:
*       ISO8583Connection.cpp
*
*   Contents:
*       Implementation of the ISO8583Connection class constructor and methods
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
*       ISO8583Connection.h
*
*
*   Created:
*		19 May 2001 Lonnie L. Filbrun
*
*   Modified:
*       09 July 2001 LLF - fixed includes/ifdefs for UNIX.
*       03 April 2002 LLF - added PPS functionality
*                           (addMsgMapping, awaitRequest, sendResponse)
*
*
**********************************************************************/

//Package specific header files
#include "ISO8583Connection.h"

using namespace std;

#ifdef _WIN32
#include "windows.h"
#endif

#ifdef _MSC_VER
#include <process.h>

#define getpid _getpid
#endif

extern int gTrace;
extern int gDebug;

extern "C" void hex_dump (unsigned char *buf, long buflen);

typedef enum
{
	 AMEX_API_ERROR_WSASTARTUP=		100,
	 AMEX_API_ERROR_ALREADY_CONNECTED=	101,
	 AMEX_API_ERROR_MUST_SPECIFY_DNS_OR_IP=	102,
	 AMEX_API_ERROR_MUST_SPECIFY_PORT=	103,
	 AMEX_API_ERROR_SOCKET=			104,
	 AMEX_API_ERROR_SOCKOPT=		105,
	 AMEX_API_ERROR_CONNECT=		106,
	 AMEX_API_FYI_CONNECTED=		107,
	 AMEX_API_ERROR_REQUEST_NULL=		108,
	 AMEX_API_ERROR_NOT_CONNECTED=		109,
	 AMEX_API_ERROR_SENDMSG=		110,
	 AMEX_API_ERROR_SERIALIZE=		111,
	 AMEX_API_ERROR_NOMEM=			112,
	 AMEX_API_ERROR_SEND_LEN=		113,
	 AMEX_API_ERROR_SEND_DATA=		114,
	 AMEX_API_FYI_REQUEST_SENT=		115,
	 AMEX_API_ERROR_RECV_LEN=		116,
	 AMEX_API_ERROR_RECV_DATA=		117,
	 AMEX_API_ERROR_RECV_ERR=		118,
	 AMEX_API_FYI_REQUEST_TIMEOUT=		119,
	 AMEX_API_ERROR_REMOTE_CONNECT=		120,
	 AMEX_API_ERROR_CLASSFACTORY=		121,
	 AMEX_API_FYI_RESPONSE_RECEIVED=	122,
	 AMEX_API_ERROR_UNKNOWN_RESPONSECODE=	123,
	 AMEX_API_FYI_DISCONNECTED=		124,
	 AMEX_API_ERROR_RECEIVEMSG=		125,
	 AMEX_API_ERROR_DESERIALIZE=		126,
	 AMEX_API_NOT_SENDER=			127,
	 AMEX_API_NOT_RECEIVER=			128,
	 AMEX_API_FYI_SOCKET=			129,
	 AMEX_API_ERROR_BUSY=			130
} API_ERRORS;

MSG_ENTRY gMsgTable[] =
{
	 {100, LOG_ERROR, "error: WSAStartup() returned error %d.\n"},
	 {101, LOG_ERROR, "error: already connected.\n"},
	{102, LOG_ERROR, "error: must specify commdaemon dnsName or ipAddr, no local host info.\n"},
	{103, LOG_ERROR, "error: must specify commdaemon port, no local port info.\n"},
	{104, LOG_ERROR, "error: socket() returned error %d.\n"},
	{105, LOG_ERROR, "error: setsockopt() returned error %d.\n"},
	{106, LOG_ERROR, "error: connect() returned error %d.\n"},
	{107, LOG_INFO,  "info: connected to commdaemon, dns: <%s> ip: %s port: %s...\n"},
	{108, LOG_ERROR, "error: request message is NULL.\n"},
	{109, LOG_ERROR, "error: not connected to commdaemon.\n"},
	{110, LOG_ERROR, "error: sendMsg() returned %s.\n"},
	{111, LOG_ERROR, "error: serialize() returned %s.\n"},
	{112, LOG_ERROR, "error: new returned error allocating memory.\n"},
	{113, LOG_ERROR, "error: send() returned error %d sending data length bytes.\n"},
	{114, LOG_ERROR, "error: send() returned error %d sending data bytes.\n"},
	{115, LOG_INFO,  "info: request message sent (%d bytes).\n"},
	{116, LOG_ERROR, "error: recv() returned error %d reading message length bytes.\n"},
	{117, LOG_ERROR, "error: invalid message length %d received.\n"},
	{118, LOG_ERROR, "error: recv() returned error %d reading message data bytes.\n"},
	{119, LOG_ERROR, "error: commdaemon returned request timed out.\n"},
	{120, LOG_ERROR, "error: commdaemon returned error connecting to SSLGateway.\n"},
	{121, LOG_ERROR, "error: class factory returned error instanciating response message, type: %s.\n"},
	{122, LOG_INFO,  "info: received response message (%d bytes).\n"},
	{123, LOG_ERROR, "error: commdaemon returned unknown response code %d.\n"},
	{124, LOG_INFO,  "info: disconnected from commdaemon.\n"},
	{125, LOG_ERROR, "error: receiveMsg() returned %s.\n"},
	{126, LOG_ERROR, "error: deSerialize() returned %s.\n"},
	{AMEX_API_NOT_SENDER, LOG_ERROR, "error: not in API_SENDER mode.\n"},
	{AMEX_API_NOT_RECEIVER, LOG_ERROR, "error: not in API_RECEIVER mode.\n"},
	{AMEX_API_FYI_SOCKET, LOG_INFO, "info: socket() pid=%d fd=%d.\n"},
	{AMEX_API_ERROR_BUSY, LOG_ERROR, "error: commdaemon returned AMEX is Busy.\n"},
};

ISO8583Connection::ISO8583Connection ()
{
	int rval = 0;

	m_iSd = -1;

	 setMode (API_SENDER);
	 setConnected (false);

	m_msgMgr = new MsgManager (gMsgTable, sizeof(gMsgTable)/sizeof(MSG_ENTRY));

	 // override the default mappings
	 m_msgHandler = new ISOMsgHandler ();

	// set the byte ordering flag
	// 0 for little endian;
	// 1 for big endian
	m_iByteOrder = getByteOrdering ();

#ifdef _WIN32
	// attach to winsock dll.
	 rval = WSAStartup (MAKEWORD(2,0), &m_wsaData);

	if (rval != 0)
	{
		 m_msgMgr->logMsg (100, rval);
		return;
	}
#endif

	return;
}

ISO8583Connection::~ISO8583Connection ()
{
	 if (isConnected () == true)
	 {
		 close ();
	 }

#ifdef _WIN32
	// release winsock dll.
	 WSACleanup ();
#endif

	 if (m_msgMgr != NULL)
	{
		delete m_msgMgr;
		m_msgMgr = NULL;
	}

	 if (m_msgHandler != NULL)
	 {
		 delete m_msgHandler;
		 m_msgHandler = NULL;
	 }

	return;
}

void ISO8583Connection::set_non_blocking(int m_Sock)
{
	fd_set socketset;
  	
	FD_ZERO(&socketset);
	FD_SET((unsigned)m_iSd, &socketset);
#ifdef _WIN32
	unsigned long enable = 1L;
	ioctlsocket(m_Sock, FIONBIO, &enable);
#else
	fcntl(m_Sock, F_SETFL, O_NONBLOCK);
#endif
}

// Special cases for testing timeout path.
// As timeouts can be in microseconds and we're using negative for
// setting them, use -1000000 to indicate special cases.
#define DEBUG_TIMEOUT_LEVEL   -1000000

void ISO8583Connection::set_local_timeout(int local_timeout_value, int type)
{
	int *local_timeout;
	struct timeval *tv;

	switch (type)
	{
		case 0:
			local_timeout = &m_local_connect_timeout;
			tv = &m_connect_tv;
			break;
		case 1:
			local_timeout = &m_local_send_timeout;
			tv = &m_send_tv;
			break;
		case 2:
			local_timeout = &m_local_receive_timeout;
			tv = &m_receive_tv;
			break;
		default:
			return;
	}

	*local_timeout = local_timeout_value;
	if (*local_timeout > 0)
	{
		tv->tv_sec = *local_timeout;
		tv->tv_usec = 0;
	}
	else if (*local_timeout < 0)
	{
		if (*local_timeout == DEBUG_TIMEOUT_LEVEL)
		{
			// special cases for testing connect, send and receive timeouts
			tv->tv_sec = 30;
			tv->tv_usec = 0;

			m_debug_timeout.tv_sec = 0;
			m_debug_timeout.tv_usec = 1;
		}
		else
		{
			tv->tv_sec = 0;
			tv->tv_usec = abs(*local_timeout);
		}
	}
}

void ISO8583Connection::set_local_timeouts(int local_connect_timeout, 
                               int local_send_timeout, int local_receive_timeout)
{
	// if one, then all must be set
	bool connect_done(false);
	bool send_done(false);
	bool recv_done(false);

	m_local_connect_timeout = m_local_send_timeout = m_local_receive_timeout = 0;

	if (local_connect_timeout != 0)
	{
		set_local_timeout(local_connect_timeout, 0);
		connect_done = true;
	}

	if (local_send_timeout != 0)
	{
		set_local_timeout(local_send_timeout, 1);
		send_done = true;
		if (!connect_done)
		{
			set_local_timeout(local_send_timeout, 0);
			connect_done = true;
		}
	}
	else if (connect_done)
	{
		// set send to same as connect
		set_local_timeout(local_connect_timeout, 1);
		send_done = true;
	}

	if (local_receive_timeout != 0)
	{
		set_local_timeout(local_receive_timeout, 2);
		recv_done = true;
		if (!connect_done)
		{
			// set connect to same as send
			set_local_timeout(local_receive_timeout, 0);
			connect_done = true;
		}
		if (!send_done)
		{
			// set send to same as receive
			set_local_timeout(local_receive_timeout, 1);
			send_done = true;
		}
	}
	else if (connect_done)
	{
		// if either send or connect set, then connect_done is true,
		// so set receive
		if (local_send_timeout != 0)
		{
			// set receive same as send
			set_local_timeout(local_send_timeout, 2);
			recv_done = true;
		}
		else
		{
			// set receive same as connect
			set_local_timeout(local_connect_timeout, 2);
			recv_done = true;
		}
	}
	// set flag to indicate there are timeouts
	m_use_timeouts = recv_done;

	if (gTrace)
	{
		if (!m_use_timeouts)
			cout << "ISO8583Connection not using timeouts" << endl;
		else
		{
			cout << "ISO8583Connection timeouts" << endl;
			if (m_connect_tv.tv_sec == 0)
				cout << " Connect: " << m_connect_tv.tv_usec << " microseconds" << endl;
			else
				cout << " Connect: " << m_connect_tv.tv_sec << " seconds" << endl;
			if (m_send_tv.tv_sec == 0)
				cout << " Send: " << m_send_tv.tv_usec << " microseconds" << endl;
			else
				cout << " Send: " << m_send_tv.tv_sec << " seconds" << endl;
			if (m_receive_tv.tv_sec == 0)
				cout << " Receive: " << m_receive_tv.tv_usec << " microseconds" << endl;
			else
				cout << " Receive: " << m_receive_tv.tv_sec << " seconds" << endl;
		}
	}
}

int ISO8583Connection::connect_with_timeout(int m_Sock, const sockaddr* name, 
                                            int namelen, bool& timed_out, int& last_error)
{
	timed_out = false;
	last_error = 0;
	int rval = connect(m_Sock, name, namelen);
	if (rval < 0)
	{
#ifdef _WIN32
		int last_err = WSAGetLastError();
		if ((last_err == WSAEINPROGRESS) || (last_err == WSAEWOULDBLOCK))
#else
  	if ((errno == EINPROGRESS) || (errno == EWOULDBLOCK))
#endif
  	{
	  	fd_set socketset;

 		  FD_ZERO(&socketset);
			FD_SET((unsigned)m_Sock, &socketset);

			int result;
			if (m_local_connect_timeout == DEBUG_TIMEOUT_LEVEL) // debug to force connection timeout
				result = select(m_Sock+1, &socketset, 0, 0, &m_debug_timeout);
			else
				result = select(m_Sock+1, 0, &socketset, 0, &m_connect_tv);
			if (result < 0)
			{
#ifdef _WIN32
				last_error = WSAGetLastError();
#else
				last_error = errno;
#endif
				return rval;
			}
			else if (result == 0)
			{
				timed_out = true;
				return rval;
			}
			else
			{
				// check for errors on socket selected
				
				int opt;
#ifndef _WIN32
				unsigned
#endif
				int optbytes(sizeof(opt));
				
				if (getsockopt(m_Sock, SOL_SOCKET, SO_ERROR, (char *)&opt, &optbytes) < 0)
				{
#ifdef _WIN32
					last_error = WSAGetLastError();
#else
					last_error = errno;
#endif
					return rval;
				}
				
				if (opt)
				{
					last_error = opt;
					return rval;
				}
			}
			// As socket ready to send, the connection is complete
			return 0;
		}
		else
		{
#ifdef _WIN32
			last_error = WSAGetLastError();
#else
			last_error = errno;
#endif
			return rval;
		}
	}
	return rval;
}

int ISO8583Connection::send_with_timeout(int m_Sock, const char* buf, int len, int flags, bool& timed_out, int& last_error)
{
	timed_out = false;
	last_error = 0;

 	fd_set socketset;

  FD_ZERO(&socketset);
	FD_SET((unsigned)m_Sock, &socketset);

	int result;
	if (m_local_send_timeout == DEBUG_TIMEOUT_LEVEL) // debug to force send timeout
		result = select(m_Sock+1, &socketset, 0, 0, &m_debug_timeout);
	else
		result = select(m_Sock+1, 0, &socketset, 0, &m_send_tv);
	if (result < 0)
	{
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
		return result;
	}
	else if (result == 0)
	{
		timed_out = true;
		return -1;
	}
	else
	{
		// check for errors on socket selected
		
		int opt;
#ifndef _WIN32
		unsigned
#endif
		int optbytes(sizeof(opt));
		
		if (getsockopt(m_Sock, SOL_SOCKET, SO_ERROR, (char *)&opt, &optbytes) < 0)
		{
#ifdef _WIN32
			last_error = WSAGetLastError();
#else
			last_error = errno;
#endif
			return -1;
		}
		
		if (opt)
		{
			last_error = opt;
			return -1;
		}
	}

	// To be really correct, we should loop around sending until count == len
	int count = send(m_Sock, buf, len, flags);

	if (gTrace)
		cout << "ISO8583Connection::send_with_timeout(). Sent " << count << " of " << len << " bytes." << endl;

	return count;
}

int ISO8583Connection::recv_with_timeout(int m_Sock, char* buf, int len, int flags, bool& timed_out, int& last_error)
{
	timed_out = false;
	last_error = 0;

 	fd_set socketset;

  FD_ZERO(&socketset);
	FD_SET((unsigned)m_Sock, &socketset);

	int result = select(m_Sock+1, &socketset, 0, 0, &m_receive_tv);
	if (result < 0)
	{
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
		return result;
	}
	else if (result == 0)
	{
		timed_out = true;
		return -1;
	}
	else
	{
		// check for errors on socket selected
		
		int opt;
#ifndef _WIN32
		unsigned
#endif
		int optbytes(sizeof(opt));
		
		if (getsockopt(m_Sock, SOL_SOCKET, SO_ERROR, (char *)&opt, &optbytes) < 0)
		{
#ifdef _WIN32
			last_error = WSAGetLastError();
#else
			last_error = errno;
#endif
			return -1;
		}
		
		if (opt)
		{
			last_error = opt;
			return -1;
		}
	}

	int count = recv(m_Sock, buf, len, flags);

	if (gTrace)
		cout << "ISO8583Connection::recv_with_timeout(). Received " << count << " bytes." << endl;

	return count;
}

bool ISO8583Connection::open(const char *strDnsName,
							  const char *strIpAddr,
							  const char *strPort,
							  const int iMode,
							  ISOStatus& statusRef, 
                int local_connect_timeout,
                int local_send_timeout,
                int local_receive_timeout)
{
	int rval = 0;
	char txt[255+1] = "";
	// server socket details
	struct linger soLinger;                // to make the socket flush data on close
	struct hostent *hp = (0);
	struct servent *serverEntry = NULL;    // to get port number from /etc/services

	set_local_timeouts(local_connect_timeout, local_send_timeout, local_receive_timeout);

	 // initialize the status object.
	 statusRef.update (false, 0, "");

	if (((strDnsName == NULL) || (strcmp (strDnsName, "") == 0))
	 && (( strIpAddr == NULL) || (strcmp ( strIpAddr, "") == 0)))
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: must specify dnsName or ipAddr.");

		m_msgMgr->logMsg (101);

		 return false;
	}

	if ((strPort == NULL)
	 || (strcmp (strPort, "") == 0))
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: must specify port.");

		m_msgMgr->logMsg (101);

		 return false;
	}

	if ((iMode != API_SENDER)
	  && (iMode != API_RECEIVER))
	{
		 statusRef.update (false, AMEX_NO_LOCAL_HOST_INFO, "error: this release only supports mode API_SENDER (0) or API_RECEIVER (1).");

		m_msgMgr->logMsg (101);

		 return false;
	}
	 else
	 {
		 // set this instances mode.
		 setMode (iMode);
	 }

	if (isConnected () == true)
	{
		 statusRef.update (true, AMEX_OK, "error: already connected.");

		m_msgMgr->logMsg (101);

		return true;
	}
	 else
	 {
		setConnected (false);
	 }

	// get server details - get host name
	memset ((char *)&(m_daemonAddr), 0, sizeof (m_daemonAddr));

	(m_daemonAddr).sin_family = AF_INET;

	if ((strIpAddr != NULL)
	 && (strcmp (strIpAddr, "") != 0))
	{
		 (m_daemonAddr).sin_addr.s_addr = inet_addr (strIpAddr);
	}
	 else if ((strDnsName != NULL)
			&& (strcmp (strDnsName, "") != 0))
	{
		 hp = (struct hostent *)gethostbyname (strDnsName);

		if (hp)
			 memcpy ((void *)&((m_daemonAddr).sin_addr), (void *)hp->h_addr, hp->h_length);
	}
	 else
	{
		 statusRef.update (false, AMEX_NO_LOCAL_HOST_INFO, "error: must specify commdaemon dnsName or ipAddr, no local host info.");

		m_msgMgr->logMsg (102);

		 return false;
	}

	// get listen port number
	serverEntry = NULL;

	if ((strPort != NULL)
	 && (strcmp (strPort, "") != 0))
	{
		 (m_daemonAddr).sin_port = htons ((unsigned short)atoi (strPort));
	}
	 else if (serverEntry = getservbyname ("ccauthsrv", NULL))
	{
		if (serverEntry)
			 (m_daemonAddr).sin_port = serverEntry->s_port;
	}
	 else
	{
		 statusRef.update (false, AMEX_NO_LOCAL_HOST_INFO, "error: must specify commdaemon port, no local port info.");

		m_msgMgr->logMsg (103);

		 return false;
	}

	// create a Internet stream (TCP/IP) socket.
	m_iSd = socket (AF_INET, SOCK_STREAM, 0);

	int last_error(0);
	if (m_iSd <= 0)
	{
#ifdef _WIN32
		last_error = WSAGetLastError();
		const DWORD sz = 100+1;
		char buffer[sz];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, last_error, 0, buffer, sz, 0);
		sprintf (txt, "error: socket() returned error %d. %s.", m_iSd, buffer);
#else
		last_error = errno;
		sprintf (txt, "error: socket() returned error %d. %s.", m_iSd,
					strerror(errno));
#endif

		statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (104, last_error);

		 return false;
	}
	else
	{
		m_msgMgr->logMsg (AMEX_API_FYI_SOCKET, getpid(), m_iSd);
	}

	// make it flush on close
	soLinger.l_onoff  = 1 ;     // option is on
	soLinger.l_linger = 0;

	rval = setsockopt (m_iSd,
							SOL_SOCKET,
						SO_LINGER,
						(char *)&soLinger,
						sizeof(soLinger));

	if (rval < 0)
	{
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
		sprintf (txt, "error: setsockopt() returned error %d.", last_error);
		statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (105, last_error);

		return false;
	}

	last_error = 0;
	if (m_use_timeouts)
	{
		set_non_blocking(m_iSd);
		bool timed_out(false);
		rval = connect_with_timeout(m_iSd, (struct sockaddr *)&(m_daemonAddr), sizeof(m_daemonAddr), timed_out, last_error);
		if (timed_out)
		{
			setConnected (false);

			sprintf (txt, "error: connect() timed out connecting to commdaemon");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (106, 0);

			return false;
		}
	}
	else
	{
		// Attempt to establish a network connection to the commdaemon.
		rval = connect (m_iSd,
						(struct sockaddr *)&(m_daemonAddr),
					sizeof (m_daemonAddr));
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	if (rval < 0)
	{
		setConnected (false);

		sprintf (txt, "error: connect() returned error %d.", last_error);
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (106, last_error);

		return false;
	}
	else
	{
		setConnected (true);

		if ((strDnsName != NULL)
		&& (strcmp (strDnsName, "") != 0))
		{
			sprintf (txt, "info: connected to commdaemon, dns: %s port: %s...",
			  strDnsName, strPort);
		}
		else
		{
			sprintf (txt, "info: connected to commdaemon, ip: %s port: %s...",
			  strIpAddr, strPort);
		}

		 statusRef.update (true, AMEX_OK, txt);

		 m_msgMgr->logMsg (107, strDnsName ? strDnsName : "(no DNS)", strIpAddr ? strIpAddr : "(no IP)", strPort ? strPort : "(no port)");
	}

	return true;
}

void ISO8583Connection::close (void)
{
	if (isConnected () == true)
	{
		// Mark as no longer connected.
		m_bConnected = false;

		// Gracefully shutdown and close the socket.
		shutdown (m_iSd, 2);

#ifdef _WIN32
		closesocket (m_iSd);
#else
		::close (m_iSd);
#endif
		m_iSd = -1;

		m_msgMgr->logMsg (124);
	}

	return;
}

ISO8583Message *ISO8583Connection::processMessage (ISO8583Message *requestMsg,
													 int iTimeout,
													  ISOStatus& statusRef)
{
	bool status = false;
	int iBitmapSize = 0;
	size_t requestLen = 0;
	char txt[255+1] = "";
	char strMsgType[64+1] = "";
	ISO8583Message *responseMsg = NULL;

	 // initialize the status object.
	 statusRef.update (false, 0, "");

	if (requestMsg == NULL)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: request message can't be NULL.");

		m_msgMgr->logMsg (108);

		return NULL;
	}

	if (getMode () != API_SENDER)
	{
		 statusRef.update (false, AMEX_API_NOT_SENDER, "error: not in API_SENDER mode.");

		m_msgMgr->logMsg (AMEX_API_NOT_SENDER);

		return NULL;
	 }

	if (isConnected () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not connected to commdaemon.");

		m_msgMgr->logMsg (109);

		return NULL;
	}

	// Serialize the message here and send across the connection
	// with the intra-daemon header information added on.

	status = sendMsg (requestMsg,
							 iTimeout,
							 statusRef);

	 if (status == false)
	{
		 statusRef.setResultCode (AMEX_COMM_LOCAL_FAIL);
		sprintf (txt,
			"error: sendMsg() returned %s.",
			statusRef.getResultDesc());

		m_msgMgr->logMsg (110, statusRef.getResultDesc());

		statusRef.setResultDesc (txt);

		return NULL;
	}

	// Get the bitmapsize.
	iBitmapSize = requestMsg->getMapSize (),

	// Get the response message type ("alter-ego").
	strcpy (strMsgType, requestMsg->getResponseType ());

	// Block in recv to read the response, msgType is IN/OUT.
	responseMsg = receiveMsg (strMsgType,
										iBitmapSize,
										 statusRef);

	 if (statusRef.getStatus () == false)
	{
		sprintf (txt,
			  "error: receiveMsg() returned %d: %s.",
			  statusRef.getResultCode (),
			 statusRef.getResultDesc());

		m_msgMgr->logMsg (125, statusRef.getResultDesc());

		statusRef.setResultDesc (txt);
	}

	return responseMsg;
}

bool ISO8583Connection::addMsgMapping (char *strMsgType, char *strClassName, ISOStatus& statusRef)
{
	 // initialize the status object.
	 statusRef.update (false, 0, "");

	if (((strMsgType == NULL) || (strcmp (strMsgType, "") == 0))
	 && ((strClassName == NULL) || (strcmp (strClassName, "") == 0)))
	{
		 if ((strMsgType == NULL) || (strcmp (strMsgType, "") == 0))
			 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: must specify strMsgType.");
		 else
			 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: must specify strClassName.");

		m_msgMgr->logMsg (101);

		 return false;
	}

	if (getMode () != API_RECEIVER)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not in API_RECEIVER mode.");

		m_msgMgr->logMsg (109);

		return false;
	 }

	 if (m_msgHandler == NULL)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: msg handler not set.");

		m_msgMgr->logMsg (109);

		return false;
	 }

	if (m_msgHandler->msgMapAdd (strMsgType, strClassName))
	{
		 statusRef.update (true, 0, "message mapping successfully added.");
		return true;
	 }
	else
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: message mapping not added.");
	}

	 return false;
}

ISO8583Message *ISO8583Connection::awaitRequest (char *strMsgType, ISOStatus & statusRef)
{
	char txt[255+1] = "";
	 size_t msgDataLen = 0;
	 unsigned char *msgData = NULL;
	 ISO8583Message *requestMsg = NULL;

	 // initialize the status object.
	 statusRef.update (false, 0, "");

	 if (strMsgType == NULL)
	 {
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: strMsgType can't be NULL.");

		m_msgMgr->logMsg (109);

		 return NULL;
	 }

	if (getMode () != API_RECEIVER)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not in API_RECEIVER mode.");

		m_msgMgr->logMsg (109);

		return NULL;
	 }

	if (isConnected () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not connected to commdaemon.");

		m_msgMgr->logMsg (109);

		return NULL;
	}

	 // Here we need to do only a GCP binary receive from the
	 // commdaemon.

	 // receive an ISO8583 message BLOB and message type.
	msgData = receiveBin (strMsgType,
								  &msgDataLen,
								  statusRef);

	if (statusRef.getStatus () == false)
	{
		sprintf (txt,
			  "error: receiveBin() returned %d: %s.",
			  statusRef.getResultCode (),
			 statusRef.getResultDesc());

		m_msgMgr->logMsg (125, statusRef.getResultDesc());

		statusRef.setResultDesc (txt);

		 delete [] msgData;
		 msgData = NULL;

		 return NULL;
	}

	 if (m_msgHandler == NULL)
	 {
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: msgHandler can't be NULL.");

		m_msgMgr->logMsg (109);

		 delete [] msgData;
		 msgData = NULL;

		 return NULL;
	 }

	 //
	 // lookup a message by ISO msg type, map to class
	 // and return ISOM8583Message instance.
	 requestMsg = m_msgHandler->vendMsg (strMsgType, statusRef);

	 if (requestMsg == NULL)
	 {
		 sprintf (txt, "error: msgHandler can't map %s.", strMsgType);

		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (109);

		 delete [] msgData;
		 msgData = NULL;

		 return NULL;
	 }

	 printf ("MSG TYPE: %s = REQUEST TYPE: %s RESPONSE TYPE: %s.\n",
		 strMsgType,
		 requestMsg->getRequestType (),
		 requestMsg->getResponseType ());

	 if (strcmp (requestMsg->getRequestType (), "ISORequest") == 0)
	 {
		 printf ("<ISORequest msgType=\"%s\">\n",
			  requestMsg->getMessageType ());
	 }

	 // load the ISO fields in the message from the buffer.
	 requestMsg->deSerialize (msgData, msgDataLen, statusRef);

	 if (statusRef.getStatus () == false)
	 {
		sprintf (txt,
			"error: receiveBin() returned %d: %s.",
			statusRef.getResultCode (),
				 statusRef.getResultDesc());

		m_msgMgr->logMsg (125, statusRef.getResultDesc());

		statusRef.setResultDesc (txt);
	 }
	 else
	 {
		 statusRef.update (true, 0, "info: received request message.");
		 m_msgMgr->logMsg (122, msgDataLen);
	 }

	 if (msgData != NULL)
	 {
		 delete [] msgData;
		 msgData = NULL;
	 }

	 return requestMsg;
}

bool ISO8583Connection::sendResponse (ISO8583Message *responseMsg, ISOStatus & statusRef)
{
	 bool bStatus = false;

	 // initialize the status object.
	 statusRef.update (false, 0, "");

	if (responseMsg == NULL)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: response message can't be NULL.");

		m_msgMgr->logMsg (108);

		return false;
	}

	if (getMode () != API_RECEIVER)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not in API_RECEIVER mode.");

		m_msgMgr->logMsg (109);

		return false;
	 }

	if (isConnected () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not connected to commdaemon.");

		m_msgMgr->logMsg (109);

		return false;
	}

	 bStatus = sendBin (responseMsg, statusRef);

	 return bStatus;
}

bool ISO8583Connection::sendMsg (ISO8583Message *message,
								  const int iTimeout,
								  ISOStatus& statusRef)
{
	// iso request message details
	unsigned char *stan = NULL;
	int encoding = 1; // ASCII
	size_t msgLen = 0;
	unsigned char *msg = NULL;
	size_t count = 0;                /* no. of bytes sent */
	char length[4] = "";
	char txt[255+1] = "";
	int msgDataLen = 0;
	unsigned char *msgDataPtr = NULL;

	 // initialize the status object.
	 statusRef.update (false, 0, "");

	 //
	// Sending ISO request to Daemon:
	// ------------------------------------------------------------------------
	//
	// ---------------------------A S C I I------------------------
	 //  | 3 bytes Len | 4 bytes Time out | 6 bytes System Trace No | Msg........
	//
	//  Note that the header data is in ASCII not EBCDIC.
	//
	//  Len doesn't include size of len field.
	//
	// ------------------------------------------------------------------------
	 //
	 if (message == NULL)
	 {
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: message can't be NULL.");

		m_msgMgr->logMsg (109);

		return false;
	 }

	if (getMode () != API_SENDER)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not in API_SENDER mode.");

		m_msgMgr->logMsg (109);

		return false;
	 }

	if (isConnected () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not connected to commdaemon.");

		m_msgMgr->logMsg (109);

		return false;
	}

	// Get a pointer to the serialized message
	msgDataPtr = message->serialize (&msgDataLen, statusRef);

	if (statusRef.getStatus () == false)
	{
		 statusRef.setResultCode (AMEX_COMM_LOCAL_FAIL);
		sprintf (txt, "error: serialize() returned %s.",
			statusRef.getResultDesc ());

		m_msgMgr->logMsg (111, statusRef.getResultDesc ());

		statusRef.setResultDesc (txt);

		return false;
	}

	// Compute the total length (TIMEOUT+MSGID+MESSAGE).
	size_t size = ISO_TMOUT_SZ+AMEX_MSGID_LEN+msgDataLen;

	// Allocate the mssage buffer
	msg = new unsigned char [size+1];

	if (msg == NULL)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: new returned error allocating memory.");

		m_msgMgr->logMsg (112);

		return false;
	}

	// Clear out the newly allocated buffer.
	memset (msg, 0, size + 1);

	// Build the transmit bytestream:
	// timeout 4 bytes
	msgLen = 0;
	sprintf ((char *)&msg[msgLen],
			  "%0*d",
			  ISO_TMOUT_SZ,
			  iTimeout);                          /* time out */
	 msgLen += ISO_TMOUT_SZ;

	// Get the system trace number.
	// 6 bytes
	int fieldLen = 0;
	stan = message->getField (11,
							  encoding,
							  &fieldLen,
							  statusRef);

	if (statusRef.getStatus () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: system trace number (BP11) is required.");

		m_msgMgr->logMsg (112);

		return false;
	}

	sprintf ((char *)&msg[msgLen],
			  "%*s",
			  AMEX_MSGID_LEN,
			  stan); /* unique id */
	 msgLen += AMEX_MSGID_LEN;

	delete [] stan;
	stan = NULL;

	// Copy the serialized message
	memcpy ((unsigned char *)&msg[msgLen], msgDataPtr, msgDataLen);
	msgLen += msgDataLen;

	// NUL terminate the buffer.
	msg[msgLen] = 0;

	if (gTrace)
	{
		cout << "ISO8583Connection::sendMsg()." << endl;

		// print the serialized bytestream in HEX.
		hex_dump (msg, msgLen);
	}

	// length 3 bytes
	// create message to send - prefix the message with its 3 byte length
	sprintf (length,
			  "%0*d",
			  ISO_MSGLEN_SZ,
			  size);

	// send the message length to the commdaemon.
	int last_error(0);
	if (m_use_timeouts)
	{
		bool timed_out(false);
		count = send_with_timeout(m_iSd, (char *)length, ISO_MSGLEN_SZ, 0, timed_out, last_error);
		if (timed_out)
		{
			if (msg != NULL)
			{
				delete [] msg;
				msg = NULL;
			}

			sprintf (txt, "error: send() timed out sending data length bytes to commdaemon.");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (113, 0);

			return false;
		}
	}
	else
	{
		count = send (m_iSd, (char *)length, ISO_MSGLEN_SZ, 0);
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	if (count != ISO_MSGLEN_SZ)
	 {
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		sprintf (txt, "error: send() returned error %d sending data length bytes.", last_error);
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (113, last_error);

		 return false;
	 }

	// send the complete message to the commdaemon.
	last_error = 0;
	if (m_use_timeouts)
	{
		bool timed_out(false);
		count = send_with_timeout(m_iSd, (char *)msg, msgLen, 0, timed_out, last_error);
		if (timed_out)
		{
			if (msg != NULL)
			{
				delete [] msg;
				msg = NULL;
			}

			sprintf (txt, "error: send() timed out sending data bytes to commdaemon.");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (114, 0);

			return false;
		}
	}
	else
	{
		count = send (m_iSd, (char *)msg, msgLen, 0);
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	if (count != msgLen)
	 {
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		sprintf (txt, "error: send() returned error %d sending data bytes.", last_error);
		statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (114, last_error);

		 return false;
	 }

	sprintf (txt, "info: send() returned %d data bytes sent.", count);
	statusRef.update (true, AMEX_OK, txt);

	m_msgMgr->logMsg (115, msgLen);

	if (msg != NULL)
	{
		delete [] msg;
		msg = NULL;
	}

	if (msgDataPtr != NULL)
	{
		delete [] msgDataPtr;
		msgDataPtr = NULL;
	}

	return true;
}

bool ISO8583Connection::sendBin (ISO8583Message *message, ISOStatus& statusRef)
{
	// iso request message details
	unsigned char *stan = NULL;
	int encoding = 1; // ASCII
	size_t msgLen = 0;
	unsigned char *msg = NULL;
	size_t count = 0;                /* no. of bytes sent */
	char length[4] = "";
	char txt[255+1] = "";
	int msgDataLen = 0;
	unsigned char *msgDataPtr = NULL;

	/* message sent to AMEX is len(msg)+msg */

	union {
		unsigned short sizeShort ;
		unsigned char  sizeChar[2] ;
	} sizeUnion ;                         /* to take care of byte ordering */

	 // initialize the status object.
	 statusRef.update (false, 0, "");

	 //
	// Sending ISO request to Daemon:
	// ------------------------------------------------------------------------
	//
	 //  | 2 bytes Binary Len | Msg........
	//
	//  Note that the header data is in binary.
	//
	// ------------------------------------------------------------------------
	 //
	 if (message == NULL)
	 {
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: message can't be NULL.");

		m_msgMgr->logMsg (109);

		return false;
	 }

	if (getMode () != API_RECEIVER)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not in API_RECEIVER mode.");

		m_msgMgr->logMsg (109);

		return false;
	 }

	if (isConnected () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not connected to commdaemon.");

		m_msgMgr->logMsg (109);

		return false;
	}

	// Get a pointer to the serialized message
	msgDataPtr = message->serialize (&msgDataLen, statusRef);

	if (statusRef.getStatus () == false)
	{
		 statusRef.setResultCode (AMEX_COMM_LOCAL_FAIL);
		sprintf (txt, "error: serialize() returned %s.",
			statusRef.getResultDesc ());

		m_msgMgr->logMsg (111, statusRef.getResultDesc ());

		statusRef.setResultDesc (txt);

		return false;
	}

	/* create message header */
	/* this is a 2 byte representation of an integer - requestLen - with the
		MSB first; size is that of the entire message, not just the data */
	size_t size = sizeUnion.sizeShort = (msgDataLen + 2);

	// Allocate the message buffer
	msg = new unsigned char [size + 1];

	if (msg == NULL)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: new returned error allocating memory.");

		m_msgMgr->logMsg (112);

		return false;
	}

	// Clear out the newly allocated buffer.
	memset (msg, 0, size + 1);

	// Get the system trace number.
	// 6 bytes
	int fieldLen = 0;
	stan = message->getField (11,
							  encoding,
							  &fieldLen,
							  statusRef);

	if (statusRef.getStatus () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: system trace number (BP11) is required.");

		m_msgMgr->logMsg (112);

		return false;
	}
	 else
	 {
		delete [] stan;
		stan = NULL;
	 }

	// Build the transmit bytestream:
	msgLen = 0;

	// 2 Length bytes
	 if (m_iByteOrder == 1) /* big endian */
	{
		msg[0] = sizeUnion.sizeChar[0] ;
		msg[1] = sizeUnion.sizeChar[1] ;
		msgLen += 2;
	}
	else  /* little endian */
	{
		msg[0] = sizeUnion.sizeChar[1] ;
		msg[1] = sizeUnion.sizeChar[0] ;
		msgLen += 2;
	}

	// Now copy the serialized message
	memcpy ((unsigned char *)&msg[msgLen], msgDataPtr, msgDataLen);
	msgLen += msgDataLen;

	// NUL terminate the buffer.
	msg[msgLen] = 0;

	if (gTrace)
	{
		cout << "ISO8583Connection::sendBin()." << endl;

		// print the serialized bytestream in HEX.
		hex_dump (msg, msgLen);
	}

	// send the message length to the commdaemon.
	int last_error(0);
	if (m_use_timeouts)
	{
		bool timed_out(false);
		count = send_with_timeout(m_iSd, (char *)&msg[0], 2, 0, timed_out, last_error);
		if (timed_out)
		{
			if (msg != NULL)
			{
				delete [] msg;
				msg = NULL;
			}

			sprintf (txt, "error: send() timed out sending data length bytes to commdaemon.");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (113, 0);

			return false;
		}
	}
	else
	{
		count = send (m_iSd, (char *)&msg[0], 2, 0);
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	if (count != 2)
	{
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		sprintf (txt, "error: send() returned error %d sending data length bytes.", last_error);
		statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (113, last_error);

		return false;
	}

	// send the complete message to the commdaemon.
	last_error = 0;
	if (m_use_timeouts)
	{
		bool timed_out(false);
		count = send_with_timeout(m_iSd, (char *)&msg[2], (msgLen-2), 0, timed_out, last_error);
		if (timed_out)
		{
			if (msg != NULL)
			{
				delete [] msg;
				msg = NULL;
			}

			sprintf (txt, "error: send() timed out sending data bytes to commdaemon.");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (114, 0);

			return false;
		}
	}
	else
	{
		count = send (m_iSd, (char *)&msg[2], (msgLen-2), 0);
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	if (count != (msgLen - 2))
	 {
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		sprintf (txt, "error: send() returned error %d sending data bytes.", last_error);
		statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (114, last_error);

		 return false;
	 }

	sprintf (txt, "info: send() returned %d data bytes sent.", count);
	statusRef.update (true, AMEX_OK, txt);

	m_msgMgr->logMsg (115, msgLen);

	if (msg != NULL)
	{
		delete [] msg;
		msg = NULL;
	}

	return true;
}

ISO8583Message *ISO8583Connection::receiveMsg (char *strMsgType,
												 int iBitmapSize,
												 ISOStatus& statusRef)
{
	// iso response message details
	size_t count = 0;                         // no. of bytes received
	size_t msgLen = 0;                        // len of actual msg
	unsigned char *msg = NULL;                // string to return, iso data
	char length[ISO_MSGLEN_SZ + 1] = "";
	char responseCodeStr[ISO_RC_SZ + 1] = "";
	int responseCode = 0;
	char txt[255+1] = "";
	ISO8583Message *message = NULL;

	 // initialize the status object.
	 statusRef.update (false, 0, "");

	//
	//  Receiving response from Daemon:
	// ------------------------------------------------------------------------
	 //
	 //  --------------A S C I I--------------
	 //  | 3 bytes Len | 2 bytes Return Code |  Msg................
	 //                    Code 10 = OK
	//
	 //  --------------A S C I I--------------
	 //  | 3 bytes Len | 2 bytes Return Code |
	 //                  Code 14 = Time Out
	 //                       19 = Comm Error with Amex
	 //
	 //  Len doesn't include size of len field.
	// ------------------------------------------------------------------------
	//

	if (getMode () != API_SENDER)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not in API_SENDER mode.");

		m_msgMgr->logMsg (109);

		return NULL;
	 }

	if (isConnected () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not connected to commdaemon.");

		m_msgMgr->logMsg (109);

		return NULL;
	}

	// receive iso message from DCP/CAS via the SSLGateway and commdaemon.
	// msg message received = 3 length, 2 status + iso_data
	int last_error(0);
	if (m_use_timeouts)
	{
		bool timed_out(false);
		count = recv_with_timeout(m_iSd, length, ISO_MSGLEN_SZ, 0, timed_out, last_error);
		if (timed_out)
		{
			sprintf (txt, "error: recv() timed out reading message length bytes from commdaemon.");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (116, last_error);

			return NULL;
		}
	}
	else
	{
		count = recv (m_iSd, length, ISO_MSGLEN_SZ, 0);
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	// NUL terminate
	length[ISO_MSGLEN_SZ] = 0;

	 if (count != ISO_MSGLEN_SZ)
	{
		sprintf (txt, "error: recv() returned error %d reading message length bytes.", last_error);
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (116, last_error);

		 return NULL;
	}

	// get the length of the actual message
	 msgLen = atoi (length);

	if ((msgLen < 1)
	 || (msgLen > 999))
	{
		sprintf (txt, "error: invalid message length %d received.", msgLen);
		statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (117, msgLen);

		return NULL;
	}

	// create a buffer to hold the received iso response message
	msg = new unsigned char [msgLen + 1];

	if (msg == NULL)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: new failed to allocate memory.");

		m_msgMgr->logMsg (112);

		return NULL;
	}

	// clear out the buffer
	memset (msg, 0, msgLen + 1);

	// read the actual message
	last_error = 0;
	if (m_use_timeouts)
	{
		bool timed_out(false);
		count = recv_with_timeout(m_iSd, (char *)msg, msgLen, 0, timed_out, last_error);
		if (timed_out)
		{
			if (msg != NULL)
			{
				delete [] msg;
				msg = NULL;
			}

			sprintf (txt, "error: recv() timed out reading message length bytes from commdaemon.");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (118, last_error);

			return NULL;
		}
	}
	else
	{
		count = recv (m_iSd, (char *)msg, msgLen, 0);
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	if (count != msgLen)
	{
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		sprintf (txt, "error: recv() returned error %d reading message data bytes.", last_error);
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (118, last_error);

		 return NULL;
	}

	// NUL terminate message
	msg[msgLen] = 0;

	if (gTrace)
	{
		cout << "ISO8583Connection::receiveMsg()." << endl;

		// for debugging dump out in hex
		hex_dump (msg, msgLen);
	}

	// extract auth server's status code;
	// message is valid only if status OK
	memcpy (responseCodeStr, (char *)msg, ISO_RC_SZ);

	// NUL terminate
	responseCodeStr[ISO_RC_SZ] = 0;

	// Convert the string to an integer
	responseCode = atoi (responseCodeStr);

	// Set the received status code from the commdaemon.
	statusRef.setResultCode (responseCode);

	if (gTrace)
		cout << "ISO8583Connection::receiveMsg() - responseCode: " << responseCode << "." << endl;

	if (responseCode == AMEX_TMOUT) // TIMEOUT
	{
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		 statusRef.update (false, AMEX_TMOUT, "error: commdaemon returned request timed out.");

		m_msgMgr->logMsg (119);

		return NULL;
	}
        else if(responseCode == AMEX_COMM_AMEX_BUSY)
        {
              if (msg != NULL)
              {
		delete [] msg;
		msg = NULL;
	      }

              statusRef.update (false, AMEX_COMM_AMEX_BUSY, "error: commdaemon returned AMEX is Busy.");

	      m_msgMgr->logMsg (AMEX_API_ERROR_BUSY);

              return NULL;

        }         
	else if (responseCode == AMEX_COMM_DISCONNECT) /* connection closed by peer */
	{
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		 statusRef.update (false, AMEX_COMM_DISCONNECT, "error: commdaemon returned error connecting to SSL Gateway.");

		m_msgMgr->logMsg (120);

		return NULL;
	}
	else if (responseCode == AMEX_COMM_LOCAL_FAIL) // Comm Error with daemon
	{
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: error in communication with commdaemon.");

		m_msgMgr->logMsg (120);

		return NULL;
	}
	else if (responseCode == AMEX_COMM_AMEX_FAIL) // Comm Error with Amex
	{
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		 statusRef.update (false, AMEX_COMM_AMEX_FAIL, "error: commdaemon returned error connecting to SSL Gateway.");

		m_msgMgr->logMsg (120);

		return NULL;
	}
	else if (responseCode == AMEX_OK)
	{
		// Init the proper response message type via the class factory.
		message = ISO8583MessageFactory ().createMessage (strMsgType,
																			64,
																			statusRef);

		if (statusRef.getStatus () == false)
		{
			if (msg != NULL)
		  {
				delete [] msg;
				msg = NULL;
		  }

			sprintf (txt,
			  "error: class factory returned error instanciating response message, type: %s.",
				  strMsgType);

			 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		  m_msgMgr->logMsg (121, strMsgType);

			return NULL;
		}

		// msgType has "class name - ISO1100Authorization"
		// msg has "real" received type.
		// set the message type
		memcpy (strMsgType, &msg[ISO_RC_SZ], 4);
		strMsgType[4] = 0;

		// convert the message type to ASCII
		CharUtility::toAsciiStrInplace ((unsigned char *)strMsgType, 4);

		// Initialized instance reconstituted from bytestream buffer.
		int dataLen = (msgLen - ISO_RC_SZ);

		if (message->deSerialize (&msg[ISO_RC_SZ],
											dataLen,
											statusRef) == false)
		{
			if (msg != NULL)
		  {
				delete [] msg;
				msg = NULL;
		  }

		  if (message != NULL)
		  {
			  delete message;
			  message = NULL;
		  }

			sprintf (txt, "error: deSerialize returned %s.",
			  statusRef.getResultDesc ());

			m_msgMgr->logMsg (126, txt);

			return NULL;
		}

		 statusRef.update (true, responseCode, "info: received response message.");

		m_msgMgr->logMsg (122, msgLen);
	}
	else
	{
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		sprintf (txt,
			"error: commdaemon returned unknown response code %d.",
				responseCode);

		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (123, responseCode);

		return NULL;
	}

	if (msg != NULL)
	{
		delete msg;
		msg = NULL;
	}

	return message;
}

unsigned char *ISO8583Connection::receiveBin (char *strMsgType,
												size_t *msgLen,
												ISOStatus& statusRef)
{
	// iso response message details
	size_t count = 0;                         // no. of bytes received
	char length[2] = "";
	 unsigned char *msg = NULL;                // string to return, iso data
	 char txt[255+1] = "";
	 size_t msgSize = 0;                    /* len of actual msg */
	 size_t tmpMsgLen = 0;

	 /* msg */
	union {
		unsigned short sizeShort;
		unsigned char  sizeChar[2];
	} sizeUnion;                    /* to take care of byte ordering */

	 // initialize the status object.
	 statusRef.update (false, 0, "");

	 *msgLen = 0;

	//
	//  Receiving response from Daemon:
	// ------------------------------------------------------------------------
	 //
	 //  | 2 bytes binary len |  Msg................
	 //
	// ------------------------------------------------------------------------
	//

	if (getMode () != API_RECEIVER)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not in API_RECEIVER mode.");

		m_msgMgr->logMsg (109);

		return NULL;
	 }

	if (isConnected () == false)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: not connected to commdaemon.");

		m_msgMgr->logMsg (109);

		return NULL;
	}

	// receive iso message from DCP/CAS via the SSLGateway and commdaemon.
	// msg message received = 2 length + iso_data
	int last_error(0);
	if (m_use_timeouts)
	{
		bool timed_out(false);
		count = recv_with_timeout(m_iSd, length, 2, 0, timed_out, last_error);
		if (timed_out)
		{
			sprintf (txt, "error: recv() timed out reading message length bytes from commdaemon.");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (116, last_error);

			return NULL;
		}
	}
	else
	{
		count = recv (m_iSd, length, 2, 0);
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	if (count != 2)
	{
		sprintf (txt, "error: recv() returned error %d reading message length bytes.", last_error);
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (116, last_error);

		 return NULL;
	}

	/* get the length of the actual message */
	if (m_iByteOrder == 1)		/* big endian */
	{
		sizeUnion.sizeChar[0] = length[0];
		sizeUnion.sizeChar[1] = length[1];
	}
	else /* little endian */
	{
		sizeUnion.sizeChar[0] = length[1];
		sizeUnion.sizeChar[1] = length[0];
	}

	/* the size sent by AMEX is for the entire message, get the data size */
	msgSize = (sizeUnion.sizeShort - 2);

	// NUL terminate
	length[2] = 0;

	// get the length of the actual message
	 tmpMsgLen = msgSize;

	if ((tmpMsgLen < 1)
	 || (tmpMsgLen > 16834))
	{
		sprintf (txt, "error: invalid message length %d received.", tmpMsgLen);
		statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (117, tmpMsgLen);

		return NULL;
	}

	// create a buffer to hold the received iso response message
	msg = new unsigned char [tmpMsgLen + 1];

	if (msg == NULL)
	{
		 statusRef.update (false, AMEX_COMM_LOCAL_FAIL, "error: new failed to allocate memory.");

		m_msgMgr->logMsg (112);

		return NULL;
	}

	// clear out the buffer
	memset (msg, 0, tmpMsgLen + 1);

	// read the actual message
	last_error = 0;
	if (m_use_timeouts)
	{
		bool timed_out(false);
		count = recv_with_timeout(m_iSd, (char *)msg, tmpMsgLen, 0, timed_out, last_error);
		if (timed_out)
		{
			if (msg != NULL)
			{
				delete [] msg;
				msg = NULL;
			}

			sprintf (txt, "error: recv() timed out reading message data bytes from commdaemon.");
			statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

			m_msgMgr->logMsg (118, last_error);

			return NULL;
		}
	}
	else
	{
		count = recv (m_iSd, (char *)msg, tmpMsgLen, 0);
#ifdef _WIN32
		last_error = WSAGetLastError();
#else
		last_error = errno;
#endif
	}

	if (count != tmpMsgLen)
	{
		if (msg != NULL)
		{
			delete [] msg;
			msg = NULL;
		}

		sprintf (txt, "error: recv() returned error %d reading message data bytes.", last_error);
		statusRef.update (false, AMEX_COMM_LOCAL_FAIL, txt);

		m_msgMgr->logMsg (118, last_error);

		return NULL;
	}

	// NUL terminate message
	 msg[tmpMsgLen] = 0;

	 *msgLen = tmpMsgLen;

	if (gTrace)
	{
		cout << "ISO8583Connection::receiveBin()." << endl;

		// for debugging dump out in hex
		hex_dump (msg, tmpMsgLen);
	}

	// set the message type
	 if (strMsgType != NULL)
	 {
		 // first 4 bytes is ISO msg type
		memcpy (strMsgType, msg, 4);
		strMsgType[4] = 0;

		// convert the message type to ASCII
		CharUtility::toAsciiStrInplace ((unsigned char *)strMsgType, 4);
	 }

	 statusRef.update (true, 0, "info: received response message.");

	m_msgMgr->logMsg (122, tmpMsgLen);

	 return msg;
}

bool ISO8583Connection::isConnected (void)
{
	return m_bConnected;
}

void ISO8583Connection::setConnected (bool bConnected)
{
	m_bConnected = bConnected;

	return;
}

void ISO8583Connection::setMode (int iMode)
{
	 m_iMode = iMode;

	 return;
}

int ISO8583Connection::getMode (void)
{
	 return m_iMode;
}

/*
Desc     : Returns the byte ordering convention used on this machine
				0 : little endian
				1 : big endian
			  -1 : unknown
*/
int ISO8583Connection::getByteOrdering (void)
{
	union {
		unsigned short i;
		char           c[sizeof(unsigned short)];
	} u;

	u.i = 1;

	if (u.c[0] == 1)
		return 0;			/* little endian */
	else if (u.c[sizeof(unsigned short)-1] == 1)
		return 1;			/* big endian */
	else
		return -1;			/* unknown byte ordering convention */
}

