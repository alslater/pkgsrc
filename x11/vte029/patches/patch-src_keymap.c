$NetBSD$

--- src/keymap.c.orig	2015-10-12 14:34:49.000000000 +0000
+++ src/keymap.c
@@ -708,6 +708,18 @@ static const struct _vte_keymap_group {
 	{GDK_KEY_F35,			_vte_keymap_GDK_F35},
 };
 
+/* Restrict modifiers to the specified mask and ensure that VTE_META_MASK,
+ * despite being a compound mask, is treated as indivisible. */
+static GdkModifierType
+_vte_keymap_fixup_modifiers(GdkModifierType modifiers,
+               GdkModifierType mask)
+{
+	if (modifiers & VTE_META_MASK)
+        	modifiers |= VTE_META_MASK;
+	return modifiers & mask;
+}
+
+
 /* Map the specified keyval/modifier setup, dependent on the mode, to
  * a literal string. */
 void
@@ -751,7 +763,7 @@ _vte_keymap_map(guint keyval,
 	/* Build mode masks. */
 	cursor_mode = app_cursor_keys ? cursor_app : cursor_default;
 	keypad_mode = app_keypad_keys ? keypad_app : keypad_default;
-	modifiers &= (GDK_SHIFT_MASK | GDK_CONTROL_MASK | VTE_META_MASK | VTE_NUMLOCK_MASK);
+	modifiers = _vte_keymap_fixup_modifiers(modifiers, GDK_SHIFT_MASK | GDK_CONTROL_MASK | VTE_META_MASK | VTE_NUMLOCK_MASK);
 
 	/* Search for the conditions. */
 	for (i = 0; entries[i].normal_length; i++)
@@ -952,7 +964,7 @@ _vte_keymap_key_add_key_modifiers(guint
 		return;
 	}
 
-	switch (modifiers & significant_modifiers) {
+	switch (_vte_keymap_fixup_modifiers(modifiers, significant_modifiers)) {
 	case 0:
 		modifier = 0;
 		break;
