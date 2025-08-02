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
/*
 * Copyright 1995-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_IDEA_H
# define HEADER_IDEA_H

# include <openssl/opensslconf.h>

# ifndef OPENSSL_NO_IDEA
# ifdef  __cplusplus
extern "C" {
# endif

typedef unsigned int IDEA_INT;

# define IDEA_ENCRYPT    1
# define IDEA_DECRYPT    0

# define IDEA_BLOCK      8
# define IDEA_KEY_LENGTH 16

typedef struct idea_key_st {
    IDEA_INT data[9][6];
} IDEA_KEY_SCHEDULE;

const char *IDEA_options(void);
void IDEA_ecb_encrypt(const unsigned char *in, unsigned char *out,
                      IDEA_KEY_SCHEDULE *ks);
void IDEA_set_encrypt_key(const unsigned char *key, IDEA_KEY_SCHEDULE *ks);
void IDEA_set_decrypt_key(IDEA_KEY_SCHEDULE *ek, IDEA_KEY_SCHEDULE *dk);
void IDEA_cbc_encrypt(const unsigned char *in, unsigned char *out,
                      long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv,
                      int enc);
void IDEA_cfb64_encrypt(const unsigned char *in, unsigned char *out,
                        long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv,
                        int *num, int enc);
void IDEA_ofb64_encrypt(const unsigned char *in, unsigned char *out,
                        long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv,
                        int *num);
void IDEA_encrypt(unsigned long *in, IDEA_KEY_SCHEDULE *ks);

# if OPENSSL_API_COMPAT < 0x10100000L
#  define idea_options          IDEA_options
#  define idea_ecb_encrypt      IDEA_ecb_encrypt
#  define idea_set_encrypt_key  IDEA_set_encrypt_key
#  define idea_set_decrypt_key  IDEA_set_decrypt_key
#  define idea_cbc_encrypt      IDEA_cbc_encrypt
#  define idea_cfb64_encrypt    IDEA_cfb64_encrypt
#  define idea_ofb64_encrypt    IDEA_ofb64_encrypt
#  define idea_encrypt          IDEA_encrypt
# endif

# ifdef  __cplusplus
}
# endif
# endif

#endif
