
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS := \
  -Wno-multichar \
  -D_ANDROID \
  -DLIBDIR="c" \
  -DIN_LIBRARY \
  -DSQLITE_HAS_CODEC=1 \
  -DCODEC_TYPE=CODEC_TYPE_AES128 \
  -DSQLITE_CORE \
  -DTHREADSAFE \
  -DSQLITE_SECURE_DELETE \
  -DSQLITE_SOUNDEX \
  -DSQLITE_ENABLE_COLUMN_METADATA

LOCAL_MODULE := quick_extensions_static
LOCAL_MODULE_FILENAME := libquickextensions

LOCAL_SRC_FILES := $(LOCAL_PATH)/quick_extensions.c \
                    $(LOCAL_PATH)/zlib/lua_zlib.c \
                    $(LOCAL_PATH)/filesystem/lfs.c \
                    $(LOCAL_PATH)/lpack/lpack.c \
                    $(LOCAL_PATH)/luaxml/LuaXML_lib.cpp

LOCAL_SRC_FILES += \
                        $(LOCAL_PATH)/cjson/fpconv.c \
                        $(LOCAL_PATH)/cjson/lua_cjson.c \
                        $(LOCAL_PATH)/cjson/strbuf.c

#ifeq ($(CC_USE_SQLITE),1)
LOCAL_SRC_FILES += \
                        $(LOCAL_PATH)/lsqlite3/shell.c \
                        $(LOCAL_PATH)/lsqlite3/sqlite3secure.c \
                        $(LOCAL_PATH)/lsqlite3/sqlite3.c \
                        $(LOCAL_PATH)/lsqlite3/lsqlite3.c \
                        $(LOCAL_PATH)/lsqlite3/rijndael.c
#endif

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/ \
                           $(LOCAL_PATH)/cjson \
                           $(LOCAL_PATH)/zlib \
                           $(LOCAL_PATH)/filesystem \
                           $(LOCAL_PATH)/lpack \
                           $(LOCAL_PATH)/lsqlite3 \
                           $(LOCAL_PATH)/luaxml

LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/cjson \
                    $(LOCAL_PATH)/zlib \
                    $(LOCAL_PATH)/debugger \
                    $(LOCAL_PATH)/filesystem \
                    $(LOCAL_PATH)/lpack \
                    $(LOCAL_PATH)/lsqlite3 \
                    $(LOCAL_PATH)/luaxml \
                    $(LOCAL_PATH)/../../../../cocos \
                    $(LOCAL_PATH)/../../../../external/lua/luajit/include




include $(BUILD_STATIC_LIBRARY)

