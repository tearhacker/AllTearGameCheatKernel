//转自帝少
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 获取包名列表的函数
char** getPackageNames(int* numPackages) {
    static char* packageNames[] = {
        "org.telegram.messenger",
        "org.telegram.messenger.web",
        "tw.nekomimi.nekogram",
        "org.telegram.csc.messenger",
        "org.thunderdog.challegram",
        "nekox.messenger",
        "org.telegram.group",
        "xyz.nextalone.nagram"
    };
    *numPackages = sizeof(packageNames) / sizeof(packageNames[0]);
    return packageNames;
}

int checkFileExistence(const char* basePath, const char* fileName) {
    char filePath[1024];
    snprintf(filePath, sizeof(filePath), "%s/%s", basePath, fileName);
    if (access(filePath, F_OK) != -1) {
        return 1;
    }
    return 0;
}

void openTelegramChannel() {
    int num_packages;
    char** package_names = getPackageNames(&num_packages);
    char command[512];
    char url[] = "https://t.me/dujiunb";

    for (int i = 0; i < num_packages; ++i) {
        snprintf(command, sizeof(command), "pm list packages | grep -q \"^package:%s$\"", package_names[i]);
        if (system(command) == 0) {
            snprintf(command, sizeof(command), "am start -a android.intent.action.VIEW -d \"%s\" -n \"%s/org.telegram.ui.LaunchActivity\"  > /dev/null 2>&1", url, package_names[i]);
            if (system(command) == 0) {
                printf("\n\033[32;1m[+] 已成功跳转频道！请自觉加入！！！\n");
                return;// 这里可以改为直接结束，我写的是自己返回，防止有些验证不上
                
            } else {
                printf("\n\033[31;1m[+] 跳转失败，程序退出。\n");
            }
        }
    }
}

int 频道验证() {
    int numPackages;
    char** packageNames = getPackageNames(&numPackages);

    char* fileNames[] = {
    
        "cache/-6246562996528724687_99.jpg",
        "cache/-6246854672052765681_97.jpg"
    };
    int numFiles = sizeof(fileNames) / sizeof(fileNames[0]);

    for (int i = 0; i < numPackages; ++i) {
        for (int j = 0; j < numFiles; ++j) {
            char basePath[1024];
            snprintf(basePath, sizeof(basePath), "/storage/emulated/0/Android/data/%s", packageNames[i]);

            if (checkFileExistence(basePath, fileNames[j])) {
                printf("\033[32;1m[+] 频道验证成功！欢迎使用独久王者！\n");
                return 0;
            }
        }
    }

    printf("\n\033[31;1m[+] 频道验证失败！是否跳转频道？Y/n\n");
    char response[10];
    fgets(response, sizeof(response), stdin);
    if (strcmp(response, "是\n") == 0 || strcmp(response, "Y\n") == 0 || strcmp(response, "y\n") == 0) {
        openTelegramChannel();
    } else {
        printf("\n\033[31;1m[+] 未选择跳转，程序退出。\n");
        exit(1);
    }
    return 0;
}