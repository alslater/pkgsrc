$NetBSD$

--- ext/dom/document.c.orig	2023-11-21 21:53:48.000000000 +0000
+++ ext/dom/document.c
@@ -23,6 +23,7 @@
 #if defined(HAVE_LIBXML) && defined(HAVE_DOM)
 #include "php_dom.h"
 #include <libxml/SAX.h>
+#include <libxml/xmlsave.h>
 #ifdef LIBXML_SCHEMAS_ENABLED
 #include <libxml/relaxng.h>
 #include <libxml/xmlschemas.h>
