# $NetBSD: Makefile,v 1.40 2015/04/25 14:24:46 tnn Exp $
#

DISTNAME=	imposter-0.3
PKGREVISION=	24
CATEGORIES=	print
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=imposter/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://imposter.sourceforge.net/
COMMENT=	Standalone OpenOffice presentations viewer using GTK2

GNU_CONFIGURE=		yes
USE_TOOLS+=		gmake msgfmt pkg-config
USE_PKGLOCALEDIR=	yes

LDFLAGS.DragonFly=	-lm
LDFLAGS.SunOS+=		-lm

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
