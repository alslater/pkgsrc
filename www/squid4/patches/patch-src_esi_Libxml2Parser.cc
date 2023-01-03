$NetBSD$

--- src/esi/Libxml2Parser.cc.orig	2020-08-22 18:37:05.000000000 +0000
+++ src/esi/Libxml2Parser.cc
@@ -91,7 +91,6 @@ ESILibxml2Parser::ESILibxml2Parser(ESIPa
 
     /* TODO: grab the document encoding from the headers */
     parser = xmlCreatePushParserCtxt(&sax, static_cast<void *>(this), NULL, 0, NULL);
-    xmlSetFeature(parser, "substitute entities", 0);
 
     if (entity_doc == NULL)
         entity_doc = htmlNewDoc(NULL, NULL);
