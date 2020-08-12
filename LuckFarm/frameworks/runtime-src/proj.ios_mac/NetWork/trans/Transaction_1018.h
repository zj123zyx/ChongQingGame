#ifndef _TRANSACTION_1018_H_
#define _TRANSACTION_1018_H_

#include "AbstractTransaction.h"

/*
 **获取银行信息
 */

class Transaction1018 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 用户账号
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 密码
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _bankId, BankId);//银行ID
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _bankName, BankName);//银行名称
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _allBanks, AllBanks);//银行列表
    
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