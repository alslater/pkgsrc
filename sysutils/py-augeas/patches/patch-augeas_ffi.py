$NetBSD$

--- augeas/ffi.py.orig	2017-08-22 10:52:24.000000000 +0000
+++ augeas/ffi.py
@@ -39,7 +39,7 @@ void aug_close(augeas *aug);
 void free(void *);
 """)
 
-lib = ffi.dlopen("augeas")
+lib = ffi.dlopen("libaugeas.so")
 
 if __name__ == "__main__":
     ffi.compile(verbose=True)
