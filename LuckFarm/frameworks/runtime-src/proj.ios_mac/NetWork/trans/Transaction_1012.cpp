#include "Transaction_1012.h"

string Transaction1012::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
	sb.append("<userPwd>" + this->_userPwd + "</userPwd>");
    sb.append("<newUserPwd>" + this->_newUserPwd + "</newUserPwd>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1012::getType()
{
	return "1012";
}

void Transaction1012::handleData(xml_node<>* resultData)
{
    
}

void Transaction1012::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}