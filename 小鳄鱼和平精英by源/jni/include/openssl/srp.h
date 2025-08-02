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
 * Copyright 2004-2018 The OpenSSL Project Authors. All Rights Reserved.
 * Copyright (c) 2004, EdelKey Project. All Rights Reserved.
 *
 * Licensed under the OpenSSL license (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 *
 * Originally written by Christophe Renou and Peter Sylvester,
 * for the EdelKey project.
 */

#ifndef HEADER_SRP_H
# define HEADER_SRP_H

#include <openssl/opensslconf.h>

#ifndef OPENSSL_NO_SRP
# include <stdio.h>
# include <string.h>
# include <openssl/safestack.h>
# include <openssl/bn.h>
# include <openssl/crypto.h>

# ifdef  __cplusplus
extern "C" {
# endif

typedef struct SRP_gN_cache_st {
    char *b64_bn;
    BIGNUM *bn;
} SRP_gN_cache;


DEFINE_STACK_OF(SRP_gN_cache)

typedef struct SRP_user_pwd_st {
    /* Owned by us. */
    char *id;
    BIGNUM *s;
    BIGNUM *v;
    /* Not owned by us. */
    const BIGNUM *g;
    const BIGNUM *N;
    /* Owned by us. */
    char *info;
} SRP_user_pwd;

void SRP_user_pwd_free(SRP_user_pwd *user_pwd);

DEFINE_STACK_OF(SRP_user_pwd)

typedef struct SRP_VBASE_st {
    STACK_OF(SRP_user_pwd) *users_pwd;
    STACK_OF(SRP_gN_cache) *gN_cache;
/* to simulate a user */
    char *seed_key;
    const BIGNUM *default_g;
    const BIGNUM *default_N;
} SRP_VBASE;

/*
 * Internal structure storing N and g pair
 */
typedef struct SRP_gN_st {
    char *id;
    const BIGNUM *g;
    const BIGNUM *N;
} SRP_gN;

DEFINE_STACK_OF(SRP_gN)

SRP_VBASE *SRP_VBASE_new(char *seed_key);
void SRP_VBASE_free(SRP_VBASE *vb);
int SRP_VBASE_init(SRP_VBASE *vb, char *verifier_file);

/* This method ignores the configured seed and fails for an unknown user. */
DEPRECATEDIN_1_1_0(SRP_user_pwd *SRP_VBASE_get_by_user(SRP_VBASE *vb, char *username))
/* NOTE: unlike in SRP_VBASE_get_by_user, caller owns the returned pointer.*/
SRP_user_pwd *SRP_VBASE_get1_by_user(SRP_VBASE *vb, char *username);

char *SRP_create_verifier(const char *user, const char *pass, char **salt,
                          char **verifier, const char *N, const char *g);
int SRP_create_verifier_BN(const char *user, const char *pass, BIGNUM **salt,
                           BIGNUM **verifier, const BIGNUM *N,
                           const BIGNUM *g);

# define SRP_NO_ERROR 0
# define SRP_ERR_VBASE_INCOMPLETE_FILE 1
# define SRP_ERR_VBASE_BN_LIB 2
# define SRP_ERR_OPEN_FILE 3
# define SRP_ERR_MEMORY 4

# define DB_srptype      0
# define DB_srpverifier  1
# define DB_srpsalt      2
# define DB_srpid        3
# define DB_srpgN        4
# define DB_srpinfo      5
# undef  DB_NUMBER
# define DB_NUMBER       6

# define DB_SRP_INDEX    'I'
# define DB_SRP_VALID    'V'
# define DB_SRP_REVOKED  'R'
# define DB_SRP_MODIF    'v'

/* see srp.c */
char *SRP_check_known_gN_param(const BIGNUM *g, const BIGNUM *N);
SRP_gN *SRP_get_default_gN(const char *id);

/* server side .... */
BIGNUM *SRP_Calc_server_key(const BIGNUM *A, const BIGNUM *v, const BIGNUM *u,
                            const BIGNUM *b, const BIGNUM *N);
BIGNUM *SRP_Calc_B(const BIGNUM *b, const BIGNUM *N, const BIGNUM *g,
                   const BIGNUM *v);
int SRP_Verify_A_mod_N(const BIGNUM *A, const BIGNUM *N);
BIGNUM *SRP_Calc_u(const BIGNUM *A, const BIGNUM *B, const BIGNUM *N);

/* client side .... */
BIGNUM *SRP_Calc_x(const BIGNUM *s, const char *user, const char *pass);
BIGNUM *SRP_Calc_A(const BIGNUM *a, const BIGNUM *N, const BIGNUM *g);
BIGNUM *SRP_Calc_client_key(const BIGNUM *N, const BIGNUM *B, const BIGNUM *g,
                            const BIGNUM *x, const BIGNUM *a, const BIGNUM *u);
int SRP_Verify_B_mod_N(const BIGNUM *B, const BIGNUM *N);

# define SRP_MINIMAL_N 1024

# ifdef  __cplusplus
}
# endif
# endif

#endif
