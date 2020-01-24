/*********************************************************************
*
*   File name:
*       CharUtility.h
*
*   Contents:
*       CharUtility class.
*
*   Description
*
*          This header file contains the definitions for the CharUtility
*		   class, which contains method signatures to convert from EBCDIC
*		   ACSII, int, unsigned int and viceversa. All these are static.
*		   Also it contains three static array attributes. All these are
*		   of private scope.
*
*   See Also:
*          Enumerations.h
*
*
*   Created:
*       05/21/01 Subbu G Gowreddy
*
*   Modified:
*		12 June 2001 Shubha Kumar
*			- No character data is null terminated
*			- The methods will take the length of character arrays sent as input
*
*
**********************************************************************/

/**************************************************************************
 *
 * CLASS NAME:          CharUtility
 *
 * SCOPE:               All methods are of public scope. and the variables
 *						are private. All are static.
 *
 * DESCRIPTION:			Contains method signatures to convert from EBCDIC
 *						ACSII, int, unsigned int and viceversa. All these
 *						are static. Also it contains three static array
 *						attributes. All these are of private scope.
 *
 **************************************************************************
 */

#ifndef CHARUTILITY_H
#define CHARUTILITY_H

#include "STU_platform.h"
#include "stddef.h"

class LINKDLL CharUtility
{
	//Attributes
private:
	/* ASCII to EBCDIC Translation Table */
	static unsigned char asc2ebc[256];

	/* EBCDIC to ASCII Translation Table */
	static unsigned char ebc2asc[256];

	static unsigned int ebcdic_int[10] ;

	//Methods
public:
	/*
	* Function : toEbcdic
	* Desc     : convert a character from ascii to ebcdic
	* Input    : unsigned char c1
	* Returns  : unsigned char c2
	* Requires : 0 <= c1 <= 127
	* Ensures  : c2 == ebcdic equivalent of c1
	*/
	static unsigned char toEbcdic(unsigned char) ;

	/*
	* Function : toAscii
	* Desc     : convert a character from ebcdic to ascii
	* Input    : unsigned char c1
	* Returns  : unsigned char c2
	* Requires : c1 has an ascii equivalent in the non-extended ASCII set
	* Ensures  : c2 == ascii equivalent of c1
	*/
	static unsigned char toAscii(unsigned char) ;

	/*
	* Function : toEbcdicStr
	* Desc     : convert a character array from ascii to ebcdic
	* Input    : unsigned char *s1, unsigned char *s2,
	*            s1 : ascii char array to be converted
	*            s2 : equivalent ebcdic char array (output)
	*			 asciiLen : Length of the ASCII char array to be converted
	* Returns  : void
	* Requires : 1. s2 has been allocated sufficient space, ie, len(s2) >= len(s1)
	*            2. for every c in s1, 0 <= c <= 127
	* Ensures  : 1. for 0 <= i < len(s1), s2[i] == ebcdic equivalent of s1[i]
	*            2. s1 does not change
	*/
	static void toEbcdicStr(unsigned char *, unsigned char *, int asciiLen) ;

	/*
	* Function : toAsciiStr
	* Desc     : convert a character array from ebcdic to ascii
	* Input    : unsigned char *s1, unsigned char *s2,
	*            s1 : ebcdic string to be converted
	*            s2 : equivalent ascii string (output)
	*			 ebcdicLen : Length of the EBCDIC char array to be converted
	* Returns  : void
	* Requires : 1. s2 has been allocated sufficient space, ie, len(s2) >= len(s1)
	*            2. for every c in s1, c has an ascii equivalent in the non-extended
	*               ASCII set
	* Ensures  : 1. for 0 <= i < len(s1), s2[i] == ascii equivalent of s1[i]
	*            2. s1 does not change
	*/
	static void toAsciiStr(unsigned char *, unsigned char *, int ebcdicLen) ;

	/*
	* Function : toEbcdicStrInplace
	* Desc     : convert a character array from ascii to ebcdic, in place.
	* Input    : unsigned char* s, int asciiLen
	* Returns  : bool(true(1) on success and false(0) if not)
	* Requires :
	* Ensures  :
	*/
	static bool toEbcdicStrInplace(unsigned char *, int asciiLen) ;

	/*
	* Function : toAsciiStrInplace
	* Desc     : convert a character array from ebcdic to ascii, in place.
	* Input    : unsigned char* s, int ebcdicLen
	* Returns  : bool(true(1) on success and false(0) if not)
	* Requires :
	* Ensures  :
	*/
	static bool toAsciiStrInplace(unsigned char *, int ebcdicLen) ;

	/*
	* Function    : itoa_pad
	* Description : converts an integer to a string; leftpad with zeros to fill
	*               'size' spaces.
	* Input       : unsigned int i
	*               unsigned int size
	* Returns     : unsigned char* s
	* Requires    : 0 <= i < FFFFFFFF
	* Ensures     : 1. s is a string representing i
	*               2. i does not change
	*               3. length of s is size or the actual number of bytes needed
	*                  to represent i, whichever is greater; if size is greater,
	*                  left padded with '0'.
	* Note        : The user should deallocate the memory allocated to s.
	*/
	static unsigned char* itoa_pad(unsigned int, unsigned int) ;

