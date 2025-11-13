$NetBSD$

--- python3/omniidl_be/dir.mk.orig	2014-07-23 09:19:07.000000000 +0000
+++ python3/omniidl_be/dir.mk
@@ -6,7 +6,10 @@ ifeq ($(PYTHON),)
 PYTHON = python
 endif
 
-FILES = __init__.py python.py
+FILES = python.py
+ifdef INSTALL_OMNIIDL_BE_INIT
+FILES += __init__.py
+endif
 
 export:: $(FILES)
 	@(dir="$(PYLIBDIR)"; \
