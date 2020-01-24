/*********************************************************************
*
*   File name:
*       ISO8583Message.cpp
*
*   Contents:
*       ISO8583Message Constructor and Destructor
*       
*   Description:
*
*		This file contains the constructor and destructor implementation of the ISO8583Message. 
*
*   See Also:
*
*
*   Created:
*       05/21/01 Arun G.
*
*   Modified:
*		08 June 2001 Shubha Kumar
*				-Removed the overloaded constructor as the attribute moved to the derisved class
*				-Modified the destructor to remove the delete statemnet for the msgType pointer
*
*
**********************************************************************/

#include <stdio.h>
#include <iostream>

//Package specific header files
#include "Enumerations.h"
#include "ISO8583Message.h"

using namespace std;

extern int gTrace;
extern int gDebug;

//Default Constructor
ISO8583Message::ISO8583Message ()
{

}

//Destructor
//The destructor will set the pointer reference to NULL
ISO8583Message::~ISO8583Message ()
{
	if (gDebug)
	   cout << "ISO8583Message::~ISO8583Message" << endl;
}
