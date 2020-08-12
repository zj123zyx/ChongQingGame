/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

package org.cocos2dx.lua;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Set;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxHelper;
import org.json.JSONException;
import org.json.JSONObject;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.provider.MediaStore;
import android.provider.Settings;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.RelativeLayout;
import android.widget.Toast;
import cn.jpush.android.api.JPushInterface;
import cn.jpush.android.api.TagAliasCallback;

//import com.anysdk.framework.BuildConfig;
//import com.anysdk.framework.PluginWrapper;
//import com.genlot.xingyunjianshou.CameraMessageHandler;
//import com.genlot.xingyunjianshou.JniTestHelper;
//import com.genlot.xingyunjianshou.MessageHandler;
//import com.genlot.xingyunjianshou.UserImageUtil;
//import com.genlot.xingyunjianshou.pay.utils.BaseHelper;
//import com.genlot.xingyunjianshou.pay.utils.MobileSecurePayer;
//import com.genlot.xingyunjianshou.pay.utils.PayConstants;
//import com.genlot.xingyunjianshou.pay.utils.PayOrder;
//import com.genlot.xingyunjianshou.pay.utils.Rsa;
//import com.genlot.xingyunjianshou.receivers.ExampleUtil;
//import com.tencent.connect.share.QQShare;
//import com.tencent.mm.sdk.modelmsg.SendAuth;
//import com.tencent.mm.sdk.modelmsg.SendMessageToWX;
//import com.tencent.mm.sdk.modelmsg.WXMediaMessage;
//import com.tencent.mm.sdk.modelmsg.WXWebpageObject;
//import com.tencent.mm.sdk.openapi.IWXAPI;
//import com.tencent.mm.sdk.openapi.WXAPIFactory;
//import com.tencent.tauth.IUiListener;
//import com.tencent.tauth.Tencent;
//import com.tencent.tauth.UiError;
import android.app.AlertDialog.Builder;

//import com.hongbogufen.hongboyicai.utils.ThreadLocalUtils;
//连连支付
//照相机

@SuppressLint("NewApi")  
public class AppActivity extends Cocos2dxActivity {
	private final static String TAG = AppActivity.class.getSimpleName();
	static String hostIPAdress = "0.0.0.0";
	public static AppActivity actInstance;
//	public LoadingIndicator mDialog = null;//new LoadingIndicator(this);
	
    ////////////////////////////////////////////////////////////////////////////////////////////////
	// 照相机
//	protected MessageHandler messageHandler;
//	protected CameraMessageHandler cameraMessageHandler;
	private static final int REQUEST_CODE_GETIMAGE_BYSDCARD = 0;// 从sd卡得到图像的请求码
	private static final int REQUEST_CODE_GETIMAGE_BYCAMERA = 1;// 从相机得到图像的请求码
	private static final int CUT_PHOTO_REQUEST_CODE = 2;// 从相机得到图像的请求码
	
	private static final String PHOTO_FILE_NAME = "headImage.jpg";//"temp_photo.jpg";
	private File tempFile;
	private Bitmap bitmap;
	////////////////////////////////////////////////////////////////////////////////////////////////
	
	//QQ APP_ID
//	private static final String QQ_APPID = "1105599422";  // QQ开放平台申请到的app_id
//	private Tencent mTencent; //qq主操作对象  
//	private IUiListener loginListener; //授权登录监听器  
//	private IUiListener shareListener;//分享监听器
//	private String QQ_SCOPE; //获取信息的范围参数  

	
	//微信
//    private static final String WX_SCOPE = "snsapi_userinfo";
//    public static final String WX_STATE = "hbec_user_login";//hbec_user_login,login_state,123
//    public static final String WX_APP_ID = "wx3b4ee895965abbd6";// 微信开放平台申请到的app_id    
//    public static final String WX_APP_SECRET = "85487429b77350972d8503f9cf8dfe08";// 微信开放平台申请到的app_id对应的app_secret
//	private static IWXAPI WXapi;  
//    private String weixinCode;  
    
    private RelativeLayout mRLayout;  
    
    //极光推送
    public static boolean isForeground = false;
    
    // 支付验证方式 0：标准版本， 1：卡前置方式，接入时，只需要配置一种即可，Demo为说明用。可以在menu中选择支付方式。
    private int pay_type_flag = 0;
    private boolean is_preauth = false;
    
    private String m_orderId = "";
    private String m_accountId = "";
    private String m_sessionId = "";
    private String m_money_order = "";

 
    //微信注册
//	private void registerToWx() {
//		setWXapi(WXAPIFactory.createWXAPI(this, WX_APP_ID, true));
//		getWXapi().registerApp(WX_APP_ID);
//	}
    
