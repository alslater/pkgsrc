/**************************************************************************
 * File Name :        Enumerations.h
 *
 * Description :      This header file contains the Enumerations needed
 *					  for the Secure Authorization application
 *
 * Author :           Arun G
 *
 * Date Created :     05/21/2001
 *
 * Modified :		On 06/08/2001 by Subbu. Added ECHO to IsRequired enum
 * 06/22/2001: Lonnie L. Filbrun Changed VARIABLELENGTH to support
 *             LLVARIABLELENGTH/LLLVARIABLELENGTH
 *
 **************************************************************************
 */

#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

/* EBCDIC values for 0 to 9 */
#define EBCDIC_VALUE_OF_0	240
#define EBCDIC_VALUE_OF_1	241
#define EBCDIC_VALUE_OF_2	242
#define EBCDIC_VALUE_OF_3	243
#define EBCDIC_VALUE_OF_4	244
#define EBCDIC_VALUE_OF_5	245
#define EBCDIC_VALUE_OF_6	246
#define EBCDIC_VALUE_OF_7	247
#define EBCDIC_VALUE_OF_8	248
#define EBCDIC_VALUE_OF_9	249

#define ASCII       1
#define EBCDIC      2

/*
 * This enumeration indicates whether values should be provided for the given field
 * in the ISO message.
 */
typedef enum
{
	REQUIRED=1,
	OPTIONAL=2,
	CONDITIONAL=3,
	ECHO=4
} IsRequired;

/*
 * This enumeration indicates whether the given field in the ISO message is of Fixed
 * length or variable length.
 */
typedef enum
{
	FIXEDLENGTH=0,
	LLVARLENGTH=2,
	LLLVARLENGTH=3
} FieldType;

/*
 * This enumeration defines the set of data types to which the fields in ISO
 * messages belong to.
 */
typedef enum
{
	NUMERIC,
	ALPHANUMERIC,	/* ALPHA and NUMERIC */
	ALPHANUMERICs,	/* ALPHA / NUMERIC / SPECIAL */
	ALPHANUMERICp,	/* ALPHA / NUMERIC / SPACE (pad) */
	BINARY,
	DATETIME,
	COMPLEX         /* Special type for fields that contain bitmap and binary data as well as strings etc ie P63 */
} DataTypes;

/*
 * This enumeration defines the Bit positions 1 to 64
 */
typedef enum
{
	BIT_POSITION_1=1,
	BIT_POSITION_2=2,
	BIT_POSITION_3=3,
	BIT_POSITION_4=4,
	BIT_POSITION_5=5,
	BIT_POSITION_6=6,
	BIT_POSITION_7=7,
	BIT_POSITION_8=8,
	BIT_POSITION_9=9,
	BIT_POSITION_10=10,
	BIT_POSITION_11=11,
	BIT_POSITION_12=12,
	BIT_POSITION_13=13,
	BIT_POSITION_14=14,
	BIT_POSITION_15=15,
	BIT_POSITION_16=16,
	BIT_POSITION_17=17,
	BIT_POSITION_18=18,
	BIT_POSITION_19=19,
	BIT_POSITION_20=20,
	BIT_POSITION_21=21,
	BIT_POSITION_22=22,
	BIT_POSITION_23=23,
	BIT_POSITION_24=24,
	BIT_POSITION_25=25,
	BIT_POSITION_26=26,
	BIT_POSITION_27=27,
	BIT_POSITION_28=28,
	BIT_POSITION_29=29,
	BIT_POSITION_30=30,
	BIT_POSITION_31=31,
	BIT_POSITION_32=32,
	BIT_POSITION_33=33,
	BIT_POSITION_34=34,
	BIT_POSITION_35=35,
	BIT_POSITION_36=36,
	BIT_POSITION_37=37,
	BIT_POSITION_38=38,
	BIT_POSITION_39=39,
	BIT_POSITION_40=40,
	BIT_POSITION_41=41,
	BIT_POSITION_42=42,
	BIT_POSITION_43=43,
	BIT_POSITION_44=44,
	BIT_POSITION_45=45,
	BIT_POSITION_46=46,
	BIT_POSITION_47=47,
	BIT_POSITION_48=48,
	BIT_POSITION_49=49,
	BIT_POSITION_50=50,
	BIT_POSITION_51=51,
	BIT_POSITION_52=52,
	BIT_POSITION_53=53,
	BIT_POSITION_54=54,
	BIT_POSITION_55=55,
	BIT_POSITION_56=56,
	BIT_POSITION_57=57,
	BIT_POSITION_58=58,
	BIT_POSITION_59=59,
	BIT_POSITION_60=60,
	BIT_POSITION_61=61,
	BIT_POSITION_62=62,
	BIT_POSITION_63=63,
	BIT_POSITION_64=64
} FieldEnum;

#undef ENOMEM

/*
 * This enumeration defines the Status Codes used to update the ISOStatus Object
 */
typedef enum
{
	VALID=1,
	ENOMEM=2,
	NO_DATA=3,
	INVALID_BIT_POSITION=4,
	INVALID=5,
	VALIDATION_FAILED=6
} StatusCodes;


/*
 * This enumeration defines the Processing Codes used in ISO8583 Messages.
 */
typedef enum
{
	AUTHORIZATION_DEBIT=4099,
	DEBIT_ADDRESS_VERIFICATION=4899,
	AUTHORIZATION_CREDIT=204099,
	ADDRESS_VERIFICATION=174899,
	FUNDING=210099,
	CASHOUT=114099,
	AVAILABLE_FUNDS=300099,
	ACTIVATE=920099,
	DEACTIVATE=930099,
	COMMUNICATION_VERIFICATION=0,
	AUTHORIZATION_REQUEST_REVERSAL=4000,
	ADDRESS_VERIFICATION_AUTHORIZATION=4800,
	AMEX_EMERGENCY_CHECK_CASHING=34000,
	CHECK_GUARANTEE_REQUEST=44000,
	AMEX_TRAVELERS_CHECK_ENCASHMENT=64000,
	AMEX_SIGHT_DRAFT=104000,
	TRANSACTION_ADDRESS_VERIFICATION=174800
} ProcessCodes;

#endif

