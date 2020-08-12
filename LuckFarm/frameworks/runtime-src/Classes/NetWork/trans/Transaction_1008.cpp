#include "Transaction_1008.h"

string Transaction1008::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
	sb.append("<password>" + this->_password + "</password>");
	sb.append("<idNumber>" + this->_idNumber + "</idNumber>");
    sb.append("<phone>" + this->_phone + "</phone>");
    sb.append("<name>" + this->_name + "</name>");
    sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1008::getType()
{
	return "1008";
}

void Transaction1008::handleData(xml_node<>* resultData)
{
    
}

void Transaction1008::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}