# $NetBSD: Makefile,v 1.54 2016/11/28 12:50:19 wiz Exp $

DISTNAME=	libgpg-error-1.36
CATEGORIES=	security
MASTER_SITES=	ftp://ftp.gnupg.org/gcrypt/libgpg-error/ \
		ftp://ftp.ring.gr.jp/pub/net/gnupg/libgpg-error/ 
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	minskim@NetBSD.org
HOMEPAGE=	http://www.gnupg.org/
COMMENT=	Definitions of common error values for all GnuPG components
LICENSE=	gnu-gpl-v2 AND gnu-lgpl-v2.1

USE_LIBTOOL=		yes
USE_MULTIARCH=		bin lib
USE_TOOLS+=		gmake
USE_PKGLOCALEDIR=	yes
GNU_CONFIGURE=		yes
MAKE_ENV+=		LC_ALL="C"
INFO_FILES=		yes
TEST_TARGET=		check

.include "../../mk/bsd.prefs.mk"

.if !empty(USE_CROSS_COMPILE:M[yY][eE][sS])
CONFIGURE_ENV+=		CC_FOR_BUILD=${NATIVE_CC:Q}
.else
CONFIGURE_ENV+=		CC_FOR_BUILD=${CC:Q}\ ${CFLAGS:M*:Q}
.endif

# XXX See HACKS
.if ${OPSYS} == "IRIX" || !empty(MACHINE_PLATFORM:MNetBSD-[3-9]*)
USE_TOOLS+=            awk
.else
USE_TOOLS+=            gawk
.endif


.if !empty(MACHINE_PLATFORM:MSunOS-5.10-*)
LIBS+=	-lrt
.endif


.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
