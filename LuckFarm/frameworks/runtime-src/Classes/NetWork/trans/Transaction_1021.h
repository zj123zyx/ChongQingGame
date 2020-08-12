//
//  Transaction_1021.h
//  sczl
//
//  Created by Leo on 15/6/29.
//
//用户投注保存

#ifndef __sczl__Transaction_1021__
#define __sczl__Transaction_1021__

#include "AbstractTransaction.h"

class Transaction1021 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _ticketId, TicketId);
    WRITEONLY_PASS_BY_REF(string, _gameId, GameId);
    WRITEONLY_PASS_BY_REF(string, _betCode, BetCode);
    WRITEONLY_PASS_BY_REF(string, _gameVersion, GameVersion);
    
    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* defined(__sczl__Transaction_1021__) */
