import java.io.*;

class ISOMessageAPI {
		
	static
	{ 
		System.out.println("loading SecureAuth JNI...");
		try {
			System.loadLibrary ("salib");           // Load the Shared Library
		}
		catch ( Exception e ) {
			System.out.println("caught exception");
			System.out.println( e.toString() );
			System.out.print( e.getMessage() );
			e.printStackTrace();
		} 
		System.out.println("SecureAuth JNI loaded...");
	}	
	
	/////////////////////////////////////////////////////
	// MISC API FUNCTIONS

	// enable/disable API debug mode
        public native static void ISO8583APISetDebug( int iDebug );
        
	// enable/disable API trace mode
        public native static void ISO8583APISetTrace( int iTrace );

	//////////////////////////////////////
	// MESSAGE FUNCTIONS

	//create a new message 
	// the message id is the return value
	// the message id is used for all other functions on messages below
	public native static int ISO8583MessageCreate( String strMsgType, int iBitmapSize, int iStatusId );

	//Set a field in a message
	public native static boolean ISO8583MessageSetField( int iMsgId, int iBitPosition, int iCharType, String strData, int iDataLen, int iStatusId );

	//Set a BINARY field in a message
	public native static boolean ISO8583MessageSetFieldBinary( int iMsgId, int iBitPosition, int iCharType, byte [] aData, int iDataLen, int iStatusId );

	//Get a field from a message
	public native static String ISO8583MessageGetField( int iMsgId, int iBitPosition, int iCharType, int iDataLen, int iStatusId  );

	//Get a field2 from a message
	public native static int ISO8583MessageGetField2( int iMsgId, int iBitPosition, int iCharType, String strData, int iDataLen, int iMaxDataLen, int iStatusId  );

	//Get a BINARY field from a message
	public native static byte [] ISO8583MessageGetFieldBinary( int iMsgId, int iBitPosition, int iCharType, int iDataLen, int iStatusId  );
	
	//Get the length of a field from a message
	public native static int ISO8583MessageGetFieldLength( int iMsgId, int iBitPosition, int iStatusId  );

	//get the type of a message
	public native static String ISO8583MessageGetMessageType( int iMsgId );

	//get the bitmap size from a message
	public native static int ISO8583MessageGetMapSize( int iMsgId );

	//perform validation on a message
	public native static boolean ISO8583MessageValidate( int iMsgId, int iStatusId  );

	//get the response message type for a message
	public native static String ISO8583MessageGetResponseType( int iMsgId );

	//encode the msg data fields into a bytestream (byte array).
    public native static byte [] ISO8583MessageSerialize ( int iMsgId, int iDataLen, int iStatusId );
        
    //decode the msg data fields from a bytestream (byte array).
    public native static boolean ISO8583MessageDeSerialize ( int iMsgId, byte [] aData, int iDataLen, int iStatusId );
        
	//destroy a message
	public native static void ISO8583MessageDestroy( int iMsgId );

	////////////////////////////////////////////////
	// CONNECTION FUNCTIONS

	//create a new connection (return the connection id, int iStatusId  )
	// the connection id is used in all other functions for 
	// connection objects below
	public native static int ISO8583ConnectionCreate();

	//destroy an existing connection
	public native static void ISO8583ConnectionDestroy( int iConnectionId );

	//open a connection
	public native static boolean ISO8583ConnectionOpen( int iConnectionId, String strDnsName, String strIpAddr, String strPort, int iMode, int iStatusId );

	//close a connection
	public native static void ISO8583ConnectionClose( int iConnectionId );

	//Process a message (API_SENDER mode only)
	public native static int ISO8583ConnectionProcessMessage( int iConnectionId, int iRequestMsgId, int iTimeout, int iStatusId );

	//Add a message map rule (API_RECEIVER mode only)
	public native static void ISO8583ConnectionAddMsgMapping( int iConnectionId, String strMsgType, String strMsgClassName, int iStatusId );

	//Await a request message (API_RECEIVER mode only)
	public native static int ISO8583ConnectionAwaitRequest( int iConnectionId, int iStatusId );

	//Send a response message (API_RECEIVER mode only)
	public native static boolean ISO8583ConnectionSendResponse( int iConnectionId, int iResponseMsgId, int iStatusId );

	//determine if a connection is connected (open)
	public native static boolean ISO8583ConnectionIsConnected( int iConnectionId );

	/////////////////////////////////////////////////////
	// ERROR STATUS FUNCTIONS

	//create a status object
	public native static int ISOStatusCreate();

	//get the current error status
	//the current error status
	public native static boolean ISOStatusGetStatus( int iStatusId );

	//get the current error result code
	public native static int ISOStatusGetResultCode( int iStatusId );

	//get the current error result description
	public native static String ISOStatusGetResultDesc( int iStatusId );

	//destroy an ISOStatus 
	public native static void ISOStatusDestroy( int iStatusId );
}