$NetBSD: patch-mozilla_netwerk_ipc_NeckoParent.cpp,v 1.1 2015/06/29 21:27:01 markd Exp $

--- mozilla/netwerk/ipc/NeckoParent.cpp.orig	2015-05-07 18:53:46.000000000 +0000
+++ mozilla/netwerk/ipc/NeckoParent.cpp
@@ -359,7 +359,7 @@ NeckoParent::RecvPRtspChannelConstructor
   RtspChannelParent* p = static_cast<RtspChannelParent*>(aActor);
   return p->Init(aConnectArgs);
 #else
-  return nullptr;
+  return false;
 #endif
 }
 
