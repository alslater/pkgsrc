# $NetBSD: Makefile,v 1.14 2015/12/06 13:51:30 taca Exp $

MODNAME=		pdo
CATEGORIES+=		databases
COMMENT=		PHP extension for PHP Data Objects (base)

USE_PHP_EXT_PATCHES=	yes

.include "../../mk/bsd.prefs.mk"

.include "../../lang/php/ext.mk"

CONFIGURE_ARGS+=	--with-${MODNAME}

INSTALLATION_DIRS+=	include/php/ext/pdo

PDO_INCLUDES=		php_pdo_driver.h php_pdo.h php_pdo_error.h
PLIST_VARS+=		pdo_error pdo_sql_parser
PLIST_SRC+=		${.CURDIR}/../../databases/php-pdo/PLIST.pdo
.if ${PHP_VER} >= 84
PDO_INCLUDES+=		pdo_sql_parser.h
PLIST.pdo_sql_parser=	yes
.endif

post-install:
.for inc in ${PDO_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/pdo/${inc}
.endfor

.include "../../mk/bsd.pkg.mk"
