# $NetBSD$

DISTNAME=	squid-4.9
PKGREVISION=	1
CATEGORIES=	www
MASTER_SITES=	http://www.squid-cache.org/Versions/v4/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	al.slater@essiell.com
HOMEPAGE=	http://www.squid-cache.org/
COMMENT=	Post-Harvest_cached WWW proxy cache and accelerator
LICENSE=	gnu-gpl-v2

GNU_CONFIGURE=	yes
USE_LANGUAGES=	c c++

USE_LANGUAGES=		c c++
USE_TOOLS+=		perl:run gmake
CONFIGURE_ARGS+=	--sysconfdir=${PKG_SYSCONFDIR}
CONFIGURE_ARGS+=	--localstatedir=${SQUID_DATADIR}
CONFIGURE_ARGS+=	--datarootdir=${PREFIX}/share/squid
CONFIGURE_ARGS+=	--disable-arch-native
CONFIGURE_ARGS+=	--disable-strict-error-checking
CONFIGURE_ARGS+=	--enable-auth
CONFIGURE_ARGS+=	--enable-cachemgr-hostname=localhost
CONFIGURE_ARGS+=	--enable-delay-pools
CONFIGURE_ARGS+=	--enable-icap-client
CONFIGURE_ARGS+=	--enable-icmp
CONFIGURE_ARGS+=	--enable-poll
CONFIGURE_ARGS+=	--enable-removal-policies=lru,heap
CONFIGURE_ARGS+=	--enable-storeio=${SQUID_BACKENDS:Q}
CONFIGURE_ARGS+=	--with-aio
CONFIGURE_ARGS+=	--with-default-user=${SQUID_USER}
CONFIGURE_ARGS+=	--with-pidfile=${VARBASE}/run/squid.pid
CONFIGURE_ARGS+=	--with-openssl=${SSLBASE:Q}
CONFIGURE_ARGS+=	--enable-ssl-crtd

# Let 'purge' find correct config file by default.
CPPFLAGS+=		-DDEFAULT_SQUID_CONF=\"${PKG_SYSCONFDIR}/squid.conf\"

BUILD_DEFS+=		VARBASE
MAKE_ENV+=		INSTALL_SCRIPT=${INSTALL_SCRIPT:Q}
MAKE_ENV+=		PKG_PREFIX=${PREFIX} VARBASE=${VARBASE}
REPLACE_PERL+=		tools/helper-mux/helper-mux

EGFILES=		src/mime.conf.default src/squid.conf.default \
			errors/errorpage.css tools/cachemgr.conf
EGDIR=			share/examples/squid
.for f in cachemgr.conf errorpage.css mime.conf squid.conf
CONF_FILES+=		${PREFIX}/${EGDIR}/${f} ${PKG_SYSCONFDIR}/${f}
.endfor
OWN_DIRS=		${SQUID_DATADIR}
OWN_DIRS_PERMS+=	${SQUID_DATADIR}/cache ${SQUID_USER} ${SQUID_GROUP} 0750 \
			${SQUID_DATADIR}/logs ${SQUID_USER} ${SQUID_GROUP} 0750

.include "Makefile.common"
.include "options.mk"

# Incorrect check for <netinet/ip_icmp.h> on FreeBSD:
CONFIGURE_ENV.FreeBSD+=	ac_cv_header_netinet_ip_icmp_h=yes

INSTALLATION_DIRS=	${EGDIR}

SPECIAL_PERMS+=		libexec/pinger ${SETUID_ROOT_PERMS}

RCD_SCRIPTS=		squid
RCD_SCRIPT_SRC.squid=	files/squid.sh

SUBST_CLASSES+=		confs
SUBST_STAGE.confs=	pre-configure
SUBST_FILES.confs=	src/cf.data.pre
SUBST_SED.confs=	-e "s/@USER@/${SQUID_USER}/"
SUBST_MESSAGE.confs=	Fixing configuration files.

post-build:
	cd ${WRKSRC}/src && ${CP} -pf squid.conf.documented squid.conf.default

post-install:
.for f in ${EGFILES}
	${INSTALL_DATA}	${WRKSRC}/${f} \
		${DESTDIR}${PREFIX}/${EGDIR}/`basename ${f} .default`
.endfor

.include "../../devel/libltdl/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

