#include "lua_accountManager_manual.hpp"
#include "CCAccountManager.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_manual_accountManager_CCAccountManager_requestFriends(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_requestFriends'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_requestFriends'", nullptr);
            return 0;
        }
        cobj->requestFriends();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:requestFriends",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_requestFriends'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_onHttpRequestCompleted(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_onHttpRequestCompleted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::network::HttpClient* arg0;
        cocos2d::network::HttpResponse* arg1;

        ok &= luaval_to_object<cocos2d::network::HttpClient>(tolua_S, 2, "cc.HttpClient",&arg0);

        ok &= luaval_to_object<cocos2d::network::HttpResponse>(tolua_S, 3, "cc.HttpResponse",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_onHttpRequestCompleted'", nullptr);
            return 0;
        }
        cobj->onHttpRequestCompleted(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:onHttpRequestCompleted",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_onHttpRequestCompleted'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_share(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_share'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 5) 
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        const char* arg3;
        const char* arg4;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "CCAccountManager:share"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "CCAccountManager:share"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "CCAccountManager:share"); arg2 = arg2_tmp.c_str();

        std::string arg3_tmp; ok &= luaval_to_std_string(tolua_S, 5, &arg3_tmp, "CCAccountManager:share"); arg3 = arg3_tmp.c_str();

        std::string arg4_tmp; ok &= luaval_to_std_string(tolua_S, 6, &arg4_tmp, "CCAccountManager:share"); arg4 = arg4_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_share'", nullptr);
            return 0;
        }
        cobj->share(arg0, arg1, arg2, arg3, arg4);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:share",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_share'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_downloadPhoto(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_downloadPhoto'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "CCAccountManager:downloadPhoto"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_downloadPhoto'", nullptr);
            return 0;
        }
        cobj->downloadPhoto(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:downloadPhoto",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_downloadPhoto'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_SystemVersion(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_SystemVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_SystemVersion'", nullptr);
            return 0;
        }
        const char* ret = cobj->SystemVersion();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:SystemVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_SystemVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReport(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReport'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReport'", nullptr);
            return 0;
        }
        cobj->applicationDidFinishLaunchingReport();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:applicationDidFinishLaunchingReport",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReport'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_logIn(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_logIn'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_logIn'", nullptr);
            return 0;
        }
        cobj->logIn();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:logIn",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_logIn'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_applicationDidBecomeActive(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_applicationDidBecomeActive'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_applicationDidBecomeActive'", nullptr);
            return 0;
        }
        cobj->applicationDidBecomeActive();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:applicationDidBecomeActive",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_applicationDidBecomeActive'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_UDID(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_UDID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_UDID'", nullptr);
            return 0;
        }
        const char* ret = cobj->UDID();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:UDID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_UDID'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_postInviteFriends(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_postInviteFriends'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCAccountManager:postInviteFriends");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_postInviteFriends'", nullptr);
            return 0;
        }
        cobj->postInviteFriends(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:postInviteFriends",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_postInviteFriends'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReportCompleted(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReportCompleted'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::network::HttpClient* arg0;
        cocos2d::network::HttpResponse* arg1;

        ok &= luaval_to_object<cocos2d::network::HttpClient>(tolua_S, 2, "cc.HttpClient",&arg0);

        ok &= luaval_to_object<cocos2d::network::HttpResponse>(tolua_S, 3, "cc.HttpResponse",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReportCompleted'", nullptr);
            return 0;
        }
        cobj->applicationDidFinishLaunchingReportCompleted(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:applicationDidFinishLaunchingReportCompleted",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReportCompleted'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_application(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_application'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "CCAccountManager:application"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "CCAccountManager:application"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_application'", nullptr);
            return 0;
        }
        bool ret = cobj->application(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:application",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_application'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_init(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "CCAccountManager:init"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:init",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_getIdfv(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_getIdfv'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_getIdfv'", nullptr);
            return 0;
        }
        const char* ret = cobj->getIdfv();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:getIdfv",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_getIdfv'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_ResVersion(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_ResVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_ResVersion'", nullptr);
            return 0;
        }
        const char* ret = cobj->ResVersion();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:ResVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_ResVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_AppVersion(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_AppVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_AppVersion'", nullptr);
            return 0;
        }
        const char* ret = cobj->AppVersion();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:AppVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_AppVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_getIdfa(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_getIdfa'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_getIdfa'", nullptr);
            return 0;
        }
        const char* ret = cobj->getIdfa();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:getIdfa",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_getIdfa'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_isLogged(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_isLogged'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_isLogged'", nullptr);
            return 0;
        }
        bool ret = cobj->isLogged();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:isLogged",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_isLogged'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_shareText(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_shareText'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "CCAccountManager:shareText"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_shareText'", nullptr);
            return 0;
        }
        cobj->shareText(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:shareText",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_shareText'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_postPhoto(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_postPhoto'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        int arg3;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "CCAccountManager:postPhoto"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "CCAccountManager:postPhoto"); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp, "CCAccountManager:postPhoto"); arg2 = arg2_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "CCAccountManager:postPhoto");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_postPhoto'", nullptr);
            return 0;
        }
        cobj->postPhoto(arg0, arg1, arg2, arg3);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:postPhoto",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_postPhoto'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingWithOptions(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingWithOptions'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingWithOptions'", nullptr);
            return 0;
        }
        cobj->applicationDidFinishLaunchingWithOptions();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:applicationDidFinishLaunchingWithOptions",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingWithOptions'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_logOut(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_logOut'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_logOut'", nullptr);
            return 0;
        }
        cobj->logOut();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:logOut",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_logOut'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_postFBListenerLua(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_postFBListenerLua'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
//        int arg0;
//
//        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "CCAccountManager:postFBListenerLua");
//        if(!ok)
//        {
//            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_postFBListenerLua'", nullptr);
//            return 0;
//        }
//        cobj->postFBListenerLua(arg0);
//        lua_settop(tolua_S, 1);
//        return 1;
        
        int handler = (toluafix_ref_function(tolua_S,2,0));
        cobj->postFBListenerLua(handler);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:postFBListenerLua",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_postFBListenerLua'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_inviteFriends(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_inviteFriends'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_inviteFriends'", nullptr);
            return 0;
        }
        cobj->inviteFriends();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:inviteFriends",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_inviteFriends'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_accountManager_CCAccountManager_purgeSharedAccountManager(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_purgeSharedAccountManager'", nullptr);
            return 0;
        }
        CCAccountManager::purgeSharedAccountManager();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "CCAccountManager:purgeSharedAccountManager",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_purgeSharedAccountManager'.",&tolua_err);
#endif
    return 0;
}
int lua_manual_accountManager_CCAccountManager_showIndicator(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_showIndicator'", nullptr);
            return 0;
        }
        CCAccountManager::showIndicator();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "CCAccountManager:showIndicator",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_showIndicator'.",&tolua_err);
#endif
    return 0;
}
int lua_manual_accountManager_CCAccountManager_hideIndicator(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_hideIndicator'", nullptr);
            return 0;
        }
        CCAccountManager::hideIndicator();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "CCAccountManager:hideIndicator",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_hideIndicator'.",&tolua_err);
#endif
    return 0;
}
int lua_manual_accountManager_CCAccountManager_downloadNewApp(lua_State* tolua_S)
{
    int argc = 0;
    CCAccountManager* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (CCAccountManager*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_accountManager_CCAccountManager_downloadNewApp'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        const char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "CCAccountManager:downloadNewApp"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_downloadNewApp'", nullptr);
            return 0;
        }
        cobj->downloadNewApp(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:downloadNewApp",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_downloadNewApp'.",&tolua_err);
#endif
    
    return 0;

}
int lua_manual_accountManager_CCAccountManager_preloadFinish(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_preloadFinish'", nullptr);
            return 0;
        }
        CCAccountManager::preloadFinish();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "CCAccountManager:preloadFinish",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_preloadFinish'.",&tolua_err);
#endif
    return 0;
}
int lua_manual_accountManager_CCAccountManager_sharedAccountManager(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"CCAccountManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_accountManager_CCAccountManager_sharedAccountManager'", nullptr);
            return 0;
        }
        CCAccountManager* ret = CCAccountManager::sharedAccountManager();
        object_to_luaval<CCAccountManager>(tolua_S, "CCAccountManager",(CCAccountManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "CCAccountManager:sharedAccountManager",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_accountManager_CCAccountManager_sharedAccountManager'.",&tolua_err);
#endif
    return 0;
}
static int lua_manual_accountManager_CCAccountManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (CCAccountManager)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"CCAccountManager",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        CCAccountManager* self = (CCAccountManager*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", nullptr);
#endif
        delete self;
    }
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
    return 0;
#endif
    return 0;
}