	/**
     * 退出
     */
    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
    	if (event.getKeyCode() == KeyEvent.KEYCODE_BACK  &&
    			event.getAction() == KeyEvent.ACTION_DOWN  && 
    			event.getRepeatCount() == 0) {                       
    		//具体的操作代码
    		Log.d(TAG, "==============返回键 ====11=====" );
    		dialog_Exit(this);
    		
    	}
    	return super.dispatchKeyEvent(event);
    	
 
    } 
    
    public void dialog_Exit(Context context) {
        AlertDialog.Builder builder = new Builder(context);
        builder.setMessage("确定要退出吗?");
        builder.setTitle("提示");
        builder.setIcon(android.R.drawable.ic_dialog_alert);
        builder.setPositiveButton("确认",
                new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                        //android.os.Process.killProcess(android.os.Process.myPid());
                        //System.exit(0);// 否则退出程序
                        Intent intent = new Intent(Intent.ACTION_MAIN);  
                        intent.addCategory(Intent.CATEGORY_HOME);  
                        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);  
                        startActivity(intent);  
                        android.os.Process.killProcess(android.os.Process.myPid());  
                    }
                });
       
        builder.setNegativeButton("取消",
                new android.content.DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();
                    }
                });
        builder.create().show();
    }
	
   
    @TargetApi(Build.VERSION_CODES.HONEYCOMB)
	@Override
    public void onWindowFocusChanged(boolean hasFocus) {
            super.onWindowFocusChanged(hasFocus);
//        if (hasFocus) {
//        	 getWindow().getDecorView().setSystemUiVisibility(
//                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
//                    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
//                    | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
//                    | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
//                    | View.SYSTEM_UI_FLAG_FULLSCREEN
//                    | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);}
    }
	
	@TargetApi(Build.VERSION_CODES.HONEYCOMB)
	@Override
	protected void onCreate(Bundle savedState)
    {
        super.onCreate(savedState);
        //隐藏虚拟按键
//        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN 
//        		| View.SYSTEM_UI_FLAG_HIDE_NAVIGATION 
//        		| View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY); 

//        PluginWrapper.init(this); // for plugins
//        PluginWrapper.setGLSurfaceView(Cocos2dxGLSurfaceView.getInstance());
        //wrapper.nativeInitPlugins();
        
        actInstance = this;
//        mDialog = new LoadingIndicator(this);
        
        
//      WindowManager.LayoutParams lp = getWindow().getAttributes();
//      lp.flags |= WindowManager.LayoutParams.FLAG_FULLSCREEN;
//      getWindow().setAttributes(lp);
//      getWindow().addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
      
      //状态栏显示在游戏内
      Window window = getWindow();
//      window.addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);    //状态栏沉浸式
//      window.addFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_NAVIGATION);// 导航栏 沉浸式
      window.addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);   //显示导航栏  隐藏状态栏

      
//      int  flags = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE ; //暂时隐藏导航栏
//      getWindow().getDecorView().setSystemUiVisibility(flags);  
     
      
      
      //自动隐藏导航栏状态栏
//     int flag =  View.SYSTEM_UI_FLAG_LAYOUT_STABLE
//      | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
//      | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
//      | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
//      | View.SYSTEM_UI_FLAG_FULLSCREEN 
//      | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
//     getWindow().getDecorView().setSystemUiVisibility(flag);  
        
        
        //创建QQ
//        initData();
        
        //注册微信
//        registerToWx();
        
        //Jpush
//        JPushInterface.setDebugMode(BuildConfig.DEBUG);// 设置开启日志,发布时请关闭日志
//        JPushInterface.init(this);
//        
//        registerMessageReceiver();  // used for receive msg
        
//		String appKey = ExampleUtil.getAppKey(getApplicationContext());
//		if (null == appKey) appKey = "AppKey异常";
//		Log.d(TAG, "appKey =  " + appKey );
        
//        if(nativeIsLandScape()) {
//            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_LANDSCAPE);
//        } else {
//            setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);
//        }
        
        //2.Set the format of window
        
        // Check the wifi is opened when the native is debug.
        if(nativeIsDebug())
        {
            getWindow().setFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON, WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
            if(!isNetworkConnected())
            {
                AlertDialog.Builder builder=new AlertDialog.Builder(this);
                builder.setTitle("Warning");
                builder.setMessage("Please open WIFI for debuging...");
                builder.setPositiveButton("OK",new DialogInterface.OnClickListener() {
                    
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        startActivity(new Intent(Settings.ACTION_WIFI_SETTINGS));
                        finish();
                        System.exit(0);
                    }
                });

                builder.setNegativeButton("Cancel", null);
                builder.setCancelable(true);
                builder.show();
            }
            hostIPAdress = getHostIpAddress();
        } 
        
        //初始化照片
//        initJavaJni();
        
        Log.d(TAG, "onCreate " );
   
       
    }
	
	//初始化照相变量
