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
 * Copyright 2020-2021 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_CORE_OBJECT_H
# define OPENSSL_CORE_OBJECT_H
# pragma once

# ifdef __cplusplus
extern "C" {
# endif

/*-
 * Known object types
 *
 * These numbers are used as values for the OSSL_PARAM parameter
 * OSSL_OBJECT_PARAM_TYPE.
 *
 * For most of these types, there's a corresponding libcrypto object type.
 * The corresponding type is indicated with a comment after the number.
 */
# define OSSL_OBJECT_UNKNOWN            0
# define OSSL_OBJECT_NAME               1 /* char * */
# define OSSL_OBJECT_PKEY               2 /* EVP_PKEY * */
# define OSSL_OBJECT_CERT               3 /* X509 * */
# define OSSL_OBJECT_CRL                4 /* X509_CRL * */

/*
 * The rest of the associated OSSL_PARAM elements is described in core_names.h
 */

# ifdef __cplusplus
}
# endif

#endif
