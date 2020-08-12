//
//  lua_Filter_auto.cpp
//  CasinoGameNew
//
//  Created by wanghongqi on 16-6-7.
//
//


#include "lua_Filter_auto.h"

#include "Filter.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

int lua_FilterApi_FilterApi_censor(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"Filter",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {

        std::string arg0_tmp;
        ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "Filter::censor");
        
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_FilterApi_FilterApi_censor'", nullptr);
            return 0;
        }
        bool rReturn = Filter::censor(arg0_tmp);
        lua_pushboolean(tolua_S, rReturn);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "Filter::censor",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_FilterApi_FilterApi_censor'.",&tolua_err);
#endif
    return 0;
}

int lua_FilterApi_FilterApi_censorEx(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"Filter",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        
        std::string arg0_tmp;
        ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "Filter::censorEx");
        
        
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_FilterApi_FilterApi_censorEx'", nullptr);
            return 0;
        }
        string rReturn = Filter::censorEx(arg0_tmp);
        lua_pushstring(tolua_S, rReturn.c_str());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "Filter::censorEx",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_FilterApi_FilterApi_censorEx'.",&tolua_err);
#endif
    return 0;
}



static int lua_FilterApi_FilterApi_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (FilterApi)");
    return 0;
}
int lua_register_FilterApi_FilterApi(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"Filter");
    tolua_cclass(tolua_S,"Filter","Filter","",nullptr);
    
    tolua_beginmodule(tolua_S,"Filter");
    tolua_function(tolua_S,"censor",lua_FilterApi_FilterApi_censor);
    tolua_function(tolua_S,"censorEx",lua_FilterApi_FilterApi_censorEx);
    
    
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Filter).name();
    g_luaType[typeName] = "Filter";
    g_typeCast["Filter"] = "Filter";
    return 1;
}
TOLUA_API int register_all_FilterApi(lua_State* tolua_S)
{
    tolua_open(tolua_S);
    
    tolua_module(tolua_S,nullptr,0);
    tolua_beginmodule(tolua_S,nullptr);
    
    lua_register_FilterApi_FilterApi(tolua_S);
    
    tolua_endmodule(tolua_S);
    return 1;
}