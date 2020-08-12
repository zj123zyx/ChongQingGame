//
//  Transaction_1010.hpp
//  HongBoECai
//
//  Created by Administrator on 16/9/9.
//
//

#ifndef Transaction_1010_hpp
#define Transaction_1010_hpp

#include "AbstractTransaction.h"

/*
 *投注记录查询
 */

class Transaction1010 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _sendOrderId, OrderId);
    WRITEONLY_PASS_BY_REF(string, _statusId , StatusId);//1-已购买，2-撤销，3-未中奖，4-返奖，5-待返奖,6-异常,7-领奖,8-取消
    WRITEONLY_PASS_BY_REF(string, _sendGameId, GameId);
    WRITEONLY_PASS_BY_REF(string, _startTime, StartTime);
    WRITEONLY_PASS_BY_REF(string, _endTime, EndTime);
    WRITEONLY_PASS_BY_REF(string, _pageCount, PageCount);
    WRITEONLY_PASS_BY_REF(string, _pageSize, PageSize);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _orderId, OrderId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _gameId, GameId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _gameIssue, GameIssue);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _createTime, CreateTime);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _ticketNum , TicketNum );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _ticketMoney , TicketMoney );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _status , Status );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _winMoney , WinMoney );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _prizeTime , PrizeTime );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _prizeMoney, PrizeMoney);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _errorMsg , ErrorMsg );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _winCoin , WinCoin );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _ticketCoins , TicketCoins );
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _betsInfo, BetsInfo);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
    string tableMeg = "";
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* Transaction_1010_hpp */
