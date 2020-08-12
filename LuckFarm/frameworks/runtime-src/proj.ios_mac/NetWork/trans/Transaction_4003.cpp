#include "Transaction_4003.h"

string Transaction4003::buildXmlBody(string sb)
{	
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<salesType>" + this->_salesType + "</salesType>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction4003::getType()
{
	return "4003";
}

void Transaction4003::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_message  = node->value();
    

}

void Transaction4003::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}
