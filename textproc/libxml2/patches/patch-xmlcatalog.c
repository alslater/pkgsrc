$NetBSD: patch-xmlcatalog.c,v 1.1 2019/01/09 19:09:03 adam Exp $

Parametrize SGML catalog directory.

--- xmlcatalog.c.orig	2023-11-16 12:17:02.000000000 +0000
+++ xmlcatalog.c
@@ -39,7 +39,7 @@ static char *filename = NULL;
 
 
 #ifndef XML_SGML_DEFAULT_CATALOG
-#define XML_SGML_DEFAULT_CATALOG SYSCONFDIR "/sgml/catalog"
+#define XML_SGML_DEFAULT_CATALOG SYSCONFDIR "/opt/scl64/etc/sgml/catalog"
 #endif
 
 /************************************************************************
