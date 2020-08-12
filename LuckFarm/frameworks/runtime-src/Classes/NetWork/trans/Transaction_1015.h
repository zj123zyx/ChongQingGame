#ifndef _TRANSACTION_1015_H_
#define _TRANSACTION_1015_H_

#include "AbstractTransaction.h"

/*
 **
 */

class Transaction1015 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _areaRank, AreaRank);
    WRITEONLY_PASS_BY_REF(string, _areaParentId, AreaParentId);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _areaId, AreaId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _curAreaRank, CurAreaRank);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _areaName, AreaName);
//    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _areaCode, AreaCode);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _areaInfo, AreaInfo);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();
    string tableMeg = "";

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif