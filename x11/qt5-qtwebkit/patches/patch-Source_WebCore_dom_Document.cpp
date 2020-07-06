$NetBSD$

Fix build with ICU >= 67.1

--- Source/WebCore/dom/Document.cpp.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/WebCore/dom/Document.cpp
@@ -4407,12 +4407,12 @@ static bool isValidNameNonASCII(const UC
     unsigned i = 0;
 
     UChar32 c;
-    U16_NEXT(characters, i, length, c)
+    U16_NEXT(characters, i, length, c);
     if (!isValidNameStart(c))
         return false;
 
     while (i < length) {
-        U16_NEXT(characters, i, length, c)
+        U16_NEXT(characters, i, length, c);
         if (!isValidNamePart(c))
             return false;
     }
@@ -4474,7 +4474,7 @@ bool Document::parseQualifiedName(const
 
     for (unsigned i = 0; i < length;) {
         UChar32 c;
-        U16_NEXT(qualifiedName, i, length, c)
+        U16_NEXT(qualifiedName, i, length, c);
         if (c == ':') {
             if (sawColon) {
                 ec = NAMESPACE_ERR;
