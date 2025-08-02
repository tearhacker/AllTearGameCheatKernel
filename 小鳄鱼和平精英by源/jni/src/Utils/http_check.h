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
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <cstring>

// 发送HTTP请求并获取状态码
int checkHttpStatusCode(const std::string& host) {
    int sockfd;
    struct sockaddr_in serveraddr;
    socklen_t addrlen = sizeof(serveraddr);
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "socket: " << strerror(errno) << std::endl;
        return -1;
    }
    std::memset(&serveraddr, 0, addrlen);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(80);
    struct hostent* host_ent;
    host_ent = gethostbyname(host.c_str());
    if (host_ent == NULL) {
        std::cerr << "gethostbyname: " << strerror(h_errno) << std::endl;
        close(sockfd);
        return -1;
    }
    struct in_addr ip = *((struct in_addr *)host_ent->h_addr);
    serveraddr.sin_addr = ip;
    if (connect(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0) {
        std::cerr << "connect: " << strerror(errno) << std::endl;
        close(sockfd);
        return -1;
    }
    std::string request = "GET / HTTP/1.1\r\nHost: " + host + "\r\nConnection: close\r\n\r\n";
    if (send(sockfd, request.c_str(), request.length(), 0) < 0) {
        std::cerr << "send: " << strerror(errno) << std::endl;
        close(sockfd);
        return -1;
    }
    char buffer[1024];
    int bytes_read = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read <= 0) {
        std::cerr << "recv: " << strerror(errno) << std::endl;
        close(sockfd);
        return -1;
    }
    buffer[bytes_read] = '\0';
    // 从响应中提取状态码
    const char* status_code_start = std::strstr(buffer, "HTTP/1.1 ");
    if (status_code_start == NULL) {
        std::cerr << "Failed to find status code" << std::endl;
        close(sockfd);
        return -1;
    }
    status_code_start += 9;
    int status_code = std::atoi(status_code_start);
    close(sockfd);
    return status_code;
}