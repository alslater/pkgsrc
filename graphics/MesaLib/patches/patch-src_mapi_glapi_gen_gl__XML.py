$NetBSD$

--- src/mapi/glapi/gen/gl_XML.py.orig	2019-12-04 22:10:14.000000000 +0000
+++ src/mapi/glapi/gen/gl_XML.py
@@ -706,7 +706,7 @@ class gl_function( gl_item ):
 
         parameters = []
         return_type = "void"
-        for child in element.getchildren():
+        for child in list(element):
             if child.tag == "return":
                 return_type = child.get( "type", "void" )
             elif child.tag == "param":
@@ -736,7 +736,7 @@ class gl_function( gl_item ):
                 if param.is_image():
                     self.images.append( param )
 
-        if element.getchildren():
+        if list(element):
             self.initialized = 1
             self.entry_point_parameters[name] = parameters
         else:
@@ -866,7 +866,7 @@ class gl_api(object):
 
 
     def process_OpenGLAPI(self, file_name, element):
-        for child in element.getchildren():
+        for child in list(element):
             if child.tag == "category":
                 self.process_category( child )
             elif child.tag == "OpenGLAPI":
@@ -886,7 +886,7 @@ class gl_api(object):
         [cat_type, key] = classify_category(cat_name, cat_number)
         self.categories[cat_type][key] = [cat_name, cat_number]
 
-        for child in cat.getchildren():
+        for child in list(cat):
             if child.tag == "function":
                 func_name = real_function_name( child )
 
