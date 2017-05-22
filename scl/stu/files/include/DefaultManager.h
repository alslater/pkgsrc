/*********************************************************************
*
*   Module:
*       DefaultManager.h
*
*   Contents:
*       DefaultManager class
*
*   Description
*
*       This header file contains the DefaultManager class
*   This object maintains a list of lists containing name/value pairs.
*   These lists (tables) can be loaded/saved from/to disk files.
*
*   Queries can be made to allow searching this default database
*   based on the desired table and the property you are looking for.
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
#ifndef DEFAULT_MANAGER_H
#define DEFAULT_MANAGER_H

#include "Property.h"

#ifdef _WIN32
#include <direct.h>
#endif

#define VALID		1
#define INVALID		2
#define ENOMEM		3

class DefaultManager
{
	private:
	   bool m_reload;

	   Property *m_defaults;

	   Property *m_propertyList;

	   char m_dbPath[255 + 1];

	protected:
	   void bootstrap (void);

	   void init (bool reload, char *dbPath);

	   Property *loadPropertyFile (char *listName);
	   int savePropertyFile (char *listName);

	   // Load a table listing the available lists.
	   Property *bootstrapTables (void);

	   Property *bootstrapMsgClasses (void);

	   // This enumeration defines the Status Codes used to update the ISOStatus Object
	   Property *bootstrapStatusCodes (void);

	   // This enumeration defines the Processing Codes used in ISO8583 Messages.
	   Property *bootstrapProcessingCodes (void);

	   // This enumeration defines the Action Codes used in ISO8583 Messages.
	   Property *bootstrapActionCodes (void);

	   // This enumeration defines the Merchant ID Codes used in ISO8583 Messages.
	   Property *bootstrapMerchantIDCodes (void);

	   // This enumeration defines the Card Type Codes used in ISO8583 Messages.
	   Property *bootstrapCardTypeCodes (void);

	   // This enumeration defines the Additional Response Data Type Codes used in ISO8583 Messages.
	   Property *bootstrapAddRespDataCodeTypes (void);

	   // This enumeration defines the Bit positions 1 to 64
	   Property *bootstrapFields (void);

	   // This enumeration defines the Bit position text 1 to 64
	   Property *bootstrapFieldText (void);

	public:
	   DefaultManager ();
	   DefaultManager (bool reload);
	   DefaultManager (bool reload, char *dbPath);

	   ~DefaultManager ();

	   void create_db (char *dbPath);
	   void drop_db (char *dbPath);

	   void add_property_list (char *tableName);
	   void drop_property_list (char *tableName);

	   void add_property (char *listName, char *propertyName, char *propertyValue);
	   void drop_property (char *listName, char *propertyName);

	   void show_tables (void);
	   void show_property_list (char *listName);
	   void show_property (char *listName, char *propertyName);

	   char *getValue (char *listName, char *propertyName);
	   int getIntValue (char *listName, char *propertyName);

	   void load (void);
	   void save (void);

	   void setReload (bool reload);
	   void setDbPath (char *path);
	   char *getDbPath ();

	   int loadDefaultsFile (char *defaultsFile);

	   void getCode (char *nameSpace, char *collection, char *code);

	private:
	   char *getDefaultByName (char *nameSpace, char *collection, char *varName);
	   char *getDefaultByValue (char *nameSpace, char *collection, char *varValue);

	   Property *selectVarList (Property *aProperty, char *listName);

	   Property *selectVarByName (Property *varList, char *varName);
	   Property *selectVarByValue (Property *varList, char *varValue);

};

#endif

