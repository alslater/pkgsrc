/*********************************************************************
*
*   Module:
*       ISO8583Bitmap.cpp
*
*   Contents:
*       Implementation of the ISO8583Bitmap class constructor and methods
*
*   Description
*
*   This class implements a object which will encode and decode an
*   ISO8583 bitmap.
*
*   The ISO8583 format specifies a messaging format which consists of
*   sets of requests and associated responses. A request or response
*   message consists of the following parts:
*
*			4 bytes:   message type, 0-9
*     8 or 16 bytes:   message bitmap, 0-255
*           n bytes:   message field data
*
*   The message bitmap instructs the receiver which data fields have been
*   populated. Reception of a message with data field 1 set indicates that
*   the message has an extended bitmap (128 bit).
*
*   Note that requests and responses are converted to EBCDIC before being
*   transmitted over the wire (socket).
*
*   This class allows the caller to create an instance of a "Bitmap".
*   This bitmap instance can then be used to encode or decode an ISO8583
*   bit map sequence using methods such as "setBit", "getBit", "isBitSet".
*   Once the caller has called "setBit" on all the set fields in a message
*   the bitmap instance can be serialized to a byteStream by invoking
*   "serialize". Also note that a byteStream can be loaded using
*   "deSerialize" and then "isBitSet" can be called to query the bits or
*   data fields that have been set.
*
*   See Also:
*       ISO8583Bitmap.cpp
*
*
*   Created:
*		19 May 2001 Lonnie L. Filbrun
*
*   Modified:
*
*
*
**********************************************************************/
//Standard includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#ifndef _WIN32
#include <sys/types.h>
#include <sys/bitmap.h>
#endif

#include "STU_platform.h"

//Package specific header files
#ifndef ISO8583BITMAP_H
#define ISO8583BITMAP_H

#define BITMAP_MODE_STANDARD		64
#define BITMAP_MODE_EXTENDED		128

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

class LINKDLL ISO8583Bitmap
{
	private:
	   int m_mode;
	   unsigned long *m_bitmap;
	   int m_bitmapLen;

	protected:

	public:
	   ISO8583Bitmap ();
	   ISO8583Bitmap (int mode);
	   ISO8583Bitmap (unsigned char *buf, size_t bufLen);

	   void init (void);

	   ~ISO8583Bitmap ();

	   void setMode (int mode);
	   int getMode (void);

	   void setBitmapLen (size_t bitmapLen);
	   size_t getBitmapLen (void);

	   void setBit (int bitPosition);
	   void bitUnset (int bitPosition);
	   bool isBitSet (int bitPosition);

	   ISO8583Bitmap *clone (void);

	   void print (void);

	   bool setBitmap (unsigned char *bitmap, size_t bitmapLen);
	   unsigned char *getBitmap (size_t *bitmapLen);

	   void serialize (unsigned char *buf, size_t *bufLen);
	   void deSerialize (unsigned char *buf, size_t bufLen);

};

#endif

