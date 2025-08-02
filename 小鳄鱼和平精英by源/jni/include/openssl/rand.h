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
 * Copyright 1995-2018 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_RAND_H
# define HEADER_RAND_H

# include <stdlib.h>
# include <openssl/ossl_typ.h>
# include <openssl/e_os2.h>
# include <openssl/randerr.h>

#ifdef  __cplusplus
extern "C" {
#endif

struct rand_meth_st {
    int (*seed) (const void *buf, int num);
    int (*bytes) (unsigned char *buf, int num);
    void (*cleanup) (void);
    int (*add) (const void *buf, int num, double randomness);
    int (*pseudorand) (unsigned char *buf, int num);
    int (*status) (void);
};

int RAND_set_rand_method(const RAND_METHOD *meth);
const RAND_METHOD *RAND_get_rand_method(void);
# ifndef OPENSSL_NO_ENGINE
int RAND_set_rand_engine(ENGINE *engine);
# endif

RAND_METHOD *RAND_OpenSSL(void);

# if OPENSSL_API_COMPAT < 0x10100000L
#   define RAND_cleanup() while(0) continue
# endif
int RAND_bytes(unsigned char *buf, int num);
int RAND_priv_bytes(unsigned char *buf, int num);
DEPRECATEDIN_1_1_0(int RAND_pseudo_bytes(unsigned char *buf, int num))

void RAND_seed(const void *buf, int num);
void RAND_keep_random_devices_open(int keep);

# if defined(__ANDROID__) && defined(__NDK_FPABI__)
__NDK_FPABI__	/* __attribute__((pcs("aapcs"))) on ARM */
# endif
void RAND_add(const void *buf, int num, double randomness);
int RAND_load_file(const char *file, long max_bytes);
int RAND_write_file(const char *file);
const char *RAND_file_name(char *file, size_t num);
int RAND_status(void);

# ifndef OPENSSL_NO_EGD
int RAND_query_egd_bytes(const char *path, unsigned char *buf, int bytes);
int RAND_egd(const char *path);
int RAND_egd_bytes(const char *path, int bytes);
# endif

int RAND_poll(void);

# if defined(_WIN32) && (defined(BASETYPES) || defined(_WINDEF_H))
/* application has to include <windows.h> in order to use these */
DEPRECATEDIN_1_1_0(void RAND_screen(void))
DEPRECATEDIN_1_1_0(int RAND_event(UINT, WPARAM, LPARAM))
# endif


#ifdef  __cplusplus
}
#endif

#endif
