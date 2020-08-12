//
//  Transaction_1026.cpp
//  sczl
//
//  Created by Leo on 15/6/30.
//
//

#include "Transaction_1026.h"

string Transaction1026::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<toConvert>" + this->_toConvert + "</toConvert>");
    sb.append("<option>" + this->_option + "</option>");
    sb.append("<gameVersion>" + this->_gameVersion + "</gameVersion>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction1026::getType()
{
    return "1026";
}

void Transaction1026::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_lotteryPoint = node->value();
    
    node = node->next_sibling();
    this->_balance = node->value();
}

void Transaction1026::handleVersionData(xml_node<>* resultData)
{
    
}