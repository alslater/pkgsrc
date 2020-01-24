/*********************************************************************
*
*   Module:
*       DefaultManager.cpp
*
*   Contents:
*       DefaultManager class
*       
*   Description
*
*       This file contains the DefaultManager class 
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

extern int gTrace;
extern int gDebug;

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include "DefaultManager.h"

using namespace std;

DefaultManager::DefaultManager ()
{
	init (false, ".\\db");

	return;
}

DefaultManager::DefaultManager (bool reload)
{
	init (reload, ".\\db");

	return;
}

DefaultManager::DefaultManager (bool reload, char *dbPath)
{
	init (reload, dbPath);

	return;
}

void DefaultManager::init (bool reload, char *dbPath)
{
	int rval = -1;

	m_defaults = new Property ("defaults");

	m_propertyList = new Property ("root");

/*
	setReload (reload);

	setDbPath (dbPath);

	if (m_reload == true)
	   load ();
	else
	   bootstrap ();
*/

	gDebug = 1;

//	rval = loadDefaultsFile (".defaults.xml");

//	getCode ("Globals", "ProcessingCodes", "CHECK_GUARANTEE");
//	getCode ("Globals", "ActionCodes", "PLEASE_CALL_ISSUER");

//	getCode ("ISO1100SV", "ProcessingCodes", "CHECK_GUARANTEE");
//	getCode ("ISO1100SV", "ActionCodes", "PLEASE_CALL_ISSUER");

	gDebug = 0;

	return;
}

DefaultManager::~DefaultManager ()
{
	Property *aChild = NULL;
	Property *selectedList = NULL;
	Property *removedChild = NULL;
	Property *removedList = NULL;
	char *name = NULL;

	if (m_propertyList != NULL)
	{
	   if (m_reload == false)
	      save ();

	   // we really need to walk the tree and
	   // remove/delete each child of each sibling.

	   while ((selectedList = m_propertyList->enumChildren ()) != NULL)
	   {
	      if (selectedList != NULL)
		  {
			 if (gDebug)
			    cout << "Cleaning up table " << endl;
	         
			 name = selectedList->getName ();

	         while ((aChild = selectedList->enumChildren (name)) != NULL)
			 {
	            if (aChild != NULL)
				{
				   if (gDebug)
				      cout << "Removing/deleting " << endl;
				   
				   if (gDebug)
			          cout << aChild->getIndex () << "->" << aChild->getName () << " = \'" << aChild->getValue () << "\'." << endl;

			       // remove the child and delete...
//				   removedChild = selectedList->removeChild (aChild);
//		           delete removedChild;
				}
			 }

			 if (gDebug)
			    cout << "Removing table " << selectedList->getName () << "..." << endl;
			 
//		     removedList = m_propertyList->removeChild (selectedList);
//			 delete removedList;
		  }
	   }

	   // lastly delete the root.
//	   delete m_propertyList;
//	   m_propertyList = NULL;
	}

	delete m_defaults;
	m_defaults = NULL;
	
	delete m_propertyList;
	m_propertyList = NULL;
	
	return;
}

void DefaultManager::create_db (char *dbPath)
{	
	init (true, dbPath);

	return;
}

void DefaultManager::drop_db (char *dbPath)
{
	// ???

	return;
}

void DefaultManager::add_property_list (char *listName)
{
	Property *newChild = NULL;
	Property *selectedChild = NULL;

	if (gDebug)
	   cout << "add_property_list: name: " << listName << "." << endl;
	
	selectedChild = m_propertyList->locateChild (listName);

	if (selectedChild == NULL)
	{
	   newChild = new Property (listName);
	   
	   m_propertyList->addChild (newChild);
	}
	else
	{
	   if (gDebug)
	      cout << "error: property_list " << listName << " already exists." << endl;
	}

	return;
}

void DefaultManager::drop_property_list (char *listName)
{
	Property *aChild = NULL;
	Property *removedChild = NULL;
	Property *selectedList = NULL;

	selectedList = m_propertyList->locateChild (listName);

	if (selectedList == NULL)
	{
	   if (gDebug)
	      cout << "error: property_list " << listName << " does not exist." << endl;	   
	}
	else
	{
	   if (gDebug)
	      cout << "dropping property_list " << listName << "." << endl;

	   while ((aChild = selectedList->enumChildren ()) != NULL)
	   {
	      if (aChild != NULL)
		  {
		     if (gDebug)
			    cout << aChild->getIndex () << "->" << aChild->getName () << " = \'" << aChild->getValue () << "\'." << endl;
		  }

		  removedChild = selectedList->removeChild (aChild);

		  delete removedChild;
	      removedChild = NULL;
	   }
	}

	return;
}

