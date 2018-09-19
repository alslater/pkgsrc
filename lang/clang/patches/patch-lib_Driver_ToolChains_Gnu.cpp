$NetBSD$

--- lib/Driver/ToolChains/Gnu.cpp.orig	2017-08-11 01:47:32.000000000 +0000
+++ lib/Driver/ToolChains/Gnu.cpp
@@ -26,6 +26,7 @@
 #include "llvm/Support/Path.h"
 #include "llvm/Support/TargetParser.h"
 #include <system_error>
+#include "llvm/Support/raw_ostream.h"
 
 using namespace clang::driver;
 using namespace clang::driver::toolchains;
@@ -1827,7 +1828,7 @@ bool Generic_GCC::GCCInstallationDetecto
       "x86_64-redhat-linux",    "x86_64-suse-linux",
       "x86_64-manbo-linux-gnu", "x86_64-linux-gnu",
       "x86_64-slackware-linux", "x86_64-linux-android",
-      "x86_64-unknown-linux"};
+      "x86_64-unknown-linux", "x86_64-sun-solaris2.11"};
   static const char *const X32LibDirs[] = {"/libx32"};
   static const char *const X86LibDirs[] = {"/lib32", "/lib"};
   static const char *const X86Triples[] = {
@@ -1890,7 +1891,8 @@ bool Generic_GCC::GCCInstallationDetecto
   // Solaris.
   static const char *const SolarisSPARCLibDirs[] = {"/gcc"};
   static const char *const SolarisSPARCTriples[] = {"sparc-sun-solaris2.11",
-                                                    "i386-pc-solaris2.11"};
+                                                    "i386-pc-solaris2.11",
+                                                    "x86_64-sun-solaris2.11"};
 
   using std::begin;
   using std::end;
@@ -2064,7 +2066,7 @@ void Generic_GCC::GCCInstallationDetecto
        !EC && LI != LE; LI = LI.increment(EC)) {
     StringRef VersionText = llvm::sys::path::filename(LI->getName());
     GCCVersion CandidateVersion = GCCVersion::Parse(VersionText);
-
+    llvm::errs() << VersionText << ":" << CandidateVersion.Major << "\n";
     if (CandidateVersion.Major != -1) // Filter obviously bad entries.
       if (!CandidateGCCInstallPaths.insert(LI->getName()).second)
         continue; // Saw this path before; no need to look at it again.
@@ -2133,11 +2135,11 @@ void Generic_GCC::GCCInstallationDetecto
     const llvm::Triple &TargetTriple, const ArgList &Args,
     const std::string &LibDir, StringRef CandidateTriple,
     bool NeedsBiarchSuffix) {
-  if (TargetTriple.getOS() == llvm::Triple::Solaris) {
-    scanLibDirForGCCTripleSolaris(TargetTriple, Args, LibDir, CandidateTriple,
-                                  NeedsBiarchSuffix);
-    return;
-  }
+//  if (TargetTriple.getOS() == llvm::Triple::Solaris) {
+//    scanLibDirForGCCTripleSolaris(TargetTriple, Args, LibDir, CandidateTriple,
+//                                  NeedsBiarchSuffix);
+//    return;
+//  }
 
   llvm::Triple::ArchType TargetArch = TargetTriple.getArch();
   // Locations relative to the system lib directory where GCC's triple-specific
