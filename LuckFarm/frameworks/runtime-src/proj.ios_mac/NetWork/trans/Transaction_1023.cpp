//
//  Transaction_1023.cpp
//  sczl
//
//  Created by Leo on 15/6/29.
//
//

#include "Transaction_1023.h"

string Transaction1023::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<gameId>" + this->_gameId + "</gameId>");
    sb.append("<gameVersion>" + this->_gameVersion + "</gameVersion>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction1023::getType()
{
    return "1023";
}

void Transaction1023::handleData(xml_node<>* resultData)
{    
    auto node = resultData->first_node();
    this->_ticketId = node->value();
    
    node = node->next_sibling();
    this->_winAmount = node->value();
    
    node = node->next_sibling();
    this->_addGameId = node->value();
    
    node = node->next_sibling();
    this->_ticketContent = node->value();
    
    node = node->next_sibling();
    this->_securityCode = node->value();
}

void Transaction1023::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    log("_urlAddress=%s", this->_urlAddress.c_str());
    
}
