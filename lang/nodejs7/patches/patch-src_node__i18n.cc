$NetBSD$

--- src/node_i18n.cc.orig	2017-01-31 22:19:51.000000000 +0000
+++ src/node_i18n.cc
@@ -43,6 +43,7 @@
 #include <unicode/ulocdata.h>
 #include <unicode/uvernum.h>
 #include <unicode/uversion.h>
+#include <unicode/ustring.h>
 
 #ifdef NODE_HAVE_SMALL_ICU
 /* if this is defined, we have a 'secondary' entry point.
@@ -364,7 +365,7 @@ static const char* GetVersion(const char
   } else if (!strcmp(type, TYPE_UNICODE)) {
     return U_UNICODE_VERSION;
   } else if (!strcmp(type, TYPE_TZ)) {
-    return TimeZone::getTZDataVersion(*status);
+    return icu::TimeZone::getTZDataVersion(*status);
   } else if (!strcmp(type, TYPE_CLDR)) {
     UVersionInfo versionArray;
     ulocdata_getCLDRVersion(versionArray, status);
