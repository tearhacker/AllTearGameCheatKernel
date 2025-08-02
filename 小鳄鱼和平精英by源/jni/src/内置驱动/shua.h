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
#include "dev4.9.186ko.h"
#include "dev4.14.117.ko.h"
#include "dev4.14.141ko.h"
#include "dev4.14.180ko.h"
#include "dev4.14.186bko.h"
#include "dev4.14.186cko.h"
#include "dev4.14.186dko.h"
#include "dev4.14.186ko.h"
#include "dev4.14.190ko.h"
#include "dev4.19.81ko.h"
#include "dev4.19.113ko.h"
#include "dev4.19.157bko.h"
#include "dev4.19.157cko.h"
#include "dev4.19.157ko.h"
#include "dev4.19.191bko.h"
#include "dev4.19.191cko.h"
#include "dev4.19.191ko.h"
#include "dev5.4.ko.h"
#include "dev5.4b.ko.h"
#include "dev5.4c.ko.h"
#include "dev5.4d.ko.h"
#include "dev5.10ko.h"
#include "dev5.15.ko.h"
#include "dev6.1.ko.h"
#include "dev6.6.ko.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void get_kernel_version() {
    FILE *fp;
    char buffer[1024];
    char command[] = "uname -r | tr -d '\n'";

    // 打开管道执行命令
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        return;
    }

    // 读取命令输出
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // 去除可能存在的换行符
        buffer[strcspn(buffer, "\n")] = 0;

        printf("内核版本：%s", buffer);
        printf("\n");
    }

    // 关闭管道
    pclose(fp);
}
    
// 函数用于获取安卓版本
void get_android_version() {
    FILE *file;
    char line[256];
    const char *target = "ro.build.version.release=";

    // 打开 /system/build.prop 文件
    file = fopen("/system/build.prop", "r");
    if (file == NULL) {
        perror("无法打开 /system/build.prop 文件");
        return;
    }

    // 逐行读取文件
    while (fgets(line, sizeof(line), file) != NULL) {
        // 检查当前行是否包含目标字符串
        if (strstr(line, target) != NULL) {
            // 找到目标行，提取版本号
            char *version = strchr(line, '=') + 1;
            // 去除换行符
            version[strcspn(version, "\n")] = 0;

            printf("安卓版本：%s\n", version);
            break;
        }
    }

    // 关闭文件
    fclose(file);
}


void write_to_file(const char* filename, const unsigned char* data, unsigned int length) {
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        perror("[-] 无法创建临时文件");
        exit(1);
    }
    fwrite(data, 1, length, fp);
    fclose(fp);
}

void insmodKernel(const char* path) {
    char command[256];
    snprintf(command, sizeof(command), "insmod %s 2>/dev/null", path);
    int ret = system(command);
    if (ret == 0) {
        printf("驱动已刷入\n");
    } else {
        printf("驱动刷入失败\n");
    }
}

void load_module(const unsigned char* data, unsigned int length, const char* name) {
    const char* temp_file = "/data/HACK.ko";

    write_to_file(temp_file, data, length);

    printf("[+] 正在加载驱动: %s\n", name);
    insmodKernel(temp_file);

 
    unlink(temp_file);
}


// 函数声明
void load_4_series();
void load_5_series();
void load_6_series();

