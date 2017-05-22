
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "hex_dump.h"

static char hex_digs[] = "0123456789ABCDEF";

static int gBSize = 1024;
static char *gBuf = NULL;
static FILE *gFStream = NULL;
static int gBlockCount = 0;
static int gTotalRead = 0;
static int gLfCount = 0;
static int gLastLfCount = 0;

int hex_dump_file (int argc, char *argv[])
{
	int rval = 0;
	int startBlock = 0;
	register char *bp = NULL;
	char filename[1024] = "";

	if ((argc < 2) || (argc > 3))
	{       
	   return (int)-1;
	}
	else
	{
	    if (argc == 2)
		{
           strcpy (filename, argv[1]);
           startBlock = 0;
		}
		else
		{
           strcpy (filename, argv[1]);
           startBlock = atoi (argv[2]);
		}
	}

	gBuf = (unsigned char *)malloc (gBSize + 1);

	if (gBuf != NULL)
	{
       gFStream = fopen (filename, "rb");

       if (gFStream != NULL)
	   {
          while (! feof (gFStream))
          {
	         if (startBlock > 0)
			 {				
	            rval = skip_block (startBlock - 1);

				gBlockCount = startBlock;
				startBlock = 0;
			 }
	         else
			 {				 
			    gBlockCount++;
 		     }

		     display_block ();
          }

          fclose (gFStream);
		  gFStream = NULL;
       }

	   free (gBuf);
	   gBuf = NULL;
	}

	return (int)0;
}

int skip_block (int startBlock)
{
	int nRead = 0;

    while ((! feof (gFStream))
	  	   && (startBlock > 0))
    {
       nRead = fread (gBuf, sizeof (unsigned char), gBSize, gFStream);

       gTotalRead += nRead;
	   startBlock--;
	}

	if (startBlock == 0)
	   return (int)0;
	else
	   return (int)-1;
}

void display_block (void)
{
	int nRead = 0;

	memset (gBuf, 0, gBSize);

    nRead = fread (gBuf, sizeof (unsigned char), gBSize, gFStream);

    gBuf[nRead + 1] = 0;

    gTotalRead += nRead;

    hex_dump (gBuf, nRead);

	return;
}

void hex_dump (unsigned char *buf, long buflen)
{ 
	char LINE[80];
	long offset = 0L;
	long left = buflen;
	int i, upto16, x;
	unsigned char b;
	char strLfCount[7] = "";
	char strLastLfCount[7] = "";

	while (left > 0)
	{
       for (i = 0; i < 79; i++)
          LINE[i] = ' ';
       
	   LINE[79] = '\0';

       sprintf (LINE, "%08Xh", offset);

	   LINE[8] = LINE[41] = LINE[58] = '|';

       upto16 = (left > 16) ? 16 : (int)left;

       for (x = 0; x < upto16; x++)
	   {
          b = buf[offset + x];
          
		  LINE[9 + (2 * x)] = hex_dig ((b &0xf0) >> 4);
          
		  LINE[10 + (2 * x)] = hex_dig (b &0x0f);

          LINE[42 + x] = isprint (b) ? (b) : '.';

		  if (b != 10)
		  {
		     gLfCount++;
		  }
		  else
		  {
	         gLastLfCount = gLfCount;

			 gLfCount = 0;
		  }
       }

	   printf ("%s\n", LINE);

       offset += 16L;
       left -= 16L;
    }

	return;
}

static char hex_dig (int num)
{
	return num < 16 ? hex_digs[num] : '?';
}
