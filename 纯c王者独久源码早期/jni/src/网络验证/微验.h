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

//#include <android_verify.h>
#include "res/Encrypt.h"
#include "res/cJSON.h"
#include "res/cJSON.c"
#include "res/weiyan.h"

using namespace std;

typedef long int ADDRESS;
typedef char PACKAGENAME;
char *ztm;
char *jhm;
char *jqm;
char *appmy = "nOgAUcKO1o88s858";//APP密钥
char *rc4key = "6KYYHncxrmabhXA";//选择rc4-2加密
char *host = "wy.llua.cn";//官网
char *dmdl = "api/?id=kmlogon&app=50036";    // 9999改你的应用id

string GGmain() {
    char *host1 = "wy.llua.cn";
    char *myapp = "nOgAUcKO1o88s858";
    char *dmdl1 = "api/?id=notice&app=50036";
    char *rc4key1 = "6KYYHncxrmabhXA";
    char *ztm1 = NULL;

    char data[256];
    char url1[256];
    char value[256];
    // 获取时间
    time_t t;
    t = time(NULL);
    int ii = time(&t);

    sprintf(data, "%d%s%s", ii, myapp, value);
    char* adga1 = Encrypt(data, rc4key1);
    sprintf(url1, "&data=%s", adga1);
    ztm1 = httppost(host1, dmdl1, url1);
    char* abcdstr = Decrypt(ztm1, rc4key1);
//    printf("调试:%s", abcdstr);
    cJSON *cjson = cJSON_Parse(abcdstr);
    if(cjson == NULL){
        printf("json pack into cjson error...");
    }
    else{//打包成功调用cJSON_Print打印输出
        cJSON_Print(cjson);
    }
    int code = cJSON_GetObjectItem(cjson, "code")->valueint;

    if (code == 200)  // 200是你的状态码即是code
    {
        char strDay[1024] = {0};
        cJSON *pValue = cJSON_GetObjectItem(cjson, "msg"); // 解析value字段内容
        if (!pValue)  // 判断value字段是否json格式
            return "";
        else
        {
            cJSON *pDay = cJSON_GetObjectItem(pValue, "app_gg");  // 解析子节点pValue的day字段字符串内容
            if (!pDay)  // 判断day字段是否json格式
                return "";
            else
            {
                if (cJSON_IsString(pDay)) // 判断day字段是否string类型
                {
                    char *app_gg =  strcpy(strDay, pDay->valuestring); // 拷贝内容到字符串数组
                    return string(app_gg);
                }
            }
        }

    }
    cJSON_Delete(cjson);

    return 0;
}

