/*********************************************************************
*
*   Module:
*       isomessage.c
*
*   Contents:
*       Components common to all ISO messages.
*       
*   Description
*
*          See isomessage.h
*
*   See Also:
*          isomessage.h
*
*   Created:
*       08 Jun 2001 Arun G.
*
*   Modified:
*               
*     
**********************************************************************/

#include "ISOMessage.h"

/*
 * This array contains the descriptions of the status codes defined
 * in the IsoStatus enumeration.  This must be kept in sync with the
 * enumeration!!!
 */
char* errorStrings[__ISO_MESSAGE_STATUS_LAST] =
     { 0,
       "Valid object",
       "No more memory.",
       "Output buffer too small.",
       "No data for item.",
       "Invalid bit position.",
       "Invalid.",
       "Invalid account number (BP 2).",
       "Invalid processing code (BP 3).",
       "Invalid amount transaction (BP 4).",
       "Invalid amount reconciliation (BP 5).",
       "Invalid currency code transaction (BP 49).",
       "Invalid currency code reconciliation (BP 50).",
       "Invalid effective date (BP 13).",
       "Invalid expiration date (BP 14).",
       "Invalid merchant type (BP 18).",
       "Invalid country code (BP 19).",
       "Invalid POS data (BP 22).",
       "Invalid function code (BP 24).",
       "Invalid reason code (BP 25).",
       "Invalid card acceptor business code (BP 26).",
       "Invalid approval code length (BP 27).",
       "Invalid approval code (BP 38).",
       "Invalid acceptor terminal identifier (BP 41).",
       "Invalid card acceptor identifier code (BP 42).",
       "Invalid card acceptor location (BP 43).",
       "Invalid system trace information (BP 11).",
       "Invalid security information (BP 53).",
       "Invalid private1 data (BP 62).",
       "Invalid private2 data (BP 63).",
       "Invalid acquiring institution identifier (BP 32).",
       "Invalid forwarding institution identifier (BP 33).",
       "Invalid account number extended identifier (BP34).",
       "Invalid track one data (BP 45).",
       "Invalid track two data (BP 35).",
       "Invalid retrieval reference number (BP 37).",
       "Invalid additional data private (BP 48).",             /* UC01 */
       "Invalid original data elements (BP 56)."
       "Invalid action code (BP 38)."
       "Invalid circuit card (BP 55)."                         /* UC02 */
     };

