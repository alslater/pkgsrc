/*********************************************************************
*
*   Module:
*       Property.cpp
*
*   Contents:
*       Property class
*       
*   Description
*
*       This header file contains the Property class 
*
*   See Also:
*
*
*
*   Created:
*		14 September 2001	Lonnie L. Filbrun
*
*   Modified:
*
*
**********************************************************************/

#include <iostream>

#include "Property.h"

using namespace std;

extern int gTrace;
extern int gDebug;

Property::Property ()
{
	init ();
	
	return;
}

Property::Property (char *name)
{
	init ();

	setName (name);

	return;
}

Property::Property (char *name, char *value)
{
	init ();

	setName (name);
	setValue (value);

	return;
}

void Property::init (void)
{
	m_name = NULL;
	m_value = NULL;

	m_prev = NULL;
	m_next = NULL;

	m_type = 0;
	m_numChildren = 0;
	m_childIndex = 0;
	m_index = 0;

	m_children = NULL;
	m_lastChild = NULL;

	return;
}

Property::~Property ()
{
	if (m_name != NULL)
	{
	   delete [] m_name;
	   m_name = NULL;
	}

	if (m_value != NULL)
	{
	   delete [] m_value;
	   m_value = NULL;
	}

	return;
}

void Property::initName (int size)
{
	if (m_name != NULL)
	{
	   delete [] m_name;
	   m_name = NULL;
	}

	m_name = new char [size + 1];
	
	if (m_name == NULL)
	   return;

	memset (m_name, 0, size + 1);

	return;
}

void Property::setName (char *newName)
{
	int len = strlen (newName);

	initName (len);

	strcpy (m_name, newName);

	return;
}

char *Property::getName (void)
{
	return m_name;
}

void Property::initValue (int size)
{
	if (m_value != NULL)
	{
	   delete [] m_value;
	   m_value = NULL;
	}

	m_value = new char [size + 1];
	
	if (m_value == NULL)
	   return;

	memset (m_value, 0, size + 1);

	return;
}

void Property::setValue (char *newValue)
{
	int len = strlen (newValue);

	initValue (len);

	strcpy (m_value, newValue);

	return;
}

char *Property::getValue (void)
{
	return m_value;
}

void Property::setIntValue (int intValue)
{
	initValue (10);

	sprintf (m_value, "%d", intValue);

	return;
}

int Property::getIntValue (void)
{
	return atoi (m_value);
}

Property *Property::getFirstChild (void)
{
	return m_children;
}

Property *Property::getLastChild (void)
{
	return m_lastChild;
}

int Property::getNumChildren (void)
{
	return m_numChildren;
}

int Property::getChildIndex (void)
{
	return m_childIndex;
}

int Property::getIndex (void)
{
	return m_index;
}

void Property::setType (int newType)
{
	m_type = newType;

	return;
}

int Property::getType (void)
{
	return m_type;
}

Property *Property::addChild (Property *aChild)
{
	Property *tmpChild = NULL;

	if (aChild == NULL)
	   return NULL;

	aChild->m_index = m_numChildren;

	if (m_children == NULL)
	{
	   // update this properties children (head)
	   // to point to the new child property.
	   m_children = aChild;

	   // update this properties lastChild (tail)
	   // to point to the new child property.
	   m_lastChild = aChild;
	}
	else
	{
	   tmpChild = m_lastChild;

	   // tack on to end of children list;
	   m_lastChild->setNextSibling (aChild);

	   // update this properties prev sibling
	   // to point to the new child property.
	   aChild->setPrevSibling (m_lastChild);

	   // update this properties last child (tail)
	   // to point to the new child property.
	   m_lastChild = aChild;
	}

	m_numChildren++;

	return aChild;
}

//	           an   bn   cn = NULL
//           a    b    c
// NULL = ap   bp   cp
//
//  a->next = c
//  c->prev = a
//

