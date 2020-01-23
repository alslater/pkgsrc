$NetBSD$

AS: For memset_s

--- crypto/apr_crypto.c.orig	2017-06-13 20:28:00.000000000 +0000
+++ crypto/apr_crypto.c
@@ -14,6 +14,8 @@
  * limitations under the License.
  */
 
+#define __STDC_WANT_LIB_EXT1__ 1
+
 #include <ctype.h>
 #include <stdio.h>
 
