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
 * Copyright 1995-2017 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_TXT_DB_H
# define HEADER_TXT_DB_H

# include <openssl/opensslconf.h>
# include <openssl/bio.h>
# include <openssl/safestack.h>
# include <openssl/lhash.h>

# define DB_ERROR_OK                     0
# define DB_ERROR_MALLOC                 1
# define DB_ERROR_INDEX_CLASH            2
# define DB_ERROR_INDEX_OUT_OF_RANGE     3
# define DB_ERROR_NO_INDEX               4
# define DB_ERROR_INSERT_INDEX_CLASH     5
# define DB_ERROR_WRONG_NUM_FIELDS       6

#ifdef  __cplusplus
extern "C" {
#endif

typedef OPENSSL_STRING *OPENSSL_PSTRING;
DEFINE_SPECIAL_STACK_OF(OPENSSL_PSTRING, OPENSSL_STRING)

typedef struct txt_db_st {
    int num_fields;
    STACK_OF(OPENSSL_PSTRING) *data;
    LHASH_OF(OPENSSL_STRING) **index;
    int (**qual) (OPENSSL_STRING *);
    long error;
    long arg1;
    long arg2;
    OPENSSL_STRING *arg_row;
} TXT_DB;

TXT_DB *TXT_DB_read(BIO *in, int num);
long TXT_DB_write(BIO *out, TXT_DB *db);
int TXT_DB_create_index(TXT_DB *db, int field, int (*qual) (OPENSSL_STRING *),
                        OPENSSL_LH_HASHFUNC hash, OPENSSL_LH_COMPFUNC cmp);
void TXT_DB_free(TXT_DB *db);
OPENSSL_STRING *TXT_DB_get_by_index(TXT_DB *db, int idx,
                                    OPENSSL_STRING *value);
int TXT_DB_insert(TXT_DB *db, OPENSSL_STRING *value);

#ifdef  __cplusplus
}
#endif

#endif
