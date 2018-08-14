$NetBSD$

--- Makefile.PL.orig	2011-06-17 01:46:42.000000000 +0000
+++ Makefile.PL
@@ -1,3 +1,5 @@
+use FindBin;
+use lib $FindBin::Bin;
 use inc::Module::Install 1.01;
 
 all_from      'lib/Crypt/DSA.pm';
