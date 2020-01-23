$NetBSD$

--- Source/JavaScriptCore/dfg/DFGOperations.cpp.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/JavaScriptCore/dfg/DFGOperations.cpp
@@ -1344,7 +1344,7 @@ void JIT_OPERATION operationLoadVarargs(
 
 double JIT_OPERATION operationFModOnInts(int32_t a, int32_t b)
 {
-    return fmod(a, b);
+    return fmod((double)a, b);
 }
 
 #if USE(JSVALUE32_64)