//	protected void initJavaJni() {
//		Looper looper = Looper.myLooper();
//		messageHandler = new MessageHandler(looper);
//		UserImageUtil.messageHandler=messageHandler;
//		
//		
//		Looper camearLooper = Looper.myLooper();
//		cameraMessageHandler = new CameraMessageHandler(camearLooper);
//		UserImageUtil.cameraMessageHandler=cameraMessageHandler;
//		
//	}
	//执行android的页面跳转，
    public Object gotoActivity()
    {
//    	actInstance.runOnUiThread(new Runnable() {
//
//			@Override
//			public void run() {
//				CharSequence[] items = { "手机相册", "手机拍照", "取消" };
//				actInstance.imageChooseItem(items);
//			}
//    	 });
    	Log.d(TAG, "gotoActivity " );
    	  System.out.println("====gotoActivity=========");
		// 手机选图
		Intent intent = new Intent(Intent.ACTION_PICK);
		intent.setType("image/*");
		startActivityForResult(intent,REQUEST_CODE_GETIMAGE_BYSDCARD);
    	
		return null;
    	
    }
    
	//执行android的页面跳转，
    public Object gotoActivityCamera()
    {
    	Log.d(TAG, "gotoActivityCamera " );
    	// 拍照
		Intent intent = new Intent("android.media.action.IMAGE_CAPTURE");
		if (hasSdcard()) {
			intent.putExtra(MediaStore.EXTRA_OUTPUT,Uri.fromFile(new File(Environment.getExternalStorageDirectory(), PHOTO_FILE_NAME)));
		}
		startActivityForResult(intent, REQUEST_CODE_GETIMAGE_BYCAMERA);
    	
		return null;
    	
    }
    
    /**
	 * 操作选择
	 * 
	 * @param items
	 */
//	public void imageChooseItem(CharSequence[] items) {
//		AlertDialog imageDialog = new AlertDialog.Builder(this)
//				.setTitle("增加图片")
//				.setItems(items, new DialogInterface.OnClickListener() {
//					public void onClick(DialogInterface dialog, int item) {
//						if (item == 0) {
//							// 手机选图
//							Intent intent = new Intent(Intent.ACTION_PICK);
//							intent.setType("image/*");
//							startActivityForResult(intent,REQUEST_CODE_GETIMAGE_BYSDCARD);
//						}
//						// 拍照
//						else if (item == 1) {
//							Intent intent = new Intent("android.media.action.IMAGE_CAPTURE");
//							if (hasSdcard()) {
//								intent.putExtra(MediaStore.EXTRA_OUTPUT,
//										Uri.fromFile(new File(Environment
//												.getExternalStorageDirectory(), PHOTO_FILE_NAME)));
//							}
//							startActivityForResult(intent, REQUEST_CODE_GETIMAGE_BYCAMERA);
//						}
//						else if (item == 2) {
//							
//						}
//					}
//				}).create();
//
//		imageDialog.show();
//	}
	
	 public static final String IMAGE_UNSPECIFIED = "image/*";
		
		public void startPhotoZoom(Uri uri) {
			System.out.println(uri);
			Intent intent = new Intent("com.android.camera.action.CROP");
			intent.setDataAndType(uri, IMAGE_UNSPECIFIED);
			intent.putExtra("crop", "true");
			// aspectX aspectY 是宽高的比例
			intent.putExtra("aspectX", 1);
			intent.putExtra("aspectY", 1);
			// outputX outputY 是裁剪图片宽高
			intent.putExtra("outputX", 68);
			intent.putExtra("outputY", 68);
			intent.putExtra("outputFormat", "JPEG");
			intent.putExtra("noFaceDetection", true);
			intent.putExtra("return-data", true);
			
			startActivityForResult(intent, CUT_PHOTO_REQUEST_CODE);
		}
		
		private boolean hasSdcard() {
			if (Environment.getExternalStorageState().equals(
					Environment.MEDIA_MOUNTED)) {
				return true;
			} else {
				return false;
			}
		}

	//////////////////////////////////////////////////////////////////////////////////////////////////////
    
	@Override
	protected void onDestroy() {
		unregisterReceiver(mMessageReceiver);
		//退出登录接口
		//JniTestHelper.setDestoryActivity();
//		PluginWrapper.onDestroy();
		super.onDestroy();
//		this.mDialog.dismiss();
		Log.d(TAG, "onDestroy " );
	}

	@Override
	protected void onPause() {
		isForeground = false;
//		PluginWrapper.onPause();
		super.onPause();
		Log.d(TAG, "onPause " );
	}

	@Override
	protected void onResume() {
		isForeground = true;
//		PluginWrapper.onResume();
		super.onResume();
		Log.d(TAG, "onResume " );
	}


	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
