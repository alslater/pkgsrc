$NetBSD$

--- gettext-runtime/gnulib-lib/localename-unsafe.c.orig	2024-02-21 10:43:40.000000000 +0000
+++ gettext-runtime/gnulib-lib/localename-unsafe.c
@@ -47,8 +47,6 @@
 # endif
 # if defined __sun
 #  if HAVE_GETLOCALENAME_L
-/* Solaris >= 12.  */
-extern char * getlocalename_l(int, locale_t);
 #  elif HAVE_SOLARIS114_LOCALES
 #   include <sys/localedef.h>
 #  endif
