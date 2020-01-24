/******************************************************************************
 *
 * SOURCE FILE:     base64_encoding.c
 *
 * DESCRIPTION:     Contains the API routines for encoding and decoding
 *                  base-64 character streams.
 *
 * REVISION HISTORY:
 *
 *     DATE    BY   REV  DESCRIPTION
 *   96/10/02  JRP  000  Creation
 *
 *****************************************************************************/
#ifndef BASE64_ENCODING_H
#define BASE64_ENCODING_H

#include <stdlib.h>
#include <string.h>

static unsigned char          base64Table[] =
     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
static unsigned char          asciiTable[] =
     "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
     "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
     "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x3E\x00\x00\x00\x3F"
     "\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x00\x00\x00\x00\x00\x00"
     "\x00\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E"
     "\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x00\x00\x00\x00\x00"
     "\x00\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21\x22\x23\x24\x25\x26\x27\x28"
     "\x29\x2A\x2B\x2C\x2D\x2E\x2F\x30\x31\x32\x33\x00\x00\x00\x00\x00";

/******************************************************************************
 *
 * Decodes a stream of unsigned characters that were encoded as base-64.  This
 * routine will ignore all characters not found within the Base64 Alphabet as
 * it assumes that they are line breaks or white space.
 *
 *****************************************************************************/

unsigned char *Base64Decode(size_t maxDestSize, size_t *destLen,
     unsigned char *destString, size_t sourceSize,
     unsigned char *sourceString, short *status)
{
     size_t                   idx;

     unsigned char            bitValue0;
     unsigned char            bitValue1;
     unsigned char            bitValue2;
     unsigned char            bitValue3;
     unsigned char            sourceValue2;
     unsigned char            sourceValue3;

     *status = 0;
     *destLen = 0;

     idx = 0;

     while (idx < sourceSize)
     {
          /* Three bytes of destination will be created from 4 bytes of    */
          /* source.  Each bitValue represents 6 bits of the original      */
          /* character stream.  Therefore, to build the first byte, one    */
          /* needs to concatenate the 6 bits from the first bitValue with  */
          /* the first two bites of the second bitValue.  Note that if the */
          /* source string contains an "=", the result returned from the   */
          /* asciiTable will be \x00.                                      */

          /* Ignore all characters not found within the base64 table.      */

          while (strchr(base64Table, sourceString[idx]) == NULL)
               idx++;

          bitValue0 = asciiTable[sourceString[idx++]];
          while (strchr(base64Table, sourceString[idx]) == NULL)
               idx++;

          bitValue1 = asciiTable[sourceString[idx++]];
          while (strchr(base64Table, sourceString[idx]) == NULL)
               idx++;

          sourceValue2 = sourceString[idx];
          bitValue2 = asciiTable[sourceString[idx++]];
          while (strchr(base64Table, sourceString[idx]) == NULL)
               idx++;

          sourceValue3 = sourceString[idx];
          bitValue3 = asciiTable[sourceString[idx++]];

          /* Verify that the source string has not been exceeded.  The     */
          /* total length of valid base 64 characters should be a multiple */
          /* of 4.                                                         */

          if (idx > sourceSize)
          {
               *status = -1;
               return NULL;
          }

          /* The first character is determined by the least significant    */
          /* six bits of bitValue0 concatenated to the most significant of */
          /* the six bits within bitValue1.                                */

          destString[(*destLen)++] = (bitValue0 << 2) | (bitValue1 >> 4);

          if (sourceValue2 == '=')
               return destString;

          /* The second character is determined by the least significant   */
          /* bits of bitValue1 concatenated to the 4 most significate bits */
          /* of bitValue2.                                                 */

          destString[(*destLen)++] = ((bitValue1 & 0x0F) << 4) | (bitValue2 >> 2);

          if (sourceValue3 == '=')
               return destString;

          /* The third character is determined by the last two bits within */
          /* bitValue2 concatenated with all the bits within bitValue3.    */

          destString[(*destLen)++] = ((bitValue2 & 0x03) << 6) | bitValue3;
     }

     return destString;
}

unsigned char *Base64Encode(size_t maxDestSize, size_t *destLen,
     unsigned char *destString, size_t sourceSize,
     const unsigned char *sourceString, short *status)
{
     size_t                   idx;
     unsigned char            tableIdx;

     unsigned char            byte0[1];
     unsigned char            byte1[1];
     unsigned char            byte2[1];

     *status = 0;
     *destLen = 0;

     for (idx = 0; idx < sourceSize; idx+=3)
     {
          /* Every 3 characters of source require 4 characters in Dest.    */

          if (*destLen + 4 > maxDestSize)
          {
               *status = -1;
               return NULL;
          }

          /* Set pointers to the all three bytes (byte0 alread set) for    */
          /* better readability.                                           */

          byte0[0] = sourceString[idx];
          byte1[0] = sourceString[idx + 1];
          byte2[0] = sourceString[idx + 2];

          /* Set the table index to the value of the first 6 bytes.  This  */
          /* is accomplished by right shifting all of the bits to the      */
          /* right by 2 leaving the high order 6 bits now moved to the     */
          /* low order 6 bits.                                             */

          tableIdx = *byte0 >> 2;
          destString[(*destLen)++] = base64Table[tableIdx];

          /* Set the table index to the value of the 7th to the 12th bytes */
          /* This is accomplished zeroing out the first 6 bits (with an &),*/
          /* shifting that to the left 4 bits.  The high order 4 bits of   */
          /* the next byte are shifted to the low order bits.  These two   */
          /* vales are "OR"d together.                                     */

          if (idx + 1 >= sourceSize)
          {
               tableIdx = ((*byte0 & 0x03) << 4);
               destString[(*destLen)++] = base64Table[tableIdx];

               memset(destString + *destLen, '=', 2);

               *destLen += 2;
               return destString;

          }
          else
          {
               tableIdx = ((*byte0 & 0x03) << 4) | (*byte1 >> 4);
               destString[(*destLen)++] = base64Table[tableIdx];
          }

          /* Set the table index to the value of the 13th to the 18th.     */
          /* This is accomplished by zeroing out the high order bits of    */
          /* the second byte, shifting them to the left 2 bits and then    */
          /* "OR"ing it to the two high order bits of the next byte that   */
          /* have been shifted to the low order.                           */

          if (idx + 2 >= sourceSize)
          {
               tableIdx = ((*byte1 & 0x0F) << 2);
               
               destString[(*destLen)++] = base64Table[tableIdx];
               destString[(*destLen)++] = '=';

               return destString;
          }
          else
          {
               tableIdx = ((*byte1 & 0x0F) << 2) | ((*byte2 & 0xC0) >> 6);
               destString[(*destLen)++] = base64Table[tableIdx];
          }

          /* Set the table index to the value of the 19th to the 24th.     */
          /* This is accomplished by clearing the high order two bits.     */

          tableIdx = (*byte2 & 0x3F);
          destString[(*destLen)++] = base64Table[tableIdx];
     }

     return destString;
}

#endif