#import "NetDataManager.h"
#include <sstream>
#include "cocos2d/LuaScriptHandlerMgr.h"
#include "CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "zconf.h"


#include "./util/md5.h"
#include "./util/Des.h"
#include "./util/GzipUtil.h"
#include "./helper/DataHelper.h"
#include "./trans/AbstractTransaction.h"

#include "./trans/TransactionA.h"
#include "./trans/Transaction_1002.h"
#include "./trans/Transaction_1003.h"
#include "./trans/Transaction_1004.h"
#include "./trans/Transaction_1005.h"
#include "./trans/Transaction_1006.h"
#include "./trans/Transaction_1007.h"
#include "./trans/Transaction_1008.h"
#include "./trans/Transaction_1010.h"
#include "./trans/Transaction_1011.h"
#include "./trans/Transaction_1012.h"
#include "./trans/Transaction_1013.h"
#include "./trans/Transaction_1014.h"
#include "./trans/Transaction_1015.h"
#include "./trans/Transaction_1018.h"
#include "./trans/Transaction_1020.h"
#include "./trans/Transaction_1023.h"
#include "./trans/Transaction_1024.h"
#include "./trans/Transaction_1026.h"
#include "./trans/Transaction_1027.h"
#include "./trans/Transaction_1030.h"
#include "./trans/Transaction_1031.h"
#include "./trans/Transaction_1032.h"
#include "./trans/Transaction_1034.h"
#include "./trans/Transaction_1035.h"
#include "./trans/Transaction_1036.h"

#include "./trans/Transaction_2002.h"
#include "./trans/Transaction_2003.h"
#include "./trans/Transaction_2005.h"
#include "./trans/Transaction_2007.h"
#include "./trans/Transaction_2008.h"
#include "./trans/Transaction_2013.h"
#include "./trans/Transaction_2014.h"
#include "./trans/Transaction_2017.h"

#include "./trans/Transaction_3005.h"
#include "./trans/Transaction_3008.h"
#include "./trans/Transaction_3015.h"
#include "./trans/Transaction_3016.h"

#include "./trans/Transaction_4002.h"
#include "./trans/Transaction_4003.h"

#include "./trans/Transaction_7001.h"
#include "./trans/Transaction_7004.h"
#include "./trans/Transaction_7005.h"
#include "./trans/Transaction_7006.h"

#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "OC-Lua-Bridge.h"
#endif
#include "AppLuaApi.h"

using namespace cocos2d;
using namespace network;

template <class T>
T toNumber(const char* val){
    if(!val)
    {
        return 0;
    }
    std::istringstream b(val);
    T num;
    b >> num;
    return num;
}

NetDataManager* NetDataManager::s_sharedNetDataManager = NULL;

NetDataManager* NetDataManager::sharedNetDataManager(void)
{
    if (!s_sharedNetDataManager)
    {
        s_sharedNetDataManager = new NetDataManager();
    }
    return s_sharedNetDataManager;
}

NetDataManager::~NetDataManager(void)
{
}

#if CC_LUA_ENGINE_ENABLED > 0
void NetDataManager::postListenerLua(cocos2d::LUA_FUNCTION listener)
{
    if (mListener)
    {
        cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->removeScriptHandler(mListener);
    }
    mListener = listener;
}
#endif

void NetDataManager::purgeSharedNetDataManager(void)
{
    if (s_sharedNetDataManager)
    {
        delete s_sharedNetDataManager;
        s_sharedNetDataManager = NULL;
    }
}

int NetDataManager::gzipToEnBase64(char *data, unsigned long size, char** en)
{
#define BUF_SIZE 65535
    
    uLong ndata = size;
    Bytef zdata[BUF_SIZE];
    uLong nzdata = BUF_SIZE;
    
    memset(zdata, 0, BUF_SIZE); // Ω´ ˝◊È¿Ôµƒ‘™Àÿ»´≤ø≥ı ºªØŒ™0, ƒ⁄»›÷√Œ™0£¨“≤æÕ ««Âø’
    //char* en;
    int enSize = 0;
    char* temp;
    if(GzipUtil::gzipCompress((Bytef *)data, ndata, zdata, &nzdata) == 0)
    {
        //log("PostHelper::enCompress=%s", zdata);//fprintf(stdout, "nzdata:%d %s/n", nzdata, zdata);
        //log("encompress.size = %d", nzdata);
        enSize = base64Encode(zdata, (unsigned int)nzdata, &temp);
        //free(zdata);  Õ∑≈Invalid address specified to RtlValidateHeap
        
        //log("EnBase64=%s", temp);
        *en = new char[enSize];
        memcpy(*en, temp, enSize);
        free(temp);
    }
    
    return enSize;
}

