$NetBSD$

--- common/gst-glib-gen.mak.orig	2011-12-11 19:03:48.000000000 +0000
+++ common/gst-glib-gen.mak
@@ -6,7 +6,8 @@
 #glib_gen_prefix=gst_color_balance
 #glib_gen_basename=colorbalance
 
-enum_headers=$(foreach h,$(glib_enum_headers),\n\#include \"$(h)\")
+hash:=\#
+enum_headers=$(foreach h,$(glib_enum_headers),\n$(hash)include \"$(h)\")
 
 # these are all the rules generating the relevant files
 $(glib_gen_basename)-marshal.h: $(glib_gen_basename)-marshal.list
