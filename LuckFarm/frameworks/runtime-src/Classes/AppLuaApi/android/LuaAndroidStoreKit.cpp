/*
 ** Lua binding: LuaAndroidStoreKit
 ** Generated automatically by tolua++-1.0.92 on Wed Aug 27 16:57:48 2014.
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

#include "AndroidStoreKit.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_LuaAndroidStoreKit_open (lua_State* tolua_S);


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
    
    tolua_usertype(tolua_S,"AndroidStoreKit");
}

/* method: sharedStoreKit of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_sharedStoreKit00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_sharedStoreKit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertable(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        {
            AndroidStoreKit* tolua_ret = (AndroidStoreKit*)  AndroidStoreKit::sharedStoreKit();
            tolua_pushusertype(tolua_S,(void*)tolua_ret,"AndroidStoreKit");
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'sharedStoreKit'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purchaseProductWithID of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_purchaseProductWithID00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_purchaseProductWithID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isstring(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        AndroidStoreKit* self = (AndroidStoreKit*)  tolua_tousertype(tolua_S,1,0);
        const char* theProductID = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char* payload = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purchaseProductWithID'", NULL);
#endif
        {
            self->purchaseProductWithID(theProductID,payload);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'purchaseProductWithID'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransactionCompletedListener of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_setTransactionCompletedListener00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_setTransactionCompletedListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        AndroidStoreKit* self = (AndroidStoreKit*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION listener = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransactionCompletedListener'", NULL);
#endif
        {
            self->setTransactionCompletedListener(listener);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTransactionCompletedListener'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTransactionErrorListener of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_setTransactionErrorListener00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_setTransactionErrorListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
        !tolua_isnoobj(tolua_S,3,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        AndroidStoreKit* self = (AndroidStoreKit*)  tolua_tousertype(tolua_S,1,0);
        LUA_FUNCTION listener = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTransactionErrorListener'", NULL);
#endif
        {
            self->setTransactionErrorListener(listener);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'setTransactionErrorListener'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsProcessDialogShow of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_getIsProcessDialogShow00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_getIsProcessDialogShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        AndroidStoreKit* self = (AndroidStoreKit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsProcessDialogShow'", NULL);
#endif
        {
            bool tolua_ret = (bool)  self->getIsProcessDialogShow();
            tolua_pushboolean(tolua_S,(bool)tolua_ret);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getIsProcessDialogShow'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showProgressDialog of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_showProgressDialog00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_showProgressDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        AndroidStoreKit* self = (AndroidStoreKit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showProgressDialog'", NULL);
#endif
        {
            self->showProgressDialog();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'showProgressDialog'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hideProgressDialog of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_hideProgressDialog00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_hideProgressDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        AndroidStoreKit* self = (AndroidStoreKit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hideProgressDialog'", NULL);
#endif
        {
            self->hideProgressDialog();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'hideProgressDialog'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: userReportCallBack of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_userReportCallBack00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_userReportCallBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,2,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        AndroidStoreKit* self = (AndroidStoreKit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'userReportCallBack'", NULL);
#endif
        {
            self->userReportCallBack();
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'userReportCallBack'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: trackingWithEvent of class  AndroidStoreKit */
#ifndef TOLUA_DISABLE_tolua_LuaAndroidStoreKit_AndroidStoreKit_trackingWithEvent00
static int tolua_LuaAndroidStoreKit_AndroidStoreKit_trackingWithEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(tolua_S,1,"AndroidStoreKit",0,&tolua_err) ||
        !tolua_isstring(tolua_S,2,0,&tolua_err) ||
        !tolua_isstring(tolua_S,3,0,&tolua_err) ||
        !tolua_isnoobj(tolua_S,4,&tolua_err)
        )
        goto tolua_lerror;
    else
#endif
    {
        AndroidStoreKit* self = (AndroidStoreKit*)  tolua_tousertype(tolua_S,1,0);
        const char* eventName = ((const char*)  tolua_tostring(tolua_S,2,0));
        const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
        if (!self) tolua_error(tolua_S,"invalid 'self' in function 'trackingWithEvent'", NULL);
#endif
        {
            self->trackingWithEvent(eventName,value);
        }
    }
    return 0;
#ifndef TOLUA_RELEASE
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'trackingWithEvent'.",&tolua_err);
    return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaAndroidStoreKit_open (lua_State* tolua_S)
{
    tolua_open(tolua_S);
    tolua_reg_types(tolua_S);
    tolua_module(tolua_S,NULL,0);
    tolua_beginmodule(tolua_S,NULL);
    tolua_cclass(tolua_S,"AndroidStoreKit","AndroidStoreKit","",NULL);
    tolua_beginmodule(tolua_S,"AndroidStoreKit");
    tolua_function(tolua_S,"sharedStoreKit",tolua_LuaAndroidStoreKit_AndroidStoreKit_sharedStoreKit00);
    tolua_function(tolua_S,"purchaseProductWithID",tolua_LuaAndroidStoreKit_AndroidStoreKit_purchaseProductWithID00);
    tolua_function(tolua_S,"setTransactionCompletedListener",tolua_LuaAndroidStoreKit_AndroidStoreKit_setTransactionCompletedListener00);
    tolua_function(tolua_S,"setTransactionErrorListener",tolua_LuaAndroidStoreKit_AndroidStoreKit_setTransactionErrorListener00);
    tolua_function(tolua_S,"getIsProcessDialogShow",tolua_LuaAndroidStoreKit_AndroidStoreKit_getIsProcessDialogShow00);
    tolua_function(tolua_S,"showProgressDialog",tolua_LuaAndroidStoreKit_AndroidStoreKit_showProgressDialog00);
    tolua_function(tolua_S,"hideProgressDialog",tolua_LuaAndroidStoreKit_AndroidStoreKit_hideProgressDialog00);
    tolua_function(tolua_S,"userReportCallBack",tolua_LuaAndroidStoreKit_AndroidStoreKit_userReportCallBack00);
    tolua_function(tolua_S,"trackingWithEvent",tolua_LuaAndroidStoreKit_AndroidStoreKit_trackingWithEvent00);
    tolua_endmodule(tolua_S);
    tolua_endmodule(tolua_S);
    return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
TOLUA_API int luaopen_LuaAndroidStoreKit (lua_State* tolua_S) {
    return tolua_LuaAndroidStoreKit_open(tolua_S);
};
#endif

