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
#include "my_str.h"
#include <stdio.h>
#include <iostream>
#include <stddef.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <random>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdio>
#include <cstdarg>


/*
JiaNan 2024/12/05
仅供学习参考
不得用于非法用途
*/

/*
请尽量避免使用 Cerr 和 Cout 来进行输出，重写两个系统函数很麻烦（钱不到位），如果要使用的话全局替换你的Cerr和Cout为my_cerr和my_cout
例：
my_cerr << "这是一条错误信息" << std::endl;
my_cout << "这是一条标准输出信息" << std::endl;


打印输出，全部替换为printf

使用方法：
编译my_str.cpp,在你的mian.cpp或者要重写的文件中引入
#include <my_str.h>


不一定非要使用my_str这种命名，可以自己改为nmsl_str_fw这种命名
my_str容易猜到，然后hook这个函数就又hoom了
*/


//随机数计算
std::string 随机字符(size_t length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/";
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    std::string random_string;

    for (size_t i = 0; i < length; ++i)
    {
        random_string += charset[dist(rng)];
    }

    return random_string;
}
/*
// 自定义 Cerr 输出流类定义
MyCerrStream& MyCerrStream::operator<<(const std::string& str) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cerr << str;
    return *this;
}

MyCerrStream& MyCerrStream::operator<<(const char* str) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cerr << str;
    return *this;
}

MyCerrStream& MyCerrStream::operator<<(int value) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cerr << value;
    return *this;
}

MyCerrStream& MyCerrStream::operator<<(float value) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cerr << value;
    return *this;
}

MyCerrStream& MyCerrStream::operator<<(double value) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cerr << value;
    return *this;
}
MyCerrStream my_cerr;  // 实例化 my_cerr

// 自定义 Cout 输出流类定义
MyCoutStream& MyCoutStream::operator<<(const std::string& str) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cout << str;
    return *this;
}

MyCoutStream& MyCoutStream::operator<<(const char* str) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cout << str;
    return *this;
}

MyCoutStream& MyCoutStream::operator<<(int value) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cout << value;
    return *this;
}

MyCoutStream& MyCoutStream::operator<<(float value) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cout << value;
    return *this;
}

MyCoutStream& MyCoutStream::operator<<(double value) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20);
    }
    std::cout << value;
    return *this;
}

MyCoutStream my_cout;  // 实例化 my_cout

*/
// 自定义 gethostbyname 函数
struct hostent *my_gethostbyname(const char *name) {
    // 生成随机数以增加安全性，防止被劫持
    std::random_device rd; // 获取随机数生成器
    std::default_random_engine eng(rd()); // 使用随机数种子
    std::uniform_int_distribution<int> distr(100, 200); // 定义随机数范围

    // 产生随机字符，作为防护措施
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20); // 产生随机字符
    }

    // 调用系统提供的 gethostbyname 函数
    return gethostbyname(name);
}


// 自定义 gethostbyname2 函数
struct hostent *my_gethostbyname2(const char *name, int af) {
    // 生成随机数以增加安全性，防止被劫持
    std::random_device rd; // 获取随机数生成器
    std::default_random_engine eng(rd()); // 使用随机数种子
    std::uniform_int_distribution<int> distr(100, 200); // 定义随机数范围

    // 产生随机字符，作为防护措施
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20); // 产生随机字符
    }
    // 调用系统提供的 gethostbyname2 函数
    return gethostbyname2(name, af);
}

// 自定义 getaddrinfo 函数
int my_getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res) {
    // 生成随机数以增加安全性，防止被劫持
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    // 产生随机字符，作为防护措施
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20); // 产生随机字符
    }

    // 调用系统提供的 getaddrinfo 函数
    return getaddrinfo(node, service, hints, res);
}
/*
// 自定义 iptables 函数
int my_iptables(const char* command) {
    // 随机字符增强安全性
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);

    // 产生随机字符，作为防护措施
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20); // 产生随机字符
    }

    // 执行 iptables 命令
    return system(command);
}

// 自定义 system 函数
int my_system(const char* command) {
    // 随机字符增强安全性
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);

    // 产生随机字符，作为防护措施
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20); // 产生随机字符
    }

    // 调用原 system 函数执行命令
    return system(command);
}
*/

// 自定义 snprintf 函数
int my_snprintf(char *buffer, size_t size, const char *format, ...) {
    va_list args; // 声明参数列表
    va_start(args, format); // 初始化参数列表

    // 生成随机数以增加安全性，防止被劫持
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    // 产生随机字符，作为防护措施
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20); // 产生随机字符
    }

    // 调用系统提供的 vsnprintf 函数，将格式化字符串写入缓冲区
    int result = vsnprintf(buffer, size, format, args);
    va_end(args); // 结束参数列表
    return result; // 返回格式化后的字符串长度
}

// 自定义 sprintf 函数
int my_sprintf(char *buffer, const char *format, ...) {
    va_list args; // 声明参数列表
    va_start(args, format); // 初始化参数列表

    // 生成随机数以增加安全性，防止被劫持
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    // 产生随机字符，作为防护措施
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20); // 产生随机字符
    }

    // 调用系统提供的 vsprintf 函数，将格式化字符串写入缓冲区
    int result = vsprintf(buffer, format, args);
    va_end(args); // 结束参数列表
    return result; // 返回格式化后的字符串长度
}

// 自定义 printf 函数
int my_printf(const char *format, ...) {
    va_list args; // 声明参数列表
    va_start(args, format); // 初始化参数列表

    // 生成随机数以增加安全性，防止被劫持
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(100, 200);
    
    // 产生随机字符，作为防护措施
    for (int i = 0; i < distr(eng); ++i) {
        随机字符(20); // 产生随机字符
    }

    // 调用系统提供的 vprintf 函数，将格式化字符串输出到标准输出
    int result = vprintf(format, args);
    va_end(args); // 结束参数列表
    return result; // 返回输出的字符数
}



// 自定义 strlen 函数
size_t my_strlen(const char *str) {
    const char *s = str; // 保存指针以计算长度
    while (*s) { // 遍历字符串直到结束符
        s++; // 移动指针
    }
    return s - str; // 返回字符串的长度
}

// 自定义 strstr 函数
char *my_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') { // 如果 needle 为空字符串
        return const_cast<char*>(haystack); // 返回 haystack
    }
    const char *h = haystack; // 保存 haystack 的起始位置
    while (*h) { // 遍历 haystack
        const char *h_start = h; // 记录当前起始位置
        const char *n = needle; // 记录 needle 的起始位置
        while (*h && *n && (*h == *n)) { // 在 haystack 中匹配 needle
            ++h; // 移动指针
            ++n; // 移动指针
        }
        if (!*n) { // 如果 needle 完全匹配
            return const_cast<char*>(h_start); // 返回 haystack 的起始位置
        }
        h = h_start + 1; // 否则，继续从下一个字符开始
    }
    return nullptr; // 如果未找到匹配，返回 nullptr
}


// 自定义 strcmp 函数
int my_strcmp(const char *str1, const char *str2) {
    while (*str1 && *str2) { // 遍历两个字符串
        if (*str1 != *str2) { // 如果字符不相等
            return static_cast<unsigned char>(*str1) - static_cast<unsigned char>(*str2); // 返回差值
        }
        ++str1; // 移动指针
        ++str2; // 移动指针
    }
    return static_cast<unsigned char>(*str1) - static_cast<unsigned char>(*str2); // 返回最终比较结果
}



// 自定义 strncmp 函数
int my_strncmp(const char *str1, const char *str2, size_t n) {
    while (n && *str1 && *str2) { // 在限制长度内比较字符
        if (*str1 != *str2) { // 如果字符不相等
            return static_cast<unsigned char>(*str1) - static_cast<unsigned char>(*str2); // 返回差值
        }
        ++str1; // 移动指针
        ++str2; // 移动指针
        --n; // 减少计数
    }
    return n ? static_cast<unsigned char>(*str1) - static_cast<unsigned char>(*str2) : 0; // 返回比较结果
}

// 自定义 strdup 函数
char *my_strdup(const char *s) {
    size_t len = my_strlen(s); // 计算字符串长度
    char *dup = new char[len + 1]; // 动态分配内存
    if (dup) {
        my_strcpy(dup, s); // 使用自定义的字符串复制函数
    }
    return dup; // 返回复制的字符串
}


// 自定义 strrchr 函数
char *my_strrchr(const char *str, int c) {
    const char *last = nullptr; // 保存最后一个匹配的位置
    while (*str) { // 遍历字符串
        if (*str == static_cast<char>(c)) { // 如果找到匹配的字符
            last = str; // 更新最后匹配的位置
        }
        str++; // 移动指针
    }
    return const_cast<char*>(last); // 返回最后匹配的字符位置
}




// 自定义 字符串复制函数
void my_strcpy(char *dest, const char *src) {
    while ((*dest++ = *src++)); // 逐字符复制，直到遇到结束符
}


//自定义文件访问权限检查函数
int my_access(const char *filename, int mode) {
    std::random_device rd; // 获取随机数种子
    std::default_random_engine eng(rd()); // 初始化随机数引擎
    std::uniform_int_distribution<int> distr(100, 200); // 设置均匀分布范围
    int random_number = distr(eng);
    int random_number2 = distr(eng);
    int a = 0;
    for (int i = 0; i < random_number; i++) {
        access(随机字符(40).c_str(), mode); // 生成随机文件名
    }
    a = access(filename, mode);

    for (int i = 0; i < random_number2; i++) {
        access(随机字符(40).c_str(), mode);
    }
    return a;
}