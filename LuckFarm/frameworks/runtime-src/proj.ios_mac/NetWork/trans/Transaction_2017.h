//
//  Transaction_2017.h
//  gameTest
//
//  Created by Leo on 15/8/13.
//
//

#ifndef __gameTest__Transaction_2017__
#define __gameTest__Transaction_2017__

#include "AbstractTransaction.h"

class Transaction2017 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _gameId, GameId);
    WRITEONLY_PASS_BY_REF(string, _amount, Amount);
    WRITEONLY_PASS_BY_REF(string, _getCount, GetCount);
    WRITEONLY_PASS_BY_REF(string, _gameVersion, GameVersion);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balance, Balance);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _lotteryPoint, LotteryPoint);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _ticketId, TicketId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _winAmount, WinAmount);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _ticketContent, TicketContent);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _securityCode, SecurityCode);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* defined(__gameTest__Transaction_2007__) */
