$NetBSD$

--- Makefile.PL.orig	2016-09-05 06:31:16.000000000 +0000
+++ Makefile.PL
@@ -1,4 +1,6 @@
 use strict;
+use FindBin;
+use lib $FindBin::Bin;
 use inc::Module::Install 0.92;
 
 $|++;
