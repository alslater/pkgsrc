$NetBSD$

--- Source/JavaScriptCore/dfg/DFGStaticExecutionCountEstimationPhase.cpp.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/JavaScriptCore/dfg/DFGStaticExecutionCountEstimationPhase.cpp
@@ -53,7 +53,7 @@ public:
             if (!block)
                 continue;
 
-            block->executionCount = pow(10, m_graph.m_naturalLoops->loopDepth(block));
+            block->executionCount = pow((double)10, (double)m_graph.m_naturalLoops->loopDepth(block));
         }
         
         // Estimate branch weights based on execution counts. This isn't quite correct. It'll
