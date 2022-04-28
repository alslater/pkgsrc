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

--- Lib/test/test_urlparse.py.orig
+++ Lib/test/test_urlparse.py
@@ -504,6 +504,54 @@ class UrlParseTestCase(unittest.TestCase
         p = urlparse.urlsplit(url)
         self.assertEqual(p.port, None)
 
+    def test_urlsplit_remove_unsafe_bytes(self):
+        # Remove ASCII tabs and newlines from input, for http common case scenario.
+        url = "h\nttp://www.python\n.org\t/java\nscript:\talert('msg\r\n')/?query\n=\tsomething#frag\nment"
+        p = urlparse.urlsplit(url)
+        self.assertEqual(p.scheme, "http")
+        self.assertEqual(p.netloc, "www.python.org")
+        self.assertEqual(p.path, "/javascript:alert('msg')/")
+        self.assertEqual(p.query, "query=something")
+        self.assertEqual(p.fragment, "fragment")
+        self.assertEqual(p.username, None)
+        self.assertEqual(p.password, None)
+        self.assertEqual(p.hostname, "www.python.org")
+        self.assertEqual(p.port, None)
+        self.assertEqual(p.geturl(), "http://www.python.org/javascript:alert('msg')/?query=something#fragment")
+
+        # Remove ASCII tabs and newlines from input as bytes, for http common case scenario.
+        url = b"h\nttp://www.python\n.org\t/java\nscript:\talert('msg\r\n')/?query\n=\tsomething#frag\nment"
+        p = urlparse.urlsplit(url)
+        self.assertEqual(p.scheme, b"http")
+        self.assertEqual(p.netloc, b"www.python.org")
+        self.assertEqual(p.path, b"/javascript:alert('msg')/")
+        self.assertEqual(p.query, b"query=something")
+        self.assertEqual(p.fragment, b"fragment")
+        self.assertEqual(p.username, None)
+        self.assertEqual(p.password, None)
+        self.assertEqual(p.hostname, b"www.python.org")
+        self.assertEqual(p.port, None)
+        self.assertEqual(p.geturl(), b"http://www.python.org/javascript:alert('msg')/?query=something#fragment")
+
+        # any scheme
+        url = "x-new-scheme\t://www.python\n.org\t/java\nscript:\talert('msg\r\n')/?query\n=\tsomething#frag\nment"
+        p = urlparse.urlsplit(url)
+        self.assertEqual(p.geturl(), "x-new-scheme://www.python.org/javascript:alert('msg')/?query=something#fragment")
+
+        # Remove ASCII tabs and newlines from input as bytes, any scheme.
+        url = b"x-new-scheme\t://www.python\n.org\t/java\nscript:\talert('msg\r\n')/?query\n=\tsomething#frag\nment"
+        p = urlparse.urlsplit(url)
+        self.assertEqual(p.geturl(), b"x-new-scheme://www.python.org/javascript:alert('msg')/?query=something#fragment")
+
+        # Unsafe bytes is not returned from urlparse cache.
+        # scheme is stored after parsing, sending an scheme with unsafe bytes *will not* return an unsafe scheme
+        url = "https://www.python\n.org\t/java\nscript:\talert('msg\r\n')/?query\n=\tsomething#frag\nment"
+        scheme = "htt\nps"
+        for _ in range(2):
+            p = urlparse.urlsplit(url, scheme=scheme)
+            self.assertEqual(p.scheme, "https")
+            self.assertEqual(p.geturl(), "https://www.python.org/javascript:alert('msg')/?query=something#fragment")
+
     def test_issue14072(self):
         p1 = urlparse.urlsplit('tel:+31-641044153')
         self.assertEqual(p1.scheme, 'tel')
