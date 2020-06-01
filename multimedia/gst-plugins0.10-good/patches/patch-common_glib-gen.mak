$NetBSD$

--- common/glib-gen.mak.orig	2011-12-11 19:10:47.000000000 +0000
+++ common/glib-gen.mak
@@ -5,7 +5,8 @@
 #glib_enum_define=GST_COLOR_BALANCE
 #glib_enum_prefix=gst_color_balance
 
-enum_headers=$(foreach h,$(glib_enum_headers),\n\#include \"$(h)\")
+H := \#
+enum_headers=$(foreach h,$(glib_enum_headers),\n$(H)include \"$(h)\")
 
 # these are all the rules generating the relevant files
 %-marshal.h: %-marshal.list
