$NetBSD$

--- common/gst-glib-gen.mak.orig	2020-05-16 07:54:54.234305653 +0000
+++ common/gst-glib-gen.mak
@@ -1,14 +1,16 @@
 # these are the variables your Makefile.am should set
 # the example is based on the colorbalance interface
 
+H := \#
+
 #glib_enum_headers=$(colorbalance_headers)
 #glib_enum_define=GST_COLOR_BALANCE
 #glib_gen_prefix=gst_color_balance
 #glib_gen_basename=colorbalance
 #glib_gen_decl_banner=GST_EXPORT
-#glib_gen_decl_include=\#include <gst/foo/foo-prelude.h>
+#glib_gen_decl_include=$(H)include <gst/foo/foo-prelude.h>
 
-enum_headers=$(foreach h,$(glib_enum_headers),\n\#include \"$(h)\")
+enum_headers=$(foreach h,$(glib_enum_headers),\n$(H)include \"$(h)\")
 
 # these are all the rules generating the relevant files
 $(glib_gen_basename)-marshal.h: $(glib_gen_basename)-marshal.list
