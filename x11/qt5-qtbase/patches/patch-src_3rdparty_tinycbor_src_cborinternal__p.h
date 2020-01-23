$NetBSD$

--- src/3rdparty/tinycbor/src/cborinternal_p.h.orig	2019-10-25 07:16:48.000000000 +0000
+++ src/3rdparty/tinycbor/src/cborinternal_p.h
@@ -88,8 +88,8 @@ static inline double decode_half(unsigne
     int exp = (half >> 10) & 0x1f;
     int mant = half & 0x3ff;
     double val;
-    if (exp == 0) val = ldexp(mant, -24);
-    else if (exp != 31) val = ldexp(mant + 1024, exp - 25);
+    if (exp == 0) val = ldexp((double)mant, -24);
+    else if (exp != 31) val = ldexp((double)(mant + 1024), exp - 25);
     else val = mant == 0 ? INFINITY : NAN;
     return half & 0x8000 ? -val : val;
 }