void DefaultManager::add_property (char *listName, char *propertyName, char *propertyValue)
{
	if (gDebug)
	   cout << "add_property: (" << listName << ") name: " << propertyName << " = \'" << propertyValue << "\'." << endl;
	
	m_propertyList->setProperty (listName, propertyName, propertyValue);

	return;
}

void DefaultManager::drop_property (char *listName, char *propertyName)
{
	Property *aProperty = NULL;

	if (gDebug)
	   cout << "drop_property: (" << listName << ") name: " << propertyName << "." << endl;
	
	aProperty = m_propertyList->getProperty (listName, propertyName);

	if (aProperty != NULL)
	{
	   m_propertyList->removeChild (aProperty);

	   delete aProperty;
	}

	return;
}

// no args = list tables
// 1 arg = list specified table
// 2 args = list specified property in specified table
void DefaultManager::show_tables (void)
{
	Property *aChild = NULL;

	if (gDebug)
	   cout << "Tables:" << endl;
	
	while ((aChild = m_propertyList->enumChildren ("Tables")) != NULL)
	{
	   if (aChild != NULL)
	   {
	      if (gDebug)
		     cout << aChild->getIndex () << "->" << aChild->getName () << " = \'" << aChild->getValue () << "\'." << endl;
	   }
	}

	return;
}

void DefaultManager::show_property_list (char *listName)
{
	Property *aChild = NULL;

	if (gDebug)
	   cout << "list: \'" << listName << "\'." << endl;

	while ((aChild = m_propertyList->enumChildren (listName)) != NULL)
	{
	   if (aChild != NULL)
	   {
	      if (gDebug)
	         cout << aChild->getIndex () << "->" << aChild->getName () << " = \'" << aChild->getValue () << "\'" << endl;
	   }
	}

	return;
}

void DefaultManager::show_property (char *listName, char *propertyName)
{
	if (gDebug)
	   cout << "show_property: " << propertyName << " = \'" << m_propertyList->getPropertyValue (listName, propertyName) << "\'." << endl;

	return;
}

char *DefaultManager::getValue (char *listName, char *propertyName)
{
	char *propertyValue = NULL;

	propertyValue = m_propertyList->getPropertyValue (listName, propertyName);

	if (gDebug)
	   cout << "getValue: " << propertyName << " = \'" << propertyValue << "\'." << endl;
	
	return propertyValue;
}

int DefaultManager::getIntValue (char *listName, char *propertyName)
{
	int propertyValue = 0;

	propertyValue = m_propertyList->getPropertyIntValue (listName, propertyName);

	if (gDebug)
	   cout << "getValueInt: " << propertyName << " = " << propertyValue << "." << endl;

	return propertyValue;
}

void DefaultManager::load (void)
{
	char *name = NULL;
	Property *aChild = NULL;
	Property *orgTables = NULL;

	orgTables = m_propertyList->addChild (loadPropertyFile ("Tables"));

	if (orgTables == NULL)
	{
	   orgTables = m_propertyList->addChild (bootstrapTables ());
	}

	while ((aChild = orgTables->enumChildren ()) != NULL)
	{
	   if (aChild != NULL)
	   {
		  if (gDebug)
	         cout << aChild->getIndex () << "->" << aChild->getName () << " = \'" << aChild->getValue () << "\'." << endl;

	      name = aChild->getName ();

	      if (strcmp (name, "Tables") != 0)
		  {
		     m_propertyList->addChild (loadPropertyFile (name));
		  }
	   }
	}
	
	return;
}

