$NetBSD$

--- src/inspector_agent.cc.orig	2017-01-31 22:19:51.000000000 +0000
+++ src/inspector_agent.cc
@@ -74,11 +74,11 @@ std::string StringViewToUtf8(const Strin
 
   size_t result_length = view.length() * sizeof(*source);
   std::string result(result_length, '\0');
-  UnicodeString utf16(unicodeSource, view.length());
+  icu::UnicodeString utf16(unicodeSource, view.length());
   // ICU components for std::string compatibility are not enabled in build...
   bool done = false;
   while (!done) {
-    CheckedArrayByteSink sink(&result[0], result_length);
+    icu::CheckedArrayByteSink sink(&result[0], result_length);
     utf16.toUTF8(sink);
     result_length = sink.NumberOfBytesAppended();
     result.resize(result_length);
@@ -88,8 +88,8 @@ std::string StringViewToUtf8(const Strin
 }
 
 std::unique_ptr<StringBuffer> Utf8ToStringView(const std::string& message) {
-  UnicodeString utf16 =
-      UnicodeString::fromUTF8(StringPiece(message.data(), message.length()));
+  icu::UnicodeString utf16 =
+      icu::UnicodeString::fromUTF8(icu::StringPiece(message.data(), message.length()));
   StringView view(reinterpret_cast<const uint16_t*>(utf16.getBuffer()),
                   utf16.length());
   return StringBuffer::create(view);
