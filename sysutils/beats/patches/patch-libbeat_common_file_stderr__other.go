$NetBSD$

--- libbeat/common/file/stderr_other.go.orig	2019-03-06 10:13:10.000000000 +0000
+++ libbeat/common/file/stderr_other.go
@@ -21,11 +21,11 @@ package file
 
 import (
 	"os"
-	"syscall"
+	"golang.org/x/sys/unix"
 )
 
 // RedirectStandardError causes all standard error output to be directed to the
 // given file.
 func RedirectStandardError(toFile *os.File) error {
-	return syscall.Dup2(int(toFile.Fd()), 2)
+	return unix.Dup2(int(toFile.Fd()), 2)
 }
