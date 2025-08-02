#include "验证/Encrypt.h"
#include "验证/cJSON.h"
#include "验证/cJSON.c"
#include "验证/http.h"

using namespace std;

typedef long int ADDRESS;
typedef char PACKAGENAME;
char *ztm;
char *jhm;
char *jqm;
char *appmy = "CMqt6nSv6cvNZq6T";//APP密钥
char *rc4key = "GS2W4n72wwv2zbWD";//选择rc4-2加密
char *host = "wy.llua.cn";//官网
char *dmdl = "api/?id=kmlogon&app=45781";    // 9999改你的应用id
char *imeipath = "/storage/emulated/0/imei";
char *kmpath = "/storage/emulated/0/flkm.txt";

int 微验验证()//泪心 github tearhacker  电报 t.me/TearGame
{
char imei[50];
    char km[50];
    
    if (fopen(kmpath, "r") == NULL)//判断是否第一次输入卡密
    {
        printf("\033[34;1m");       // 绿色
        printf("\n请输入卡密(点击右下角IM即可提起键盘)：");
        scanf("%s",&km);
        int fd = open(kmpath, O_WRONLY | O_CREAT);
        write(fd, km, sizeof(km));  // 写入文本
        close(fd);
    }
    else//不是则直接读取卡密路径
    {
    printf("注意：正在自动读取手机目录的卡密进行登录\n");
    fscanf(fopen(kmpath, "r"), "%s", &km);//读取卡密
    }
   
    // 获取时间
    time_t t;
    t = time(NULL);
    int ii = time(&t);

    // 合并微验提交数据
    char value[256];
    char sign[256];
    char data[256];
    sprintf(value, "%d", ii);
    sprintf(sign, "kami=%s&markcode=%s&t=%d&%s", km, imei, ii, appmy);

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
    char weiyan[256];
    sprintf(weiyan, "%d%s%s", ii, appmy, value);

    sprintf(data, "kami=%s&markcode=%s&t=%d&sign=%s&value=%s", km, imei, ii, lkey, value);
    char* adga = Encrypt(data, rc4key);
    
    char url[128];
    sprintf(url, "&data=%s", adga);
    ztm = httppost(host, dmdl, url);
    char* abcdstr = Decrypt(ztm, rc4key);
    
    cJSON *cjson = cJSON_Parse(abcdstr);
    int code = cJSON_GetObjectItem(cjson, "code")->valueint;
    int time = cJSON_GetObjectItem(cjson, "time")->valueint;
    char *msg = cJSON_GetObjectItem(cjson, "msg")->valuestring;
    char *check = cJSON_GetObjectItem(cjson, "check")->valuestring;
    if (code == 656)
    {                           // 200是你的状态码即是code
        if (time - ii > 30)
        {
            printf("error");
            exit(0);
        }
        if (time - ii < -30)
        {
            printf("error");
            exit(0);
        }
        // md5验证签名
        char *aaaa = weiyan;
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
        // ---------------------------------------------------------
        if (check = ykey)
        {
        printf("登录成功\n"); // 这里放可执行代码
        printf("触摸自瞄和范围只能二选一\n"); // 这里放可执行代码
		printf("8.23日更新\n"); // 这里放可执行代码
		printf("内置自动局内防举报\n"); // 这里放可执行代码
		printf("前几天在出差没带安卓手机\n"); // 这里放可执行代码
		printf("低调使用，QQ被全部冻结\n"); // 这里放可执行代码
		printf("唯一微信wbwb-1201\n"); // 这里放可执行代码
		
		return 0;
     
			
		  }else{
            exit(0);
        }
    }
    else
    {
        printf("Error:%s", msg);// 这里是错误提示，正式环境可删掉    
    }
    exit(0);
}          
