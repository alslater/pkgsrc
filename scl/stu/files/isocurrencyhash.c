#include "STU_platform.h"

/* C code produced by gperf version 2.7.2 */
/* Command-line: gperf -a -C -K code -n -D -S 1 -T -t -p -H isoCurrencyHash -N isoCurrencyLookup isocurrencyhash.gperf  */
#include <string.h>
#include "ISOMessage.h"

#define TOTAL_KEYWORDS 334
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 3
#define MIN_HASH_VALUE 0
#define MAX_HASH_VALUE 510
/* maximum key range = 511, duplicates = 177 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
isoCurrencyHash (str, len)
     register const char *str;
     register unsigned int len;
{
  static const unsigned short asso_values[] =
    {
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511,   0,  59,
       10, 200,  15,   3, 120,  29,  50,  84, 511, 511,
      511, 511, 511, 511, 511,  45, 245, 159, 255, 114,
      194, 234, 190, 134,  70,  94,  23, 189, 209,  35,
      140,  10, 214,  80, 115, 155,  20,  65, 150,   5,
      215, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511, 511, 511, 511, 511,
      511, 511, 511, 511, 511, 511
    };
  return asso_values[(unsigned char)str[len - 1]] + asso_values[(unsigned char)str[0]];
}

#ifdef __GNUC__
__inline
#endif
LINKDLL const struct IsoCurrencyCode_t *
isoCurrencyLookup (str, len)
     register const char *str;
     register unsigned int len;
{
  static const struct IsoCurrencyCode_t wordlist[] =
    {
      {"020", 0},
      {"090", 2},
      {"060", 2},
      {"050", 2},
      {"040", 2},
      {"590", 2},
      {"012", 2},
      {"280", 2},
      {"270", 2},
      {"250", 2},
      {"230", 2},
      {"200", 2},
      {"072", 2},
      {"052", 2},
      {"032", 2},
      {"512", 3},
      {"532", 2},
      {"004", 0},
      {"480", 2},
      {"470", 2},
      {"450", 0},
      {"430", 2},
      {"410", 0},
      {"400", 3},
      {"084", 2},
      {"064", 2},
      {"044", 2},
      {"024", 0},
      {"504", 2},
      {"554", 2},
      {"524", 2},
      {"222", 2},
      {"292", 2},
      {"262", 0},
      {"242", 2},
      {"214", 2},
      {"462", 2},
      {"442", 0},
      {"422", 2},
      {"710", 2},
      {"780", 2},
      {"760", 2},
      {"740", 2},
      {"720", 3},
      {"404", 2},
      {"484", 0},
      {"454", 2},
      {"434", 3},
      {"414", 3},
      {"702", 2},
      {"792", 2},
      {"752", 2},
      {"VUV", 0},
      {"704", 2},
      {"784", 2},
      {"764", 2},
      {"724", 0},
      {"LSL", 2},
      {"LUL", 0},
      {"008", 2},
      {"890", 0},
      {"840", 2},
      {"810", 2},
      {"800", 2},
      {"068", 2},
      {"048", 3},
      {"508", 2},
      {"598", 2},
      {"578", 2},
      {"558", 2},
      {"548", 0},
      {"528", 2},
      {"100", 2},
      {"180", 2},
      {"170", 2},
      {"208", 2},
      {"882", 2},
      {"862", 2},
      {"288", 2},
      {"278", 2},
      {"238", 2},
      {"218", 2},
      {"408", 2},
      {"894", 2},
      {"834", 2},
      {"458", 2},
      {"418", 0},
      {"ALL", 2},
      {"132", 2},
      {"192", 2},
      {"152", 2},
      {"104", 2},
      {"174", 0},
      {"144", 2},
      {"124", 2},
      {"JPY", 0},
      {"748", 2},
      {"788", 3},
      {"950", 0},
      {"990", 2},
      {"995", 0},
      {"ARA", 2},
      {"952", 0},
      {"992", 0},
      {"954", 2},
      {"818", 3},
      {"858", 2},
      {"SLL", 2},
      {"SZL", 2},
      {"108", 0},
      {"188", 2},
      {"997", 2},
      {"LAK", 0},
      {"036", 2},
      {"690", 2},
      {"620", 0},
      {"600", 0},
      {"096", 2},
      {"076", 2},
      {"056", 0},
      {"566", 2},
      {"586", 2},
      {"ATS", 2},
      {"246", 2},
      {"682", 2},
      {"642", 2},
      {"978", 2},
      {"998", 2},
      {"988", 0},
      {"426", 2},
      {"694", 2},
      {"654", 2},
      {"634", 2},
      {"624", 2},
      {"604", 2},
      {"496", 2},
      {"446", 2},
      {"TRL", 2},
      {"AOK", 0},
      {"901", 2},
      {"991", 2},
      {"951", 2},
      {"706", 2},
      {"776", 2},
      {"756", 2},
      {"736", 2},
      {"716", 2},
      {"ITL", 0},
      {"KPW", 2},
      {"KRW", 0},
      {"SOS", 2},
      {"LBP", 2},
      {"CNY", 2},
      {"989", 0},
      {"608", 2},
      {"886", 2},
      {"826", 2},
      {"678", 0},
      {"KES", 2},
      {"SEK", 2},
      {"116", 2},
      {"196", 2},
      {"156", 2},
      {"136", 2},
      {"WST", 2},
      {"LUC", 0},
      {"ADP", 0},
      {"ECS", 2},
      {"TZS", 2},
      {"300", 0},
      {"380", 0},
      {"360", 2},
      {"340", 2},
      {"320", 2},
      {"533", 0},
      {"332", 2},
      {"392", 0},
      {"372", 2},
      {"352", 0},
      {"MTL", 2},
      {"HNL", 2},
      {"ILS", 2},
      {"324", 0},
      {"364", 2},
      {"344", 2},
      {"LUF", 0},
      {"YER", 2},
      {"SDP", 2},
      {"SYP", 2},
      {"SHP", 2},
      {"QAR", 2},
      {"ISK", 0},
      {"TPE", 0},
      {"PGK", 2},
      {"UGS", 2},
      {"USS", 2},
      {"LKR", 2},
      {"ROL", 2},
      {"ZAL", 2},
      {"SVC", 2},
      {"616", 2},
      {"646", 0},
      {"626", 0},
      {"GTQ", 2},
      {"OMR", 3},
      {"328", 2},
      {"388", 2},
      {"348", 2},
      {"CSK", 2},
      {"EGP", 3},
      {"PTE", 0},
      {"ESP", 0},
      {"TOP", 2},
      {"YDD", 3},
      {"YUD", 0},
      {"VEB", 2},
      {"BEL", 0},
      {"BGL", 2},
      {"ECU", 2},
      {"CVE", 2},
      {"IEP", 2},
      {"PEI", 2},
      {"VND", 2},
      {"LRD", 2},
      {"LYD", 3},
      {"ANG", 2},
      {"AWG", 0},
      {"PHP", 2},
      {"MWK", 2},
      {"953", 0},
      {"993", 0},
      {"KMF", 0},
      {"SAR", 2},
      {"SUR", 2},
      {"SCR", 2},
      {"UYP", 2},
      {"CLP", 2},
      {"CYP", 2},
      {"CUP", 2},
      {"COP", 2},
      {"AED", 2},
      {"AUD", 2},
      {"NOK", 2},
      {"MNT", 2},
      {"XEU", 2},
      {"KHR", 2},
      {"ZMK", 2},
      {"SRG", 2},
      {"CRC", 2},
      {"356", 2},
      {"376", 2},
      {"JMD", 2},
      {"JOD", 3},
      {"EUR", 2},
      {"MOP", 2},
      {"MXP", 0},
      {"FKP", 2},
      {"SBD", 2},
      {"STD", 0},
      {"SGD", 2},
      {"BUK", 2},
      {"XAF", 0},
      {"XPF", 0},
      {"XOF", 0},
      {"IDR", 2},
      {"IRR", 2},
      {"INR", 2},
      {"DKK", 2},
      {"KYD", 2},
      {"KWD", 3},
      {"CHF", 2},
      {"CLF", 2},
      {"PKR", 2},
      {"PLZ", 2},
      {"ESB", 0},
      {"ETB", 2},
      {"BDT", 2},
      {"THB", 2},
      {"USN", 2},
      {"NIC", 2},
      {"TND", 3},
      {"TWD", 2},
      {"TTD", 2},
      {"GBP", 2},
      {"PYG", 0},
      {"GWP", 2},
      {"GIP", 2},
      {"MZM", 2},
      {"FIM", 2},
      {"MGF", 0},
      {"HUF", 2},
      {"BWP", 2},
      {"PAB", 2},
      {"FRF", 2},
      {"GHC", 2},
      {"DOP", 2},
      {"MXN", 2},
      {"MUR", 2},
      {"MYR", 2},
      {"MVR", 2},
      {"BEC", 0},
      {"BRC", 2},
      {"XCD", 2},
      {"RWF", 0},
      {"USD", 2},
      {"CAD", 2},
      {"NGN", 2},
      {"NPR", 2},
      {"HTG", 2},
      {"GNF", 0},
      {"ZAR", 2},
      {"ZRZ", 2},
      {"BEF", 0},
      {"BIF", 0},
      {"NLG", 2},
      {"DDM", 2},
      {"MAD", 2},
      {"DEM", 2},
      {"HKD", 2},
      {"DJF", 0},
      {"FJD", 2},
      {"BTN", 2},
      {"NZD", 2},
      {"GMD", 2},
      {"GYD", 2},
      {"GRD", 0},
      {"BOB", 2},
      {"BBD", 2},
      {"BZD", 2},
      {"BSD", 2},
      {"BND", 2},
      {"BMD", 2},
      {"BHD", 3},
      {"DZD", 2}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = isoCurrencyHash (str, len);

      if (key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE)
        {
          register const struct IsoCurrencyCode_t *wordptr;
          register const struct IsoCurrencyCode_t *wordendptr;
          register const struct IsoCurrencyCode_t *resword;

          switch (key)
            {
              case 0:
                wordptr = &wordlist[0];
                wordendptr = wordptr + 5;
                goto multicompare;
              case 3:
                resword = &wordlist[5];
                goto compare;
              case 10:
                wordptr = &wordlist[6];
                wordendptr = wordptr + 9;
                goto multicompare;
              case 13:
                wordptr = &wordlist[15];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 15:
                wordptr = &wordlist[17];
                wordendptr = wordptr + 11;
                goto multicompare;
              case 18:
                wordptr = &wordlist[28];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 20:
                wordptr = &wordlist[31];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 25:
                wordptr = &wordlist[35];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 29:
                wordptr = &wordlist[39];
                wordendptr = wordptr + 5;
                goto multicompare;
              case 30:
                wordptr = &wordlist[44];
                wordendptr = wordptr + 5;
                goto multicompare;
              case 39:
                wordptr = &wordlist[49];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 40:
                resword = &wordlist[52];
                goto compare;
              case 44:
                wordptr = &wordlist[53];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 46:
                wordptr = &wordlist[57];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 50:
                wordptr = &wordlist[59];
                wordendptr = wordptr + 7;
                goto multicompare;
              case 53:
                wordptr = &wordlist[66];
                wordendptr = wordptr + 6;
                goto multicompare;
              case 59:
                wordptr = &wordlist[72];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 60:
                wordptr = &wordlist[75];
                wordendptr = wordptr + 7;
                goto multicompare;
              case 65:
                wordptr = &wordlist[82];
                wordendptr = wordptr + 5;
                goto multicompare;
              case 68:
                resword = &wordlist[87];
                goto compare;
              case 69:
                wordptr = &wordlist[88];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 74:
                wordptr = &wordlist[91];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 75:
                resword = &wordlist[95];
                goto compare;
              case 79:
                wordptr = &wordlist[96];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 84:
                wordptr = &wordlist[98];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 87:
                resword = &wordlist[100];
                goto compare;
              case 90:
                resword = &wordlist[101];
                goto compare;
              case 94:
                wordptr = &wordlist[102];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 99:
                resword = &wordlist[104];
                goto compare;
              case 100:
                wordptr = &wordlist[105];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 103:
                wordptr = &wordlist[107];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 109:
                wordptr = &wordlist[109];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 113:
                resword = &wordlist[111];
                goto compare;
              case 117:
                resword = &wordlist[112];
                goto compare;
              case 120:
                wordptr = &wordlist[113];
                wordendptr = wordptr + 7;
                goto multicompare;
              case 123:
                wordptr = &wordlist[120];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 125:
                resword = &wordlist[122];
                goto compare;
              case 130:
                wordptr = &wordlist[123];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 134:
                wordptr = &wordlist[126];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 135:
                wordptr = &wordlist[129];
                wordendptr = wordptr + 8;
                goto multicompare;
              case 138:
                resword = &wordlist[137];
                goto compare;
              case 139:
                resword = &wordlist[138];
                goto compare;
              case 143:
                wordptr = &wordlist[139];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 149:
                wordptr = &wordlist[142];
                wordendptr = wordptr + 5;
                goto multicompare;
              case 157:
                resword = &wordlist[147];
                goto compare;
              case 159:
                wordptr = &wordlist[148];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 160:
                resword = &wordlist[150];
                goto compare;
              case 163:
                resword = &wordlist[151];
                goto compare;
              case 164:
                resword = &wordlist[152];
                goto compare;
              case 168:
                resword = &wordlist[153];
                goto compare;
              case 170:
                wordptr = &wordlist[154];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 174:
                wordptr = &wordlist[158];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 179:
                wordptr = &wordlist[160];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 180:
                resword = &wordlist[164];
                goto compare;
              case 182:
                resword = &wordlist[165];
                goto compare;
              case 185:
                resword = &wordlist[166];
                goto compare;
              case 194:
                resword = &wordlist[167];
                goto compare;
              case 195:
                resword = &wordlist[168];
                goto compare;
              case 200:
                wordptr = &wordlist[169];
                wordendptr = wordptr + 5;
                goto multicompare;
              case 203:
                resword = &wordlist[174];
                goto compare;
              case 210:
                wordptr = &wordlist[175];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 212:
                resword = &wordlist[179];
                goto compare;
              case 213:
                resword = &wordlist[180];
                goto compare;
              case 214:
                resword = &wordlist[181];
                goto compare;
              case 215:
                wordptr = &wordlist[182];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 217:
                resword = &wordlist[185];
                goto compare;
              case 219:
                resword = &wordlist[186];
                goto compare;
              case 220:
                wordptr = &wordlist[187];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 224:
                resword = &wordlist[190];
                goto compare;
              case 228:
                resword = &wordlist[191];
                goto compare;
              case 229:
                resword = &wordlist[192];
                goto compare;
              case 234:
                resword = &wordlist[193];
                goto compare;
              case 235:
                wordptr = &wordlist[194];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 237:
                wordptr = &wordlist[196];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 238:
                resword = &wordlist[198];
                goto compare;
              case 239:
                resword = &wordlist[199];
                goto compare;
              case 240:
                wordptr = &wordlist[200];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 244:
                resword = &wordlist[203];
                goto compare;
              case 249:
                resword = &wordlist[204];
                goto compare;
              case 250:
                wordptr = &wordlist[205];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 253:
                resword = &wordlist[208];
                goto compare;
              case 254:
                wordptr = &wordlist[209];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 255:
                resword = &wordlist[212];
                goto compare;
              case 260:
                wordptr = &wordlist[213];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 265:
                resword = &wordlist[215];
                goto compare;
              case 268:
                wordptr = &wordlist[216];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 269:
                resword = &wordlist[218];
                goto compare;
              case 273:
                resword = &wordlist[219];
                goto compare;
              case 274:
                wordptr = &wordlist[220];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 275:
                resword = &wordlist[222];
                goto compare;
              case 278:
                wordptr = &wordlist[223];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 279:
                wordptr = &wordlist[225];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 280:
                resword = &wordlist[227];
                goto compare;
              case 283:
                resword = &wordlist[228];
                goto compare;
              case 284:
                wordptr = &wordlist[229];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 288:
                resword = &wordlist[231];
                goto compare;
              case 294:
                wordptr = &wordlist[232];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 295:
                resword = &wordlist[235];
                goto compare;
              case 299:
                wordptr = &wordlist[236];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 300:
                wordptr = &wordlist[240];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 303:
                resword = &wordlist[242];
                goto compare;
              case 304:
                resword = &wordlist[243];
                goto compare;
              case 305:
                resword = &wordlist[244];
                goto compare;
              case 308:
                resword = &wordlist[245];
                goto compare;
              case 309:
                resword = &wordlist[246];
                goto compare;
              case 314:
                resword = &wordlist[247];
                goto compare;
              case 318:
                resword = &wordlist[248];
                goto compare;
              case 320:
                wordptr = &wordlist[249];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 325:
                wordptr = &wordlist[251];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 328:
                resword = &wordlist[253];
                goto compare;
              case 329:
                wordptr = &wordlist[254];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 334:
                resword = &wordlist[256];
                goto compare;
              case 335:
                wordptr = &wordlist[257];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 339:
                resword = &wordlist[260];
                goto compare;
              case 344:
                wordptr = &wordlist[261];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 348:
                wordptr = &wordlist[264];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 349:
                wordptr = &wordlist[267];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 353:
                wordptr = &wordlist[270];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 354:
                resword = &wordlist[272];
                goto compare;
              case 355:
                resword = &wordlist[273];
                goto compare;
              case 359:
                wordptr = &wordlist[274];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 360:
                wordptr = &wordlist[276];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 364:
                resword = &wordlist[278];
                goto compare;
              case 368:
                resword = &wordlist[279];
                goto compare;
              case 370:
                wordptr = &wordlist[280];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 374:
                wordptr = &wordlist[283];
                wordendptr = wordptr + 4;
                goto multicompare;
              case 378:
                resword = &wordlist[287];
                goto compare;
              case 383:
                wordptr = &wordlist[288];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 384:
                resword = &wordlist[290];
                goto compare;
              case 385:
                wordptr = &wordlist[291];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 388:
                resword = &wordlist[293];
                goto compare;
              case 393:
                resword = &wordlist[294];
                goto compare;
              case 395:
                resword = &wordlist[295];
                goto compare;
              case 398:
                resword = &wordlist[296];
                goto compare;
              case 403:
                wordptr = &wordlist[297];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 404:
                wordptr = &wordlist[300];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 405:
                resword = &wordlist[302];
                goto compare;
              case 408:
                resword = &wordlist[303];
                goto compare;
              case 410:
                resword = &wordlist[304];
                goto compare;
              case 414:
                resword = &wordlist[305];
                goto compare;
              case 418:
                resword = &wordlist[306];
                goto compare;
              case 423:
                resword = &wordlist[307];
                goto compare;
              case 424:
                resword = &wordlist[308];
                goto compare;
              case 428:
                resword = &wordlist[309];
                goto compare;
              case 429:
                resword = &wordlist[310];
                goto compare;
              case 430:
                resword = &wordlist[311];
                goto compare;
              case 439:
                wordptr = &wordlist[312];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 443:
                resword = &wordlist[314];
                goto compare;
              case 444:
                wordptr = &wordlist[315];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 445:
                resword = &wordlist[318];
                goto compare;
              case 449:
                wordptr = &wordlist[319];
                wordendptr = wordptr + 2;
                goto multicompare;
              case 454:
                resword = &wordlist[321];
                goto compare;
              case 464:
                resword = &wordlist[322];
                goto compare;
              case 489:
                wordptr = &wordlist[323];
                wordendptr = wordptr + 3;
                goto multicompare;
              case 490:
                resword = &wordlist[326];
                goto compare;
              case 500:
                wordptr = &wordlist[327];
                wordendptr = wordptr + 6;
                goto multicompare;
              case 510:
                resword = &wordlist[333];
                goto compare;
            }
          return 0;
        multicompare:
          while (wordptr < wordendptr)
            {
              register const char *s = wordptr->code;

              if (*str == *s && !strcmp (str + 1, s + 1))
                return wordptr;
              wordptr++;
            }
          return 0;
        compare:
          {
            register const char *s = resword->code;

            if (*str == *s && !strcmp (str + 1, s + 1))
              return resword;
          }
        }
    }
  return 0;
}
