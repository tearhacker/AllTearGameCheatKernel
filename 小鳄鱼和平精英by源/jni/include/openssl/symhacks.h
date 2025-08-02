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
 * Copyright 1999-2018 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_SYMHACKS_H
# define HEADER_SYMHACKS_H

# include <openssl/e_os2.h>

/* Case insensitive linking causes problems.... */
# if defined(OPENSSL_SYS_VMS)
#  undef ERR_load_CRYPTO_strings
#  define ERR_load_CRYPTO_strings                 ERR_load_CRYPTOlib_strings
#  undef OCSP_crlID_new
#  define OCSP_crlID_new                          OCSP_crlID2_new

#  undef d2i_ECPARAMETERS
#  define d2i_ECPARAMETERS                        d2i_UC_ECPARAMETERS
#  undef i2d_ECPARAMETERS
#  define i2d_ECPARAMETERS                        i2d_UC_ECPARAMETERS
#  undef d2i_ECPKPARAMETERS
#  define d2i_ECPKPARAMETERS                      d2i_UC_ECPKPARAMETERS
#  undef i2d_ECPKPARAMETERS
#  define i2d_ECPKPARAMETERS                      i2d_UC_ECPKPARAMETERS

/* This one clashes with CMS_data_create */
#  undef cms_Data_create
#  define cms_Data_create                         priv_cms_Data_create

# endif

#endif                          /* ! defined HEADER_VMS_IDHACKS_H */
