# $NetBSD: Makefile,v 1.29 2015/04/25 14:23:33 tnn Exp $

DISTNAME=	kalzium-${_KDE_VERSION}
PKGREVISION=	2
CATEGORIES=	misc
COMMENT=	Periodic table of elements

.include "../../meta-pkgs/kde4/Makefile.kde4"

.include "../../meta-pkgs/kde4/kde4.mk"

.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
#BUILDLINK_API_DEPENDS.eigen2+=  eigen2>=2.0.3
.include "../../math/eigen3/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../x11/kdelibs4/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
