#include "lua_cocos2dx_app_notification.hpp"
#include "AppNotification.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_app_notification_bindings_AppNotification_RegisterForRemoteNotificationTypes(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_RegisterForRemoteNotificationTypes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_RegisterForRemoteNotificationTypes'", nullptr);
            return 0;
        }
        bool ret = cobj->RegisterForRemoteNotificationTypes();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:RegisterForRemoteNotificationTypes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_RegisterForRemoteNotificationTypes'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_cancelAllLocalNotifications(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_cancelAllLocalNotifications'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_cancelAllLocalNotifications'", nullptr);
            return 0;
        }
        cobj->cancelAllLocalNotifications();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:cancelAllLocalNotifications",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_cancelAllLocalNotifications'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_DidReceiveLocalNotification(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_DidReceiveLocalNotification'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppNotification:DidReceiveLocalNotification"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_DidReceiveLocalNotification'", nullptr);
            return 0;
        }
        cobj->DidReceiveLocalNotification(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:DidReceiveLocalNotification",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_DidReceiveLocalNotification'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_RegisterLocalNotification(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_RegisterLocalNotification'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppNotification:RegisterLocalNotification"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "AppNotification:RegisterLocalNotification"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_RegisterLocalNotification'", nullptr);
            return 0;
        }
        cobj->RegisterLocalNotification(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:RegisterLocalNotification",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_RegisterLocalNotification'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_GetTimeByString(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_GetTimeByString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppNotification:GetTimeByString"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_GetTimeByString'", nullptr);
            return 0;
        }
        double ret = cobj->GetTimeByString(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:GetTimeByString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_GetTimeByString'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_DidRegisterForRemoteNotificationWithDeviceToken(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_DidRegisterForRemoteNotificationWithDeviceToken'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppNotification:DidRegisterForRemoteNotificationWithDeviceToken"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_DidRegisterForRemoteNotificationWithDeviceToken'", nullptr);
            return 0;
        }
        cobj->DidRegisterForRemoteNotificationWithDeviceToken(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:DidRegisterForRemoteNotificationWithDeviceToken",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_DidRegisterForRemoteNotificationWithDeviceToken'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_DidFailToRegisterForRemoteNotificationWithError(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_DidFailToRegisterForRemoteNotificationWithError'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "AppNotification:DidFailToRegisterForRemoteNotificationWithError");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_DidFailToRegisterForRemoteNotificationWithError'", nullptr);
            return 0;
        }
        cobj->DidFailToRegisterForRemoteNotificationWithError(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:DidFailToRegisterForRemoteNotificationWithError",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_DidFailToRegisterForRemoteNotificationWithError'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_canceLoacalNotification(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_canceLoacalNotification'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "AppNotification:canceLoacalNotification"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_canceLoacalNotification'", nullptr);
            return 0;
        }
        cobj->canceLoacalNotification(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:canceLoacalNotification",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_canceLoacalNotification'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_GetDeviceToken(lua_State* tolua_S)
{
    int argc = 0;
    AppNotification* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (AppNotification*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_app_notification_bindings_AppNotification_GetDeviceToken'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_GetDeviceToken'", nullptr);
            return 0;
        }
        const char* ret = cobj->GetDeviceToken();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "AppNotification:GetDeviceToken",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_GetDeviceToken'.",&tolua_err);
#endif

    return 0;
}
int lua_app_notification_bindings_AppNotification_sharedAppNotification(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"AppNotification",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_app_notification_bindings_AppNotification_sharedAppNotification'", nullptr);
            return 0;
        }
        AppNotification* ret = AppNotification::sharedAppNotification();
        object_to_luaval<AppNotification>(tolua_S, "AppNotification",(AppNotification*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "AppNotification:sharedAppNotification",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_app_notification_bindings_AppNotification_sharedAppNotification'.",&tolua_err);
#endif
    return 0;
}
static int lua_app_notification_bindings_AppNotification_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AppNotification)");
    return 0;
}

int lua_register_app_notification_bindings_AppNotification(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"AppNotification");
    tolua_cclass(tolua_S,"AppNotification","AppNotification","",nullptr);

    tolua_beginmodule(tolua_S,"AppNotification");
        tolua_function(tolua_S,"RegisterForRemoteNotificationTypes",lua_app_notification_bindings_AppNotification_RegisterForRemoteNotificationTypes);
        tolua_function(tolua_S,"cancelAllLocalNotifications",lua_app_notification_bindings_AppNotification_cancelAllLocalNotifications);
        tolua_function(tolua_S,"DidReceiveLocalNotification",lua_app_notification_bindings_AppNotification_DidReceiveLocalNotification);
        tolua_function(tolua_S,"RegisterLocalNotification",lua_app_notification_bindings_AppNotification_RegisterLocalNotification);
        tolua_function(tolua_S,"GetTimeByString",lua_app_notification_bindings_AppNotification_GetTimeByString);
        tolua_function(tolua_S,"DidRegisterForRemoteNotificationWithDeviceToken",lua_app_notification_bindings_AppNotification_DidRegisterForRemoteNotificationWithDeviceToken);
        tolua_function(tolua_S,"DidFailToRegisterForRemoteNotificationWithError",lua_app_notification_bindings_AppNotification_DidFailToRegisterForRemoteNotificationWithError);
        tolua_function(tolua_S,"canceLoacalNotification",lua_app_notification_bindings_AppNotification_canceLoacalNotification);
        tolua_function(tolua_S,"GetDeviceToken",lua_app_notification_bindings_AppNotification_GetDeviceToken);
        tolua_function(tolua_S,"sharedAppNotification", lua_app_notification_bindings_AppNotification_sharedAppNotification);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(AppNotification).name();
    g_luaType[typeName] = "AppNotification";
    g_typeCast["AppNotification"] = "AppNotification";
    return 1;
}
TOLUA_API int register_all_app_notification_bindings(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_app_notification_bindings_AppNotification(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