void load_4_series() {
    int choice;
    while (1) {
        get_android_version();
        get_kernel_version();
        printf("\n4系内核驱动选择:\n");
        printf("[1] 4.9.186\n");
        printf("[2] 4.14.117\n");
        printf("[3] 4.14.141\n");
        printf("[4] 4.14.180\n");
        printf("[5] 4.14.186\n");
        printf("[6] 4.14.186b\n");
        printf("[7] 4.14.186c\n");
        printf("[8] 4.14.186d\n");
        printf("[9] 4.14.190\n");
        printf("[10] 4.19.81\n");
        printf("[11] 4.19.113\n");
        printf("[12] 4.19.157\n");
        printf("[13] 4.19.157b\n");
        printf("[14] 4.19.157c\n");
        printf("[15] 4.19.191\n");
        printf("[16] 4.19.191b\n");
        printf("[17] 4.19.191c\n");
        printf("[18] 返回主菜单\n");
        printf("[-] 请选择版本: ");
        scanf("%d", &choice);

        switch (choice) {
case 1:
load_module(dev4_9_186_ko, dev4_9_186_ko_len, "4.9.186");
sleep(1);
break;
case 2:
load_module(dev4_14_117_ko, dev4_14_117_ko_len, "4.14.117");
sleep(1);
break;
case 3:
load_module(dev4_14_141_ko, dev4_14_141_ko_len, "4.14.141");
sleep(1);
break;
case 4:
load_module(dev4_14_180_ko, dev4_14_180_ko_len, "4.14.180");
sleep(1);
break;
case 5:
load_module(dev4_14_186_ko, dev4_14_186_ko_len, "4.14.186");
sleep(1);
break;
case 6:
load_module(dev4_14_186b_ko, dev4_14_186b_ko_len, "4.14.186b");
sleep(1);
break;
case 7:
load_module(dev4_14_186c_ko, dev4_14_186c_ko_len, "4.14.186c");
sleep(1);
break;
case 8:
load_module(dev4_14_186d_ko, dev4_14_186d_ko_len, "4.14.186d");
sleep(1);
break;
case 9:
load_module(dev4_14_190_ko, dev4_14_190_ko_len, "4.14.190");
sleep(1);
break;
case 10:
load_module(dev4_19_81_ko, dev4_19_81_ko_len, "4.19.81");
sleep(1);
break;
case 11:
load_module(dev4_19_113_ko, dev4_19_113_ko_len, "4.19.113");
sleep(1);
break;
case 12:
load_module(dev4_19_157_ko, dev4_19_157_ko_len, "4.19.157");
sleep(1);
break;
case 13:
load_module(dev4_19_157b_ko, dev4_19_157b_ko_len, "4.19.157b");
sleep(1);
break;
case 14:
load_module(dev4_19_157c_ko, dev4_19_157c_ko_len, "4.19.157c");
sleep(1);
break;
case 15:
load_module(dev4_19_191_ko, dev4_19_191_ko_len, "4.19.191");
sleep(1);
break;
case 16:
load_module(dev4_19_191b_ko, dev4_19_191b_ko_len, "4.19.191b");
sleep(1);
break;
case 17:
load_module(dev4_19_191c_ko, dev4_19_191c_ko_len, "4.19.191c");
sleep(1);
break;
 
            case 18:
                return;
            default:
                printf("[-] 输入错误，请重新选择\n");
        }
    }
}

void load_5_series() {
    int choice;
    while (1) {
        get_android_version();
        get_kernel_version();
        printf("\n5系内核驱动选项:\n");
        printf("[1] 5.4\n");
        printf("[2] 5.4b\n");
        printf("[3] 5.4c\n");
        printf("[4] 5.4d\n");
        printf("[5] 5.10\n");
        printf("[6] 5.15\n");
        printf("[7] 返回主菜单\n");
        printf("[-] 请选择版本: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
    load_module(dev5_4_ko, dev5_4_ko_len, "5.4");
    sleep(1);
    break;
    case 2:
    load_module(dev5_4b_ko, dev5_4b_ko_len, "5.4b");
    sleep(1);
    break;
    case 3:
    load_module(dev5_4c_ko, dev5_4c_ko_len, "5.4c");
    sleep(1);
    break;
    case 4:
    load_module(dev5_4d_ko, dev5_4d_ko_len, "5.4d");
    sleep(1);
    break;
    case 5:
    load_module(dev5_10ko, dev5_10ko_len, "5.10"); // 修正dev5_10ko为dev5_10_ko
    sleep(1);
    break;
    case 6:
    load_module(dev5_15_ko, dev5_15_ko_len, "5.15");
    sleep(1);
    break;
            case 7:
                return;
            default:
                printf("[-] 输入错误，请重新选择\n");
        }
    }
}

void load_6_series() {
    int choice;
    while (1) {
        get_android_version();
        get_kernel_version();
        printf("\n6系内核驱动选项:\n");
        printf("[1] 6.1\n");
        printf("[2] 6.6\n");
        printf("[3] 返回主菜单\n");
        printf("[-] 请选择版本: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            load_module(dev6_1_ko, dev6_1_ko_len, "6.1");
            sleep(1);
            break;
            case 2:
            load_module(dev6_6_ko, dev6_6_ko_len, "6.6");
            sleep(1);
            break;
            case 3:
                return;
            default:
                printf("[-] 输入错误，请重新选择\n");
        }
    }
}

void shuaru() {
    int choice;

    // 初始版本信息展示
    get_android_version();
    get_kernel_version();

    while (1) {
        printf("[1] 4系驱动\n");
        printf("[2] 5系驱动\n");
        printf("[3] 6系驱动\n");
        printf("[4] 已经刷入 直接进入\n");
        printf("[-] 请选择主菜单选项: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                load_4_series();
                break;
            case 2:
                load_5_series();
                break;
            case 3:
                load_6_series();
                break;
            case 4:
                return;  // 新增：退出函数结束循环
            default:
                printf("[-] 输入错误，请重新选择\n");
                break;
        }
    }

    // 这里可以添加后续操作（例如执行提权等）
    // system("/data/shell_script.sh");
}
