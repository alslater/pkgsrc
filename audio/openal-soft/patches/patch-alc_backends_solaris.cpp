$NetBSD$

--- alc/backends/solaris.cpp.orig	2019-11-28 08:45:08.000000000 +0000
+++ alc/backends/solaris.cpp
@@ -34,6 +34,7 @@
 #include <errno.h>
 #include <poll.h>
 #include <math.h>
+#include <string.h>
 
 #include <thread>
 #include <functional>
