$NetBSD$

--- gnome-pty-helper/gnome-utmp.c.orig	2015-10-12 14:28:42.000000000 +0000
+++ gnome-pty-helper/gnome-utmp.c
@@ -245,6 +245,9 @@ write_logout_record (char *login_name, v
 #if defined(HAVE_UT_UT_ID)
 	strncpy (put.ut_id, ut->ut_id, sizeof (put.ut_id));
 #endif
+#if defined(HAVE_UT_UT_NAME)
+	strncpy (put.ut_name, ut->ut_name, sizeof (put.ut_name));
+#endif
 
 	strncpy (put.ut_line, ut->ut_line, sizeof (put.ut_line));
 
@@ -265,6 +268,10 @@ write_logout_record (char *login_name, v
 	if (utmp)
 		update_utmp (&put);
 
+#if defined(HAVE_UT_UT_NAME)
+	memset (put.ut_name, 0, sizeof (put.ut_name));
+#endif
+
 	if (wtmp)
 		update_wtmp (WTMP_OUTPUT_FILENAME, &put);
 
