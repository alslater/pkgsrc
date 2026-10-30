$NetBSD: patch-xmlcatalog.c,v 1.1 2019/01/09 19:09:03 adam Exp $

Parametrize SGML catalog directory.

--- xmlcatalog.c.orig	2026-09-04 16:22:45.000000000 +0000
+++ xmlcatalog.c
@@ -57,7 +57,7 @@ static char *filename = NULL;
 
 #ifdef LIBXML_SGML_CATALOG_ENABLED
 #ifndef XML_SGML_DEFAULT_CATALOG
-#define XML_SGML_DEFAULT_CATALOG XML_SYSCONFDIR "/sgml/catalog"
+#define XML_SGML_DEFAULT_CATALOG XML_SYSCONFDIR "/opt/scl64/etc/sgml/catalog"
 #endif
 #endif
 
