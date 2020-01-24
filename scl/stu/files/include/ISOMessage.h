#if !defined(__ISO_MESSAGE_H)
#define __ISO_MESSAGE_H

/**************************************************************************
 * File Name :          ISOMessage.h
 *
 * Description :      Definitions common to all ISO messages.
 *
 * Author :           Arun G.
 *
 * Date Created :     07 June 2001
 *
 * Modified :
 *
 **************************************************************************
 */

#if defined(sun4)
#include <sys/param.h>
#include <memory.h>
#elif defined(sun)
#include <sys/types.h>
#include <sys/bitmap.h>
#else
#define _ALL_SOURCE
#define const
#ifndef _WIN32
#include <sys/param.h>
#endif

/* Commented by Arun G
#if !defined (sgi)
#include <memory.h>
#endif
*/
#include <sys/types.h>
#endif

/*
 * Define TRUE and FALSE if not already defined.
 */
#if !defined(TRUE)
#define TRUE 1
#endif
#if !defined(FALSE)
#define FALSE 0
#endif

/*
 * Define bit manipulation routines: set, clear, test.
 */


#if defined(sun)

#define IsoSetBit(bitMapPtr, bitPosition) BT_SET(((unsigned long*)bitMapPtr),  bitPosition)
#define IsoClearBit(bitMapPtr, bitPosition) BT_CLEAR(((unsigned long *)bitMapPtr), bitPosition)
#define IsoTestBit(bitMapPtr, bitPosition) BT_TEST(((unsigned long *)bitMapPtr), bitPosition)

#else

#define IsoSetBit(bitMapPtr, bitPosition) setbit(bitMapPtr, bitPosition)
#define IsoClearBit(bitMapPtr, bitPosition) clrbit(bitMapPtr, bitPosition)
#define IsoTestBit(bitMapPtr, bitPosition) (isset(bitMapPtr, bitPosition) != 0)

#endif /* defined(sun) */

#if defined(_WIN32) || defined (sgi)
#define NBBY        8      /* # of bits in a byte */
#define setbit(a,i) ((a)[(i)/NBBY] |= 1<<((i)%NBBY))
#define clrbit(a,i) ((a)[(i)/NBBY] &= ~(1<<((i)%NBBY)))
#define isset(a,i)  ((a)[(i)/NBBY] & (1<<((i)%NBBY)))
#define isclr(a,i)  (((a)[(i)/NBBY] & (1<<((i)%NBBY))) == 0)
#endif

/*
 * This enumeration defines the set of processing codes that are
 * used by the ISO messages.  They directly correspond to the
 * processing codes defined by ISO 8583.
 */

/* //Commented since the enumeration is included in the new version

typedef enum
{
     ZERO_PROC_CODE = 0,
     CC_AUTHENTICATION = 4000,
     CC_REVERSAL,
     CC_AUTHENTICATION_ADDRESS_VERIFICATION = 4800,
     AMEX_EMERGENCY_CHECK_CASHING = 34000,
     CHECK_GUARANTEE = 44000,
     AMEX_TRAVELERS_CHECK = 64000,
     AMEX_SIGHT_DRAFT = 104000,
     ADDRESS_VERIFICATION = 174800,
     GRMS_RELATIONSHIP_INQUIRY = 384900,                  UC02 /
     TELLER_CASH = 14000,
     __LAST_ITEM                    / Do not use /
} IsoProcCode;
*/

/*
 * This enumeration defines the set of character types that the ISO
 * messages can handle as input and output.
 */

/* //Commented since the enumeration is included in the new version
typedef enum
{
     ASCII,
     EBCDIC
} IsoCharacterType;
*/

typedef struct IsoCurrencyCode_t
{
     char *code;
     unsigned int decimalPoint;
} IsoCurrencyCode;

typedef enum
{
     AMEX_SE,
     AIRLINE_CODE,
     NCR_NUMBER,
     IATA_AGENT_ID
} IsoMerchantIDType;

typedef enum
{
     ISO_AMEX,
     ISO_VISA,
     ISO_MASTERCARD,
     ISO_CARD_OTHER
} IsoCardType;

/*
 * This type defines the information passed back as "additional response"
 * data (bit position 44).  Use the getAdditionalResponseData() method.
 */
typedef enum
{
     ADDRESS_AND_ZIP_CORRECT,
     ADDRESS_AND_ZIP_INCORRECT,
     ADDRESS_CORRECT,
     ZIP_CORRECT,
     INFORMATION_UNAVAIL,
     ADDRESS_VERIF_SUBSCR_VALID,
     SYSTEM_UNAVAIL
} IsoAddRespData;

/*
 * This type defines the action code for the authorization request (bit
 * position 39).  Use the getActionCode() method to access.
 */
