//
//  Transaction7001.cpp
//  HongBoECai
//
//  Created by Administrator on 16/10/14.
//
//

#include "Transaction_7001.h"

string Transaction7001::buildXmlBody(string sb)
{
    sb.append("<accountId>" + this->_accountId + "</accountId>");
    sb.append("<sessionId>" + this->_sessionId + "</sessionId>");
    sb.append("<amount>" + this->_amount + "</amount>");
    sb.append("<bankAccount>" + this->_bankAccount + "</bankAccount>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction7001::getType()
{
    return "7001";
}

void Transaction7001::handleData(xml_node<>* resultData)
{
    /*
     _orderId, OrderId);                  //订单Id
     _createTime, CreateTime);            //订单时间
     _userAccountId, UserAccountId);      //用户账号
     _oid_partner, Oid_partner);          //商户编号
     _sign_type, Sign_type);              //签名方式
     _buis_partner, Buis_partner);        //商户业务类型
     _notify_url, Notify_url);            //异步通知url
     _rsa_private_key, Rsa_private_key);  //商家私钥
     */
    auto node = resultData->first_node();
    this->_orderId = node->value();
    
    node = node->next_sibling();
    this->_createTime = node->value();
    
    node = node->next_sibling();
    this->_userAccountId = node->value();
    
    node = node->next_sibling();
    this->_oid_partner = node->value();
    
    node = node->next_sibling();
    this->_sign_type = node->value();
    
    node = node->next_sibling();
    this->_buis_partner = node->value();
    
    node = node->next_sibling();
    this->_notify_url = node->value();
    
    node = node->next_sibling();
    this->_rsa_private_key = node->value();
    
    node = node->next_sibling();
    this->_rsa_public_key = node->value();
    
    node = node->next_sibling();
    this->_registerTime = node->value();
    
    node = node->next_sibling();
    this->_phoneNumber = node->value();
}

void Transaction7001::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
    
}
