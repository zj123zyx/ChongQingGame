#include "Transaction_1020.h"

string Transaction1020::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
	sb.append("<memo>" + this->_memo + "</memo>");
	sb.append("<type>" + this->_adviceType + "</type>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1020::getType()
{
	return "1020";
}

void Transaction1020::handleData(xml_node<>* resultData)
{
    
}

void Transaction1020::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}