void DefaultManager::save (void)
{
	char *name = NULL;
	Property *aChild = NULL;

//	savePropertyFile ("Tables");
/*
	savePropertyFile ("MsgClasses");
    savePropertyFile ("Fields");
	savePropertyFile ("FieldText");
	savePropertyFile ("StatusCodes");
	savePropertyFile ("ProcessingCodes");
	savePropertyFile ("ActionCodes");
	savePropertyFile ("MerchantIDCodes");
	savePropertyFile ("CardTypeCodes");
	savePropertyFile ("AddRespDataCodes");
*/

	while ((aChild = m_propertyList->enumChildren ()) != NULL)
	{
	   if (aChild != NULL)
	   {
		  if (gDebug)
	         cout << aChild->getIndex () << "->" << aChild->getName () << " = \'" << aChild->getValue () << "\'." << endl;

	      name = aChild->getName ();

//	      if (strcmp (name, "Tables") != 0)
//		  {
		     savePropertyFile (name);
//		  }
	   }
	}

	return;
}

void DefaultManager::setReload (bool reload)
{
	m_reload = reload;

	return;
}

void DefaultManager::setDbPath (char *path)
{
	strcpy (m_dbPath, path);

	return;
}

char *DefaultManager::getDbPath (void)
{
	return m_dbPath;
}

Property *DefaultManager::loadPropertyFile (char *listName)
{
	int bufLen = 0;
	int fooLen = 0;
	int tokenLen = 0;
	FILE *fp = NULL;
	char *ptr = NULL;
    char *token = NULL;
	char lname[128+1] = "";
	char lvalue[512+1] = "";
	char buf[1024+1] = "";
	char fileName[255+1] = "";
	Property *newChild = NULL;

	sprintf (fileName,
		"%s\\%s.properties",
		   m_dbPath, listName);

	if (gDebug)
	   cout << "loading " << listName << " from " << fileName << "." << endl;

	fp = fopen (fileName, "r");

	if (fp == NULL)
	{
	   return NULL;
	}

	newChild = new Property (listName);

	while (! feof (fp))
	{
	   memset (lname, 0, 128+1);
	   memset (lvalue, 0, 512+1);

	   if (fgets (buf, 640, fp))
	   {
          ptr = buf;

	      bufLen = strlen (buf);

	      token = strstr (ptr, "=");

	      if (token == NULL)
	         return NULL;

	      tokenLen = strlen (token);

	      fooLen = (bufLen - tokenLen);

          if (fooLen > 128)
             return NULL;
      
	      strncpy (lname, buf, fooLen);

	      token = &buf[fooLen+1];

	      if (token == NULL)
	         return NULL;

	      tokenLen = strlen (token);

	      if (tokenLen > 512)
             return NULL;

	      strncpy (lvalue, token, (tokenLen-1));

	      if ((strcmp (lname, "") != 0)
		   && (strcmp (lvalue, "") != 0))
		  {
	         newChild->addChild (new Property (lname, lvalue));
		  }
	   }
	}

	fclose (fp);

	if (gDebug)
	   cout << "added " << newChild->getNumChildren () << " children." << endl;

	return newChild;
}

int DefaultManager::savePropertyFile (char *listName)
{
	int tok = 0;
	FILE *fp = NULL;
	Property *aChild = NULL;
	Property *selectedList = NULL;
	char fileName[255+1] = "";

	selectedList = m_propertyList->locateChild (listName);

	if (selectedList == NULL)
	{
	   if (gDebug)
	      cout << "error: property_list " << listName << " does not exist." << endl;
	}
	else
	{
	   if (gDebug)
	      cout << "saving property_list " << listName << " to file " << fileName << "." << endl;

	   sprintf (fileName,
	      "%s\\%s.properties",
		     m_dbPath, listName);

#ifdef _WIN32
	   mkdir(m_dbPath);
#else
	   mkdir(m_dbPath, 0666);
#endif

	   if (gDebug)
	      cout << "saving " << listName << " to file " << fileName << "." << endl;

	   fp = fopen (fileName, "w");

	   if (fp == NULL)
	   {
	      return -1;
	   }

	   while ((aChild = selectedList->enumChildren ()) != NULL)
	   {
	      if (aChild != NULL)
		  {
		     if (gDebug)
	            cout << aChild->getIndex () << "->" << aChild->getName () << " = \'" << aChild->getValue () << "\'." << endl;

	         tok = fprintf (fp,
		           "%s=%s\n",
		              aChild->getName (),
			          aChild->getValue ());
		  }
	   }

	   fclose (fp);
	}

	return 0;
}

