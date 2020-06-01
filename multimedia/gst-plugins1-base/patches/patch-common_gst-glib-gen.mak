$NetBSD$

--- common/gst-glib-gen.mak.orig	2019-04-19 09:16:22.000000000 +0000
+++ common/gst-glib-gen.mak
@@ -8,7 +8,8 @@
 #glib_gen_decl_banner=GST_EXPORT
 #glib_gen_decl_include=\#include <gst/foo/foo-prelude.h>
 
-enum_headers=$(foreach h,$(glib_enum_headers),\n\#include \"$(h)\")
+H := \#
+enum_headers=$(foreach h,$(glib_enum_headers),\n$(H)include \"$(h)\")
 
 # these are all the rules generating the relevant files
 $(glib_gen_basename)-marshal.h: $(glib_gen_basename)-marshal.list
