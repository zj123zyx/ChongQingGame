//
//  Transaction_1010.hpp
//  HongBoECai
//
//  Created by Administrator on 16/9/9.
//
//

#ifndef Transaction_1007_hpp
#define Transaction_1007_hpp

#include "AbstractTransaction.h"

/*
 *投注记录查询
 */

class Transaction1007 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _tradeType, TradeType);
    WRITEONLY_PASS_BY_REF(string, _pageCount, PageCount);
    WRITEONLY_PASS_BY_REF(string, _pageSize, PageSize);
    WRITEONLY_PASS_BY_REF(string, _gameId, GameId);
    

    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _tradeTime, TradeTime);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _tradeType2, TradeType2);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _status, Status);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _orderId , OrderId );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _type , Type );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _gameId2 , GameId2 );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balance, Balance);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _tradeGameCurrency ,TradeGameCurrency );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balanceGameCurrency, BalanceGameCurrency);
    
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

#endif /* Transaction_1007_hpp */
