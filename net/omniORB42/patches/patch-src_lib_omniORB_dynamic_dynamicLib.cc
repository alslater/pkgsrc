$NetBSD$

--- src/lib/omniORB/dynamic/dynamicLib.cc.orig	2017-02-20 22:45:59.000000000 +0000
+++ src/lib/omniORB/dynamic/dynamicLib.cc
@@ -30,7 +30,7 @@
 #include <omniORB4/CORBA.h>
 #include <omniORB4/callDescriptor.h>
 #include <dynamicLib.h>
-#include <context.h>
+#include <omniORB4/internal/context.h>
 #include <initialiser.h>
 #include <omniORB4/linkHacks.h>
 
