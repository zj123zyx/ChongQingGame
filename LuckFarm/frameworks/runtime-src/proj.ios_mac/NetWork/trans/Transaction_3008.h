//
//  Transaction_3008.h
//  sczl
//
//  Created by Leo on 15/6/29.
//
//

#ifndef __sczl__Transaction_3008__
#define __sczl__Transaction_3008__

#include "AbstractTransaction.h"

class Transaction3008 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _gameId, GameId);
    WRITEONLY_PASS_BY_REF(string, _ticketId, TicketId);
    WRITEONLY_PASS_BY_REF(string, _gameVersion, GameVersion);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balance, Balance);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _lotteryPoint, LotteryPoint);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _awardLevel, AwardLevel);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _winLotteryPoint, WinLotteryPoint);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _winAmount, WinAmount);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* defined(__sczl__Transaction_3008__) */
