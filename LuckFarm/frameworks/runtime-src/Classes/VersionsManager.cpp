//
//  VersionsManager.cpp
//  SlotFun
//
//  Created by xuzhiqiang on 14-4-21.
//
//

#include "cocos2d.h"

#include "VersionsManager.h"
#include "LoadingLayer.h"

#include <curl/curl.h>
#include <curl/easy.h>


#include "json/document.h"
#include "json/filestream.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "AppLuaApi/AppLuaApi.h"
#include "Global.h"

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//安卓
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

    //演示地址
    #define  KEY_STATIC_SERVERURL   "http://123.206.33.176/static/hongboecai/android/repository_"
    #define  KEY_STATIC_VERSIONURL  "http://123.206.33.176/static/hongboecai/android/version_"

    //提审上线地址
//    #define  KEY_STATIC_SERVERURL   "http://download.zuanyanguoji.com/static/hongboecai/test_android/repository_"
//    #define  KEY_STATIC_VERSIONURL  "http://download.zuanyanguoji.com/static/hongboecai/test_android/version_"

////    //开发地址
//    #define  KEY_STATIC_SERVERURL      "http://download.zuanyanguoji.com/static/hongboecai/develop_android/repository_"
//    #define  KEY_STATIC_VERSIONURL      "http://download.zuanyanguoji.com/static/hongboecai/develop_android/version_"

    #define SERVER_HOST "http://casinocn.zuanyanguoji.com/"
#endif

//ios
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //演示地址
    #define  KEY_STATIC_SERVERURL   "http://123.206.33.176/static/hongboecai/ios/repository_"
    #define  KEY_STATIC_VERSIONURL  "http://123.206.33.176/static/hongboecai/ios/version_"

    //提审上线地址
//    #define  KEY_STATIC_SERVERURL   "http://download.zuanyanguoji.com/static/hongboecai/test_ios/repository_"
//    #define  KEY_STATIC_VERSIONURL  "http://download.zuanyanguoji.com/static/hongboecai/test_ios/version_"

    //开发地址
//    #define  KEY_STATIC_SERVERURL   "http://download.zuanyanguoji.com/static/hongboecai/develop_ios/repository_"
//    #define  KEY_STATIC_VERSIONURL  "http://download.zuanyanguoji.com/static/hongboecai/develop_ios/version_"

    #define SERVER_HOST "http://casinocn.zuanyanguoji.com/"
#endif

using namespace cocos2d;
using namespace extension;
using namespace network;
using namespace cocosbuilder;

using namespace std;

VersionsManager* VersionsManager::s_sharedVersionsManager = NULL;

