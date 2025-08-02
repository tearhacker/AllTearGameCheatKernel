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
#include "drivers/driver.h"

#include <dirent.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
// #include <vectoor>

Data dataMap[17];

bool executeBinary(const unsigned char* binaryData, size_t dataSize, const std::string& outputPath) {
    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile) {
        return false;
    }
    outputFile.write(reinterpret_cast<const char*>(binaryData), dataSize);
    outputFile.close();

    if (chmod(outputPath.c_str(), 0777) != 0) {
        return false;
    }
    int result = system(outputPath.c_str());
    if (result != 0) {
        return false;
    }
    if (std::remove(outputPath.c_str()) != 0) {
        return false;
    }
    return true;
}

void 初始化驱动() {
    dataMap[7].str = "HOOK6.1无痕";
    size_t kernel_6_1_size = sizeof(kernel_6_1);
    dataMap[7].size = kernel_6_1_size;
    dataMap[7].data = new unsigned char[kernel_6_1_size];
    memcpy(dataMap[7].data, kernel_6_1, kernel_6_1_size);

    dataMap[2].str = "HOOK5.15无痕";
    size_t kernel_5_15_size = sizeof(kernel_5_15);
    dataMap[2].size = kernel_5_15_size;
    dataMap[2].data = new unsigned char[kernel_5_15_size];
    memcpy(dataMap[2].data, kernel_5_15, kernel_5_15_size);


    dataMap[6].str = "HOOK5.4无痕";
    size_t C_kernel_5_4_size = sizeof(C_kernel_5_4);
    dataMap[6].size = C_kernel_5_4_size;
    dataMap[6].data = new unsigned char[C_kernel_5_4_size];
    memcpy(dataMap[6].data, C_kernel_5_4, C_kernel_5_4_size);

    dataMap[5].str = "HOOK5.4无痕2";
    size_t color_kernel_5_4_size = sizeof(color_kernel_5_4);
    dataMap[5].size = color_kernel_5_4_size;
    dataMap[5].data = new unsigned char[color_kernel_5_4_size];
    memcpy(dataMap[5].data, color_kernel_5_4, color_kernel_5_4_size);

    dataMap[4].str = "HOOK5.10无痕";
    size_t B_kernel_5_10_size = sizeof(B_kernel_5_10);
    dataMap[4].size = B_kernel_5_10_size;
    dataMap[4].data = new unsigned char[B_kernel_5_10_size];
    memcpy(dataMap[4].data, B_kernel_5_10, B_kernel_5_10_size);

    dataMap[3].str = "HOOK5.4无痕3";
    size_t B_kernel_5_4_size = sizeof(B_kernel_5_4);
    dataMap[3].size = B_kernel_5_4_size;
    dataMap[3].data = new unsigned char[B_kernel_5_4_size];
    memcpy(dataMap[3].data, B_kernel_5_4, B_kernel_5_4_size);


    dataMap[1].str = "HOOK5.10无痕2";
    size_t A_kernel_5_10_size = sizeof(A_kernel_5_10);
    dataMap[1].size = A_kernel_5_10_size;
    dataMap[1].data = new unsigned char[A_kernel_5_10_size];
    memcpy(dataMap[1].data, A_kernel_5_10, A_kernel_5_10_size);

    dataMap[0].str = "HOOK5.4无痕4";
    size_t A_kernel_5_4_size = sizeof(A_kernel_5_4);
    dataMap[0].size = A_kernel_5_4_size;
    dataMap[0].data = new unsigned char[A_kernel_5_4_size];
    memcpy(dataMap[0].data, A_kernel_5_4, A_kernel_5_4_size);

}

int flushDriver() {
    初始化驱动();
    // printf("\033[1m\033[36m\033[4m驱动刷写 Kernel 1.0\n");
    printf("\033[31m检测本机内核版本:: \033[0m");
    char buffer[256];
    FILE* fp = popen("uname -r", "r");
    fgets(buffer, sizeof(buffer), fp);
    buffer[strcspn(buffer, "\n")] = 0;
    printf("%s\n", buffer);
    pclose(fp);

    std::string Namecontent = "";
    int choose, number = 0;

    for (int i = 0; i < 25; i++) {
        Namecontent += std::to_string(i) + ". " + dataMap[i].str;
        Namecontent += "\n";
        /* if (number == 1) {
          Namecontent+= "\n\n";
          number = 0;
          continue;
        }
        Namecontent+= " 或 ";
        number++; */
    }
    printf("\033[32m%s\033[0m", Namecontent.c_str());
 
std::cout << "\033[38;2;190;190;190m刷入HOOK之前请手动重启设备一次\033[0m" << std::endl;
    std::cout << "BYYXnb提示:请输入对应的HOOK数字：" << std::endl;

    std::cin >> choose;
    if (choose < 0 || choose > 25) {
        printf("请勿乱输\n");
        exit(0);
    }

    /*
    std::ifstream inputFile("/data/user/0/com.Pikachu.Tencent/files/Qudo.txt");
    std::string line;
    std::getline(inputFile, line);
    int choose = std::stoi(line);
    //printf("%d\n",choose);
    inputFile.close();
    */
    executeBinary(dataMap[choose].data, dataMap[choose].size, "/data/temp_binary");
}