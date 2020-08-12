//
//  Transaction_2013.h
//  gameTest
//
//  Created by Leo on 15/8/13.
//
//

#ifndef __gameTest__Transaction_2013__
#define __gameTest__Transaction_2013__

#include "AbstractTransaction.h"

class Transaction2013 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _gameId, GameId);
    WRITEONLY_PASS_BY_REF(string, _amount, Amount);
    WRITEONLY_PASS_BY_REF(string, _gameVersion, GameVersion);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balance, Balance);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _lotteryPoint, LotteryPoint);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _ticketId, TicketId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _ticketContent, TicketContent);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _securityCode, SecurityCode);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _totalMessage, TotalMessage);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _wastageMessage, WastageMessage);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _gameMessage, GameMessage);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);
    
    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* defined(__gameTest__Transaction2013__) */
