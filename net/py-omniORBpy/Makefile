# $NetBSD: Makefile,v 1.17 2019/11/03 11:45:51 rillig Exp $

DISTNAME=	omniORBpy-4.2.4
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
PKGREVISION=	1
CATEGORIES=	devel python
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=omniorb/}
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	tonnerre@NetBSD.org
HOMEPAGE=	http://omniorb.sourceforge.net/
COMMENT=	Python interface to omniORB

PLIST_SUBST+=	PYINC=${PYINC} PYSITELIB=${PYSITELIB}
GNU_CONFIGURE=	yes
USE_TOOLS+=	gmake
USE_LANGUAGES+=	c c++
MAKE_FILE=	GNUmakefile

PYTHON_SELF_CONFLICT=		yes
PYTHON_VERSIONS_INCOMPATIBLE=      27

post-install:
	${FIND} ${DESTDIR}${PREFIX}/${PYSITELIB} -name "__pycache__" | xargs rm -rf

.include "../../lang/python/application.mk"
.include "../../net/omniORB/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
