#include "Transaction_1005.h"

string Transaction1005::buildXmlBody(string sb)
{	
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<amount>" + this->_amount + "</amount>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1005::getType()
{
	return "1005";
}

void Transaction1005::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_param = node->value();
    
}

void Transaction1005::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}