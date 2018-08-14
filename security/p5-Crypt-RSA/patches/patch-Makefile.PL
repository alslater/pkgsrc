$NetBSD$

--- Makefile.PL.orig	2008-07-07 08:53:12.000000000 +0000
+++ Makefile.PL
@@ -10,2 +10,4 @@
 
+use FindBin;
+use lib $FindBin::Bin;
 use inc::Module::Install;
