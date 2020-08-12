//
//  Transaction_1036.cpp
//  HongBoECai
//
//  Created by Administrator on 16/10/19.
//
//

#include "Transaction_1036.h"

string Transaction1036::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<id>"+this->_emailId+"</id>");
    
    sb.append("<userType>A</userType>");
    
    return sb;
}

string Transaction1036::getType()
{
    return "1036";
}

void Transaction1036::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_giftAmount = node->value();
    
    node = node->next_sibling();
    this->_balance = node->value();
    
    node = node->next_sibling();
    this->_giftBalance = node->value();
}

void Transaction1036::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}
