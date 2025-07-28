#include "draw.h"

#include "微验.h"

bool VPN检测()
{
    char command[256] = "";
    memset(command, 0, 256);
    if ((access("/system/bin/ifconfig", 0)) != -1){
        sprintf(command, "%s", "/system/bin/ifconfig");
    }else{
        return true;
    }
    FILE* fp = NULL;
    char line[1024] = "";
    fp = popen(command, "r");
    while (fgets(line, 1024, fp) != NULL)
    {
        if (strstr(line, "tun0") != NULL || strstr(line, "ppppp0") != NULL){
            pclose(fp);
            return true;
        }
    }
    pclose(fp);
    return false;
}
/*
int HttpCanary = getPID("com.guoshi.httpcanary");
int 小黄鸭过检测 = getPID("cn.iyya.vvv");

void 检测()
{

if(HttpCanary != -1)  
{
system("am force-stop com.guoshi.httpcanary");    
}

if(小黄鸭过检测 != -1)
{
system("am force-stop cn.iyya.vvv");
}

}
*/





/*bool fileExistsAndNotEmpty(const std::string& file) {
    // 实现 fileExistsAndNotEmpty 函数逻辑
    // ...
    return true;
}

bool isProcessRunning(const std::string& process) {
    // 实现 isProcessRunning 函数逻辑
    // ...
    return true;
}
*/




#include <fstream>
#include <unistd.h>
#include <iostream>
#include <vector>

const std::string FILE_PREFIX = "/data/media/0/Android/data/";

bool fileExistsAndNotEmpty(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good() && !file.eof();
}

bool isProcessRunning(const std::string& processName) {
    std::string command = "pgrep " + processName;
    return system(command.c_str()) == 0;
}

int checkTG() {
    std::cout << "\n开始电报验证\n";
    sleep(1); // 使用 sleep 函数使程序暂停一秒钟

    std::vector<std::string> filePaths = {
        "org.telegram.messenger.web/cache/--6125326115691149973_99.jpg",
        "org.telegram.messenger.web/cache/-6125326115691149973_99.jpg",
        "tw.nekomimi.nekogram/cache/-6125326115691149973_99.jpg",
        "tw.nekomimi.nekogram/cache/-6125326115691149973_99.jpg",
        "org.telegram.csc.messenger/cache/-6125326115691149973_99.jpg",
        "org.telegram.csc.messenger/cache/-6125326115691149973_99.jpg",
        "org.thunderdog.challegram/cache/-6125326115691149973_99.jpg",
        "org.thunderdog.challegram/cache/-6125326115691149973_99.jpg",
        "nekox.messenger/cache/-6125326115691149973_99.jpg",
        "nekox.messenger/cache/-6125326115691149973_99.jpg",
        "xyz.nextalone.nagram/cache/-6125326115691149973_99.jpg",
        "xyz.nextalone.nagram/cache/-6125326115691149973_99.jpg"
    };

    int count = 0;
    for (const auto& file : filePaths) {
        std::string filePath = FILE_PREFIX + file;
        if (fileExistsAndNotEmpty(filePath)) {
            count++;
        } else {
            std::cout << "电报验证失败\n请加入TG群聊：https://t.me/PDXGY\n请加去频道点击头像刷新 " << filePath << std::endl;
            exit(1);  // 文件大小为0或不存在则退出程序
        }
    }

    if (count >= 2) {
        if (isProcessRunning("nekox.messenger")) {
            std::cout << "电报验证成功\n";
            return 1;
        } else {
            std::cout << "电报验证成功\n";
            return 0;
        }
    } else {
        std::cout << "电报验证失败\n请加入TG群聊：https://t.me/PDXGY\n";
        exit(0);  // 直接退出程序
    }
}