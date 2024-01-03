$NetBSD$

--- modules/filters/mod_xml2enc.c.orig	2020-02-21 00:33:40.000000000 +0000
+++ modules/filters/mod_xml2enc.c
@@ -35,6 +35,7 @@
 #endif
 
 /* libxml2 */
+#include <libxml/xmlstring.h>
 #include <libxml/encoding.h>
 
 #if defined(__clang__)
