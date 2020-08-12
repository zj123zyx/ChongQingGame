//
//  Transaction_1035.cpp
//  HongBoECai
//
//  Created by Administrator on 16/10/19.
//
//

#include "Transaction_1035.h"

string Transaction1035::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<id>"+this->_emailId+"</id>");
    
    sb.append("<userType>A</userType>");
    
    return sb;
}

string Transaction1035::getType()
{
    return "1035";
}

void Transaction1035::handleData(xml_node<>* resultData)
{
    
}

void Transaction1035::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}
