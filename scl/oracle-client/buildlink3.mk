BUILDLINK_TREE+=       oracle-client 

.if !defined(ORACLE_CLIENT_BUILDLINK3_MK)
ORACLE_CLIENT_BUILDLINK3_MK:=

.include "../../scl/oracle-client/oraclehome.mk"

BUILDLINK_API_DEPENDS.oracle-client+=	oracle-instantclient>=11
BUILDLINK_PKGSRCDIR.oracle-client?=      ../../scl/oracle-client
.endif # ORACLE_CLIENT_BUILDLINK3_MK

BUILDLINK_TREE+=        -oracle-client

