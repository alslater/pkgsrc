/*********************************************************************
*
*   File name:
*       CharUtility.cpp
*   Contents:
*       Implements the methods described in the CharUtility.h header file
*       for the CharUtility class.
*
*       
*   Description
*
*          This file contains the implementation of the methods which
*          are used to convert a char,string, int and unsigned int from
*          EBCDIC to ASCII and Viceversa. 
*
*
*   See Also:
*          CharUtility.h
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

//standard includes
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <memory.h>

//Package specific header files.
#include "CharUtility.h"

	#if !defined(NULL)
	#define NULL (0)
	#endif

	//Decimal Eqivalent of zero in EBCDIC 
	const unsigned char EBCDIC_ZERO  = 240;
	//Decimal Eqivalent of minus(-) in EBCDIC
	const unsigned char EBCDIC_MINUS = 96; 
	//Decimal Eqivalent of plus(+) in EBCDIC
	const unsigned char EBCDIC_PLUS  = 78;

	//ASCII to EBCDIC conversion table
	unsigned char CharUtility::asc2ebc[] = 
	{
	   /* -00-  -01-  -02-  -03-  -04-  -05-  -06-  -07- */
		  0x00, 0x01, 0x02, 0x03, 0x37, 0x2D, 0x2E, 0x2F,
	   /* -08-  -09-  -0A-  -0B-  -0C-  -0D-  -0E-  -0F- */
		  0x16, 0x05, 0x15, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	   /* -10-  -11-  -12-  -13-  -14-  -15-  -16-  -17- */
		  0x10, 0x11, 0x12, 0x13, 0x3C, 0x3D, 0x32, 0x26,
	   /* -18-  -19-  -1A-  -1B-  -1C-  -1D-  -1E-  -1F- */
		  0x18, 0x19, 0x3F, 0x27, 0x1C, 0x1D, 0x1E, 0x1F,
	   /* -20-  -21-  -22-  -23-  -24-  -25-  -26-  -27- */
		  0x40, 0x5A, 0x7F, 0x7B, 0x5B, 0x6C, 0x50, 0x7D,
	   /* -28-  -29-  -2A-  -2B-  -2C-  -2D-  -2E-  -2F- */
		  0x4D, 0x5D, 0x5C, 0x4E, 0x6B, 0x60, 0x4B, 0x61,
	   /* -30-  -31-  -32-  -33-  -34-  -35-  -36-  -37- */
		  0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
	   /* -38-  -39-  -3A-  -3B-  -3C-  -3D-  -3E-  -3F- */
		  0xF8, 0xF9, 0x7A, 0x5E, 0x4C, 0x7E, 0x6E, 0x6F,
	   /* -40-  -41-  -42-  -43-  -44-  -45-  -46-  -47- */
		  0x7C, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
	   /* -48-  -49-  -4A-  -4B-  -4C-  -4D-  -4E-  -4F- */
		  0xC8, 0xC9, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,
	   /* -50-  -51-  -52-  -53-  -54-  -55-  -56-  -57- */
		  0xD7, 0xD8, 0xD9, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,
	   /* -58-  -59-  -5A-  -5B-  -5C-  -5D-  -5E-  -5F- */
		  0xE7, 0xE8, 0xE9, 0xAD, 0xE0, 0xBD, 0x5F, 0x6D,
	   /* -60-  -61-  -62-  -63-  -64-  -65-  -66-  -67- */
		  0x79, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	   /* -68-  -69-  -6A-  -6B-  -6C-  -6D-  -6E-  -6F- */
		  0x88, 0x89, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,
	   /* -70-  -71-  -72-  -73-  -74-  -75-  -76-  -77- */
		  0x97, 0x98, 0x99, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,
	   /* -78-  -79-  -7A-  -7B-  -7C-  -7D-  -7E-  -7F- */
		  0xA7, 0xA8, 0xA9, 0xC0, 0x4F, 0xD0, 0xA1, 0x07,
	   /* -80-  -81-  -82-  -83-  -84-  -85-  -86-  -87- */
		  0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x06, 0x17,
	   /* -88-  -89-  -8A-  -8B-  -8C-  -8D-  -8E-  -8F- */
		  0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x09, 0x0A, 0x1B,
	   /* -90-  -91-  -92-  -93-  -94-  -95-  -96-  -97- */
		  0x30, 0x31, 0x1A, 0x33, 0x34, 0x35, 0x36, 0x08,
	   /* -98-  -99-  -9A-  -9B-  -9C-  -9D-  -9E-  -9F- */
		  0x38, 0x39, 0x3A, 0x3B, 0x04, 0x14, 0x3E, 0xFF,
	   /* -A0-  -A1-  -A2-  -A3-  -A4-  -A5-  -A6-  -A7- */
		  0x41, 0xAA, 0x4A, 0xB1, 0x9F, 0xB2, 0x6A, 0xB5,
	   /* -A8-  -A9-  -AA-  -AB-  -AC-  -AD-  -AE-  -AF- */
		  0xBB, 0xB4, 0x9A, 0x8A, 0xB0, 0xCA, 0xAF, 0xBC,
	   /* -B0-  -B1-  -B2-  -B3-  -B4-  -B5-  -B6-  -B7- */
		  0x90, 0x8F, 0xEA, 0xFA, 0xBE, 0xA0, 0xB6, 0xB3,
	   /* -B8-  -B9-  -BA-  -BB-  -BC-  -BD-  -BE-  -BF- */
		  0x9D, 0xDA, 0x9B, 0x8B, 0xB7, 0xB8, 0xB9, 0xAB,
	   /* -C0-  -C1-  -C2-  -C3-  -C4-  -C5-  -C6-  -C7- */
		  0x64, 0x65, 0x62, 0x66, 0x63, 0x67, 0x9E, 0x68,
	   /* -C8-  -C9-  -CA-  -CB-  -CC-  -CD-  -CE-  -CF- */
		  0x74, 0x71, 0x72, 0x73, 0x78, 0x75, 0x76, 0x77,
	   /* -D0-  -D1-  -D2-  -D3-  -D4-  -D5-  -D6-  -D7- */
		  0xAC, 0x69, 0xED, 0xEE, 0xEB, 0xEF, 0xEC, 0xBF,
	   /* -D8-  -D9-  -DA-  -DB-  -DC-  -DD-  -DE-  -DF- */
		  0x80, 0xFD, 0xFE, 0xFB, 0xFC, 0xBA, 0xAE, 0x59,
	   /* -E0-  -E1-  -E2-  -E3-  -E4-  -E5-  -E6-  -E7- */
		  0x44, 0x45, 0x42, 0x46, 0x43, 0x47, 0x9C, 0x48,
	   /* -E8-  -E9-  -EA-  -EB-  -EC-  -ED-  -EE-  -EF- */
		  0x54, 0x51, 0x52, 0x53, 0x58, 0x55, 0x56, 0x57,
	   /* -F0-  -F1-  -F2-  -F3-  -F4-  -F5-  -F6-  -F7- */
		  0x8C, 0x49, 0xCD, 0xCE, 0xCB, 0xCF, 0xCC, 0xE1,
	   /* -F8-  -F9-  -FA-  -FB-  -FC-  -FD-  -FE-  -FF- */
		  0x70, 0xDD, 0xDE, 0xDB, 0xDC, 0x8D, 0x8E, 0xDF
	};

	//EBCDIC to ASCII conversion table
	unsigned char CharUtility::ebc2asc[] =
	{
	   /* -00-  -01-  -02-  -03-  -04-  -05-  -06-  -07- */
		  0x00, 0x01, 0x02, 0x03, 0x9C, 0x09, 0x86, 0x7F,
	   /* -08-  -09-  -0A-  -0B-  -0C-  -0D-  -0E-  -0F- */
		  0x97, 0x8D, 0x8E, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	   /* -10-  -11-  -12-  -13-  -14-  -15-  -16-  -17- */
		  0x10, 0x11, 0x12, 0x13, 0x9D, 0x0A, 0x08, 0x87,
	   /* -18-  -19-  -1A-  -1B-  -1C-  -1D-  -1E-  -1F- */
		  0x18, 0x19, 0x92, 0x8F, 0x1C, 0x1D, 0x1E, 0x1F,
	   /* -20-  -21-  -22-  -23-  -24-  -25-  -26-  -27- */
		  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x17, 0x1B,
	   /* -28-  -29-  -2A-  -2B-  -2C-  -2D-  -2E-  -2F- */
		  0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x05, 0x06, 0x07,
	   /* -30-  -31-  -32-  -33-  -34-  -35-  -36-  -37- */
		  0x90, 0x91, 0x16, 0x93, 0x94, 0x95, 0x96, 0x04,
	   /* -38-  -39-  -3A-  -3B-  -3C-  -3D-  -3E-  -3F- */
		  0x98, 0x99, 0x9A, 0x9B, 0x14, 0x15, 0x9E, 0x1A,
	   /* -40-  -41-  -42-  -43-  -44-  -45-  -46-  -47- */
		  0x20, 0xA0, 0xE2, 0xE4, 0xE0, 0xE1, 0xE3, 0xE5,
	   /* -48-  -49-  -4A-  -4B-  -4C-  -4D-  -4E-  -4F- */
		  0xE7, 0xF1, 0xA2, 0x2E, 0x3C, 0x28, 0x2B, 0x7C,
	   /* -50-  -51-  -52-  -53-  -54-  -55-  -56-  -57- */
		  0x26, 0xE9, 0xEA, 0xEB, 0xE8, 0xED, 0xEE, 0xEF,
	   /* -58-  -59-  -5A-  -5B-  -5C-  -5D-  -5E-  -5F- */
		  0xEC, 0xDF, 0x21, 0x24, 0x2A, 0x29, 0x3B, 0x5E,
	   /* -60-  -61-  -62-  -63-  -64-  -65-  -66-  -67- */
		  0x2D, 0x2F, 0xC2, 0xC4, 0xC0, 0xC1, 0xC3, 0xC5,
	   /* -68-  -69-  -6A-  -6B-  -6C-  -6D-  -6E-  -6F- */
		  0xC7, 0xD1, 0xA6, 0x2C, 0x25, 0x5F, 0x3E, 0x3F,
	   /* -70-  -71-  -72-  -73-  -74-  -75-  -76-  -77- */
		  0xF8, 0xC9, 0xCA, 0xCB, 0xC8, 0xCD, 0xCE, 0xCF,
	   /* -78-  -79-  -7A-  -7B-  -7C-  -7D-  -7E-  -7F- */
		  0xCC, 0x60, 0x3A, 0x23, 0x40, 0x27, 0x3D, 0x22,
	   /* -80-  -81-  -82-  -83-  -84-  -85-  -86-  -87- */
		  0xD8, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	   /* -88-  -89-  -8A-  -8B-  -8C-  -8D-  -8E-  -8F- */
		  0x68, 0x69, 0xAB, 0xBB, 0xF0, 0xFD, 0xFE, 0xB1,
	   /* -90-  -91-  -92-  -93-  -94-  -95-  -96-  -97- */
		  0xB0, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
	   /* -98-  -99-  -9A-  -9B-  -9C-  -9D-  -9E-  -9F- */
		  0x71, 0x72, 0xAA, 0xBA, 0xE6, 0xB8, 0xC6, 0xA4,
	   /* -A0-  -A1-  -A2-  -A3-  -A4-  -A5-  -A6-  -A7- */
		  0xB5, 0x7E, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	   /* -A8-  -A9-  -AA-  -AB-  -AC-  -AD-  -AE-  -AF- */
		  0x79, 0x7A, 0xA1, 0xBF, 0xD0, 0x5B, 0xDE, 0xAE,
	   /* -B0-  -B1-  -B2-  -B3-  -B4-  -B5-  -B6-  -B7- */
		  0xAC, 0xA3, 0xA5, 0xB7, 0xA9, 0xA7, 0xB6, 0xBC,
	   /* -B8-  -B9-  -BA-  -BB-  -BC-  -BD-  -BE-  -BF- */
		  0xBD, 0xBE, 0xDD, 0xA8, 0xAF, 0x5D, 0xB4, 0xD7,
	   /* -C0-  -C1-  -C2-  -C3-  -C4-  -C5-  -C6-  -C7- */
		  0x7B, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	   /* -C8-  -C9-  -CA-  -CB-  -CC-  -CD-  -CE-  -CF- */
		  0x48, 0x49, 0xAD, 0xF4, 0xF6, 0xF2, 0xF3, 0xF5,
	   /* -D0-  -D1-  -D2-  -D3-  -D4-  -D5-  -D6-  -D7- */
		  0x7D, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
	   /* -D8-  -D9-  -DA-  -DB-  -DC-  -DD-  -DE-  -DF- */
		  0x51, 0x52, 0xB9, 0xFB, 0xFC, 0xF9, 0xFA, 0xFF,
	   /* -E0-  -E1-  -E2-  -E3-  -E4-  -E5-  -E6-  -E7- */
		  0x5C, 0xF7, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
	   /* -E8-  -E9-  -EA-  -EB-  -EC-  -ED-  -EE-  -EF- */
		  0x59, 0x5A, 0xB2, 0xD4, 0xD6, 0xD2, 0xD3, 0xD5,
	   /* -F0-  -F1-  -F2-  -F3-  -F4-  -F5-  -F6-  -F7- */
		  0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	   /* -F8-  -F9-  -FA-  -FB-  -FC-  -FD-  -FE-  -FF- */
		  0x38, 0x39, 0xB3, 0xDB, 0xDC, 0xD9, 0xDA, 0x9F
	};
	
	//EBCDIC eqivalents of integers from 0 to 9
	unsigned int CharUtility::ebcdic_int[] = 
	{
		240, 241, 242, 243, 244, 245, 246, 247, 248, 249
	} ;


	/****************************************************************************
	Function : toEbcdic
	Desc     : convert a character from ascii to ebcdic
	Input    : unsigned char c1
	Returns  : unsigned char c2
	Requires : 0 <= c1 <= 127 
	Ensures  : c2 == ebcdic equivalent of c1
	****************************************************************************/
	unsigned char CharUtility::toEbcdic(unsigned char cAsc)
	{
		return (asc2ebc[(unsigned int) cAsc]) ;
	}

	/****************************************************************************
	Function : toAscii
	Desc     : convert a character from ebcdic to ascii
	Input    : unsigned char c1
	Returns  : unsigned char c2
	Requires : c1 has an ascii equivalent in the non-extended ASCII set
	Ensures  : c2 == ascii equivalent of c1
	****************************************************************************/
	unsigned char CharUtility::toAscii(unsigned char cEbc)
	{
		 return (ebc2asc[(unsigned int) cEbc]) ;
	}

	/****************************************************************************
	Function : toEbcdicStr
	Desc     : convert a character array from ascii to ebcdic
	Input    : unsigned char *s1, unsigned char *s2, int dataLen
			   s1 : ascii string to be converted
			   s2 : equivalent ebcdic array (output)
			   asciiLen : Length of the ascii data sent.
	Returns  : void
	Requires : 1. s2 has been allocated sufficient space, ie, len(s2) >= len(s1)
			   2. for every c in s1, 0 <= c <= 127 
	Ensures  : 1. for 0 <= i < len(s1), s2[i] == ebcdic equivalent of s1[i]
			   2. s1 does not change
	****************************************************************************/
	void CharUtility::toEbcdicStr(unsigned char* asc_str, unsigned char* ebc_str, int asciiLen)
	{
		//convert each ascii character to ebcdic
		for(int i=0; i<asciiLen; i++) 
		{
			ebc_str[i] = asc2ebc[(unsigned int) asc_str[i]];
		}
		return ;
	}


	/****************************************************************************
	Function : toAsciiStr
	Desc     : convert a character from ebcdic array to ascii
	Input    : unsigned char *s1, unsigned char *s2, int dataLen
			   s1 : ebcdic string to be converted
			   s2 : equivalent ascii array (output)
			   ebcdicLen : Length of the data sent.
	Returns  : void
	Requires : 1. s2 has been allocated sufficient space, ie, len(s2) >= len(s1)
			   2. for every c in s1, c has an ascii equivalent in the non-extended 
				  ASCII set
	Ensures  : 1. for 0 <= i < len(s1), s2[i] == ascii equivalent of s1[i]
			   2. s1 does not change
	****************************************************************************/
	void CharUtility::toAsciiStr(unsigned char *ebc_str, unsigned char *asc_str, int ebcdicLen)
	{
		//convert each ebcdic character to ascii
		for(int i=0; i<ebcdicLen; i++) 
		{
			ebc_str[i] = asc2ebc[(unsigned int) asc_str[i]];
		}

		 return ;
	}


	                                
	/****************************************************************************
	Function : toAsciiStrInplace
	Desc     : convert a character from ebcdic array to ascii, in place
	Input    : unsigned char* s, int ebcdicLen
	Returns  : bool (True on success and False if not)
	Requires :
	Ensures  :
	****************************************************************************/
	bool CharUtility::toAsciiStrInplace(unsigned char *ebc_str, int ebcdicLen)
	{
		//to hold the new ascii array
		unsigned char* asc_str = NULL;
		int i=0;         
        //allocate memory for the new array to hold the ascii array
		//memory released at the end of the function
		asc_str = new unsigned char[ebcdicLen+1] ;

		//Check if memory has been allocated, if not return false
        if (asc_str == NULL)
			return false;
		else
		{
			//Initialize the pointer to char with NULL
			memset(asc_str,0, ebcdicLen+1);
			//convert each ebcdic character in the array to ascii
			for(i=0; i<ebcdicLen; i++) 
			{
				asc_str[i] = ebc2asc[(unsigned int) ebc_str[i]];
			}

			//put the converted array back to the output parameter "ebc_str"    
			for(i=0; i < ebcdicLen; i++)
				ebc_str[i] = asc_str[i];
       
			//release the local pointer for new ascii array
			delete asc_str;
 
			return true;
		}        
	}

	/****************************************************************************
	Function : toEbcdicStrInplace
	Desc     : convert a character from ebcdic array to ascii, in place
	Input    : unsigned char* s, int asciiLen
	Returns  : bool (True on success and False if not)
	Requires :
	Ensures  :
	****************************************************************************/

	bool CharUtility::toEbcdicStrInplace(unsigned char *asc_str, int asciiLen)
	{
		//to hold the new ebcdic array		
		unsigned char* ebc_str = NULL;
		int i=0;			 
		//allocate memory for the converted array
		//memory released at the end of the function
		ebc_str = new unsigned char [asciiLen+1] ;

		//Check if memory has been allocated, if not return false
		if (ebc_str == NULL)
				return false ;
		else
		{
			//Initialize the pointer to char with NULL
			memset(ebc_str,0, asciiLen+1);
			//convert each ascii character in the array to ebcdic
			for(i=0; i<asciiLen; i++) 
			{
				ebc_str[i] = asc2ebc[(unsigned int) asc_str[i]];
			}

			//put the converted array back to the output parameter "ebc_str"    
			for(i=0; i < asciiLen; i++)
				asc_str[i] = ebc_str[i];

			//release local pointer for the new ebcdic array		
			delete ebc_str;

			return true ;
		}		
	}
 


	/****************************************************************************
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
	****************************************************************************/
	unsigned char* CharUtility::itoa_pad(unsigned int i, unsigned int size) 
	{
		 unsigned char temp[25] ;  /* good for 64 bits */
		 unsigned int  tempsize, index ;
		 unsigned char *strptr = NULL;

		 (void) sprintf((char*)temp, "%d", i) ;
		 tempsize = strlen((char*) temp) ;

		 size = ((size>tempsize)?size:tempsize) ;
		 //allocate memory for the ascii converted strong
		 //memory released in the calling function
		 strptr = new unsigned char[size+1] ;

		//Check if memory has been allocated
		 if (strptr == NULL)
			  return NULL;
		 else
		 {
			//Initialize the pointer to char with NULL
			memset(strptr,0, size+1);
			/* left pad with zero's */
			for (index=0; index<size-tempsize; index++)
			  strptr[index] = '0' ;
			strptr[index] = '\0' ;
			strcat((char*)strptr, (char*)temp) ;
			return (strptr) ;
			
		 }

		 
	}

	/****************************************************************************
	Function : ebcdic2int
	Desc     : convert an ebcdic character array to integer.
	Input    : unsigned char *ebcdicStr, int ebcdicLen 
	Returns  : int
	Requires : 1. ebcdicStr represents a valid integer 
	Ensures  : 1. return value is the int represented by the ebcdic str.
			   2. ebcdicStr does not change.
	****************************************************************************/
	int CharUtility::ebcdic2int(unsigned char *ebcdicStr, int ebcdicLen)
	{
		 int  i,  index ;
		 size_t count;
		 int  sign = 1;

		 i = 0 ;
		 count = 0 ;
		 if (*ebcdicStr == EBCDIC_MINUS)     
		 {
			  sign = -1 ;
			  count = 1 ;
		 }
		 else if (*ebcdicStr == EBCDIC_PLUS)
			  count = 1 ;

		 for ( ; count < (unsigned)ebcdicLen; count++)
		 {
			  for (index=0; ebcdic_int[index]!=(unsigned int) *(ebcdicStr+count) && index<10; index++) /* loop */ ;
				i = ((int) 10)*i+ (int) index ;
		 }

		 return sign*i ;
	}


	/****************************************************************************
	Function : int2ebcdic
	Desc     : convert an integer to an ebcdic character array.
	Input    : int i
	Returns  : unsigned char *ebcdicStr 
	Requires : 1. i be representable in <= 64 bits
			   2. two's complement representation is used
	Ensures  : 1. return value is the ebcdic representation of i.
			   2. i does not change.
	Note     : the function allocates the memory required for ebcdicStr; the 
				 user should deallocate it after use.
	****************************************************************************/
	unsigned char* CharUtility::int2ebcdic(int i)
	{
		 unsigned char tempStr[22] ;          /* sufficient for 64 bits */ 
		 unsigned char *ebcdicStr = NULL;
		 int temp ;                                                  /* local copy of i */
		 int index, index2, rem, quot ;
		 int sign = 0 ; /* set to 1 if negative */
		 int intmin = 0 ; /* set to 1 if INT_MIN */

		 temp = i ;
		 if (temp==0)
		 {
			  ebcdicStr = new unsigned char[2] ;

			  //Check if memory has been allocated
			  if (ebcdicStr == NULL)
				   return NULL ;
			  ebcdicStr[0] = EBCDIC_ZERO ;
			  ebcdicStr[1] = '\0' ;
			  return ebcdicStr ;
		 }

		 /* check for negative */
		 if (temp==INT_MIN)
		 {
			  sign = 1 ;
			  intmin = 1 ;
			  temp = INT_MAX ;
		 }
		 else if (temp<0)
		 {
			  sign = 1 ;
			  temp *= -1 ;
		 }

		 index = 0 ;
		 while (temp>0)
		 {
			  quot = temp/10 ;
			  rem = temp - quot*10 ;
			  rem = intmin ? rem+1 : rem ;/* assuming abs(INT_MIN)==INT_MAX+1 */
			  intmin = 0 ;                                        /* don't want rem to incr. after 1'st time */
			  tempStr[index++] = EBCDIC_ZERO+rem ;
			  temp = quot ; 
		 }

		 if (sign)
			  tempStr[index++] = EBCDIC_MINUS ;

		 /* reverse the string */
		 //allocate memory for new ebcdic array
		 //memory released by the calling function
		 ebcdicStr = new unsigned char[index+1] ;

		 //Check if memory has been allocated
		 if (ebcdicStr == NULL)
			  return NULL ;

		 //Initialize the pointer to char with NULL
		 memset(ebcdicStr,0, index+1);
		 index-- ;
		 index2 = 0 ;
		 while (index>=0)
			  ebcdicStr[index2++] = tempStr[index--] ;
		 //ebcdicStr[index2] = '\0' ;

		 return (unsigned char *) ebcdicStr ;
	}


	/****************************************************************************
	Function : int2ebcdic_pad
	Desc     : convert an integer to an ebcdic character string with left padding.
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
	****************************************************************************/
	unsigned char* CharUtility::int2ebcdic_pad(int i, unsigned int size)
	{
		 unsigned char tempStr[22] ;          /* sufficient for 64 bits */ 
		 unsigned char *ebcdicStr = NULL ;
		 int temp ;                                                  /* local copy of i */
		 unsigned int index, index2;
		 int rem, quot ;
		 int sign = 0 ;                                         /* set to 1 if negative */
		 int intmin = 0 ;                                    /* set to 1 if INT_MIN */

		 index = 0 ;
		 temp = i ;
		 if (temp==0)
		 {
			  tempStr[0] = EBCDIC_ZERO ;
			  index = 1 ;
		 }
		 else
		 {
			  /* check for negative */
			  if (temp==INT_MIN)
			  {
				   sign = 1 ;
				   intmin = 1 ;
				   temp = INT_MAX ;
			  }
			  else if (temp<0)
			  {
				   sign = 1 ;
				   temp *= -1 ;
			  }
     
			  while (temp>0)
			  {
				   quot = temp/10 ;
				   rem = temp - quot*10 ;
				   rem = intmin ? rem+1 : rem ;/* assuming abs(INT_MIN)==INT_MAX+1 */
				   intmin = 0 ;                                        /* don't want rem to incr. after 1'st time */
				   tempStr[index++] = EBCDIC_ZERO+rem ;
				   temp = quot ; 
			  }
     
			  if (sign)
				   tempStr[index++] = EBCDIC_MINUS ;
		 } /* if temp==0 */

		 /* reverse the string */
		 //memory released by the calling function
		 ebcdicStr = new unsigned char[(((size>index)?size:index)+1)] ;

         //Check if memory has been allocated
		 if (ebcdicStr == NULL)
			  return NULL ;

		 //Initialize the pointer to char with NULL
		 memset(ebcdicStr,0, (((size>index)?size:index)+1));
		 /* initial padding */
		 index2 = 0 ;
		 while (index2 < (size-index))
			  ebcdicStr[index2++] = EBCDIC_ZERO ;
		 /* actual data */
		 index-- ;
		 while (index>=0)
			  ebcdicStr[index2++] = tempStr[index--] ;
		 //ebcdicStr[index2] = '\0' ;

		 return (unsigned char *) ebcdicStr ;
	}

	
	/****************************************************************************
	Function : ebcdic2uint
	Desc     : converts an ebcdic character array to unsigned integer.
	Input    : unsigned char *ebcdicStr, int ebcdicLen
	Returns  : unsigned int
	Requires : 1. ebcdicStr represents a valid unsigned integer 
	Ensures  : 1. return value is the unsigned int represented by the ebcdic str.
			   2. ebcdicStr does not change.
	****************************************************************************/
	unsigned int CharUtility::ebcdic2uint(unsigned char *ebcdicStr, int ebcdicLen)
	{
		 int  i,  index ;
		 size_t count;

		 i = 0 ;
		 count = 0 ;
		 for ( ; count<(unsigned)ebcdicLen; count++)
		 {
			  for (index=0; ebcdic_int[index]!=(unsigned int) *(ebcdicStr+count) && index<10; index++) /* loop */ ;
			  i = ((int) 10)*i+ (int) index ;
		 }

		 return i ;
	}


	/****************************************************************************
	Function : uint2ebcdic
	Desc     : convert an unsigned integer to an ebcdic character array.
	Input    : unsigned int i
	Returns  : unsigned char *ebcdicStr 
	Requires : 1. i be representable in <= 64 bits
	Ensures  : 1. return value is the ebcdic representation of i.
			   2. i does not change.
	Note     : the function allocates the memory required for ebcdicStr; the 
				 user should deallocate it after use.
	****************************************************************************/
	unsigned char* CharUtility::uint2ebcdic(unsigned int i)
	{
		 unsigned char tempStr[22] ;          /* sufficient for 64 bits */ 
		 unsigned char *ebcdicStr = NULL;
		 unsigned int temp ;                                                  /* local copy of i */
		 int index, index2, rem, quot ;

		 temp = i ;
		 if (temp==0)
		 {
			ebcdicStr = new unsigned char[2] ;

            //Check if memory has been allocated
			if (ebcdicStr == NULL)
			   return NULL ;
			ebcdicStr[0] = EBCDIC_ZERO ;
			ebcdicStr[1] = '\0' ;
			return ebcdicStr ;
		 }

		 index = 0 ;
		 while (temp>0)
		 {
			  quot = temp/10 ;
			  rem = temp - quot*10 ;
			  tempStr[index++] = EBCDIC_ZERO+rem ;
			  temp = quot ; 
		 }

		 /* reverse the string */
		 //memory released by the calling function
		 ebcdicStr = new unsigned char[index+1] ;

    	  //Check if memory has been allocated
		 if (ebcdicStr == NULL)
			  return NULL ;

		 //Initialize the pointer to char with NULL
		 memset(ebcdicStr,0, index+1);
		 index-- ;
		 index2 = 0 ;
		 while (index>=0)
			  ebcdicStr[index2++] = tempStr[index--] ;
		 //ebcdicStr[index2] = '\0' ;

		 return (unsigned char *) ebcdicStr ;
	}


	/****************************************************************************
	Function : uint2ebcdic_pad
	Desc     : convert an unsigned integer to an ebcdic character string with
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
	****************************************************************************/
	unsigned char* CharUtility::uint2ebcdic_pad(unsigned int i, unsigned int size)
	{
		 unsigned char tempStr[22] ;          /* sufficient for 64 bits */ 
		 unsigned char *ebcdicStr = NULL;
		 unsigned int temp ;                              /* local copy of i */
		 unsigned int index, index2;
		 int rem, quot ;

		 index = 0 ;
		 temp = i ;
		 if (temp==0)
		 {
			  tempStr[0] = EBCDIC_ZERO ;
			  index = 1 ;
		 }
		 else
		 {
			  while (temp>0)
			  {
				   quot = temp/10 ;
				   rem = temp - quot*10 ;
				   tempStr[index++] = EBCDIC_ZERO+rem ;
				   temp = quot ; 
			  }
		 } /* if temp==0 */

		 /* reverse the string */
		 //memory released by the calling function
		 ebcdicStr = new unsigned char[(((size>index)?size:index)+1) ];

		  //Check if memory has been allocated
		 if (ebcdicStr == NULL)
			  return NULL ;

		 //Initialize the pointer to char with NULL
		 memset(ebcdicStr,0, (((size>index)?size:index)+1));
		 /* initial padding */
		 index2 = 0 ;
		 while (index2 < (size-index))
			  ebcdicStr[index2++] = EBCDIC_ZERO ;
		 /* actual data */
		 index-- ;
		 while (index>=0)
			  ebcdicStr[index2++] = tempStr[index--] ;
		// ebcdicStr[index2] = '\0' ;

		 return (unsigned char *) ebcdicStr ;
	}

	/***********************************************************************
	Function : createErrMessage
	Desc     : Creates final error message by appending the bit position at 
			   which the error is raised to the original error message raised 
			   at the point where error is raised.
	Input    : int (BitPosition), char* (Original error message).
	Returns  : char* (Final error message). 
	
	*************************************************************************/

	char* CharUtility::createErrMessage(int bitPosition, char* errMsg)
	{
		//convert the bitPosition which is an integer to string
		//Required to create error message.
		//memory released at the end of the function
		char* bit = NULL;
		bit = (char*)itoa_pad((unsigned int)bitPosition,3);

		//Check if the memory has been allocated
		if(bit != NULL)
		{
			//new error message to be appended to the existing message
			char bitPosMsg[25] = "Bit position #";
			strcat(bitPosMsg, bit);
			strcat(bitPosMsg, ": ");
			strcat(bitPosMsg, "\0");

			//delete the memory allocated for bit
			delete bit;

			//pointer to the new error message array
			//Memory released by the calling function
			char* newErrMsg = NULL;
			newErrMsg = new char[strlen(bitPosMsg) + strlen(errMsg) + 1];
			
			//Check if the memory has been allocated
			if(newErrMsg != NULL)
			{
				//Initialize the pointer to char with NULL
				memset(newErrMsg,0, strlen(bitPosMsg) + strlen(errMsg) + 1);
				//copy the bit position message to the new message
				strcpy(newErrMsg, bitPosMsg);
				//append the already existing message
				strcat(newErrMsg, errMsg);
				//add a null character in the end
				strcat(newErrMsg, "\0");

				return newErrMsg;
			}
			else
				return newErrMsg;
				
		}
		else
			return bit;
		
	}

	bool CharUtility::UnpackBCD(unsigned char* buf, int len, unsigned char* retbuf, int expected_len)
	{
		if (len <= 0)
			return false;

		if (retbuf == 0)
			return false;
		int check_len = len * 2;

		if ((expected_len != check_len) && (expected_len != (check_len - 1)))
			return false;

		bool odd = expected_len % 2;
		unsigned char *p = buf;
		unsigned char *q = retbuf;
		for (int i=0; i < len; i++)
		{
			*q = ((*p & 0xf0) >> 4) + 0x30;
			if (odd && (i == 0) && (*q == 0x30))
				; // Ignore the first character as it's zero
			else
				q++;

			*q = (*p & 0xf) + 0x30;
			q++, p++;
		}
		return true;
	}

	size_t CharUtility::toPackedBCDInplace(unsigned char *buf, int dataLen)
	{
		unsigned char* p = buf;
		size_t packed_size(0);

		if (dataLen <= 0)
			return 0;

		size_t start(0);
		if (dataLen % 2) // ie If an odd number, add a 0 at the front
		{
			start = 1;
			*p = (buf[0] & 0xf);
			packed_size++;
			p++;
		}
		for (size_t i=start; i < dataLen; i += 2)
		{
			*p = ((buf[i] & 0xf) << 4) + (buf[i+1] & 0xf);
			packed_size++;
			p++;
		}
		return packed_size;
	}

	size_t CharUtility::PackedBCDSize(size_t dataLen)
	{
		if (dataLen > 0)
			return (dataLen/2) + (dataLen % 2);
		else
			return 0;
	}

	/* end of file */



