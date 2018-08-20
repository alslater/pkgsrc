$NetBSD$

--- xpath.c.orig	2017-12-02 08:58:10.000000000 +0000
+++ xpath.c
@@ -485,9 +485,9 @@ int wrap_cmp( xmlNodePtr x, xmlNodePtr y
 #define INFINITY HUGE_VAL
 #endif
 
-double xmlXPathNAN = NAN;
-double xmlXPathPINF = INFINITY;
-double xmlXPathNINF = -INFINITY;
+double xmlXPathNAN;
+double xmlXPathPINF;
+double xmlXPathNINF;
 
 /**
  * xmlXPathInit:
@@ -498,6 +498,9 @@ double xmlXPathNINF = -INFINITY;
  */
 void
 xmlXPathInit(void) {
+    xmlXPathNAN = NAN;
+    xmlXPathPINF = INFINITY;
+    xmlXPathNINF = -INFINITY;
 }
 
 /**
