/*********************************************************************
*
*   Module:
*       FieldMapArrayData.cpp
*
*   Contents:
*       Global FieldMapElement data
*
*   Description
*
*       This header file contains the FieldMapElement data
*       initialization. This is used by both the ISO8583Implementation
*       class AND the tester applications.
*       This is why it is declared extern (global).
*
*   See Also:
*       Enumeriations.h
*		FieldMapElement.h
*
*   Created:
*		10 August 2001	Lonnie L. Filbrun
*
*   Modified:
*
*
**********************************************************************/

#include "Enumerations.h"
#include "FieldMapElement.h"
#include "FieldMapArrayData.h"

void InitFieldMapArray( FieldMapElement **retval )
{
	//Initializing Field Position - 1 internal
	retval[0] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, BINARY, 8);

	//Initializing Field Position - 2 (Primary Account Number)
	retval[1] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, NUMERIC, 19);

	//Initializing Field Position - 3 (Processing Code)
	retval[2] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 6);

	//Initializing Field Position - 4 (Transaction Amount)
	retval[3] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 12);

	//Initializing Field Position - 5 (Reconciliation Amount)
	retval[4] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 12);

	//Initializing Field Position - 6 (Cardholder Billing Amount)
	retval[5] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 12);

	//Initializing Field Position - 7 (Transmission Date and Time)
	retval[6] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, DATETIME, 10);

	//Initializing Field Position - 8 (Cardholder Billing Fee Amount)
	retval[7] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 8);

	//Initializing Field Position - 9 (Reconciliation Conversion Rate)
	retval[8] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 8);

	//Initializing Field Position - 10 (Cardholder Billing Conversion Rate)
	retval[9] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 8);

	//Initializing Field Position - 11 (Systems Trace Audit Number)
	retval[10] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 6);

	//Initializing Field Position - 12 (Local Transmission Date and Time)
	retval[11] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, DATETIME, 12);

	//Initializing Field Position - 13 (Card Effective Date)
	retval[12] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, DATETIME, 4);

	//Initializing Field Position - 14 (Card Expiration Date)
	retval[13] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, DATETIME, 4);

	//Initializing Field Position - 15 (Settlement Date)
	retval[14] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, DATETIME, 6);

	//Initializing Field Position - 16 (Conversion Date)
	retval[15] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, DATETIME, 4);

	//Initializing Field Position - 17 (Capture Date)
	retval[16] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, DATETIME, 4);

	//Initializing Field Position - 18 (Merchant Type)
	retval[17] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 4);

	//Initializing Field Position - 19 (Acquiring Institution Country Code)
	retval[18] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 20 (Primary Acct Number Country Code)
	retval[19] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 21 (Forwarding Institution Country Code)
	retval[20] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 22 (Point of Service Data)
	retval[21] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, ALPHANUMERIC, 12);

	//Initializing Field Position - 23 (Card sequence Number)
	retval[22] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 24 (Function Code)
	retval[23] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 25 (Message Reason Code)
	retval[24] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 4);

	//Initializing Field Position - 26 (Card Acceptior Business Code)
	retval[25] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 4);

	//Initializing Field Position - 27 (Approval Code Length)
	retval[26] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 1);

	//Initializing Field Position - 28 (Reconciliation Date)
	retval[27] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, DATETIME, 6);

	//Initializing Field Position - 29 (Reconciliation Indicator)
	retval[28] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 30 (Original Amounts)
	retval[29] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 24);

	//Initializing Field Position - 31 (Aquirer Reference Data)
	retval[30] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, ALPHANUMERICs, 99);

	//Initializing Field Position - 32 (Acquiring Institution Identification Code)
	retval[31] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, NUMERIC, 11);

	//Initializing Field Position - 33 (Forwarding Institution Identification Code)
	retval[32] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, NUMERIC, 11);

	//Initializing Field Position - 34 (Primary Account No Extended)
	retval[33] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, NUMERIC, 28);

	//Initializing Field Position - 35 (Track 2 Data)
	retval[34] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, ALPHANUMERICs, 37);

	//Initializing Field Position - 36 (Track 3 Data)
	retval[35] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, BINARY, 104);

	//Initializing Field Position - 37 (Retrieval Reference Number)
	retval[36] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, ALPHANUMERICp, 12);

	//Initializing Field Position - 38 (Approval Code)
	retval[37] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, ALPHANUMERICp, 6);

	//Initializing Field Position - 39 (Action Code)
	retval[38] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 40 (Service Code)
	retval[39] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 41 (Card Acceptor Terminal Identification)
	retval[40] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, ALPHANUMERICs, 8);

	//Initializing Field Position - 42 (Card Acceptor Identification Code)
	retval[41] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, ALPHANUMERICs, 15);

	//Initializing Field Position - 43 (Card Acceptor Name/Location)
	retval[42] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, ALPHANUMERICs, 99);

	//Initializing Field Position - 44 (Additional Reaponse Data)
	retval[43] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, ALPHANUMERICs, 99);

	//Initializing Field Position - 45 (Track 1 Data)
	retval[44] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, ALPHANUMERICs, 76);

	//Initializing Field Position - 46 (Amounts Fees)
	retval[45] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 204);

	//Initializing Field Position - 47 (Addtional data - National)
	retval[46] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 999);

	//Initializing Field Position - 48 (Addtional data - Private)
	retval[47] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 999);

	//Initializing Field Position - 49 (Transaction Currency Code)
	retval[48] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, ALPHANUMERIC, 3);

	//Initializing Field Position - 50 (Reconciliation Currency Code)
	retval[49] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, ALPHANUMERIC, 3);

	//Initializing Field Position - 51 (Cardholder Billing Currency Code)
	retval[50] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, ALPHANUMERIC, 3);

	//Initializing Field Position - 52 (Personal Identification Number - PIN)
	retval[51] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, BINARY, 8);

	//Initializing Field Position - 53 (Security Related Control Information)
	retval[52] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, BINARY, 48);

	//Initializing Field Position - 54 (Additional Amount)
	retval[53] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 120);

	//Initializing Field Position - 55 (IC card data)
	retval[54] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, BINARY, 255);

	//Initializing Field Position - 56 (Original Data)
	retval[55] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, NUMERIC, 35);

	//Initializing Field Position - 57 (Authorization Life Cycle Code)
	retval[56] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, NUMERIC, 3);

	//Initializing Field Position - 58 (Original Data)
	retval[57] =  new FieldMapElement( true, OPTIONAL, LLVARLENGTH, NUMERIC, 11);

	//Initializing Field Position - 59 (Transport Data)
	retval[58] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 999);

	//Initializing Field Position - 60 (National Use Data)
	retval[59] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 999);

	//Initializing Field Position - 61 (National Use Data)
	retval[60] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 999);

	//Initializing Field Position - 62 (Private Use Data)
	retval[61] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 999);

	//Initializing Field Position - 63 (Private Data)
	retval[62] =  new FieldMapElement( true, OPTIONAL, LLLVARLENGTH, ALPHANUMERICs, 999);

	//Initializing Field Position - 64 (Message Authentication Code)
	retval[63] =  new FieldMapElement( true, OPTIONAL, FIXEDLENGTH, BINARY, 8);

	return;
}
