$NetBSD: patch-python_setup.py,v 1.1 2017/10/31 13:15:44 fhajny Exp $

Trust pkgsrc to know which iconv to use.
It will be either in the buildlink directory, or in the compiler's
default search path.

--- python/setup.py.orig	2022-02-20 12:11:17.000000000 +0000
+++ python/setup.py
@@ -66,11 +66,7 @@ else:
 # - libxml2/libxml/tree.h
 # - libxslt/xsltconfig.h
 includes_dir = [
-"/usr/include",
-"/usr/local/include",
-"/opt/include",
 os.path.join(ROOT,'include'),
-HOME
 ];
 
 xml_includes=""
