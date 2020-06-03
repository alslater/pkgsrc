$NetBSD$

--- gcc/config/i386/sol2.h.orig	2020-05-12 14:14:29.291428744 +0000
+++ gcc/config/i386/sol2.h
@@ -76,7 +76,7 @@ along with GCC; see the file COPYING3.
 #define ASM_CPU_SPEC "%(asm_cpu_default) " ASM_XBRACE_COMMENT_SPEC
 
 /* Don't include ASM_PIC_SPEC.  While the Solaris 10+ assembler accepts -K PIC,
-   it gives many warnings: 
+   it gives many warnings:
 	Absolute relocation is used for symbol "<symbol>"
    GNU as doesn't recognize -K at all.  */
 #undef ASM_SPEC
