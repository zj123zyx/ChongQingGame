//
//  AppConfig.h
//  Text
//
//  Created by Administrator on 16/7/8.
//  Copyright © 2016年 Tim. All rights reserved.


#ifndef ECai_AppConfig_h
#define ECai_AppConfig_h

/*
 * ====================
 * 第三方接入
 * ====================
 */

//secret key
#define WEIXIN_APPID     "wxe78cc928c11c921e"
#define WEIXIN_APPSECRET "171b91d5406964e0b3dd29f8ab071194"

#define QQ_APPID         "1105583977"
#define QQ_APPSECRET     "InqLMvypsWmUmVpx"

/*
 * 分享的平台(1:微信, 2:新浪微博, 3:朋友圈, 4:QQ, 5:QQ空间)
 */
typedef enum
{
    SharePlatformWeixin       = 1,
    SharePlatformWeibo        = 2,
    SharePlatformMoments      = 3,
    SharePlatformQQ           = 4,
    SharePlatformQZone        = 5,
}
eSharePlatform;

/*
 * 第三方登录来源(1:微信, 2:QQ, 3:新浪微博)
 */
typedef enum
{
    LoginPlatformWeixin       = 1,
    LoginPlatformQQ           = 2,
    LoginPlatformWeibo        = 3,
}
eLoginPlatform;

#endif
