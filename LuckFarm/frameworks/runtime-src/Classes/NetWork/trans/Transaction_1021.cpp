//
//  Transaction_1021.cpp
//  sczl
//
//  Created by Leo on 15/6/29.
//
//

#include "Transaction_1021.h"

string Transaction1021::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<ticketId>" + this->_ticketId + "</ticketId>");
    sb.append("<gameId>" + this->_gameId + "</gameId>");
    sb.append("<betCode>" + this->_betCode + "</betCode>");
    sb.append("<gameVersion>" + this->_gameVersion + "</gameVersion>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction1021::getType()
{
    return "1021";
}

void Transaction1021::handleData(xml_node<>* resultData)
{
    
}