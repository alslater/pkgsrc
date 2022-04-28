Fixes CVE-2022-0391.
Desc:
  A flaw was found in Python, specifically within the urllib.parse module. This
  module helps break Uniform Resource Locator (URL) strings into components.
  The issue involves how the urlparse method does not sanitize input and allows
  characters like '\r' and '\n' in the URL path. This flaw allows an attacker
  to input a crafted URL, leading to injection attacks.

Upstream bug: https://bugs.python.org/issue43882

Backported from:
https://github.com/python/cpython/pull/25923

--- Lib/urlparse.py.orig
+++ Lib/urlparse.py
@@ -62,6 +62,9 @@ scheme_chars = ('abcdefghijklmnopqrstuvw
                 '0123456789'
                 '+-.')
 
+# Unsafe bytes to be removed per WHATWG spec
+_UNSAFE_URL_BYTES_TO_REMOVE = ['\t', '\r', '\n']
+
 MAX_CACHE_SIZE = 20
 _parse_cache = {}
 
@@ -184,12 +187,19 @@ def _checknetloc(netloc):
                              "under NFKC normalization"
                              % netloc)
 
+def _remove_unsafe_bytes_from_url(url):
+    for b in _UNSAFE_URL_BYTES_TO_REMOVE:
+        url = url.replace(b, "")
+    return url
+
 def urlsplit(url, scheme='', allow_fragments=True):
     """Parse a URL into 5 components:
     <scheme>://<netloc>/<path>?<query>#<fragment>
     Return a 5-tuple: (scheme, netloc, path, query, fragment).
     Note that we don't break the components up in smaller bits
     (e.g. netloc is a single string) and we don't expand % escapes."""
+    url = _remove_unsafe_bytes_from_url(url)
+    scheme = _remove_unsafe_bytes_from_url(scheme)
     allow_fragments = bool(allow_fragments)
     key = url, scheme, allow_fragments, type(url), type(scheme)
     cached = _parse_cache.get(key, None)
