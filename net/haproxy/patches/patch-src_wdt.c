$NetBSD$

Backport https://github.com/haproxy/haproxy/commit/d6f196654 and
https://github.com/haproxy/haproxy/commit/7259fa2b8

--- src/wdt.c.orig	2022-05-13 15:43:21.000000000 +0000
+++ src/wdt.c
@@ -141,7 +141,8 @@ int init_wdt_per_thread()
 	sev.sigev_notify          = SIGEV_SIGNAL;
 	sev.sigev_signo           = WDTSIG;
 	sev.sigev_value.sival_int = tid;
-	if (timer_create(ti->clock_id, &sev, &ti->wd_timer) == -1)
+	if (timer_create(ti->clock_id, &sev, &ti->wd_timer) == -1 &&
+	    timer_create(CLOCK_REALTIME, &sev, &ti->wd_timer) == -1)
 		goto fail1;
 
 	if (!wdt_ping(tid))
