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
 * Copyright 2023 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OPENSSL_E_OSTIME_H
# define OPENSSL_E_OSTIME_H
# pragma once

# include <openssl/macros.h>
# include <openssl/opensslconf.h>
# include <openssl/e_os2.h>

/*
 * This header guarantees that 'struct timeval' will be available. It includes
 * the minimum headers needed to facilitate this. This may still be a
 * substantial set of headers on some platforms (e.g. <winsock2.h> on Win32).
 */

# if defined(OPENSSL_SYS_WINDOWS)
#  if !defined(_WINSOCKAPI_)
    /*
     * winsock2.h defines _WINSOCK2API_ and both winsock2.h and winsock.h define
     * _WINSOCKAPI_. Both of these provide struct timeval. Don't include
     * winsock2.h if either header has been included to avoid breakage with
     * applications that prefer to use <winsock.h> over <winsock2.h>.
     */
#   include <winsock2.h>
#  endif
# else
#  include <sys/time.h>
# endif

#endif
