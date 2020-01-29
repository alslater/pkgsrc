$NetBSD$

--- gcc/dojump.c.orig	2018-09-14 23:30:32.000000000 +0000
+++ gcc/dojump.c
@@ -77,7 +77,7 @@ void
 clear_pending_stack_adjust (void)
 {
   if (optimize > 0
-      && (! flag_omit_frame_pointer || cfun->calls_alloca)
+      && (! 0 || cfun->calls_alloca)
       && EXIT_IGNORE_STACK)
     discard_pending_stack_adjust ();
 }
