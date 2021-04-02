$NetBSD$

--- base/stdpre.h.orig	2019-10-15 09:05:37.000000000 +0000
+++ base/stdpre.h
@@ -31,7 +31,7 @@ typedef struct gp_file_s gp_file;
 /* if we define _LARGEFILE64_SOURCE zlib tries to include unistd.h */
 #ifndef _MSC_VER
 /* Ghostscript uses transitional LFS functions. */
-#define _LARGEFILE64_SOURCE 1
+#define _LARGEFILE_SOURCE 1
 #endif
 
 #ifndef _FILE_OFFSET_BITS
