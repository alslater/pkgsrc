$NetBSD$

--- src/esi/VarState.cc.orig	2019-11-05 19:14:40.000000000 +0000
+++ src/esi/VarState.cc
@@ -12,6 +12,7 @@
 #include "esi/VarState.h"
 #include "fatal.h"
 #include "HttpReply.h"
+#include "strings.h"
 
 char const *ESIVariableUserAgent::esiUserOs[]= {
     "WIN",
