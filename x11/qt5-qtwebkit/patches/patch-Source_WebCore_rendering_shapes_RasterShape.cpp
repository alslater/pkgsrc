$NetBSD$

--- Source/WebCore/rendering/shapes/RasterShape.cpp.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/WebCore/rendering/shapes/RasterShape.cpp
@@ -142,7 +142,7 @@ const RasterShapeIntervals& RasterShape:
         return *m_intervals;
 
     int shapeMarginInt = clampToPositiveInteger(ceil(shapeMargin()));
-    int maxShapeMarginInt = std::max(m_marginRectSize.width(), m_marginRectSize.height()) * sqrt(2);
+    int maxShapeMarginInt = std::max(m_marginRectSize.width(), m_marginRectSize.height()) * sqrt(static_cast<double>(2));
     if (!m_marginIntervals)
         m_marginIntervals = m_intervals->computeShapeMarginIntervals(std::min(shapeMarginInt, maxShapeMarginInt));
 
