$NetBSD$

--- Source/WebKit/qt/WebCoreSupport/InspectorServerQt.cpp.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/WebKit/qt/WebCoreSupport/InspectorServerQt.cpp
@@ -285,7 +285,7 @@ int InspectorServerRequestHandlerQt::web
     m_tcpConnection->putChar(0x81);
     if (length <= 125)
         m_tcpConnection->putChar(static_cast<uint8_t>(length));
-    else if (length <= pow(2, 16)) {
+    else if (length <= pow(static_cast<double>(2), 16)) {
         m_tcpConnection->putChar(126);
         quint16 length16 = qToBigEndian<quint16>(static_cast<quint16>(length));
         m_tcpConnection->write(reinterpret_cast<char*>(&length16), 2);
