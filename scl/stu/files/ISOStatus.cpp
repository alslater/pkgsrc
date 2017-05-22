/**************************************************************************
 * File Name :        ISOStatus.cpp
 *
 * Contents:		  Constructor, Destructor,	Functions -	ISOStatus::setStatus, 
 *															ISOStatus::setResultCode, 
 *															ISOStatus::setResultDesc
 *															ISOStatus::getStatus, 
 *															ISOStatus::getResultCode, 
 *															ISOStatus::getResultDesc 
 *
 * Description :	  This file contains the implementation of the functions in ISOStatus class 
 *					  which are used by the message object to update the status of the message 
 *					  after each operation
 *
 * Author :				Arun G
 *
 * Date Created :		05/22/2001
 *
 * Modified :
 *						06 July 2001	Arun G.
 *							- Fixed memory leaks in functions setResultDesc and getResultDesc
 * 14 July 2001 -  Lonnie L. Filbrun - fixed memory leaks - arrays are deleted by delete [] foo;
 *     
 *****************************************************************************************
 */

//standard inlcudes
#include <string.h>
#include <malloc.h>

//Package specific header files
#include "Enumerations.h"
#include "ISOStatus.h"



//Constructor
/******************************************************************************************
 *
 * NAME:                ISOStatus
 *
 * ARGUMENTS:           
 *                                   
 * RETURN VALUE:        
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This is the default constructor for the class.
 * 
 ******************************************************************************************
 */
 ISOStatus::ISOStatus()
 {
    m_status = false;
	m_resultCode = 0;

	m_resultDesc = new char [255+1];

    memset (m_resultDesc, 0, 255+1);

    return;
 }


//Destructor
/******************************************************************************************
 *
 * NAME:                ~ISOStatus
 *
 * ARGUMENTS:           
 *                                   
 * RETURN VALUE:        
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This is the destructor for the class.
 * 
 ******************************************************************************************
 */
 ISOStatus::~ISOStatus()
 {
	 //delete memory allocated to the pointer
	 if (m_resultDesc != NULL)
	 {
		 delete [] m_resultDesc;
		 m_resultDesc = NULL;
	 }
 }


//Functions

/******************************************************************************************
 *
 * NAME:                setStatus
 *
 * ARGUMENTS:           boolean status
 *
 * RETURN VALUE:        
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This sets the StatusCode with the value passed in the argument
 * 
 * IMPLEMENTATION:		Assign the argument to the field.
 ******************************************************************************************
 */
 void ISOStatus::setStatus(bool stat)
 {
	 m_status = stat;
 }


/******************************************************************************************
 *
 * NAME:                setResultCode()
 *
 * ARGUMENTS:           int resCode
 *
 * RETURN VALUE:        
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This function sets the ResultCode with the value passed as argument
 *  
 * IMPLEMENTATION:		Assign the argument to the field.
 ******************************************************************************************
 */
 void  ISOStatus::setResultCode(int resCode)
 {
	 m_resultCode = resCode;
 }

 
 /******************************************************************************************
 *
 * NAME:                getResultDesc()
 *
 * ARGUMENTS:           char* resDesc
 *
 * RETURN VALUE:        
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This function assigns the Character array passed as argument to the
 *						resultDesc field.
 * 
 * IMPLEMENTATION:		Assign the argument to the field. 
 ******************************************************************************************
 */
 void  ISOStatus::setResultDesc(char* resDesc)
 {
	 int len = 0;

	 if (resDesc != NULL)
	 {
	     len = strlen (resDesc);

		 memcpy (m_resultDesc, resDesc, (len < 255) ? len : 255 );
		 m_resultDesc[((len < 255) ? len : 255)] = 0;
	 }
 }


/******************************************************************************************
 *
 * NAME:                getStatus
 *
 * ARGUMENTS:           
 *
 * RETURN VALUE:        boolean
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This function returns the StatusCode in the ISOStatus object
 *
 * IMPLEMENTATION:		Return the value of the 'status' variable
 * 
 ******************************************************************************************
 */
 bool ISOStatus::getStatus()
 {
	return m_status ;
 }


/******************************************************************************************
 *
 * NAME:                getResultCode()
 *
 * ARGUMENTS:           
 *
 * RETURN VALUE:        integer representing the StatusCodes
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This function returns the ResultCode in the ISOStatus object
 *
 * IMPLEMENTATION:		Return the value of the 'resultCode' integer
 * 
 ******************************************************************************************
 */
 int  ISOStatus::getResultCode()
 {
	return m_resultCode; 
 }


/******************************************************************************************
 *
 * NAME:                getResultDesc()
 *
 * ARGUMENTS:           
 *
 * RETURN VALUE:        Character array which contains the description
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This function returns the ResultDesc in the ISOStatus object
 *
 * IMPLEMENTATION:		Return the 'resultDesc' character array
 * 
 ******************************************************************************************
 */
char*  ISOStatus::getResultDesc()
{
	 return m_resultDesc;
}

/******************************************************************************************
 *
 * NAME:                update()
 *
 * ARGUMENTS:           
 *                      bool status
 *                      int resultCode
 *                      char *resultDesc
 *
 * RETURN VALUE:        void
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			This function sets all status member variables with one call.
 *
 * IMPLEMENTATION:		set all isostatus member variables.
 * 
 ******************************************************************************************
 */

void ISOStatus::update (bool status, int resultCode, char *resultDesc)
{
	setStatus (status);
	setResultCode (resultCode);
	setResultDesc (resultDesc);

	return;
}
