$NetBSD$

--- Source/WebCore/platform/text/icu/UTextProvider.h.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/WebCore/platform/text/icu/UTextProvider.h
@@ -80,12 +80,12 @@ inline bool uTextAccessInChunkOrOutOfRan
             // Ensure chunk offset is well formed if computed offset exceeds int32_t range.
             ASSERT(offset < std::numeric_limits<int32_t>::max());
             text->chunkOffset = offset < std::numeric_limits<int32_t>::max() ? static_cast<int32_t>(offset) : 0;
-            isAccessible = TRUE;
+            isAccessible = true;
             return true;
         }
         if (nativeIndex >= nativeLength && text->chunkNativeLimit == nativeLength) {
             text->chunkOffset = text->chunkLength;
-            isAccessible = FALSE;
+            isAccessible = false;
             return true;
         }
     } else {
@@ -94,12 +94,12 @@ inline bool uTextAccessInChunkOrOutOfRan
             // Ensure chunk offset is well formed if computed offset exceeds int32_t range.
             ASSERT(offset < std::numeric_limits<int32_t>::max());
             text->chunkOffset = offset < std::numeric_limits<int32_t>::max() ? static_cast<int32_t>(offset) : 0;
-            isAccessible = TRUE;
+            isAccessible = true;
             return true;
         }
         if (nativeIndex <= 0 && !text->chunkNativeStart) {
             text->chunkOffset = 0;
-            isAccessible = FALSE;
+            isAccessible = false;
             return true;
         }
     }
