#include "Transaction_1027.h"

string Transaction1027::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<bankId>" + this->_bankId + "</bankId>");
	sb.append("<areaId>" + this->_areaId + "</areaId>");
    sb.append("<cardNumber>" + this->_cardNumber + "</cardNumber>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1027::getType()
{
	return "1027";
}

void Transaction1027::handleData(xml_node<>* resultData)
{
    
}

void Transaction1027::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}