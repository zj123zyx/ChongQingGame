//
//  Transaction_7006.cpp
//  HongBoECai
//
//  Created by Administrator on 16/9/5.
//
//

#include "Transaction_7006.h"

string Transaction7006::buildXmlBody(string sb)
{
    sb.append("<account>"+this->_account+"</account>");
    sb.append("<password>"+this->_password+"</password>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction7006::getType()
{
    return "7006";
}

void Transaction7006::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_openId = node->value();
    
    node = node->next_sibling();
    this->_accessToken = node->value();
}

void Transaction7006::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}