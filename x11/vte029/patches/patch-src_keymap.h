$NetBSD$

--- src/keymap.h.orig	2015-10-12 14:34:49.000000000 +0000
+++ src/keymap.h
@@ -26,7 +26,7 @@
 
 G_BEGIN_DECLS
 
-#define VTE_META_MASK		GDK_META_MASK
+#define VTE_META_MASK		(GDK_META_MASK | GDK_MOD1_MASK)
 #define VTE_NUMLOCK_MASK	GDK_MOD2_MASK
 
 /* Map the specified keyval/modifier setup, dependent on the mode, to either
