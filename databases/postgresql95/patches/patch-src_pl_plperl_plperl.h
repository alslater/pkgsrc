$NetBSD: patch-src_pl_plperl_plperl.h,v 1.2 2017/08/13 19:25:18 adam Exp $

--- src/pl/plperl/plperl.h.orig	2021-02-08 22:03:12.000000000 +0000
+++ src/pl/plperl/plperl.h
@@ -42,6 +42,11 @@
 #undef vsnprintf
 #endif
 
+#ifdef __sun
+#define list_head sun_list_head
+#define list_tail sun_list_tail
+#endif
+
 /*
  * ActivePerl 5.18 and later are MinGW-built, and their headers use GCC's
  * __inline__.  Translate to something MSVC recognizes.
@@ -68,6 +73,11 @@
 #include "XSUB.h"
 #endif
 
+#ifdef __sun
+#undef list_head
+#undef list_tail
+#endif
+
 /* put back our snprintf and vsnprintf */
 #ifdef USE_REPL_SNPRINTF
 #ifdef snprintf
