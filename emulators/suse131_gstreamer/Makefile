# $NetBSD: Makefile,v 1.5 2015/03/02 19:25:58 tnn Exp $

PKGNAME=	suse_gstreamer-${SUSE_VERSION}
PKGREVISION=	2
CATEGORIES=	emulators
RPMPKGS+=	libgstreamer-0_10-0-0.10.36-10.1.3.${SUSE_ARCH}
RPMPKGS+=	gstreamer-0_10-plugins-bad-0.10.23-13.1.4.${SUSE_ARCH}
RPMPKGS+=	gstreamer-0_10-plugins-base-0.10.36-9.1.4.${SUSE_ARCH}
RPMPKGS+=	gstreamer-0_10-plugins-good-0.10.31-10.1.4.${SUSE_ARCH}
RPMPKGS+=	libgstinterfaces-0_10-0-0.10.36-9.1.4.${SUSE_ARCH}
RPMPKGS+=	libgstreamer-1_0-0-1.0.10-2.1.4.${SUSE_ARCH}
RPMUPDPKGS+=	gstreamer-plugin-gstclutter-2.0.8-3.1.${SUSE_ARCH}
RPMUPDPKGS+=	gstreamer-plugins-bad-1.0.10-2.5.4.${SUSE_ARCH}
RPMUPDPKGS+=	gstreamer-plugins-base-1.0.10-2.4.1.${SUSE_ARCH}
RPMPKGS+=	gstreamer-plugins-good-1.0.10-2.1.4.${SUSE_ARCH}
RPMPKGS+=	liborc-0_4-0-0.4.17-2.1.2.${SUSE_ARCH}

MAINTAINER=	rodent@NetBSD.org
COMMENT=	Linux compatibility package for gstreamer

EMUL_MODULES.linux=	base

PLIST_SRC=	${RPM2PKG_PLIST}

.include "../../emulators/suse131_linux/Makefile.common"
.include "../../mk/bsd.pkg.mk"
