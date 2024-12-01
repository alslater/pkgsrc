$NetBSD: patch-src_queue.c,v 1.1 2021/12/09 10:36:07 jperkin Exp $

Avoid 'struct queue' conflict.

--- src/queue.c.orig	2024-09-19 15:54:06.000000000 +0000
+++ src/queue.c
@@ -177,7 +177,7 @@ static inline void pendconn_queue_unlock
  */
 void pendconn_unlink(struct pendconn *p)
 {
-	struct queue  *q  = p->queue;
+	struct haqueue  *q  = p->queue;
 	struct proxy  *px = q->px;
 	struct server *sv = q->sv;
 	uint oldidx;
@@ -439,7 +439,7 @@ struct pendconn *pendconn_add(struct str
 	struct pendconn *p;
 	struct proxy    *px;
 	struct server   *srv;
-	struct queue    *q;
+	struct haqueue    *q;
 	unsigned int *max_ptr;
 	unsigned int old_max, new_max;
 
@@ -639,7 +639,7 @@ int pendconn_dequeue(struct stream *strm
  */
 int pendconn_must_try_again(struct pendconn *p)
 {
-	struct queue  *q  = p->queue;
+	struct haqueue  *q  = p->queue;
 	struct proxy  *px = q->px;
 	struct server *sv = q->sv;
 	int ret = 0;
