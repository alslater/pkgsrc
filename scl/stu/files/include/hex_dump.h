
#ifndef HEX_DUMP_H
#define HEX_DUMP_H

#ifdef _WIN32
#include <windows.h>
#endif /* _WIN32 */

#include <stdio.h>
#include <ctype.h>

int hex_dump_file (int argc, char *argv[]);

int skip_block (int startBlock);
void display_block (void);

void hex_dump (unsigned char *buf, long buflen);
static char hex_dig (int num);

#endif

