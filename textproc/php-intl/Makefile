# $NetBSD: Makefile,v 1.28 2017/04/30 22:49:54 maya Exp $

MODNAME=		intl
CATEGORIES+=		textproc
COMMENT=		PHP extension for i18n
PKGREVISION=		2
LICENSE=		php

CXXFLAGS+=		-std=c++11
USE_LANGUAGES=		c c++
CONFIGURE_ARGS+=	--enable-${MODNAME}=shared,${BUILDLINK_DIR}

CFLAGS+=		-DU_USING_ICU_NAMESPACE=1

.include "../../lang/php/ext.mk"
.include "../../textproc/icu/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