void DefaultManager::bootstrap (void)
{
	m_propertyList->addChild (bootstrapTables ());

	m_propertyList->addChild (bootstrapMsgClasses ());

	// This enumeration defines the Status Codes used to update the ISOStatus Object
	m_propertyList->addChild (bootstrapStatusCodes ());

	// This enumeration defines the Processing Codes used in ISO8583 Messages.
	m_propertyList->addChild (bootstrapProcessingCodes ());

	// This enumeration defines the Action Codes used in ISO8583 Messages.
	m_propertyList->addChild (bootstrapActionCodes ());

	// This enumeration defines the Merchant ID Codes used in ISO8583 Messages.
	m_propertyList->addChild (bootstrapMerchantIDCodes ());

	// This enumeration defines the Card Type Codes used in ISO8583 Messages.
	m_propertyList->addChild (bootstrapCardTypeCodes ());

	// This enumeration defines the Additional Response Data Type Codes used in ISO8583 Messages.
	m_propertyList->addChild (bootstrapAddRespDataCodeTypes ());

	// This enumeration defines the Bit positions 1 to 64
	m_propertyList->addChild (bootstrapFields ());

	// This enumeration defines the Bit position text 1 to 64
	m_propertyList->addChild (bootstrapFieldText ());

	return;
}

// Load a table listing the available lists.
Property *DefaultManager::bootstrapTables (void)
{
	Property *newChild = NULL;

	newChild = new Property ("Tables");

	newChild->addChild (new Property ("0", "MsgClasses"));
	newChild->addChild (new Property ("1", "StatusCodes"));
	newChild->addChild (new Property ("2", "ProcessingCodes"));
	newChild->addChild (new Property ("3", "ActionCodes"));
	newChild->addChild (new Property ("4", "MerchantIDCodes"));
	newChild->addChild (new Property ("5", "CardTypeCodes"));
	newChild->addChild (new Property ("6", "AddRespDataCodes"));
	newChild->addChild (new Property ("7", "Fields"));
	newChild->addChild (new Property ("8", "FieldText"));

	return newChild;
}

// This enumeration defines the Additional Response Data Type Codes used in ISO8583 Messages.
Property *DefaultManager::bootstrapMsgClasses (void)
{
	Property *newChild = NULL;

	newChild = new Property ("MsgClasses");
	newChild->addChild (new Property ( "0", "ISO1100"));
	newChild->addChild (new Property ( "1", "ISO1100SV"));
	newChild->addChild (new Property ( "2", "ISO1110"));	

	newChild->addChild (new Property ( "3", "ISO1220"));	
	newChild->addChild (new Property ( "4", "ISO1220SV"));
	newChild->addChild (new Property ( "5", "ISO1230"));	

	newChild->addChild (new Property ( "6", "ISO1420"));	
	newChild->addChild (new Property ( "7", "ISO1420SV"));
	newChild->addChild (new Property ( "8", "ISO1430"));	
	
	newChild->addChild (new Property ( "9", "ISO1804"));
	newChild->addChild (new Property ("10", "ISO1814"));
	
	newChild->addChild (new Property ("11", "ISORequest"));	
	newChild->addChild (new Property ("12", "ISOResponse"));	

	return newChild;
}

// This enumeration defines the Status Codes used to update the ISOStatus Object
Property *DefaultManager::bootstrapStatusCodes (void)
{
	Property *newChild = NULL;

	newChild = new Property ("StatusCodes");
	newChild->addChild (new Property ("0", "VALID"));
	newChild->addChild (new Property ("1", "ENOMEM"));
	newChild->addChild (new Property ("2", "NO_DATA"));
	newChild->addChild (new Property ("3", "INVALID_BIT_POSITION"));
	newChild->addChild (new Property ("4", "INVALID"));
	newChild->addChild (new Property ("5", "VALIDATION_FAILED"));

	return newChild;
}

