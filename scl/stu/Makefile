# $NetBSD: Makefile,v 1.218 2016/06/21 12:23:01 joerg Exp $

# Notes to package maintainers:
#
# Updating this package does not automatically necessitate bumping
# PKGTOOLS_REQD in bsd.pkg.mk. Do so if and only if there is a critical
# change in the pkg_* tools that pkgsrc relies on for proper operation.

PKGNAME=		stu-1.0
PKGREVISION=	1
CATEGORIES=		pkgtools

MAINTAINER=		al.slater@scluk.com
HOMEPAGE=		http://www.scluk.com
COMMENT=		Amex STU library
LICENSE=		modified-bsd

SKIP_LICENSE_CHECK=	yes

GNU_CONFIGURE=		yes
USE_TOOLS= gmake

USE_LANGUAGES+= c++
USE_LANGUAGES+= c

.include "../../mk/bsd.prefs.mk"

MAKE_ENV+=		PKGSRC_MACHINE_ARCH=${MACHINE_ARCH}
MAKE_ENV+=		OPSYS=${OPSYS}
MAKE_ENV+=		MANINSTALL=${MANINSTALL:Q}

CONFIG_GUESS_OVERRIDE+= ${WRKSRC}/config.guess
CONFIG_SUB_OVERRIDE+= ${WRKSRC}/config.sub


#CONFIGURE_ENV+=	LIBS=${LIBS:Q}

do-extract:
	@${CP} -R ${FILESDIR} ${WRKSRC}

pre-configure:
	cd ${WRKSRC} && ${CONFIG_SHELL} ${CONFIG_SHELL_FLAGS} ./configure &&		\
	${SETENV} ${MAKE_ENV} ${BSD_MAKE_ENV} ${MAKE_PROGRAM}		\
		${MAKE_FLAGS} ${BUILD_MAKE_FLAGS} -f ${MAKE_FILE} all

.include "../../mk/bsd.pkg.mk"
