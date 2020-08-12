//
//  Transaction_2005.cpp
//  sczl
//
//  Created by Leo on 15/6/29.
//
//2）	乐透型即开取正在进行游戏的票

#include "Transaction_2005.h"

string Transaction2005::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<gameId>" + this->_gameId + "</gameId>");
    sb.append("<gameVersion>" + this->_gameVersion + "</gameVersion>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction2005::getType()
{
    return "2005";
}

void Transaction2005::handleData(xml_node<>* resultData)
{    
//    auto node = resultData->first_node();
//    this->_ticketId = node->value();
//    
//    node = node->next_sibling();
//    this->_balance = node->value();
//    
//    node = node->next_sibling();
//    this->_lotteryPoint = node->value();
//    
//    node = node->next_sibling();
//    this->_addGameId = node->value();
//    
//    node = node->next_sibling();
//    this->_ticketContent = node->value();
//    
//    node = node->next_sibling();
//    this->_securityCode = node->value();
    
    auto node = resultData->first_node();
    this->_addGameId = node->value();
    
    node = node->next_sibling();
    this->_ticketContent = node->value();
    
    node = node->next_sibling();
    this->_ticketId = node->value();
    
    node = node->next_sibling();
    this->_balance = node->value();
    
    node = node->next_sibling();
    this->_lotteryPoint = node->value();
    
    node = node->next_sibling();
    this->_securityCode = node->value();
}

void Transaction2005::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    log("_urlAddress=%s", this->_urlAddress.c_str());
    
}