// This enumeration defines the Processing Codes used in ISO8583 Messages.
Property *DefaultManager::bootstrapProcessingCodes (void)
{
	Property *newChild = NULL;

	newChild = new Property ("ProcessingCodes");
	newChild->addChild (new Property ("CC_AUTHENTICATION",						"4000"));
	newChild->addChild (new Property ("CC_REVERSAL",							"4001"));
	newChild->addChild (new Property ("AUTHORIZATION_DEBIT",					"4099"));
	newChild->addChild (new Property ("CC_AUTHENTICATION_ADDRESS_VERIFICATION",	"4800"));
	newChild->addChild (new Property ("DEBIT_ADDRESS_VERIFICATION",				"4899"));
	newChild->addChild (new Property ("TELLER_CASH",							"14000"));
	newChild->addChild (new Property ("AMEX_EMERGENCY_CHECK_CASHING",			"34000"));
	newChild->addChild (new Property ("CHECK_GUARANTEE",						"44000"));
	newChild->addChild (new Property ("AMEX_TRAVELERS_CHECK",					"64000"));
	newChild->addChild (new Property ("AMEX_SIGHT_DRAFT",						"104000"));
	newChild->addChild (new Property ("CASHOUT",								"114099"));
	newChild->addChild (new Property ("ADDRESS_VERIFICATION",					"174800"));
	newChild->addChild (new Property ("ADDRESS_VERIFICATION2",					"174899"));	
	newChild->addChild (new Property ("AUTHORIZATION_CREDIT",					"204099"));
	newChild->addChild (new Property ("FUNDING",								"210099"));
	newChild->addChild (new Property ("AVAILABLE_FUNDS",						"300099"));
	newChild->addChild (new Property ("GRMS_RELATIONSHIP_INQUIRY",				"384900"));
	newChild->addChild (new Property ("ACTIVATE",								"920099"));
	newChild->addChild (new Property ("DEACTIVATE",								"930099"));

	return newChild;
}

// This enumeration defines the Action Codes used in ISO8583 Messages.
Property *DefaultManager::bootstrapActionCodes (void)
{
	Property *newChild = NULL;

	newChild = new Property ("ActionCodes");
	newChild->addChild (new Property ("APPROVED",							"0"));
	newChild->addChild (new Property ("APPROVE_WITH_ID",					"1"));
	newChild->addChild (new Property ("APPROVE_VIP",						"3"));
	newChild->addChild (new Property ("APPROVED_EXPRESS_REWARDS_PROGRAM",	"92"));
	newChild->addChild (new Property ("DENY",								"100"));
	newChild->addChild (new Property ("EXPIRED_CARD",						"101"));
	newChild->addChild (new Property ("DIGIT_MANUAL",						"103"));
	newChild->addChild (new Property ("DENY_NEW_CARD_ISSUED",				"104"));
	newChild->addChild (new Property ("DENY_ACCOUNT_CANCELED",				"105"));
	newChild->addChild (new Property ("PLEASE_CALL_ISSUER",					"107"));
	newChild->addChild (new Property ("INVALID_MERCHANT",					"109"));
	newChild->addChild (new Property ("INVALID_AMOUNT",						"110"));
	newChild->addChild (new Property ("INVALID_ACCOUNT",					"111"));
	newChild->addChild (new Property ("SERVICE_NOT_PERMITTED",				"115"));
	newChild->addChild (new Property ("NO_RECORD_FOR_CARD",					"118"));
	newChild->addChild (new Property ("INVALID_CID",						"122"));
	newChild->addChild (new Property ("INVALID_EFFECTIVE_DATE",				"125"));
	newChild->addChild (new Property ("FORMAT_ERROR",						"181"));
	newChild->addChild (new Property ("PLEASE_WAIT",						"182"));
	newChild->addChild (new Property ("INVALID_CURRENCY_CODE",				"183"));
	newChild->addChild (new Property ("DENY_PICK_UP_CARD",					"200"));
	newChild->addChild (new Property ("REVERSAL_ACCEPTED",					"400"));
	newChild->addChild (new Property ("CARD_ISSUER_TIMEOUT",				"911"));
	newChild->addChild (new Property ("CARD_ISSUER_UNAVAILABLE",			"212"));
	newChild->addChild (new Property ("PPN_EXPIRED",						"940"));
	newChild->addChild (new Property ("PPN_INVALID",						"941"));
	newChild->addChild (new Property ("PPN_AUTH_LIMIT_EXCEEDED",			"942"));
	newChild->addChild (new Property ("PPN_AMOUNT_LIMIT_EXCEEDED",			"943"));
	newChild->addChild (new Property ("PPN_PPN_CANCELED",					"944"));
	newChild->addChild (new Property ("PPN_INVALID_EXPIRATION_DATE",		"945"));
	newChild->addChild (new Property ("PPN_PLEASE_CALL_CHANGED_TO_DENY",	"946"));
	newChild->addChild (new Property ("PPN_TIMEOUT",						"947"));

	return newChild;
}

