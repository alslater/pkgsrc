$NetBSD$

    http://www.squid-cache.org/Advisories/SQUID-2018_4.txt
    http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2018-19131

--- src/ssl/ErrorDetail.cc.orig	2019-02-04 15:02:36.107882302 +0000
+++ src/ssl/ErrorDetail.cc
@@ -8,6 +8,8 @@
 
 #include "squid.h"
 #include "errorpage.h"
+#include "fatal.h"
+#include "html_quote.h"
 #include "ssl/ErrorDetail.h"
 
 #include <climits>
@@ -432,8 +434,11 @@ const char  *Ssl::ErrorDetail::subject()
 {
     if (broken_cert.get()) {
         static char tmpBuffer[256]; // A temporary buffer
-        if (X509_NAME_oneline(X509_get_subject_name(broken_cert.get()), tmpBuffer, sizeof(tmpBuffer)))
-            return tmpBuffer;
+        if (X509_NAME_oneline(X509_get_subject_name(broken_cert.get()), tmpBuffer, sizeof(tmpBuffer))) {
+            // quote to avoid possible html code injection through
+            // certificate subject
+            return html_quote(tmpBuffer);
+        }
     }
     return "[Not available]";
 }
@@ -461,8 +466,11 @@ const char *Ssl::ErrorDetail::cn() const
         static String tmpStr;  ///< A temporary string buffer
         tmpStr.clean();
         Ssl::matchX509CommonNames(broken_cert.get(), &tmpStr, copy_cn);
-        if (tmpStr.size())
-            return tmpStr.termedBuf();
+        if (tmpStr.size()) {
+            // quote to avoid possible html code injection through
+            // certificate subject
+            return html_quote(tmpStr.termedBuf());
+        }
     }
     return "[Not available]";
 }
@@ -474,8 +482,11 @@ const char *Ssl::ErrorDetail::ca_name()
 {
     if (broken_cert.get()) {
         static char tmpBuffer[256]; // A temporary buffer
-        if (X509_NAME_oneline(X509_get_issuer_name(broken_cert.get()), tmpBuffer, sizeof(tmpBuffer)))
-            return tmpBuffer;
+        if (X509_NAME_oneline(X509_get_issuer_name(broken_cert.get()), tmpBuffer, sizeof(tmpBuffer))) {
+            // quote to avoid possible html code injection through
+            // certificate issuer subject
+            return html_quote(tmpBuffer);
+        }
     }
     return "[Not available]";
 }
