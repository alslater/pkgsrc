$NetBSD$

--- gcc/config/sol2.h.orig	2020-05-12 14:14:58.612638694 +0000
+++ gcc/config/sol2.h
@@ -206,7 +206,7 @@ along with GCC; see the file COPYING3.
 				   shared|" PIE_SPEC ":crtbeginS.o%s; \
 				   :crtbegin.o%s}"
 #else
-#define STARTFILE_CRTBEGIN_SPEC	"crtbegin.o%s"
+#define STARTFILE_CRTBEGIN_SPEC	"%{shared:crtbeginS.o%s;:crtbegin.o%s}"
 #endif
 
 #if ENABLE_VTABLE_VERIFY
@@ -256,7 +256,7 @@ along with GCC; see the file COPYING3.
 			       shared|" PIE_SPEC ":crtendS.o%s; \
 			       :crtend.o%s}"
 #else
-#define ENDFILE_CRTEND_SPEC "crtend.o%s"
+#define ENDFILE_CRTEND_SPEC "%{shared:crtendS.o%s;:crtend.o%s}"
 #endif
 
 #undef  ENDFILE_SPEC
