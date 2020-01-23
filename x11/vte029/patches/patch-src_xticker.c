$NetBSD$

--- src/xticker.c.orig	2015-10-12 14:28:30.000000000 +0000
+++ src/xticker.c
@@ -49,6 +49,8 @@ main(int argc, char **argv)
 	long length = DEFAULT_WIDTH, delay = DEFAULT_DELAY, fd, i, j;
 	int c;
 	struct stat st;
+	extern char *optarg;
+	extern int optind;
 	char *buffer, *outbuf;
 
 	while ((c = getopt(argc, argv, "d:w:")) != -1) {
