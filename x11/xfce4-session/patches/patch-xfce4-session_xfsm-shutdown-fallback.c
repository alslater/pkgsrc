$NetBSD$

--- xfce4-session/xfsm-shutdown-fallback.c.orig	2019-08-11 20:11:06.000000000 +0000
+++ xfce4-session/xfsm-shutdown-fallback.c
@@ -388,13 +388,16 @@ xfsm_shutdown_fallback_try_action (XfsmS
       xfsm_helper_action = "restart";
       cmd = REBOOT_CMD;
       break;
-    case XFSM_SHUTDOWN_SUSPEND:
+#if defined(UP_BACKEND_SUSPEND_COMMAND)
+   case XFSM_SHUTDOWN_SUSPEND:
       xfsm_helper_action = "suspend";
       cmd = UP_BACKEND_SUSPEND_COMMAND;
       /* On suspend we try to lock the screen */
       if (!lock_screen (error))
         return FALSE;
       break;
+#endif
+#if defined(UP_BACKEND_HIBERNATE_COMMAND)
     case XFSM_SHUTDOWN_HIBERNATE:
       xfsm_helper_action = "hibernate";
       cmd = UP_BACKEND_HIBERNATE_COMMAND;
@@ -409,6 +412,7 @@ xfsm_shutdown_fallback_try_action (XfsmS
       if (!lock_screen (error))
         return FALSE;
       break;
+#endif
     default:
       return FALSE;
   }