//判断是否IPv6网络
bool isIPV6Net(const std::string domainStr = "www.baidu.com")
{
    bool isIPV6Net = false;
    
    struct addrinfo *result = nullptr,*curr;
    
    struct sockaddr_in6 dest;
    bzero(&dest, sizeof(dest));
    
    dest.sin6_family  = AF_INET6;
    
    int ret = getaddrinfo(domainStr.c_str(),nullptr,nullptr,&result);
    if (ret == 0)
    {
        for (curr = result; curr != nullptr; curr = curr->ai_next)
        {
            switch (curr->ai_family)
            {
                case AF_INET6:
                {
                    isIPV6Net = true;
                    break;
                }
                case AF_INET:
                    
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    freeaddrinfo(result);
    
    return isIPV6Net;
}


static std::string domainToIP(const char* pDomain)
{
    if (isIPV6Net(pDomain))
    {
        struct addrinfo hint;
        memset(&hint, 0x0, sizeof(hint));
        hint.ai_family = AF_INET6;
        hint.ai_flags = AI_V4MAPPED;
        
        addrinfo* answer = nullptr;
        getaddrinfo(pDomain, nullptr, &hint, &answer);
        
        if (answer != nullptr)
        {
            char hostname[1025] = "";
            
            getnameinfo(answer->ai_addr,answer->ai_addrlen,hostname,1025,nullptr,0,0);
            
            char ipv6[128] = "";
            memcpy(ipv6,hostname,128);
            
            CCLOG("domainToIP addrStr:%s", ipv6);
            
            return ipv6;
        }
        
        freeaddrinfo(answer);
    }
    else
    {
        struct hostent* h = gethostbyname(pDomain);
        if( h != NULL )
        {
            unsigned char* p = (unsigned char *)(h->h_addr_list)[0];
            if( p != NULL )
            {
                char ip[16] = {0};
                sprintf(ip, "%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
                return ip;
            }
        }
    }
    return "";
}


string getIPWithHostName(string hostName,string server="http"){
    
    struct addrinfo hints,* result;
    struct addrinfo * res;
    char ipstr[128];
    int error = 0;
    bool IS_IPV6 = false;

    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC; /* Allow IPv4 */
    hints.ai_flags = AI_PASSIVE;/* For wildcard IP address */
    hints.ai_protocol = 0; /* Any protocol */
    //hints.ai_socktype = SOCK_STREAM;
    
    error = getaddrinfo(hostName.c_str(), NULL, &hints, &result);
    if(error != 0) {
        return "";
    }
    for(res = result; res!=NULL; res = res->ai_next) {
        void *addr;
        char *ipver;
        
        if (res->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
            addr = &(ipv4->sin_addr);
            IS_IPV6 = false;
            
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
            addr = &(ipv6->sin6_addr);
            IS_IPV6 = true;
            
        }
        
        // convert the IP to a string and print it:
        inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);
        printf(" %s: %s,\n", ipver, ipstr);
    }
    freeaddrinfo(result);

    return ipstr;
}
string getIpWithAllName(string allName,string server="http"){
    if(allName == ""){
        return "";
    }
    int comPos = 0;
    int httpPos = 0;
    
    string hostName;
    
    comPos = allName.find(".com/");
    httpPos = allName.find(server);
    if(comPos !=0){
        //printf("%d",allName.size());
        hostName = allName.substr(httpPos+server.size()+3,comPos-(httpPos+server.size()+3)+4);
        printf("%s",hostName.c_str());
        //string ip = getIPWithHostName(hostName,server);
        string ip = domainToIP(hostName.c_str());
        if(ip == ""){
            return "";
        }
        string newAllName;
        newAllName = server+"://"+ip+allName.substr(comPos+4);
        printf("%s",newAllName.c_str());
        return newAllName;
    }
    return "";
}


static size_t getVCode(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    string *version = (string*)userdata;
    version->append((char*)ptr, size * nmemb);
    
    return (size * nmemb);
}
//字符串分割函数
void splitString(std::string str, std::vector<std::string>& dest, const char* pttn)
{
    if(str.size() == 0) return;
    
    std::string pattern = pttn;
    
    std::string::size_type pos;
    str+=pattern;//扩展字符串以方便操作
    size_t size=str.size();
    
    for(size_t i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            dest.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
}
VersionsManager* VersionsManager::sharedVersionsManager(void)
{
    if (!s_sharedVersionsManager)
    {
        s_sharedVersionsManager = new VersionsManager();
    }
    return s_sharedVersionsManager;
}
 
VersionsManager::VersionsManager():m_serverUrl(""),m_versionUrl("")
{
    
    //TODO 测试
//    string ip = getIpWithAllName("http://www.zuanyanguoji.com/static/casino_cn/ios/version.html");
//    printf("ip:%s",ip.c_str());
//    //string ip = getIPWithHostName(SERVER_HOST);
//    if(ip==""){
//        printf("VersionsManager::VersionsManager==>无法连接到网络");
//        ip =SERVER_HOST;
//    }
//
//    m_serverUrl = "http://"+ip+"/static/casino_cn/ios/repository_" + string(AppLuaApi::getInstance()->AppVersion()) + ".json";
//    m_versionUrl = "http://"+ip+"/static/casino_cn/ios/version.html";
    
    m_serverUrl = KEY_STATIC_SERVERURL+ string(AppLuaApi::getInstance()->AppVersion()) + ".json";
    m_versionUrl = KEY_STATIC_VERSIONURL+ string(AppLuaApi::getInstance()->AppVersion()) + ".html";;
    
    CCLOG("VersionsManager::VersionsManager==>m_serverUrl:%s",m_serverUrl.c_str());
    CCLOG("VersionsManager::VersionsManager==>m_versionUrl:%s",m_versionUrl.c_str());
    
    m_pAssetsManager = new AssetsManager("","","");
    std::string pathToSave = FileUtils::getInstance()->getWritablePath();
    m_pAssetsManager->setVersionFileUrl(m_versionUrl.c_str());
    m_pAssetsManager->setStoragePath(pathToSave.c_str());
    m_pAssetsManager->setConnectionTimeout(3);
    
    UserDefault::getInstance()->setStringForKey(KEY_VERSIONURL,m_versionUrl);
    m_pLoadLayar = NULL;
}

VersionsManager::~VersionsManager(void)
{
}
void VersionsManager::purgeSharedVersionsManager(void)
{
    if (s_sharedVersionsManager)
    {
        delete s_sharedVersionsManager;
        s_sharedVersionsManager = NULL;
    }
}

bool VersionsManager::checkUpdate()
{
    void *_curl;
    
    _curl = curl_easy_init();
    if (! _curl)
    {
        CCLOG("can not init curl");
        return false;
    }
    
    // Clear _version before assign new value.
    std::string _version;
    
    CURLcode res;
    curl_easy_setopt(_curl, CURLOPT_URL, m_versionUrl.c_str());
    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, getVCode);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &_version);
    if (3) curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, 3);
    res = curl_easy_perform(_curl);
    
    if (res != 0)
    {
        CCLOG("can not get version file content, error code is %d", res);
        curl_easy_cleanup(_curl);
        return false;
    }
    
    
    //解析版本号
    vector<string> tokens;
    string server_versionBig;
    string server_versionSmall;
    splitString(_version,tokens,"-");
    if(tokens.size()==2){
        server_versionBig = tokens[0];
        server_versionSmall = tokens[1];
        CCLOG("server_version:%s,%s",server_versionBig.c_str(),server_versionSmall.c_str());
    }
    
    //校验主版本号
    const char* appversionBig = AppLuaApi::getInstance()->AppVersion();
    if (strcmp(server_versionBig.c_str(), appversionBig) >0){
        log("VersionsManager::checkUpdate==> 服务器版本:%s 本地版本:%s", server_versionBig.c_str(), appversionBig);
        AppLuaApi::downloadNewApp(server_versionBig.c_str());
        curl_easy_cleanup(_curl);
        return false;
    }

    
    //校验小版本号
    std::string version = UserDefault::getInstance()->getStringForKey(KEY_CURRENT_VERSION);
    
    if ( version.size() == 0 )
    {
        version = "0";
        //version = string(AppLuaApi::getInstance()->AppVersionCode());
        UserDefault::getInstance()->setStringForKey(KEY_CURRENT_VERSION,version.c_str());
    }
    
    CCLOG("VersionsManager::checkUpdate==>本地小版本号: %s, 服务器小版本号:%s", version.c_str(), server_versionSmall.c_str());
    
    if (version == server_versionSmall)
    {
        curl_easy_cleanup(_curl);

        CCLOG("VersionsManager::checkUpdate==>没有小版本更新");
        // Set resource search path.
        return false;
    }
    
    curl_easy_cleanup(_curl);
    CCLOG("VersionsManager::checkUpdate==>小版本需要更新最新版本号: %s", server_versionSmall.c_str());
    
    return true;

}

void VersionsManager::getUpdateFilesList()
{
    this->showLoading();
    
    HttpRequest* pRequest = new HttpRequest();
    pRequest->setUrl(m_serverUrl.c_str());
    //pRequest->setUrl("http://66.228.33.68/static/slotsfun/universal/140610232842/dict.zip");
    pRequest->setRequestType(HttpRequest::Type::GET);
    //pRequest->setResponseCallback(this, httpresponse_selector(VersionsManager::onHttpRequestCompleted));
    pRequest->setResponseCallback(CC_CALLBACK_2(VersionsManager::onHttpRequestCompleted, this));
    pRequest->setTag("2");
    HttpClient::getInstance()->send(pRequest);
    pRequest->release();
    
}

void VersionsManager::postUpdateAgain()
{
    CCLOG("VersionsManager::postUpdateAgain");
    
    LoadingLayer* loading = (LoadingLayer*)openLoadingLayer();
    loading->initWithAssetsManager(m_pAssetsManager,mDownloadFiles);
    
    Director::getInstance()->getRunningScene()->addChild(loading);
    
}

void VersionsManager::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLOG("%s completed", response->getHttpRequest()->getTag());
    }
    
    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", (int)statusCode, response->getHttpRequest()->getTag());
    
    CCLOG("response code: %d", (int)statusCode);
    
    if (!response->isSucceed())
    {
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_UPDATE_FINISHBACK_EVENT");
        CCLOG("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    mDownloadFiles.clear();
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    size_t size = buffer->size();
    std::string bufferStr(size,'1');
    
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        bufferStr[i] = (*buffer)[i];
    }
    
    rapidjson::Document jsonDoc;
    
    
    if (jsonDoc.Parse<0>(bufferStr.c_str()).HasParseError()) {
        log("read server json file failed because of %s", jsonDoc.GetParseError());
        return;
    }
    
    
    std::string baseurl = jsonDoc[KEY_BASEURL].GetString();
    //baseurl = getIpWithAllName(baseurl);

    
    UserDefault::getInstance()->setStringForKey(KEY_BASEURL,baseurl);
    
    const char* main_version = jsonDoc[KEY_MAINVERSION].GetString();
    const char* appversion = AppLuaApi::getInstance()->AppVersion();
    
    log("VersionsManager::onHttpRequestCompleted==》服务器列表主版本:%s 本地包主版本:%s", main_version, appversion);
    
    if (strcmp(main_version, appversion) >0)
    {
        CCLOG("VersionsManager::onHttpRequestCompleted==》服务器version版本与列表版本不一致！");
        AppLuaApi::downloadNewApp(main_version);
        return;
    }
    
    const rapidjson::Value& res_value = jsonDoc[KEY_RES];

    for (int i=0; i < res_value.Size(); ++i) {
        const rapidjson::Value& value = res_value[i];

        const char* flag = value["flag"].GetString();
        const char* name = value["name"].GetString();
        const char* md5  = value["md5"].GetString();
        
        string savedmd5 = "";
        
        if( strcmp(flag, "0") != 0) {
            
            string fileval = UserDefault::getInstance()->getStringForKey(flag);
            
            std::vector<std::string> filesarray;
            splitString(fileval, filesarray, ",");
            if (filesarray.size()==2) {
                savedmd5 = filesarray[1];
            }
            
        }else{
            savedmd5 = UserDefault::getInstance()->getStringForKey(name);
        }
        
        
        if(strcmp(savedmd5.c_str(), md5) != 0){
            
            if( strcmp(flag, "0") != 0){
                addUserDownload(flag, name, md5);
            }
            else{
                mDownloadFiles.insert(std::make_pair(name, md5));  //添加数据
            }
        }
    }
    std::string dwonloadurl = jsonDoc[KEY_DOWNLOADURL].GetString();
    std::string serverurl = jsonDoc[KEY_SERVERURL].GetString();
    std::string socket_addr = jsonDoc[KEY_SOCKET_ADDR].GetString();
    std::string socket_prot = jsonDoc[KEY_SOCKET_PORT].GetString();

    UserDefault::getInstance()->setStringForKey(KEY_DOWNLOADURL,dwonloadurl);
    UserDefault::getInstance()->setStringForKey(KEY_SERVERURL,serverurl);
    UserDefault::getInstance()->setStringForKey(KEY_SOCKET_ADDR,socket_addr);
    UserDefault::getInstance()->setStringForKey(KEY_SOCKET_PORT,socket_prot);
    
    if (mDownloadFiles.size() > 0 ){
        onLoadLayerLoaded();
    }
    else{
        std::string version = jsonDoc[KEY_VERSION].GetString();

        UserDefault::getInstance()->setStringForKey(KEY_CURRENT_VERSION,version);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_UPDATE_FINISHBACK_EVENT");
    }

}

