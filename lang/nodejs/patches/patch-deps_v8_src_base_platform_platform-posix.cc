$NetBSD: patch-deps_v8_src_base_platform_platform-posix.cc,v 1.5 2018/05/03 21:19:16 fhajny Exp $

Use sysconf(_SC_THREAD_STACK_MIN) instead of PTHREAD_STACK_MIN.
Cast explicitly.

--- deps/v8/src/base/platform/platform-posix.cc.orig	2019-10-22 16:36:24.000000000 +0000
+++ deps/v8/src/base/platform/platform-posix.cc
@@ -68,14 +68,6 @@
 #define MAP_ANONYMOUS MAP_ANON
 #endif
 
-#if defined(V8_OS_SOLARIS)
-#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE > 2) || defined(__EXTENSIONS__)
-extern "C" int madvise(caddr_t, size_t, int);
-#else
-extern int madvise(caddr_t, size_t, int);
-#endif
-#endif
-
 #ifndef MADV_FREE
 #define MADV_FREE MADV_DONTNEED
 #endif
@@ -151,7 +143,7 @@ int ReclaimInaccessibleMemory(void* addr
   // marks the pages with the reusable bit, which allows both Activity Monitor
   // and memory-infra to correctly track the pages.
   int ret = madvise(address, size, MADV_FREE_REUSABLE);
-#elif defined(_AIX) || defined(V8_OS_SOLARIS)
+#elif defined(_AIX)
   int ret = madvise(reinterpret_cast<caddr_t>(address), size, MADV_FREE);
 #else
   int ret = madvise(address, size, MADV_FREE);
@@ -494,6 +486,8 @@ int OS::GetCurrentThreadId() {
   return static_cast<int>(syscall(__NR_gettid));
 #elif V8_OS_ANDROID
   return static_cast<int>(gettid());
+#elif V8_OS_NETBSD || V8_OS_FREEBSD
+  return static_cast<int>(reinterpret_cast<intptr_t>(pthread_self()));
 #elif V8_OS_AIX
   return static_cast<int>(thread_self());
 #elif V8_OS_FUCHSIA
@@ -691,8 +685,13 @@ Thread::Thread(const Options& options)
     : data_(new PlatformData),
       stack_size_(options.stack_size()),
       start_semaphore_(nullptr) {
+#if defined(__NetBSD__)
+  if (stack_size_ > 0 && static_cast<size_t>(stack_size_) < sysconf(_SC_THREAD_STACK_MIN)) {
+    stack_size_ = sysconf(_SC_THREAD_STACK_MIN);
+#else
   if (stack_size_ > 0 && static_cast<size_t>(stack_size_) < PTHREAD_STACK_MIN) {
     stack_size_ = PTHREAD_STACK_MIN;
+#endif
   }
   set_name(options.name());
 }
@@ -708,7 +707,7 @@ static void SetThreadName(const char* na
   pthread_set_name_np(pthread_self(), name);
 #elif V8_OS_NETBSD
   STATIC_ASSERT(Thread::kMaxThreadNameLength <= PTHREAD_MAX_NAMELEN_NP);
-  pthread_setname_np(pthread_self(), "%s", name);
+  pthread_setname_np(pthread_self(), "%s", (void *)name);
 #elif V8_OS_MACOSX
   // pthread_setname_np is only available in 10.6 or later, so test
   // for it at runtime.
