$NetBSD: patch-modules_pyFixed.cc,v 1.1 2015/12/25 20:09:28 joerg Exp $

--- modules/pyFixed.cc.orig	2017-02-20 22:45:59.000000000 +0000
+++ modules/pyFixed.cc
@@ -70,7 +70,7 @@ omniPy::newFixedObject(PyObject* self, P
       }
 #if (PY_VERSION_HEX <= 0x03000000)
       else if (PyInt_Check(pyv)) {
-	long l = PyInt_AsLong(pyv);
+	CORBA::LongLong l = PyInt_AsLong(pyv);
 	CORBA::Fixed f(l);
 	return omniPy::newFixedObject(f);
       }
@@ -112,7 +112,7 @@ omniPy::newFixedObject(PyObject* self, P
 
 #if (PY_VERSION_HEX <= 0x03000000)
 	if (PyInt_Check(pyv)) {
-	  long l = PyInt_AsLong(pyv);
+	  CORBA::LongLong l = PyInt_AsLong(pyv);
 	  CORBA::Fixed f(l);
 	  f.PR_changeScale(scale);
 	  f.PR_setLimits(digits, scale);
@@ -366,7 +366,7 @@ extern "C" {
   fixed_coerce(PyObject** pv, PyObject** pw)
   {
     if (PyInt_Check(*pw)) {
-      long l = PyInt_AsLong(*pw);
+      CORBA::LongLong l = PyInt_AsLong(*pw);
       CORBA::Fixed f(l);
       *pw = omniPy::newFixedObject(f);
       Py_INCREF(*pv);
