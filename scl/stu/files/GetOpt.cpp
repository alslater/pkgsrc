
#include "GetOpt.h"

extern "C" void hex_dump (unsigned char *buf, long buflen);

/*
 * Global data
 */
int   opterr = 1;	/* if error message should be printed */
int   optind = 1;	/* index into parent argv vector */
int   optopt;		/* character checked for validity */
char *optarg;		/* argument associated with option */

/*
 * getopt
 *
 * An implementation of the Unix getopt() function. Please
 * consult the Unix manual pages for a description of the
 * function's operation.
 */
int getopt (int nargc, char *CONST *nargv, CONST char *ostr)
{
	static char	*place = EMSG;
	register const char	*oli;

	if (! *place)
	{
	   if ((optind >= nargc)
		|| (*(place = nargv[optind]) != '-')
		|| (! *++place))
	   {
	      return (EOF);
	   }
		
	   if (*place == '-')
	   {
	      ++optind;
	      return (EOF);
	   }
	}

	if (((optopt = (int)*place++) == (int)':')
	 || (! (oli = strchr (ostr, optopt))))
	{
	   if (! *place)
	      ++optind;

	   tell (": illegal option -- ");
	}
	
	if (*++oli != ':')
	{
	   optarg = NULL;

	   if (! *place)
	      ++optind;
	}
	else
	{
	   if (*place)
	   {
		  optarg = place;
	   }
	   else if (nargc <= ++optind)
	   {
		  place = EMSG;
		  tell (": option requires an argument -- ");
	   }
	   else
	   {
	      optarg = nargv[optind];
	   }

	   place = EMSG;
	   ++optind;
	}

	return (optopt);
}

