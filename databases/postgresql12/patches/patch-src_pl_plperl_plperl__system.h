$NetBSD$

--- src/pl/plperl/plperl_system.h.orig	2024-11-18 20:41:03.000000000 +0000
+++ src/pl/plperl/plperl_system.h
@@ -83,6 +83,11 @@
 #define HAS_BOOL 1
 #endif
 
+#ifdef __sun
+#define list_head sun_list_head
+#define list_tail sun_list_tail
+#endif
+
 /*
  * Get the basic Perl API.  We use PERL_NO_GET_CONTEXT mode so that our code
  * can compile against MULTIPLICITY Perl builds without including XSUB.h.
@@ -124,6 +129,11 @@
 #include "XSUB.h"
 #endif
 
+#ifdef __sun
+#undef list_head
+#undef list_tail
+#endif
+
 /* put back our *printf macros ... this must match src/include/port.h */
 #ifdef vsnprintf
 #undef vsnprintf
