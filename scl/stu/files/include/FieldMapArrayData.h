/*********************************************************************
*
*   Module:
*       FieldMapArrayData.h
*
*   Contents:
*       FieldMapElement data
*
*   Description
*
*       This header file contains the FieldMapElement data
*       initialization. This is used by both the ISO8583Implementation
*       class AND the tester applications.
*
*   See Also:
*       Enumeriations.h
*		FieldMapElement.h
*
*   Created:
*		10 August 2001	Lonnie L. Filbrun
*
*   Modified:
*
*
**********************************************************************/
#ifndef FIELDMAP_ARRAY_DATA_H
#define FIELDMAP_ARRAY_DATA_H

#include "Enumerations.h"
#include "FieldMapElement.h"

void InitFieldMapArray (FieldMapElement **);

#endif