void NetDataManager::createTransaction(char* xmlData)
{
    string data = xmlData;
    xml_document<> doc;
    doc.parse<0>(const_cast<char *>(data.c_str()));//将数据写入xml_document
    
    xml_node<>* rootNode = doc.first_node();//获取根节点
    string xmlType = rootNode->value();
    
    if (strcmp(xmlType.c_str(), "1001") == 0 ){//build用户登录接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1001 *tranc1001 = new Transaction1001();

        nextNode = nextNode->next_sibling();
        string name = nextNode->value();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char *nameStr = OCBridge::utf8ToString(name.c_str());
            tranc1001->setUserName(nameStr);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            const char *nameStr = AppLuaApi::getInstance()->utf8ToString(name.c_str());
            tranc1001->setUserName(nameStr);
        #endif
        
        nextNode = nextNode->next_sibling();
        string userPwd = nextNode->value();
        tranc1001->setUserPwd(userPwd);
        
        nextNode = nextNode->next_sibling();
        string verifyNumber = nextNode->value();
        tranc1001->setVerifyNumber(verifyNumber);
        
        _transaction = tranc1001;
    }else if (strcmp(xmlType.c_str(), "1002") == 0 ){//build用户注册接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1002 *tranc1002 = new Transaction1002();

        nextNode = nextNode->next_sibling();
        string name = nextNode->value();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char *nameStr = OCBridge::utf8ToString(name.c_str());
            tranc1002->setName(nameStr);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            const char *nameStr = AppLuaApi::getInstance()->utf8ToString(name.c_str());
            tranc1002->setName(nameStr);
        #endif
        
        nextNode = nextNode->next_sibling();
        string userPwd = nextNode->value();
        tranc1002->setUserPwd(userPwd);
        
        nextNode = nextNode->next_sibling();
        string phone = nextNode->value();
        tranc1002->setPhone(phone);
        
        _transaction = tranc1002;
    }else if (strcmp(xmlType.c_str(), "1004") == 0 ){//build完善用户资料或账户变更接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1004 *tranc1004 = new Transaction1004();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1004->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1004->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string realName = nextNode->value();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char *realNameStr = OCBridge::utf8ToString(realName.c_str());
            tranc1004->setRealName(realNameStr);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            const char *realNameStr = AppLuaApi::getInstance()->utf8ToString(realName.c_str());
            tranc1004->setRealName(realNameStr);
        #endif
        
        nextNode = nextNode->next_sibling();
        string bankId = nextNode->value();
        tranc1004->setBankId(bankId);
        
        nextNode = nextNode->next_sibling();
        string areaId = nextNode->value();
        tranc1004->setAreaId(areaId);
        
        nextNode = nextNode->next_sibling();
        string idNumber = nextNode->value();
        tranc1004->setIdNumber(idNumber);
        
        nextNode = nextNode->next_sibling();
        string loginPhone = nextNode->value();
        tranc1004->setLoginPhone(loginPhone);
        
        //        nextNode = nextNode->next_sibling();
        //        string phone = nextNode->value();
        //        tranc1004->setPhone(phone);
        
        nextNode = nextNode->next_sibling();
        string cardNumber = nextNode->value();
        tranc1004->setCardNumber(cardNumber);
        
        _transaction = tranc1004;
    }else if (strcmp(xmlType.c_str(), "1005") == 0 ){//用户支付宝快捷支付充值
        xml_node<>* nextNode=rootNode;
        
        Transaction1005 *tranc1005 = new Transaction1005();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1005->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1005->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc1005->setAmount(amount);
        
        _transaction = tranc1005;
    }else if (strcmp(xmlType.c_str(), "1006") == 0 ){//用户提款
        xml_node<>* nextNode=rootNode;
        
        Transaction1006 *tranc1006 = new Transaction1006();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1006->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1006->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string bankAccount = nextNode->value();
        tranc1006->setBankAccount(bankAccount);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc1006->setAmount(amount);
        
        _transaction = tranc1006;
    }else if (strcmp(xmlType.c_str(), "1007") == 0){//build用户购彩订单查询接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1007 *tranc1007 = new Transaction1007();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1007->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1007->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string tradeType = nextNode->value();
        tranc1007->setTradeType(tradeType);
        
        nextNode = nextNode->next_sibling();
        string pageCount = nextNode->value();
        tranc1007->setPageCount(pageCount);
        
        nextNode = nextNode->next_sibling();
        string pageSize = nextNode->value();
        tranc1007->setPageSize(pageSize);
        
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc1007->setGameId(gameId);
        
        _transaction = tranc1007;
    }else if (strcmp(xmlType.c_str(), "1008") == 0 ){//build用户注销接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1008 *tranc1008 = new Transaction1008();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1008->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1008->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string password = nextNode->value();
        tranc1008->setPassword(password);
        
        nextNode = nextNode->next_sibling();
        string idNumber = nextNode->value();
        tranc1008->setIdNumber(idNumber);
        
        nextNode = nextNode->next_sibling();
        string phone = nextNode->value();
        tranc1008->setPhone(phone);
        
        nextNode = nextNode->next_sibling();
        string name = nextNode->value();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char *nameStr = OCBridge::utf8ToString(name.c_str());
            tranc1008->setName(nameStr);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            const char *nameStr = AppLuaApi::getInstance()->utf8ToString(name.c_str());
            tranc1008->setName(nameStr);
        #endif
        
        _transaction = tranc1008;
    }else if (strcmp(xmlType.c_str(), "1010") == 0){//build用户购彩订单查询接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1010 *tranc1010 = new Transaction1010();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1010->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1010->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string orderId = nextNode->value();
        tranc1010->setOrderId(orderId);
        
        nextNode = nextNode->next_sibling();
        string statusId = nextNode->value();
        tranc1010->setStatusId(statusId);
        
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc1010->setGameId(gameId);
        
        nextNode = nextNode->next_sibling();
        string startTime = nextNode->value();
        tranc1010->setStartTime(startTime);
        
        nextNode = nextNode->next_sibling();
        string endTime = nextNode->value();
        tranc1010->setEndTime(endTime);
        
        nextNode = nextNode->next_sibling();
        string pageCount = nextNode->value();
        tranc1010->setPageCount(pageCount);
        
        nextNode = nextNode->next_sibling();
        string pageSize = nextNode->value();
        tranc1010->setPageSize(pageSize);
        
        _transaction = tranc1010;
    }else if (strcmp(xmlType.c_str(), "1011") == 0 ){//build查询用户信息接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1011 *tranc1011 = new Transaction1011();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1011->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1011->setSessionId(sessionId);
        
        _transaction = tranc1011;
    }else if (strcmp(xmlType.c_str(), "1012") == 0 ){//build用户密码修改接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1012 *tranc1012 = new Transaction1012();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1012->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1012->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string userPwd = nextNode->value();
        tranc1012->setUserPwd(userPwd);
        nextNode = nextNode->next_sibling();
        string newUserPwd = nextNode->value();
        tranc1012->setNewUserPwd(newUserPwd);
        
        _transaction = tranc1012;
    }else if (strcmp(xmlType.c_str(), "1013") == 0 ){//用户支付宝WAP支付充值
        xml_node<>* nextNode=rootNode;
        
        Transaction1013 *tranc1013 = new Transaction1013();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1013->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1013->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc1013->setAmount(amount);
        
        _transaction = tranc1013;
    }else if (strcmp(xmlType.c_str(), "1014") == 0 ){//build短信验证的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1014 *tranc1014 = new Transaction1014();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1014->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1014->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string oldPhone = nextNode->value();
        tranc1014->setOldPhone(oldPhone);
        nextNode = nextNode->next_sibling();
        string newPhone = nextNode->value();
        tranc1014->setNewPhone(newPhone);
        nextNode = nextNode->next_sibling();
        string cardNumber = nextNode->value();
        tranc1014->setCardNumber(cardNumber);
        nextNode = nextNode->next_sibling();
        string type = nextNode->value();
        tranc1014->setType(type);
        
        _transaction = tranc1014;
    }else if (strcmp(xmlType.c_str(), "1015") == 0 ){//
        xml_node<>* nextNode=rootNode;
        
        Transaction1015 *tranc1015 = new Transaction1015();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1015->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1015->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string areaRank = nextNode->value();
        tranc1015->setAreaRank(areaRank);
        nextNode = nextNode->next_sibling();
        string areaParentId = nextNode->value();
        tranc1015->setAreaParentId(areaParentId);
        
        _transaction = tranc1015;
    }
    else if (strcmp(xmlType.c_str(), "1018") == 0 ){//build获取银行信息接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1018 *tranc1018 = new Transaction1018();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1018->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1018->setSessionId(sessionId);
        
        _transaction = tranc1018;
    }else if (strcmp(xmlType.c_str(), "1024") == 0 ){//build退出登录接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1024 *tranc1024 = new Transaction1024();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1024->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1024->setSessionId(sessionId);
        
        _transaction = tranc1024;
    }else if (strcmp(xmlType.c_str(), "1027") == 0 ){//build用户更新银行资料接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1027 *tranc1027 = new Transaction1027();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1027->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1027->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string bankId = nextNode->value();
        tranc1027->setBankId(bankId);
        
        nextNode = nextNode->next_sibling();
        string areaId = nextNode->value();
        tranc1027->setAreaId(areaId);
        
        nextNode = nextNode->next_sibling();
        string cardNumber = nextNode->value();
        tranc1027->setCardNumber(cardNumber);
        
        _transaction = tranc1027;
    }else if (strcmp(xmlType.c_str(), "1030") == 0 ){//build用户更新手机资料接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1030 *tranc1030 = new Transaction1030();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1030->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1030->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string phone = nextNode->value();
        tranc1030->setPhone(phone);
        
        _transaction = tranc1030;
    }else if (strcmp(xmlType.c_str(), "1031") == 0 ){//build用户忘记密码接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1031 *tranc1031 = new Transaction1031();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1031->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1031->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string phone = nextNode->value();
        tranc1031->setPhone(phone);
        
        nextNode = nextNode->next_sibling();
        string userName = nextNode->value();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char *userNameStr = OCBridge::utf8ToString(userName.c_str());
            tranc1031->setUserName(userNameStr);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            const char *userNameStr = AppLuaApi::getInstance()->utf8ToString(userName.c_str());
            tranc1031->setUserName(userNameStr);
        #endif
        
        nextNode = nextNode->next_sibling();
        string idNumber = nextNode->value();
        tranc1031->setIdNumber(idNumber);
        
        nextNode = nextNode->next_sibling();
        string userPwd = nextNode->value();
        tranc1031->setUserPwd(userPwd);
        
        _transaction = tranc1031;
    }else if (strcmp(xmlType.c_str(), "1020") == 0 ){//build用户反馈接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1020 *tranc1020 = new Transaction1020();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1020->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1020->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string memo = nextNode->value();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        const char *memoStr = OCBridge::utf8ToString(memo.c_str());
        tranc1020->setMemo(memoStr);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        const char *memoStr = AppLuaApi::getInstance()->utf8ToString(memo.c_str());
        tranc1020->setMemo(memoStr);
#endif
        
        nextNode = nextNode->next_sibling();
        string adviceType = nextNode->value();
        tranc1020->setAdviceType(adviceType);
    
        _transaction = tranc1020;
    }else if (strcmp(xmlType.c_str(), "1032") == 0 ){//build意见反馈查询接口的xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1032 *tranc1032 = new Transaction1032();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1032->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1032->setSessionId(sessionId);
        
        _transaction = tranc1032;
    }else if (strcmp(xmlType.c_str(), "1026") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction1026 *tranc1026 = new Transaction1026();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1026->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1026->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string toConvert = nextNode->value();
        tranc1026->setToConvert(toConvert);
        nextNode = nextNode->next_sibling();
        string option = nextNode->value();
        tranc1026->setOption(option);
        string version = nextNode->value();
        tranc1026->setGameVersion(version);
        
        _transaction = tranc1026;
    }else if (strcmp(xmlType.c_str(), "1034") == 0){//build个人信件查询xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1034 *tranc1034 = new Transaction1034();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1034->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1034->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string pageCount = nextNode->value();
        tranc1034->setPageCount(pageCount);
        
        nextNode = nextNode->next_sibling();
        string pageSize = nextNode->value();
        tranc1034->setPageSize(pageSize);
        
        _transaction = tranc1034;
    }else if (strcmp(xmlType.c_str(), "1035") == 0){//build个人信件删除xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1035 *tranc1035 = new Transaction1035();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1035->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1035->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string emailID = nextNode->value();
        tranc1035->setEmailId(emailID);
        
        _transaction = tranc1035;
    }else if (strcmp(xmlType.c_str(), "1036") == 0){//build领取类信件领取奖励xml
        xml_node<>* nextNode=rootNode;
        
        Transaction1036 *tranc1036 = new Transaction1036();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1036->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1036->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string emailID = nextNode->value();
        tranc1036->setEmailId(emailID);
        
        _transaction = tranc1036;
    }else if (strcmp(xmlType.c_str(), "2007") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction2007 *tranc2007 = new Transaction2007();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc2007->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc2007->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc2007->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc2007->setAmount(amount);
        nextNode = nextNode->next_sibling();
        string count = nextNode->value();
        tranc2007->setGetCount(count);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc2007->setGameVersion(version);
        
        _transaction = tranc2007;
    }else if (strcmp(xmlType.c_str(), "2002") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction2002 *tranc2002 = new Transaction2002();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc2002->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc2002->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc2002->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc2002->setAmount(amount);
        nextNode = nextNode->next_sibling();
        string count = nextNode->value();
        tranc2002->setGetCount(count);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc2002->setGameVersion(version);
        
        _transaction = tranc2002;
    }else if (strcmp(xmlType.c_str(), "1023") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction1023 *tranc1023 = new Transaction1023();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1023->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1023->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc1023->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc1023->setGameVersion(version);
        
        _transaction = tranc1023;
        
    }else if (strcmp(xmlType.c_str(), "3005") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction3005 *tranc3005 = new Transaction3005();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc3005->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc3005->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc3005->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string ticketId = nextNode->value();
        tranc3005->setTicketId(ticketId);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc3005->setGameVersion(version);
        
        _transaction = tranc3005;
    }else if (strcmp(xmlType.c_str(), "2017") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction2017 *tranc2017 = new Transaction2017();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc2017->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc2017->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc2017->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc2017->setAmount(amount);
        nextNode = nextNode->next_sibling();
        string count = nextNode->value();
        tranc2017->setGetCount(count);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc2017->setGameVersion(version);
        
        _transaction = tranc2017;
    }else if (strcmp(xmlType.c_str(), "3015") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction3015 *tranc3015 = new Transaction3015();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc3015->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc3015->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc3015->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string ticketId = nextNode->value();
        tranc3015->setTicketId(ticketId);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc3015->setGameVersion(version);
        
        _transaction = tranc3015;
    }else if (strcmp(xmlType.c_str(), "2003") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction2003 *tranc2003 = new Transaction2003();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc2003->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc2003->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc2003->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc2003->setAmount(amount);
        nextNode = nextNode->next_sibling();
        string content = nextNode->value();
        tranc2003->setGetContent(content);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc2003->setGameVersion(version);
        
        _transaction = tranc2003;
    }
    else if (strcmp(xmlType.c_str(), "2005") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction2005 *tranc2005 = new Transaction2005();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc2005->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc2005->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc2005->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc2005->setGameVersion(version);
        
        _transaction = tranc2005;
        
    }else if (strcmp(xmlType.c_str(), "2008") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction2008 *tranc2008 = new Transaction2008();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc2008->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc2008->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc2008->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc2008->setAmount(amount);
        nextNode = nextNode->next_sibling();
        string content = nextNode->value();
        tranc2008->setGetContent(content);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc2008->setGameVersion(version);
        
        _transaction = tranc2008;
    }else if (strcmp(xmlType.c_str(), "3008") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction3008 *tranc3008 = new Transaction3008();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc3008->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc3008->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc3008->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string ticketId = nextNode->value();
        tranc3008->setTicketId(ticketId);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc3008->setGameVersion(version);
        
        _transaction = tranc3008;
    }else if (strcmp(xmlType.c_str(), "2013") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction2013 *tranc2013 = new Transaction2013();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc2013->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc2013->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc2013->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc2013->setAmount(amount);
        nextNode = nextNode->next_sibling();
        //        string count = nextNode->value();
        //        tranc2017->setGetCount(count);
        //        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc2013->setGameVersion(version);
        
        _transaction = tranc2013;
    }else if (strcmp(xmlType.c_str(), "2014") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction2014 *tranc2014 = new Transaction2014();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc2014->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc2014->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc2014->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc2014->setAmount(amount);
        nextNode = nextNode->next_sibling();
        string content = nextNode->value();
        tranc2014->setGetContent(content);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc2014->setGameVersion(version);
        
        _transaction = tranc2014;
    }else if (strcmp(xmlType.c_str(), "3016") == 0 ){
        xml_node<>* nextNode=rootNode;
        
        Transaction3016 *tranc3016 = new Transaction3016();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc3016->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc3016->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string gameId = nextNode->value();
        tranc3016->setGameId(gameId);
        nextNode = nextNode->next_sibling();
        string ticketId = nextNode->value();
        tranc3016->setTicketId(ticketId);
        nextNode = nextNode->next_sibling();
        string version = nextNode->value();
        tranc3016->setGameVersion(version);
        
        _transaction = tranc3016;
    }else if (strcmp(xmlType.c_str(), "4002") == 0 ){//签到 完善信息
        xml_node<>* nextNode=rootNode;
        
        Transaction4002 *tranc4002 = new Transaction4002();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc4002->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc4002->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string salesType = nextNode->value();
        tranc4002->setSalesType(salesType);
        
        _transaction = tranc4002;
    }else if (strcmp(xmlType.c_str(), "1003") == 0 ){//
        xml_node<>* nextNode=rootNode;
        
        Transaction1003 *tranc1003 = new Transaction1003();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc1003->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc1003->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();

        _transaction = tranc1003;
    }else if (strcmp(xmlType.c_str(), "4003") == 0 ){//查询签到 完善信息
        xml_node<>* nextNode=rootNode;
        
        Transaction4003 *tranc4003 = new Transaction4003();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc4003->setAccountId(accountId);
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc4003->setSessionId(sessionId);
        nextNode = nextNode->next_sibling();
        string salesType = nextNode->value();
        tranc4003->setSalesType(salesType);
        
        _transaction = tranc4003;
    }else if (strcmp(xmlType.c_str(), "7001") == 0){
        xml_node<>* nextNode=rootNode;
        
        Transaction7001 *tranc7001 = new Transaction7001();
        
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc7001->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc7001->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string amount = nextNode->value();
        tranc7001->setAmount(amount);
        
        nextNode = nextNode->next_sibling();
        string bankAccount = nextNode->value();
        tranc7001->setBankAccount(bankAccount);
        
        _transaction = tranc7001;
    }else if (strcmp(xmlType.c_str(), "7002") == 0){
        xml_node<>* nextNode=rootNode;
        
        Transaction7002 *tranc7002 = new Transaction7002();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc7002->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc7002->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string ret_code = nextNode->value();
        tranc7002->setRet_code(ret_code);
        
        nextNode = nextNode->next_sibling();
        string ret_msg = nextNode->value();
        tranc7002->setRet_msg(ret_msg);
        
        nextNode = nextNode->next_sibling();
        string result_pay = nextNode->value();
        tranc7002->setResult_pay(result_pay);
        
        nextNode = nextNode->next_sibling();
        string oid_paybill = nextNode->value();
        tranc7002->setOid_paybill(oid_paybill);
        
        nextNode = nextNode->next_sibling();
        string money_order = nextNode->value();
        tranc7002->setMoney_order(money_order);
        
        nextNode = nextNode->next_sibling();
        string no_order = nextNode->value();
        tranc7002->setNo_order(no_order);
        
        _transaction = tranc7002;
    }else if (strcmp(xmlType.c_str(), "7004") == 0){
        xml_node<>* nextNode=rootNode;
        
        Transaction7004 *tranc7004 = new Transaction7004();
        nextNode = nextNode->next_sibling();
        string openId = nextNode->value();
        tranc7004->setOpenId(openId);
        
        nextNode = nextNode->next_sibling();
        string accessToken = nextNode->value();
        tranc7004->setAccessToken(accessToken);
        
        nextNode = nextNode->next_sibling();
        string platformName = nextNode->value();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char *platformStr = OCBridge::utf8ToString(platformName.c_str());
            tranc7004->setPlatformName(platformStr);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            const char *platformStr = AppLuaApi::getInstance()->utf8ToString(platformName.c_str());
            tranc7004->setPlatformName(platformStr);
        #endif

        _transaction = tranc7004;
    }else if (strcmp(xmlType.c_str(), "7005") == 0){
        xml_node<>* nextNode=rootNode;
        
        Transaction7005 *tranc7005 = new Transaction7005();
        nextNode = nextNode->next_sibling();
        string accountId = nextNode->value();
        tranc7005->setAccountId(accountId);
        
        nextNode = nextNode->next_sibling();
        string sessionId = nextNode->value();
        tranc7005->setSessionId(sessionId);
        
        nextNode = nextNode->next_sibling();
        string openId = nextNode->value();
        tranc7005->setOpenId(openId);
        
        nextNode = nextNode->next_sibling();
        string accessToken = nextNode->value();
        tranc7005->setAccessToken(accessToken);
        
        nextNode = nextNode->next_sibling();
        string platformName = nextNode->value();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char *platformStr = OCBridge::utf8ToString(platformName.c_str());
            tranc7005->setPlatformName(platformStr);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            const char *platformStr = AppLuaApi::getInstance()->utf8ToString(platformName.c_str());
            tranc7005->setPlatformName(platformStr);
        #endif
        
        _transaction = tranc7005;
    }else if (strcmp(xmlType.c_str(), "7006") == 0){
        xml_node<>* nextNode=rootNode;
        
        Transaction7006 *tranc7006 = new Transaction7006();
        nextNode = nextNode->next_sibling();
        string account = nextNode->value();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char *accountStr = OCBridge::utf8ToString(account.c_str());
            tranc7006->setAccount(accountStr);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            const char *accountStr = AppLuaApi::getInstance()->utf8ToString(account.c_str());
            tranc7006->setAccount(accountStr);
        #endif


        
        nextNode = nextNode->next_sibling();
        string password = nextNode->value();
        tranc7006->setPassword(password);
        
        _transaction = tranc7006;
    }
    else{
        
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 发送需要进行RSA加密处理前build的xml数据包
 */
void NetDataManager::buildXMLData(char* xmlData)
{
    
    this->createTransaction(xmlData);
    
    string sendXml = _transaction->getSendContent();
    
    log("NetDataManager::buildXMLData=%s", sendXml.c_str());
    
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    cocos2d::LuaValueDict event;
    event["sendContent"] = cocos2d::LuaValue::stringValue(sendXml);
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
    
}
/*
 发送需要进行RSA加密处理的xml数据包
 */
void NetDataManager::postRSA(char* xmlData)
{
    
    string sendXml = xmlData;
    
    //log("NetDataManager::postRSA::send1=%s", xmlData);
    
    unsigned char *ciphertext;
    int outSize = Des::encrypt((unsigned char*)sendXml.c_str(), &ciphertext, (int)sendXml.size(), (unsigned char*)DES_KEY);
    //char *output = (char * ) malloc(outSize*2 + 1);
    /*char* dst = new char[outSize*2 + 1];
     for (int i = 0; i < outSize; i++) {
     sprintf(&dst[i*2], "%02X", ciphertext[i]);
     }*/
    char* dst = DataHelper::bytesToString(ciphertext, outSize);
    free(ciphertext);
    //log("NetDataManager::postRSA::send2=%s", dst);
    
    char* enXml;
    int enSize = this->gzipToEnBase64(dst, outSize*2, &enXml); // dst size = 2 * outSize
    delete []dst;
    
    this->httpSendData(enXml, enSize);
    free(enXml);
    
}
/*
 判断是否是需要进行RSA加密的接口
 */
bool NetDataManager::doRsaEncrypt()
{
    log("doRsaEncrypt getType=%s", _transaction->getType().c_str());
    if (strcmp(_transaction->getType().c_str(), "1001") == 0 ){//用户登录
        return true;
    }else if (strcmp(_transaction->getType().c_str(), "1002") == 0 ){//用户注册
        return true;
    }else if (strcmp(_transaction->getType().c_str(), "1004") == 0 ){//完善用户资料或账户变更
        return true;
    }else if (strcmp(_transaction->getType().c_str(), "1008") == 0 ){//用户注销
        return true;
    }else if (strcmp(_transaction->getType().c_str(), "1012") == 0 ){//用户密码修改
        return true;
    }else if (strcmp(_transaction->getType().c_str(), "1027") == 0 ){//用户更新银行资料
        return true;
    }else if (strcmp(_transaction->getType().c_str(), "1031") == 0 ){//用户忘记密码
        return true;
    }
    return false;
}

/**
 * 判断是否是第三方登录的接口
 */
bool NetDataManager::isThirdLoginRequest()
{
    log("isThirdLoginRequest getType=%s", _transaction->getType().c_str());
    if (strcmp(_transaction->getType().c_str(), "7004") == 0 ){//QQ，微信联合登录
        return true;
    }else if (strcmp(_transaction->getType().c_str(), "7005") == 0 ){//QQ,微信用户发起绑定请求
        return true;
    }else if (strcmp(_transaction->getType().c_str(), "7006") == 0 ){//彩乐乐用户获取Authcode
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 //向服务器请求静态页面的用户中奖信息
 */
void NetDataManager::postUpdateNotice(char* serverAddress)
{
    string url = serverAddress;
    
    //log("PostHelper::postUpdateNotice=%s", url.c_str());
    
    HttpRequest* pRequest = new HttpRequest();
    pRequest->setUrl(url.c_str());
    pRequest->setRequestType(HttpRequest::Type::GET);
    pRequest->setResponseCallback(CC_CALLBACK_2(NetDataManager::onUpdateNoticeHttpRequestCompleted, this));
    pRequest->setTag("2");
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
    
}

void NetDataManager::onUpdateNoticeHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    
    //log("onUpdateNoticeHttpRequestCompleted");
    
    if (!response)
    {
        return;
    }
    
    
    if (!response->isSucceed())
    {
        CCLOG("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    size_t size = buffer->size();
    std::string bufferStr(size,'1');
    
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        bufferStr[i] = (*buffer)[i];
    }
//    log("read server json file sucessed %s", bufferStr.c_str());
    rapidjson::Document jsonDoc;
    
    if (jsonDoc.Parse<0>(bufferStr.c_str()).HasParseError()) {
        log("read server json file failed because of %s", jsonDoc.GetParseError());
        return;
    }
    
    string message = "";
    
    const rapidjson::Value& res_value = jsonDoc["notice"];
    
    for (int i=0; i < res_value.Size(); ++i) {
        const rapidjson::Value& value = res_value[i];
        
        const char* desc = value.GetString();
//        log("====desc=====%s", desc);
        message = message + desc + ",";
    }

    UserDefault::getInstance()->setStringForKey("notice", message);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//向服务器请求静态页面的累积奖
void NetDataManager::postJackpots(char* gameId)
{
    string idData = gameId;
    
    string url = "http://58.22.103.139:8066/jackpots/";
    url.append(idData);
    
    //log("PostHelper::postJackpots=%s", url.c_str());
    
    HttpRequest* pRequest = new HttpRequest();
    pRequest->setUrl(url.c_str());
    pRequest->setRequestType(HttpRequest::Type::GET);
    pRequest->setResponseCallback(CC_CALLBACK_2(NetDataManager::onJackpotsHttpRequestCompleted, this));
    pRequest->setTag("2");
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
    
}
void NetDataManager::onJackpotsHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    //log("onJackpotsHttpRequestCompleted");
    
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    //    if (0 != strlen(response->getHttpRequest()->getTag()))
    //    {
    //        CCLOG("%s completed", response->getHttpRequest()->getTag());
    //    }
    
    //    long statusCode = response->getResponseCode();
    //    char statusString[64] = {};
    //    sprintf(statusString, "HTTP Status Code: %d, tag = %s", (int)statusCode, response->getHttpRequest()->getTag());
    //    log("onJackpotsHttpRequestCompleted： =%s", statusString);
    //    CCLOG("response code: %d", (int)statusCode);
    
    if (!response->isSucceed())
    {
        CCLOG("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    size_t size = buffer->size();
    std::string bufferStr(size,'1');
    
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        bufferStr[i] = (*buffer)[i];
    }
    
    //log("read server json file sucessed %s", bufferStr.c_str());
    
    if( strcmp(bufferStr.c_str(), "0") != 0){
        UserDefault::getInstance()->setStringForKey("Jackpots",bufferStr.c_str());
    }
}

/*
 //退出登录接口请求(非RSA)
 */
void NetDataManager::postQuit()
{
    string accountId = UserDefault::getInstance()->getStringForKey("accountId");
    string sessionId = UserDefault::getInstance()->getStringForKey("sessionId");
    log("postQuit::accountId=%s", accountId.c_str());
    log("postQuit::sessionId=%s", sessionId.c_str());
    
    //    log("accountId.empty()=%d", accountId.empty());
    //    log("sessionId.empty()=%d", sessionId.empty());
    int account_length=accountId.length();
    int sessionId_length=sessionId.length();
    log("accountId.length()=%d", account_length);
    log("sessionId.length()=%d", sessionId_length);
    
    if((account_length > 0) && (sessionId_length > 0)){
        Transaction1024 *tranc1024 = new Transaction1024();
        tranc1024->setAccountId(accountId);
        tranc1024->setSessionId(sessionId);
        _transaction = tranc1024;
        
        string sendXml = _transaction->getSendContent();
        
        log("postQuit::send=%s", sendXml.c_str());
        
        UserDefault::getInstance()->setStringForKey("accountId", "");
        UserDefault::getInstance()->setStringForKey("sessionId", "");
        
        unsigned char *ciphertext;
        int outSize = Des::encrypt((unsigned char*)sendXml.c_str(), &ciphertext, (int)sendXml.size(), (unsigned char*)DES_KEY);
        
        char* dst = DataHelper::bytesToString(ciphertext, outSize);
        free(ciphertext);
        
        char* enXml;
        int enSize = this->gzipToEnBase64(dst, outSize*2, &enXml); // dst size = 2 * outSize
        delete []dst;
        
        this->httpSendData(enXml, enSize);
        free(enXml);
    }
}

/**
 * 支付成功，通知服务器
 */
void NetDataManager::sendLLpayResultToServer(Transaction7002 *tranc7002)
{
    string accountId = UserDefault::getInstance()->getStringForKey("accountId");
    string sessionId = UserDefault::getInstance()->getStringForKey("sessionId");
    int account_length=accountId.length();
    int sessionId_length=sessionId.length();
    log("accountId.length()=%d", account_length);
    log("sessionId.length()=%d", sessionId_length);
    
    if((account_length > 0) && (sessionId_length > 0)){
        _transaction = tranc7002;
        
        string sendXml = _transaction->getSendContent();
        
        log("sendLLpayResultToServer::send=%s", sendXml.c_str());
        
        unsigned char *ciphertext;
        int outSize = Des::encrypt((unsigned char*)sendXml.c_str(), &ciphertext, (int)sendXml.size(), (unsigned char*)DES_KEY);
        
        char* dst = DataHelper::bytesToString(ciphertext, outSize);
        free(ciphertext);
        
        char* enXml;
        int enSize = this->gzipToEnBase64(dst, outSize*2, &enXml); // dst size = 2 * outSize
        delete []dst;
        
        this->httpSendData(enXml, enSize);
        free(enXml);
    }
}

/**
 * 支付成功，通知服务器----Android
 */
void NetDataManager::sendLLpayResultToServerForAndroid(const char* retCode, const char* retMsg, const char* resultPay, const char* oidPaybill, const char* moneyOrder, const char* noOrder)
{
    log("sendLLpayResultToServerForAndroid");
    Transaction7002 *tranc7002 = new Transaction7002();
    string accountId = UserDefault::getInstance()->getStringForKey("accountId");
    tranc7002->setAccountId(accountId);
    
    string sessionId = UserDefault::getInstance()->getStringForKey("sessionId");
    tranc7002->setSessionId(sessionId);
    
    tranc7002->setRet_code(retCode);
    tranc7002->setRet_msg(retMsg);
    tranc7002->setResult_pay(resultPay);
    tranc7002->setOid_paybill(oidPaybill);
    tranc7002->setMoney_order(moneyOrder);
    tranc7002->setNo_order(noOrder);

    int account_length=accountId.length();
    int sessionId_length=sessionId.length();
    log("accountId.length()=%d", account_length);
    log("sessionId.length()=%d", sessionId_length);
    
    if((account_length > 0) && (sessionId_length > 0)){
        _transaction = tranc7002;
        
        string sendXml = _transaction->getSendContent();
        
        log("sendLLpayResultToServerForAndroid::send=%s", sendXml.c_str());
        
        unsigned char *ciphertext;
        int outSize = Des::encrypt((unsigned char*)sendXml.c_str(), &ciphertext, (int)sendXml.size(), (unsigned char*)DES_KEY);
        
        char* dst = DataHelper::bytesToString(ciphertext, outSize);
        free(ciphertext);
        
        char* enXml;
        int enSize = this->gzipToEnBase64(dst, outSize*2, &enXml); // dst size = 2 * outSize
        delete []dst;
        
        this->httpSendData(enXml, enSize);
        free(enXml);
    }
}

/*
 //正常调用发送接口请求(非RSA)
 */
void NetDataManager::post(char* xmlData)
{
    
    this->createTransaction(xmlData);
    
    string sendXml = _transaction->getSendContent();
    
    log("PostHelper::send1=%s", sendXml.c_str());
    
    
    unsigned char *ciphertext;
    int outSize = Des::encrypt((unsigned char*)sendXml.c_str(), &ciphertext, (int)sendXml.size(), (unsigned char*)DES_KEY);
    //char *output = (char * ) malloc(outSize*2 + 1);
    /*char* dst = new char[outSize*2 + 1];
     for (int i = 0; i < outSize; i++) {
     sprintf(&dst[i*2], "%02X", ciphertext[i]);
     }*/
    char* dst = DataHelper::bytesToString(ciphertext, outSize);
    free(ciphertext);
    //log("PostHelper::send2=%s", dst);
    
    char* enXml;
    int enSize = this->gzipToEnBase64(dst, outSize*2, &enXml); // dst size = 2 * outSize
    delete []dst;
    
    this->httpSendData(enXml, enSize);
    free(enXml);
}

void NetDataManager::httpSendData(char * postData, unsigned int size)
{
    bool isImmediate = true;
    
    string url = UserDefault::getInstance()->getStringForKey("postUrl");
    //    if(url.empty()){
    //        url = "http://61.145.116.221:8000/LotteryAgentServer/ServiceServlet";
    //    }
    //    log("PostHelper::httpSendData url = %s", url.c_str());
    
     string baseUrl = UserDefault::getInstance()->getStringForKey("server_url");
  
    //判断是否为需要RSA加密的接口
    if(this->doRsaEncrypt()){
        //连接RSA的内网
        url = baseUrl + "RsaServlet";
//         url = "http://hbelottery.gnway.cc:18021/LotteryAgentServer/RsaServlet";
//         url = "http://58.22.103.139:18021/LotteryAgentServer/RsaServlet";
    }else{
        //连接内网
        url = baseUrl + "ServiceServlet";
//        url = "http://hbelottery.gnway.cc:18021/LotteryAgentServer/ServiceServlet";
//         url = "http://58.22.103.139:18021/LotteryAgentServer/ServiceServlet";
    }
    
    //判断是否是第三方登录的接口
    if (this->isThirdLoginRequest()) {
         url = baseUrl + "PlatformServlet";
//        url = "http://hbelottery.gnway.cc:18021/LotteryAgentServer/PlatformServlet";
//        url = "http://58.22.103.139:18021/LotteryAgentServer/PlatformServlet";
    }
    log("PostHelper::httpSendData url 222 = %s", url.c_str());
    
    HttpRequest* request = new HttpRequest();	//(std::nothrow) µ±ip¥Ì ±≤ªª·‘À––µΩonHttpRequestCompleted
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::POST);
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/x-www-form-urlencoded; charset=utf-8");
    request->setHeaders(headers);
    request->setResponseCallback(CC_CALLBACK_2(NetDataManager::onHttpRequestCompleted, this));
    
    request->setRequestData(postData, size);
    
    HttpClient * httpClient = HttpClient::getInstance();
    httpClient->setTimeoutForConnect(30);
    httpClient->setTimeoutForRead(20);
    request->setTag("1001");
    if (isImmediate)
    {
        httpClient->sendImmediate(request);
    }
    else
    {
        httpClient->send(request);
    }
    request->release();
    
    log("PostHelper::loading...");
}

void NetDataManager::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("PostHelper::status=%s", statusString);
    contentSign = 0;
    if (!response->isSucceed())
    {
        log("PostHelper::response failed");
        this->onNetError(_transaction, response);
        this->onFinished(_transaction);
        
        cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
        
        cocos2d::LuaValueDict event;
        event["responseCode"] = cocos2d::LuaValue::stringValue("-1");
        event["responseMsg"] = cocos2d::LuaValue::stringValue("网络超时");
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
        
        return;
    }
    
    std::vector<char> *buffer = response->getResponseData();
    // log("Http Test, dump data: ");
    
    char result[65535] ;
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        sprintf(&result[i], "%c", (*buffer)[i]);
    }
    //log("PostHelper::result1=%s", result);
    
    char* bytes;
    int bytesSize = DataHelper::stringToBytes(result, &bytes);
    
    unsigned char *outbuf;
    int outSize = Des::decrypt((unsigned char*)bytes, &outbuf, bytesSize, (unsigned char*)DES_KEY);
    //log("PostHelper::result2=%s", outbuf);
    delete []bytes;
    unsigned char *resp = DeBase64ToGunzip((char*)outbuf, outSize);
    free(outbuf);
    
    //log("PostHelper::result3=%s", (char*)resp);
    if (contentSign > 0)
    {
        //log("PostHelper::response is failed for no content");
        this->onNetError(_transaction, response);
        this->onFinished(_transaction);
        
        cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
        
        cocos2d::LuaValueDict event;
        event["responseCode"] = cocos2d::LuaValue::stringValue("-1");
        event["responseMsg"] = cocos2d::LuaValue::stringValue("数据出错");
        stack->pushLuaValueDict(event);
        stack->executeFunctionByHandler(mListener, 1);
        return;
    }
    
    if (response->getHttpRequest()->getReferenceCount() != 2)
    {
        log("PostHelper::request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
    }
    
    string revXml((char*)resp);
    _transaction->handleXml(const_cast<char*>(revXml.c_str())); // ±ÿ–Î“™string,≤ªø…char*
    
    string responseCode = _transaction->getResponseCode();
    string responseMsg = _transaction->getResponseMsg();
    
    if (_transaction->getResponseCode() == "000000")
    {
        this->onOK(_transaction);
        
        if (strcmp(_transaction->getType().c_str(), "1001") == 0 ){//用户登录接口返回数据处理
            Transaction1001 *tranc1001 = static_cast<Transaction1001 *>(_transaction);
            
            string accountId = tranc1001->getAccountId();
            string sessionId = tranc1001->getSessionId();
            string isConsummate = tranc1001->getIsConsummate();
            string userId = tranc1001->getUserId();
            string balance = tranc1001->getBalance();
            string freeze = tranc1001->getFreeze();
            string lotteryPoint = tranc1001->getLotteryPoint();
            string scale = tranc1001->getScale();
            
            string bigMoney = tranc1001->getBigMoney();
            string giftBalance = tranc1001->getGiftBalance();
            string giftLotteryPoint = tranc1001->getGiftLotteryPoint();
            string totalSale = tranc1001->getTotalSale();
            string totalPrize = tranc1001->getTotalPrize();
            
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                OCBridge::setAliasWithAccountId(accountId.c_str());
            #endif
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
                AppLuaApi::getInstance()->setJPushTag(accountId.c_str());
            #endif
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"]     = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"]      = cocos2d::LuaValue::stringValue(responseMsg);
            event["accountId"]        = cocos2d::LuaValue::stringValue(accountId);
            event["sessionId"]        = cocos2d::LuaValue::stringValue(sessionId);
            event["isConsummate"]     = cocos2d::LuaValue::stringValue(isConsummate);
            event["userId"]           = cocos2d::LuaValue::stringValue(userId);
            event["balance"]          = cocos2d::LuaValue::stringValue(balance);
            event["freeze"]           = cocos2d::LuaValue::stringValue(freeze);
            event["lotteryPoint"]     = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["scale"]            = cocos2d::LuaValue::stringValue(scale);
            event["bigMoney"]         = cocos2d::LuaValue::stringValue(bigMoney);
            event["giftBalance"]      = cocos2d::LuaValue::stringValue(giftBalance);
            event["giftLotteryPoint"] = cocos2d::LuaValue::stringValue(giftLotteryPoint);
            event["totalSale"]        = cocos2d::LuaValue::stringValue(totalSale);
            event["totalPrize"]       = cocos2d::LuaValue::stringValue(totalPrize);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1002") == 0 ){//用户注册接口返回数据处理
            Transaction1002 *tranc1002 = static_cast<Transaction1002 *>(_transaction);
            
            string userId = tranc1002->getUserId();
            string accountId = tranc1002->getAccountId();
            string sessionId = tranc1002->getSessionId();
            string balance = tranc1002->getBalance();
            string lotteryPoint = tranc1002->getLotteryPoint();
            string freeze = tranc1002->getFreeze();
            string isConsummate = tranc1002->getIsConsummate();
            string bigMoney = tranc1002->getBigMoney();
            string giftBalance = tranc1002->getGiftBalance();
            string giftLotteryPoint = tranc1002->getGiftLotteryPoint();
            string totalSale = tranc1002->getTotalSale();
            string totalPrize = tranc1002->getTotalPrize();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["userId"] = cocos2d::LuaValue::stringValue(userId);
            event["accountId"] = cocos2d::LuaValue::stringValue(accountId);
            event["sessionId"] = cocos2d::LuaValue::stringValue(sessionId);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["freeze"] = cocos2d::LuaValue::stringValue(freeze);
            event["isConsummate"] = cocos2d::LuaValue::stringValue(isConsummate);
            event["bigMoney"] = cocos2d::LuaValue::stringValue(bigMoney);
            event["giftBalance"] = cocos2d::LuaValue::stringValue(giftBalance);
            event["giftLotteryPoint"] = cocos2d::LuaValue::stringValue(giftLotteryPoint);
            event["totalSale"] = cocos2d::LuaValue::stringValue(totalSale);
            event["totalPrize"] = cocos2d::LuaValue::stringValue(totalPrize);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1004") == 0 ){//完善用户资料或账户变更返回数据处理
            //Transaction1004 *tranc1004 = static_cast<Transaction1004 *>(_transaction);
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1005") == 0 ){//用户支付宝快捷支付充值
            Transaction1005 *tranc1005 = static_cast<Transaction1005 *>(_transaction);
            
            string param = tranc1005->getParam();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["param"] = cocos2d::LuaValue::stringValue(param);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "4002") == 0 ){//签到 完善信息
            Transaction4002 *tranc4002 = static_cast<Transaction4002 *>(_transaction);
            
            string giftAmount = tranc4002->getGiftAmount();
            string giftBalance = tranc4002->getGiftBalance();
            string balance = tranc4002->getBalance();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["giftAmount"] = cocos2d::LuaValue::stringValue(giftAmount);
            event["giftBalance"] = cocos2d::LuaValue::stringValue(giftBalance);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "4003") == 0 ){//查询签到 完善信息
            Transaction4003 *tranc4003 = static_cast<Transaction4003 *>(_transaction);
            
            string message = tranc4003->getMessage();
   
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["message"] = cocos2d::LuaValue::stringValue(message);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1003") == 0 ){//
            Transaction1003 *tranc1003 = static_cast<Transaction1003 *>(_transaction);
            
            string balance = tranc1003->getBalance();
            string lotteryPoint = tranc1003->getLotteryPoint();
            string freezeMoney  = tranc1003->getFreezeMoney();
            string totalPrizeMoney  = tranc1003->getTotalPrizeMoney();
            string bigMoney = tranc1003->getBigMoney();
            string giftBalance = tranc1003->getGiftBalance();
            string giftLotteryPoint = tranc1003->getGiftLotteryPoint();
            string totalSale = tranc1003->getTotalSale();
            string totalPrize = tranc1003->getTotalPrize();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["freezeMoney"] = cocos2d::LuaValue::stringValue(freezeMoney);
            event["totalPrizeMoney"] = cocos2d::LuaValue::stringValue(totalPrizeMoney);
            event["bigMoney"] = cocos2d::LuaValue::stringValue(bigMoney);
            event["giftBalance"] = cocos2d::LuaValue::stringValue(giftBalance);
            event["giftLotteryPoint"] = cocos2d::LuaValue::stringValue(giftLotteryPoint);
            event["totalSale"] = cocos2d::LuaValue::stringValue(totalSale);
            event["totalPrize"] = cocos2d::LuaValue::stringValue(totalPrize);
          
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1006") == 0 ){//用户提款
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1007") == 0){
            Transaction1007 *tranc1007 = static_cast<Transaction1007 *>(_transaction);
            
            string betsInfo = tranc1007->getBetsInfo();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["betsInfo"] = cocos2d::LuaValue::stringValue(betsInfo);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1008") == 0 ){//用户注销返回数据处理
            //Transaction1008 *tranc1008 = static_cast<Transaction1008 *>(_transaction);
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1010") == 0){
            Transaction1010 *tranc1010 = static_cast<Transaction1010 *>(_transaction);
            
            string betsInfo = tranc1010->getBetsInfo();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["betsInfo"] = cocos2d::LuaValue::stringValue(betsInfo);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1011") == 0 ){
            Transaction1011 *tranc1011 = static_cast<Transaction1011 *>(_transaction);
            
            string userName = tranc1011->getUserName();
            string userId = tranc1011->getUserId();
            string idNumber = tranc1011->getIdNumber();
            string phoneNumber = tranc1011->getPhoneNumber();
            string cardNumber = tranc1011->getCardNumber();
            string bank = tranc1011->getBank();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["userName"] = cocos2d::LuaValue::stringValue(userName);
            event["userId"] = cocos2d::LuaValue::stringValue(userId);
            event["idNumber"] = cocos2d::LuaValue::stringValue(idNumber);
            event["phoneNumber"] = cocos2d::LuaValue::stringValue(phoneNumber);
            event["cardNumber"] = cocos2d::LuaValue::stringValue(cardNumber);
            event["bank"] = cocos2d::LuaValue::stringValue(bank);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1012") == 0 ){//用户密码修改
            //Transaction1012 *tranc1012 = static_cast<Transaction1012 *>(_transaction);
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1013") == 0 ){//用户支付宝WAP支付充值
            Transaction1013 *tranc1013 = static_cast<Transaction1013 *>(_transaction);
            
            string uri = tranc1013->getUri();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["uri"] = cocos2d::LuaValue::stringValue(uri);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1014") == 0 ){
            Transaction1014 *tranc1014 = static_cast<Transaction1014 *>(_transaction);
            
            string smsNum = tranc1014->getSmsNum();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["smsNum"] = cocos2d::LuaValue::stringValue(smsNum);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1015") == 0 ){
            Transaction1015 *tranc1015 = static_cast<Transaction1015 *>(_transaction);
            
            string areaInfo = tranc1015->getAreaInfo();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["areaInfo"] = cocos2d::LuaValue::stringValue(areaInfo);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1018") == 0 ){//获取银行信息
            Transaction1018 *tranc1018 = static_cast<Transaction1018 *>(_transaction);
            
            string allBanks = tranc1018->getAllBanks();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["allBanks"] = cocos2d::LuaValue::stringValue(allBanks);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1024") == 0 ){//退出登录
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1027") == 0 ){//用户更新银行资料
            //Transaction1027 *tranc1027 = static_cast<Transaction1027 *>(_transaction);
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1030") == 0 ){//用户更新手机资料
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1031") == 0 ){//用户忘记密码
            //Transaction1031 *tranc1031 = static_cast<Transaction1031 *>(_transaction);
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1020") == 0 ){//用户反馈
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1032") == 0 ){//意见反馈查询
            Transaction1032 *tranc1032 = static_cast<Transaction1032 *>(_transaction);
            
            string id = tranc1032->getId();
            string type = tranc1032->getType();
            string memo = tranc1032->getMemo();
            string createTime = tranc1032->getCreateTime();
            string reply = tranc1032->getReply();
            string replyTime = tranc1032->getReplyTime();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["id"] = cocos2d::LuaValue::stringValue(id);
            event["type"] = cocos2d::LuaValue::stringValue(type);
            event["memo"] = cocos2d::LuaValue::stringValue(memo);
            event["createTime"] = cocos2d::LuaValue::stringValue(createTime);
            event["reply"] = cocos2d::LuaValue::stringValue(reply);
            event["replyTime"] = cocos2d::LuaValue::stringValue(replyTime);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1034") == 0){
            Transaction1034 *tranc1034 = static_cast<Transaction1034 *>(_transaction);
            
            string emailsInfo = tranc1034->getEmailsInfo();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["emailsInfo"] = cocos2d::LuaValue::stringValue(emailsInfo);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1035") == 0){
//            Transaction1035 *tranc1035 = static_cast<Transaction1035 *>(_transaction);
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1036") == 0){
            Transaction1036 *tranc1036 = static_cast<Transaction1036 *>(_transaction);
            
            string giftAmount = tranc1036->getGiftAmount();
            string balance = tranc1036->getBalance();
            string giftBalance = tranc1036->getGiftBalance();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["giftAmount"] = cocos2d::LuaValue::stringValue(giftAmount);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["giftBalance"] = cocos2d::LuaValue::stringValue(giftBalance);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "1026") == 0 ){
            Transaction1026 *tranc1026 = static_cast<Transaction1026 *>(_transaction);
            
            string balance = tranc1026->getBalance();
            string lotteryPoint = tranc1026->getLotteryPoint();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "2007") == 0 )
        {
            Transaction2007 *tranc2007 = static_cast<Transaction2007 *>(_transaction);
            
            string balance = tranc2007->getBalance();
            string lotteryPoint = tranc2007->getLotteryPoint();
            string ticketId = tranc2007->getTicketId();
            string ticketContent = tranc2007->getTicketContent();
            string securityCode = tranc2007->getSecurityCode();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "2002") == 0 )
        {
            Transaction2002 *tranc2002 = static_cast<Transaction2002 *>(_transaction);
            
            string balance = tranc2002->getBalance();
            string lotteryPoint = tranc2002->getLotteryPoint();
            string ticketId = tranc2002->getTicketId();
            string ticketContent = tranc2002->getTicketContent();
            string securityCode = tranc2002->getSecurityCode();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "1023") == 0 ){
            
            Transaction1023 *tranc1023 = static_cast<Transaction1023 *>(_transaction);
            
            string ticketId = tranc1023->getTicketId();
            string winAmount = tranc1023->getWinAmount();
            string gameId = tranc1023->getAddGameId();
            string ticketContent = tranc1023->getTicketContent();
            string securityCode = tranc1023->getSecurityCode();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["winAmount"] = cocos2d::LuaValue::stringValue(winAmount);
            event["gameId"] = cocos2d::LuaValue::stringValue(gameId);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
            
        }else if(strcmp(_transaction->getType().c_str(), "3005") == 0 ){
            Transaction3005 *tranc3005 = static_cast<Transaction3005 *>(_transaction);
            
            string balance = tranc3005->getBalance();
            string lotteryPoint = tranc3005->getLotteryPoint();
            string awardLevel = tranc3005->getAwardLevel();
            string winLotteryPoint = tranc3005->getWinLotteryPoint();
            string winAmount = tranc3005->getWinAmount();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["awardLevel"] = cocos2d::LuaValue::stringValue(awardLevel);
            event["winLotteryPoint"] = cocos2d::LuaValue::stringValue(winLotteryPoint);
            event["winAmount"] = cocos2d::LuaValue::stringValue(winAmount);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "2017") == 0 ){
            Transaction2017 *tranc2017 = static_cast<Transaction2017 *>(_transaction);
            
            string balance = tranc2017->getBalance();
            string lotteryPoint = tranc2017->getLotteryPoint();
            string ticketId = tranc2017->getTicketId();
            string winAmount = tranc2017->getWinAmount();
            string ticketContent = tranc2017->getTicketContent();
            string securityCode = tranc2017->getSecurityCode();
            
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["winAmount"] = cocos2d::LuaValue::stringValue(winAmount);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "3015") == 0 ){
            Transaction3015 *tranc3015 = static_cast<Transaction3015 *>(_transaction);
            
            string balance = tranc3015->getBalance();
            string lotteryPoint = tranc3015->getLotteryPoint();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "2003") == 0 ){
            Transaction2003 *tranc2003 = static_cast<Transaction2003 *>(_transaction);
            
            string balance = tranc2003->getBalance();
            string lotteryPoint = tranc2003->getLotteryPoint();
            string ticketId = tranc2003->getTicketId();
            string ticketContent = tranc2003->getTicketContent();
            string securityCode = tranc2003->getSecurityCode();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2005") == 0 ){
            
            Transaction2005 *tranc2005 = static_cast<Transaction2005 *>(_transaction);
            
            string ticketId = tranc2005->getTicketId();
            string balance = tranc2005->getBalance();
            string lotteryPoint = tranc2005->getLotteryPoint();
            string gameId = tranc2005->getAddGameId();
            string ticketContent = tranc2005->getTicketContent();
            string securityCode = tranc2005->getSecurityCode();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["gameId"] = cocos2d::LuaValue::stringValue(gameId);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
            
        }else if (strcmp(_transaction->getType().c_str(), "2008") == 0 ){
            Transaction2008 *tranc2008 = static_cast<Transaction2008 *>(_transaction);
            
            string balance = tranc2008->getBalance();
            string lotteryPoint = tranc2008->getLotteryPoint();
            string ticketId = tranc2008->getTicketId();
            string ticketContent = tranc2008->getTicketContent();
            string securityCode = tranc2008->getSecurityCode();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "3008") == 0 ){
            Transaction3008 *tranc3008 = static_cast<Transaction3008 *>(_transaction);
            
            string balance = tranc3008->getBalance();
            string lotteryPoint = tranc3008->getLotteryPoint();
            string awardLevel = tranc3008->getAwardLevel();
            string winLotteryPoint = tranc3008->getWinLotteryPoint();
            string winAmount = tranc3008->getWinAmount();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["awardLevel"] = cocos2d::LuaValue::stringValue(awardLevel);
            event["winLotteryPoint"] = cocos2d::LuaValue::stringValue(winLotteryPoint);
            event["winAmount"] = cocos2d::LuaValue::stringValue(winAmount);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "2013") == 0 ){
            Transaction2013 *tranc2013 = static_cast<Transaction2013 *>(_transaction);
            
            string balance = tranc2013->getBalance();
            string lotteryPoint = tranc2013->getLotteryPoint();
            string ticketId = tranc2013->getTicketId();
            string ticketContent = tranc2013->getTicketContent();
            string securityCode = tranc2013->getSecurityCode();
            
            //            log("balance::, is %s", balance.c_str());
            //            log("lotteryPoint::, is %s", lotteryPoint.c_str());
            //            log("winAmount::, is %s", winAmount.c_str());
            //            log("ticketId::, is %s", ticketId.c_str());
            //            log("ticketContent::, is %s", ticketContent.c_str());
            //            log("securityCode::, is %s", securityCode.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "2014") == 0 ){
            Transaction2014 *tranc2014 = static_cast<Transaction2014 *>(_transaction);
            
            string balance = tranc2014->getBalance();
            string lotteryPoint = tranc2014->getLotteryPoint();
            string ticketId = tranc2014->getTicketId();
            string ticketContent = tranc2014->getTicketContent();
            string securityCode = tranc2014->getSecurityCode();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["ticketId"] = cocos2d::LuaValue::stringValue(ticketId);
            event["ticketContent"] = cocos2d::LuaValue::stringValue(ticketContent);
            event["securityCode"] = cocos2d::LuaValue::stringValue(securityCode);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "3016") == 0 ){
            Transaction3016 *tranc3016 = static_cast<Transaction3016 *>(_transaction);
            
            string balance = tranc3016->getBalance();
            string lotteryPoint = tranc3016->getLotteryPoint();
            string winAmount = tranc3016->getWinAmount();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["winAmount"] = cocos2d::LuaValue::stringValue(winAmount);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "7001") == 0){
            Transaction7001 *tranc7001 = static_cast<Transaction7001 *>(_transaction);
            
            string orderId = tranc7001->getOrderId();
            string createTime = tranc7001->getCreateTime();
            string accountId = tranc7001->getUserAccountId();
            string oid_partner = tranc7001->getOid_partner();
            string sign_type = tranc7001->getSign_type();
            string buis_partner = tranc7001->getBuis_partner();
            string notify_url = tranc7001->getNotify_url();
            string rsa_private_key = tranc7001->getRsa_private_key();
            string registerTime = tranc7001->getRegisterTime();
            string phoneNumber = tranc7001->getPhoneNumber();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["responseType"] = cocos2d::LuaValue::stringValue("7001");
            event["orderId"] = cocos2d::LuaValue::stringValue(orderId);
            event["createTime"] = cocos2d::LuaValue::stringValue(createTime);
            event["accountId"] = cocos2d::LuaValue::stringValue(accountId);
            event["oid_partner"] = cocos2d::LuaValue::stringValue(oid_partner);
            event["sign_type"] = cocos2d::LuaValue::stringValue(sign_type);
            event["buis_partner"] = cocos2d::LuaValue::stringValue(buis_partner);
            event["notify_url"] = cocos2d::LuaValue::stringValue(notify_url);
            event["rsa_private_key"] = cocos2d::LuaValue::stringValue(rsa_private_key);
            event["registerTime"] = cocos2d::LuaValue::stringValue(registerTime);
            event["phoneNumber"] = cocos2d::LuaValue::stringValue(phoneNumber);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "7002") == 0){
//            Transaction7002 *tranc7002 = static_cast<Transaction7002 *>(_transaction);
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["responseType"] = cocos2d::LuaValue::stringValue("7002");
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "7004") == 0){
            Transaction7004 *tranc7004 = static_cast<Transaction7004 *>(_transaction);
            string userId = tranc7004->getUserId();
            string accountId = tranc7004->getAccountId();
            string sessionId = tranc7004->getSessionId();
            string balance = tranc7004->getBalance();
            string lotteryPoint = tranc7004->getLotteryPoint();
            string freeze = tranc7004->getFreeze();
            string isConsummate = tranc7004->getIsConsummate();
            string bigMoney = tranc7004->getBigMoney();
            string giftBalance = tranc7004->getGiftBalance();
            string giftLotteryPoint = tranc7004->getGiftLotteryPoint();
            string totalSale = tranc7004->getTotalSale();
            string totalPrize = tranc7004->getTotalPrize();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["userId"] = cocos2d::LuaValue::stringValue(userId);
            event["accountId"] = cocos2d::LuaValue::stringValue(accountId);
            event["sessionId"] = cocos2d::LuaValue::stringValue(sessionId);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["freeze"] = cocos2d::LuaValue::stringValue(freeze);
            event["isConsummate"] = cocos2d::LuaValue::stringValue(isConsummate);
            event["bigMoney"] = cocos2d::LuaValue::stringValue(bigMoney);
            event["giftBalance"] = cocos2d::LuaValue::stringValue(giftBalance);
            event["giftLotteryPoint"] = cocos2d::LuaValue::stringValue(giftLotteryPoint);
            event["totalSale"] = cocos2d::LuaValue::stringValue(totalSale);
            event["totalPrize"] = cocos2d::LuaValue::stringValue(totalPrize);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "7005") == 0){
            //            Transaction7005 *tranc7005 = static_cast<Transaction7005 *>(_transaction);
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "7006") == 0){
            Transaction7006 *tranc7006 = static_cast<Transaction7006 *>(_transaction);
            
            string openId = tranc7006->getOpenId();
            string accessToken = tranc7006->getAccessToken();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["openId"] = cocos2d::LuaValue::stringValue(openId);
            event["accessToken"] = cocos2d::LuaValue::stringValue(accessToken);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }
    }
    else if (_transaction->getResponseCode() == "100302"){
        log("this->ios 100302");
        if(strcmp(_transaction->getType().c_str(), "1023") == 0 ){
            log("1023接口 版本不匹配");
            Transaction1023 *tranc1023 = static_cast<Transaction1023 *>(_transaction);
            
            string urlAddress = tranc1023->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2007") == 0){
            log("2007 版本不匹配");
            
            Transaction2007 *tranc2007 = static_cast<Transaction2007 *>(_transaction);
            
            string urlAddress = tranc2007->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2002") == 0){
            log("2002 版本不匹配");
            
            Transaction2002 *tranc2002 = static_cast<Transaction2002 *>(_transaction);
            
            string urlAddress = tranc2002->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "3005") == 0){
            log("3005 版本不匹配");
            
            Transaction3005 *tranc3005 = static_cast<Transaction3005 *>(_transaction);
            
            string urlAddress = tranc3005->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2017") == 0){
            log("2017 附加游戏版本不匹配");
            
            Transaction2017 *tranc2017 = static_cast<Transaction2017 *>(_transaction);
            
            string urlAddress = tranc2017->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "3015") == 0){
            log("3015 附加游戏版本不匹配");
            
            Transaction3015 *tranc3015 = static_cast<Transaction3015 *>(_transaction);
            
            string urlAddress = tranc3015->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2005") == 0 ){
            log("2005接口 版本不匹配");
            Transaction2005 *tranc2005 = static_cast<Transaction2005 *>(_transaction);
            
            string urlAddress = tranc2005->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2003") == 0){
            log("2003 版本不匹配");
            
            Transaction2003 *tranc2003 = static_cast<Transaction2003 *>(_transaction);
            
            string urlAddress = tranc2003->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2008") == 0){
            log("2008 版本不匹配");
            
            Transaction2008 *tranc2008 = static_cast<Transaction2008 *>(_transaction);
            
            string urlAddress = tranc2008->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "3008") == 0){
            log("3008 版本不匹配");
            
            Transaction3008 *tranc3008 = static_cast<Transaction3008 *>(_transaction);
            
            string urlAddress = tranc3008->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2013") == 0){
            log("2013 版本不匹配");
            
            Transaction2013 *tranc2013 = static_cast<Transaction2013 *>(_transaction);
            
            string urlAddress = tranc2013->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "2014") == 0){
            log("2014 版本不匹配");
            
            Transaction2014 *tranc2014 = static_cast<Transaction2014 *>(_transaction);
            
            string urlAddress = tranc2014->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if(strcmp(_transaction->getType().c_str(), "3016") == 0){
            log("3016 版本不匹配");
            
            Transaction3016 *tranc3016 = static_cast<Transaction3016 *>(_transaction);
            
            string urlAddress = tranc3016->getUrlAddress();
            
            log("urlAddress=%s", urlAddress.c_str());
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["urlAddress"] = cocos2d::LuaValue::stringValue(urlAddress);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }
    }
    else if (_transaction->getResponseCode() == "700008"){
        if (strcmp(_transaction->getType().c_str(), "7004") == 0) {
            log("7004--没绑定账号");
            
            this->onOK(_transaction);
            
            Transaction7004 *tranc7004 = static_cast<Transaction7004 *>(_transaction);
            string nickName = tranc7004->getNickName();
            string figureUrl = tranc7004->getFigureUrl();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["nickName"] = cocos2d::LuaValue::stringValue(nickName);
            event["figureUrl"] = cocos2d::LuaValue::stringValue(figureUrl);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }
    }
    else {
        this->onFail(_transaction);
        
        if(strcmp(_transaction->getType().c_str(), "3005") == 0 ){
            Transaction3005 *tranc3005 = static_cast<Transaction3005 *>(_transaction);
            
            string balance = tranc3005->getBalance();
            string lotteryPoint = tranc3005->getLotteryPoint();
            string awardLevel = tranc3005->getAwardLevel();
            string winLotteryPoint = tranc3005->getWinLotteryPoint();
            string winAmount = tranc3005->getWinAmount();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["awardLevel"] = cocos2d::LuaValue::stringValue(awardLevel);
            event["winLotteryPoint"] = cocos2d::LuaValue::stringValue(winLotteryPoint);
            event["winAmount"] = cocos2d::LuaValue::stringValue(winAmount);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
            
        }else if(strcmp(_transaction->getType().c_str(), "3015") == 0 ){
            Transaction3015 *tranc3015 = static_cast<Transaction3015 *>(_transaction);
            
            string balance = tranc3015->getBalance();
            string lotteryPoint = tranc3015->getLotteryPoint();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
            
        }else if(strcmp(_transaction->getType().c_str(), "3016") == 0 ){
            Transaction3016 *tranc3016 = static_cast<Transaction3016 *>(_transaction);
            
            string balance = tranc3016->getBalance();
            string lotteryPoint = tranc3016->getLotteryPoint();
            string winAmount = tranc3016->getWinAmount();
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["balance"] = cocos2d::LuaValue::stringValue(balance);
            event["lotteryPoint"] = cocos2d::LuaValue::stringValue(lotteryPoint);
            event["winAmount"] = cocos2d::LuaValue::stringValue(winAmount);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
            
        }else if (strcmp(_transaction->getType().c_str(), "7001") == 0){
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["responseType"] = cocos2d::LuaValue::stringValue("7001");
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }else if (strcmp(_transaction->getType().c_str(), "7002") == 0){
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            event["responseType"] = cocos2d::LuaValue::stringValue("7002");
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }
        else{
            
            this->onFinished(_transaction);
            
            cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
            
            cocos2d::LuaValueDict event;
            event["responseCode"] = cocos2d::LuaValue::stringValue(responseCode);
            event["responseMsg"] = cocos2d::LuaValue::stringValue(responseMsg);
            
            stack->pushLuaValueDict(event);
            stack->executeFunctionByHandler(mListener, 1);
        }
    }
    
}

