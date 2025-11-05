$NetBSD$

--- vendor/curl-sys/curl/lib/http.c.orig	2022-08-09 00:43:07.000000000 +0000
+++ vendor/curl-sys/curl/lib/http.c
@@ -399,8 +399,6 @@ static bool pickoneauth(struct auth *pic
     pick->picked = CURLAUTH_DIGEST;
   else if(avail & CURLAUTH_NTLM)
     pick->picked = CURLAUTH_NTLM;
-  else if(avail & CURLAUTH_NTLM_WB)
-    pick->picked = CURLAUTH_NTLM_WB;
   else if(avail & CURLAUTH_BASIC)
     pick->picked = CURLAUTH_BASIC;
   else if(avail & CURLAUTH_AWS_SIGV4)
@@ -491,9 +489,7 @@ static CURLcode http_perhapsrewind(struc
 #if defined(USE_NTLM)
     /* There is still data left to send */
     if((data->state.authproxy.picked == CURLAUTH_NTLM) ||
-       (data->state.authhost.picked == CURLAUTH_NTLM) ||
-       (data->state.authproxy.picked == CURLAUTH_NTLM_WB) ||
-       (data->state.authhost.picked == CURLAUTH_NTLM_WB)) {
+       (data->state.authhost.picked == CURLAUTH_NTLM)) {
       if(((expectsend - bytessent) < 2000) ||
          (conn->http_ntlm_state != NTLMSTATE_NONE) ||
          (conn->proxy_ntlm_state != NTLMSTATE_NONE)) {
@@ -714,15 +710,6 @@ output_auth_headers(struct Curl_easy *da
   }
   else
 #endif
-#if defined(USE_NTLM) && defined(NTLM_WB_ENABLED)
-  if(authstatus->picked == CURLAUTH_NTLM_WB) {
-    auth = "NTLM_WB";
-    result = Curl_output_ntlm_wb(data, conn, proxy);
-    if(result)
-      return result;
-  }
-  else
-#endif
 #ifndef CURL_DISABLE_CRYPTO_AUTH
   if(authstatus->picked == CURLAUTH_DIGEST) {
     auth = "Digest";
@@ -989,31 +976,15 @@ CURLcode Curl_http_input_auth(struct Cur
       /* NTLM support requires the SSL crypto libs */
       if(checkprefix("NTLM", auth) && is_valid_auth_separator(auth[4])) {
         if((authp->avail & CURLAUTH_NTLM) ||
-           (authp->avail & CURLAUTH_NTLM_WB) ||
            Curl_auth_is_ntlm_supported()) {
           *availp |= CURLAUTH_NTLM;
           authp->avail |= CURLAUTH_NTLM;
 
-          if(authp->picked == CURLAUTH_NTLM ||
-             authp->picked == CURLAUTH_NTLM_WB) {
+          if(authp->picked == CURLAUTH_NTLM) {
             /* NTLM authentication is picked and activated */
             CURLcode result = Curl_input_ntlm(data, proxy, auth);
             if(!result) {
               data->state.authproblem = FALSE;
-#ifdef NTLM_WB_ENABLED
-              if(authp->picked == CURLAUTH_NTLM_WB) {
-                *availp &= ~CURLAUTH_NTLM;
-                authp->avail &= ~CURLAUTH_NTLM;
-                *availp |= CURLAUTH_NTLM_WB;
-                authp->avail |= CURLAUTH_NTLM_WB;
-
-                result = Curl_input_ntlm_wb(data, conn, proxy, auth);
-                if(result) {
-                  infof(data, "Authentication problem. Ignoring this.");
-                  data->state.authproblem = TRUE;
-                }
-              }
-#endif
             }
             else {
               infof(data, "Authentication problem. Ignoring this.");
