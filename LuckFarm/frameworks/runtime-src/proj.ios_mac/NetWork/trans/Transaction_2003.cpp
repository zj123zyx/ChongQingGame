//
//  Transaction_2003.cpp
//  gameTest
//
//  Created by Leo on 15/8/13.
//
//1）	乐透型即开票购买(钱)

#include "Transaction_2003.h"

string Transaction2003::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<gameId>" + this->_gameId + "</gameId>");
    sb.append("<amount>" + this->_amount + "</amount>");
    sb.append("<content>" + this->_getContent + "</content>");
    sb.append("<gameVersion>" + this->_gameVersion + "</gameVersion>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction2003::getType()
{
    return "2003";
}

void Transaction2003::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_balance = node->value();
    
    node = node->next_sibling();
    this->_lotteryPoint = node->value();
    
    node = node->next_sibling();
    this->_ticketId = node->value();
    
    node = node->next_sibling();
    this->_ticketContent = node->value();
    
    node = node->next_sibling();
    this->_securityCode = node->value();
    
    node = node->next_sibling();
    this->_totalMessage = node->value();
    
    node = node->next_sibling();
    this->_wastageMessage = node->value();
    
    node = node->next_sibling();
    this->_gameMessage = node->value();
    
}

void Transaction2003::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}