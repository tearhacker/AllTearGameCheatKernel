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
#include <asm/ptrace.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <dirent.h>
#include <elf.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <asm/unistd.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <sys/system_properties.h>
#include <vector>
#include "Logger.h"

enum deviceArchitecture {
    armeabi_v7a,
    arm64_v8a,
    x86,
    x86_64,
    Unknown,
};

//System libs
const char *libcPath = "";
const char *linkerPath = "";
const char *libDLPath = "";
deviceArchitecture arch;
int sdkVersion = 0;

void setupSystemLibs() {
    char _sdkVersion[32];
    char sysArchitecture[32];
    __system_property_get("ro.build.version.sdk", _sdkVersion);
    __system_property_get("ro.product.cpu.abi", sysArchitecture);
    sdkVersion = atoi(_sdkVersion);

    if (strcmp(sysArchitecture, "x86_64") == 0) {
        arch = deviceArchitecture::x86_64;
        libcPath = "/system/lib64/libc.so";
        linkerPath = "/system/bin/linker64";
        libDLPath = "/system/lib64/libdl.so";
    } else if (strcmp(sysArchitecture, "x86") == 0) {
        arch = deviceArchitecture::x86;
        libcPath = "/system/lib/libc.so";
        linkerPath = "/system/bin/linker";
        libDLPath = "/system/lib/arm/nb/libdl.so";
    } else if (strcmp(sysArchitecture, "arm64-v8a") == 0) {
        arch = deviceArchitecture::arm64_v8a;
        if (sdkVersion >= 29) { //Android 10
            libcPath = "/apex/com.android.runtime/lib64/bionic/libc.so";
            linkerPath = "/apex/com.android.runtime/bin/linker64";
            libDLPath = "/apex/com.android.runtime/lib64/bionic/libdl.so";
        } else {
            libcPath = "/system/lib64/libc.so";
            linkerPath = "/system/bin/linker64";
            libDLPath = "/system/lib64/libdl.so";
        }
    } else if (strcmp(sysArchitecture, "armeabi-v7a") == 0) {
        arch = deviceArchitecture::armeabi_v7a;
    } else {
        arch = deviceArchitecture::Unknown;
        LOGE("Device not supported");
    }
}

int isSELinuxEnabled() {
    bool result = 0;
    FILE* fp = fopen("/proc/filesystems", "r");
    char line[100];
    while(fgets(line, 100, fp)) {
        if (strstr(line, "selinuxfs")) {
            result = 1;
        }
    }
    fclose(fp);
    return result;
}

void disableSELinux() {
    char line[1024];
    FILE* fp = fopen("/proc/mounts", "r");
    while(fgets(line, 1024, fp)) {
        if (strstr(line, "selinuxfs")) {
            strtok(line, " ");
            char* selinux_dir = strtok(NULL, " ");
            char* selinux_path = strcat(selinux_dir, "/enforce");

            FILE* fp_selinux = fopen(selinux_path, "w");
            char buf[2] = "0"; //0 = Permissive
            fwrite(buf, strlen(buf), 1, fp_selinux);
            fclose(fp_selinux);
            break;
        }
    }
    fclose(fp);
}



void launchApp(char *appLaunchActivity) {
    //Test on termux:
    //am start packagename/launchActivity
    char start_cmd[1024] = "am start ";

    strcat(start_cmd, appLaunchActivity);
    LOGI("%s", start_cmd);

    system(start_cmd);
}

//Search the base address of the module in the process
void *getModuleBaseAddr1(pid_t pid, const char *moduleName) {
    long moduleBaseAddr = 0;
    char mapsPath[50] = {0};
    char szMapFileLine[1024] = {0};

    snprintf(mapsPath, sizeof(mapsPath), "/proc/%d/maps", pid);
    FILE *fp = fopen(mapsPath, "r");

    if (fp != nullptr) {
        while (fgets(szMapFileLine, sizeof(szMapFileLine), fp)) {
            if (strstr(szMapFileLine, moduleName)) {
                char *address = strtok(szMapFileLine, "-");
                moduleBaseAddr = strtoul(address, nullptr, 16);

                if (moduleBaseAddr == 0x8000) {
                    moduleBaseAddr = 0;
                }

                break;
            }
        }
        fclose(fp);
    }

    return (void *)moduleBaseAddr;
}

//Get the address of the function in the module loaded by the remote process and this process
void *getRemoteFuncAddr(pid_t pid, const char *moduleName, void *localFuncAddr) {
    void *localModuleAddr = getModuleBaseAddr1(getpid(), moduleName); //Starting address of the module in my process
    void *remoteModuleAddr = getModuleBaseAddr1(pid, moduleName); //Starting address of module loaded in other process
    void *remoteFuncAddr = (void *)((uintptr_t)localFuncAddr - (uintptr_t)localModuleAddr + (uintptr_t)remoteModuleAddr); //Address of the function in the other process

    //printf("getRemoteFunctionAddr path: %s, localModuleAddr: 0x%lX, remoteModuleAddr: 0x%lX, localModuleAddr: 0x%lX, remoteFuncAddr: 0x%lX", moduleName, localModuleAddr, remoteModuleAddr, localModuleAddr, remoteFuncAddr);
    return remoteFuncAddr;
}
