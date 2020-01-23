$NetBSD: patch-Source_WTF_wtf_InlineASM.h,v 1.1 2014/12/30 17:23:47 adam Exp $

* Add NetBSD support
* Add Solaris/SunOS support

--- Source/WTF/wtf/InlineASM.h.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/WTF/wtf/InlineASM.h
@@ -40,7 +40,7 @@
 #define THUMB_FUNC_PARAM(name)
 #endif
 
-#if (OS(LINUX) || OS(FREEBSD)) && CPU(X86_64)
+#if (OS(LINUX) || OS(FREEBSD) || OS(NETBSD) || OS(SOLARIS)) && CPU(X86_64) || (OS(SOLARIS) && CPU(X86))
 #define GLOBAL_REFERENCE(name) #name "@plt"
 #elif CPU(X86) && COMPILER(MINGW)
 #define GLOBAL_REFERENCE(name) "@" #name "@4"
@@ -84,6 +84,7 @@
     || OS(OPENBSD)             \
     || OS(HURD)                \
     || OS(NETBSD)              \
+    || OS(SOLARIS)             \
     || COMPILER(MINGW)
     // GNU as-compatible syntax.
 #define LOCAL_LABEL_STRING(name) ".L" #name
