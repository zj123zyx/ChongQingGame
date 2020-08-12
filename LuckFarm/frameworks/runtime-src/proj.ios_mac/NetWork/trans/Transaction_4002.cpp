#include "Transaction_4002.h"

string Transaction4002::buildXmlBody(string sb)
{	
	sb.append("<accountId>" + this->_accountId + "</accountId>");
	sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<salesType>" + this->_salesType + "</salesType>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction4002::getType()
{
	return "4002";
}

void Transaction4002::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_giftAmount = node->value();
    node = node->next_sibling();
    this->_balance = node->value();
    node = node->next_sibling();
    this->_giftBalance = node->value();
    
}

void Transaction4002::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}
