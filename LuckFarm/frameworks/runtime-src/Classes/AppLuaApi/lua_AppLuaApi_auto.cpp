#include "lua_AppLuaApi_auto.hpp"
#include "AppLuaApi.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

int lua_AppLuaApi_AppLuaApi_postFBListenerLua(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_postFBListenerLua'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        //        int arg0;
        //
        //        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "AppLuaApi:postFBListenerLua");
        //        if(!ok)
        //        {
        //            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_postFBListenerLua'", nullptr);
        //            return 0;
        //        }
        //        cobj->postFBListenerLua(arg0);
        //        lua_settop(tolua_S, 1);
        //        return 1;
        int handler = (toluafix_ref_function(tolua_S,2,0));
        cobj->postFBListenerLua(handler);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:postFBListenerLua",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_postFBListenerLua'.",&tolua_err);
#endif
    
    return 0;
}
int lua_AppLuaApi_AppLuaApi_downloadPhoto(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_downloadPhoto'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi:downloadPhoto"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_downloadPhoto'", nullptr);
            return 0;
        }
        cobj->downloadPhoto(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:downloadPhoto",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_downloadPhoto'.",&tolua_err);
#endif
    
    return 0;
}
int lua_AppLuaApi_AppLuaApi_SystemVersion(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_SystemVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_SystemVersion'", nullptr);
            return 0;
        }
        const char* ret = cobj->SystemVersion();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:SystemVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_SystemVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_AppLuaApi_AppLuaApi_ResVersion(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_ResVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_ResVersion'", nullptr);
            return 0;
        }
        const char* ret = cobj->ResVersion();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:ResVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_ResVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_AppLuaApi_AppLuaApi_AppVersion(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_AppVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_AppVersion'", nullptr);
            return 0;
        }
        const char* ret = cobj->AppVersion();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:AppVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_AppVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_AppLuaApi_AppLuaApi_purgeInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_purgeInstance'", nullptr);
            return 0;
        }
        AppLuaApi::purgeInstance();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:purgeInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_purgeInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_getInstance'", nullptr);
            return 0;
        }
        AppLuaApi* ret = AppLuaApi::getInstance();
        object_to_luaval<AppLuaApi>(tolua_S, "AppLuaApi",(AppLuaApi*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_getInstance'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_showIndicator(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_showIndicator'", nullptr);
            return 0;
        }
        AppLuaApi::showIndicator();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:showIndicator",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_showIndicator'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_hideIndicator(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_hideIndicator'", nullptr);
            return 0;
        }
        AppLuaApi::hideIndicator();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:hideIndicator",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_hideIndicator'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_openLLPayForPayWith(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp;
        ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi::openLLPayForPayWith");
        arg0 = arg0_tmp.c_str();
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_openLLPayForPayWith'", nullptr);
            return 0;
        }
        AppLuaApi::openLLPayForPayWith(arg0);
        lua_settop(tolua_S, 1);
        
        
        //    argc = lua_gettop(tolua_S) - 1;
        //
        //    if (argc == 0)
        //    {
        //        if(!ok)
        //        {
        //            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_downloadNewApp'", nullptr);
        //            return 0;
        //        }
        //        AppLuaApi::downloadNewApp();
        //        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:openLLPayForPayWith",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_openLLPayForPayWith'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_gotoQQLogin(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_gotoQQLogin'", nullptr);
            return 0;
        }
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        AppLuaApi::gotoQQLogin();
        //#endif
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:gotoQQLogin",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_gotoQQLogin'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_gotoWeiXinLogin(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_gotoWeiXinLogin'", nullptr);
            return 0;
        }
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        AppLuaApi::gotoWeiXinLogin();
        //#endif
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:gotoWeiXinLogin",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_gotoWeiXinLogin'.",&tolua_err);
#endif
    return 0;
}


int lua_AppLuaApi_AppLuaApi_stringToUtf8(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp;
        ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi::stringToUtf8");
        arg0 = arg0_tmp.c_str();
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_stringToUtf8'", nullptr);
            return 0;
        }

        const char* ret = AppLuaApi::stringToUtf8(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);

//        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:stringToUtf8",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_stringToUtf8'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_utf8ToString(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp;
        ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi::utf8ToString");
        arg0 = arg0_tmp.c_str();
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_utf8ToString'", nullptr);
            return 0;
        }

        const char* ret = AppLuaApi::utf8ToString(arg0);
        tolua_pushstring(tolua_S,(const char*)ret);

//        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:utf8ToString",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_utf8ToString'.",&tolua_err);
#endif
    return 0;
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
int lua_AppLuaApi_AppLuaApi_setIsNeedShowWait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        bool arg0;
        std::string arg0_tmp;
        ok &= luaval_to_boolean(tolua_S, 2, &arg0, "AppLuaApi::setIsNeedShowWait");
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_setIsNeedShowWait'", nullptr);
            return 0;
        }
        AppLuaApi::setIsNeedShowWait(arg0);
        lua_settop(tolua_S, 1);
        return 0;
    }
    
    
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:setIsNeedShowWait",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_setIsNeedShowWait'.",&tolua_err);
#endif
    return 0;
}

#endif


int lua_AppLuaApi_AppLuaApi_setGameOrientation(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_setGameOrientation'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi:setGameOrientation"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_setGameOrientation'", nullptr);
            return 0;
        }
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                cobj->setGameOrientation(arg0);
        #endif
        
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:setGameOrientation",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_setGameOrientation'.",&tolua_err);
#endif
    
    return 0;
}
int lua_AppLuaApi_AppLuaApi_setStatusBar(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_setStatusBar'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi:setStatusBar"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_setStatusBar'", nullptr);
            return 0;
        }
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            cobj->setStatusBar(arg0);
        #endif
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            cobj->setStatusBar(arg0);
        #endif
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:setStatusBar",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_setStatusBarn'.",&tolua_err);
#endif
    
    return 0;
}
int lua_AppLuaApi_AppLuaApi_AppVersionCode(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_AppVersionCode'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_AppVersionCode'", nullptr);
            return 0;
        }
        const char* ret = cobj->AppVersionCode();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:AppVersionCode",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_AppVersionCode'.",&tolua_err);
#endif
    
    return 0;
}

int lua_AppLuaApi_AppLuaApi_UDID(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_UDID'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_UDID'", nullptr);
            return 0;
        }
        const char* ret = cobj->UDID();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:UDID",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_UDID'.",&tolua_err);
#endif
    
    return 0;
}

static int lua_AppLuaApi_AppLuaApi_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AppLuaApi)");
    return 0;
}

int lua_AppLuaApi_AppLuaApi_downloadNewApp(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp;
        ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi::downloadNewApp");
        arg0 = arg0_tmp.c_str();
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_downloadNewApp'", nullptr);
            return 0;
        }
        AppLuaApi::downloadNewApp(arg0);
        lua_settop(tolua_S, 1);
    
    
//    argc = lua_gettop(tolua_S) - 1;
//    
//    if (argc == 0)
//    {
//        if(!ok)
//        {
//            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_downloadNewApp'", nullptr);
//            return 0;
//        }
//        AppLuaApi::downloadNewApp();
//        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:downloadNewApp",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_downloadNewApp'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_cryptorToolsToRSA(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_cryptorToolsToRSA'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi:cryptorToolsToRSA"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_cryptorToolsToRSA'", nullptr);
            return 0;
        }
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            const char* ret = cobj->cryptorToolsToRSA(arg0);
            tolua_pushstring(tolua_S,(const char*)ret);
        #endif
        
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:cryptorToolsToRSA",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_cryptorToolsToRSA'.",&tolua_err);
#endif
    
    return 0;
}


int lua_AppLuaApi_AppLuaApi_encryptWithRsa(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_encryptWithRsa'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi:encryptWithRsa"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_encryptWithRsa'", nullptr);
            return 0;
        }
        cobj->encryptWithRsa(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:encryptWithRsa",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_encryptWithRsa'.",&tolua_err);
#endif
    
    return 0;
}

int lua_AppLuaApi_AppLuaApi_app_to_call(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_app_to_call'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi:app_to_call"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_app_to_call'", nullptr);
            return 0;
        }

        cobj->app_to_call(arg0);
        lua_settop(tolua_S, 1);

        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:app_to_call",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_app_to_call'.",&tolua_err);
#endif
    
    return 0;
}


int lua_AppLuaApi_AppLuaApi_shareWeChatFriend(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_shareWeChatFriend'", nullptr);
            return 0;
        }
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            AppLuaApi::shareWeChatFriend();
        //#endif
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:shareWeChatFriend",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_shareWeChatFriend'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_shareWeChatFriendQuan(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_shareWeChatFriendQuan'", nullptr);
            return 0;
        }
       // #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            AppLuaApi::shareWeChatFriendQuan();
       // #endif
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:shareWeChatFriendQuan",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_shareWeChatFriendQuan'.",&tolua_err);
#endif
    return 0;
}

int lua_AppLuaApi_AppLuaApi_shareQQFriend(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_shareQQFriend'", nullptr);
            return 0;
        }
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        AppLuaApi::shareQQFriend();
//#endif
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppLuaApi:shareQQFriend",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_shareQQFriend'.",&tolua_err);
#endif
    return 0;
}


int lua_AppLuaApi_AppLuaApi_openPhotoAlbum(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_openPhotoAlbum'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_openPhotoAlbum'", nullptr);
            return 0;
        }
        cobj->openPhotoAlbum();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:openPhotoAlbum",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_openPhotoAlbum'.",&tolua_err);
#endif
    
    return 0;
}

int lua_AppLuaApi_AppLuaApi_openCamera(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_openCamera'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_openCamera'", nullptr);
            return 0;
        }
        cobj->openCamera();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:openCamera",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_openCamera'.",&tolua_err);
#endif
    
    return 0;
}

