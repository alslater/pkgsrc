$NetBSD: patch-Makefile.SH,v 1.6 2017/06/06 12:37:50 jperkin Exp $

Fix DTrace object generation.

--- Makefile.SH.orig	2018-05-21 13:22:09.000000000 +0000
+++ Makefile.SH
@@ -275,6 +275,7 @@ LNS = $lns
 # NOTE: some systems don't grok "cp -f". XXX Configure test needed?
 CPS = $cp
 RMS = rm -f
+ECHO = $echo
 ranlib = $ranlib
 
 # The following are mentioned only to make metaconfig include the
