# $NetBSD: Makefile,v 1.6 2015/03/06 21:03:20 ryoon Exp $

FISHVER=		2.1.2
DISTNAME=		fish-${FISHVER}
CATEGORIES=		shells
MASTER_SITES=		http://fishshell.com/files/${FISHVER}/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://www.fishshell.com/
COMMENT=		User friendly command line shell for UNIX-like operating systems
LICENSE=		gnu-gpl-v2

USE_LANGUAGES+=		c++
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--sysconfdir=${PKG_SYSCONFDIR}
CONFIGURE_ARGS+=	--without-xsel
USE_TOOLS+=		gmake

EGDIR=			${PREFIX}/share/examples/fish
INSTALL_ENV+=		EGDIR=${EGDIR}

PKG_SHELL=		bin/fish

REPLACE_PYTHON+=	share/tools/*.py
REPLACE_PYTHON+=	share/tools/web_config/webconfig.py

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "NetBSD" && exists(/usr/include/execinfo.h)
CPPFLAGS+=		-DHAVE_BACKTRACE
CPPFLAGS+=		-DHAVE_BACKTRACE_SYMBOLS
CXXFLAGS.NetBSD+=	-fpermissive
LDFLAGS+=		-lexecinfo
.endif

.include "../../lang/python/application.mk"
.include "../../mk/curses.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
