$NetBSD$

--- src/lib/omniORB/dynamic/serverRequest.cc.orig	2017-02-20 22:45:59.000000000 +0000
+++ src/lib/omniORB/dynamic/serverRequest.cc
@@ -32,7 +32,7 @@
 #include <omniORB4/IOP_S.h>
 #include <dynamicImplementation.h>
 #include <pseudo.h>
-#include <context.h>
+#include <omniORB4/internal/context.h>
 #include <exceptiondefs.h>
 #include <poacurrentimpl.h>
 
