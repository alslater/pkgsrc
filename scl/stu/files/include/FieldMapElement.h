/*********************************************************************
*
*   Module:
*       FieldMapElement.h
*
*   Contents:
*       FieldMapElement class
*
*   Description
*
*       This header file contains the FieldMapElement class
*
*   See Also:
*
*
*
*   Created:
*		22 May 2001	Arun G.
*
*   Modified:
*
* 8/10/2001 Lonnie L. Filbrun - removed redundant fields. modified constructor
*           to create proper field instance based on passed-in parameter
*
*
**********************************************************************/

#ifndef FIELDMAPELEMENT_H
#define FIELDMAPELEMENT_H

#include "STU_platform.h"

//specific inlcudes
#include "ISOField.h"

/***************************************************************************
 * CLASS NAME:          FieldMapElement
 *
 * SCOPE:               public and instantiable
 *
 * DESCRIPTION:
 *
 * The class FieldMapElement will be called from ISO1100SVMessage object
 * This class assigns the values passed to the constructor to the class variables
 *
 **************************************************************************
 */

class LINKDLL FieldMapElement
{

//Attributes
public:
	//Class variables

	//indicates weather this field supported by the message.
	bool m_isSupported;

	//indicates weather the field is "REQUIRED", "CONDITIONAL" or "OPTIONAL"
	int m_isRequired;

	//indicates the type of field "FIXED" "LLVARIABLE" or "LLLVARIABLE"
	int m_fieldType;

	//indicates the datatype of the data. It may be "NUMERIC" , "ALPHANUMERIC"
	int m_dataType;

	//indicates the maximum length of the field
	int m_maxDataLength;

	//points to the ISOField object
	ISOField *m_fieldPointer;

	//indicates weather the field is set or not.
	bool m_isSet;

	//Constructor
	//default constructor
	FieldMapElement();

	/*
	 * creates an instance of FieldMapElement
	 */
	FieldMapElement(bool isSupported, int isReq, int fieldType, int dataType, int maxLen);

	//Destructor
	~FieldMapElement();

private:

};

#endif

