//
//  SNSManager.m
//  Text
//
//  Created by Administrator on 16/7/8.
//  Copyright © 2016年 Tim. All rights reserved.
//

#import "SNSManager.h"
#import "OC-Lua-Bridge.h"
#import "AppController.h"
#include "NetDataManager.h"

@implementation SNSManager
{
    TencentOAuth * tencentOAuth;
}

#pragma mark -
#pragma mark 初始化方法
/*
 * ===============================================
 * 初始化方法
 * ===============================================
 */
-(id)init
{
    if (self = [super init]) {
        [WXApi registerApp:@WEIXIN_APPID];
    }
    return self;
}


+ (id) alloc
{
    @synchronized(self)     {
        NSAssert(sharedManager == nil, @"Attempted to allocate a second instance of a singleton.");
        return [super alloc];
    }
    return nil;
}

static SNSManager* sharedManager;
+ (SNSManager*) sharedManager
{
    @synchronized(self){
        if (!sharedManager) {
            sharedManager = [[SNSManager alloc] init];
        }
    }
    return sharedManager;
}

+ (void)clear
{
    sharedManager = nil;
}


+(BOOL)handleOpenURL:(NSURL *)url withType:(NSInteger)actionType
{
    switch (actionType) {
        case 1:
            return [WXApi handleOpenURL:url delegate:[SNSManager sharedManager]];
        case 2:
            return [TencentOAuth HandleOpenURL:url];
//            return [QQApiInterface handleOpenURL:url delegate:[SNSManager sharedManager]];
        default:
            break;
    }
    return YES;
}

- (void)action_thirdPartyLoginWithType:(NSInteger)type;
{
    if (type == 0) {
        //微信
        SendAuthReq* req =[[SendAuthReq alloc] init];
        req.scope = @"snsapi_userinfo";
        req.state = @"123";
        AppController *controller = (AppController *)[[UIApplication sharedApplication] delegate];
        [WXApi sendAuthReq:req viewController:(UIViewController *)controller.viewController delegate:self];
    }else if (type == 1){
        //QQ
        tencentOAuth = [[TencentOAuth alloc]initWithAppId:@QQ_APPID andDelegate:[SNSManager sharedManager]];
        NSArray* permissions = [NSArray arrayWithObjects:
                                kOPEN_PERMISSION_GET_SIMPLE_USER_INFO,
                                nil];
        [tencentOAuth authorize:permissions inSafari:NO];
    }
}

-(void)shareQQFriendURLWithImage:(UIImage *)image
{
    printf("=======qq==quan==");
    NSString *utf8String = @"https://itunes.apple.com/us/app/hong-bo-yi-cai/id1147435653?l=zh&ls=1&mt=8";
    NSString *title = @"鸿博易彩";
    NSString *description = @"鸿博易彩，赢超级大奖！";
//    NSString *path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"res/Icon-80.png"];
//    NSData* dataImage = [NSData dataWithContentsOfFile:path];
//    NSString *path = [[NSBundle mainBundle] pathForResource:@"res/Icon-80" ofType:@"png"];
//    UIImage *image = [UIImage imageWithContentsOfFile:path];
    
    
    NSData *dataImage = UIImagePNGRepresentation(image);
    
    tencentOAuth = [[TencentOAuth alloc]initWithAppId:@QQ_APPID andDelegate:[SNSManager sharedManager]];
    
    QQApiNewsObject *newsObj = [QQApiNewsObject objectWithURL:[NSURL URLWithString:utf8String] title:title description:description previewImageData:dataImage];
    
    SendMessageToQQReq *req = [SendMessageToQQReq reqWithContent:newsObj];
    //将内容分享到qq
    QQApiSendResultCode sent = [QQApiInterface sendReq:req];
    [self handleSendResult:sent];
}

#pragma mark - Weixin Send message protocal

- (void)changeScene:(NSInteger)scene
{
    self.scene = (enum WXScene)scene;
}

- (BOOL)sendTextContentWithTitle:(NSString*)title desc:(NSString*)desc link:(NSString*)link
{
    if ([WXApi isWXAppInstalled] == NO) {
//        [UIKitAdditions showAlertOnKeyWindowWithContent:@"您还没有安装微信"];
        return NO;
    }
    
    WXMediaMessage *message = [WXMediaMessage message];
    
    message.title = title;
    message.description = desc;
    message.mediaTagName = @"来自鸿博易彩";
    [message setThumbImage:[UIImage imageNamed:@"Icon-120.png"]];
    
    WXWebpageObject *ext = [WXWebpageObject object];
    ext.webpageUrl = link;
    
    message.mediaObject = ext;
    
    SendMessageToWXReq* req = [[SendMessageToWXReq alloc] init];
    req.bText = NO;
    req.message = message;
    req.scene = _scene;
    
    [WXApi sendReq:req];
    return YES;
}

- (void)sendImageContent
{}

- (BOOL)sendLinkContentWithTitle:(NSString*)title andDesc:(NSString*)desc andWebpageUrl:(NSString*)webpageUrl andThumbImage:(UIImage *)thumbImage
{
    if ([WXApi isWXAppInstalled] == NO) {
//        [UIKitAdditions showAlertOnKeyWindowWithContent:@"您还没有安装微信"];
        return NO;
    }
    WXMediaMessage *message = [WXMediaMessage message];
    message.title = title;
    message.description = desc;
    [message setThumbImage:thumbImage];
    
    WXWebpageObject *ext = [WXWebpageObject object];
    ext.webpageUrl = webpageUrl;
    
    message.mediaObject = ext;
    
    SendMessageToWXReq* req = [[SendMessageToWXReq alloc] init];
    req.bText = NO;
    req.message = message;
    req.scene = _scene;
    
    BOOL success = [WXApi sendReq:req];
    return success;
}

- (void)sendMusicContent
{}

- (void)sendVideoContent
{}

- (void)sendAppContent
{}

- (void)sendNonGifContent
{}

- (void)sendGifContent
{}

- (void)sendFileContent
{}

#pragma mark - 微信 delegate
/*
 * ===============================
 *  微信 delegate
 * ===============================
 */

- (void)onReq:(BaseReq *)req
{
    NSLog(@"onReq");
}

- (void)onResp:(BaseResp *)resp
{
    NSLog(@"onResp");
    if (self.actionType == 1) {
        if (self.TapShareActionType == SharePlatformWeixin ||
            self.TapShareActionType == SharePlatformMoments)
        {
            switch (resp.errCode) {
                case WXSuccess:
                {
//                    [UIKitAdditions showAlertOnKeyWindowWithContent:@"分享成功"];
                    break;
                }
                case WXErrCodeCommon:
                {
//                    [UIKitAdditions showAlertOnKeyWindowWithContent:@"分享失败"];
                    break;
                }
                case WXErrCodeUserCancel:
                {
//                    [UIKitAdditions showAlertOnKeyWindowWithContent:@"分享取消"];
                    break;
                }
                case WXErrCodeSentFail:
                {
//                    [UIKitAdditions showAlertOnKeyWindowWithContent:@"分享发送失败"];
                    break;
                }
                case WXErrCodeAuthDeny:
                {
//                    [UIKitAdditions showAlertOnKeyWindowWithContent:@"授权失败"];
                    break;
                }
                case WXErrCodeUnsupport:
                {
//                    [UIKitAdditions showAlertOnKeyWindowWithContent:@"微信不支持此操作"];
                    break;
                }
                default:
                    break;
            }
        }
        if (self.TapLoginActionType == LoginPlatformWeixin) {
            int errCode = resp.errCode;
            if (errCode == 0) {
                NSString * codeStr = [(SendAuthResp *)resp code];
                const char *code = [codeStr cStringUsingEncoding:NSUTF8StringEncoding];
                OCBridge::getTokenFromLuaRequestWithCode(code);
            }
        }
    }
}


#pragma mark - QQ delegate
/*
 * ===============================
 *  QQ delegate
 * ===============================
 */
-(void)tencentDidLogin
{
    if (tencentOAuth.accessToken && 0 != [tencentOAuth.accessToken length])
    {
        //记录登录用户的OpenID、Token以及过期时间
        NSString * accessToken = tencentOAuth.accessToken;
        NSString * openID = tencentOAuth.openId;
        
        const char *openId = [openID cStringUsingEncoding:NSUTF8StringEncoding];
        const char *aToken = [accessToken cStringUsingEncoding:NSUTF8StringEncoding];
        
        NetDataManager::sharedNetDataManager()->returnToLuaWithOpenIDAndAccessToken(openId, aToken);
    }
    else{
//        [UIKitAdditions showAlertOnKeyWindowWithContent:@"授权失败"];
    }
}

-(void)tencentDidNotLogin:(BOOL)cancelled
{
    if (cancelled){
        NSLog(@"用户取消登录");
    }
    else{
        NSLog(@"登录失败");
    }
}

-(void)tencentDidNotNetWork
{
    NSLog(@"无网络连接，请设置网络");
}

-(void)isOnlineResponse:(NSDictionary *)response
{
    
}

- (void)handleSendResult:(QQApiSendResultCode)sendResult
{
    switch (sendResult)
    {
        case EQQAPIAPPNOTREGISTED:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"App未注册" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
//            [msgbox release];
            
            break;
        }
        case EQQAPIMESSAGECONTENTINVALID:
        case EQQAPIMESSAGECONTENTNULL:
        case EQQAPIMESSAGETYPEINVALID:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"发送参数错误" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
//            [msgbox release];
            
            break;
        }
        case EQQAPIQQNOTINSTALLED:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"未安装QQ" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
//            [msgbox release];
            
            break;
        }
        case EQQAPIQQNOTSUPPORTAPI:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"API接口不支持" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
//            [msgbox release];
            
            break;
        }
        case EQQAPISENDFAILD:
        {
            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"发送失败" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
            [msgbox show];
//            [msgbox release];
            
            break;
        }
//        case EQQAPIVERSIONNEEDUPDATE:
//        {
//            UIAlertView *msgbox = [[UIAlertView alloc] initWithTitle:@"Error" message:@"当前QQ版本太低，需要更新" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil];
//            [msgbox show];
//            break;
//        }
        default:
        {
            break;
        }
    }
}














@end
