//
//  Transaction_3008.cpp
//  sczl
//
//  Created by Leo on 15/6/29.
//
//

#include "Transaction_3008.h"

string Transaction3008::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<gameId>" + this->_gameId + "</gameId>");
    sb.append("<ticketId>" + this->_ticketId + "</ticketId>");
    sb.append("<gameVersion>" + this->_gameVersion + "</gameVersion>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction3008::getType()
{
    return "3008";
}

void Transaction3008::handleData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_balance = node->value();
    
    node = node->next_sibling();
    this->_lotteryPoint = node->value();
    
    node = node->next_sibling();
    this->_awardLevel = node->value();
    
    node = node->next_sibling();
    this->_winLotteryPoint = node->value();
    
    node = node->next_sibling();
    this->_winAmount = node->value();
    
}

void Transaction3008::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}