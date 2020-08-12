#ifndef _TRANSACTION_1027_H_
#define _TRANSACTION_1027_H_

#include "AbstractTransaction.h"

/*
 **用户更新银行资料
 */

class Transaction1027 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);
    WRITEONLY_PASS_BY_REF(string, _bankId, BankId);// 银行编号
    WRITEONLY_PASS_BY_REF(string, _areaId, AreaId);// 区域代码
    WRITEONLY_PASS_BY_REF(string, _cardNumber, CardNumber);// 借记卡号码
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif