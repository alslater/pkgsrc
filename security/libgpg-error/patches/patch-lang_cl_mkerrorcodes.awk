--- lang/cl/mkerrcodes.awk.orig
+++ lang/cl/mkerrcodes.awk
@@ -122,7 +122,7 @@ header {
 }
 
 !header {
-  sub (/\#.+/, "");
+  sub (/#.+/, "");
   sub (/[ 	]+$/, ""); # Strip trailing space and tab characters.
 
   if (/^$/)
