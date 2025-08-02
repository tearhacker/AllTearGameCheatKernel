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

#ifndef HEADER_RC5_H
# define HEADER_RC5_H

# include <openssl/opensslconf.h>

# ifndef OPENSSL_NO_RC5
# ifdef  __cplusplus
extern "C" {
# endif

# define RC5_ENCRYPT     1
# define RC5_DECRYPT     0

# define RC5_32_INT unsigned int

# define RC5_32_BLOCK            8
# define RC5_32_KEY_LENGTH       16/* This is a default, max is 255 */

/*
 * This are the only values supported.  Tweak the code if you want more The
 * most supported modes will be RC5-32/12/16 RC5-32/16/8
 */
# define RC5_8_ROUNDS    8
# define RC5_12_ROUNDS   12
# define RC5_16_ROUNDS   16

typedef struct rc5_key_st {
    /* Number of rounds */
    int rounds;
    RC5_32_INT data[2 * (RC5_16_ROUNDS + 1)];
} RC5_32_KEY;

void RC5_32_set_key(RC5_32_KEY *key, int len, const unsigned char *data,
                    int rounds);
void RC5_32_ecb_encrypt(const unsigned char *in, unsigned char *out,
                        RC5_32_KEY *key, int enc);
void RC5_32_encrypt(unsigned long *data, RC5_32_KEY *key);
void RC5_32_decrypt(unsigned long *data, RC5_32_KEY *key);
void RC5_32_cbc_encrypt(const unsigned char *in, unsigned char *out,
                        long length, RC5_32_KEY *ks, unsigned char *iv,
                        int enc);
void RC5_32_cfb64_encrypt(const unsigned char *in, unsigned char *out,
                          long length, RC5_32_KEY *schedule,
                          unsigned char *ivec, int *num, int enc);
void RC5_32_ofb64_encrypt(const unsigned char *in, unsigned char *out,
                          long length, RC5_32_KEY *schedule,
                          unsigned char *ivec, int *num);

# ifdef  __cplusplus
}
# endif
# endif

#endif
