
#ifndef MSGMANAGER_H
#define MSGMANAGER_H

#define LOG_DEBUG	'D'
#define LOG_INFO	'I'
#define LOG_WARN	'W'
#define LOG_ERROR	'E'

typedef struct msgEntry
{
	int code;
	char level;
	char format[255+1];
} MSG_ENTRY;

class MsgManager
{
    private:
	   MSG_ENTRY *m_msgTable;
	   int m_msgTableCount;

    protected:

	   void init (void);
	   int getMsgIndex (int code);

    public:
	   MsgManager ();
	   MsgManager (MSG_ENTRY *aMsgTable, int count);

	   ~MsgManager ();

	   void setMsgTable (MSG_ENTRY *aMsgTable, int mableCount);

       char *getMsgFormat (int code, char *level);

	   void logMsg (int code, ...);

};

#endif

