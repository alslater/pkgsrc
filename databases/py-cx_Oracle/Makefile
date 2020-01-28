# $NetBSD: Makefile,v 1.3 2013/04/06 12:08:38 rodent Exp $
#

DISTVER=	7.0
DISTNAME=	cx_Oracle-${DISTVER}
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=	www python
GITHUB_PROJECT= python-cx_Oracle
MASTER_SITES=   ${MASTER_SITE_GITHUB:=oracle/}
MAINTAINER=	joerg@NetBSD.org
HOMEPAGE=	https://oracle.github.io/python-cx_Oracle/	
COMMENT=	Oracle binding for Python

PYDISTUTILSPKG=	yes

WRKSRC=		${WRKDIR}/python-${DISTNAME}

.include "../../mk/bsd.prefs.mk"
.include "../../scl/oracle-client/buildlink3.mk"
.include "../../scl/oracle-sdk/buildlink3.mk"

.if !defined(ORACLE_HOME)
PKG_FAIL_REASON+=	"You must set ORACLE_HOME to the location of your Oracle installation"
#.elif !exists(${ORACLE_HOME})
#PKG_FAIL_REASON+=	"The location of ORACLE_HOME does not exist"
.endif

BUILDLINK_PASSTHRU_DIRS+=	${ORACLE_HOME}
BUILDLINK_PASSTHRU_RPATHDIRS+=	${ORACLE_HOME}
LDFLAGS+=	-Wl,-rpath,${ORACLE_HOME}/lib

ALL_ENV+=	ORACLE_HOME=${ORACLE_HOME:Q}

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