//		PluginWrapper.onActivityResult(requestCode, resultCode, data);
		Log.d(TAG, "-----requestCode------- " + requestCode);
		Log.d(TAG, "-----resultCode-------- " + resultCode);
        if (requestCode == 10100) {//Constants.REQUEST_LOGIN QQ10100登录成功  10103分享成功
            if (resultCode == -1) {
//            	Tencent.handleResultData(data, loginListener);
            }
        }
		super.onActivityResult(requestCode, resultCode, data);
		
		Log.d(TAG, "-------------------------- " );
		
		// 从相册取图片
		if (requestCode == REQUEST_CODE_GETIMAGE_BYSDCARD) {
			Log.d(TAG, "-----REQUEST_CODE_GETIMAGE_BYSDCARD-------- ");
				if (data != null) {
					Uri selectedImage = data.getData();
					startPhotoZoom(selectedImage);
				}
		}
		// 拍摄图片
		else if (requestCode == REQUEST_CODE_GETIMAGE_BYCAMERA) {
			Log.d(TAG, "-----REQUEST_CODE_GETIMAGE_BYCAMERA-------- ");
				if (hasSdcard()) {
					Log.d(TAG, "-----hasSdcard-------- ");
					tempFile = new File(Environment.getExternalStorageDirectory(),
							PHOTO_FILE_NAME);
					Log.d(TAG, "-----tempFile-------- ");
					startPhotoZoom(Uri.fromFile(tempFile));
				}else {
					Toast.makeText(this, "not found sdcard", Toast.LENGTH_SHORT).show();
				}	
		} else if (requestCode == CUT_PHOTO_REQUEST_CODE) {
			Log.d(TAG, "-----CUT_PHOTO_REQUEST_CODE-------- ");
				if (data != null) {
					bitmap = data.getParcelableExtra("data");
				}
				if (bitmap != null){
					Log.d(TAG, "-----bitmap-------- ");
					String writePath = Cocos2dxHelper.getCocos2dxWritablePath();
					//String writePath = Environment.getExternalStorageDirectory().getAbsolutePath();
					
			        SharedPreferences sharedPreferences = getSharedPreferences("num", 0);
			        int num = sharedPreferences.getInt("num", 0) + 1;
			        SharedPreferences.Editor  editor = sharedPreferences.edit();
			        editor.putInt("num",num);
			        editor.commit();
			        
			        System.out.println("num = " + num);
					
			        String fullFileName = writePath+"/"+"head_"+num+".jpg";
					File f = new File(fullFileName); 
					
					System.out.println("fullFileName = " + fullFileName);
					
					//删除过去的图片
					deleteOldImage(writePath, num);
					
					try { 
						FileOutputStream out = new FileOutputStream(f); 
						bitmap.compress(Bitmap.CompressFormat.JPEG, 100, out); 
						out.flush(); 
						out.close(); 
						
						if(tempFile!=null){
							boolean delete = tempFile.delete();
							System.out.println("delete = " + delete);
						}
						
			        } catch (Exception e) {
			        	System.out.println("catch");
			            e.printStackTrace();
			        }
					
					
					Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable() {
			               @Override
			               public void run() {
			            	   SharedPreferences sharedPreferences = getSharedPreferences("num", 0);
			   		        	int num = sharedPreferences.getInt("num", 0);
			   		        	System.out.println("queueEvent run num = " + num);
//			   		        	UserImageUtil.nativeSetHeadImg("head_"+num+".jpg");
			            	    //UserImageUtil.nativeSetHeadImg("headImage.jpg");
			               }
			        });
				}		
		}
		Log.d(TAG, "onActivityResult " );
	}
	
	protected void deleteOldImage(String writePath, int num) {
		Log.d(TAG, "deleteOldImage " + num);
		if (num - 1 > 0) {
			String fullFileName = writePath+"/"+"head_"+(num-1)+".jpg";
			//System.out.println("fullFileName = " + fullFileName);
			File f = new File(fullFileName); 
			if (f.exists()) { 
				//删除图片
				f.delete(); 
				//发送广播刷新缩略图
				Intent scanIntent = new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE); 
				scanIntent.setData(Uri.fromFile(new File(fullFileName))); 
				this.sendBroadcast(scanIntent); 
			} 
		}
		
	}

	@Override
	protected void onNewIntent(Intent intent) {
//		PluginWrapper.onNewIntent(intent);
		super.onNewIntent(intent);
		Log.d(TAG, "onNewIntent " );
	}

	@Override
	protected void onStop() {
//		PluginWrapper.onStop();
		super.onStop();
		Log.d(TAG, "onStop " );
	}

	@Override
	protected void onRestart() {
//		PluginWrapper.onRestart();
		super.onRestart();
		//AppLuaApi.showIndicator();
		Log.d(TAG, "onRestart " );
	}
	private boolean isNetworkConnected() {
        ConnectivityManager cm = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);  
        if (cm != null) {  
            NetworkInfo networkInfo = cm.getActiveNetworkInfo();  
        ArrayList networkTypes = new ArrayList();
        networkTypes.add(ConnectivityManager.TYPE_WIFI);
        try {
            networkTypes.add(ConnectivityManager.class.getDeclaredField("TYPE_ETHERNET").getInt(null));
        } catch (NoSuchFieldException nsfe) {
        }
        catch (IllegalAccessException iae) {
            throw new RuntimeException(iae);
        }
        if (networkInfo != null && networkTypes.contains(networkInfo.getType())) {
                return true;  
            }  
        }  
        return false;  
    } 
 
	public String getHostIpAddress() {
	    WifiManager wifiMgr = (WifiManager) getSystemService(WIFI_SERVICE);
	    WifiInfo wifiInfo = wifiMgr.getConnectionInfo();
	    int ip = wifiInfo.getIpAddress();
	    return ((ip & 0xFF) + "." + ((ip >>>= 8) & 0xFF) + "." + ((ip >>>= 8) & 0xFF) + "." + ((ip >>>= 8) & 0xFF));
	}
	
	public static String getLocalIpAddress() {
	    return hostIPAdress;
	}
	
	private static native boolean nativeIsLandScape();
	private static native boolean nativeIsDebug();

