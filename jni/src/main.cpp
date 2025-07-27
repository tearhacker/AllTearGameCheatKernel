  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
   //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <iostream>
#include <fstream>

#include<iostream>
#include<ctime>

using namespace std;
    //  extern int volume();
    
   //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
    
   //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <sys/system_properties.h>
#include <main.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>


    
   //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 



 


int main(){
 
screen_config();
    ::abs_ScreenX = (::displayInfo.height > ::displayInfo.width ? ::displayInfo.height : ::displayInfo.width);
    ::abs_ScreenY = (::displayInfo.height < ::displayInfo.width ? ::displayInfo.height : ::displayInfo.width);

    ::native_window_screen_x = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    ::native_window_screen_y = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
//system("am start com.tencent.tmgp.sgame/com.tencent.tmgp.sgame.SGameActivity");
    if (init_egl(::native_window_screen_x, ::native_window_screen_y)) {
        ImGui_init();
    } else {
        printf("EGL err\n");
        exit(0);    
    }

    Touch::Init({(float)::abs_ScreenX, (float)::abs_ScreenY}, false); //要想模拟触摸最后一个参数改成 false
    Touch::setOrientation(displayInfo.orientation);	
while (1) {     
tick();


}

shutdown();

return 0;




}

	/*
#define FIBER_STACK 8192
void * stack;
//pArg记得加上定义void*表示一切空指针不然非参数定义报错


int fnProcess(void *stack)
{
    std::thread Main_down(Mainthread);
    Main_down.join();
    return 1;
}


int main(int argc, char *argv[]) {

        //  screen_config2();

      stack = malloc(FIBER_STACK);//为子进程申请系统堆栈
  void*  pArg = new std::tuple<std::string, std::string, std::string>("1234", "8888", "com.tencent.ooo");
    clone(&fnProcess, (char *)stack + FIBER_STACK, CLONE_PARENT, pArg);//创建子线程
    
    
}

        */
