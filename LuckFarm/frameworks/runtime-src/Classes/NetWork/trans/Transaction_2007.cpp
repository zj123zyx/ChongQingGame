//
//  Transaction_2001.cpp
//  gameTest
//
//  Created by Leo on 15/8/13.
//
//

#include "Transaction_2007.h"

string Transaction2007::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<gameId>" + this->_gameId + "</gameId>");
    sb.append("<amount>" + this->_amount + "</amount>");
    sb.append("<getCount>" + this->_getCount + "</getCount>");
    sb.append("<gameVersion>" + this->_gameVersion + "</gameVersion>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction2007::getType()
{
    return "2007";
}

void Transaction2007::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_balance = node->value();
    
    node = node->next_sibling();
    this->_lotteryPoint = node->value();
    
    node = node->next_sibling();//ticketInfos
    node = node->first_node();//ticketInfo
    
    node = node->first_node();
    this->_ticketId = node->value();
    
    node = node->next_sibling();
    this->_ticketContent = node->value();
    
    node = node->next_sibling();
    this->_securityCode = node->value();
    
}

void Transaction2007::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}