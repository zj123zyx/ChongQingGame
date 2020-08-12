//
//  OC-Lua-Bridge.m
//  HongBoECai
//
//  Created by Administrator on 16/8/4.
//
//

#import "OC-Lua-Bridge.h"
#include "AppController.h"
#include "RootViewController.h"
#include "NetDataManager.h"
#import "SNSManager.h"
#import "JPUSHService.h"
//#include "UserLoginViewController.h"
//#include "UserRegisterViewController.h"

using namespace cocos2d;

void OCBridge::gotoLoginVC() {
    id sth = [[UIApplication sharedApplication] delegate];
    if ([sth isKindOfClass:[AppController class]]) {
        //        UserLoginViewController *userLoginVC = [[UserLoginViewController alloc] initWithNibName:nil bundle:nil];
        //        AppController *controller = (AppController *)sth;
        //        [controller.navigationController pushViewController:userLoginVC animated:YES];
    }
}

void OCBridge::gotoRegisterVC() {
    id sth = [[UIApplication sharedApplication] delegate];
    if ([sth isKindOfClass:[AppController class]]) {
        //        UserRegisterViewController *userRegisterVC = [[UserRegisterViewController alloc] initWithNibName:nil bundle:nil];
        //        AppController *controller = (AppController *)sth;
        //        [controller.navigationController pushViewController:userRegisterVC animated:YES];
    }
}

void OCBridge::openLLPayForPayWith(const char *orderinfo) {
    id sth = [[UIApplication sharedApplication] delegate];
    if ([sth isKindOfClass:[AppController class]]) {
        AppController *controller = (AppController *)sth;
        NSMutableDictionary *orderDic = [[NSMutableDictionary alloc]init];
        
        NSString *infoStr = [NSString stringWithCString:orderinfo encoding:NSUTF8StringEncoding];
        NSLog(@"infoStr = %@",infoStr);
        
        NSArray *orderArray =[infoStr componentsSeparatedByString:@"&&&&&"];
        for (NSInteger i=0; i<orderArray.count; i++) {
            NSString *subStr = orderArray[i];
//            NSLog(@"subStr = %@",subStr);
            NSArray *subArray = [subStr componentsSeparatedByString:@"====="];
            NSString *key = subArray[0];
            NSString *value = subArray[1];
//            NSLog(@"key = %@ && value = %@",key,value);
            
            if (key != nil && value != nil) {
                [orderDic setObject:value forKey:key];
            }
        }
        
        NSString *userOrderId         = [orderDic objectForKey:@"orderId"];
        NSString *userCreateTime      = [orderDic objectForKey:@"createTime"];
        NSString *userAccountId       = [orderDic objectForKey:@"accountId"];
        NSString *userOid_partner     = [orderDic objectForKey:@"oid_partner"];
        NSString *userSign_type       = [orderDic objectForKey:@"sign_type"];
        NSString *userBuis_partner    = [orderDic objectForKey:@"buis_partner"];
        NSString *userNotify_url      = [orderDic objectForKey:@"notify_url"];
        NSString *userRsa_private_key = [orderDic objectForKey:@"rsa_private_key"];
        NSString *userRegisterTime    = [orderDic objectForKey:@"registerTime"];
        NSString *userPhoneNumber     = [orderDic objectForKey:@"phoneNumber"];
        NSString *userMoney_order     = [orderDic objectForKey:@"money_order"];

        [controller.viewController openLLPayForPayWithOrderId:userOrderId
                                                   createTime:userCreateTime
                                                  money_order:userMoney_order
                                                    accountId:userAccountId
                                                  oid_partner:userOid_partner
                                                    sign_type:userSign_type
                                                 buis_partner:userBuis_partner
                                                   notify_url:userNotify_url
                                              rsa_private_key:userRsa_private_key
                                                 registerTime:userRegisterTime
                                                  phoneNumber:userPhoneNumber];
    }
}

void OCBridge::gotoQQLogin() {
    SNSManager *manager = [SNSManager sharedManager];
    manager.actionType = 2; //微信登陆是1，QQ登录是2
    manager.TapLoginActionType = LoginPlatformQQ;
    [manager action_thirdPartyLoginWithType:1];
}

void OCBridge::gotoWeiXinLogin() {
    SNSManager *manager = [SNSManager sharedManager];
    manager.actionType = 1; //微信登陆是1，QQ登录是2
    manager.TapLoginActionType = LoginPlatformWeixin;
    [manager action_thirdPartyLoginWithType:0];
}

