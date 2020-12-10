$NetBSD$

--- Zend/zend.c.orig	2020-09-29 10:17:15.000000000 +0000
+++ Zend/zend.c
@@ -1309,7 +1309,9 @@ static ZEND_COLD void zend_error_va_list
 #ifdef HAVE_DTRACE
 	if (DTRACE_ERROR_ENABLED()) {
 		char *dtrace_error_buffer;
-		zend_vspprintf(&dtrace_error_buffer, 0, format, args);
+		va_copy(usr_copy, args);
+		zend_vspprintf(&dtrace_error_buffer, 0, format, usr_copy);
+		va_end(usr_copy);
 		DTRACE_ERROR(dtrace_error_buffer, (char *)error_filename, error_lineno);
 		efree(dtrace_error_buffer);
 	}
