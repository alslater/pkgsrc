# $NetBSD: Makefile,v 1.27 2016/12/02 11:00:39 fhajny Exp $

DISTNAME=		elixir-1.6.6
PKGNAME=		${DISTNAME:S/-server//}
CATEGORIES=		lang
#MASTER_SITES=		https://github.com/elixir-lang/elixir/archive/v${PKGVERSION_NOREV}/
#EXTRACT_SUFX=		.tar.gz
MASTER_SITES= 		${MASTER_SITE_GITHUB:=elixir-lang/}
GITHUB_TAG= 		v${PKGVERSION_NOREV}

MAINTAINER=		al.slater@scluk.com
HOMEPAGE=		https://github.com/elixir-lang/elixir
COMMENT=		Elixir is a dynamic, functional language designed for building scalable and maintainable applications.	
LICENSE=		apache-2.0

DEPENDS+=		erlang>=18.0:../../lang/erlang

USE_TOOLS+=		gmake

.include		"../../mk/bsd.prefs.mk"

BUILD_TARGET=		compile

REPLACE_INTERPRETER+=	elixir
REPLACE.elixir.old=	.*elixir
REPLACE.elixir.new=	${PREFIX}/bin/elixir
REPLACE_FILES.elixir= bin/mix

.include "../../mk/bsd.pkg.mk"

MAKE_ENV+=		LC_CTYPE="en_US.UTF-8"
MAKE_ENV+=		LC_LANG="en_US.UTF-8"
MAKE_ENV+=		LC_ALL=""