//    private void initData() {  
//        //初始化qq主操作对象  
//        mTencent = Tencent.createInstance(QQ_APPID, AppActivity.this);  
//        //要所有权限，不然会再次申请增量权限，这里不要设置成get_user_info,add_t  
//        QQ_SCOPE = "all";  
//          
//        loginListener = new IUiListener() {  
//  
//            @Override  
//            public void onError(UiError uiError) {  
//                // TODO Auto-generated method stub  
//            	//登录失败后回调该方法
//                Toast.makeText(AppActivity.this, "登录失败", Toast.LENGTH_SHORT).show();
//                Log.e("LoginError:", uiError.toString());
//            }  
//  
//            /** 
//             * 返回json数据样例 
//             *  
//             * {"ret":0,"pay_token":"D3D678728DC580FBCDE15722B72E7365", 
//             * "pf":"desktop_m_qq-10000144-android-2002-", 
//             * "query_authority_cost":448, 
//             * "authority_cost":-136792089, 
//             * "openid":"015A22DED93BD15E0E6B0DDB3E59DE2D", 
//             * "expires_in":7776000, 
//             * "pfkey":"6068ea1c4a716d4141bca0ddb3df1bb9", 
//             * "msg":"", 
//             * "access_token":"A2455F491478233529D0106D2CE6EB45", 
//             * "login_cost":499} 
//             */  
//            @Override  
//            public void onComplete(Object value) {  
//                // TODO Auto-generated method stub  
//                  
//                System.out.println("有数据返回..");  
//                if (value == null) {  
//                    return;  
//                }  
//  
//                try {  
//                    JSONObject jo = (JSONObject) value;  
//  
//                    int ret = jo.getInt("ret");  
//                      
//                    System.out.println("json=" + String.valueOf(jo));  
//                      
//                    if (ret == 0) {  
//                        Toast.makeText(AppActivity.this, "登录成功",  Toast.LENGTH_LONG).show();  
//  
//                        String openID = jo.getString("openid");  
//                        String accessToken = jo.getString("access_token");  
////                        String expires = jo.getString("expires_in");  
////                        mTencent.setOpenId(openID);  
////                        mTencent.setAccessToken(accessToken, expires);  
//                        Log.d(TAG, "openID " + openID);
//                        Log.d(TAG, "accessToken " + accessToken);
//                        //回调到cpp调用接口
////                        JniTestHelper.returnToLuaWithOpenIDAndAccessToken(openID, accessToken);
//                    }  
//  
//                } catch (Exception e) {  
//                    // TODO: handle exception  
//                	e.printStackTrace();
//                }  
//  
//            }  
//
//  
//            @Override  
//            public void onCancel() {  
//                // TODO Auto-generated method stub  
//            	//取消登录后回调该方法
//                Toast.makeText(AppActivity.this, "取消登录", Toast.LENGTH_SHORT).show();
//            }  
//        };  
//        
//      //qq分享的回调接口
//        shareListener = new IUiListener() {
//            @Override
//            public void onComplete(Object o) {
//                //分享成功后回调
//                Toast.makeText(AppActivity.this, "分享成功！", Toast.LENGTH_SHORT).show();
//            }
//
//            @Override
//            public void onError(UiError uiError) {
//                //分享失败后回调
//            }
//
//            @Override
//            public void onCancel() {
//                //取消分享后回调
//            }
//        };
//    }  
//    
//	//qq登录
//	public void qqLogin() {
//		//login(); 
//		//开始qq授权登录  
//        mTencent.login(AppActivity.this, QQ_SCOPE, loginListener); 
//	}
//    
//  //qq分享
//    public void qqShare() throws IOException {
//        Bundle params = new Bundle();
//        params.putInt(QQShare.SHARE_TO_QQ_KEY_TYPE, QQShare.SHARE_TO_QQ_TYPE_DEFAULT);
//        params.putString(QQShare.SHARE_TO_QQ_TITLE, "鸿博易彩");
//        params.putString(QQShare.SHARE_TO_QQ_SUMMARY,"鸿博易彩，赢超级大奖！");
//        params.putString(QQShare.SHARE_TO_QQ_TARGET_URL,"https://itunes.apple.com/us/app/hong-bo-yi-cai/id1147435653?l=zh&ls=1&mt=8");
//        
////        InputStream is =getResources().getAssets().open("res/Icon-80.png");
////        String path = new String(InputStreamToByte(is)); 
//        //获取要分享图片的绝对路径
//        String path = sendImgFriend();
//        
//        System.out.println("========qqShare path========== "+path);
//        
//        params.putString(QQShare.SHARE_TO_QQ_IMAGE_URL, path);
//        params.putString(QQShare.SHARE_TO_QQ_APP_NAME, "鸿博易彩");
//        mTencent.shareToQQ(this, params, shareListener);
//    }
    
    /** 
     *  
     * @param 输入流 
     * 将输入流转换成为一个字节数组
     */ 
    private byte[] InputStreamToByte(InputStream is) throws IOException {
        ByteArrayOutputStream bytestream = new ByteArrayOutputStream();
        int ch;
        while ((ch = is.read()) != -1) {
            bytestream.write(ch);
        }
        byte imgdata[] = bytestream.toByteArray();
        bytestream.close();
        return imgdata;
    }
    
    /** 
     *  
     * @param bs 
     * 把字节数组写到SDCard中,然后再读取该图片 
     */  
    public void writetoSDCard(byte []bs){  
        try {  
            FileOutputStream out=new FileOutputStream(new File("/sdcard/shareQQIcon.png")); //重新命名的图片为shareQQIcon.png.想要获取的图片的路径就是该图片的路径  
            try {  
                out.write(bs);  
                out.flush();  
                out.close();  
            } catch (IOException e) {  
                // TODO Auto-generated catch block  
                e.printStackTrace();  
            }  
        } catch (FileNotFoundException e) {  
            // TODO Auto-generated catch block  
            e.printStackTrace();  
        }  
    } 
    
    /** 
     *  
     * 通过Environment类中的一些方法获取String类型的绝对路径
     */ 
    public String sendImgFriend() throws IOException{  
        //InputStream abpath=getClass().getResourceAsStream("/assets/picture/logo.png");  
    	//将该文件夹下面的文件转换成为一个输入流
        InputStream abpath =getResources().getAssets().open("res/Icon-80.png");
      
        try {  
            writetoSDCard(InputStreamToByte(abpath));  
                  
        } catch (IOException e) {  
            // TODO Auto-generated catch block  
            e.printStackTrace();  
        }  
        
        String path_img=Environment.getExternalStorageDirectory().getAbsolutePath()+"/shareQQIcon.png";
        return path_img;
    }
    
