/*********************************************************************
*
*   Module:
*       FieldMapElement.cpp
*
*   Contents:
*       FieldMapElement class
*       
*   Description
*
*       This header file contains the FieldMapElement class 
*
*   See Also:
*		ISOField.h
*		FieldMapElement.h
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

#include <stdio.h>

//specific header files
#include "Enumerations.h"
#include "FieldMapElement.h"

/*  Name: FieldMapElement
 *	Description : Default Constructor
 */

FieldMapElement::FieldMapElement()
{
	m_isSupported=false;
	m_isRequired=0;
	m_fieldType=0;
	m_dataType=0;
	m_maxDataLength=0;
	m_fieldPointer=NULL;
	m_isSet=false;
}

/*  Name: FieldMapElement
 *	Description : Default destructor
 */

FieldMapElement::~FieldMapElement()
{
	//delete memory allocated to the ISOField pointer
	if (m_fieldPointer!=NULL)
		delete m_fieldPointer;
}

/*  Name: FieldMapElement
 *  Arguments:
 *		isSupported: indicates whether this field supported by the message type.
 *		isReq: indicates whether the field is "REQUIRED", "CONDITIONAL" or "OPTIONAL"
 *		fieldType: indicates the type of field "FIXED" / "LLVAR" / or "LLLVAR"
 *		dataType: indicates the datatype of the data. It may be "NUMERIC" , "ALPHANUMERIC", etc.
 *		maxLen: indicates the maximum length of the field
 *
 *   
 *   Return Type: 
 *
 *   Implementation Details:
 *		1. Assign the parameter values to the class variables.
 */

FieldMapElement::FieldMapElement(bool isSupported, int isReq, int fieldType, int dataType, int maxLen)
{
	this->m_isSet = false;
	this->m_isSupported = isSupported;
	this->m_isRequired = isReq;
	this->m_fieldType = fieldType;
	this->m_dataType = dataType;
	this->m_maxDataLength = maxLen;
	
	switch (fieldType)
	{
	   case LLVARLENGTH:
	      this->m_fieldPointer = new ISOFieldLLVar (dataType, maxLen);
	      break;

	   case LLLVARLENGTH:
		  this->m_fieldPointer = new ISOFieldLLLVar (dataType, maxLen);
	      break;

	   case FIXEDLENGTH:
	   default:
	      this->m_fieldPointer = new ISOFieldFixed (dataType, maxLen);
	      break;
	}

	return;
}