Property *Property::removeChild (Property *aChild)
{
	Property *tmpChild = NULL;
	Property *next = NULL;
	Property *prev = NULL;
	
	if (aChild == NULL)
	   return NULL;

	next = aChild->getNextSibling ();
	prev = aChild->getPrevSibling ();

	// Attempt to locate the child in this
	// properties children list.
	tmpChild = locateChild (aChild);
	
	// If located
	if (tmpChild != NULL)
	{
	   if (tmpChild == m_children)
	   {
	      // Head of list
		  // make the next head of list
		  m_children = tmpChild->m_next;
	   }
	   else if (tmpChild == m_lastChild)
	   {
	      // Tail of list
		  // make the prev tail of list
		  m_lastChild = tmpChild->m_prev;
	   }

	   //
	   if (prev != NULL)
	      prev->setNextSibling (next);
	   
	   if (next != NULL)
		  next->setPrevSibling (prev);

	   tmpChild->setNextSibling (NULL);
	   tmpChild->setPrevSibling (NULL);

	   m_numChildren--;
	}

	return tmpChild;
}

void Property::setPrevSibling (Property *prev)
{
	if (prev != NULL)
	   prev->m_next = this;
	
	m_prev = prev;

	return;
}

Property *Property::getPrevSibling (void)
{
	return m_prev;
}

void Property::setNextSibling (Property *next)
{
	if (next != NULL)
	   next->m_prev = this;

	m_next = next;

	return;
}

Property *Property::getNextSibling (void)
{
	return m_next;
}

Property *Property::locateSibling (Property *aSibling)
{
	Property *le = NULL;
	Property *ne = NULL;
	Property *start = this;

	for (le = m_children; le != NULL; le = ne)
	{
	   ne = le->m_next;

	   if (le == aSibling)
	      return le;
	}

	return NULL;
}

Property *Property::locateSibling (char *name)
{
	Property *le = NULL;
	Property *ne = NULL;

	for (le = m_children; le != NULL; le = ne)
	{
	   ne = le->m_next;

	   if (strcmp (le->m_name, name) == 0)
	      return le;
	}

	return NULL;
}

Property *Property::locateSibling (int index)
{
	Property *le = NULL;
	Property *ne = NULL;

	for (le = m_children; le != NULL; le = ne)
	{
	   ne = le->m_next;

	   if (le->m_index == index)
	      return le;
	}

	return NULL;
}

Property *Property::locateChild (Property *aChild)
{
	Property *le = NULL;
	Property *ne = NULL;

	for (le = m_children; le != NULL; le = ne)
	{
	   ne = le->m_next;

	   if (le == aChild)
	      return le;
	}

	return NULL;
}

Property *Property::locateChild (char *name)
{
	Property *le = NULL;
	Property *ne = NULL;

	for (le = m_children; le != NULL; le = ne)
	{
	   ne = le->m_next;

	   if (strcmp (le->m_name, name) == 0)
	      return le;
	}

	return NULL;
}

Property *Property::locateChild (int index)
{
	Property *le = NULL;
	Property *ne = NULL;

	for (le = m_children; le != NULL; le = ne)
	{
	   ne = le->m_next;

	   if (le->m_index == index)
	      return le;
	}

	return NULL;
}

Property *Property::enumSiblings (char *listName)
{
	int numChildren = 0;
	Property *selectedChild = NULL;
	Property *aProperty = NULL;

	selectedChild = locateChild (listName);

	if (selectedChild == NULL)
	{
	   if (gDebug)
	      cout << "selected property list " << listName << " does not exist." << endl;
	   
	   return NULL;
	}

	numChildren = selectedChild->getNumChildren ();

	if (selectedChild->m_childIndex < numChildren)
	{
	   aProperty = selectedChild->getPropertyAt (selectedChild->m_childIndex);
	   selectedChild->m_childIndex++;
	}
	else
	{
	   selectedChild->m_childIndex = 0;
	}

	return aProperty;
}

Property *Property::enumChildren (void)
{
	int numChildren = 0;
	Property *aChild = NULL;

	numChildren = getNumChildren ();

	if (m_childIndex < numChildren)
	{
	   aChild = getPropertyAt (m_childIndex);
	   m_childIndex++;
	}
	else
	{
	   m_childIndex = 0;
	}

	return aChild;
}

