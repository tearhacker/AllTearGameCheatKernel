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
 * Copyright 1995-2023 The OpenSSL Project Authors. All Rights Reserved.
 * Copyright (c) 2002, Oracle and/or its affiliates. All rights reserved
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_THREAD_H
# define OPENSSL_THREAD_H

# define OSSL_THREAD_SUPPORT_FLAG_THREAD_POOL (1U<<0)
# define OSSL_THREAD_SUPPORT_FLAG_DEFAULT_SPAWN (1U<<1)

# include <openssl/types.h>

# ifdef  __cplusplus
extern "C" {
# endif

uint32_t OSSL_get_thread_support_flags(void);
int OSSL_set_max_threads(OSSL_LIB_CTX *ctx, uint64_t max_threads);
uint64_t OSSL_get_max_threads(OSSL_LIB_CTX *ctx);

# ifdef  __cplusplus
}
# endif

#endif /* OPENSSL_THREAD_H */
