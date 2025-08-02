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
#include "网络验证/微验.h"
#include <ctime>
#include <main.h>
#include <stdlib.h>
#include <exception>//泪心 github tearhacker  电报 t.me/TearGame
#include <fstream>
#include <iostream>
#include <sstream>//泪心 github tearhacker  电报 t.me/TearGame
#include <linux/input.h>//泪心 github tearhacker  电报 t.me/TearGame
#include <dirent.h>//泪心 github tearhacker  电报 t.me/TearGame
using namespace std;
int main(int argc, char **argv)
{	  
//该源码首次购买于树的人生 🌲  后续被无限开源了n次
    //微验验证();
    screen_config();
    init_screen_x = screen_x + screen_y;
    init_screen_y = screen_y + screen_x;
	if(!init_egl(init_screen_x,init_screen_y)) 
	{
     exit(0);
    }
    ImGui_init();
    new std::thread(Getxfctouch);
	new std::thread(Getxfctouch2);
	new std::thread(AimBotAuto,ImGui::GetForegroundDrawList());
    while (1)
    {     	
	 tick();  
	}
    shutdown();
    return 0;
}
