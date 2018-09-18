$NetBSD$

--- aws-cpp-sdk-core/source/platform/linux-shared/OSVersionInfo.cpp.orig	2018-09-06 22:50:27.000000000 +0000
+++ aws-cpp-sdk-core/source/platform/linux-shared/OSVersionInfo.cpp
@@ -53,7 +53,7 @@ Aws::String GetSysCommandOutput(const ch
 
 Aws::String ComputeOSVersionString()
 {
-    utsname name;
+    struct utsname name;
     int32_t success = uname(&name);
     if(success >= 0)
     {
