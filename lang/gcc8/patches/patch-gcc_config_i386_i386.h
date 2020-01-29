$NetBSD$

--- gcc/config/i386/i386.h.orig	2018-11-18 20:41:32.000000000 +0000
+++ gcc/config/i386/i386.h
@@ -2451,6 +2451,7 @@ enum avx_u128_state
   */
 struct GTY(()) ix86_frame
 {
+  int nmsave_args;
   int nsseregs;
   int nregs;
   int va_arg_size;
@@ -2463,6 +2464,7 @@ struct GTY(()) ix86_frame
   HOST_WIDE_INT stack_pointer_offset;
   HOST_WIDE_INT hfp_save_offset;
   HOST_WIDE_INT reg_save_offset;
+  HOST_WIDE_INT arg_save_offset;
   HOST_WIDE_INT stack_realign_allocate;
   HOST_WIDE_INT stack_realign_offset;
   HOST_WIDE_INT sse_reg_save_offset;
