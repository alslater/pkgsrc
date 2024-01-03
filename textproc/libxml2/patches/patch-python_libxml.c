$NetBSD: patch-python_libxml.c,v 1.1 2019/01/09 13:40:50 wiz Exp $

Avoid returning invalid UTF-8 strings to python.
Based on https://bugzilla.opensuse.org/attachment.cgi?id=746044&action=edit
Fixes https://github.com/itstool/itstool/issues/22

--- python/libxml.c.orig	2023-11-23 17:09:31.000000000 +0000
+++ python/libxml.c
@@ -1505,6 +1505,7 @@ libxml_xmlErrorFuncHandler(ATTRIBUTE_UNU
     PyObject *message;
     PyObject *result;
     char str[1000];
+    unsigned char *ptr = (unsigned char *)str;
 
     if (libxml_xmlPythonErrorFuncHandler == NULL) {
         va_start(ap, msg);
@@ -1516,10 +1517,14 @@ libxml_xmlErrorFuncHandler(ATTRIBUTE_UNU
 	    str[999] = 0;
         va_end(ap);
 
+        /* Ensure the error string doesn't start at UTF8 continuation. */
+        while (*ptr && (*ptr & 0xc0) == 0x80)
+            ptr++;
+
         list = PyTuple_New(2);
         PyTuple_SetItem(list, 0, libxml_xmlPythonErrorFuncCtxt);
         Py_XINCREF(libxml_xmlPythonErrorFuncCtxt);
-        message = libxml_charPtrConstWrap(str);
+        message = libxml_charPtrConstWrap(ptr);
         PyTuple_SetItem(list, 1, message);
         result = PyObject_CallObject(libxml_xmlPythonErrorFuncHandler, list);
         Py_XDECREF(list);
