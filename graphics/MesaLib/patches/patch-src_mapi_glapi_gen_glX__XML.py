$NetBSD$

--- src/mapi/glapi/gen/glX_XML.py.orig	2019-12-04 22:10:14.000000000 +0000
+++ src/mapi/glapi/gen/glX_XML.py
@@ -48,7 +48,7 @@ class glx_enum(gl_XML.gl_enum):
 
         self.functions = {}
 
-        for child in element.getchildren():
+        for child in list(element):
             if child.tag == "size":
                 n = child.get( "name" )
                 c = child.get( "count" )
@@ -130,7 +130,7 @@ class glx_function(gl_XML.gl_function):
                     self.counter_list.append(param.counter)
 
 
-        for child in element.getchildren():
+        for child in list(element):
             if child.tag == "glx":
                 rop = child.get( 'rop' )
                 sop = child.get( 'sop' )
