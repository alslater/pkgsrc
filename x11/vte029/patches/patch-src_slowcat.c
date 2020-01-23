$NetBSD$

--- src/slowcat.c.orig	2015-10-12 14:28:30.000000000 +0000
+++ src/slowcat.c
@@ -81,6 +81,8 @@ main(int argc, char **argv)
 	int i, c;
 	long delay = 200000, chunksize = 1, tmp;
 	char *p;
+	extern char *optarg;
+	extern int optind;
 	GList *files = NULL, *file;
 
 	while ((c = getopt(argc, argv, "t:c:")) != -1) {
