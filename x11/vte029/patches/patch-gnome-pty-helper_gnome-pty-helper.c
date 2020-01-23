$NetBSD$

--- gnome-pty-helper/gnome-pty-helper.c.orig	2015-10-12 14:28:42.000000000 +0000
+++ gnome-pty-helper/gnome-pty-helper.c
@@ -122,6 +122,7 @@ pass_fd (int client_fd, int fd)
 	msg.msg_iovlen     = 1;
 	msg.msg_name       = NULL;
 	msg.msg_namelen    = 0;
+#if defined(CMSG_FIRSTHDR)
 	msg.msg_control    = (caddr_t) cmsgbuf;
 	msg.msg_controllen = sizeof(cmsgbuf);
 
@@ -131,6 +132,7 @@ pass_fd (int client_fd, int fd)
 	cmptr->cmsg_len   = CMSG_LEN(sizeof(int));
         fdptr = (int *) CMSG_DATA(cmptr);
         memcpy (fdptr, &fd, sizeof(int));
+#endif
 	if (sendmsg (client_fd, &msg, 0) != 1)
 		return -1;
 
