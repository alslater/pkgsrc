$NetBSD$

Backport https://github.com/haproxy/haproxy/commit/d6f196654 and
https://github.com/haproxy/haproxy/commit/7259fa2b8

--- src/wdt.c.orig	2020-02-13 06:58:50.000000000 +0000
+++ src/wdt.c
@@ -143,7 +143,8 @@ int init_wdt_per_thread()
 	sev.sigev_notify          = SIGEV_SIGNAL;
 	sev.sigev_signo           = WDTSIG;
 	sev.sigev_value.sival_int = tid;
-	if (timer_create(ti->clock_id, &sev, &ti->wd_timer) == -1)
+	if (timer_create(ti->clock_id, &sev, &ti->wd_timer) == -1 &&
+	    timer_create(CLOCK_REALTIME, &sev, &ti->wd_timer) == -1)
 		goto fail1;
 
 	if (!wdt_ping(tid))
@@ -156,7 +157,7 @@ int init_wdt_per_thread()
  fail1:
 	ti->wd_timer = TIMER_INVALID;
 	ha_warning("Failed to setup watchdog timer for thread %u, disabling lockup detection.\n", tid);
-	return 0;
+	return 1;
 }
 
 void deinit_wdt_per_thread()