// This enumeration defines the Merchant ID Codes used in ISO8583 Messages.
Property *DefaultManager::bootstrapMerchantIDCodes (void)
{
	Property *newChild = NULL;

	newChild = new Property ("MerchantIDCodes");
	newChild->addChild (new Property ("AMEX_SE",		"0"));
	newChild->addChild (new Property ("AIRLINE_CODE",	"1"));
	newChild->addChild (new Property ("NCR_NUMBER",		"2"));
	newChild->addChild (new Property ("IATA_AGENT_ID",	"3"));	

	return newChild;
}

// This enumeration defines the Card Type Codes used in ISO8583 Messages.
Property *DefaultManager::bootstrapCardTypeCodes (void)
{
	Property *newChild = NULL;

	newChild = new Property ("CardTypeCodes");
	newChild->addChild (new Property ("ISO_AMEX",		"0"));
	newChild->addChild (new Property ("ISO_VISA",		"1"));
	newChild->addChild (new Property ("ISO_MASTERCARD",	"2"));
	newChild->addChild (new Property ("ISO_CARD_OTHER",	"3"));	

	return newChild;
}

// This enumeration defines the Additional Response Data Type Codes used in ISO8583 Messages.
Property *DefaultManager::bootstrapAddRespDataCodeTypes (void)
{
	Property *newChild = NULL;

	newChild = new Property ("AddRespDataCodes");
	newChild->addChild (new Property ("ADDRESS_AND_ZIP_CORRECT",		"0"));
	newChild->addChild (new Property ("ADDRESS_AND_ZIP_INCORRECT",		"1"));
	newChild->addChild (new Property ("ADDRESS_CORRECT",				"2"));
	newChild->addChild (new Property ("ZIP_CORRECT",					"3"));	
	newChild->addChild (new Property ("INFORMATION_UNAVAIL",			"4"));	
	newChild->addChild (new Property ("ADDRESS_VERIF_SUBSCR_VALID",		"5"));	
	newChild->addChild (new Property ("SYSTEM_UNAVAIL",					"6"));	

	return newChild;
}


// This enumeration defines the Bit positions 1 to 64
Property *DefaultManager::bootstrapFields (void)
{
	Property *newChild = NULL;
	char name[128+1] = "";
	char value[512+1] = "";

	newChild = new Property ("Fields");

	int bp = 0;
	for (bp = 1; bp < (64+1); bp++)
	{
	   sprintf (name, "BP%03d", bp);
	   sprintf (value, "%d", bp);

	   newChild->addChild (new Property (name,  value));
	}

	return newChild;
}

