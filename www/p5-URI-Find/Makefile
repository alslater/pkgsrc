# $NetBSD: Makefile,v 1.14 2015/06/12 10:52:13 wiz Exp $

DISTNAME=		URI-Find-20140709
PKGNAME=		p5-${DISTNAME}
PKGREVISION=		1
CATEGORIES=		www perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=URI/}

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://search.cpan.org/dist/URI-Find/
COMMENT=		Perl5 module to find URIs in arbitrary text
LICENSE=		${PERL5_LICENSE}

# requires URI::URL 5.00 - oldest available URI on CPAN contains 5.03
DEPENDS+=		p5-URI>=1.60:../../www/p5-URI
BUILD_DEPENDS+=		{perl>=5.10.1,p5-Test-Simple>=0.82}:../../devel/p5-Test-Simple

USE_LANGUAGES=		# empty

PERL5_PACKLIST=		auto/URI/Find/.packlist
PERL5_MODULE_TYPE=	Module::Build

#BUILD_DEPENDS+=		{perl>=5.13.11,p5-Module-Build>=0.30000}:../../devel/p5-Module-Build

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
