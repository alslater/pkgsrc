$NetBSD$

--- src/pty.c.orig	2015-10-12 14:34:49.000000000 +0000
+++ src/pty.c
@@ -931,12 +931,15 @@ _vte_pty_read_ptypair(int tunnel, int *p
 		msg.msg_namelen = 0;
 		msg.msg_iov = &vec;
 		msg.msg_iovlen = 1;
+#if defined(CMSG_FIRSTHDR)
 		msg.msg_control = control;
 		msg.msg_controllen = sizeof(control);
+#endif
 		ret = recvmsg(tunnel, &msg, PTY_RECVMSG_FLAGS);
 		if (ret == -1) {
 			return;
 		}
+#if defined(CMSG_FIRSTHDR)
 		for (cmsg = CMSG_FIRSTHDR(&msg);
 		     cmsg != NULL;
 		     cmsg = CMSG_NXTHDR(&msg, cmsg)) {
@@ -955,6 +958,7 @@ _vte_pty_read_ptypair(int tunnel, int *p
 				}
 			}
 		}
+#endif
 	}
 }
 #elif defined (I_RECVFD)