	/*
	* Function : ebcdic2int
	* Desc     : convert an ebcdic character array to integer.
	* Input    : unsigned char *ebcdicStr, int ebcdicLen
	* Returns  : int
	* Requires : 1. ebcdicStr represents a valid integer
	* Ensures  : 1. return value is the int represented by the ebcdic str.
	*            2. ebcdicStr does not change.
	*/
	static int ebcdic2int(unsigned char *, int ebcdicLen) ;

	/*
	* Function : int2ebcdic
	* Desc     : convert an integer to an ebcdic character array.
	* Input    : int i
	* Returns  : unsigned char *ebcdicStr
	* Requires : 1. i should be representable in <= 64 bits
	*            2. two's complement representation is used
	* Ensures  : 1. return value is the ebcdic representation of i.
	*            2. i does not change.
	* Note     : the function allocates the memory required for ebcdicStr; the
	*            user should deallocate it after use.
	*/

	static unsigned char* int2ebcdic(int) ;


	/*
	Function : int2ebcdic_pad
	Desc     : convert an integer to an ebcdic character array with left padding.
	Input    : int i, unsigned int size
	Returns  : unsigned char *ebcdicStr
	Requires : 1. i be representable in <= 64 bits
			   2. two's complement representation is used
	Ensures  : 1. return value is the ebcdic representation of i.
			   2. i does not change.
			   3. length of s is size or the actual number of bytes needed
				  to represent i, whichever is greater; if size is greater,
				  left padded with '0'.
	Note     : the function allocates the memory required for ebcdicStr; the
			   user should deallocate it after use.
	*/


	static unsigned char* int2ebcdic_pad(int, unsigned int) ;

	/*
	* Function : ebcdic2uint
	* Desc     : convert an ebcdic character array to unsigned integer.
	* Input    : unsigned char *ebcdicStr, int ebcdicLen
	* Returns  : unsigned int
	* Requires : 1. ebcdicStr represents a valid unsigned integer
	* Ensures  : 1. return value is the unsigned int represented by the ebcdic str.
	*            2. ebcdicStr does not change.
	*/
	static unsigned int ebcdic2uint(unsigned char *, int ebcdicLen) ;


	/*
	* Function : uint2ebcdic
	* Desc     : convert an unsigned integer to an ebcdic character array.
	* Input    : unsigned int i
	* Returns  : unsigned char *ebcdicStr
	* Requires : 1. i should be representable in <= 64 bits
	* Ensures  : 1. return value is the ebcdic representation of i.
	*            2. i does not change.
	* Note     : the function allocates the memory required for ebcdicStr; the
				 user should deallocate it after use.
	*/
	static unsigned char* uint2ebcdic(unsigned int) ;


	/***********************************************************************
	Function : uint2ebcdic_pad
	Desc     : convert an unsigned integer to an ebcdic character array with
			   left '0' padding.
	Input    : unsigned int i, unsigned int size
	Returns  : unsigned char *ebcdicStr
	Requires : 1. i be representable in <= 64 bits
	Ensures  : 1. return value is the ebcdic representation of i.
			   2. i does not change.
			   3. length of s is size or the actual number of bytes needed
				  to represent i, whichever is greater; if size is greater,
				  left padded with '0'.
	Note     : the function allocates the memory required for ebcdicStr; the
				 user should deallocate it after use.
	*************************************************************************/
	static unsigned char* uint2ebcdic_pad(unsigned int, unsigned int) ;

	/***********************************************************************
	Function : createErrMessage
	Desc     : Creates final error message by appending the bit position at
			   which the error is raised to the original error message raised
			   at the point where error is raised.
	Input    : int (BitPosition), char* (Original error message)
	Returns  : char* (Final error message).

	*************************************************************************/
	static char* createErrMessage(int , char*);


	/*
	* Function : unPackBCD
	* Desc     : convert a character array from packed BCD to ascii.
	* Input    : unsigned char* buf     - packedBCD string.
	*            int len                - length of the packdBCD string.
	*            unsigned char* retbuf  - pointer to ascii buffer allocated to retlen characters.
	*            int expected_len       - length of ascii string and expected length of the returned data.
	* Returns  : bool - true if successful.
	* Note retbuf must be expected_len in size. If the string would be an odd number size, the leading zero
	* will be skipped when unpacking the BCD.
	*/
	static bool UnpackBCD(unsigned char* buf, int len, unsigned char* retbuf, int expected_len) ;

	/*
	* Function : toPackedBCDInplace
	* Desc     : convert a character array from ascii to packed BCD, in place.
	* Input    : unsigned char* s, int dataLen
	* Returns  : size_t - length of packed BCD data
	* Note data after the packed BCD data is unchanged ie not set to 0.
	*/
	static size_t toPackedBCDInplace(unsigned char *, int dataLen) ;

	/*
	* Function : PackedBCDSize
	* Desc     : Calculates the PackedBCD size of data of the given length
	* Input    : size_t datalen - length of the data
	* Returns  : size_t - length of packed BCD data
	*/
	static size_t PackedBCDSize(size_t dataLen) ;

	/* end of file */

};

#endif


