$NetBSD$

--- utils.c.orig	2016-09-12 07:45:50.000000000 +0000
+++ utils.c
@@ -15,6 +15,14 @@
 #include "error.h"
 #include "utils.h"
 
+#ifdef __sun
+double get_ts(void)
+{
+        hrtime_t t = gethrtime();
+        
+        return (double)t / 1000000000;
+}
+#else
 double get_ts(void)
 {
 	struct timeval ts;
@@ -25,6 +33,7 @@ double get_ts(void)
 
 	return (double)ts.tv_sec + ((double)ts.tv_usec)/1000000.0 + (double)(tz.tz_minuteswest * 60);
 }
+#endif
 
 void split_string(const char *in, const char *split, char ***list, int *list_n)
 {
