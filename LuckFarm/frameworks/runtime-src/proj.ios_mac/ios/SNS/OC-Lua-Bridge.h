//
//  OC-Lua-Bridge.h
//  HongBoECai
//
//  Created by Administrator on 16/8/4.
//
//

#include "cocos2d.h"

class OCBridge {
    
public:
    static void gotoLoginVC();
    
    static void gotoRegisterVC();
    
    static void openLLPayForPayWith(const char *orderinfo);
    
    static void gotoQQLogin();
    
    static void gotoWeiXinLogin();
    
    static void getTokenFromLuaRequestWithCode(const char* code);
    
    static const char* stringToUtf8(const char *str);
    
    static const char* utf8ToString(const char *str);
    
    static void setAliasWithAccountId(const char *str);
    
    static void shareWeChatFriend();
    //    std::string name,std::string url,std::string andThumbImage, cocos2d::Image image
    static void shareWeChatFriendQuan();
    
    static void shareQQFriend();
    

    
};
