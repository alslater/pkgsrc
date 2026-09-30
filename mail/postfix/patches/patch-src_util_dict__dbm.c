$NetBSD$

--- src/util/dict_dbm.c.orig	2025-10-24 00:04:12.000000000 +0000
+++ src/util/dict_dbm.c
@@ -472,8 +472,7 @@ DICT   *dict_dbm_open(const char *path,
 	msg_fatal("open database %s: cannot support GDBM", path);
     if (fstat(dict_dbm->dict.stat_fd, &st) < 0)
 	msg_fatal("dict_dbm_open: fstat: %m");
-    if (open_flags == O_RDONLY)
-	dict_dbm->dict.mtime = st.st_mtime;
+    dict_dbm->dict.mtime = st.st_mtime;
     dict_dbm->dict.owner.uid = st.st_uid;
     dict_dbm->dict.owner.status = (st.st_uid != 0);
 