Property *Property::enumChildren (char *listName)
{
	int numChildren = 0;
	Property *aChild = NULL;
	Property *selectedList = NULL;

	selectedList = locateChild (listName);

	if (selectedList == NULL)
	{
	   if (gDebug)
	      cout << "selected property list " << listName << " does not exist." << endl;
	   	   
	   return NULL;
	}

	numChildren = selectedList->getNumChildren ();

	if (selectedList->m_childIndex < numChildren)
	{
	   aChild = selectedList->getPropertyAt (selectedList->m_childIndex);
	   selectedList->m_childIndex++;
	}
	else
	{
	   selectedList->m_childIndex = 0;
	}

	return aChild;
}

int Property::setProperty (char *listName,
	char *propertyName,
	char *propertyValue)
{
	Property *selectedChild = NULL;
	Property *selectedList = NULL;
	Property *newChild = NULL;

	selectedList = locateChild (listName);

	if (selectedList == NULL)
	{
	   if (gDebug)
	      cout << "selected property list " << listName << " does not exist." << endl;
	   
	   return -1;
	}

	selectedChild = selectedList->locateChild (propertyName);

	if (selectedChild == NULL)
	{
	   // not on list
	   newChild = new Property (propertyName, propertyValue);

	   selectedList->addChild (newChild);

	   return 0;
	}
	else
	{
	   if (propertyValue != NULL)
	   {
		  selectedChild->setValue (propertyValue);

	      return 0;
	   }
	}

	return -1;
}

char *Property::getPropertyValue (char *listName, char *propertyName)
{
	Property *selectedChild = NULL;
	Property *selectedList = NULL;

	selectedList = locateChild (listName);

	if (selectedList == NULL)
	{
	   if (gDebug)
	      cout << "selected property list " << listName << " does not exist." << endl;
	   
	   return NULL;
	}

	selectedChild = selectedList->locateChild (propertyName);

	if (selectedChild == NULL)
	{
	   if (gDebug)
	      cout << "selected property \'" << propertyName << "\' was not located in the " << listName << " property list." << endl;

	   return NULL;
	}

	return selectedChild->getValue ();
}

int Property::getPropertyIntValue (char *listName, char *propertyName)
{
	Property *selectedChild = NULL;
	Property *selectedList = NULL;

	selectedList = locateChild (listName);

	if (selectedList == NULL)
	{
	   if (gDebug)
	      cout << "selected property list " << listName << " does not exist." << endl;

	   return 0;
	}

	selectedChild = selectedList->locateChild (propertyName);

	if (selectedChild == NULL)
	{
	   if (gDebug)
	      cout << "selected property \'" << propertyName << "\' was not located in the " << listName << " property list." << endl;

	   return 0;
	}

	return selectedChild->getIntValue ();
}

Property *Property::getProperty (char *listName, char *propertyName)
{
	Property *selectedChild = NULL;
	Property *selectedList = NULL;

	selectedList = locateChild (listName);

	if (selectedList == NULL)
	{
	   if (gDebug)
	      cout << "selected property list " << listName << " does not exist." << endl;
	   
	   return NULL;
	}

	selectedChild = selectedList->locateChild (propertyName);

	if (selectedChild == NULL)
	{
	   if (gDebug)
	      cout << "selected property \'" << propertyName << "\' was not located in the " << listName << " property list." << endl;

	   return NULL;
	}

	return selectedChild;
}

char *Property::getPropertyValueAt (char *listName, int propertyIndex)
{
	Property *selectedChild = NULL;
	Property *selectedList = NULL;

	selectedList = locateChild (listName);

	if (selectedList == NULL)
	{
	   if (gDebug)
	      cout << "selected property list " << listName << " does not exist." << endl;
	   
	   return NULL;
	}

	selectedChild = selectedList->locateChild (propertyIndex);

	if (selectedChild == NULL)
	{
	   if (gDebug)
	      cout << "selected property " << propertyIndex << " was not located in the " << listName << " property list." << endl;

	   return NULL;
	}

	return selectedChild->getValue ();
}

Property *Property::getPropertyAt (int propertyIndex)
{
	Property *selectedChild = NULL;

	selectedChild = locateChild (propertyIndex);

	if (selectedChild == NULL)
	{
	   if (gDebug)
	      cout << "selected property " << propertyIndex << " was not located in the " << getName () << " property list." << endl;

	   return NULL;
	}

	return selectedChild;
}
