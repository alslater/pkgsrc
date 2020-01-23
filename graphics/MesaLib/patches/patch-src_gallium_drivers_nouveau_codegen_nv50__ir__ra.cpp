$NetBSD$

--- src/gallium/drivers/nouveau/codegen/nv50_ir_ra.cpp.orig	2019-12-04 22:10:12.000000000 +0000
+++ src/gallium/drivers/nouveau/codegen/nv50_ir_ra.cpp
@@ -1347,7 +1347,7 @@ GCRA::simplify()
                bestMaxReg = it->maxReg;
             }
          }
-         if (isinf(bestScore)) {
+         if (std::isinf(bestScore)) {
             ERROR("no viable spill candidates left\n");
             return false;
          }
