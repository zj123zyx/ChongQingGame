//
//  Transaction_1010.cpp
//  HongBoECai
//
//  Created by Administrator on 16/9/9.
//
//

#include "Transaction_1010.h"

string Transaction1010::buildXmlBody(string sb)
{
    sb.append("<accountId>"+this->_accountId+"</accountId>");
    sb.append("<sessionId>"+this->_sessionId+"</sessionId>");
    
    sb.append("<orderId>"+this->_sendOrderId+"</orderId>");
    sb.append("<statusId>"+this->_statusId+"</statusId>");
    sb.append("<gameId>"+this->_sendGameId+"</gameId>");
    sb.append("<startTime>"+this->_startTime+"</startTime>");
    sb.append("<endTime>"+this->_endTime+"</endTime>");
    sb.append("<page>");
    sb.append("<pageCount>"+this->_pageCount+"</pageCount>");
    sb.append("<pageSize>"+this->_pageSize+"</pageSize>");
    sb.append("</page>");
    
    sb.append("<userType>A</userType>");
    
    return sb;
}

string Transaction1010::getType()
{
    return "1010";
}

void Transaction1010::handleData(xml_node<>* resultData)
{
    auto nodeLotteryOeder = resultData->first_node();//LotteryOeder<>
    if(nodeLotteryOeder == NULL){
        return;
    }
    auto nodeItem  = nodeLotteryOeder->first_node();//item<>
    if(nodeItem == NULL){
        return;
    }
    
    for (int i=0; nodeItem != NULL;i++) {
        auto nodeOrderId = nodeItem->first_node();//_orderId
        this->_orderId = nodeOrderId->value();
        tableMeg = tableMeg + "orderId==" + this->_orderId + ",";
        
        auto nodeGameId = nodeOrderId->next_sibling();//_gameId
        this->_gameId = nodeGameId->value();
        tableMeg = tableMeg + "gameId==" + this->_gameId+ ",";
        
        auto nodeGameIssue = nodeGameId->next_sibling();//_gameIssue
        this->_gameIssue = nodeGameIssue->value();
        tableMeg = tableMeg + "gameIssue==" + this->_gameIssue+ ",";
        
        auto nodeCreateTime = nodeGameIssue->next_sibling();//_createTime
        this->_createTime = nodeCreateTime->value();
        tableMeg = tableMeg + "createTime==" + this->_createTime+ ",";
        
        auto nodeTicketNum = nodeCreateTime->next_sibling();//_ticketNum
        this->_ticketNum = nodeTicketNum->value();
        tableMeg = tableMeg + "ticketNum==" + this->_ticketNum+ ",";
        
        auto nodeTicketMoney = nodeTicketNum->next_sibling();//_ticketMoney
        this->_ticketMoney = nodeTicketMoney->value();
        tableMeg = tableMeg + "ticketMoney==" + this->_ticketMoney+ ",";
        
        auto nodeStatus = nodeTicketMoney->next_sibling();//_status
        this->_status = nodeStatus->value();
        tableMeg = tableMeg + "status==" + this->_status+ ",";
        
        auto nodeWinMoney = nodeStatus->next_sibling();//_winMoney
        this->_winMoney = nodeWinMoney->value();
        tableMeg = tableMeg + "winMoney==" + this->_winMoney+ ",";
        
        auto nodePrizeTime = nodeWinMoney->next_sibling();//_prizeTime
        this->_prizeTime = nodePrizeTime->value();
        tableMeg = tableMeg + "prizeTime==" + this->_prizeTime+ ",";
        
        auto nodePrizeMoney = nodePrizeTime->next_sibling();//_prizeMoney
        this->_prizeMoney = nodePrizeMoney->value();
        tableMeg = tableMeg + "prizeMoney==" + this->_prizeMoney+ ",";
        
        auto nodeWinCoin = nodePrizeMoney->next_sibling();//_winCoin
        this->_winCoin = nodeWinCoin->value();
        tableMeg = tableMeg + "winCoins==" + this->_winCoin+ ",";
        
        auto nodeTicketCoins = nodeWinCoin->next_sibling();//_ticketCoins
        this->_ticketCoins = nodeTicketCoins->value();
        tableMeg = tableMeg + "ticketCoins==" + this->_ticketCoins+ ",";
        
        auto nodeErrorMsg = nodeTicketCoins->next_sibling();//_errorMsg
        this->_errorMsg = nodeErrorMsg->value();
        tableMeg = tableMeg + "errorMsg==" + this->_errorMsg+ ",";
        
        tableMeg = tableMeg + ";";
        
        nodeItem = nodeItem->next_sibling();
    }
    this->_betsInfo = tableMeg;
}

void Transaction1010::handleVersionData(xml_node<>* resultData)
{
    auto node = resultData->first_node();
    this->_urlAddress = node->value();
}