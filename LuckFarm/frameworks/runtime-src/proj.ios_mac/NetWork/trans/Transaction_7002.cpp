//
//  Transaction_7002.cpp
//  HongBoECai
//
//  Created by Administrator on 16/9/5.
//
//

#include "Transaction_7002.h"

string Transaction7002::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<ret_code>" + this->_ret_code + "</ret_code>");
    sb.append("<ret_msg>" + this->_ret_msg + "</ret_msg>");
    sb.append("<result_pay>" + this->_result_pay + "</result_pay>");
    sb.append("<oid_paybill>" + this->_oid_paybill + "</oid_paybill>");
    sb.append("<money_order>" + this->_money_order + "</money_order>");
    sb.append("<no_order>" + this->_no_order + "</no_order>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction7002::getType()
{
    return "7002";
}

void Transaction7002::handleData(xml_node<>* resultData)
{
    
}

void Transaction7002::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}
