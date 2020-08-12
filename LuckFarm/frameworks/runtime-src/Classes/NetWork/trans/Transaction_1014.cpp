#include "Transaction_1014.h"

string Transaction1014::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<oldPhone>"+this->_oldPhone+"</oldPhone>");
    sb.append("<newPhone>"+this->_newPhone+"</newPhone>");
    sb.append("<cardNumber>"+this->_cardNumber+"</cardNumber>");
    sb.append("<type>"+this->_type+"</type>");
    sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1014::getType()
{
	return "1014";
}

void Transaction1014::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_smsNum = node->value();
}

void Transaction1014::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}