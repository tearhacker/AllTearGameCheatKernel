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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <netdb.h> // 用于 getaddrinfo
#include <sstream>
#include <memory> // 添加智能指针支持

std::string send_post(const std::string& host, const std::string& endpoint, const std::string& params) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return "";
    }

    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(host.c_str(), "80", &hints, &res);
    if (status != 0) {
        std::cerr << "getaddrinfo failed: " << gai_strerror(status) << std::endl;
        close(sock);
        return "";
    }

    std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> res_ptr(res, freeaddrinfo);
    struct sockaddr_in *server_addr = (struct sockaddr_in *)res->ai_addr;
    server_addr->sin_port = htons(80);

    if (connect(sock, (struct sockaddr *)server_addr, sizeof(*server_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sock);
        return "";
    }

    std::string request = "POST " + endpoint + " HTTP/1.1\r\n" +
                          "Host: " + host + "\r\n" +
                          "Content-Type: application/x-www-form-urlencoded\r\n" +
                          "Content-Length: " + std::to_string(params.length()) + "\r\n" +
                          "Connection: close\r\n\r\n" +
                          params;

    if (send(sock, request.c_str(), request.length(), 0) < 0) {
        std::cerr << "Send failed" << std::endl;
        close(sock);
        return "";
    }

    std::string response;
    char buffer[4096];
    int bytes_received;
    while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        response += buffer;
    }

    // 提取响应主体
    std::string::size_type pos = response.find("\r\n\r\n");
    if (pos != std::string::npos) {
        response = response.substr(pos + 4);
    }

    return response;
} 