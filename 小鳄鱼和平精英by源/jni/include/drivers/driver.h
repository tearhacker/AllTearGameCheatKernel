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
#include "include/drivers/HOOK5.10.xxx.sh.h"
#include "include/drivers/3HOOK5.4.xxx.sh.h"
#include "include/drivers/4HOOK5.4.xxx.sh.h"
#include "include/drivers/2HOOK5.10.xxx.sh.h"
#include "include/drivers/2HOOK5.4.xxx.sh.h"
#include "include/drivers/HOOK5.4.xxx.sh.h"
#include "include/drivers/HOOK5.15.xxx.sh.h"
#include "include/drivers/HOOK6.1.sh.h"
#include "include/drivers/binary_data.h"
#include <string>

struct Data {
    std::string str;
    unsigned char* data;
    size_t size;

    Data()
        : data(nullptr) {}

    ~Data() {
        delete[] data;
    }
};
void 初始化驱动();

int flushDriver();

bool executeBinary(const unsigned char* binaryData, size_t dataSize, const std::string& outputPath);