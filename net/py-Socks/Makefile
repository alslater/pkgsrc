# $NetBSD: Makefile,v 1.1 2016/01/02 10:10:10 wiz Exp $

DISTNAME=	PySocks-1.6.8
PKGNAME=	${PYPKGPREFIX}-${DISTNAME:S/Py//}
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_PYPI:=P/PySocks/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/Anorov/PySocks
COMMENT=	Python Socks module
LICENSE=	modified-bsd

CONFLICTS=  ${PYPKGPREFIX}-SocksiPy-branch-[0-9]*

USE_LANGUAGES=	# none

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
