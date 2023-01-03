$NetBSD$

--- xcbgen/align.py.orig	2018-03-05 09:18:15.000000000 +0000
+++ xcbgen/align.py
@@ -2,7 +2,7 @@
 This module contains helper classes for alignment arithmetic and checks
 '''
 
-from fractions import gcd
+from math import gcd
 
 class Alignment(object):
 
