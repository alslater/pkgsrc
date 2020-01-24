/*********************************************************************
*
*   Module:
*       Property.h
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

#ifndef PROPERTY_H
#define PROPERTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Property
{
   private:
	   int m_type;
       char *m_name;
       char *m_value;
       Property *m_prev;			// Previous sibling
       Property *m_next;			// Next sibling
	   Property *m_children;      // descendents starting at oldest.
	   int m_numChildren;			// number of descendents
	   Property *m_lastChild;		// youngest descendent
	   int m_index;				// descendent position
	   int m_childIndex;			// used while enumerating

   protected:
	   void init (void);
	   void initName (int size);
	   void initValue (int size);

   public:
       Property ();
       Property (char *name);
	   Property (char *name, char *value);

	   ~Property ();

	   void setName (char *newName);
	   char *getName (void);

	   void setValue (char *newValue);
	   char *getValue (void);

	   void setIntValue (int intValue);
	   int getIntValue (void);

	   Property *getFirstChild (void);
	   Property *getLastChild (void);

	   int getNumChildren (void);
	   int getChildIndex (void);
	   int getIndex (void);

	   void setType (int newType);
	   int getType (void);

	   Property *addChild (Property *child);
       Property *removeChild (Property *aChild);

	   void setPrevSibling (Property *prev);
	   Property *getPrevSibling (void);

	   void setNextSibling (Property *next);
	   Property *getNextSibling (void);

	   Property *locateSibling (Property *aSibling);
	   Property *locateSibling (char *name);
	   Property *locateSibling (int index);

	   Property *locateChild (Property *aChild);
	   Property *locateChild (char *name);
	   Property *locateChild (int index);

	   Property *enumSiblings (char *listName);

	   Property *enumChildren (void);
	   Property *enumChildren (char *listName);

	   int setProperty (char *listName, char *propertyName, char *propertyValue);

	   char *getPropertyValue (char *listName, char *propertyName);
	   Property *getProperty (char *listName, char *propertyName);

	   int getPropertyIntValue (char *listName, char *propertyName);

	   char *getPropertyValueAt (char *listName, int propertyIndex);
	   Property *getPropertyAt (int propertyIndex);

};

#endif

