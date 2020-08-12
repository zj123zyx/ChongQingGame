#ifndef _TRANSACTION_1003_H_
#define _TRANSACTION_1003_H_

#include "AbstractTransaction.h"

/*
 **用户注册接口
 */

class Transaction1003 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _accountId, AccountId);// 账户名
    WRITEONLY_PASS_BY_REF(string, _sessionId, SessionId);// 账户密码
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _balance , Balance );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _lotteryPoint , LotteryPoint );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _freezeMoney  , FreezeMoney );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _totalPrizeMoney  , TotalPrizeMoney );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _bigMoney , BigMoney );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _giftBalance , GiftBalance );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _giftLotteryPoint , GiftLotteryPoint );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _totalSale , TotalSale );
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _totalPrize , TotalPrize );
    
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _urlAddress, UrlAddress);

public:	
	string getType();

protected:
	void handleData(xml_node<>* resultData);
    
    void handleVersionData(xml_node<>* resultData);

	string buildXmlBody(string sb);
};

#endif