int lua_register_manual_accountManager_CCAccountManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"CCAccountManager");
    tolua_cclass(tolua_S,"CCAccountManager","CCAccountManager","",nullptr);

    tolua_beginmodule(tolua_S,"CCAccountManager");
        tolua_function(tolua_S,"requestFriends",lua_manual_accountManager_CCAccountManager_requestFriends);
        tolua_function(tolua_S,"onHttpRequestCompleted",lua_manual_accountManager_CCAccountManager_onHttpRequestCompleted);
        tolua_function(tolua_S,"share",lua_manual_accountManager_CCAccountManager_share);
        tolua_function(tolua_S,"downloadPhoto",lua_manual_accountManager_CCAccountManager_downloadPhoto);
        tolua_function(tolua_S,"SystemVersion",lua_manual_accountManager_CCAccountManager_SystemVersion);
        tolua_function(tolua_S,"applicationDidFinishLaunchingReport",lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReport);
        tolua_function(tolua_S,"logIn",lua_manual_accountManager_CCAccountManager_logIn);
        tolua_function(tolua_S,"applicationDidBecomeActive",lua_manual_accountManager_CCAccountManager_applicationDidBecomeActive);
        tolua_function(tolua_S,"UDID",lua_manual_accountManager_CCAccountManager_UDID);
        tolua_function(tolua_S,"postInviteFriends",lua_manual_accountManager_CCAccountManager_postInviteFriends);
        tolua_function(tolua_S,"applicationDidFinishLaunchingReportCompleted",lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingReportCompleted);
        tolua_function(tolua_S,"application",lua_manual_accountManager_CCAccountManager_application);
        tolua_function(tolua_S,"init",lua_manual_accountManager_CCAccountManager_init);
        tolua_function(tolua_S,"getIdfv",lua_manual_accountManager_CCAccountManager_getIdfv);
        tolua_function(tolua_S,"ResVersion",lua_manual_accountManager_CCAccountManager_ResVersion);
        tolua_function(tolua_S,"AppVersion",lua_manual_accountManager_CCAccountManager_AppVersion);
        tolua_function(tolua_S,"getIdfa",lua_manual_accountManager_CCAccountManager_getIdfa);
        tolua_function(tolua_S,"isLogged",lua_manual_accountManager_CCAccountManager_isLogged);
        tolua_function(tolua_S,"shareText",lua_manual_accountManager_CCAccountManager_shareText);
        tolua_function(tolua_S,"postPhoto",lua_manual_accountManager_CCAccountManager_postPhoto);
        tolua_function(tolua_S,"applicationDidFinishLaunchingWithOptions",lua_manual_accountManager_CCAccountManager_applicationDidFinishLaunchingWithOptions);
        tolua_function(tolua_S,"logOut",lua_manual_accountManager_CCAccountManager_logOut);
        tolua_function(tolua_S,"postFBListenerLua",lua_manual_accountManager_CCAccountManager_postFBListenerLua);
        tolua_function(tolua_S,"inviteFriends",lua_manual_accountManager_CCAccountManager_inviteFriends);
        tolua_function(tolua_S,"purgeSharedAccountManager", lua_manual_accountManager_CCAccountManager_purgeSharedAccountManager);
        tolua_function(tolua_S,"showIndicator", lua_manual_accountManager_CCAccountManager_showIndicator);
        tolua_function(tolua_S,"hideIndicator", lua_manual_accountManager_CCAccountManager_hideIndicator);
        tolua_function(tolua_S,"downloadNewApp", lua_manual_accountManager_CCAccountManager_downloadNewApp);
        tolua_function(tolua_S,"preloadFinish", lua_manual_accountManager_CCAccountManager_preloadFinish);
        tolua_function(tolua_S,"sharedAccountManager", lua_manual_accountManager_CCAccountManager_sharedAccountManager);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(CCAccountManager).name();
    g_luaType[typeName] = "CCAccountManager";
    g_typeCast["CCAccountManager"] = "CCAccountManager";
    return 1;
}
TOLUA_API int register_all_manual_accountManager(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_manual_accountManager_CCAccountManager(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

