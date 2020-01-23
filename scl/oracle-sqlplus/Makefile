# instantclient-basic-solaris.x64-11.2.0.4.0.zip
DISTNAME=	instantclient-sqlplus-${DIST_OS}.${DIST_ARCH}-11.${UPDATE_NUMBER}
PKGNAME=	oracle-instantclient-sqlplus-11.${UPDATE_NUMBER}
MASTER_SITES=	# empty

LICENSE=	oracle-binary-code-license

DOWNLOAD_NAME=	Oracle 11 Instant Client SDK

CATEGORIES=	database
COMMENT=	${DOWNLOAD_NAME}

MAINTAINER=	al.slater@scluk.com
HOMEPAGE=	
DOWNLOAD=	
ARCHIVE=	

.include "../../scl/oracle-client/Makefile.common"

# Simplify distinfo generation
.if make(distinfo)
DISTFILES+=	instantclient-sqlplus-${DIST_OS}.${DIST_ARCH}-11.${UPDATE_NUMBER}.zip
FETCH_MESSAGE=	"You must fetch the following files to generate distinfo:"
FETCH_MESSAGE+=	""
.for file in ${DISTFILES}
FETCH_MESSAGE+=	"	${file}"
.endfor
FETCH_MESSAGE+=	""
FETCH_MESSAGE+=	"from:"
FETCH_MESSAGE+=	"	${DOWNLOAD}"
FETCH_MESSAGE+=	"	or ${ARCHIVE}"
.endif


WRKSRC=		${WRKDIR}/instantclient_11_2/

SFILES_MK=sfiles-${DIST_OS}-${EMUL_ARCH}.mk

.sinclude "${SFILES_MK}"

CHECK_SSP_SKIP+= oracle/11/libsqlplus.so
CHECK_SSP_SKIP+= oracle/11/libsqlplusic.so

.include "../../scl/oracle-client/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