void OCBridge::getTokenFromLuaRequestWithCode(const char *code)
{
    NSLog(@"%s",code);
    NSString * url = [NSString stringWithFormat:@"https://api.weixin.qq.com/sns/oauth2/access_token?appid=%@&secret=%@&code=%s&grant_type=authorization_code",@WEIXIN_APPID, @WEIXIN_APPSECRET, code];
    
    const char *urlStr = [url cStringUsingEncoding:NSUTF8StringEncoding];
    NetDataManager::sharedNetDataManager()->getOpenTokenAndOpenIdFromWeiXinWithUrl(urlStr);
}

const char* OCBridge::stringToUtf8(const char *str)
{
    NSString * string = [NSString stringWithCString:str encoding:NSUTF8StringEncoding];
    string = [string stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    const char *resultStr = [string cStringUsingEncoding:NSUTF8StringEncoding];
    return resultStr;
}

const char* OCBridge::utf8ToString(const char *str)
{
    NSString * string = [NSString stringWithCString:str encoding:NSUTF8StringEncoding];
    string = [string stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    const char *resultStr = [string UTF8String];
    return resultStr;
}

void OCBridge::setAliasWithAccountId(const char *str)
{
    NSString * string = [NSString stringWithCString:str encoding:NSUTF8StringEncoding];
//    [JPUSHService setAlias:string callbackSelector:@selector(sendToServer) object:nil];
    [JPUSHService setTags:nil alias:string fetchCompletionHandle:^(int iResCode, NSSet *iTags, NSString *iAlias) {
        NSLog(@"iResCode = %d",iResCode);
        if (iResCode == 0) {
            NSLog(@"设置别名成功");
        }
        NSLog(@"Alias = %@",iAlias);
    }];
}

void OCBridge::shareWeChatFriend()
{
    
    SNSManager *manager = [SNSManager sharedManager];
    manager.scene = WXSceneSession; //微信登陆是1，QQ登录是2
    manager.TapShareActionType = SharePlatformWeixin;
    printf("=======dasfds=friend==2=");
    NSString *path = [[NSBundle mainBundle] pathForResource:@"res/Icon-80" ofType:@"png"];
    UIImage *image = [UIImage imageWithContentsOfFile:path];
    BOOL bb = [manager sendLinkContentWithTitle:@"鸿博易彩" andDesc:@"鸿博易彩，赢超级大奖！" andWebpageUrl:@"https://itunes.apple.com/us/app/hong-bo-yi-cai/id1147435653?l=zh&ls=1&mt=8" andThumbImage:image];

    printf("%d",bb);
}

void OCBridge::shareWeChatFriendQuan()
{
    SNSManager *manager = [SNSManager sharedManager];
    manager.scene = WXSceneTimeline; //微信登陆是1，QQ登录是2
    manager.TapShareActionType = SharePlatformMoments;
    printf("=======dasfds==quan==");
    NSString *path = [[NSBundle mainBundle] pathForResource:@"res/Icon-80" ofType:@"png"];
    UIImage *image = [UIImage imageWithContentsOfFile:path];
    BOOL bb = [manager sendLinkContentWithTitle:@"鸿博易彩" andDesc:@"鸿博易彩，赢超级大奖！" andWebpageUrl:@"https://itunes.apple.com/us/app/hong-bo-yi-cai/id1147435653?l=zh&ls=1&mt=8" andThumbImage:image];
    printf("%d",bb);
}

void OCBridge::shareQQFriend()
{
    SNSManager *manager = [SNSManager sharedManager];
    
    printf("=======qq==quan==");
    NSString *utf8String = @"https://itunes.apple.com/us/app/hong-bo-yi-cai/id1147435653?l=zh&ls=1&mt=8";
    NSString *title = @"鸿博易彩";
    NSString *description = @"鸿博易彩，赢超级大奖！";
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"res/Icon-80" ofType:@"png"];
    UIImage *image = [UIImage imageWithContentsOfFile:path];
    NSData *dataImage = UIImagePNGRepresentation(image);

//    [manager shareQQFriendURLWithImage:image];
    TencentOAuth *tencentOAuth = [[TencentOAuth alloc]initWithAppId:@QQ_APPID andDelegate:[SNSManager sharedManager]];
    
    QQApiNewsObject *newsObj = [QQApiNewsObject objectWithURL:[NSURL URLWithString:utf8String] title:title description:description previewImageData:dataImage];
    SendMessageToQQReq *req = [SendMessageToQQReq reqWithContent:newsObj];
    //将内容分享到qq
    QQApiSendResultCode sent = [QQApiInterface sendReq:req];
    [manager handleSendResult:sent];
}


