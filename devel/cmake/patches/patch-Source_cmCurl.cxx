$NetBSD$

--- Source/cmCurl.cxx.orig	2022-11-01 14:55:49.000000000 +0000
+++ Source/cmCurl.cxx
@@ -70,7 +70,7 @@ std::string cmCurlSetNETRCOption(::CURL*
                                  const std::string& netrc_file)
 {
   std::string e;
-  CURL_NETRC_OPTION curl_netrc_level = CURL_NETRC_LAST;
+  long int curl_netrc_level = CURL_NETRC_LAST;
   ::CURLcode res;
 
   if (!netrc_level.empty()) {