typedef enum
{
     APPROVED                           = 0,
     APPROVE_WITH_ID                    = 1,
     APPROVE_VIP                        = 3,
     APPROVED_EXPRESS_REWARDS_PROGRAM   = 92,
     DENY                               = 100,
     EXPIRED_CARD                       = 101,
     DIGIT_MANUAL                       = 103,       /* UC02 */
     DENY_NEW_CARD_ISSUED               = 104,
     DENY_ACCOUNT_CANCELED              = 105,
     PLEASE_CALL_ISSUER                 = 107,
     INVALID_MERCHANT                   = 109,
     INVALID_AMOUNT                     = 110,
     INVALID_ACCOUNT                    = 111,
     SERVICE_NOT_PERMITTED              = 115,
     NO_RECORD_FOR_CARD                 = 118,       /* UC02 */
     INVALID_CID                        = 122,
     INVALID_EFFECTIVE_DATE             = 125,
     FORMAT_ERROR                       = 181,
     PLEASE_WAIT                        = 182,
     INVALID_CURRENCY_CODE              = 183,
     DENY_PICK_UP_CARD                  = 200,
     REVERSAL_ACCEPTED                  = 400,
     CARD_ISSUER_TIMEOUT                = 911,       /* UC03 */
     CARD_ISSUER_UNAVAILABLE            = 912,       /* UC02 */
     PPN_EXPIRED                        = 940,
     PPN_INVALID                        = 941,
     PPN_AUTH_LIMIT_EXCEEDED            = 942,
     PPN_AMOUNT_LIMIT_EXCEEDED          = 943,
     PPN_PPN_CANCELED                   = 944,
     PPN_INVALID_EXPIRATION_DATE        = 945,
     PPN_PLEASE_CALL_CHANGED_TO_DENY    = 946,
     PPN_TIMEOUT                        = 947
} IsoActionCode;

/*
 * This enumeration is a list of all of the status codes that the ISO
 * message can return.
 *
 * NOTE:
 *          It *must* be coordinated with the errorStrings array defined
 *          in isomessage.c.  If you change this enumeration, you must
 *          change the errorStrings array.
 */

/* included in the new version
#ifdef ENOMEM
#undef ENOMEM
#endif

typedef enum
{
     VALID = 1,
     ENOMEM,
     OUTPUT_BUFFER_TOO_SMALL,
     NODATA,
     INVALID_BIT_POSITION,
     INVALID,
     ISO_ACCOUNT_NO_INVALID,
     ISO_PROCESSING_CODE_INVALID,
     ISO_AMOUNT_TRANSACTION_INVALID,
     ISO_AMOUNT_RECONCILIATION_INVALID,
     ISO_CURRENCY_CODE_TRANSACTION_INVALID,
     ISO_CURRENCY_CODE_RECONCILIATION_INVALID,
     ISO_DATE_EFFECTIVE_INVALID,
     ISO_DATE_EXPIRATION_INVALID,
     ISO_MERCHANT_TYPE_INVALID,
     ISO_COUNTRY_CODE_INVALID,
     ISO_POS_DATA_CODE_INVALID,
     ISO_FUNCTION_CODE_INVALID,
     ISO_MESSAGE_REASON_CODE_INVALID,
     ISO_CARD_ACCEPTOR_BUS_CODE_INVALID,
     ISO_APPROVAL_CODE_LENGTH_INVALID,
     ISO_APPROVAL_CODE_INVALID,
     ISO_ACCEPT_TERM_ID_INVALID,
     ISO_CARD_ACCEPT_ID_INVALID,
     ISO_CARD_ACCEPT_LOCATION_INVALID,
     ISO_SYSTEM_TRACE_INVALID,
     ISO_SECURITY_INFO_INVALID,
     ISO_PRIVATE1_DATA_INVALID,
     ISO_PRIVATE2_DATA_INVALID,
     ISO_ACQUIRE_INST_ID_INVALID,
     ISO_FORWARD_INST_ID_INVALID,
     ISO_ACCOUNT_NO_EXTENDED_INVALID,
     ISO_TRACK1_DATA_INVALID,
     ISO_TRACK2_DATA_INVALID,
     ISO_RETRIEVAL_REF_INVALID,
     ISO_ADDITIONAL_DATA_PRIV_INVALID,                / UC01 /
     ISO_ORIGINAL_DATA_INVALID,
     ISO_ACTION_CODE_INVALID,
     ISO_CIRCUIT_CARD_INVALID,                        / UC04 /
     __ISO_MESSAGE_STATUS_LAST     / Not used /
} IsoMessageStatus;
*/

/* extern char* errorStrings[__ISO_MESSAGE_STATUS_LAST]; */

#endif

