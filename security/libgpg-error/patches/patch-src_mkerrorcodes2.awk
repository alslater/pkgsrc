--- src/mkerrcodes2.awk.orig
+++ src/mkerrcodes2.awk
@@ -91,7 +91,7 @@ header {
 }
 
 !header {
-  sub (/\#.+/, "");
+  sub (/#.+/, "");
   sub (/[ 	]+$/, ""); # Strip trailing space and tab characters.
 
   if (/^$/)
