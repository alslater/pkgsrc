$NetBSD$

--- include/AL/al.h.orig	2019-11-28 08:45:08.000000000 +0000
+++ include/AL/al.h
@@ -34,6 +34,8 @@ extern "C" {
 #define AL_VERSION_1_0
 #define AL_VERSION_1_1
 
+#include <stdint.h>
+
 /** 8-bit boolean */
 typedef char ALboolean;
 
@@ -41,7 +43,7 @@ typedef char ALboolean;
 typedef char ALchar;
 
 /** signed 8-bit 2's complement integer */
-typedef signed char ALbyte;
+typedef int8_t ALbyte;
 
 /** unsigned 8-bit integer */
 typedef unsigned char ALubyte;
