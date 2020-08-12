#include "Transaction_1030.h"

string Transaction1030::buildXmlBody(string sb)
{	
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<phone>" + this->_phone + "</phone>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1030::getType()
{
	return "1030";
}

void Transaction1030::handleData(xml_node<>* resultData)
{

}

void Transaction1030::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}