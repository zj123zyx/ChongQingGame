//
//  ImagePickerViewController.h
//  HongBoECai
//
//  Created by yi.liu on 16/10/9.
//
//

#import <Foundation/Foundation.h>

#ifndef ImagePickerViewController_h
#define ImagePickerViewController_h

#import <UIKit/UIKit.h>

@interface ImagePickerViewController:UIViewController<UINavigationControllerDelegate,UIImagePickerControllerDelegate>
{
    NSString *filePath;
}

//打开本地相册
-(void)localPhoto;

//打开相机
-(void)takePhoto;

@end
#endif
