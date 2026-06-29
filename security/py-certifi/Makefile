# $NetBSD: Makefile,v 1.27 2022/01/04 20:54:39 wiz Exp $

DISTNAME=	certifi-2026.5.20
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
PKGREVISION=	1
CATEGORIES=	security python
MASTER_SITES=	${MASTER_SITE_PYPI:=c/certifi/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://certifi.io/
COMMENT=	Python package for providing Mozilla's CA Bundle
LICENSE=	mpl-2.0

BUILD_DEPENDS+= ${PYPKGPREFIX}-setuptools_scm-[0-9]*:../../devel/py-setuptools_scm

USE_LANGUAGES=	# none

.include "../../lang/python/wheel.mk"
.include "../../mk/bsd.pkg.mk"
