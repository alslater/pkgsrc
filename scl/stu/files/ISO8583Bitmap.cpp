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
*       ISO8583Bitmap.h
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

//Package specific header files
#include "Enumerations.h"
#include "ISO8583Bitmap.h"
#include "CharUtility.h"

using namespace std;

extern int gTrace;
extern int gDebug;

ISO8583Bitmap::ISO8583Bitmap ()
{
	int mode = BITMAP_MODE_STANDARD;

	if (gDebug)
	   cout << "ISO8583Bitmap::ISO8583Bitmap() - mode: " << mode << "." << endl;

	m_bitmap = NULL;
	m_bitmapLen = 0;

	setMode (mode);

	init ();

	return;
}

ISO8583Bitmap::ISO8583Bitmap (int mode)
{
	if (! mode)
	   mode = BITMAP_MODE_STANDARD;

	if (gDebug)
	   cout << "ISO8583Bitmap::ISO8583Bitmap(int) - mode: " << mode << "." << endl;

	m_bitmap = NULL;
	m_bitmapLen = 0;

	setMode (mode);

	init ();

	return;
}

ISO8583Bitmap::ISO8583Bitmap (unsigned char *buf, size_t bufLen)
{
	int mode = BITMAP_MODE_STANDARD;

	if (gDebug)
	   cout << "ISO8583Bitmap::ISO8583Bitmap(buf,bufLen) - mode: " << mode << "." << endl;

	m_bitmap = NULL;
	m_bitmapLen = 0;

	setMode (mode);

	init ();

	deSerialize (buf, bufLen);

	return;
}

void ISO8583Bitmap::init (void)
{
	if (gDebug)
	   cout << "ISO8583Bitmap::init() invoked." << endl;

	if (m_bitmap != NULL)
	{
	   delete [] m_bitmap;
	   m_bitmap = NULL;
	}

	if (m_bitmap == NULL)
	{
	   m_bitmap = new unsigned long [m_bitmapLen + 1];

	   if (m_bitmap != NULL)
	   {
		  int i;
		  for (i = 0; i < m_bitmapLen + 1; i++)
		  {
		     m_bitmap[i] = 0;
		  }
	   }
	}

	return;
}

ISO8583Bitmap::~ISO8583Bitmap ()
{
	if (gDebug)
	   cout << "ISO8583Bitmap::~ISO8583Bitmap() invoked." << endl;

	if (m_bitmap != NULL)
	{
	   delete [] m_bitmap;
	   m_bitmap = NULL;
	}

	return;
}

void ISO8583Bitmap::setMode (int mode)
{
	if (gDebug)
	   cout << "ISO8583Bitmap::setMode() - mode: " << mode << "." << endl;

	m_mode = mode;

	setBitmapLen ((m_mode == BITMAP_MODE_STANDARD) ? 8 : 16);

	return;
}

int ISO8583Bitmap::getMode (void)
{
	if (gDebug)
	   cout << "ISO8583Bitmap::getMode() - mode: " << m_mode << "." << endl;

	return m_mode;
}

void ISO8583Bitmap::setBitmapLen (size_t bitmapLen)
{
	if (gDebug)
	   cout << "ISO8583Bitmap::setBitmapLen() - bitmapLen: " << bitmapLen << "." << endl;

	m_bitmapLen = bitmapLen;

	return;
}

size_t ISO8583Bitmap::getBitmapLen (void)
{
	if (gDebug)
	   cout << "ISO8583Bitmap::getBitmapLen() - bitmapLen: " << m_bitmapLen << "." << endl;

	return m_bitmapLen;
}

