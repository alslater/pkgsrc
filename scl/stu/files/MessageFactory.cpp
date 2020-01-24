#include "MessageFactory.h"

#include "ClassFactory.h"

MessageFactory::MessageFactory() {}

	//Destructor
MessageFactory::~MessageFactory(){}

MessageFactory & ISO8583MessageFactory () 
{
	return ISO8583ClassFactory();
}
