$NetBSD$

--- ext/libxml/php_libxml.h.orig	2022-10-31 10:36:06.000000000 +0000
+++ ext/libxml/php_libxml.h
@@ -37,6 +37,7 @@ extern zend_module_entry libxml_module_e
 
 #include "zend_smart_str.h"
 #include <libxml/tree.h>
+#include <libxml/parser.h>
 
 #define LIBXML_SAVE_NOEMPTYTAG 1<<2
 
