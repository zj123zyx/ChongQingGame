/****************************************************************************
 Copyright (c) 2010-2011 cocos2d-x.org
 Copyright (c) 2010      Ricardo Quesada
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"
#include "SimpleConfigParser.h"

#import "LLPayUtil.h"
#import "NetDataManager.h"
#include "./trans/Transaction_7002.h"

// TODO: 修改两个参数成商户自己的配置
//static NSString *kLLOidPartner = @"201408071000001546";              // 商户号
//static NSString *kLLPartnerKey = @"201408071000001546_test_20140815"; // 密钥
//static LLPayType payType = LLPayTypeQuick;                     //支付方式

@implementation RootViewController
{
    NSString *orderID;
    NSString *moneyNum;
}

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
//    if (SimpleConfigParser::getInstance()->isLanscape()) {
//        return UIInterfaceOrientationIsLandscape( interfaceOrientation );
//    }else{
//        return UIInterfaceOrientationIsPortrait( interfaceOrientation );
//    }
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
//    if (SimpleConfigParser::getInstance()->isLanscape()) {
//        return UIInterfaceOrientationMaskLandscape;
//    }else{
//        return UIInterfaceOrientationMaskPortraitUpsideDown;
//    }
    return UIInterfaceOrientationMaskLandscape;
#endif
}

- (BOOL) shouldAutorotate {
    if (SimpleConfigParser::getInstance()->isLanscape()) {
        return YES;
    }else{
        return NO;
    }
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
    BOOL isVisible = [accountDefaults boolForKey: @"StatusBarVisible"];
    //NSLog(@"prefersStatusBarHidden isVisible =  %d", isVisible);
    
    return isVisible;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBar.hidden = YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


#pragma mark - 创建订单

- (NSMutableDictionary *)createOrderWithOrderId:(NSString *)orderId
                                     createTime:(NSString *)createTime
                                    money_order:(NSString *)money_order
                                      accountId:(NSString *)accountId
                                    oid_partner:(NSString *)oid_partner
                                      sign_type:(NSString *)sign_type
                                   buis_partner:(NSString *)buis_partner
                                     notify_url:(NSString *)notify_url
                                rsa_private_key:(NSString *)rsa_private_key
                                   registerTime:(NSString *)registerTime
                                    phoneNumber:(NSString *)phoneNumber
{
//    NSString *partnerPrefix = @"HB"; // TODO: 修改成自己公司前缀
    
    NSString *signType = sign_type;     // MD5 || RSA || HMAC
    NSString *user_id = accountId;
    
    NSMutableDictionary *param = [NSMutableDictionary dictionary];
    
    //风控参数
    NSDictionary *riskDic = @{
                              @"frms_ware_category":@"1003",
                              @"user_info_mercht_userno":accountId,
                              @"user_info_bind_phone":phoneNumber,
                              @"user_info_dt_register":registerTime,
                              };
    // TODO: 请开发人员修改下面订单的所有信息，以匹配实际需求
    [param setDictionary:@{
                           @"sign_type" : signType,
                           @"busi_partner" : buis_partner,
                           @"dt_order" : createTime,
                           @"money_order" : money_order,
                           @"no_order" : orderId,
                           @"name_goods" : @"鸿博易彩充值",
                           @"info_order" : createTime,
                           @"valid_order" : @"10080",
                           @"notify_url" : notify_url,
                           @"risk_item" : [LLPayUtil jsonStringOfObj:riskDic],  //风险控制参数
                           @"user_id" : user_id,
                           }];
    param[@"oid_partner"] = oid_partner;
    orderID = orderId;
    moneyNum = money_order;
    
    return param;
}

#pragma mark - 订单支付

- (void)openLLPayForPayWithOrderId:(NSString *)orderId
                        createTime:(NSString *)createTime
                       money_order:(NSString *)money_order
                         accountId:(NSString *)accountId
                       oid_partner:(NSString *)oid_partner
                         sign_type:(NSString *)sign_type
                      buis_partner:(NSString *)buis_partner
                        notify_url:(NSString *)notify_url
                   rsa_private_key:(NSString *)rsa_private_key
                      registerTime:(NSString *)registerTime
                       phoneNumber:(NSString *)phoneNumber
{
    LLPayUtil *payUtil = [[LLPayUtil alloc] init];
    
    NSMutableDictionary *orderDic = [self createOrderWithOrderId:orderId
                                                      createTime:createTime
                                                     money_order:money_order
                                                       accountId:accountId
                                                     oid_partner:oid_partner
                                                       sign_type:sign_type
                                                    buis_partner:buis_partner
                                                      notify_url:notify_url
                                                 rsa_private_key:rsa_private_key
                                                    registerTime:registerTime
                                                     phoneNumber:phoneNumber];
    
    // 进行签名
    NSDictionary *signedOrder = [payUtil signedOrderDic:orderDic andSignKey:rsa_private_key];
    
    [LLPaySdk sharedSdk].sdkDelegate = self;
    
    //接入什么产品就传什么LLPayType
    [[LLPaySdk sharedSdk] presentLLPaySDKInViewController:self
                                              withPayType:LLPayTypeQuick
                                            andTraderInfo:signedOrder];
}

#pragma - mark 支付结果 LLPaySdkDelegate
// 订单支付结果返回，主要是异常和成功的不同状态
// TODO: 开发人员需要根据实际业务调整逻辑
- (void)paymentEnd:(LLPayResult)resultCode withResultDic:(NSDictionary *)dic {
    NSString *msg = @"支付异常";
    switch (resultCode) {
        case kLLPayResultSuccess: {
            msg = @"支付成功";
        } break;
        case kLLPayResultFail: {
            msg = @"支付失败";
        } break;
        case kLLPayResultCancel: {
            msg = @"支付取消";
        } break;
        case kLLPayResultInitError: {
            msg = @"sdk初始化异常";
        } break;
        case kLLPayResultInitParamError: {
            msg = dic[@"ret_msg"];
        } break;
        default:
            break;
    }
    
    NSString *result_pay = @"";
    NSString *oid_paybill = @"";
    
    NSString *ret_code    = [dic objectForKey:@"ret_code"];
    NSString *ret_msg     = [dic objectForKey:@"ret_msg"];
    NSString *no_order    = orderID;
    NSString *money_order = moneyNum;
    if (resultCode == kLLPayResultSuccess) {
        result_pay  = [dic objectForKey:@"result_pay"];
        oid_paybill = [dic objectForKey:@"oid_paybill"];
    }
    
    NetDataManager::sharedNetDataManager()->returnToLuaWithLLpayResult([ret_msg UTF8String]);
    
//    NSString *showMsg = [msg stringByAppendingString:[LLPayUtil jsonStringOfObj:dic]];
    
    Transaction7002 *tranc7002 = new Transaction7002();
    string accountId = UserDefault::getInstance()->getStringForKey("accountId");
    tranc7002->setAccountId(accountId);
    
    string sessionId = UserDefault::getInstance()->getStringForKey("sessionId");
    tranc7002->setSessionId(sessionId);
    
    string retCode = [ret_code UTF8String];
    tranc7002->setRet_code(retCode);
    
    string retMsg = [ret_msg UTF8String];
    tranc7002->setRet_msg(retMsg);
    
    string resultPay = [result_pay UTF8String];
    tranc7002->setResult_pay(resultPay);
    
    string oidPaybill = [oid_paybill UTF8String];
    tranc7002->setOid_paybill(oidPaybill);
    
    string moneyOrder = [money_order UTF8String];
    tranc7002->setMoney_order(moneyOrder);
    
    string noOrder = [no_order UTF8String];
    tranc7002->setNo_order(noOrder);
    NetDataManager::sharedNetDataManager()->sendLLpayResultToServer(tranc7002);
}


- (void)dealloc {
    [super dealloc];
}

//+ (void) payForCoins:(NSDictionary *)dict
//{
//    NSString *orderId = [dict objectForKey:@"orderId"];
//}

@end
