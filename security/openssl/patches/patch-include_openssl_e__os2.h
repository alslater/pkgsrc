$NetBSD$

AS - fix noreturn for c++17

--- include/openssl/e_os2.h.orig	2019-09-10 13:13:07.000000000 +0000
+++ include/openssl/e_os2.h
@@ -279,7 +279,7 @@ typedef unsigned __int64 uint64_t;
 #  define ossl_inline inline
 # endif
 
-# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
+# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(__cplusplus)
 #  define ossl_noreturn _Noreturn
 # elif defined(__GNUC__) && __GNUC__ >= 2
 #  define ossl_noreturn __attribute__((noreturn))
