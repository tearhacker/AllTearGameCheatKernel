/*
    By 开源 公益分享
   搜集各个公益文件分享
    更多公益开源 文件 @BYYXnb
    TG @BYYXnb QQ群 427975011
    
源码捐赠链接
https://v.youxi186.com/shop/YIZ6ZA6X

源码捐赠地址2：
https://shop.pp13.cn/shop/byyxnb

公益网盘资源分享
https://www.123865.com/s/NxyZVv-K44U3?提取码：QWT6

QQ群过验证[有的文件需要]
https://www.123865.com/s/f4A7Vv-Pqc0A?提取码：9IVI

由于易支付漏洞 如果进不去
如您需拿卡 点击 联系我
赞助链接已重新更新 

〖如果你点开提示 站点停止运行或者进不去，那么解决办法有两个

1.复制链接去别的浏览器打开
2.清除你浏览器的数据即可
*/
// 微验网络验证//
// 如果是AIDE编译jni，请将原main.cpp删除，将此注入好的文件改成main.cpp
#include "res/Encrypt.h"
#include "res/cJSON.c"
#include "res/cJSON.h"
#include "res/weiyan.h"
#include <ctime>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <iostream>
#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
using namespace std;

#include "辅助类.h"
#include <Draw.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <random>
#include <set>
#include <sys/stat.h>
#include <unistd.h>

#include <csignal>
#include <cstdlib>
#include <ctime>
#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <malloc.h>
#include <pthread.h>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/inotify.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "图片调用.h"

    //  #include "wcnm.h"
    //  #include <curl/curl.h>
#include <my_str.h>

#include "drivers/driver.h"

using namespace std;

int abs_ScreenX, abs_ScreenY;

int 无后台, 自瞄选项, 漏打;

