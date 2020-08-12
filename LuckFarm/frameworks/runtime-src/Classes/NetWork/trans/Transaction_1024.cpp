#include "Transaction_1024.h"

string Transaction1024::buildXmlBody(string sb)
{	
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1024::getType()
{
	return "1024";
}

void Transaction1024::handleData(xml_node<>* resultData)
{

}

void Transaction1024::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}