#include "Transaction_1013.h"

string Transaction1013::buildXmlBody(string sb)
{	
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<amount>" + this->_amount + "</amount>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1013::getType()
{
	return "1013";
}

void Transaction1013::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_uri = node->value();
}

void Transaction1013::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}