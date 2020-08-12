//
//  Transaction_1023.h
//  sczl
//
//  Created by Leo on 15/6/29.
//
//

#ifndef __sczl__Transaction_1023__
#define __sczl__Transaction_1023__

#include "AbstractTransaction.h"

class Transaction1023 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _gameId, GameId);
    WRITEONLY_PASS_BY_REF(string, _gameVersion, GameVersion);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _ticketId, TicketId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _winAmount, WinAmount);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _addGameId, AddGameId);
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

#endif /* defined(__sczl__Transaction_1023__) */