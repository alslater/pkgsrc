# $NetBSD$

VERSION=	0.7
DISTNAME=	auditmonitor-${VERSION}
PKGREVISION=	1
PKGNAME=    auditmonitor-${VERSION}
CATEGORIES=	scl python
MASTER_SITES=	${MASTER_SITE_GITHUB:=alslater/}
GITHUB_TAG= 	v${PKGVERSION_NOREV}
DIST_SUBDIR=	auditmonitor

MAINTAINER=	al.slater@scluk.com
HOMEPAGE=	https://github.com/alslater/auditmonitor/
COMMENT=	BSM Audit Monitor	
#LICENSE=	# TODO: (see mk/license.mk)

WRKSRC=     ${WRKDIR}/auditmonitor-${VERSION}

PYTHON_VERSIONS_ACCEPTED= 38

SMF_NAME=	auditmonitor

post-install:
	${MV} ${DESTDIR}${PREFIX}/bin/auditmon \
	${DESTDIR}${PREFIX}/bin/auditmon${PYVERSSUFFIX} || ${TRUE}

DEPENDS+=   ${PYPKGPREFIX}-watchdog>=0.9.0:../../sysutils/py-watchdog

.include "../../lang/python/application.mk"
.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
