# $NetBSD: Makefile,v 1.17 2018/11/03 12:47:16 leot Exp $

DISTNAME=	jq-1.8.1
#PKGREVISION= 1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=jqlang/}
GITHUB_RELEASE=	${DISTNAME}

MAINTAINER=	leot@NetBSD.org
HOMEPAGE=	https://github.com/jqlang/jq/
COMMENT=	Command-line JSON processor
LICENSE=	mit

USE_LANGUAGES=	c99
USE_LIBTOOL=	yes
USE_TOOLS+=	bison flex gmake
GNU_CONFIGURE=	yes

TEST_TARGET=	check

PKGCONFIG_OVERRIDE=	libjq.pc.in

.include "options.mk"

.include "../../mk/bsd.pkg.mk"
