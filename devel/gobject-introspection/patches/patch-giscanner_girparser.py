$NetBSD: patch-giscanner_girparser.py,v 1.1 2019/06/05 09:12:32 prlw1 Exp $

cElementTree is deprecated since Python 3.3.
(gobject-introspection requires meson 0.47.0 which requires Python 3.5.)

--- giscanner/girparser.py.orig	2019-09-09 19:22:10.000000000 +0000
+++ giscanner/girparser.py
@@ -21,7 +21,7 @@
 import os
 
 from collections import OrderedDict
-from xml.etree.cElementTree import parse
+from xml.etree.ElementTree import parse
 
 from . import ast
 from .girwriter import COMPATIBLE_GIR_VERSION
@@ -75,17 +75,17 @@ class GIRParser(object):
 
     def _find_first_child(self, node, name_or_names):
         if isinstance(name_or_names, str):
-            for child in node.getchildren():
+            for child in list(node):
                 if child.tag == name_or_names:
                     return child
         else:
-            for child in node.getchildren():
+            for child in list(node):
                 if child.tag in name_or_names:
                     return child
         return None
 
     def _find_children(self, node, name):
-        return [child for child in node.getchildren() if child.tag == name]
+        return [child for child in list(node) if child.tag == name]
 
     def _get_current_file(self):
         if not self._filename_stack:
@@ -103,7 +103,7 @@ class GIRParser(object):
             raise SystemExit("%s: Incompatible version %s (supported: %s)" %
                              (self._get_current_file(), version, COMPATIBLE_GIR_VERSION))
 
-        for node in root.getchildren():
+        for node in list(root):
             if node.tag == _corens('include'):
                 self._parse_include(node)
             elif node.tag == _corens('package'):
@@ -145,7 +145,7 @@ class GIRParser(object):
             parser_methods[_corens('function-macro')] = self._parse_function_macro
             parser_methods[_corens('function')] = self._parse_function
 
-        for node in ns.getchildren():
+        for node in list(ns):
             method = parser_methods.get(node.tag)
             if method is not None:
                 method(node)
@@ -413,7 +413,7 @@ class GIRParser(object):
     def _parse_fields(self, node, obj):
         res = []
         names = (_corens('field'), _corens('record'), _corens('union'), _corens('callback'))
-        for child in node.getchildren():
+        for child in list(node):
             if child.tag in names:
                 fieldobj = self._parse_field(child, obj)
                 res.append(fieldobj)
