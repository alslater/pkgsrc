/**************************************************************************
 * File Name :        ISOStatus.h
 *
 * Contents:		  ISOStatus class
 *
 * Description :	  This header file contains the class called ISOStatus which is used by the
 *					  message object to update the status of the message after each operation
 *
 * Author :           Arun G
 *
 * Date Created :     05/21/2001
 *
 * Modified :
 *
 **************************************************************************
 */


/**************************************************************************
 *
 * CLASS NAME:          ISOStatus
 *
 * SCOPE:               public
 *
 * DESCRIPTION:			ISOStatus is a class which stores the status of a ISOMessage object at
 *						any given point of time.
 *
 **************************************************************************
 */

#ifndef ISOSTATUS_H
#define ISOSTATUS_H

#include "STU_platform.h"

 class LINKDLL ISOStatus
 {
	//Attributes
    private:

       //Indicates the Status. Values can be TRUE or FALSE.
       bool m_status;

       //Integer value which represents the result code. Values range from 1 to 6.
       int m_resultCode;

       //Character array which stores the result Description.
       char *m_resultDesc;

    //Constructor and Functions
   	public:

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
		 ISOStatus();

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
		 ~ISOStatus();


		//Methods:

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
		 ******************************************************************************************
		 */
		 void setStatus(bool status);


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
		 ******************************************************************************************
		 */
		 void  setResultCode(int resCode);


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
		 ******************************************************************************************
		 */
		 void  setResultDesc(char* resDesc);


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
		 ******************************************************************************************
		 */
		 bool  getStatus();


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
		 ******************************************************************************************
		 */
		 int  getResultCode();


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
		 ******************************************************************************************
		 */
		 char*  getResultDesc();

		/******************************************************************************************
		 *
		 * NAME:                update ()
		 *
		 * ARGUMENTS:
		 *
		 * RETURN VALUE:        none
		 *
		 * SCOPE:               public
		 *
		 * DESCRIPTION:			This function sets all status information in one call
		 *                      - should only be used by API internally.
		 *
		 ******************************************************************************************
		 */

		 void update (bool status, int resultCode, char *resultDesc);
};

#endif

