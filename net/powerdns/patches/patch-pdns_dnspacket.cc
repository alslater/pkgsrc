$NetBSD: patch-pdns_dnspacket.cc,v 1.5 2015/06/10 16:24:44 fhajny Exp $

Resolve boost symbol ambiguity.
Avoid ambiguous abs() call.

--- pdns/dnspacket.cc.orig	2017-01-13 08:13:16.000000000 +0000
+++ pdns/dnspacket.cc
@@ -319,7 +319,7 @@ void DNSPacket::wrapup()
           pos->content=".";
         
         pw.startRecord(pos->qname, pos->qtype.getCode(), pos->ttl, pos->qclass, (DNSPacketWriter::Place)pos->d_place); 
-        shared_ptr<DNSRecordContent> drc(DNSRecordContent::mastermake(pos->qtype.getCode(), pos->qclass, pos->content));
+        boost::shared_ptr<DNSRecordContent> drc(DNSRecordContent::mastermake(pos->qtype.getCode(), pos->qclass, pos->content));
               drc->toPacket(pw);
         if(pw.size() + 20U > (d_tcp ? 65535 : getMaxReplyLen())) { // 20 = room for EDNS0
           pw.rollback();
@@ -647,7 +647,7 @@ bool checkForCorrectTSIG(const DNSPacket
     return false;
   }
 
-  uint64_t now = time(0);
+  float now = time(0);
   if(abs(trc->d_time - now) > trc->d_fudge) {
     L<<Logger::Error<<"Packet for '"<<q->qdomain<<"' denied: TSIG (key '"<<*keyname<<"') time delta "<< abs(trc->d_time - now)<<" > 'fudge' "<<trc->d_fudge<<endl;
     return false;
