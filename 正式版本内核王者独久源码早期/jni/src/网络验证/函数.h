#include <iostream>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl/curl.h"


#define MAX_LENGTH 1024

// 用于从源字符串中提取子字符串
char *getSubstring(const char *const src, const char *const startTag, const char *const endTag) {
    const char *start = strstr(src, startTag);
    if (start == nullptr) {
        return nullptr;
    }
    start += strlen(startTag);

    const char *end = strstr(start, endTag);
    if (end == nullptr) {
        return nullptr;
    }

    size_t length = end - start;
    if (length == 0) {
        return nullptr;
    }

    char *result = (char *)malloc(sizeof(char) * (length + 1));
    if (result == nullptr) {
        return nullptr;
    }
    strncpy(result, start, length);
    result[length] = '\0';

    return result;
}

// 获取云端链接
char *获取云端链接() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/186fc92654f06eebc46cd35ee430d821");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return nullptr;
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *链接文本 = strstr(buf, "[链接]");
        if (链接文本 != nullptr) {
            pclose(fp);
            return getSubstring(链接文本, "[链接]", "[链接]");
        }
    }

    pclose(fp);
    return nullptr;
}

// 获取云端版本号
int 获取云端版本号() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/186fc92654f06eebc46cd35ee430d821");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return 0; // or any suitable default value
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *version = strstr(buf, "[版本号]");
        if (version != nullptr) {
            pclose(fp);
            version = getSubstring(version, "[版本号]", "[版本号]");
            int convertedVersion = atoi(version);
            free(version);
            return convertedVersion;
        }
    }

    pclose(fp);
    return 0; // or any suitable default value
}

// 获取云端公告
char *获取云端公告() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/186fc92654f06eebc46cd35ee430d821");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return nullptr;
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *公告文本 = strstr(buf, "[公告]");
        if (公告文本 != nullptr) {
            pclose(fp);
            return getSubstring(公告文本, "[公告]", "[公告]");
        }
    }

    pclose(fp);
    return nullptr;
}

// 获取云端文件名
char *获取云端文件名() {
    char url[128];
    sprintf(url, "curl -s %s", "https://sharechain.qq.com/186fc92654f06eebc46cd35ee430d821");
    FILE *fp = popen(url, "r");
    if (fp == nullptr) {
        return nullptr;
    }
    char buf[MAX_LENGTH];

    while (fgets(buf, MAX_LENGTH, fp) != nullptr) {
        char bti[256];
        sscanf(buf, " <title>%[^<]</title>", bti);
        char *文件名 = strstr(buf, "[文件名]");
        if (文件名 != nullptr) {
            pclose(fp);
            return getSubstring(文件名, "[文件名]", "[文件名]");
        }
    }

    pclose(fp);
    return nullptr;
}

// 云更新
void 云更新() {
    puts("[+] 正在验证版本号...");
    int 当前版本 = 10; // 为了演示目的，这里将当前版本设为2
    int 云端版本 = 获取云端版本号();
    char *更新公告 = 获取云端公告();
    if (云端版本 <= 当前版本) {
        printf("[+] 公告:%s\n", 更新公告);
        puts("[+] 版本已为最新");
    } else {
        printf("[+] 程序版本过低，开始云更新\n");
        char *下载链接 = 获取云端链接();
        char *更新文件名 = 获取云端文件名();
        
        printf("[+] 更新文件名:%s\n", 更新文件名);
        system("rm -rf 独久王者.sh");
        char cmd[MAX_LENGTH];
        snprintf(cmd, sizeof(cmd), "curl -L %s -o %s", 下载链接, 更新文件名);
        int ret = system(cmd);
        if (ret == 0) {
            printf("[+] 辅助更新完毕，请重启动更新好的文件！！\n");
             system("chmod 777 独久王者.sh");
            system("./独久王者.sh");
            exit(0);
        } else {
            printf("[-] 更新失败请前往\nTG:https://t.me/dujiunb h\n手动更新");
            exit(0);
        }
        free(下载链接);//释放内存
        free(更新公告);
        free(更新文件名);
        exit(0);
    }
}
