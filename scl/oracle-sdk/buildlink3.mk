BUILDLINK_TREE+=       oracle-sdk 

.if !defined(ORACLE_SDK_BUILDLINK3_MK)
ORACLE_SDK_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.oracle-sdk+=   oracle-instantclient-sdk>=11
BUILDLINK_PKGSRCDIR.oracle-sdk?=      ../../scl/oracle-sdk

.include	"../../scl/oracle-client/buildlink3.mk"

.endif # ORACLE_SDK_BUILDLINK3_MK

BUILDLINK_TREE+=        -oracle-sdk

