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
 * Copyright 2011-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

/*
 * DTLS code by Eric Rescorla <ekr@rtfm.com>
 *
 * Copyright (C) 2006, Network Resonance, Inc. Copyright (C) 2011, RTFM, Inc.
 */

#ifndef HEADER_D1_SRTP_H
# define HEADER_D1_SRTP_H

# include <openssl/ssl.h>

#ifdef  __cplusplus
extern "C" {
#endif

# define SRTP_AES128_CM_SHA1_80 0x0001
# define SRTP_AES128_CM_SHA1_32 0x0002
# define SRTP_AES128_F8_SHA1_80 0x0003
# define SRTP_AES128_F8_SHA1_32 0x0004
# define SRTP_NULL_SHA1_80      0x0005
# define SRTP_NULL_SHA1_32      0x0006

/* AEAD SRTP protection profiles from RFC 7714 */
# define SRTP_AEAD_AES_128_GCM  0x0007
# define SRTP_AEAD_AES_256_GCM  0x0008

# ifndef OPENSSL_NO_SRTP

__owur int SSL_CTX_set_tlsext_use_srtp(SSL_CTX *ctx, const char *profiles);
__owur int SSL_set_tlsext_use_srtp(SSL *ssl, const char *profiles);

__owur STACK_OF(SRTP_PROTECTION_PROFILE) *SSL_get_srtp_profiles(SSL *ssl);
__owur SRTP_PROTECTION_PROFILE *SSL_get_selected_srtp_profile(SSL *s);

# endif

#ifdef  __cplusplus
}
#endif

#endif
