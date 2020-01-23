$NetBSD: patch-Source_JavaScriptCore_heap_MachineStackMarker.cpp,v 1.3 2019/12/13 09:48:02 mrg Exp $

Support NetBSD on x86, arm, arm64 and mips.

--- Source/JavaScriptCore/heap/MachineStackMarker.cpp.orig	2019-06-26 16:25:02.000000000 +0000
+++ Source/JavaScriptCore/heap/MachineStackMarker.cpp
@@ -20,6 +20,9 @@
  */
 
 #include "config.h"
+#if OS(SOLARIS)
+#undef _FILE_OFFSET_BITS
+#endif
 #include "MachineStackMarker.h"
 
 #include "ConservativeRoots.h"
@@ -53,7 +56,11 @@
 #include <unistd.h>
 
 #if OS(SOLARIS)
-#include <thread.h>
+#include <sys/types.h>
+#include <sys/stat.h>
+#include <fcntl.h>
+#include <procfs.h>
+#include <pthread.h>
 #else
 #include <pthread.h>
 #endif
@@ -483,7 +490,7 @@ size_t MachineThreads::Thread::getRegist
     return sizeof(CONTEXT);
 #elif USE(PTHREADS)
     pthread_attr_init(&regs.attribute);
-#if HAVE(PTHREAD_NP_H) || OS(NETBSD)
+#if HAVE(PTHREAD_NP_H) || OS(NETBSD) || OS(SOLARIS)
 #if !OS(OPENBSD)
     // e.g. on FreeBSD 5.4, neundorf@kde.org
     pthread_attr_get_np(platformThread, &regs.attribute);
@@ -578,6 +585,7 @@ void* MachineThreads::Thread::Registers:
     return reinterpret_cast<void*>((uintptr_t) regs.machineContext.sp);
 #elif CPU(MIPS)
     return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[29]);
+
 #else
 #error Unknown Architecture
 #endif
@@ -665,6 +673,39 @@ void* MachineThreads::Thread::Registers:
 #error Unknown Architecture
 #endif
 
+#elif OS(NETBSD)
+
+#if CPU(X86)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_EBP]);
+#elif CPU(X86_64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_RBP]);
+#elif CPU(ARM)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_FP]);
+#elif CPU(ARM64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_X29]);
+#elif CPU(MIPS)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_S8]);
+#else
+#error Unknown Architecture
+#endif
+
+#elif OS(SOLARIS)
+
+// The following sequence depends on glibc's sys/ucontext.h.
+#if CPU(X86)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[REG_EBP]);
+#elif CPU(X86_64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[REG_RBP]);
+#elif CPU(ARM)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.arm_fp);
+#elif CPU(ARM64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.regs[29]);
+#elif CPU(MIPS)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[30]);
+#else
+#error Unknown Architecture
+#endif
+
 #elif defined(__GLIBC__)
 
 // The following sequence depends on glibc's sys/ucontext.h.
@@ -747,6 +788,39 @@ void* MachineThreads::Thread::Registers:
 #error Unknown Architecture
 #endif
 
+#elif OS(NETBSD)
+
+#if CPU(X86)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_EIP]);
+#elif CPU(X86_64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_RIP]);
+#elif CPU(ARM)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_PC]);
+#elif CPU(ARM64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_ELR]);
+#elif CPU(MIPS)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_EPC]);
+#else
+#error Unknown Architecture
+#endif
+
+#elif OS(SOLARIS)
+
+// The following sequence depends on glibc's sys/ucontext.h.
+#if CPU(X86)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[REG_EIP]);
+#elif CPU(X86_64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[REG_RIP]);
+#elif CPU(ARM)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.arm_pc);
+#elif CPU(ARM64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.pc);
+#elif CPU(MIPS)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.pc);
+#else
+#error Unknown Architecture
+#endif
+
 #elif defined(__GLIBC__)
 
 // The following sequence depends on glibc's sys/ucontext.h.
@@ -837,6 +911,39 @@ void* MachineThreads::Thread::Registers:
 #else
 #error Unknown Architecture
 #endif
+
+#elif OS(NETBSD)
+
+#if CPU(X86)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_ESI]);
+#elif CPU(X86_64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_R8]);
+#elif CPU(ARM)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_R8]);
+#elif CPU(ARM64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_R4]);
+#elif CPU(MIPS)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.__gregs[_REG_T4]);
+#else
+#error Unknown Architecture
+#endif
+
+#elif OS(SOLARIS)
+
+// The following sequence depends on glibc's sys/ucontext.h.
+#if CPU(X86)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[REG_ESI]);
+#elif CPU(X86_64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[REG_R8]);
+#elif CPU(ARM)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.arm_r8);
+#elif CPU(ARM64)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.regs[4]);
+#elif CPU(MIPS)
+    return reinterpret_cast<void*>((uintptr_t) regs.machineContext.gregs[12]);
+#else
+#error Unknown Architecture
+#endif
 
 #elif defined(__GLIBC__)
 