void ISO8583Bitmap::setBit (int bitPosition)
{
	int byteIndex = 0;   /* 0 thru 7, byte that the bitPosition is in */
	int bitIndex = 0;    /* 0 thru 7, bit in the byte that bitPosition corr. to */
	int shifts = 0;      /* the bitIndex should actually be counted from the
	                     beginning of the byte, so we need to shift it */

	bitPosition-- ; /* change from 1-64 to 0-63 or 1-128 to 0-127 */

	if (gDebug)
	   cout << "ISO8583Bitmap::setBit() - BP: " << (bitPosition+1) << "." << endl;

	if ((bitPosition < 0)
	 || (bitPosition > (BITMAP_MODE_EXTENDED - 1)))
	{
	   return;
	}

	if (bitPosition > (BITMAP_MODE_STANDARD - 1))
	{
	   byteIndex = ((bitPosition - BITMAP_MODE_STANDARD) / 8);
	   bitIndex  = (bitPosition - BITMAP_MODE_STANDARD) - (8 * byteIndex);
	}
	else
	{
	   byteIndex = (bitPosition / 8);
	   bitIndex  = bitPosition - (8 * byteIndex);
	}

	shifts = 7 - bitIndex; /* since we start from the "wrong" end */

	if (gDebug)
	   cout << "ISO8583Bitmap::setBit() - byteIndex: " << byteIndex << " bitIndex: " << bitIndex << " shifts: " << shifts << "." << endl;

	/*
	eg : bitPosition 23 will become byteIndex 2, bitIndex 6, shifts = 1 
	*/
	if (bitPosition > (BITMAP_MODE_STANDARD - 1))
	   m_bitmap[byteIndex+8] |= (1<<shifts);
	else
	   m_bitmap[byteIndex] |= (1<<shifts);
    
	return;
}

void ISO8583Bitmap::bitUnset (int bitPosition)
{
	int byteIndex = 0;   /* 0 thru 7, byte that the bitPosition is in */
	int bitIndex = 0;    /* 0 thru 7, bit in the byte that bitPosition corr. to */
	int shifts = 0;      /* the bitIndex should actually be counted from the
	                     beginning of the byte, so we need to shift it */

	bitPosition-- ; /* change from 1-64 to 0-63 or 1-128 to 0-127 */

	if (gDebug)
	   cout << "ISO8583Bitmap::bitUnset() - BP: " << (bitPosition+1) << "." << endl;

	if ((bitPosition < 0)
	 || (bitPosition > (BITMAP_MODE_EXTENDED - 1)))
	{
	   return;
	}

	if (bitPosition > (BITMAP_MODE_STANDARD - 1))
	{
	   byteIndex = ((bitPosition - BITMAP_MODE_STANDARD) / 8);
	   bitIndex  = (bitPosition - BITMAP_MODE_STANDARD) - (8 * byteIndex);
	}
	else
	{
	   byteIndex = (bitPosition / 8);
	   bitIndex  = bitPosition - (8 * byteIndex);
	}

	shifts = 7 - bitIndex; /* since we start from the "wrong" end */

	if (gDebug)
	   cout << "ISO8583Bitmap::bitUnset() - byteIndex: " << byteIndex << " bitIndex: " << bitIndex << " shifts: " << shifts << "." << endl;

	if (bitPosition > (BITMAP_MODE_STANDARD - 1))
	   m_bitmap[byteIndex+8] &= (~(1<<shifts));
	else
       m_bitmap[byteIndex] &= (~(1<<shifts));

	return;
}

