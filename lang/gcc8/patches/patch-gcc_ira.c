$NetBSD$

--- gcc/ira.c.orig	2018-02-05 10:47:56.000000000 +0000
+++ gcc/ira.c
@@ -1724,7 +1724,7 @@ ira_init (void)
 {
   this_target_ira_int->free_register_move_costs ();
   setup_reg_mode_hard_regset ();
-  setup_alloc_regs (flag_omit_frame_pointer != 0);
+  setup_alloc_regs (0 != 0);
   setup_class_subset_and_memory_move_costs ();
   setup_reg_class_nregs ();
   setup_prohibited_class_mode_regs ();
@@ -2279,7 +2279,7 @@ ira_setup_eliminable_regset (void)
      case.  At some point, we should improve this by emitting the
      sp-adjusting insns for this case.  */
   frame_pointer_needed
-    = (! flag_omit_frame_pointer
+    = (! 0
        || (cfun->calls_alloca && EXIT_IGNORE_STACK)
        /* We need the frame pointer to catch stack overflow exceptions if
 	  the stack pointer is moving (as for the alloca case just above).  */
