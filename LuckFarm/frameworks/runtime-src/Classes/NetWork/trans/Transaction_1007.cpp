//
//  Transaction_1007.cpp
//  HongBoECai
//
//  Created by Administrator on 16/9/9.
//
//

#include "Transaction_1007.h"

string Transaction1007::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    sb.append("<tradeType>"+this->_tradeType+"</tradeType>");
    sb.append("<page>");
    sb.append("<pageCount>"+this->_pageCount+"</pageCount>");
    sb.append("<pageSize>"+this->_pageSize+"</pageSize>");
    sb.append("</page>");
    sb.append("<gameId>"+this->_gameId+"</gameId>");
    sb.append("<userType>A</userType>");
    
    return sb;
}

string Transaction1007::getType()
{
    return "1007";
}

void Transaction1007::handleData(xml_node<>* resultData)
{
    auto fundsDetail = resultData->first_node();//fundsSummary<>
    if(fundsDetail == NULL){
        return;
    }
    auto nodeItem  = fundsDetail->first_node();//item<>
    if(nodeItem == NULL){
        return;
    }
    
    for (int i=0; nodeItem != NULL;i++) {
        auto tradeTime = nodeItem->first_node();  //tradeTime
        this->_tradeTime = tradeTime->value();
        tableMeg = tableMeg + "tradeTime==" + this->_tradeTime + ",";
        
        auto tradeType = tradeTime->next_sibling();   //tradeType
        this->_tradeType2 = tradeType->value();
        tableMeg = tableMeg + "tradeType==" + this->_tradeType2+ ",";
        
        auto status = tradeType->next_sibling();//amount
        this->_status = status->value();
        tableMeg = tableMeg + "status==" + this->_status+ ",";
        
        auto orderId = status->next_sibling();//balance
        this->_orderId = orderId->value();
        tableMeg = tableMeg + "orderId==" + this->_orderId+ ",";
        
        auto type = orderId->next_sibling();//orderId
        this->_type = type->value();
        tableMeg = tableMeg + "type==" + this->_type+ ",";
        
        auto gameId = type->next_sibling();//gameId
        this->_gameId2 = gameId->value();
        tableMeg = tableMeg + "gameId==" + this->_gameId2+ ",";
        
        auto tradeGameCurrency = gameId->next_sibling();//gameId
        this->_tradeGameCurrency = tradeGameCurrency->value();
        tableMeg = tableMeg + "tradeGameCurrency==" + this->_tradeGameCurrency+ ",";
        
        auto balanceGameCurrency = tradeGameCurrency->next_sibling();//gameId
        this->_balanceGameCurrency = balanceGameCurrency->value();
        tableMeg = tableMeg + "balanceGameCurrency==" + this->_balanceGameCurrency+ ",";
        
        tableMeg = tableMeg + ";";
        nodeItem = nodeItem->next_sibling();
    }
    printf("=ddd=%s",tableMeg.c_str());
    this->_betsInfo = tableMeg;
}

void Transaction1007::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}
