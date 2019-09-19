--- src/mkerrnos.awk.orig
+++ src/mkerrnos.awk
@@ -83,7 +83,7 @@ header {
 }
 
 !header {
-  sub (/\#.+/, "");
+  sub (/#.+/, "");
   sub (/[ 	]+$/, ""); # Strip trailing space and tab characters.
 
   if (/^$/)
