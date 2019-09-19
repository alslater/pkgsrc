# $NetBSD$

DISTNAME=	auditmonitor-0.6
#PKGREVICSION=	1
CATEGORIES=	scl python
MASTER_SITES=	${MASTER_SITE_GITHUB:=alslater/}
GITHUB_TAG= 	v${PKGVERSION_NOREV}
DIST_SUBDIR=	auditmonitor

MAINTAINER=	al.slater@scluk.com
HOMEPAGE=	https://github.com/alslater/auditmonitor/
COMMENT=	BSM Audit Monitor	
#LICENSE=	# TODO: (see mk/license.mk)

PYTHON_VERSIONS_INCOMPATIBLE= 27 34 35

SMF_NAME=	auditmonitor

post-install:
	${MV} ${DESTDIR}${PREFIX}/bin/auditmon \
	${DESTDIR}${PREFIX}/bin/auditmon${PYVERSSUFFIX} || ${TRUE}

DEPENDS+=   ${PYPKGPREFIX}-watchdog>=0.9.0:../../sysutils/py-watchdog

.include "../../lang/python/application.mk"
.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
