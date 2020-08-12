#include "Transaction_1011.h"

string Transaction1011::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1011::getType()
{
	return "1011";
}

void Transaction1011::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_userName = node->value();
    
    node = node->next_sibling();
    this->_userId = node->value();
    
    node = node->next_sibling();
    this->_idNumber = node->value();
    
    node = node->next_sibling();
    this->_phoneNumber = node->value();
    
    node = node->next_sibling();
    this->_cardNumber = node->value();
    
    node = node->next_sibling();
    this->_bank = node->value();
}

void Transaction1011::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}