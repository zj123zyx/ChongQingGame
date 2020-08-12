LOCAL_PATH := $(call my-dir)
$(call import-add-path,$(LOCAL_PATH)/../)

####### third so begin
include $(CLEAR_VARS)
LOCAL_MODULE := jpush220
LOCAL_SRC_FILES := prebuilt/$(TARGET_ARCH_ABI)/libjpush220.so
include $(PREBUILT_SHARED_LIBRARY)
LOCAL_SHARED_LIBRARIES := jpush220
####### third so end

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := \
../../Classes/AppDelegate.cpp \
../../Classes/LoadingLayer.cpp \
../../Classes/VersionsManager.cpp \
../../Classes/LogoScene.cpp \
../../Classes/AppLuaApi/android/AppLuaApi.cpp \
../../Classes/AppLuaApi/android/AppNotification.cpp \
../../Classes/AppLuaApi/lua_AppLuaApi_auto.cpp \
../../Classes/AppLuaApi/lua_cocos2dx_app_notification.cpp \
../../../luaprotobuf/binary/binary.c \
../../../luaprotobuf/binary/buffer.c \
../../../luaprotobuf/binary/luabuf.c \
../../../luaprotobuf/protobuf/pb.c \
../../Classes/ide-support/SimpleConfigParser.cpp \
../../Classes/anysdkbindings.cpp \
../../Classes/anysdk_manual_bindings.cpp \
../../Classes/NetWork/util/Des.cpp \
../../Classes/NetWork/util/GzipUtil.cpp \
../../Classes/NetWork/util/md5.cpp \
../../Classes/NetWork/helper/DataHelper.cpp \
../../Classes/NetWork/interaction/PostHelper.cpp \
../../Classes/NetWork/trans/AbstractTransaction.cpp \
../../Classes/NetWork/trans/TransactionA.cpp \
../../Classes/NetWork/trans/Transaction_2002.cpp \
../../Classes/NetWork/trans/Transaction_2007.cpp \
../../Classes/NetWork/trans/Transaction_1023.cpp \
../../Classes/NetWork/trans/Transaction_3005.cpp \
../../Classes/NetWork/trans/Transaction_3015.cpp \
../../Classes/NetWork/trans/Transaction_2017.cpp \
../../Classes/NetWork/trans/Transaction_2003.cpp \
../../Classes/NetWork/trans/Transaction_2005.cpp \
../../Classes/NetWork/trans/Transaction_1026.cpp \
../../Classes/NetWork/trans/Transaction_2008.cpp \
../../Classes/NetWork/trans/Transaction_2013.cpp \
../../Classes/NetWork/trans/Transaction_3008.cpp \
../../Classes/NetWork/trans/Transaction_3016.cpp \
../../Classes/NetWork/trans/Transaction_2014.cpp \
../../Classes/NetWork/trans/Transaction_1002.cpp \
../../Classes/NetWork/trans/Transaction_1003.cpp \
../../Classes/NetWork/trans/Transaction_1004.cpp \
../../Classes/NetWork/trans/Transaction_1007.cpp \
../../Classes/NetWork/trans/Transaction_1008.cpp \
../../Classes/NetWork/trans/Transaction_1010.cpp \
../../Classes/NetWork/trans/Transaction_1012.cpp \
../../Classes/NetWork/trans/Transaction_1027.cpp \
../../Classes/NetWork/trans/Transaction_1031.cpp \
../../Classes/NetWork/trans/Transaction_1011.cpp \
../../Classes/NetWork/trans/Transaction_1014.cpp \
../../Classes/NetWork/trans/Transaction_1020.cpp \
../../Classes/NetWork/trans/Transaction_1032.cpp \
../../Classes/NetWork/trans/Transaction_1034.cpp \
../../Classes/NetWork/trans/Transaction_1035.cpp \
../../Classes/NetWork/trans/Transaction_1036.cpp \
../../Classes/NetWork/trans/Transaction_1005.cpp \
../../Classes/NetWork/trans/Transaction_1006.cpp \
../../Classes/NetWork/trans/Transaction_1013.cpp \
../../Classes/NetWork/trans/Transaction_1018.cpp \
../../Classes/NetWork/trans/Transaction_1024.cpp \
../../Classes/NetWork/trans/Transaction_1030.cpp \
../../Classes/NetWork/trans/Transaction_1015.cpp \
../../Classes/NetWork/trans/Transaction_7001.cpp \
../../Classes/NetWork/trans/Transaction_7002.cpp \
../../Classes/NetWork/trans/Transaction_7004.cpp \
../../Classes/NetWork/trans/Transaction_7005.cpp \
../../Classes/NetWork/trans/Transaction_7006.cpp \
../../Classes/NetWork/trans/Transaction_4002.cpp \
../../Classes/NetWork/trans/Transaction_4003.cpp \
../../Classes/NetWork/NetDataManager.cpp \
../../Classes/NetWork/lua_cocos2dx_net_datamanager.cpp \
../../Classes/third_platform/android/CCAccountManager.cpp \
../../Classes/third_platform/lua_binding/lua_accountManager_manual.cpp \
../../Classes/AppLuaApi/android/JniTestHelper.cpp \
../../Classes/third_platform/android/JniInterface.cpp \
../../Classes/third_platform/android/ImagePicker.cpp \
../../Classes/third_platform/lua_binding/lua_imagePicker_manual.cpp \
hellolua/main.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../../../luaprotobuf/ \
$(LOCAL_PATH)/../../../luaprotobuf/luabinding \
$(LOCAL_PATH)/../../../luaprotobuf/binary \
$(LOCAL_PATH)/../../Classes/sqlite_ext \
$(LOCAL_PATH)/../../Classes/AppLuaApi \
$(LOCAL_PATH)/../../Classes/AppLuaApi/android \
$(LOCAL_PATH)/../../Classes \
$(COCOS2DX_ROOT)/external \
$(LOCAL_PATH)/../../../cocos2d-x/external \
$(LOCAL_PATH)/../../Classes/include \
$(LOCAL_PATH)/../../Classes/include/openssl \
$(LOCAL_PATH)/../../Classes/NetWork \
$(LOCAL_PATH)/../../Classes/NetWork/util \
$(LOCAL_PATH)/../../Classes/NetWork/util/xml \
$(LOCAL_PATH)/../../Classes/NetWork/helper \
$(LOCAL_PATH)/../../Classes/NetWork/interaction \
$(LOCAL_PATH)/../../Classes/NetWork/trans \
$(LOCAL_PATH)/../../Classes/third_platform \
$(LOCAL_PATH)/../../Classes/third_platform/android \
$(LOCAL_PATH)/../../Classes/third_platform/lua_binding \
$(LOCAL_PATH)/../protocols/include \
$(LOCAL_PATH)/../protocols/android \
$(LOCAL_PATH)/../protocols/include \
$(LOCAL_PATH)/../../../cocos2d-x/tools/simulator/libsimulator/lib

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static
LOCAL_STATIC_LIBRARIES += cocos2d_simulator_static

# _COCOS_LIB_ANDROID_BEGIN
LOCAL_STATIC_LIBRARIES += quick_libs_static
# _COCOS_LIB_ANDROID_END


LOCAL_WHOLE_STATIC_LIBRARIES += PluginProtocolStatic

include $(BUILD_SHARED_LIBRARY)


$(call import-module,scripting/lua-bindings/proj.android)
$(call import-module,tools/simulator/libsimulator/proj.android)
$(call import-module,protocols/android)


# _COCOS_LIB_IMPORT_ANDROID_BEGIN
$(call import-module,proj.android)
# _COCOS_LIB_IMPORT_ANDROID_END

