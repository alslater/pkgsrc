$NetBSD$

--- libs/python/src/exec.cpp.orig	2025-03-31 15:03:12.241318097 +0000
+++ libs/python/src/exec.cpp
@@ -86,7 +86,7 @@ object BOOST_PYTHON_DECL exec_file(str f
   char *f = python::extract<char *>(filename);
   // Let python open the file to avoid potential binary incompatibilities.
 #if PY_VERSION_HEX >= 0x03040000
-  FILE *fs = _Py_fopen(f, "r");
+  FILE *fs = fopen(f, "r");
 #elif PY_VERSION_HEX >= 0x03000000
   PyObject *fo = Py_BuildValue("s", f);
   FILE *fs = _Py_fopen(fo, "r");
