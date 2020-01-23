# $NetBSD$

BUILDLINK_TREE+=	aws-sdk-cpp

.if !defined(AWS_SDK_CPP_BUILDLINK3_MK)
AWS_SDK_CPP_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.aws-sdk-cpp+=	aws-sdk-cpp>=1.6.6
BUILDLINK_ABI_DEPENDS.aws-sdk-cpp?=	aws-sdk-cpp>=1.6.6nb1
BUILDLINK_PKGSRCDIR.aws-sdk-cpp?=	../../devel/aws-sdk-cpp

.include "../../security/openssl/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../audio/pulseaudio/buildlink3.mk"
.endif	# AWS_SDK_CPP_BUILDLINK3_MK

BUILDLINK_TREE+=	-aws-sdk-cpp
