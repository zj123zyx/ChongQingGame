#ifndef _TRANSACTIONA_H_
#define _TRANSACTIONA_H_

#include "AbstractTransaction.h"
/*
 **用户登录接口
 */

class Transaction1001 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _userName, UserName);
    WRITEONLY_PASS_BY_REF(string, _userPwd, UserPwd);
    WRITEONLY_PASS_BY_REF(string, _verifyNumber, VerifyNumber);
    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _bigMoney, BigMoney);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _isConsummate, IsConsummate);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _userId, UserId);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balance, Balance);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _freeze, Freeze);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _accountId, AccountId);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _scale, Scale);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _lotteryPoint, LotteryPoint);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _giftBalance, GiftBalance);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _giftLotteryPoint, GiftLotteryPoint);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _totalSale, TotalSale);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _totalPrize, TotalPrize);
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _sessionId, SessionId);
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif
