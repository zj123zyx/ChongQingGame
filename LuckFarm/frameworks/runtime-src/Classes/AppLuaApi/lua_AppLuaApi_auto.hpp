#include "base/ccConfig.h"
#ifndef __AppLuaApi_h__
#define __AppLuaApi_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_AppLuaApi(lua_State* tolua_S);










#endif // __AppLuaApi_h__
