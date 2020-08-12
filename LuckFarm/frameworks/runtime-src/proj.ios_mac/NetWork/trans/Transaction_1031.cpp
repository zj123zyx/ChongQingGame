#include "Transaction_1031.h"

string Transaction1031::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
	sb.append("<phone>" + this->_phone + "</phone>");
	sb.append("<userName>" + this->_userName + "</userName>");
    sb.append("<idNumber>" + this->_idNumber + "</idNumber>");
    sb.append("<userPwd>" + this->_userPwd + "</userPwd>");
	sb.append("<userType>A</userType>");
	return sb;
}

string Transaction1031::getType()
{
	return "1031";
}

void Transaction1031::handleData(xml_node<>* resultData)
{
    
}

void Transaction1031::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}