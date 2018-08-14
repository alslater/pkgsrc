$NetBSD$

--- Makefile.PL.orig	2014-04-24 14:50:29.000000000 +0000
+++ Makefile.PL
@@ -8,7 +8,8 @@ use Getopt::Long qw( GetOptionsFromArray
 use Path::Class;
 use Try::Tiny;
 
-use inc::IO::Interactive::Tiny;
+use lib 'inc';
+use IO::Interactive::Tiny;
 
 caller
     or run(\@ARGV, [qw{ssl crypto ssl32 ssleay32 eay32 libeay32 z}]);
