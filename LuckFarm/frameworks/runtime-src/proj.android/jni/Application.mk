APP_STL := gnustl_static
NDK_TOOLCHAIN_VERSION := clang

APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic

#APP_DEBUG = 1
#COCOS2D_DEBUG = 1

ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif

LOCAL_CFLAGS := -g -ggdb -O0 -DSQLITE_HAS_CODEC
LOCAL_LDFLAGS := -Wl,-Map,xxx.map