# $NetBSD: version.mk,v 1.25 2017/04/30 23:02:09 maya Exp $

.include "../../mk/bsd.prefs.mk"

GO_VERSION=	1.8.1
GO14_VERSION=	1.4.3

ONLY_FOR_PLATFORM=	*-*-i386 *-*-x86_64 *-*-*arm*
NOT_FOR_PLATFORM=	SunOS-*-i386
.if ${MACHINE_ARCH} == "i386"
GOARCH=		386
GOCHAR=		8
.elif ${MACHINE_ARCH} == "x86_64"
GOARCH=		amd64
GOCHAR=		6
.elif !empty(MACHINE_ARCH:M*arm*)
GOARCH=		arm
GOCHAR=		5
.endif
PLIST_SUBST+=	GO_PLATFORM=${LOWER_OPSYS:Q}_${GOARCH:Q} GOARCH=${GOARCH:Q}
PLIST_SUBST+=	GOCHAR=${GOCHAR:Q}

# Disable stack protection for go and all go based packages.
# Stack protection causes binaries to link libssp dynamically,
# whereas go normally links everything statically, resulting in
# random runtime linking against unsanctioned GCC libs.
_PKGSRC_USE_SSP=	no