int GXmain() {
    char *host1 = "wy.llua.cn";
    string app_version = "1.7";
    char *myapp = "nOgAUcKO1o88s858";
    char *dmdl1 = "api/?id=ini&app=50036";
    char *rc4key1 = "6KYYHncxrmabhXA";
    char *ztm1 = NULL;
    printf("[+] 程序版本: %s\n", app_version.c_str());
    char data[256];
    char url1[256];
    char value[256];
    // 获取时间
    time_t t;
    t = time(NULL);
    int ii = time(&t);

    sprintf(data, "%d%s%s", ii, myapp, value);
    char* adga1 = Encrypt(data, rc4key1);
    sprintf(url1, "&data=%s", adga1);
    ztm1 = httppost(host1, dmdl1, url1);
    char* abcdstr = Decrypt(ztm1, rc4key1);
//    printf("调试:%s", abcdstr);
    cJSON *cjson = cJSON_Parse(abcdstr);
    if(cjson == NULL){
        printf("json pack into cjson error...");
    }
    else{
        cJSON_Print(cjson);
    }
    int code = cJSON_GetObjectItem(cjson, "code")->valueint;

    char temp_01[128];
    char temp_02[128];
char temp_03[128];
    if (code == 200)
    {
        char *server_version;
        char *server_show;
        char *server_ur1;
        cJSON *pValue = cJSON_GetObjectItem(cjson, "msg");
        if (!pValue)
            return 0;
        else
        {
            cJSON *sgx = cJSON_GetObjectItem(pValue, "version");
            cJSON *sgx2 = cJSON_GetObjectItem(pValue, "app_update_show");
           cJSON *sgx3 = cJSON_GetObjectItem(pValue, "app_update_url");

            if (!sgx)
                return 0;
            else
            {
                if (cJSON_IsString(sgx) && cJSON_IsString(sgx2) && cJSON_IsString(sgx3))
                {
                    server_version = strcpy(temp_01, sgx->valuestring);
                    server_show = strcpy(temp_02, sgx2->valuestring);
                     server_ur1 = strcpy(temp_03, sgx3->valuestring);
                    if (app_version.compare(server_version))
                    {
                        printf("[+] 请更新插件 最新版本:%s\n[+] 更新内容: %s\n[+] 更新地址: %s\n", server_version, server_show, server_ur1);
                        exit(0);
                    }
                }
            }
        }

    }
    cJSON_Delete(cjson);

    return 0;
}
int 微验验证()
{

//    char *host = "wy.llua.cn";
    // 填入 卡密登录接口

    char *APPID = "50036";
    // 填入 APPID
    
    const static char *APPKEY = "nOgAUcKO1o88s858";
    // 填入 APPKEY

    const static char *RC4KEY = "6KYYHncxrmabhXA";
    // 用户管理后台-RC4密钥

    const static char *km_luj = "/sdcard/独久/王者小狐狸卡密.c";
    // 卡密路径

    const static char *imei_luj = "/sdcard/独久/王者小狐狸设备码.c";
    // 机器码路径


    printf("[+] 欢迎使用小狐狸王者内核\n");
    
    
    home_main:
    char km[40];                // 卡密
    if (fopen(km_luj, "r") == NULL)
    {
        
        printf("[+] 请输入卡密:");
        char str[] = "";
        scanf("%s",&str);
    
        FILE *fp = fopen(km_luj, "w");
        if (fp != NULL) {
            fprintf(fp, "%s", str);
            fclose(fp);
        }
        std::cout << "[+] 写入成功！正在重新验证卡密" << std::endl;
    }
    fscanf(fopen(km_luj, "r"), "%s", &km);


    char imei[40];              // 设备码
    if (fopen(imei_luj, "r") == NULL)
    {

        printf("\033[31;1m");
        printf("[+] 设备码获取失败\n");
        srand(time(NULL)); // 设置随机数种子为当前时间
        char* str = (char*)malloc((20 + 1) * sizeof(char));
        int i;
        for (i = 0; i < 20; i++) {
            int randomNum = rand() % 26; // 生成0到25之间的随机数
            str[i] = 'a' + randomNum; // 将随机数转换为对应的小写字母
        }
        str[20] = '\0'; // 字符串末尾添加结束符
    
        FILE *fp = fopen(imei_luj, "w");
        if (fp == NULL) {
            printf("[-] 文件创建失败");
            return 1;
        }
        fprintf(fp, "%s", str);
    
        fclose(fp);
    
        std::cout << "[-] 设备码已重新获取！正在重新验证卡密" << std::endl;
 
        
    }
    fscanf(fopen(imei_luj, "r"), "%s", &imei);


    printf("[-] 卡密:%s\n[-] 设备码:%s\n", km, imei);
    // ---------------------------------------------------------

    if (km == "" or imei == "")
    {
        printf("\033[31;1m");
        printf("[-] 无设备码或者卡密");
        exit(1);
    }

    // 时间戳
    time_t t;
    t = time(NULL);
    int ii = time(&t);
    srand(time(NULL));
    // 合并数据
    char value[256];
    char sign[256];
    char data[256];
    sprintf(value, "%d%d", ii,rand());
    sprintf(sign, "kami=%s&markcode=%s&t=%d&%s", km, imei, ii, APPKEY);


    // ---------------------------------------------------------
    // md5验证签名
    char *aaa = sign;
    unsigned char *bbb = (unsigned char *)aaa;
    MD5_CTX md5c;
    MD5Init(&md5c);
    int i;
    unsigned char decrypt[16];
    MD5Update(&md5c, bbb, strlen((char *)bbb));
    MD5Final(&md5c, decrypt);
    char lkey[32] = { 0 };
    for (i = 0; i < 16; i++)
    {
        sprintf(&lkey[i * 2], "%02x", decrypt[i]);
    }
    // md5验证签名
    // ---------------------------------------------------------

    // RC4加密
    sprintf(data, "kami=%s&markcode=%s&t=%d&sign=%s&value=%s", km, imei, ii, lkey, value);
    char *dataa=Encrypt(data, RC4KEY);

    // 合并数据
    char cs[256];
    sprintf(cs, "&data=%s", dataa);
    
    char url[256];
    sprintf(url, "api/?id=kmlogon&app=%s",APPID);
    
    // 提交数据
    char *tijiao = httppost(host,url,cs);

    // RC4解密
    char* tijiaoo=Decrypt(tijiao, RC4KEY);
    
    //解析JSON
    cJSON *cjson = cJSON_Parse(tijiaoo);
    
    // 读取状态码
    int code = cJSON_GetObjectItem(cjson, "code")->valueint;

    // 服务器时间
    int time = cJSON_GetObjectItem(cjson, "time")->valueint;

    // 错误信息
    char *msg = cJSON_GetObjectItem(cjson, "msg")->valuestring;
    
    // 登录校验
    char *check = cJSON_GetObjectItem(cjson, "check")->valuestring;

    // 验证登录
    if (code == 200) //code判断
    {
        cJSON *msgdata = cJSON_GetObjectItem(cjson, "msg");

        // 到期时间戳
        long vip = cJSON_GetObjectItem(msgdata, "vip")->valuedouble;

        char weijy[256];
        sprintf(weijy, "%d%s%s", time, APPKEY, value);

        // ---------------------------------------------------------
        // md5验证签名
        char *aaaa = weijy;
        unsigned char *bbbb = (unsigned char *)aaaa;
        MD5_CTX md5c;
        MD5Init(&md5c);
        int i;
        unsigned char decrypt[16];
        MD5Update(&md5c, bbbb, strlen((char *)bbbb));
        MD5Final(&md5c, decrypt);
        char ykey[32] = { 0 };
        for (i = 0; i < 16; i++)
        {
            sprintf(&ykey[i * 2], "%02x", decrypt[i]);
        }
        // md5验证签名
        // ---------------------------------------------------------
        if (string(ykey) == check)
        {
            
            printf("[+] 登录成功\n");
            
            if (vip)
            {
                char vipmsg[11];
                sprintf(vipmsg, "%ld", vip);
                time_t timestamp = std::atoll(vipmsg);  // 将字符串类型的时间戳转换为time_t类型
                std::tm * timeinfo = std::localtime(&timestamp);    // 将时间戳转换为本地时间
                char buffer[80];
                std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);   // 格式化时间
       std::string filePath = "/sdcard/独久/王者小狐狸卡密时间.c";

       // 创建并打开文件准备写入
    std::ofstream file(filePath, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "无法创建或打开文件" << std::endl;
        return 1;
    }

    // 写入格式化的时间到文件
    file << buffer << std::endl;

    // 关闭文件
    file.close();


                std::cout << "[-] 到期时间：" << buffer << std::endl;
            }
        }
        else
        {
            printf("[-] 校验失败\n");
            remove(km_luj);
            goto home_main;
        }
    }
    else
    {
        
        cout << msg << endl;
        remove(km_luj);
        goto home_main;
    }
    return 0;
}
