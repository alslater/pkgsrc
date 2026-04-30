$NetBSD: patch-include_haproxy_server-t.h,v 1.1 2021/12/09 10:36:07 jperkin Exp $

Avoid 'struct queue' conflict.

--- include/haproxy/server-t.h.orig	2026-03-20 09:15:21.000000000 +0000
+++ include/haproxy/server-t.h
@@ -323,7 +323,7 @@ struct server {
 	unsigned int max_used_conns;            /* Max number of used connections (the counter is reset at each connection purges */
 	unsigned int est_need_conns;            /* Estimate on the number of needed connections (max of curr and previous max_used) */
 
-	struct queue queue;			/* pending connections */
+	struct haqueue queue;			/* pending connections */
 	struct mt_list sess_conns;		/* list of private conns managed by a session on this server */
 	unsigned int dequeuing;                 /* non-zero = dequeuing in progress (atomic) */
 
