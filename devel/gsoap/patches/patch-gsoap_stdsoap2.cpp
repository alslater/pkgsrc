$NetBSD$

--- gsoap/stdsoap2.cpp.orig	2018-02-18 20:57:30.000000000 +0000
+++ gsoap/stdsoap2.cpp
@@ -1080,7 +1080,19 @@ frecv(struct soap *soap, char *s, size_t
         if (r > 0)
           return (size_t)r;
         err = SSL_get_error(soap->ssl, r);
-        if (err != SSL_ERROR_NONE && err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE)
+        if (err == SSL_ERROR_SYSCALL
+         && retries-- > 0
+         && (ERR_peek_error() == 0
+             ? (errno == EAGAIN || errno == EWOULDBLOCK)
+             : (ERR_GET_LIB(ERR_peek_error()) == ERR_LIB_SYS
+                && (ERR_GET_REASON(ERR_peek_error()) == EAGAIN
+                    || ERR_GET_REASON(ERR_peek_error()) == EWOULDBLOCK))))
+        { /* SSL_ERROR_SYSCALL/EAGAIN on SSL_read: non-blocking socket not ready; retry. */
+          ERR_clear_error();
+          if (tcp_select(soap, sk, SOAP_TCP_SELECT_RCV | SOAP_TCP_SELECT_ERR, -100000) < 0)
+            return 0;
+        }
+        else if (err != SSL_ERROR_NONE && err != SSL_ERROR_WANT_READ && err != SSL_ERROR_WANT_WRITE)
           return 0;
       }
       else if (soap->bio)
@@ -5747,6 +5759,26 @@ again:
             return soap->socket = SOAP_INVALID_SOCKET;
           }
         }
+        else if (err == SSL_ERROR_SYSCALL
+              && retries-- > 0
+              && (ERR_peek_error() == 0
+                  ? (errno == EAGAIN || errno == EWOULDBLOCK)
+                  : (ERR_GET_LIB(ERR_peek_error()) == ERR_LIB_SYS
+                     && (ERR_GET_REASON(ERR_peek_error()) == EAGAIN
+                         || ERR_GET_REASON(ERR_peek_error()) == EWOULDBLOCK))))
+        { /* SSL_ERROR_SYSCALL/EAGAIN: non-blocking socket not ready; retry.
+             Empty error stack means plain syscall EAGAIN; non-empty means
+             OpenSSL 3.5+ pushed ERR_LIB_SYS onto the stack. Both are retryable. */
+          ERR_clear_error();
+          int s = tcp_select(soap, sk, SOAP_TCP_SELECT_RCV | SOAP_TCP_SELECT_ERR, -100000);
+          if (s < 0)
+          {
+            DBGLOG(TEST, SOAP_MESSAGE(fdebug, "SSL_connect/select error in tcp_connect\n"));
+            soap_set_receiver_error(soap, soap_ssl_error(soap, r), "SSL_connect failed in tcp_connect()", SOAP_TCP_ERROR);
+            soap->fclosesocket(soap, sk);
+            return soap->socket = SOAP_INVALID_SOCKET;
+          }
+        }
         else
         {
           soap_set_receiver_error(soap, soap_ssl_error(soap, r), "SSL_connect error in tcp_connect()", SOAP_SSL_ERROR);
@@ -6313,6 +6345,24 @@ tcp_disconnect(struct soap *soap)
         }
       }
     }
+    /* SSL_ERROR_SYSCALL/EAGAIN during shutdown on a non-blocking socket:
+       empty error stack means plain syscall EAGAIN; non-empty means
+       OpenSSL 3.5+ pushed ERR_LIB_SYS. Both are retryable. */
+    if (r < 0)
+    {
+      int serr = SSL_get_error(soap->ssl, r);
+      unsigned long e = ERR_peek_error();
+      if (serr == SSL_ERROR_SYSCALL
+       && (e == 0
+           ? (errno == EAGAIN || errno == EWOULDBLOCK)
+           : (ERR_GET_LIB(e) == ERR_LIB_SYS
+              && (ERR_GET_REASON(e) == EAGAIN || ERR_GET_REASON(e) == EWOULDBLOCK))))
+      {
+        ERR_clear_error();
+        tcp_select(soap, soap->socket, SOAP_TCP_SELECT_RCV | SOAP_TCP_SELECT_SND | SOAP_TCP_SELECT_ERR, 1);
+        r = SSL_shutdown(soap->ssl);
+      }
+    }
     if (r != 1)
     {
       DBGLOG(TEST, SOAP_MESSAGE(fdebug, "Shutdown failed: %d\n", SSL_get_error(soap->ssl, r)));
