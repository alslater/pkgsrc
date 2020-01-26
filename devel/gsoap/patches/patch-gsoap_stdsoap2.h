$NetBSD$

--- gsoap/stdsoap2.h.orig	2018-02-18 20:57:30.000000000 +0000
+++ gsoap/stdsoap2.h
@@ -861,7 +861,6 @@ extern intmax_t __strtoull(const char*,
 #   endif
 #   ifdef SUN_OS
 #    include <sys/stream.h>             /* SUN */
-#    include <sys/socketvar.h>          /* only needed with SUN < 2.8 ? */
 #   endif
 #   ifdef VXWORKS
 #    ifdef _WRS_KERNEL
