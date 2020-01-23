$NetBSD$

--- lib/replace/system/select.h.orig	2019-12-06 09:46:56.000000000 +0000
+++ lib/replace/system/select.h
@@ -30,6 +30,7 @@
 #include <sys/select.h>
 #endif
 
+#undef HAVE_SYS_EPOLL_H
 #ifdef HAVE_SYS_EPOLL_H
 #include <sys/epoll.h>
 #endif
