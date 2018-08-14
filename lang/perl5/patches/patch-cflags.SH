$NetBSD: patch-cflags.SH,v 1.2 2018/01/15 10:07:50 jperkin Exp $

Don't add -std=c89 or -ansi, requires c99.

--- cflags.SH.orig	2018-07-31 17:58:18.274987379 +0000
+++ cflags.SH
@@ -178,7 +178,7 @@ Intel*) ;; # # Is that you, Intel C++?
 # -std=c89 before -ansi
 # -pedantic* before -Werror=d-a-s
 #
-*)  for opt in -std=c89 -ansi $pedantic \
+*)  for opt in $pedantic \
 		-Werror=declaration-after-statement \
 	        -Werror=pointer-arith \
 		-Wextra -W \
