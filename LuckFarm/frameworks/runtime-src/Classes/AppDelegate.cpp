#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "lua_module_register.h"
#include "VersionsManager.h"
#include "ConfigParser.h"
#include "AppLuaApi.h"


//#include "lua_cocos2dx_pluginx_auto.hpp"
//#include "lua_pluginx_manual_callback.h"
//#include "lua_pluginx_manual_protocols.h"
#include "lua_cocos2dx_app_notification.hpp"
#include "lua_AppLuaApi_auto.hpp"
#include "filter/lua_Filter_auto.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "anysdkbindings.h"
#include "anysdk_manual_bindings.h"
#include "AgentManager.h"
#include "ProtocolUser.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "luabinding/cocos2dx_extra_ios_iap_luabinding.h"
//#include "LuaIntergrateAppsFlyer.h"
#include "lua_cocos2dx_pluginx_auto.hpp"
#include "lua_pluginx_manual_callback.h"
#include "lua_pluginx_manual_protocols.h"
#endif



//#include "filter/Filter.h"
#include<iostream>
#include<string>
#include<list>
#include <fstream>
#include <sys/timeb.h>
//#include "filter/FilterUtils.h"

#include "LogoScene.h"




//protobuf-gen-lua 引用的pb.c
extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
    int luaopen_pb (lua_State *L);
}
//luabuffer.c 主要是为lua提供二进制数据操作
extern "C"{
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
    int luaopen_iobuffer (lua_State *L);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #define APP_PUBLISH   0
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #define APP_PUBLISH   0
#endif



using namespace CocosDenshion;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
using namespace anysdk::framework;
#endif


USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
{
    
    CCLOG("AppDelegate::AppDelegate==》CC_PLATFORM_MAC:%d",CC_TARGET_PLATFORM);
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    extern void package_quick_register();
	package_quick_register();
	return 0; //flag for packages manager
}
void AppDelegate::showLogo(){
    //LOGO
    LogoScene * scene = LogoScene::create();
    scene->setDelegate(this);
    Director::getInstance()->runWithScene(scene);
    
}

void AppDelegate::showGameScene(){
    //不更新
    postUpdateImpl();
    
//    if (VersionsManager::sharedVersionsManager()->checkUpdate()){
//        
//        Director::getInstance()->getEventDispatcher()->addCustomEventListener(
//                                                                              "APP_UPDATE_FINISHBACK_EVENT", std::bind(&AppDelegate::postUpdate, this, std::placeholders::_1));
//        
//        
//        VersionsManager::sharedVersionsManager()->getUpdateFilesList();
//    }
//    else{
//        postUpdateImpl();
//    }

}

bool AppDelegate::applicationDidFinishLaunching()
{
    // set default FPS
    Director::getInstance()->setAnimationInterval(1.0 / 60.0f);
    cocos2d::Device::setKeepScreenOn(true);
    
    this->initWindow();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    this->showLogo();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    this->showGameScene();
#endif
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_ENTER_BACKGROUND_EVENT");
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("APP_ENTER_FOREGROUND_EVENT");
    
// #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//     AgentManager * mAgent =  AgentManager::getInstance();
//     ProtocolUser * user = mAgent->getUserPlugin();
//     if(!user || !user->isFunctionSupported("pause")){
//         return ;
//     }else{
//         user->callFuncWithParam("pause", NULL);
//     }
// #endif
    
}

void AppDelegate::setLaunchMode(int mode)
{
    _launchMode = mode;
}

void AppDelegate::initWindow()
{
    Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    float CON_WIDTH = 640;//960;
    float CON_HEIGHT = 1136;//640;
    
    float scaleX = 1.0;
    float scaleY = 1.0;
    
    if ((size.width == 1024 && size.height == 768)
        || (size.width == 2048 && size.height == 1536)){
        
        CON_WIDTH = 1024;
        CON_HEIGHT = 768;
        
        scaleX = size.width/1024;
        scaleY = size.height/768;
    }
    else{
        scaleX = size.width/CON_WIDTH;
        scaleY = size.height/CON_HEIGHT;
    }
    
    float scale = scaleY;
    CON_WIDTH = size.width / scale;
    
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(CON_WIDTH, CON_HEIGHT, ResolutionPolicy::NO_BORDER);
}

void AppDelegate::postUpdate(cocos2d::EventCustom* event)
{
    this->postUpdateImpl();
}

void AppDelegate::postUpdateImpl()
{
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("APP_UPDATE_FINISHBACK_EVENT");
    
    // register lua module
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCLOG("AppDelegate::postUpdateImpl==>开始加载anysdk");
    
    LuaStack* stack = engine->getLuaStack();
    lua_getglobal(stack->getLuaState(), "_G");
    tolua_anysdk_open(stack->getLuaState());
    tolua_anysdk_manual_open(stack->getLuaState());
    lua_pop(stack->getLuaState(), 1);
    CCLOG("AppDelegate::postUpdateImpl==>加载anysdk end");
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    register_all_pluginx_protocols(L);
    register_all_pluginx_manual_callback(L);
    register_all_pluginx_manual_protocols(L);
#endif
    
    register_all_packages();
    register_all_app_notification_bindings(L);

    
    //lua使用protobuf
    luaopen_pb(L);
    
    //lua的iobuffer库扩展
    luaopen_iobuffer(L);
    
    //system api
    register_all_AppLuaApi(L);
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //tolua_LuaIntergrateAppsFlyer_open(L);
#endif
    
    std::vector<std::string> paths;
    
    const char* appversion = AppLuaApi::getInstance()->AppVersion();
    std::string wPath =FileUtils::getInstance()->getWritablePath();
    std::string topdir = wPath;
    topdir += appversion;
    topdir += "/";
    
    std::string userdownload = wPath;
    userdownload += "userdownload/";
    
    paths.push_back(topdir);
    paths.push_back(userdownload);
    paths.push_back(wPath);
    paths.push_back("");
    FileUtils::getInstance()->setSearchPaths(paths);
    
    
    //读取自动更新屏蔽字库
    //初始化屏蔽字库
//    string fullPathAuto = FileUtils::getInstance()->fullPathForFilename("res/badwordadd/BadWordAdd.txt");
//    bool isExit2 = FileUtils::getInstance()->isFileExist(fullPathAuto);
//    CCLOG("fullPathAuto:%s===%d",fullPathAuto.c_str(),isExit2);
//    if(isExit2){
//        Filter::init(Filter::NORMAL,fullPathAuto.c_str());
//    }
    
//#if ANYSDK_DEFINE > 0
//    lua_getglobal(stack->getLuaState(), "_G");
//    tolua_anysdk_open(stack->getLuaState());
//    tolua_anysdk_manual_open(stack->getLuaState());
//    lua_pop(stack->getLuaState(), 1);
//#endif
    
    //register custom function
    //LuaStack* stack = engine->getLuaStack();
    //register_custom_function(stack->getLuaState());
// 发布正式版本 打开
//#if (COCOS2D_DEBUG < 1)
//    LuaStack* stack = engine->getLuaStack();
//
//    //stack->setXXTEAKeyAndSign("2dxLua", strlen("2dxLua"), "XXTEA", strlen("XXTEA"));
//    stack->loadChunksFromZIP("scripts.zip");
//    stack->executeString("require 'main'");
//    return;
//    
//#endif

#if APP_PUBLISH == 1
    LuaStack* luastack = engine->getLuaStack();
    luastack->setXXTEAKeyAndSign("ZHUANYAN", strlen("ZHUANYAN"), "SLOTS_LOBBY", strlen("SLOTS_LOBBY"));
    luastack->loadChunksFromZIP("scripts.zip");
    luastack->executeString("require 'main'");
    return;
#endif

    
#if (COCOS2D_DEBUG > 0) && (CC_TARGET_PLATFORM != CC_PLATFORM_WP8) && CC_USE_RUNTIME
    // NOTE:Please don't remove this call if you want to debug with Cocos Code IDE
    if (_launchMode)
    {
        startRuntime();
    }
    else
    {
        engine->executeScriptFile(ConfigParser::getInstance()->getEntryFile().c_str());
    }
#else
    engine->executeScriptFile(ConfigParser::getInstance()->getEntryFile().c_str());
#endif
    
    
}
