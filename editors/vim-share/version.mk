# $NetBSD: version.mk,v 1.99 2016/11/16 10:38:35 wiz Exp $

VIM_VERSION=		8.1
VIM_PATCHLEVEL=		1523
VIM_SUBDIR=		vim81

PRINT_PLIST_AWK+=   { gsub(/${VIM_SUBDIR}/, "$${VIM_SUBDIR}"); print; next; }
