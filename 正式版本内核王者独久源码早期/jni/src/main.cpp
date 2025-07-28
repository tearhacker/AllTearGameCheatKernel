#include "网络验证/微验.h"
#include "网络验证/v检测.h"
#include "网络验证/函数.h"
#include "网络验证/频道验证.h"
#include "draw.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>

#include<fstream>
#include<iostream>
#include <iostream>
#include<thread>
static char sstr[512];



/*

https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
*/


int Option;
int main(int argc, char *argv[]) {

 /*   int total = 102; // 总进度
    int progress = 0; // 当前进度
    while (progress <= total) {
        // 清除上一次的进度条
        printf("\r"); // \r是回车符，将光标移回行首
        for (int i = 0; i < progress; ++i) {
            printf("\b"); // 退格符，将光标向左移动一个位置
        }
        // 打印空格以覆盖之前的进度条
        for (int i = 0; i < total; ++i) {
            
        }
        // 打印新的进度条
        printf("TG@dujiunb%-100s\033[1;32m独久来了\033[0m← %d%%", "", progress * 100 / total);
        fflush(stdout); // 刷新输出缓冲区，确保进度条立即显示
        // 模拟耗时操作
        usleep(40000); // 暂停0.05秒
        progress++; // 增加进度
    }*/
   // printf("\n"); // 完成后换行
        printf("\033[1;31m------------------------------------------------\n");
    system("echo -e '\033[93m[+] 安卓版本:\033[0m' $(getprop ro.build.version.release)");
    system("echo -e '\033[93m[+] 设备机型:\033[0m' $(getprop ro.product.marketname)"); 
    std::cout <<"\033[1;34m[!] 欢迎你使用独久公益王者内核\n";
    std::cout <<"\033[1;36m[!] 已更新王者最新数据\n";
    std::cout <<"\033[1;36m[!] 本版本是内核版本 版本号: 2.0\n";
    std::cout <<"\033[1;36m[!] 官方频道https://t.me/dujiunb\n";
    云更新();
    频道验证();
    std::cout << "[+] 是否开启内核无后台模式:[1]是 [2]否: ";
    cin >> Option;
    if (Option == 2) {
    }else {
      pid_t pids = fork();
      if (pids > 0) {
      std::cout << "[+] 以为你启动无后台模式，请稍等几秒";
        exit(0);
      }
    }
    screen_config();
    ::abs_ScreenX = (::displayInfo.height > ::displayInfo.width ? ::displayInfo.height : ::displayInfo.width);
    ::abs_ScreenY = (::displayInfo.height < ::displayInfo.width ? ::displayInfo.height : ::displayInfo.width);

    ::native_window_screen_x = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    ::native_window_screen_y = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
//system("am start com.tencent.tmgp.sgame/com.tencent.tmgp.sgame.SGameActivity");
  //  createSocket() ;
    usleep(500);
	new std::thread(音量);
	createSocket();
    if (init_egl(::native_window_screen_x, ::native_window_screen_y)) {
        ImGui_init();
    } else {
        printf("EGL err\n");
        exit(0);    
    }
   
    Touch::Init({(float)::abs_ScreenX, (float)::abs_ScreenY}, true); //要想模拟触摸最后一个参数改成 false
    Touch::setOrientation(displayInfo.orientation);//
//system("am start com.tencent.tmgp.sgame/com.tencent.tmgp.sgame.SGameActivity");
    while (true) {     
        drawBegin();
        
   	    tick();  
   	    
   	    drawEnd();
    }
   
    shutdown();
    
    return 0;
    
}