bool VersionsManager::addUserDownload(const char* flag,const char* name,const char* md5)
{
    std::string filestr = name;
    filestr += ",";
    filestr += md5;
    
    UserDefault::getInstance()->setStringForKey(flag,   filestr);

    return true;
}
void VersionsManager::showLoading()
{

    // create a scene. it's an autorelease object
    auto scene = CCScene::create();
    
    m_pLoadLayar = (LoadingLayer*)openLoadingLayer();
    scene->addChild(m_pLoadLayar);
    
    Director::getInstance()->runWithScene(scene);
    
}

void VersionsManager::onLoadLayerLoaded()
{
    
    // create a scene. it's an autorelease object
    
    m_pLoadLayar->initWithAssetsManager(m_pAssetsManager,mDownloadFiles);
    
}

Node* VersionsManager::openLoadingLayer()
{
    FileUtils::getInstance()->addSearchPath("res/");
    
    NodeLoaderLibrary * pNodeLoadLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary();

    pNodeLoadLibrary->registerNodeLoader("LoadingLayer", LoadingLayerLoader::loader());

    CCBReader* pReader = new CCBReader(pNodeLoadLibrary);
    
    std::string file = "Loading.ccbi";
    
    Node* pNode = pReader->readNodeGraphFromFile(file.c_str());
    
    
    CC_SAFE_DELETE(pReader);
        
    return pNode;
}
