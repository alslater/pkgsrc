#include "STU_platform.h"

/* C code produced by gperf version 2.5 (GNU C++ version) */
/* Command-line: gperf -a -C -K code -n -S 1 -D -H isoMerchantTypeHash -N isoMerchantTypeIsValid isomerchanttypehash.gperf  */

#include <string.h>

#define TOTAL_KEYWORDS 247
#define MIN_WORD_LENGTH 4
#define MAX_WORD_LENGTH 4
#define MIN_HASH_VALUE 0
#define MAX_HASH_VALUE 112
/* maximum key range = 113, duplicates = 203 */

static unsigned int
isoMerchantTypeHash (register const char *str, register int len)
{
  static const unsigned char asso_values[] =
    {
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113,   4,  35,
      17,   2,  32,   0,  61,  20,  25,  51, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
     113, 113, 113, 113, 113, 113, 113, 113,
    };
  return asso_values[str[len - 1]] + asso_values[str[0]];
}

LINKDLL char *
isoMerchantTypeIsValid (register char *str, register int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = isoMerchantTypeHash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
            {
              char *resword; 

              switch (key)
                {
                case    0:
                  resword = "5655";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5995";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5975";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5945";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5935";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5735";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case    2:
                  resword = "5533";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5993";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5983";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5973";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5963";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5943";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5933";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5813";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5733";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5713";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case    4:
                  resword = "5310";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5970";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5950";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5940";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case    6:
                  resword = "0763"; break;
                case    8:
                  resword = "0780"; break;
                case   17:
                  resword = "5422";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5992";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5972";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5942";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5932";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5912";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5812";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5732";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5722";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5712";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5592";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5542";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5532";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5462";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   20:
                  resword = "5697";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7995";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7535";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7395";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7295";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5997";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5977";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5947";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5937";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   21:
                  resword = "0742"; break;
                case   22:
                  resword = "7033";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7993";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7933";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7833";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7623";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7523";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7513";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7393";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7333";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7273";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   24:
                  resword = "7210";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7280";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7230";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   25:
                  resword = "5598";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8675";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5998";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5978";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5948";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5718";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5698";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   27:
                  resword = "8043"; break;
                case   29:
                  resword = "8050";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8220";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   32:
                  resword = "4215";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5994";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5974";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5944";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5814";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5734";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5714";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4225";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   35:
                  resword = "5211";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5971";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5961";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5941";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5931";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5921";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5811";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5691";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5681";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5661";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5651";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5641";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5631";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5621";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5611";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5571";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5561";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5551";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5541";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5531";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5521";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5511";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5451";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5441";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5411";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5331";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5311";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5271";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5261";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5251";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5231";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   36:
                  resword = "4900"; break;
                case   37:
                  resword = "7032";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7992";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7932";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7922";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7832";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7692";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7622";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7542";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7512";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7392";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7372";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7342";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7332";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7322";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   39:
                  resword = "1520";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "1750";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "1740";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   40:
                  resword = "7217";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7997";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7297";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7277";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   42:
                  resword = "8042";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8062";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   45:
                  resword = "7278";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7998";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7538";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7338";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7298";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   49:
                  resword = "4582";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4812";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4722";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   50:
                  resword = "8398"; break;
                case   51:
                  resword = "5399";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5999";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5949";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5719";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5699";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5599";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5499";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   52:
                  resword = "4457";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7994";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7534";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7394";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   53:
                  resword = "9223"; break;
                case   55:
                  resword = "7011";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7991";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7941";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7911";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7841";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7641";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7631";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7531";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7361";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7341";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7321";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7311";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7261";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7251";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7221";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7211";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   57:
                  resword = "4468";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8244";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8044";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   60:
                  resword = "8011";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8931";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8911";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8661";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8651";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8641";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8351";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8241";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8211";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8111";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8071";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8041";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8031";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8021";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   61:
                  resword = "5946";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5996";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "5976";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   64:
                  resword = "4214";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4814";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4784";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   65:
                  resword = "6010";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "6760";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "6300";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   67:
                  resword = "4011";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4821";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4761";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4511";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4411";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4131";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4121";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4111";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   68:
                  resword = "9222"; break;
                case   70:
                  resword = "1711";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "1771";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "1761";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "1731";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   71:
                  resword = "7279";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7999";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7929";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7699";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7629";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7549";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7519";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7399";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7389";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7349";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7339";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7299";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   76:
                  resword = "8049";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8999";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8699";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8299";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8249";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "8099";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   78:
                  resword = "6012"; break;
                case   81:
                  resword = "7216";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7996";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7296";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "7276";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   83:
                  resword = "4119";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4899";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4829";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "4789";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   86:
                  resword = "1799";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "9411";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "9401";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "9311";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "9211";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   96:
                  resword = "6011";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "6611";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "6381";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "6211";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "6051";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  102:
                  resword = "9399"; break;
                case  112:
                  resword = "6399"; break;
                default: return 0;
                }
              if (*str == *resword && !strcmp (str + 1, resword + 1))
                return resword;
              return 0;
            }
         }
    }
  return 0;
}
