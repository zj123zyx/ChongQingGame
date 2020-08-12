//
//  Transaction_1026.h
//  sczl
//
//  Created by Leo on 15/6/30.
//
//

#ifndef __sczl__Transaction_1026__
#define __sczl__Transaction_1026__

#include "AbstractTransaction.h"

class Transaction1026 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _toConvert, ToConvert);
    WRITEONLY_PASS_BY_REF(string, _option, Option);
    WRITEONLY_PASS_BY_REF(string, _gameVersion, GameVersion);
    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _lotteryPoint, LotteryPoint);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balance, Balance);

    
public:
    string getType();
    
protected:
    void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);
    
    string buildXmlBody(string sb);
};

#endif /* defined(__sczl__Transaction_1026__) */
