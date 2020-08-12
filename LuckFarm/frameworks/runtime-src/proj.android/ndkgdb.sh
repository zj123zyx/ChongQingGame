APPNAME="Slot"
APP_ANDROID_NAME="com.phonegames.casino"

if [ -z "${SDK_ROOT+aaa}" ]; then
# ... if SDK_ROOT is not set, use "$HOME/bin/android-sdk"
    SDK_ROOT=$ANDROID_SDK_ROOT
fi

if [ -z "${NDK_ROOT+aaa}" ]; then
# ... if NDK_ROOT is not set, use "$HOME/bin/android-ndk"
    NDK_ROOT=$NDK_ROOT
fi

if [ -z "${COCOS2DX_ROOT+aaa}" ]; then
# ... if COCOS2DX_ROOT is not set
# ... find current working directory
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
    APP_ROOT="$DIR/../../.."
    APP_ANDROID_ROOT="$DIR"
    export COCOS2DX_ROOT=$DIR/../../cocos2d-x
else
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
    APP_ROOT="$DIR/../../.."
    APP_ANDROID_ROOT="$DIR"
    export COCOS2DX_ROOT=$DIR/../../cocos2d-x
fi

echo "NDK_ROOT = $NDK_ROOT"
echo "SDK_ROOT = $SDK_ROOT"
echo "COCOS2DX_ROOT = $COCOS2DX_ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_ANDROID_ROOT = $APP_ANDROID_ROOT"
echo "APP_ANDROID_NAME = $APP_ANDROID_NAME"

echo
echo "Killing and restarting ${APP_ANDROID_NAME}"
echo

set -x

"${SDK_ROOT}"/platform-tools/adb shell am force-stop "${APP_ANDROID_NAME}"

#NDK_MODULE_PATH="${COCOS2DX_ROOT}":"${COCOS2DX_ROOT}"/cocos2dx/platform/third_party/android/prebuilt:/Users/mey/project/slot/client/trunk/SlotFun \
NDK_MODULE_PATH=${APP_ANDROID_ROOT}:${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos:${COCOS2DX_ROOT}/external:${COCOS2DX_ROOT}/cocos/scripting:${APP_ANDROID_ROOT}/../Classes:${COCOS2DX_ROOT}/../luaprotobuf:${COCOS2DX_ROOT}/cocos/quick_libs \
    "${NDK_ROOT}"/ndk-gdb.py \
    --adb="${SDK_ROOT}"/platform-tools/adb \
    --verbose \
    --force \
    --nowait \
    --launch=org.cocos2dx.lua.AppActivity
