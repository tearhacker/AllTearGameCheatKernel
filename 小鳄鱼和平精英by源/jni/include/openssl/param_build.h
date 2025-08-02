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
 * Copyright 2019-2021 The OpenSSL Project Authors. All Rights Reserved.
 * Copyright (c) 2019, Oracle and/or its affiliates.  All rights reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_PARAM_BUILD_H
# define OPENSSL_PARAM_BUILD_H
# pragma once

# include <openssl/params.h>
# include <openssl/types.h>

# ifdef __cplusplus
extern "C" {
# endif

OSSL_PARAM_BLD *OSSL_PARAM_BLD_new(void);
OSSL_PARAM *OSSL_PARAM_BLD_to_param(OSSL_PARAM_BLD *bld);
void OSSL_PARAM_BLD_free(OSSL_PARAM_BLD *bld);

int OSSL_PARAM_BLD_push_int(OSSL_PARAM_BLD *bld, const char *key, int val);
int OSSL_PARAM_BLD_push_uint(OSSL_PARAM_BLD *bld, const char *key,
                             unsigned int val);
int OSSL_PARAM_BLD_push_long(OSSL_PARAM_BLD *bld, const char *key,
                             long int val);
int OSSL_PARAM_BLD_push_ulong(OSSL_PARAM_BLD *bld, const char *key,
                              unsigned long int val);
int OSSL_PARAM_BLD_push_int32(OSSL_PARAM_BLD *bld, const char *key,
                              int32_t val);
int OSSL_PARAM_BLD_push_uint32(OSSL_PARAM_BLD *bld, const char *key,
                               uint32_t val);
int OSSL_PARAM_BLD_push_int64(OSSL_PARAM_BLD *bld, const char *key,
                              int64_t val);
int OSSL_PARAM_BLD_push_uint64(OSSL_PARAM_BLD *bld, const char *key,
                               uint64_t val);
int OSSL_PARAM_BLD_push_size_t(OSSL_PARAM_BLD *bld, const char *key,
                               size_t val);
int OSSL_PARAM_BLD_push_time_t(OSSL_PARAM_BLD *bld, const char *key,
                               time_t val);
int OSSL_PARAM_BLD_push_double(OSSL_PARAM_BLD *bld, const char *key,
                               double val);
int OSSL_PARAM_BLD_push_BN(OSSL_PARAM_BLD *bld, const char *key,
                           const BIGNUM *bn);
int OSSL_PARAM_BLD_push_BN_pad(OSSL_PARAM_BLD *bld, const char *key,
                               const BIGNUM *bn, size_t sz);
int OSSL_PARAM_BLD_push_utf8_string(OSSL_PARAM_BLD *bld, const char *key,
                                    const char *buf, size_t bsize);
int OSSL_PARAM_BLD_push_utf8_ptr(OSSL_PARAM_BLD *bld, const char *key,
                                 char *buf, size_t bsize);
int OSSL_PARAM_BLD_push_octet_string(OSSL_PARAM_BLD *bld, const char *key,
                                     const void *buf, size_t bsize);
int OSSL_PARAM_BLD_push_octet_ptr(OSSL_PARAM_BLD *bld, const char *key,
                                  void *buf, size_t bsize);

# ifdef __cplusplus
}
# endif
#endif  /* OPENSSL_PARAM_BUILD_H */