//	//微信登录
//	public void weixinLogin() {
//		Log.d(TAG, "=======weixinLogin======== ");
//
//	     SendAuth.Req req = new SendAuth.Req();  
//	     req.scope = WX_SCOPE;  
//	     req.state = WX_STATE;  
//	     if(getWXapi()==null){
//	    	 Toast.makeText(getApplicationContext(), "向微信发起请求失败",Toast.LENGTH_LONG).show();
//	    	 return;
//	     }
//	     getWXapi().sendReq(req);  
//	     Log.d(TAG, "微信登录正在后台操作...");
//	}
//        
//    /** 
//    * 微信分享 flag 0-分享到微信好友 ；1-分享到微信朋友圈
//    * @param get_user_info_url 调用URL 
//    */ 
//    public void wechatShare(int flag) throws IOException{  
//       Log.d(TAG, "=======wechatShare======== " + flag);
//       WXWebpageObject webpage = new WXWebpageObject();  
//       webpage.webpageUrl = "https://itunes.apple.com/us/app/hong-bo-yi-cai/id1147435653?l=zh&ls=1&mt=8";  
//       WXMediaMessage msg = new WXMediaMessage(webpage);  
//       msg.title = "鸿博易彩";  
//       msg.description = "鸿博易彩，赢超级大奖！";  
//       //这里替换一张自己工程里的图片资源  
//
//       InputStream is =getResources().getAssets().open("res/Icon-80.png");
//       Bitmap thumb = BitmapFactory.decodeStream(is);  
//       msg.setThumbImage(thumb);  
//              
//       SendMessageToWX.Req req = new SendMessageToWX.Req();  
//       req.transaction = String.valueOf(System.currentTimeMillis());  
//       req.message = msg;  
//       req.scene = flag==0?SendMessageToWX.Req.WXSceneSession:SendMessageToWX.Req.WXSceneTimeline;  
//       getWXapi().sendReq(req); 
//     }
//
//	public static IWXAPI getWXapi() {
//		return WXapi;
//	}
//
//	public static void setWXapi(IWXAPI wXapi) {
//		WXapi = wXapi;
//	}
	
	//for receive customer msg from jpush server
	private MessageReceiver mMessageReceiver;
	public static final String MESSAGE_RECEIVED_ACTION = "com.hongbogufen.hongboyicai.MyReceiver.MESSAGE_RECEIVED_ACTION";
	public static final String KEY_TITLE = "title";
	public static final String KEY_MESSAGE = "message";
	public static final String KEY_EXTRAS = "extras";
	
	public void registerMessageReceiver() {
		mMessageReceiver = new MessageReceiver();
		IntentFilter filter = new IntentFilter();
		filter.setPriority(IntentFilter.SYSTEM_HIGH_PRIORITY);
		filter.addAction(MESSAGE_RECEIVED_ACTION);
		registerReceiver(mMessageReceiver, filter);
	}

	public class MessageReceiver extends BroadcastReceiver {

		@Override
		public void onReceive(Context context, Intent intent) {
			if (MESSAGE_RECEIVED_ACTION.equals(intent.getAction())) {
              String messge = intent.getStringExtra(KEY_MESSAGE);
              String extras = intent.getStringExtra(KEY_EXTRAS);
              StringBuilder showMsg = new StringBuilder();
              showMsg.append(KEY_MESSAGE + " : " + messge + "\n");
//              if (!ExampleUtil.isEmpty(extras)) {
//            	  showMsg.append(KEY_EXTRAS + " : " + extras + "\n");
//              }
              setCostomMsg(showMsg.toString());
			}
		}
	}
	
	private void setCostomMsg(String msg){
		Log.d(TAG, " setCostomMsg == " + msg);
//		 if (null != msgText) {
//			 msgText.setText(msg);
//			 msgText.setVisibility(android.view.View.VISIBLE);
//         }
	}
	
	//设置别名
    public void setJPushTag(String userName) {
        mHandler.sendMessage(mHandler.obtainMessage(MSG_SET_ALIAS, userName));
    }

    private static final int MSG_SET_ALIAS = 1001;
    private static final int MSG_SET_TAGS = 1002;
    private final Handler mHandler = new Handler() {
        @Override
        public void handleMessage(android.os.Message msg) {
            super.handleMessage(msg);
            switch (msg.what) {
                case MSG_SET_ALIAS:
                    Log.d(TAG, "Set alias in handler.");
                    JPushInterface.setAliasAndTags(AppActivity.actInstance, (String) msg.obj, null, mTagsAliasCallback);
                    break;

                case MSG_SET_TAGS:
                    Log.d(TAG, "Set tags in handler.");
                    JPushInterface.setAliasAndTags(AppActivity.actInstance, null, (Set<String>) msg.obj, mTagsAliasCallback);
                    break;

                default:
                    Log.d(TAG, "Unhandled msg - "+ msg.what);
            }
        }
    };
    private final TagAliasCallback mTagsAliasCallback = new TagAliasCallback() {

        @Override
        public void gotResult(int code, String alias, Set<String> tags) {
            String logs;
            switch (code) {
                case 0:
                    logs = "Set tags and alias success";
                    Log.d(TAG, "=======TagAliasCallback======== "+logs);
                    break;
                case 6002:
                    logs = "Failed to set alias and tags due to timeout. Try again after 60s.";
                    Log.d(TAG, "=======TagAliasCallback======== "+logs);
                    break;

                default:
                    logs = "Failed with errorCode = " + code;
                    Log.d(TAG, "=======TagAliasCallback======== "+logs);
            }
        }

    };
      
	public void setAndroidStatusBar(int sign) {

		Log.d(TAG, "setAndroidStatusBar = " + sign);
        if (sign == 1) {
        	Log.d(TAG, " sign == " + sign);
        	
        	
        	
        	
        	
        	//mRLayout.setSystemUiVisibility(View.SYSTEM_UI_FLAG_VISIBLE); 
//            WindowManager.LayoutParams lp = getWindow().getAttributes();
//            lp.flags |= WindowManager.LayoutParams.FLAG_FULLSCREEN;
//            getWindow().setAttributes(lp);
//           getWindow().addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
//        	getWindow().getDecorView().setSystemUiVisibility(
//        	            View.SYSTEM_UI_FLAG_LAYOUT_STABLE
//        	            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
//        	            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN);
        	
        	

        } else if (sign == 2) {
        	Log.d(TAG, " sign == " + sign);
        	//mRLayout.setSystemUiVisibility(View.INVISIBLE);
        	mRLayout.setSystemUiVisibility(
        			View.SYSTEM_UI_FLAG_LAYOUT_STABLE
        			| View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
        			| View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
        			| View.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
        			| View.SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
        			| View.SYSTEM_UI_FLAG_IMMERSIVE);
//            WindowManager.LayoutParams attr = getWindow().getAttributes();
//            attr.flags &= (~WindowManager.LayoutParams.FLAG_FULLSCREEN);
//            getWindow().setAttributes(attr);
//            getWindow().clearFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
//        	getWindow().getDecorView().setSystemUiVisibility(
//                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
//                    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
//                    | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
//                    | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
//                    | View.SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
//                    | View.SYSTEM_UI_FLAG_IMMERSIVE);
//        	getWindow().getDecorView().setSystemUiVisibility(
//        			View.SYSTEM_UI_FLAG_LAYOUT_STABLE
//        			| View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
//        			| View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
//        			| View.SYSTEM_UI_FLAG_HIDE_NAVIGATION // hide nav bar
//        			| View.SYSTEM_UI_FLAG_FULLSCREEN // hide status bar
//        			| View.SYSTEM_UI_FLAG_IMMERSIVE);

        }
    }
	
