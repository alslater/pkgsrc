# $NetBSD: Makefile,v 1.3 2014/04/19 01:15:20 asau Exp $

DISTNAME=	mingw-runtime-3.14
PKGNAME=	mingw-runtime-bin-3.14
CATEGORIES=	cross
MASTER_SITES=	${MASTER_SITE_MINGW}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://mingw.sourceforge.net/
COMMENT=	GCC runtime libraries for win32 cross-development

NO_BUILD=	yes
NO_CONFIGURE=	yes
USE_CROSSBASE=	yes
USE_TOOLS+=	pax
WRKSRC=		${WRKDIR}

INSTALLATION_DIRS+=	${MINGW_TARGET}

do-install:
	cd ${WRKSRC} && pax -rw -pp bin include lib \
		${DESTDIR}${PREFIX}/${MINGW_TARGET}

.include "../../cross/mingw/Makefile.common"
.include "../../mk/bsd.pkg.mk"
