//
//  SNSManager.h
//  Text
//
//  Created by Administrator on 16/7/8.
//  Copyright © 2016年 Tim. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AppConfig.h"
#import "WXApi.h"
#import <TencentOpenAPI/TencentOAuth.h>
#import "TencentOpenAPI/QQApiInterface.h"

@interface SNSManager : NSObject <TencentSessionDelegate, QQApiInterfaceDelegate, WXApiDelegate>

//微信
@property (assign, nonatomic) enum WXScene scene;
//微信登陆是1，QQ登录是2
@property (assign, nonatomic) NSInteger actionType;
@property (assign, nonatomic) eSharePlatform TapShareActionType;  //(1:微信, 2:新浪微博, 3:朋友圈, 4:QQ, 5:QQ空间)
@property (assign, nonatomic) eLoginPlatform TapLoginActionType;  //(1:微信, 2:QQ, 3:新浪微博)

+(SNSManager*) sharedManager;

+ (BOOL)handleOpenURL:(NSURL *)url withType:(NSInteger)actionType;
- (void)action_thirdPartyLoginWithType:(NSInteger)type;
- (void)changeScene:(NSInteger)scene;

- (BOOL)sendTextContentWithTitle:(NSString*)title desc:(NSString*)desc link:(NSString*)link;
- (void)sendImageContent;
- (BOOL)sendLinkContentWithTitle:(NSString*)title andDesc:(NSString*)desc andWebpageUrl:(NSString*)webpageUrl andThumbImage:(UIImage *)thumbImage;
- (void)sendMusicContent;
- (void)sendVideoContent;
- (void)sendAppContent;
- (void)sendNonGifContent;
- (void)sendGifContent;
- (void)sendFileContent;
-(void)shareQQFriendURLWithImage:(UIImage *)image;
- (void)handleSendResult:(QQApiSendResultCode)sendResult;

@end