int lua_AppLuaApi_AppLuaApi_openURL(lua_State* tolua_S)
{
    int argc = 0;
    AppLuaApi* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppLuaApi",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (AppLuaApi*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_AppLuaApi_AppLuaApi_openURL'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppLuaApi:openURL"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_AppLuaApi_AppLuaApi_openURL'", nullptr);
            return 0;
        }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        cobj->openURL(arg0);
        lua_settop(tolua_S, 1);
#endif
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppLuaApi:openURL",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AppLuaApi_AppLuaApi_openURL'.",&tolua_err);
#endif
    
    return 0;
}


int lua_register_AppLuaApi_AppLuaApi(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"AppLuaApi");
    tolua_cclass(tolua_S,"AppLuaApi","AppLuaApi","",nullptr);

    tolua_beginmodule(tolua_S,"AppLuaApi");
    tolua_function(tolua_S,"postFBListenerLua",lua_AppLuaApi_AppLuaApi_postFBListenerLua);
    tolua_function(tolua_S,"downloadPhoto",lua_AppLuaApi_AppLuaApi_downloadPhoto);
    tolua_function(tolua_S,"SystemVersion",lua_AppLuaApi_AppLuaApi_SystemVersion);
    tolua_function(tolua_S,"ResVersion",lua_AppLuaApi_AppLuaApi_ResVersion);
    tolua_function(tolua_S,"AppVersion",lua_AppLuaApi_AppLuaApi_AppVersion);
    tolua_function(tolua_S,"purgeInstance", lua_AppLuaApi_AppLuaApi_purgeInstance);
    tolua_function(tolua_S,"getInstance", lua_AppLuaApi_AppLuaApi_getInstance);
    tolua_function(tolua_S,"showIndicator", lua_AppLuaApi_AppLuaApi_showIndicator);
    tolua_function(tolua_S,"hideIndicator", lua_AppLuaApi_AppLuaApi_hideIndicator);
    
    
//    tolua_function(tolua_S,"gotoLoginVC", lua_AppLuaApi_AppLuaApi_gotoLoginVC);
//    tolua_function(tolua_S, "gotoRegisterVC", lua_AppLuaApi_AppLuaApi_gotoRegisterVC),
    tolua_function(tolua_S, "openLLPayForPayWith", lua_AppLuaApi_AppLuaApi_openLLPayForPayWith),
    tolua_function(tolua_S, "gotoQQLogin", lua_AppLuaApi_AppLuaApi_gotoQQLogin),
    tolua_function(tolua_S, "gotoWeiXinLogin", lua_AppLuaApi_AppLuaApi_gotoWeiXinLogin),
    tolua_function(tolua_S,"stringToUtf8",lua_AppLuaApi_AppLuaApi_stringToUtf8);
    tolua_function(tolua_S,"utf8ToString",lua_AppLuaApi_AppLuaApi_utf8ToString);
    
    tolua_function(tolua_S, "shareWeChatFriend", lua_AppLuaApi_AppLuaApi_shareWeChatFriend),
    tolua_function(tolua_S, "shareWeChatFriendQuan", lua_AppLuaApi_AppLuaApi_shareWeChatFriendQuan),
    tolua_function(tolua_S, "shareQQFriend", lua_AppLuaApi_AppLuaApi_shareQQFriend),
    

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    tolua_function(tolua_S,"setIsNeedShowWait", lua_AppLuaApi_AppLuaApi_setIsNeedShowWait);
    #endif
    tolua_function(tolua_S,"setGameOrientation", lua_AppLuaApi_AppLuaApi_setGameOrientation);
    tolua_function(tolua_S,"setStatusBar", lua_AppLuaApi_AppLuaApi_setStatusBar);
    tolua_function(tolua_S,"AppVersionCode", lua_AppLuaApi_AppLuaApi_AppVersionCode);
    tolua_function(tolua_S,"UDID",lua_AppLuaApi_AppLuaApi_UDID);
    tolua_function(tolua_S,"downloadNewApp",lua_AppLuaApi_AppLuaApi_downloadNewApp);
    tolua_function(tolua_S,"cryptorToolsToRSA",lua_AppLuaApi_AppLuaApi_cryptorToolsToRSA);
    tolua_function(tolua_S,"encryptWithRsa",lua_AppLuaApi_AppLuaApi_encryptWithRsa);
    tolua_function(tolua_S,"app_to_call",lua_AppLuaApi_AppLuaApi_app_to_call);
    tolua_function(tolua_S,"openPhotoAlbum",lua_AppLuaApi_AppLuaApi_openPhotoAlbum);
    tolua_function(tolua_S,"openCamera",lua_AppLuaApi_AppLuaApi_openCamera);
    tolua_function(tolua_S,"openURL",lua_AppLuaApi_AppLuaApi_openURL);
    
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(AppLuaApi).name();
    g_luaType[typeName] = "AppLuaApi";
    g_typeCast["AppLuaApi"] = "AppLuaApi";
    return 1;
}
TOLUA_API int register_all_AppLuaApi(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_AppLuaApi_AppLuaApi(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

