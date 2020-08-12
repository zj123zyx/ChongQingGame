#include "lua_imagePicker_manual.hpp"
#include "ImagePicker.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_manual_imagePicker_ImagePicker_setImgPickerListenerLua(lua_State* tolua_S)
{
    int argc = 0;
    ImagePicker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImagePicker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ImagePicker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_imagePicker_ImagePicker_setImgPickerListenerLua'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
//        int arg0;
//
//        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ImagePicker:setImgPickerListenerLua");
//        if(!ok)
//        {
//            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_imagePicker_ImagePicker_setImgPickerListenerLua'", nullptr);
//            return 0;
//        }
//        cobj->setImgPickerListenerLua(arg0);
//        return 0;
        int handler = (toluafix_ref_function(tolua_S,2,0));
        cobj->setImgPickerListenerLua(handler);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImagePicker:setImgPickerListenerLua",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_imagePicker_ImagePicker_setImgPickerListenerLua'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_imagePicker_ImagePicker_startImagePicker(lua_State* tolua_S)
{
    int argc = 0;
    ImagePicker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImagePicker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ImagePicker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_imagePicker_ImagePicker_startImagePicker'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_imagePicker_ImagePicker_startImagePicker'", nullptr);
            return 0;
        }
        cobj->startImagePicker();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImagePicker:startImagePicker",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_imagePicker_ImagePicker_startImagePicker'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_imagePicker_ImagePicker_startImageCamera(lua_State* tolua_S)
{
    int argc = 0;
    ImagePicker* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImagePicker",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ImagePicker*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_manual_imagePicker_ImagePicker_startImageCamera'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_imagePicker_ImagePicker_startImageCamera'", nullptr);
            return 0;
        }
        cobj->startImageCamera();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImagePicker:startImageCamera",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_imagePicker_ImagePicker_startImageCamera'.",&tolua_err);
#endif

    return 0;
}
int lua_manual_imagePicker_ImagePicker_sharedImagePicker(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ImagePicker",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_manual_imagePicker_ImagePicker_sharedImagePicker'", nullptr);
            return 0;
        }
        ImagePicker* ret = ImagePicker::sharedImagePicker();
        object_to_luaval<ImagePicker>(tolua_S, "ImagePicker",(ImagePicker*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ImagePicker:sharedImagePicker",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_manual_imagePicker_ImagePicker_sharedImagePicker'.",&tolua_err);
#endif
    return 0;
}
static int lua_manual_imagePicker_ImagePicker_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ImagePicker)");
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
    !tolua_isusertype(tolua_S,1,"ImagePicker",0,&tolua_err) ||
    !tolua_isnoobj(tolua_S,2,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        ImagePicker* self = (ImagePicker*)  tolua_tousertype(tolua_S,1,0);
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

int lua_register_manual_imagePicker_ImagePicker(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ImagePicker");
    tolua_cclass(tolua_S,"ImagePicker","ImagePicker","",nullptr);

    tolua_beginmodule(tolua_S,"ImagePicker");
        tolua_function(tolua_S,"setImgPickerListenerLua",lua_manual_imagePicker_ImagePicker_setImgPickerListenerLua);
        tolua_function(tolua_S,"startImagePicker",lua_manual_imagePicker_ImagePicker_startImagePicker);
        tolua_function(tolua_S,"startImageCamera",lua_manual_imagePicker_ImagePicker_startImageCamera);
        tolua_function(tolua_S,"sharedImagePicker", lua_manual_imagePicker_ImagePicker_sharedImagePicker);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ImagePicker).name();
    g_luaType[typeName] = "ImagePicker";
    g_typeCast["ImagePicker"] = "ImagePicker";
    return 1;
}
TOLUA_API int register_all_manual_imagePicker(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_manual_imagePicker_ImagePicker(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

