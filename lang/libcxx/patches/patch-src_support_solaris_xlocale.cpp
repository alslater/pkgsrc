$NetBSD$

--- src/support/solaris/xlocale.cpp.orig	2019-01-19 10:56:40.000000000 +0000
+++ src/support/solaris/xlocale.cpp
@@ -11,7 +11,9 @@
 #include "support/solaris/xlocale.h"
 #include <stdarg.h>
 #include <stdio.h>
-#include <sys/localedef.h>
+#include <ctype.h>
+#include <wctype.h>
+#include <uchar.h>
 
 extern "C" {
 