unsigned char* NetDataManager::DeBase64ToGunzip(char *en, unsigned int size)
{
#define BUF_SIZE 65535
    Bytef  odata[BUF_SIZE];
    uLong nodata = BUF_SIZE;
    
    unsigned char* de;
    int deSize = base64Decode((unsigned char*)en, size, &de);
    log("DeBase64 = %s ", de);
    log("DeBase64 size = %d", deSize);
    if(deSize == 0)
    {
        contentSign = 1;
    }
    
    memset(odata, 0, BUF_SIZE);
    if(GzipUtil::gzipDecompress(de, deSize, odata, &nodata) == 0)
    {
        log("PostHelper::deCompress=%s", odata);
    }
    free(de);
    
    return odata;
}

void NetDataManager::onOK(AbstractTransaction* transaction)
{
    log("PostHelper::onOK...");
    //    if(_onOKCallback)
    //        _onOKCallback(transaction);
}

void NetDataManager::onFail(AbstractTransaction* transaction)
{
    log("PostHelper::onFail...");
    if (transaction->getResponseCode() == "100105") //”√ªß—È÷§ ß∞‹
    {
        
    }
    else if (transaction->getResponseCode() == "100102") //”√ªß”‡∂Ó≤ª◊„
    {
        
    }
    else if (transaction->getResponseCode() == "300111") //Ω±∆⁄Œ¥ø™ €ªÚ“—π˝Ωÿ÷π ±º‰
    {
        
    }
    else if (transaction->getResponseCode() == "300121" || transaction->getResponseCode() == "300110") //ŒﬁŒ¥ÕÍ≥…µƒ∆±
    {
        
    }
    else if (transaction->getResponseCode() == "100302") //”Œœ∑øÕªß∂À∞Ê±æ”Î∑˛ŒÒ∆˜≤ª∆•≈‰
    {
        
    }
    //    if(_onFailCallback)
    //        _onFailCallback(transaction);
}

