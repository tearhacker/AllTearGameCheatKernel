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
#include <vector>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <iomanip>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/err.h>

using namespace std;


// RC4 密钥调度算法 (KSA)
void rc4_ksa(const std::string& key, std::vector<unsigned char>& S) {
    int key_length = key.size();
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + key[i % key_length]) % 256;
        std::swap(S[i], S[j]);
    }
}

// RC4 伪随机生成算法 (PRGA)
void rc4_prga(std::vector<unsigned char>& S, const std::string& data, std::string& output) {
    int i = 0, j = 0;
    for (size_t n = 0; n < data.size(); ++n) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        unsigned char K = S[(S[i] + S[j]) % 256];
        output.push_back(data[n] ^ K);
    }
}

// 将二进制数据转换为十六进制字符串
std::string to_hex_string(const std::string& data) {
    std::ostringstream oss;
    for (unsigned char c : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return oss.str();
}

// 将十六进制字符串转换为二进制数据
std::string from_hex_string(const std::string& hex) {
    std::string output;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = static_cast<char>(strtol(byteString.c_str(), nullptr, 16));
        output.push_back(byte);
    }
    return output;
}

// RC4 加密/解密
std::string rc4(const std::string& data, const std::string& key) {
    std::vector<unsigned char> S(256);
    rc4_ksa(key, S);

    std::string output;
    rc4_prga(S, data, output);

    return output;
} 


// Base64解码（兼容URL安全字符）
vector<unsigned char> base64_decode(const string &encoded)
{
    BIO *bio, *b64;
    vector<unsigned char> decoded(encoded.size());

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new_mem_buf(encoded.data(), encoded.length());
    bio = BIO_push(b64, bio);

    int decoded_len = BIO_read(bio, decoded.data(), encoded.size());
    decoded.resize(decoded_len);

    BIO_free_all(bio);
    return decoded;
}

// 从字符串加载公钥
RSA *load_public_key(const char *pub_key)
{
    BIO *bio = BIO_new_mem_buf(pub_key, -1);
    RSA *rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    BIO_free(bio);

    if (!rsa)
    {
        cerr << "ERROR: 公钥格式错误！请确认包含-----BEGIN PUBLIC KEY-----标记" << endl;
    }
    return rsa;
}

// 分块解密核心逻辑
string rsa_decrypt(RSA *rsa, const string &ciphertext_base64)
{
    // Base64解码
    vector<unsigned char> ciphertext = base64_decode(ciphertext_base64);
    const int key_size = RSA_size(rsa); // 获取密钥字节长度（如256）

    if (ciphertext.size() % key_size != 0)
    {
        throw runtime_error("密文长度不匹配，应为" + to_string(key_size) + "字节的整数倍");
    }

    string plaintext;
    vector<unsigned char> buf(key_size);

    // 分块解密
    for (size_t i = 0; i < ciphertext.size(); i += key_size)
    {
        int decrypt_len = RSA_public_decrypt(
            key_size,
            &ciphertext[i],
            buf.data(),
            rsa,
            RSA_PKCS1_PADDING);

        if (decrypt_len == -1)
        {
            throw runtime_error("解密失败，错误代码: " + to_string(ERR_get_error()));
        }

        plaintext.append(reinterpret_cast<char *>(buf.data()), decrypt_len);
    }

    return plaintext;
}

// Base64编码（URL安全）
string base64_encode(const vector<unsigned char> &data)
{
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, data.data(), data.size());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    string encoded(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);

    // 移除末尾换行符
    if (!encoded.empty() && encoded.back() == '\n')
    {
        encoded.pop_back();
    }
    return encoded;
}

// 分块加密核心逻辑
string rsa_encrypt(RSA *rsa, const string &plaintext)
{
    const int key_size = RSA_size(rsa);
    const int max_block_size = key_size - 11; // PKCS#1 v1.5填充最大块

    if (max_block_size <= 0)
    {
        throw runtime_error("无效的密钥长度");
    }

    vector<unsigned char> ciphertext;
    vector<unsigned char> buf(key_size);

    // 分块加密
    for (size_t i = 0; i < plaintext.size(); i += max_block_size)
    {
        int in_len = min(max_block_size, (int)(plaintext.size() - i));

        int encrypt_len = RSA_public_encrypt(
            in_len,
            reinterpret_cast<const unsigned char *>(plaintext.data() + i),
            buf.data(),
            rsa,
            RSA_PKCS1_PADDING);

        if (encrypt_len == -1)
        {
            throw runtime_error("加密失败，错误代码: " + to_string(ERR_get_error()));
        }

        ciphertext.insert(ciphertext.end(), buf.begin(), buf.begin() + encrypt_len);
    }

    return base64_encode(ciphertext);
}

