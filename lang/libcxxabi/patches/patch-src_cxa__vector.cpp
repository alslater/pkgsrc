$NetBSD$

--- src/cxa_vector.cpp.orig	2019-04-11 17:16:35.000000000 +0000
+++ src/cxa_vector.cpp
@@ -127,7 +127,7 @@ void throw_bad_array_new_length() {
 
 bool mul_overflow(size_t x, size_t y, size_t *res) {
 #if (defined(_LIBCXXABI_COMPILER_CLANG) && __has_builtin(__builtin_mul_overflow)) \
-    || defined(_LIBCXXABI_COMPILER_GCC)
+    || (defined(_LIBCXXABI_COMPILER_GCC) && __has_builtin(__builtin_mul_overflow)) 
     return __builtin_mul_overflow(x, y, res);
 #else
     *res = x * y;
@@ -137,7 +137,7 @@ bool mul_overflow(size_t x, size_t y, si
 
 bool add_overflow(size_t x, size_t y, size_t *res) {
 #if (defined(_LIBCXXABI_COMPILER_CLANG) && __has_builtin(__builtin_add_overflow)) \
-    || defined(_LIBCXXABI_COMPILER_GCC)
+    || (defined(_LIBCXXABI_COMPILER_GCC) && __has_builtin(__builtin_mul_overflow)) 
   return __builtin_add_overflow(x, y, res);
 #else
   *res = x + y;