bool ISO8583Bitmap::isBitSet (int bitPosition)
{
	int byteIndex = 0;   /* 0 thru 7, byte that the bitPosition is in */
	int bitIndex = 0;    /* 0 thru 7, bit in the byte that bitPosition corr. to */
	int shifts = 0;      /* the bitIndex should actually be counted from the
	                     beginning of the byte, so we need to shift it */

	int temp = 0;

	bitPosition-- ; /* change from 1-64 to 0-63 or 1-128 to 0-127 */

	if (gDebug)
	   cout << "ISO8583Bitmap::isBitSet() - BP: " << (bitPosition+1) << "." << endl;

	if ((bitPosition < 0)
	 || (bitPosition > (BITMAP_MODE_EXTENDED - 1)))
	{
	   return false;
	}

	if (bitPosition > (BITMAP_MODE_STANDARD - 1))
	{
	   byteIndex = ((bitPosition - BITMAP_MODE_STANDARD) / 8);
	   bitIndex  = (bitPosition - BITMAP_MODE_STANDARD) - (8 * byteIndex);
	}
	else
	{
	   byteIndex = (bitPosition / 8);
	   bitIndex  = bitPosition - (8 * byteIndex);
	}

	shifts = 7 - bitIndex; /* since we start from the "wrong" end */

	if (gDebug)
	   cout << "ISO8583Bitmap::isBitSet() - byteIndex: " << byteIndex << " bitIndex: " << bitIndex << " shifts: " << shifts << "." << endl;

	if (bitPosition > (BITMAP_MODE_STANDARD - 1))
	   temp = m_bitmap[byteIndex+8] & (1<<shifts);
	else
	   temp = m_bitmap[byteIndex] & (1<<shifts);

	if (temp)
		return true;
	else
		return false;
}

void ISO8583Bitmap::print (void)
{
	int i;
	int bitmapLen = getBitmapLen ();

	if (gDebug)
	{
	   for (i = 0; i < (int)(bitmapLen); i++)
	   {
	      cout << m_bitmap[i];
	   }

	   cout << endl;
	}

	return;
}

bool ISO8583Bitmap::setBitmap (unsigned char *bitmap, size_t bitmapLen)
{
	if (m_bitmap != NULL)
	{
	   memcpy (m_bitmap, bitmap, bitmapLen);

	   setBitmapLen (bitmapLen);
	}

	return true;
}

unsigned char *ISO8583Bitmap::getBitmap (size_t *bitmapLen)
{
	*bitmapLen = getBitmapLen ();

	return (unsigned char *)m_bitmap;
}

ISO8583Bitmap *ISO8583Bitmap::clone (void)
{
	size_t bitmapSize = 0;
	size_t numberOfBitPositions = 0;
	ISO8583Bitmap *newBitmap = NULL;
	unsigned char *tmpBitmap = NULL;
	size_t tmpBitmapLen = 0;

	if (gDebug)
	   cout << "ISO8583Bitmap::clone() invoked." << endl;

	numberOfBitPositions = getMode ();

	bitmapSize = (numberOfBitPositions == BITMAP_MODE_STANDARD) ? 8 : 16;

	newBitmap = new ISO8583Bitmap (numberOfBitPositions);

	if (newBitmap != NULL)
	{
	   newBitmap->setMode (numberOfBitPositions);

	   tmpBitmap = getBitmap (&tmpBitmapLen);

	   if (tmpBitmap != NULL)
	   {
	      newBitmap->setBitmap (tmpBitmap, tmpBitmapLen);
	   }
	}

	return newBitmap;
}

void ISO8583Bitmap::serialize (unsigned char *buf, size_t *bufLen)
{
	size_t length = 0;

	if (gDebug)
	   cout << "ISO8583Bitmap::serialize() invoked." << endl;
	
	*bufLen = 0;

	length = (getMode () == BITMAP_MODE_STANDARD) ? 8 : 16;

	if (m_bitmap != NULL)
	{
	   int i;
	   for (i = 0; i < (int)length; i++)
	   {
		  buf[i] = m_bitmap[i];
	   }

	   *bufLen = length;
	}

	return;
}

void ISO8583Bitmap::deSerialize (unsigned char *buf, size_t bufLen)
{
	if (gDebug)
       cout << "ISO8583Bitmap::deSerialize() invoked." << endl;
	
	if (m_bitmap != NULL)
	{
	   if (bufLen != 8 && bufLen != 16)
	      return;

	   int i;
	   for (i = 0; i < (int)bufLen; i++)
	   {
	      m_bitmap[i] = buf[i];
	   }

	   setBitmapLen (bufLen);
	}

	return;
}
