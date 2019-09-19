--- src/mkerrcodes1.awk.orig
+++ src/mkerrcodes1.awk
@@ -81,7 +81,7 @@ header {
 }
 
 !header {
-  sub (/\#.+/, "");
+  sub (/#.+/, "");
   sub (/[ 	]+$/, ""); # Strip trailing space and tab characters.
 
   if (/^$/)
