//
//  Transaction7004.hpp
//  HongBoECai
//
//  Created by Administrator on 16/9/2.
//
//

#ifndef Transaction7004_hpp
#define Transaction7004_hpp

#include "AbstractTransaction.h"

/**
 * QQ ，微信联合登陆
 */
class Transaction7004 : public AbstractTransaction
{
    WRITEONLY_PASS_BY_REF(string, _openId, OpenId);
    WRITEONLY_PASS_BY_REF(string, _accessToken, AccessToken);
    WRITEONLY_PASS_BY_REF(string, _platformName, PlatformName);
    
    /**
     * 未绑定账号时返回
     */
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _nickName, NickName);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(string, _figureUrl, FigureUrl);
    
    /**
     * 已绑定账号，直接返回登录信息
     */
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

#endif /* Transaction7004_hpp */