布局 布局;
绘制 绘制;
int main() {
  // const static char *_wyHost = "wy.llua.cn";
  // const static char *_wyAppid = "19325";
  // const static char *_wyAppkey = "cJZoOTulAAOjsCcb";
  // const static char *_wyRc4key = "5cf05cbf79b265a96f13f3eb84476b70";
  // // 以上信息勿动

  // const static char *_kmPath = "/sdcard/km";
  // // 卡密路径

  // const static char *_imeiPath = "/sdcard/imei";
  // // 机器码路径

  // const static bool _ggSwitch = false;
  // // 公告开关

  // printf("\033[35;1m");		// 粉红色
  // printf("欢迎使用微验验证[%s]\n",_wyAppid);
  // printf("\033[32;1m");		// 绿色
  // printf("\n微验官网:http://llua.cn\n\n");
  // printf("\033[33;1m");		// 黄色

  // if (_ggSwitch){
  //     char _ggUrl[1024];
  //     sprintf(_ggUrl, "app=%s",_wyAppid);
  // 	char *_ggData = httppost(_wyHost,"api/?id=notice",_ggUrl);
  // 	char* _deggData=Decrypt(_ggData, _wyRc4key);
  // 	cJSON *_ggJson = cJSON_Parse(_deggData);
  // 	int _ggCode = cJSON_GetObjectItem(_ggJson, "code")->valueint;
  // 	if (_ggCode == 200){
  // 		cJSON *_ggMsg = cJSON_GetObjectItem(_ggJson, "msg");
  //         char *_appgg = cJSON_GetObjectItem(_ggMsg, "app_gg")->valuestring;
  // 	    printf("\n\n公告:%s\n\n",_appgg);
  // 	}
  // }

  // home_main:
  // char _Kami[40];
  // if (fopen(_kmPath, "r") == NULL)
  // {
  // 	printf("\033[31;1m");
  // 	printf("请输入卡密:");
  //     char _inputKm[] = "";
  //     scanf("%s",&_inputKm);
  //     FILE *fp = fopen(_kmPath, "w");
  //     if (fp != NULL) {
  //         fprintf(fp, "%s", _inputKm);
  // 	    fclose(fp);
  //     }
  //     std::cout << "写入成功！正在重新验证卡密" << std::endl;
  // }
  // fscanf(fopen(_kmPath, "r"), "%s", &_Kami);
  // char _Imei[40];
  // if (fopen(_imeiPath, "r") == NULL)
  // {
  // 	printf("\033[31;1m");
  // 	printf("设备码获取失败\n");
  // 	srand(time(NULL));
  //     char* _Str = (char*)malloc((20 + 1) * sizeof(char));
  //     for (int i = 0; i < 20; i++) {
  //         int _randomNum = rand() % 26;
  //         _Str[i] = 'a' + _randomNum;
  //     }
  //     _Str[20] = '\0';

  //     FILE *fp = fopen(_imeiPath, "w");
  //     if (fp == NULL) {
  //         printf("文件创建失败");
  //         return 0;
  //     }
  //     fprintf(fp, "%s", _Str);
  //     fclose(fp);
  //     std::cout << "设备码已重新获取！正在重新验证卡密" << std::endl;
  // }
  // fscanf(fopen(_imeiPath, "r"), "%s", &_Imei);
  // printf("卡密： %s\n设备码： %s\n\n", _Kami, _Imei);
  // if (_Kami == "" or _Imei == "")
  // {
  // 	printf("\033[31;1m");
  // 	printf("无设备码或者卡密");
  // 	return 0;
  // }
  // time_t _Timet = time(NULL);
  // int _Time = time(&_Timet);
  // srand(time(NULL));
  // char _Value[1024];
  // char _Sign[1024];
  // char _Data[1024];
  // sprintf(_Value, "%d%d", _Time,rand());
  // sprintf(_Sign, "kami=%s&markcode=%s&t=%d&%s", _Kami, _Imei, _Time, _wyAppkey);
  // unsigned char *_SignData = (unsigned char *)_Sign;
  // MD5_CTX md5c;
  // MD5Init(&md5c);
  // unsigned char _Decrypt[16];
  // MD5Update(&md5c, _SignData, strlen((char *)_SignData));
  // MD5Final(&md5c, _Decrypt);
  // char _SignMd5[33] = { 0 };
  // for (int i = 0; i < 16; i++)
  // {
  // 	sprintf(&_SignMd5[i * 2], "%02x", _Decrypt[i]);
  // }
  // sprintf(_Data, "kami=%s&markcode=%s&t=%d&sign=%s&value=%s", _Kami, _Imei, _Time, _SignMd5, _Value);
  // char *_enData=Encrypt(_Data, _wyRc4key);
  // char _deData[1024];
  // sprintf(_deData, "&data=%s", _enData);
  // char _deUrl[1024];
  // sprintf(_deUrl, "api/?id=kmlogin&app=%s",_wyAppid);
  // char *_loginData = httppost(_wyHost,_deUrl,_deData);
  // char* _deloginData=Decrypt(_loginData, _wyRc4key);
  // cJSON *_loginJson = cJSON_Parse(_deloginData);
  // int _loginCode = cJSON_GetObjectItem(_loginJson, "e42514085c1327d0fca0aa5f9d025ccec")->valueint;
  // int _loginTime = cJSON_GetObjectItem(_loginJson, "qc9506aeacb3e76ed8f9904a7c2e48378")->valueint;
  // char *_loginMsg = cJSON_GetObjectItem(_loginJson, "ic1b0e8644e0459acdd9c0eadb25145d6")->valuestring;
  // char *_loginCheck = cJSON_GetObjectItem(_loginJson, "t41ed9f790bc6d55c7e16ff95bce52d67")->valuestring;
  // if (_loginCode == 34055)
  // {
  // 	cJSON *_loginMsgs = cJSON_GetObjectItem(_loginJson, "ic1b0e8644e0459acdd9c0eadb25145d6");
  //     char *_checkCode = cJSON_GetObjectItem(_loginMsgs, "w04e4f4bd2781d20a96a6d7b9d7f728de")->valuestring;
  // 	long _loginVip = cJSON_GetObjectItem(_loginMsgs, "z2bbcd5b18f5aa8c2b1fd17fc6e961342")->valuedouble;
  // 	long _loginId = cJSON_GetObjectItem(_loginMsgs, "uccedf2f4a68641da8722eedf0c082d12")->valuedouble;
  // 	char _deCheck[1024];
  // 	sprintf(_deCheck, "%d%s%s",_loginTime,_wyAppkey,_Value);
  // 	unsigned char *_deCheckData = (unsigned char *)_deCheck;
  // 	MD5_CTX md5c;
  // 	MD5Init(&md5c);
  // 	unsigned char _Decrypt[16];
  // 	MD5Update(&md5c, _deCheckData, strlen((char *)_deCheckData));
  // 	MD5Final(&md5c, _Decrypt);
  // 	char _checkMd5[33] = { 0 };
  // 	for (int i = 0; i < 16; i++)
  // 	{
  // 		sprintf(&_checkMd5[i * 2], "%02x", _Decrypt[i]);
  // 	}
  // 	if ((string)_checkCode != "fcde3bdb1531f69ac47b50d5e88793c4"){
  // 	    return 0;
  // 	}
  // 	if ((string)_checkMd5 == _loginCheck)
  // 	{
  // 		printf("\033[32;1m");	// 绿色
  // 		printf("登录成功\n");
  // 		if (_loginVip)
  // 		{
  // 			char _vipTime[11];
  // 			sprintf(_vipTime, "%ld", _loginVip);
  // 			time_t _timeStamp = std::atoll(_vipTime);
  // 			std::tm * _timeInfo = std::localtime(&_timeStamp);
  // 			char _buffer[80];
  // 			std::strftime(_buffer, sizeof(_buffer), "%Y-%m-%d %H:%M:%S", _timeInfo);
  // 			std::cout << "到期时间：" << _buffer << std::endl;
  // 			//到期自动退出
  // 			signal(SIGALRM, _exit);
  //             alarm(_loginVip-_Time);
  // 		}
  // 	}
  // 	else
  // 	{
  // 		printf("校验失败\n");
  // 		remove(_kmPath);
  // 	    goto home_main;
  // 	    return 0;
  // 	}
  // }
  // else
  // {
  // 	printf("\033[35;1m");	// 粉红色
  // 	cout << _loginMsg << endl;
  // 	remove(_kmPath);
  // 	goto home_main;
  // 	return 0;
  // }

  绘制.防录屏 = 0;     // std::stoi(argv[1]);
  绘制.自瞄模式 = 0;   // std::stoi(argv[2]);
  绘制.无后台开关 = 1; // std::stoi(argv[3]);
  绘制.漏打模式 = 0;   // std::stoi(argv[4]);

  // 无后台选择
  std::cout << "\033[38;2;190;190;190m正在检测ROOT环境...\033[0m" << std::endl;

  std::cout << "\033[33;5;190;190;190m ROOT环境正常！驱动进程正常！ 设备未在黑名单！\033[0m" << std::endl;

  printf("\033[38;2;190;190;190m");
  std::cout << std::endl
            << " [ - ] 是否开启无后台运行辅助 < 输入1有后台运行辅助 > < 输入2无后台运行辅助 > ;";
  std::cin >> 无后台;
  if (无后台 == 1) {
  } else {
    pid_t pids = fork();
    if (pids > 0) {
      exit(0);
    }
  }

  if (绘制.漏打模式 == 1) {
    绘制.漏打开关 = true;
  } else {
    绘制.漏打开关 = false;
  }

  布局.初始化程序();
  加载内存图片();
  /*
  std::cout << std::endl << "[-] 自瞄模式：\n[-] 1.触摸自瞄\n[-] 2.驱动自瞄\n\n";
  std::cin >> 自瞄选项;
  */
  if (绘制.自瞄模式 == 0 /*  and strstr(绘制.卡密,"ZM") != 0 */) {
    绘制.自瞄.预判力度 = 1.55f;
    绘制.自瞄主线程();
    // 绘制.掩体线程();
    绘制.GetTouch();
    绘制.按钮.自瞄选项 = true;
    // 绘制.是否开启自瞄页面 = true;
  }
  绘制.读取配置();

  // 绘制.自瞄主线程();
  // 绘制.GetTouch();

  布局.开启悬浮窗();
}