$NetBSD$

--- gdb/score-tdep.c.orig	2018-01-05 04:07:23.000000000 +0000
+++ gdb/score-tdep.c
@@ -937,13 +937,13 @@ score7_analyze_prologue (CORE_ADDR start
                    && G_FLD (inst->v, 2, 0) == 0x0)
             {
               /* subei! r0, n */
-              sp_offset += (int) pow (2, G_FLD (inst->v, 6, 3));
+              sp_offset += (int) pow (2.0, G_FLD (inst->v, 6, 3));
             }
           else if (G_FLD (inst->v, 14, 7) == 0xc0
                    && G_FLD (inst->v, 2, 0) == 0x0)
             {
               /* addei! r0, n */
-              sp_offset -= (int) pow (2, G_FLD (inst->v, 6, 3));
+              sp_offset -= (int) pow (2.0, G_FLD (inst->v, 6, 3));
             }
         }
       else
