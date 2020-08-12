//
//  JniLoadGame.h
//  gameTest
//
//  Created by Leo on 15/9/10.
//
//

#ifndef __gameTest__JniLoadGame__
#define __gameTest__JniLoadGame__

#include "cocos2d.h"
#include "editor-support/spine/Json.h"

using namespace cocos2d;

static void jniLoadGame(std::string url)
{
    std::string strJson = url;
    log("csj传入游戏的参数:%s", strJson.c_str());
    
    if(strJson!="")
    {
        Json *jsonRoot = Json_create(strJson.c_str());
        Json *jsonAccountId = Json_getItem(jsonRoot, "accountId");
        Json *jsonSessionID = Json_getItem(jsonRoot, "sessionId");
        Json *jsonUserId = Json_getItem(jsonRoot, "userId");
        Json *jsonBalance = Json_getItem(jsonRoot, "balance");
        Json *jsonLotteryPoint = Json_getItem(jsonRoot, "lotteryPoint");
        Json *jsonFreeze = Json_getItem(jsonRoot, "freeze");
        Json *jsonIsConsummate = Json_getItem(jsonRoot, "isConsummate");
        
        Json *jsonClientType = Json_getItem(jsonRoot, "clientType");
        Json *jsonHallVersion = Json_getItem(jsonRoot, "hallVersion");
        
        Json *jsonUrl = Json_getItem(jsonRoot, "url");

        std::string accountId = std::string(jsonAccountId->valueString);
        std::string sessionId = std::string(jsonSessionID->valueString);
        std::string userId = std::string(jsonUserId->valueString);
        std::string lotteryPoint = std::string(jsonLotteryPoint->valueString);
        std::string balance = std::string(jsonBalance->valueString);
        std::string freeze = std::string(jsonFreeze->valueString);
        std::string isConsummate = std::string(jsonIsConsummate->valueString);
        
        std::string clientType = std::string(jsonClientType->valueString);
        std::string hallVersion = std::string(jsonHallVersion->valueString);
        
        std::string url = std::string(jsonUrl->valueString);
        
        UserDefault::getInstance()->setStringForKey("accountId",accountId);
        UserDefault::getInstance()->setStringForKey("sessionId",sessionId);
        UserDefault::getInstance()->setStringForKey("userId",userId);
        UserDefault::getInstance()->setStringForKey("balance",balance);
        UserDefault::getInstance()->setStringForKey("lotteryPoint",lotteryPoint);
        UserDefault::getInstance()->setStringForKey("freeze",freeze);
        UserDefault::getInstance()->setStringForKey("isConsummate",isConsummate);
        
        UserDefault::getInstance()->setStringForKey("clientType",clientType);
        UserDefault::getInstance()->setStringForKey("hallVersion",hallVersion);
        
        UserDefault::getInstance()->setStringForKey("postUrl",url);

        log("csj-222222222222222");


    }
    

}

#endif /* defined(__gameTest__JniLoadGame__) */
