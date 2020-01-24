#if !defined(__ISOHASH_H_)
#define __ISOHASH_H_

/**************************************************************************
 * File Name :		ISOHash.h
 *
 * Description : 	Declarations for hash functions
 *
 * Author : 		Arun G
 *
 * See also:
 *		ISOCountryHash.c
 *		ISOCurrencyHash.c
 *		ISOMerchantTypeHash.c
 *
 * Date Created :
 *
 **************************************************************************
 */

#include "STU_platform.h"

#include "ISOMessage.h"

extern LINKDLL const char* isoMerchantTypeIsValid(const char *str, int len);
extern LINKDLL const IsoCurrencyCode* isoCurrencyLookup (const char *str, int len);
extern LINKDLL const char* isoCountryIsValid (const char *str, int len);

#endif

