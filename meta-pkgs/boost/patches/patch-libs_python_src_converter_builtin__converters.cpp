$NetBSD$

Backported fixes to support python > 3.7 

--- libs/python/src/converter/builtin_converters.cpp.orig	2020-01-13 08:10:22.664028166 +0000
+++ libs/python/src/converter/builtin_converters.cpp
@@ -48,7 +48,7 @@ namespace
 #else
   void* convert_to_cstring(PyObject* obj)
   {
-      return PyUnicode_Check(obj) ? _PyUnicode_AsString(obj) : 0;
+      return PyUnicode_Check(obj) ? const_cast<void*>(reinterpret_cast<const void*>(_PyUnicode_AsString(obj))) : 0; 
   }
 #endif
 
