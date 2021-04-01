$NetBSD$

Revert dovecot commit 3a2098a987b81fe89b74a9a628e9ef164f053633
to restore replication of deleted emails

--- src/plugins/replication/replication-plugin.c.orig	2020-12-22 13:26:52.000000000 +0000
+++ src/plugins/replication/replication-plugin.c
@@ -255,8 +255,9 @@ replication_want_sync_changes(const stru
 {
 	/* Replication needs to be triggered on all the user-visible changes,
 	   but not e.g. due to writes to cache file. */
-	return (changes->changes_mask &
-		ENUM_NEGATE(MAIL_INDEX_TRANSACTION_CHANGE_OTHERS)) != 0;
+/*	return (changes->changes_mask &
+		ENUM_NEGATE(MAIL_INDEX_TRANSACTION_CHANGE_OTHERS)) != 0; */
+	return changes->changes_mask;
 }
 
 static void
