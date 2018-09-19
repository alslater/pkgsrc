$NetBSD$

--- lib/Driver/ToolChains/Solaris.cpp.orig	2017-07-14 17:49:52.000000000 +0000
+++ lib/Driver/ToolChains/Solaris.cpp
@@ -105,7 +105,6 @@ void solaris::Linker::ConstructJob(Compi
     CmdArgs.push_back("-lgcc_s");
     CmdArgs.push_back("-lc");
     if (!Args.hasArg(options::OPT_shared)) {
-      CmdArgs.push_back("-lgcc");
       CmdArgs.push_back("-lm");
     }
   }
@@ -140,6 +139,8 @@ Solaris::Solaris(const Driver &D, const
 
   addPathIfExists(D, getDriver().SysRoot + getDriver().Dir + "/../lib", Paths);
 
+  getFilePaths().push_back("/opt/scl64/gcc49/lib/gcc/x86_64-sun-solaris2.11/4.9.4");
+
   std::string LibPath = "/usr/lib/";
   switch (Triple.getArch()) {
   case llvm::Triple::x86:
@@ -177,17 +178,9 @@ void Solaris::AddClangCXXStdlibIncludeAr
   // rather than libstdc++ if it's requested.
   addSystemInclude(DriverArgs, CC1Args, "/usr/include/c++/v1/support/solaris");
 
-  if (GCCInstallation.isValid()) {
-    GCCVersion Version = GCCInstallation.getVersion();
-    addSystemInclude(DriverArgs, CC1Args,
-                     getDriver().SysRoot + "/usr/gcc/" +
-                     Version.MajorStr + "." +
-                     Version.MinorStr +
-                     "/include/c++/" + Version.Text);
-    addSystemInclude(DriverArgs, CC1Args,
-                     getDriver().SysRoot + "/usr/gcc/" + Version.MajorStr +
-                     "." + Version.MinorStr + "/include/c++/" +
-                     Version.Text + "/" +
-                     GCCInstallation.getTriple().str());
-  }
+  GCCVersion Version = GCCInstallation.getVersion();
+  addSystemInclude(DriverArgs, CC1Args,
+                   getDriver().SysRoot + "/opt/scl64/gcc49/include/c++");
+  addSystemInclude(DriverArgs, CC1Args,
+                   getDriver().SysRoot + "/opt/scl64/gcc49/include/c++/x86_64-sun-solaris2.11");
 }
