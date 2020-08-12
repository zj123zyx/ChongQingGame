LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := game_libs_static

LOCAL_MODULE_FILENAME := gamelibs

LOCAL_SRC_FILES :=../binary/binary.c \
          ../binary/buffer.c \
          ../binary/luabuf.c \
          ../protobuf/pb.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../luabinding \
                           $(LOCAL_PATH)/../tolua \
                           $(LOCAL_PATH)/../binary \
                           $(LOCAL_PATH)/../protobuf


LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2d_lua_static

LOCAL_CFLAGS += -Wno-psabi
LOCAL_EXPORT_CFLAGS += -Wno-psabi

include $(BUILD_STATIC_LIBRARY)

#$(call import-module,libcocos2d)
#$(call import-module,scripting/lua/proj.android)

$(call import-module,scripting/lua-bindings/proj.android)