Property *DefaultManager::bootstrapFieldText (void)
{
	Property *newChild = NULL;

	newChild = new Property ("FieldText");

	newChild->addChild (new Property ("BP001", "Internal Use"));
	newChild->addChild (new Property ("BP002", "Primary Account Number"));
	newChild->addChild (new Property ("BP003", "Processing Code"));
	newChild->addChild (new Property ("BP004", "Transaction Amount"));
	newChild->addChild (new Property ("BP005", "Reconciliation Amount"));
	newChild->addChild (new Property ("BP006", "Cardholder Billing Amount"));
	newChild->addChild (new Property ("BP007", "Transmission Date and Time"));
	newChild->addChild (new Property ("BP008", "Cardholder Billing Fee Amount"));
	newChild->addChild (new Property ("BP009", "Reconciliation Conversion Rate"));
	newChild->addChild (new Property ("BP010", "Cardholder Billing Conversion Rate"));
	newChild->addChild (new Property ("BP011", "Systems Trace Audit Number"));
	newChild->addChild (new Property ("BP012", "Local Transmission Date and Time"));
	newChild->addChild (new Property ("BP013", "Card Effective Date"));
	newChild->addChild (new Property ("BP014", "Card Expiration Date"));
	newChild->addChild (new Property ("BP015", "Settlement Date"));
	newChild->addChild (new Property ("BP016", "Conversion Date"));
	newChild->addChild (new Property ("BP017", "Capture Date"));
	newChild->addChild (new Property ("BP018", "Merchant Type"));
	newChild->addChild (new Property ("BP019", "Acquiring Institution Country Code"));
	newChild->addChild (new Property ("BP020", "Primary Acct Number Country Code"));
	newChild->addChild (new Property ("BP021", "Forwarding Institution Country Code"));
	newChild->addChild (new Property ("BP022", "Point of Service Data"));
	newChild->addChild (new Property ("BP023", "Card sequence Number"));
	newChild->addChild (new Property ("BP024", "Function Code"));
	newChild->addChild (new Property ("BP025", "Message Reason Code"));
	newChild->addChild (new Property ("BP026", "Card Acceptior Business Code"));
	newChild->addChild (new Property ("BP027", "Approval Code Length"));
	newChild->addChild (new Property ("BP028", "Reconciliation Date"));
	newChild->addChild (new Property ("BP029", "Reconciliation Indicator"));
	newChild->addChild (new Property ("BP030", "Original Amounts"));
	newChild->addChild (new Property ("BP031", "Aquirer Reference Data"));
	newChild->addChild (new Property ("BP032", "Acquiring Institution Identification Code"));
	newChild->addChild (new Property ("BP033", "Forwarding Institution Identification Code"));
	newChild->addChild (new Property ("BP034", "Primary Account No Extended"));
	newChild->addChild (new Property ("BP035", "Track 2 Data"));
	newChild->addChild (new Property ("BP036", "Track 3 Data"));
	newChild->addChild (new Property ("BP037", "Retrieval Reference Number"));
	newChild->addChild (new Property ("BP038", "Approval Code"));
	newChild->addChild (new Property ("BP039", "Action Code"));
	newChild->addChild (new Property ("BP040", "Service Code"));
	newChild->addChild (new Property ("BP041", "Card Acceptor Terminal Identification"));
	newChild->addChild (new Property ("BP042", "Card Acceptor Identification Code"));
	newChild->addChild (new Property ("BP043", "Card Acceptor Name/Location"));
	newChild->addChild (new Property ("BP044", "Additional Reaponse Data"));
	newChild->addChild (new Property ("BP045", "Track 1 Data"));
	newChild->addChild (new Property ("BP046", "Amounts Fees"));
	newChild->addChild (new Property ("BP047", "Addtional data - National"));
	newChild->addChild (new Property ("BP048", "Addtional data - Private"));
	newChild->addChild (new Property ("BP049", "Transaction Currency Code"));
	newChild->addChild (new Property ("BP050", "Reconciliation Currency Code"));
	newChild->addChild (new Property ("BP051", "Cardholder Billing Currency Code"));
	newChild->addChild (new Property ("BP052", "Personal Identification Number - PIN"));
	newChild->addChild (new Property ("BP053", "Security Related Control Information"));
	newChild->addChild (new Property ("BP054", "Additional Amount"));
	newChild->addChild (new Property ("BP055", "IC card data"));
	newChild->addChild (new Property ("BP056", "Original Data"));
	newChild->addChild (new Property ("BP057", "Authorization Life Cycle Code"));
	newChild->addChild (new Property ("BP058", "Original Data"));
	newChild->addChild (new Property ("BP059", "Transport Data"));
	newChild->addChild (new Property ("BP060", "National Use Data"));
	newChild->addChild (new Property ("BP061", "National Use Data"));
	newChild->addChild (new Property ("BP062", "Private Use Data"));
	newChild->addChild (new Property ("BP063", "Private Data"));
	newChild->addChild (new Property ("BP064", "Message Authentication Code"));

	return newChild;
}

void DefaultManager::getCode (char *nameSpace, char *collection, char *code)
{
	char *codeName = NULL;
	char *codeValue = NULL;

	codeValue = getDefaultByName (nameSpace, collection, code);

	if (codeValue)
	{
	   cout << "*** " << collection << " *** " << endl;

	   cout << code << " codeValue->" << codeValue << "<" << endl;
	
	   codeName = getDefaultByValue (nameSpace, collection, codeValue);

	   if (codeName)
	      cout << codeValue << " codeName->" << codeName << "<" << endl;
	}

	cout << endl;

	return;
}

char *DefaultManager::getDefaultByName (char *nameSpace, char *collection, char *varName)
{
	Property *selectedNameSpace = NULL;
	Property *selectedVarList = NULL;
	Property *selectedVar = NULL;

	selectedNameSpace = selectVarList (m_defaults, nameSpace);
	
	if (selectedNameSpace)
	{
	   selectedVarList = selectVarList (selectedNameSpace, collection);

	   if (selectedVarList)
	   {
	      selectedVar = selectVarByName (selectedVarList, varName);

	      if (selectedVar)
		  {
		     return selectedVar->getValue ();
		  }
	   }
	}

	return NULL;
}

