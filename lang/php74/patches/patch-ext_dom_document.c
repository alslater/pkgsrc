$NetBSD$

--- ext/dom/document.c.orig	2022-10-31 10:36:09.000000000 +0000
+++ ext/dom/document.c
@@ -25,6 +25,7 @@
 #if HAVE_LIBXML && HAVE_DOM
 #include "php_dom.h"
 #include <libxml/SAX.h>
+#include <libxml/xmlsave.h>
 #ifdef LIBXML_SCHEMAS_ENABLED
 #include <libxml/relaxng.h>
 #include <libxml/xmlschemas.h>
