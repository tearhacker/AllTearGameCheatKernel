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
 * Copyright 2022-2024 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_QUIC_H
# define OPENSSL_QUIC_H
# pragma once

# include <openssl/macros.h>
# include <openssl/ssl.h>

# ifndef OPENSSL_NO_QUIC

#  ifdef __cplusplus
extern "C" {
#  endif

/*
 * Method used for non-thread-assisted QUIC client operation.
 */
__owur const SSL_METHOD *OSSL_QUIC_client_method(void);

/*
 * Method used for thread-assisted QUIC client operation.
 */
__owur const SSL_METHOD *OSSL_QUIC_client_thread_method(void);

/*
 * QUIC transport error codes (RFC 9000 s. 20.1)
 */
#  define OSSL_QUIC_ERR_NO_ERROR                  0x00
#  define OSSL_QUIC_ERR_INTERNAL_ERROR            0x01
#  define OSSL_QUIC_ERR_CONNECTION_REFUSED        0x02
#  define OSSL_QUIC_ERR_FLOW_CONTROL_ERROR        0x03
#  define OSSL_QUIC_ERR_STREAM_LIMIT_ERROR        0x04
#  define OSSL_QUIC_ERR_STREAM_STATE_ERROR        0x05
#  define OSSL_QUIC_ERR_FINAL_SIZE_ERROR          0x06
#  define OSSL_QUIC_ERR_FRAME_ENCODING_ERROR      0x07
#  define OSSL_QUIC_ERR_TRANSPORT_PARAMETER_ERROR 0x08
#  define OSSL_QUIC_ERR_CONNECTION_ID_LIMIT_ERROR 0x09
#  define OSSL_QUIC_ERR_PROTOCOL_VIOLATION        0x0A
#  define OSSL_QUIC_ERR_INVALID_TOKEN             0x0B
#  define OSSL_QUIC_ERR_APPLICATION_ERROR         0x0C
#  define OSSL_QUIC_ERR_CRYPTO_BUFFER_EXCEEDED    0x0D
#  define OSSL_QUIC_ERR_KEY_UPDATE_ERROR          0x0E
#  define OSSL_QUIC_ERR_AEAD_LIMIT_REACHED        0x0F
#  define OSSL_QUIC_ERR_NO_VIABLE_PATH            0x10

/* Inclusive range for handshake-specific errors. */
#  define OSSL_QUIC_ERR_CRYPTO_ERR_BEGIN          0x0100
#  define OSSL_QUIC_ERR_CRYPTO_ERR_END            0x01FF

#  define OSSL_QUIC_ERR_CRYPTO_ERR(X) \
    (OSSL_QUIC_ERR_CRYPTO_ERR_BEGIN + (X))

/* Local errors. */
#  define OSSL_QUIC_LOCAL_ERR_IDLE_TIMEOUT        \
    ((uint64_t)0xFFFFFFFFFFFFFFFFULL)

#  ifdef __cplusplus
}
#  endif

# endif /* OPENSSL_NO_QUIC */
#endif
