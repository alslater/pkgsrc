$NetBSD$

--- Lib/urllib2.py.orig	2020-04-19 21:13:39.000000000 +0000
+++ Lib/urllib2.py
@@ -856,7 +856,7 @@ class AbstractBasicAuthHandler:
 
     # allow for double- and single-quoted realm values
     # (single quotes are a violation of the RFC, but appear in the wild)
-    rx = re.compile('(?:.*,)*[ \t]*([^ \t]+)[ \t]+'
+    rx = re.compile('(?:.*,)*[ \t]*([^ \t,]+)[ \t]+'
                     'realm=(["\']?)([^"\']*)\\2', re.I)
 
     # XXX could pre-emptively send auth info already accepted (RFC 2617,
