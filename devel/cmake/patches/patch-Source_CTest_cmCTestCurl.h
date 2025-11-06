$NetBSD$

--- Source/CTest/cmCTestCurl.h.orig	2022-11-01 14:55:49.000000000 +0000
+++ Source/CTest/cmCTestCurl.h
@@ -44,7 +44,7 @@ private:
   std::vector<std::string> HttpHeaders;
   std::string HTTPProxyAuth;
   std::string HTTPProxy;
-  curl_proxytype HTTPProxyType;
+  long int HTTPProxyType;
   bool VerifyHostOff;
   bool VerifyPeerOff;
   bool UseHttp10;