//	public void payClick(String orderinfo) throws JSONException {
//		Log.d(TAG, " payClick  ");
//		PayOrder order = null;
//        // 标准模式
//        order = constructGesturePayOrder(orderinfo);
//        
////        order.setCard_no("9558374827648478467");
//        
//        String content4Pay = BaseHelper.toJSONString(order);
//
//        // 关键 content4Pay 用于提交到支付SDK的订单支付串，如遇到签名错误的情况，请将该信息帖给我们的技术支持
//       // Log.i(StandActivity.class.getSimpleName(), content4Pay);
//        Log.d(TAG, " pay == " + content4Pay);
//        MobileSecurePayer msp = new MobileSecurePayer();
//        boolean bRet = msp.pay(content4Pay, mPayHandler,
//        		PayConstants.RQF_PAY, this, false);
//        Log.d(TAG, " pay == " + String.valueOf(bRet));
//        
//	}
	

//    private Handler mPayHandler = createHandler();

//    private Handler createHandler() {
//        return new Handler() {
//            public void handleMessage(android.os.Message msg) {
//            	super.handleMessage(msg);
//                String strRet = (String) msg.obj;
//                switch (msg.what) {
//                    case PayConstants.RQF_PAY: {
//                        JSONObject objContent = BaseHelper.string2JSON(strRet);
//                        String retCode = objContent.optString("ret_code");
//                        String retMsg = objContent.optString("ret_msg");
//                        
//                        String result_pay = "";
//                        String oid_paybill = "";
//                        
//                        Log.d(TAG, " retCode == " + retCode);
//                        Log.d(TAG, " retMsg == " + retMsg);
//
//                        // 成功
//                        if (PayConstants.RET_CODE_SUCCESS.equals(retCode)) {
//                        	result_pay = objContent.optString("result_pay");
//                            oid_paybill = objContent.optString("oid_paybill");
//                            Log.d(TAG, " result_pay == " + result_pay);
//                            Log.d(TAG, " oid_paybill == " + oid_paybill);
//                            BaseHelper.showDialog(AppActivity.actInstance, "提示",
//                                    "支付成功，交易状态码：" + retCode +" 返回报文:"+strRet,
//                                    android.R.drawable.ic_dialog_alert);
//                        } else if (PayConstants.RET_CODE_PROCESS.equals(retCode)) {
//                            // TODO 处理中，掉单的情形
//                            String resulPay = objContent.optString("result_pay");
//                            if (PayConstants.RESULT_PAY_PROCESSING
//                                    .equalsIgnoreCase(resulPay)) {
//                                BaseHelper.showDialog(AppActivity.actInstance, "提示",
//                                        objContent.optString("ret_msg") + "交易状态码："
//                                                + retCode +" 返回报文:"+strRet,
//                                        android.R.drawable.ic_dialog_alert);
//                            }
//
//                        } else {
//                            // TODO 失败
//                            BaseHelper.showDialog(AppActivity.actInstance, "提示", retMsg
//                                    + "，交易状态码:" + retCode +" 返回报文:"+strRet,
//                                    android.R.drawable.ic_dialog_alert);
//                        }
//                        
//                        //把结果回调到服务器
////                        JniTestHelper.sendLLpayResultToServer(retCode, retMsg, result_pay, oid_paybill, m_money_order, m_orderId);
//                    }
//                    break;
//                }
//                super.handleMessage(msg);
//            }
//        };
//
//    }
//
//    //标准版本
//    private PayOrder constructGesturePayOrder(String orderinfo) throws JSONException {
//    	Log.d(TAG, " constructGesturePayOrder " +  orderinfo);
//    	//获取json数据
//    	JSONObject orderJSON = new JSONObject(orderinfo);  
//    	String orderId = orderJSON.getString("orderId");
//    	String createTime = orderJSON.getString("createTime");
//    	String accountId = orderJSON.getString("accountId");
//    	String oid_partner = orderJSON.getString("oid_partner");
//    	String sign_type = orderJSON.getString("sign_type");
//    	String buis_partner = orderJSON.getString("buis_partner");
//    	String notify_url = orderJSON.getString("notify_url");
//    	String rsa_private_key = orderJSON.getString("rsa_private_key");
//    	String registerTime = orderJSON.getString("registerTime");
//    	String phoneNumber = orderJSON.getString("phoneNumber");
//    	String money_order = orderJSON.getString("money_order");
//    	
//        m_orderId = orderId;
//        m_money_order = money_order;
//
////    	Log.d(TAG, " orderId " +  orderId);
////    	Log.d(TAG, " createTime " +  createTime);
////    	Log.d(TAG, " accountId " +  accountId);
////    	Log.d(TAG, " oid_partner " +  oid_partner);
////    	Log.d(TAG, " sign_type " +  sign_type);
////    	Log.d(TAG, " buis_partner " +  buis_partner);
////    	Log.d(TAG, " notify_url " +  notify_url);
////    	Log.d(TAG, " rsa_private_key " +  rsa_private_key);
////    	Log.d(TAG, " registerTime " +  registerTime);
////    	Log.d(TAG, " phoneNumber " +  phoneNumber);
////    	Log.d(TAG, " money_order " +  money_order);
//        
//
//        PayOrder order = new PayOrder();
//        order.setBusi_partner(buis_partner);
//        order.setNo_order(orderId);
//        order.setDt_order(createTime);
//        order.setName_goods("鸿博易彩充值");
//        order.setNotify_url(notify_url);
//
//        // TODO RSA 签名方式
//        order.setSign_type(sign_type);
//        
//        order.setValid_order("10080");
//        order.setMoney_order(money_order);
//
//        // 风险控制参数
//        order.setRisk_item(constructRiskItem(accountId, registerTime, phoneNumber));
//
//        order.setOid_partner(oid_partner);
//        
//        String content = BaseHelper.sortParam(order);
//        // TODO MD5 签名方式, 签名方式包括两种，一种是MD5，一种是RSA 这个在商户站管理里有对验签方式和签名Key的配置。
//        // RSA 签名方式
//        String sign = "";
//        sign = Rsa.sign(content, rsa_private_key);
//        order.setSign(sign);
//        
//        return order;
//    }

    private String constructRiskItem(String accountId,String registerTime, String phoneNumber) {
        JSONObject mRiskItem = new JSONObject();
        try {
            mRiskItem.put("frms_ware_category", "1003");
            mRiskItem.put("user_info_mercht_userno", accountId);
            mRiskItem.put("user_info_bind_phone", phoneNumber);
            mRiskItem.put("user_info_dt_register", registerTime);
            //mRiskItem.put("request_imei", "1122111221");

        } catch (JSONException e) {
            e.printStackTrace();
        }

        return mRiskItem.toString();
    }

}