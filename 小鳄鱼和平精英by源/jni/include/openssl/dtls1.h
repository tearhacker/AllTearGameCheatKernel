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
 * Copyright 2005-2018 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_DTLS1_H
# define HEADER_DTLS1_H

#ifdef  __cplusplus
extern "C" {
#endif

# define DTLS1_VERSION                   0xFEFF
# define DTLS1_2_VERSION                 0xFEFD
# define DTLS_MIN_VERSION                DTLS1_VERSION
# define DTLS_MAX_VERSION                DTLS1_2_VERSION
# define DTLS1_VERSION_MAJOR             0xFE

# define DTLS1_BAD_VER                   0x0100

/* Special value for method supporting multiple versions */
# define DTLS_ANY_VERSION                0x1FFFF

/* lengths of messages */
/*
 * Actually the max cookie length in DTLS is 255. But we can't change this now
 * due to compatibility concerns.
 */
# define DTLS1_COOKIE_LENGTH                     256

# define DTLS1_RT_HEADER_LENGTH                  13

# define DTLS1_HM_HEADER_LENGTH                  12

# define DTLS1_HM_BAD_FRAGMENT                   -2
# define DTLS1_HM_FRAGMENT_RETRY                 -3

# define DTLS1_CCS_HEADER_LENGTH                  1

# define DTLS1_AL_HEADER_LENGTH                   2

/* Timeout multipliers */
# define DTLS1_TMO_READ_COUNT                      2
# define DTLS1_TMO_WRITE_COUNT                     2

# define DTLS1_TMO_ALERT_COUNT                     12

#ifdef  __cplusplus
}
#endif
#endif
