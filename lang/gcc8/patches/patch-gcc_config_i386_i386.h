$NetBSD$

--- gcc/config/i386/i386.h.orig	2020-03-04 08:30:00.000000000 +0000
+++ gcc/config/i386/i386.h
@@ -618,7 +618,7 @@ extern tree x86_mfence;
 #define TARGET_SUBTARGET64_DEFAULT 0
 #define TARGET_SUBTARGET64_ISA_DEFAULT 0
 
-/* Replace MACH-O, ifdefs by in-line tests, where possible. 
+/* Replace MACH-O, ifdefs by in-line tests, where possible.
    (a) Macros defined in config/i386/darwin.h  */
 #define TARGET_MACHO 0
 #define TARGET_MACHO_SYMBOL_STUBS 0
@@ -1562,11 +1562,11 @@ enum reg_class
 /* If defined, the maximum amount of space required for outgoing arguments
    will be computed and placed into the variable `crtl->outgoing_args_size'.
    No space will be pushed onto the stack for each call; instead, the
-   function prologue should increase the stack frame size by this amount.  
+   function prologue should increase the stack frame size by this amount.
 
    In 32bit mode enabling argument accumulation results in about 5% code size
    growth because move instructions are less compact than push.  In 64bit
-   mode the difference is less drastic but visible.  
+   mode the difference is less drastic but visible.
 
    FIXME: Unlike earlier implementations, the size of unwind info seems to
    actually grow with accumulation.  Is that because accumulated args
@@ -2285,7 +2285,7 @@ do {							\
 } while (0)
 
 /* Which processor to tune code generation for.  These must be in sync
-   with processor_target_table in i386.c.  */ 
+   with processor_target_table in i386.c.  */
 
 enum processor_type
 {
@@ -2443,6 +2443,11 @@ enum avx_u128_state
 
    saved frame pointer			if frame_pointer_needed
 					<- HARD_FRAME_POINTER
+
+   [-msave-args]			<- arg_save_offset
+
+   [saveargs padding]
+
    [saved regs]
 					<- reg_save_offset
    [padding0]
@@ -2476,6 +2481,7 @@ enum avx_u128_state
   */
 struct GTY(()) ix86_frame
 {
+  int nmsave_args;
   int nsseregs;
   int nregs;
   int va_arg_size;
@@ -2487,6 +2493,7 @@ struct GTY(()) ix86_frame
   HOST_WIDE_INT hard_frame_pointer_offset;
   HOST_WIDE_INT stack_pointer_offset;
   HOST_WIDE_INT hfp_save_offset;
+  HOST_WIDE_INT arg_save_offset;
   HOST_WIDE_INT reg_save_offset;
   HOST_WIDE_INT stack_realign_allocate;
   HOST_WIDE_INT stack_realign_offset;