void NetDataManager::onNetError(AbstractTransaction* transaction, HttpResponse *response)
{
    log("PostHelper::onNetError: %s", response->getErrorBuffer());
    //    if(_onNetErrorCallback)
    //        _onNetErrorCallback(transaction, response->getErrorBuffer());
}

void NetDataManager::onFinished(AbstractTransaction* transaction)
{
    log("PostHelper::onFinished...");
    //    if(_onFinishedCallback)
    //        _onFinishedCallback(transaction);
    
    delete _transaction;
    _transaction = nullptr;
    
}

#pragma mark ---- 微信登录验证------

void NetDataManager::getOpenTokenAndOpenIdFromWeiXinWithUrl(const char* url)
{
    log("PostHelper::getOpenTokenAndOpenIdFromWeiXinWithUrl=%s", url);
    
    HttpRequest* pRequest = new HttpRequest();
    pRequest->setUrl(url);
    pRequest->setRequestType(HttpRequest::Type::GET);
    pRequest->setResponseCallback(CC_CALLBACK_2(NetDataManager::onGetOpenTokenAndOpenIdHttpRequestCompleted, this));
    pRequest->setTag("5");
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
}

void NetDataManager::onGetOpenTokenAndOpenIdHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    log("onGetOpenTokenAndOpenIdHttpRequestCompleted");
    
    if (!response)
    {
        return;
    }
    
    
    if (!response->isSucceed())
    {
        CCLOG("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    size_t size = buffer->size();
    std::string bufferStr(size,'1');
    
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        bufferStr[i] = (*buffer)[i];
    }
//    log("read server json file sucessed %s", bufferStr.c_str());
    rapidjson::Document jsonDoc;
    
    if (jsonDoc.Parse<0>(bufferStr.c_str()).HasParseError()) {
        log("read server json file failed because of %s", jsonDoc.GetParseError());
        return;
    }
    
    //    std::string errcode = jsonDoc["errcode"].GetString();
    
    std::string accessToken = jsonDoc["access_token"].GetString();
    std::string openId = jsonDoc["openid"].GetString();
    std::string refresh_token = jsonDoc["refresh_token"].GetString();
    
    //    const char *platform = OCBridge::getPlatform(true);
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        std::string platform = OCBridge::stringToUtf8("微信");
    #endif
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        std::string platform = AppLuaApi::getInstance()->utf8ToString("微信");
    #endif
    
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    cocos2d::LuaValueDict event;
    event["responseCode"] = cocos2d::LuaValue::stringValue("35000");
    event["openId"] = cocos2d::LuaValue::stringValue(openId);
    event["accessToken"] = cocos2d::LuaValue::stringValue(accessToken);
    event["platformName"] = cocos2d::LuaValue::stringValue(platform);
    
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
}

