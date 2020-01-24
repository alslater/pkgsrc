
#ifndef GETOPT_H
#define GETOPT_H

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifndef CONST
#	if defined(__STDC__) || defined(__cplusplus)
#		define CONST const
#	else
#		define CONST
#	endif
#endif

#define BADCH (int)'?'
#define EMSG  ""
#define tell(s)	if (opterr) {fputs(*nargv,stderr);fputs(s,stderr); \
		fputc(optopt,stderr);fputc('\n',stderr);return(BADCH);}

int getopt (int nargc, char *CONST *nargv, CONST char *ostr);

#endif

