//
//  Transaction7005.cpp
//  HongBoECai
//
//  Created by Administrator on 16/9/5.
//
//

#include "Transaction_7005.h"

string Transaction7005::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<openId>" + this->_openId + "</openId>");
    sb.append("<accessToken>" + this->_accessToken + "</accessToken>");
    sb.append("<platformName>" + this->_platformName + "</platformName>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction7005::getType()
{
    return "7005";
}

void Transaction7005::handleData(xml_node<>* resultData)
{
    
}

void Transaction7005::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}