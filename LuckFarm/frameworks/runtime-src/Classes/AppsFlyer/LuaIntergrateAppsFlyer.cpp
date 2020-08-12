/*
** Lua binding: LuaIntergrateAppsFlyer
** Generated automatically by tolua++-1.0.92 on Wed May 28 18:02:06 2014.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

#include "LuaIntergrateAppsFlyer.h"
#include "IntegrateAppsFlyer.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_LuaIntergrateAppsFlyer_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"IntergrateAppsFlyer");
}

/* method: instance of class  IntergrateAppsFlyer */
#ifndef TOLUA_DISABLE_tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_instance00
static int tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"IntergrateAppsFlyer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   IntergrateAppsFlyer* tolua_ret = (IntergrateAppsFlyer*)  IntergrateAppsFlyer::instance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"IntergrateAppsFlyer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: integrateAppsFlyer of class  IntergrateAppsFlyer */
#ifndef TOLUA_DISABLE_tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_integrateAppsFlyer00
static int tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_integrateAppsFlyer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IntergrateAppsFlyer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IntergrateAppsFlyer* self = (IntergrateAppsFlyer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'integrateAppsFlyer'", NULL);
#endif
  {
   self->integrateAppsFlyer();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'integrateAppsFlyer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: appsFlyerTrackEvent of class  IntergrateAppsFlyer */
#ifndef TOLUA_DISABLE_tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_appsFlyerTrackEvent00
static int tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_appsFlyerTrackEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IntergrateAppsFlyer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IntergrateAppsFlyer* self = (IntergrateAppsFlyer*)  tolua_tousertype(tolua_S,1,0);
  const char* iName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* iValue = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'appsFlyerTrackEvent'", NULL);
#endif
  {
   self->appsFlyerTrackEvent(iName,iValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'appsFlyerTrackEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIDFA of class  IntergrateAppsFlyer */
#ifndef TOLUA_DISABLE_tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_getIDFA00
static int tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_getIDFA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IntergrateAppsFlyer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IntergrateAppsFlyer* self = (IntergrateAppsFlyer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIDFA'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getIDFA();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIDFA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaIntergrateAppsFlyer_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"IntergrateAppsFlyer","IntergrateAppsFlyer","",NULL);
  tolua_beginmodule(tolua_S,"IntergrateAppsFlyer");
   tolua_function(tolua_S,"instance",tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_instance00);
   tolua_function(tolua_S,"integrateAppsFlyer",tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_integrateAppsFlyer00);
   tolua_function(tolua_S,"appsFlyerTrackEvent",tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_appsFlyerTrackEvent00);
   tolua_function(tolua_S,"getIDFA",tolua_LuaIntergrateAppsFlyer_IntergrateAppsFlyer_getIDFA00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LuaIntergrateAppsFlyer (lua_State* tolua_S) {
 return tolua_LuaIntergrateAppsFlyer_open(tolua_S);
};
#endif