char *DefaultManager::getDefaultByValue (char *nameSpace, char *collection, char *varValue)
{
	Property *selectedNameSpace = NULL;
	Property *selectedVarList = NULL;
	Property *selectedVar = NULL;

	selectedNameSpace = selectVarList (m_defaults, nameSpace);
	
	if (selectedNameSpace)
	{
	   selectedVarList = selectVarList (selectedNameSpace, collection);

	   if (selectedVarList)
	   {
	      selectedVar = selectVarByValue (selectedVarList, varValue);

	      if (selectedVar)
		  {
		     return selectedVar->getName ();
		  }
	   }
	}
	
	return NULL;
}

Property *DefaultManager::selectVarList (Property *first, char *listName)
{
	int i = 0;
	Property *newChild = NULL;
	Property *varList = NULL;
	Property *defaults = NULL;

	if (gDebug)
	   cout << "DefaultManager::selectVarList() - listName=" << listName << "." << endl;

	// loop through global default area.
	// search for matching list with name listName
	if (first != NULL)
	   defaults = first;
	else
	   defaults = m_defaults;

	// for each list
/*
	for (i = 0; i < (globals->childrenCount); i++)
	{
	   // get a list (List).
	   varList = &globals->children[i];

	   if (strcmp (varList->getName (), listName) == 0)
	   {
	      // found a match so return pointing to it.
	      if (gDebug)
		     cout << "List.Name: " << listName << " FOUND!" << endl;
		  
	      return varList;
	   }
	}
*/

    // no match found so return NULL.
    if (gDebug)
	   cout << "List.Name: " << listName << " ***NOT*** FOUND!" << endl;
	
	return NULL;
}

Property *DefaultManager::selectVarByName (Property *varList, char *varName)
{
	int j = 0;
	Property *var = NULL;
	Property *globals = NULL;
	Property *defaults = NULL;

	if (gDebug)
	   cout << "DefaultManager::selectVarByName() - varName=" << varName << "." << endl;

	// loop through global default area.
	// search for matching list with name listName
	defaults = m_defaults;

//	globals = &defaults->globals;

/*
	if (varList != NULL)
	{
	   // for each possible child.
	   for (j = 0; j < (varList->childrenCount); j++)
	   {
	      // get a child (Code).
	      var = &varList->children[j];

		  if (strcmp (var->getName (), varName) == 0)
		  {
		     // setup the var element name attribute.
	         if (gDebug)
			    cout << "Code.Name: " << var->getName () << " Code.Value: >" << var->getValue () << "<" << endl;
			 
			 return var;
		  }
	   }
	}
*/

    // no match found so return NULL.
    if (gDebug)
	   cout << "Code.Name: " << varName << " ***NOT*** FOUND!" << endl;

	return NULL;
}

Property *DefaultManager::selectVarByValue (Property *varList, char *varValue)
{
	int j = 0;
	Property *var = NULL;
	Property *globals = NULL;
	Property *defaults = NULL;

	if (gDebug)
	   cout << "DefaultManager::selectVarByValue() - varValue=" << varValue << "." << endl;

	// loop through global default area.
	// search for matching list with name listName
	defaults = m_defaults;

//	globals = &defaults->globals;

/*
	if (varList != NULL)
	{
	   // for each possible child.
	   for (j = 0; j < (varList->childrenCount); j++)
	   {
	      // get a child (Code).
	      var = &varList->children[j];

		  if (strcmp (var->getValue (), varValue) == 0)
		  {
		     // setup the var element name attribute.
	         if (gDebug)
		        cout << "Code.Name: " << var->getName () << " Code.Value: >" << var->getValue () << "<" << endl;
			 
			 return var;
		  }
	   }
	}
*/

    // no match found so return NULL.
    if (gDebug)
	   cout << "Code.Value: " << varValue << " ***NOT*** FOUND!" << endl;

	return NULL;
}


/*

Defaults
	Globals numberOfChildren=3
		List numberOfChildren=4
			Code name=name1, value=15
			Code name=name2, value=01
			Code name=name3, value=99
			Code name=name4, value=10
		List
			...
		List
			...

*/

