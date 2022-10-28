$NetBSD$

--- src/intel/genxml/gen_sort_tags.py.orig	2019-12-04 22:10:14.000000000 +0000
+++ src/intel/genxml/gen_sort_tags.py
@@ -65,7 +65,7 @@ def add_struct_refs(items, node):
         return
     if node.tag != 'struct' and node.tag != 'group':
         return
-    for c in node.getchildren():
+    for c in list(node):
         add_struct_refs(items, c)
 
 
@@ -115,7 +115,7 @@ def print_node(f, offset, node):
     for a in attribs:
         if a in node.attrib:
             f.write(' {0}="{1}"'.format(a, node.attrib[a]))
-    children = node.getchildren()
+    children = list(node)
     if len(children) > 0:
         f.write('>\n')
         for c in children:
@@ -138,7 +138,7 @@ def main():
     enum_dict = {}
     for e in enums:
         values = e.findall('./value')
-        e[:] = sorted(e.getchildren(), key=get_value)
+        e[:] = sorted(list(e), key=get_value)
         enum_dict[e.attrib['name']] = e
 
     # Structs are a bit annoying because they can refer to each other. We sort
@@ -147,7 +147,7 @@ def main():
     structs = sorted(xml.findall('./struct'), key=get_name)
     wrapped_struct_dict = {}
     for s in structs:
-        s[:] = sorted(s.getchildren(), key=get_start)
+        s[:] = sorted(list(s), key=get_start)
         ws = Struct(s)
         wrapped_struct_dict[ws.name] = ws
 
@@ -161,11 +161,11 @@ def main():
 
     instructions = sorted(xml.findall('./instruction'), key=get_name)
     for i in instructions:
-        i[:] = sorted(i.getchildren(), key=get_start)
+        i[:] = sorted(list(i), key=get_start)
 
     registers = sorted(xml.findall('./register'), key=get_name)
     for r in registers:
-        r[:] = sorted(r.getchildren(), key=get_start)
+        r[:] = sorted(list(r), key=get_start)
 
     genxml[:] = enums + sorted_structs.values() + instructions + registers
 
