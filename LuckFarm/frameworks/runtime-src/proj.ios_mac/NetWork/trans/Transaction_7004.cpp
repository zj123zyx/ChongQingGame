//
//  Transaction7004.cpp
//  HongBoECai
//
//  Created by Administrator on 16/9/2.
//
//

#include "Transaction_7004.h"

string Transaction7004::buildXmlBody(string sb)
{
    sb.append("<openId>" + this->_openId + "</openId>");
    sb.append("<accessToken>" + this->_accessToken + "</accessToken>");
    sb.append("<platformName>" + this->_platformName + "</platformName>");
    sb.append("<userType>A</userType>");
    return sb;
}

string Transaction7004::getType()
{
    return "7004";
}

void Transaction7004::handleData(xml_node<>* resultData)
{
    string responseCode = this->getResponseCode();
    if (responseCode == "700008") {
        auto node = resultData->first_node();
        this->_nickName = node->value();
        
        node = node->next_sibling();
        this->_figureUrl = node->value();
        
    }else{
        auto node = resultData->first_node();
        this->_bigMoney = node->value();
        
        node = node->next_sibling();
        this->_isConsummate = node->value();
        
        node = node->next_sibling();
        this->_userId = node->value();
        
        node = node->next_sibling();
        this->_balance = node->value();
        
        node = node->next_sibling();
        this->_freeze = node->value();
        
        node = node->next_sibling();
        this->_accountId = node->value();
        
        node = node->next_sibling();
        this->_scale = node->value();
        
        node = node->next_sibling();
        this->_lotteryPoint = node->value();
        
        node = node->next_sibling();
        this->_giftBalance = node->value();
        
        node = node->next_sibling();
        this->_giftLotteryPoint = node->value();
        
        node = node->next_sibling();
        this->_totalSale = node->value();
        
        node = node->next_sibling();
        this->_totalPrize = node->value();
        
        node = node->next_sibling();
        this->_sessionId = node->value();
    }
}

void Transaction7004::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}