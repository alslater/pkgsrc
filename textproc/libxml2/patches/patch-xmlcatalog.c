$NetBSD: patch-xmlcatalog.c,v 1.1 2019/01/09 19:09:03 adam Exp $

Parametrize SGML catalog directory.

--- xmlcatalog.c.orig	2022-05-02 12:10:22.000000000 +0000
+++ xmlcatalog.c
@@ -40,7 +40,7 @@ static char *filename = NULL;
 
 
 #ifndef XML_SGML_DEFAULT_CATALOG
-#define XML_SGML_DEFAULT_CATALOG SYSCONFDIR "/sgml/catalog"
+#define XML_SGML_DEFAULT_CATALOG SYSCONFDIR "@@SGML_DEFAULT_CATALOG@@"
 #endif
 
 /************************************************************************