void NetDataManager::returnToLuaWithOpenIDAndAccessToken(const char* openId, const char* accessToken)
{
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    cocos2d::LuaValueDict event;
    event["responseCode"] = cocos2d::LuaValue::stringValue("35000");
    event["openId"] = cocos2d::LuaValue::stringValue(openId);
    event["accessToken"] = cocos2d::LuaValue::stringValue(accessToken);
    event["platformName"] = cocos2d::LuaValue::stringValue("QQ");
    
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
}

void NetDataManager::returnToLuaWithNotificationInfo(const char* userInfo)
{
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    cocos2d::LuaValueDict event;
    event["responseCode"] = cocos2d::LuaValue::stringValue("35001");
    event["userInfo"] = cocos2d::LuaValue::stringValue(userInfo);
    event["responseMsg"] = cocos2d::LuaValue::stringValue("");
    
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
}

void NetDataManager::returnToLuaWithAndroidNotificationInfo(const char* userInfo, const char* clientType)
{
    UserDefault::getInstance()->setBoolForKey("ReceivePushMessage", true);
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    cocos2d::LuaValueDict event;
    event["responseCode"] = cocos2d::LuaValue::stringValue("35001");
    event["userInfo"] = cocos2d::LuaValue::stringValue(userInfo);
    event["clientType"] = cocos2d::LuaValue::stringValue(clientType);
    event["responseMsg"] = cocos2d::LuaValue::stringValue("");
    
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
}

void NetDataManager::returnToLuaWithLLpayResult(const char* result)
{
    cocos2d::LuaStack* stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    
    cocos2d::LuaValueDict event;
    event["responseCode"] = cocos2d::LuaValue::stringValue("35002");
    event["responseMsg"] = cocos2d::LuaValue::stringValue(result);
    event["responseType"] = cocos2d::LuaValue::stringValue("7001");
    
    stack->pushLuaValueDict(event);
    stack->executeFunctionByHandler(mListener, 1);
}
