#include "STU_platform.h"

/* C code produced by gperf version 2.5 (GNU C++ version) */
/* Command-line: gperf -a -C -K code -n -S 1 -D -H isoCountryHash -N isoCountryIsValid isocountryhash.gperf  */

#include <string.h>

#define TOTAL_KEYWORDS 237
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 3
#define MIN_HASH_VALUE 0
#define MAX_HASH_VALUE 98
/* maximum key range = 99, duplicates = 194 */

static unsigned int
isoCountryHash (register const char *str, register int len)
{
  static const unsigned char asso_values[] =
    {
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 20, 45,
      6, 41,  0, 17, 15, 57,  7, 60, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99, 99, 99,
     99, 99, 99, 99, 99, 99, 99, 99,
    };
  return asso_values[str[len - 1]] + asso_values[str[0]];
}

LINKDLL char *
isoCountryIsValid (register char *str, register int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = isoCountryHash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
            {
              char *resword; 

              switch (key)
                {
                case   0:
                  resword = "404";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "484";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "474";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "454";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "434";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "414";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   6:
                  resword = "204";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "492";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "462";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "442";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "422";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "254";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "234";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "214";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case   7:
                  resword = "854";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "894";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "804";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "834";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "498";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "478";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "458";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "438";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "428";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "418";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "408";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  12:
                  resword = "262";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "292";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "242";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "232";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "222";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "212";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  13:
                  resword = "208";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "862";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "882";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "288";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "268";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "258";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "238";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "218";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  14:
                  resword = "818";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "858";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  15:
                  resword = "624";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "694";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "674";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "654";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "634";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "604";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "496";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "466";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "446";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "426";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  17:
                  resword = "584";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "574";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "554";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "524";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "504";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  20:
                  resword = "004";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "480";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "470";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "450";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "440";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "430";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "410";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "400";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "074";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "064";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "084";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "044";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "024";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  21:
                  resword = "226";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "682";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "662";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "642";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "612";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "296";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "276";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "266";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "246";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  22:
                  resword = "608";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "876";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "826";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "678";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "638";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  23:
                  resword = "562";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "512";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  24:
                  resword = "508";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "548";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "598";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "578";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "558";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "528";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  26:
                  resword = "012";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "270";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "260";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "250";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "092";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "072";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "052";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "032";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  27:
                  resword = "008";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "850";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "860";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "840";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "800";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "068";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "048";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "028";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  30:
                  resword = "626";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "686";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "666";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "646";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "616";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  32:
                  resword = "516";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "586";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "566";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  34:
                  resword = "585"; break;
                case  35:
                  resword = "016";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "690";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "670";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "630";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "620";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "600";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "096";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "086";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "076";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "056";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "036";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "660";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  37:
                  resword = "500";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "580";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "570";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "540";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "530";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "520";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  40:
                  resword = "020";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "090";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "070";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "060";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "050";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "040";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "010";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  41:
                  resword = "384";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "364";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "344";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "334";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "324";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "304";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  45:
                  resword = "124";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "144";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "104";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "184";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "174";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  47:
                  resword = "203";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "392";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "372";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "352";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "332";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "312";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "233";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  48:
                  resword = "308";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "398";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "388";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "368";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "348";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "328";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  51:
                  resword = "112";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "231";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "192";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "162";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "152";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "132";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  52:
                  resword = "108";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "891";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "158";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "188";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "178";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "148";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  56:
                  resword = "316";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "336";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "643";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "376";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "356";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  57:
                  resword = "417";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "704";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "784";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "764";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "744";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "724";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  58:
                  resword = "533";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "583";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  60:
                  resword = "116";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "196";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "166";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "156";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "136";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  61:
                  resword = "300";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "380";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "360";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "340";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "320";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  62:
                  resword = "175";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "581";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "591";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  63:
                  resword = "702";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "732";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "792";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "772";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "762";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "752";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  64:
                  resword = "748";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "887";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "798";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "788";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "768";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  65:
                  resword = "031";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "180";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "170";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "140";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "120";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "100";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  66:
                  resword = "249";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "239";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  72:
                  resword = "706";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "716";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "796";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "776";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "756";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "736";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  74:
                  resword = "705";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "795";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  75:
                  resword = "659"; break;
                case  77:
                  resword = "710";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "780";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "760";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  resword = "740";
                  if (*str == *resword && !strcmp (str + 1, resword + 1)) return resword;
                  return 0;
                case  90:
                  resword = "191"; break;
                case  98:
                  resword = "703"; break;
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
