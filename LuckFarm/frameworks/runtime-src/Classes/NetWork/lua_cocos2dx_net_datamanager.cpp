
#include "lua_cocos2dx_net_datamanager.hpp"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "NetDataManager.h"


int lua_net_datamanager_bindings_NetDataManager_post(lua_State* tolua_S)
{
    int argc = 0;
    NetDataManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (NetDataManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_net_datamanager_bindings_NetDataManager_post'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "NetDataManager:post"); arg0 = (char*)arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_net_datamanager_bindings_NetDataManager_post'", nullptr);
            return 0;
        }
        cobj->post(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetDataManager:post",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_net_datamanager_bindings_NetDataManager_post'.",&tolua_err);
#endif

    return 0;
}
int lua_net_datamanager_bindings_NetDataManager_buildXMLData(lua_State* tolua_S)
{
    int argc = 0;
    NetDataManager* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (NetDataManager*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_net_datamanager_bindings_NetDataManager_buildXMLData'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "NetDataManager:buildXMLData"); arg0 = (char*)arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_net_datamanager_bindings_NetDataManager_buildXMLData'", nullptr);
            return 0;
        }
        cobj->buildXMLData(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetDataManager:buildXMLData",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_net_datamanager_bindings_NetDataManager_buildXMLData'.",&tolua_err);
#endif
    
    return 0;
}
int lua_net_datamanager_bindings_NetDataManager_postRSA(lua_State* tolua_S)
{
    int argc = 0;
    NetDataManager* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (NetDataManager*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_net_datamanager_bindings_NetDataManager_postRSA'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "NetDataManager:postRSA"); arg0 = (char*)arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_net_datamanager_bindings_NetDataManager_postRSA'", nullptr);
            return 0;
        }
        cobj->postRSA(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetDataManager:postRSA",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_net_datamanager_bindings_NetDataManager_postRSA'.",&tolua_err);
#endif
    
    return 0;
}
int lua_net_datamanager_bindings_NetDataManager_postUpdateNotice(lua_State* tolua_S)
{
    int argc = 0;
    NetDataManager* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (NetDataManager*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_net_datamanager_bindings_NetDataManager_postUpdateNotice'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "NetDataManager:postUpdateNotice"); arg0 = (char*)arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_net_datamanager_bindings_NetDataManager_postUpdateNotice'", nullptr);
            return 0;
        }
        cobj->postUpdateNotice(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetDataManager:postUpdateNotice",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_net_datamanager_bindings_NetDataManager_postUpdateNotice'.",&tolua_err);
#endif
    
    return 0;
}
int lua_net_datamanager_bindings_NetDataManager_postListenerLua(lua_State* tolua_S)
{
    int argc = 0;
    NetDataManager* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (NetDataManager*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_net_datamanager_bindings_NetDataManager_postFBListenerLua'", nullptr);
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
        //            tolua_error(tolua_S,"invalid arguments in function 'lua_CCAccountManager_CCAccountManager_postFBListenerLua'", nullptr);
        //            return 0;
        //        }
        //        cobj->postFBListenerLua(arg0);
        //
        LUA_FUNCTION listener = (  toluafix_ref_function(tolua_S,2,0));
        cobj->postListenerLua(listener);
        
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "CCAccountManager:postFBListenerLua",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_CCAccountManager_CCAccountManager_postFBListenerLua'.",&tolua_err);
#endif
    
    return 0;
}

int lua_net_datamanager_bindings_NetDataManager_purgeSharedNetDataManager(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"NetDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_net_datamanager_bindings_NetDataManager_purgeSharedNetDataManager'", nullptr);
            return 0;
        }
        NetDataManager::purgeSharedNetDataManager();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "NetDataManager:purgeSharedNetDataManager",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_net_datamanager_bindings_NetDataManager_purgeSharedNetDataManager'.",&tolua_err);
#endif
    return 0;
}
int lua_net_datamanager_bindings_NetDataManager_sharedNetDataManager(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"NetDataManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_net_datamanager_bindings_NetDataManager_sharedNetDataManager'", nullptr);
            return 0;
        }
        NetDataManager* ret = NetDataManager::sharedNetDataManager();
        object_to_luaval<NetDataManager>(tolua_S, "NetDataManager",(NetDataManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "NetDataManager:sharedNetDataManager",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_net_datamanager_bindings_NetDataManager_sharedNetDataManager'.",&tolua_err);
#endif
    return 0;
}



int lua_net_datamanager_bindings_NetDataManager_postJackpots(lua_State* tolua_S)
{
    int argc = 0;
    NetDataManager* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"NetDataManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (NetDataManager*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_net_datamanager_bindings_NetDataManager_postJackpots'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        char* arg0;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "NetDataManager:post"); arg0 = (char*)arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_net_datamanager_bindings_NetDataManager_postJackpots'", nullptr);
            return 0;
        }
        cobj->postJackpots(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "NetDataManager:post",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_net_datamanager_bindings_NetDataManager_postJackpots'.",&tolua_err);
#endif
    
    return 0;
}


static int lua_net_datamanager_bindings_NetDataManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (NetDataManager)");
    return 0;
}

int lua_register_net_datamanager_bindings_NetDataManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"NetDataManager");
    tolua_cclass(tolua_S,"NetDataManager","NetDataManager","",nullptr);

    tolua_beginmodule(tolua_S,"NetDataManager");
        tolua_function(tolua_S,"post",lua_net_datamanager_bindings_NetDataManager_post);
        tolua_function(tolua_S,"buildXMLData",lua_net_datamanager_bindings_NetDataManager_buildXMLData);
        tolua_function(tolua_S,"postRSA",lua_net_datamanager_bindings_NetDataManager_postRSA);
        tolua_function(tolua_S,"postUpdateNotice",lua_net_datamanager_bindings_NetDataManager_postUpdateNotice);
        tolua_function(tolua_S,"postListenerLua",lua_net_datamanager_bindings_NetDataManager_postListenerLua);
        tolua_function(tolua_S,"postJackpots",lua_net_datamanager_bindings_NetDataManager_postJackpots);
    
        tolua_function(tolua_S,"purgeSharedNetDataManager", lua_net_datamanager_bindings_NetDataManager_purgeSharedNetDataManager);
        tolua_function(tolua_S,"sharedNetDataManager", lua_net_datamanager_bindings_NetDataManager_sharedNetDataManager);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(NetDataManager).name();
    g_luaType[typeName] = "NetDataManager";
    g_typeCast["NetDataManager"] = "NetDataManager";
    return 1;
}
TOLUA_API int register_all_net_datamanager_bindings(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_net_datamanager_bindings_NetDataManager(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

