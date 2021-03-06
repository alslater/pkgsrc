$NetBSD: patch-IlmImf_ImfSystemSpecific.cpp,v 1.2 2014/08/19 13:34:42 joerg Exp $

Rework cpuid function to use gnuc __get_cpuid (requiring at least gcc 4.3)
This get's over issues such as encountered with PIC builds.
Upstream issue : https://github.com/openexr/openexr/issues/128

--- IlmImf/ImfSystemSpecific.cpp.orig	2014-08-10 04:23:57.000000000 +0000
+++ IlmImf/ImfSystemSpecific.cpp
@@ -40,21 +40,30 @@ OPENEXR_IMF_INTERNAL_NAMESPACE_SOURCE_EN
 
 namespace {
 #if defined(IMF_HAVE_SSE2) &&  defined(__GNUC__)
-
     // Helper functions for gcc + SSE enabled
-    void cpuid(int n, int &eax, int &ebx, int &ecx, int &edx)
+    void cpuid(unsigned int n, unsigned int &eax, unsigned int &ebx,
+					unsigned int &ecx, unsigned int &edx)
     {
+#ifdef __i386__
+        __asm__ __volatile__ (
+            "pushl %%ebx; cpuid; movl %%ebx, %0; popl %%ebx"
+            : /* Output  */ "=m"(ebx), "=a"(eax), "=c"(ecx), "=d"(edx) 
+            : /* Input   */ "a"(n)
+            : /* Clobber */);
+#else
         __asm__ __volatile__ (
             "cpuid"
             : /* Output  */ "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) 
             : /* Input   */ "a"(n)
             : /* Clobber */);
+#endif
     }
 
 #else // IMF_HAVE_SSE2 && __GNUC__
 
     // Helper functions for generic compiler - all disabled
-    void cpuid(int n, int &eax, int &ebx, int &ecx, int &edx)
+    void cpuid(unsigned int n, unsigned int &eax, unsigned int &ebx,
+					unsigned int &ecx, unsigned int &edx)
     {
         eax = ebx = ecx = edx = 0;
     }
@@ -64,7 +73,7 @@ namespace {
 
 #ifdef OPENEXR_IMF_HAVE_GCC_INLINE_ASM_AVX
 
-    void xgetbv(int n, int &eax, int &edx)
+    void xgetbv(unsigned int n, unsigned int &eax, unsigned int &edx)
     {
         __asm__ __volatile__ (
             "xgetbv"
@@ -75,7 +84,7 @@ namespace {
 
 #else //  OPENEXR_IMF_HAVE_GCC_INLINE_ASM_AVX
 
-    void xgetbv(int n, int &eax, int &edx)
+    void xgetbv(unsigned int n, unsigned int &eax, unsigned int &edx)
     {
         eax = edx = 0;
     }
@@ -94,8 +103,8 @@ CpuId::CpuId():
     f16c(false)
 {
     bool osxsave = false;
-    int  max     = 0;
-    int  eax, ebx, ecx, edx;
+    unsigned int  max     = 0;
+    unsigned int  eax, ebx, ecx, edx;
 
     cpuid(0, max, ebx, ecx, edx);
     if (max > 0)
