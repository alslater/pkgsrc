$NetBSD$

--- src/lib/omniORB/dynamic/request.cc.orig	2017-02-20 22:45:59.000000000 +0000
+++ src/lib/omniORB/dynamic/request.cc
@@ -35,7 +35,7 @@
 #endif
 
 #include <request.h>
-#include <context.h>
+#include <omniORB4/internal/context.h>
 #include <string.h>
 #include <omniORB4/callDescriptor.h>
 #include <remoteIdentity.h>
