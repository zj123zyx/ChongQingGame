//
//  ImagePickerViewController.mm
//  HongBoECai
//
//  Created by yi.liu on 16/10/9.
//
//


#import <Foundation/Foundation.h>
#import "ImagePickerViewController.h"
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "CCLuaValue.h"

@interface ImagePickerViewController ()

@end

@implementation ImagePickerViewController

-(void)viewDidLoad
{
    [super viewDidLoad];
}

-(void)viewDidUnload
{
    [super viewDidUnload];
}

-(void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(void)localPhoto
{
    NSLog(@"-(void)localPhoto");
    UIImagePickerController *picker = [[UIImagePickerController alloc]init];
    picker.delegate = self;
    picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    picker.allowsEditing = YES;
    [self presentViewController:picker animated:YES completion:^(void)
     {
         NSLog(@"ImageViewController is presented");
     }];
    [picker release];
}

-(void)takePhoto
{
    UIImagePickerControllerSourceType sourceType = UIImagePickerControllerSourceTypeCamera;
    if ([UIImagePickerController isSourceTypeAvailable:sourceType])
    {
        UIImagePickerController *picker = [[UIImagePickerController alloc]init];
        picker.delegate = self;
        //设置拍照后可以编辑
        picker.allowsEditing = YES;
        picker.sourceType = sourceType;
        [self presentViewController:picker animated:YES completion:^(void)
         {
             NSLog(@"ImageViewController is presented");
         }];
    }
    else
    {
        NSLog(@"模拟器无法使用相机，请在真机中调试");
    }
    NSLog(@"-(void)takePhoto");
}

-(void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<NSString *,id> *)info
{
    NSString *type = [info objectForKey:@"UIImagePickerControllerMediaType"];
    if ([type isEqualToString:@"public.image"])
    {
        //先把图片转成NSData
        //原始图
        //UIImage *image = [info objectForKey:@"UIImagePickerControllerOriginalImage"];
        
        UIImage *image = [info objectForKey:@"UIImagePickerControllerEditedImage"];
        NSData *data;
        if (UIImagePNGRepresentation(image) == nil)
        {
            data = UIImageJPEGRepresentation(image, 1.0);
        }
        else
        {
            data = UIImagePNGRepresentation(image);
        }
        //这里将图片放在沙盒的documents/photo文件夹中
        std::string str = cocos2d::FileUtils::getInstance()->getWritablePath();
        str += "/photo";
        NSString *imgPath=[NSString stringWithUTF8String:str.c_str()];
        //文件管理器
        NSFileManager *fileManager = [NSFileManager defaultManager];
        //生成唯一字符串
        NSString *uuid = [[NSUUID UUID]UUIDString];
        //生成文件名
        NSString *fileName = [NSString stringWithFormat:@"%@.png",uuid];
        
        NSString *ImageName = fileName;
        //把刚刚由图片转成的data对象拷贝至沙盒中 并保存为xxxxx-xxxx-xxx...xxx.png
        /******保存之前最好先清空下，不然占用磁盘越来越大********/
        [fileManager removeItemAtPath:imgPath error:nil];
        /*************************************************/
        
        [fileManager createDirectoryAtPath:imgPath withIntermediateDirectories:YES attributes:nil error:nil];
        [fileManager createFileAtPath:[imgPath stringByAppendingPathComponent:fileName] contents:data attributes:nil];
        
        //得到选择后沙盒中图片的完整路径
        filePath = [[NSString alloc]initWithFormat:@"%@",[imgPath stringByAppendingPathComponent:fileName]];
        NSLog(@"=======ok ==   %@\n",filePath);
        //关闭相册界面
        [picker dismissViewControllerAnimated:YES completion:^(void){}];
        
        
        //把沙盒目录下的图片路径记录下来
        NSUserDefaults *accountDefaults = [NSUserDefaults standardUserDefaults];
        [accountDefaults setValue:ImageName forKey:@"changeImage"];
   
        
        
        //通知ImageCrop完成取图
//        const char *strFilePath = [filePath UTF8String];
//        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("ImageCropEvent",&strFilePath);
        
    }
}

-(void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    NSLog(@"您取消了照片选择");
    [picker dismissViewControllerAnimated:YES completion:^(void){}];
}

@end
