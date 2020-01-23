# $NetBSD$

DISTNAME=	aws-sdk-cpp-1.6.6
PKGREVISION=	1
CATEGORIES=	devel
MASTER_SITES=	-https://github.com/aws/aws-sdk-cpp/archive/${PKGVERSION_NOREV}${EXTRACT_SUFX}
EXTRACT_SUFX=	.tar.gz

MAINTAINER=	al.slater@scluk.com
HOMEPAGE=	https://github.com/aws/aws-sdk-cpp
COMMENT=	AWS SDK for C++
LICENSE=	apache-2.0

USE_CMAKE=    yes
USE_LANGUAGES=             c c++

USE_TOOLS+=	gmake

CMAKE_ARGS+=	-DCMAKE_BUILD_TYPE:STRING=Release -DENABLE_TESTING=OFF

#MAKE_JOBS_SAFE=		no

#do-build:
#	cd ${WRKSRC} && env ${CONFIGURE_ENV} make VERBOSE=1 

.include "../../security/openssl/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../audio/pulseaudio/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"

