# $NetBSD: Makefile,v 1.6 2016/12/04 16:30:00 bsiegert Exp $

DISTNAME=	go-crypto-0.0.20180308
#PKGREVISION= 1
CATEGORIES=	security
MASTER_SITES=	${MASTER_SITE_GITHUB:=golang/}
GITHUB_PROJECT=	crypto
GITHUB_TAG=	c7dcf104e3

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/golang/crypto/
COMMENT=	Go supplementary cryptography libraries
LICENSE=	modified-bsd

GO_SRCPATH= golang.org/x/crypto
GO_DIST_BASE=   ${GITHUB_PROJECT}-${GITHUB_TAG}*

.include "../../lang/go/go-package.mk"
.include "../../devel/go-sys/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
