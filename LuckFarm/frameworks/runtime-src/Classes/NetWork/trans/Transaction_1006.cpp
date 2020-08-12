#include "Transaction_1006.h"

string Transaction1006::buildXmlBody(string sb)
{	
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<bankAccount></bankAccount>");
    sb.append("<amount>" + this->_amount + "</amount>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1006::getType()
{
	return "1006";
}

void Transaction1006::handleData(xml_node<>* resultData)
{
    
}

void Transaction1006::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}