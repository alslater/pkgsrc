# $NetBSD: Makefile,v 1.2 2012/10/23 17:18:44 asau Exp $
#

VERSION=        2.6.2 
DISTNAME=       omniEvents-2_6_2-src
PKGNAME=        omniEvents-${VERSION}
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=omnievents/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://omnievents.sourceforge.net/
COMMENT=	CORBA Events Service
LICENSE=	gnu-gpl-v2

WRKSRC=		${WRKDIR}/omniEvents-2_6_2
GNU_CONFIGURE=	yes
USE_LANGUAGES=	c c++
USE_TOOLS+=	gmake
MAKE_FILE=	Makefile

MAKE_JOBS_SAFE= no

.include "../../net/omniORB/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
