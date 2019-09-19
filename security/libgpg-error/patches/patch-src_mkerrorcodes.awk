--- src/mkerrcodes.awk.orig
+++ src/mkerrcodes.awk
@@ -85,7 +85,7 @@ header {
 }
 
 !header {
-  sub (/\#.+/, "");
+  sub (/#.+/, "");
   sub (/[ 	]+$/, ""); # Strip trailing space and tab characters.
 
   if (/^$/)
