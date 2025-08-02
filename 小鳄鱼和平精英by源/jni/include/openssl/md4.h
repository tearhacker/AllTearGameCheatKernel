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

#ifndef HEADER_MD4_H
# define HEADER_MD4_H

# include <openssl/opensslconf.h>

# ifndef OPENSSL_NO_MD4
# include <openssl/e_os2.h>
# include <stddef.h>
# ifdef  __cplusplus
extern "C" {
# endif

/*-
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * ! MD4_LONG has to be at least 32 bits wide.                     !
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */
# define MD4_LONG unsigned int

# define MD4_CBLOCK      64
# define MD4_LBLOCK      (MD4_CBLOCK/4)
# define MD4_DIGEST_LENGTH 16

typedef struct MD4state_st {
    MD4_LONG A, B, C, D;
    MD4_LONG Nl, Nh;
    MD4_LONG data[MD4_LBLOCK];
    unsigned int num;
} MD4_CTX;

int MD4_Init(MD4_CTX *c);
int MD4_Update(MD4_CTX *c, const void *data, size_t len);
int MD4_Final(unsigned char *md, MD4_CTX *c);
unsigned char *MD4(const unsigned char *d, size_t n, unsigned char *md);
void MD4_Transform(MD4_CTX *c, const unsigned char *b);

# ifdef  __cplusplus
}
# endif
# endif

#endif
