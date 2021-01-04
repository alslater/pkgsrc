$NetBSD$

--- Source/WebCore/xml/XPathGrammar.y.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/WebCore/xml/XPathGrammar.y
@@ -50,6 +50,7 @@ using namespace XPath;
 %pure-parser
 %lex-param { parser }
 %parse-param { Parser& parser }
+%define api.header.include { "XPathGrammar.h" }
 
 %union { 
     NumericOp::Opcode numericOpcode; 
