# $NetBSD: Makefile,v 1.4 2017/08/18 10:14:21 taca Exp $
#

MODNAME=	redis3
PKGMODNAME=	redis
PECL_VERSION=	5.3.3
PECL_LEGACY_VERSION_SCHEME=	yes
PECL_DISTNAME=	${PECL_VERSION}
CATEGORIES=	databases
MASTER_SITES=	${MASTER_SITE_GITHUB:=phpredis/}
GITHUB_PROJECT=	phpredis
EXTRACT_SUFX=	.tar.gz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/phpredis/phpredis
COMMENT=	PHP extension for Redis
LICENSE=	php

PHP_VERSIONS_INCOMPATIBLE=	56

WRKSRC=		${WRKDIR}/${GITHUB_PROJECT}-${PECL_VERSION}

.include "../../mk/compiler.mk"
.if !empty(PKGSRC_COMPILER:Mclang)
CFLAGS+=	-Wno-error=return-type
.endif

.include "../../lang/php/ext.mk"
.if ${PKG_PHP_MAJOR_VERS} < 8
.include "../../textproc/php-json/buildlink3.mk"
.endif
.include "../../mk/bsd.pkg.mk"
