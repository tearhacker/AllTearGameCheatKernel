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
#ifndef 手持调用_H
#define 手持调用_H
#include "./include/My_Utils/imgui_image.h"
#include <map>
#include "手持图片/101001.h"
#include "手持图片/101002.h"
#include "手持图片/101003.h"
#include "手持图片/101004.h"
#include "手持图片/101005.h"
#include "手持图片/101006.h"
#include "手持图片/101007.h"
#include "手持图片/101008.h"
#include "手持图片/101009.h"
#include "手持图片/101010.h"
#include "手持图片/101011.h"
#include "手持图片/101012.h"
#include "手持图片/102001.h"
#include "手持图片/102002.h"
#include "手持图片/102003.h"
#include "手持图片/102004.h"
#include "手持图片/102005.h"
#include "手持图片/102007.h"
#include "手持图片/102105.h"
#include "手持图片/103001.h"
#include "手持图片/103002.h"
#include "手持图片/103003.h"
#include "手持图片/103004.h"
#include "手持图片/103005.h"
#include "手持图片/103006.h"
#include "手持图片/103007.h"
#include "手持图片/103008.h"
#include "手持图片/103009.h"
#include "手持图片/103010.h"
#include "手持图片/103011.h"
#include "手持图片/103012.h"
#include "手持图片/103013.h"
#include "手持图片/103014.h"
#include "手持图片/103015.h"
#include "手持图片/103100.h"
#include "手持图片/103901.h"
#include "手持图片/103902.h"
#include "手持图片/103903.h"
#include "手持图片/104001.h"
#include "手持图片/104002.h"
#include "手持图片/104003.h"
#include "手持图片/104004.h"
#include "手持图片/104100.h"
#include "手持图片/105001.h"
#include "手持图片/105002.h"
#include "手持图片/105010.h"
#include "手持图片/106001.h"
#include "手持图片/106002.h"
#include "手持图片/106003.h"
#include "手持图片/106004.h"
#include "手持图片/106005.h"
#include "手持图片/106006.h"
#include "手持图片/106007.h"
#include "手持图片/106008.h"
#include "手持图片/106010.h"
#include "手持图片/107001.h"
#include "手持图片/107007.h"
#include "手持图片/108001.h"
#include "手持图片/108002.h"
#include "手持图片/108003.h"
#include "手持图片/108004.h"
#include "手持图片/602001.h"
#include "手持图片/602002.h"
#include "手持图片/602003.h"
#include "手持图片/602004.h"

#include "手持图片/101013.h"
#include "手持图片/102008.h"
#include "手持图片/106011.h"
#include "手持图片/107006.h"
#include "手持图片/107008.h"

#include "手持图片/真人.h"
#include "手持图片/人机.h"
#include "手持图片/拳头.h"
#include "手持图片/盒子.h"
#include "手持图片/自瞄按钮1.h"
#include "手持图片/自瞄按钮2.h"

#include "手持图片/车辆/2001001.png.h"
#include "手持图片/车辆/2001002.png.h"
#include "手持图片/车辆/2001003.png.h"
#include "手持图片/车辆/2001004.png.h"
#include "手持图片/车辆/2001005.png.h"
#include "手持图片/车辆/2001006.png.h"
#include "手持图片/车辆/2001007.png.h"
#include "手持图片/车辆/2001008.png.h"
#include "手持图片/车辆/2001009.png.h"
#include "手持图片/车辆/2001010.png.h"
#include "手持图片/车辆/2001011.png.h"
#include "手持图片/车辆/2001012.png.h"
#include "手持图片/车辆/2001013.png.h"
#include "手持图片/车辆/2001014.png.h"

#include "手持图片/车辆/2002001.png.h"
#include "手持图片/车辆/2002002.png.h"
#include "手持图片/车辆/2002003.png.h"
#include "手持图片/车辆/2002004.png.h"
#include "手持图片/车辆/2002005.png.h"
#include "手持图片/车辆/2002006.png.h"

#include "手持图片/车辆/2003001.png.h"
#include "手持图片/车辆/2003002.png.h"
#include "手持图片/车辆/2004001.png.h"
#include "手持图片/车辆/2004002.png.h"

#include "手持图片/图标.h"
#include "手持图片/背景.h"
#include "手持图片/Logo/快手.h"

#include "手持图片/宝箱.h"
#include "手持图片/药箱.h"
#include "手持图片/武器箱.h"

extern std::map<int, TextureInfo> 手持图片;

inline void 加载内存图片()
{

    手持图片[250] = createTexture_ALL_FromMem(宝箱, sizeof(宝箱));
    手持图片[251] = createTexture_ALL_FromMem(药箱, sizeof(药箱));
    手持图片[252] = createTexture_ALL_FromMem(武器箱, sizeof(武器箱));

    手持图片[200] = createTexture_ALL_FromMem(快手logo, sizeof(快手logo));

    手持图片[30] = createTexture_ALL_FromMem(picture_obj_2001001, sizeof(picture_obj_2001001)); // 蹦蹦车
    手持图片[31] = createTexture_ALL_FromMem(picture_obj_2001002, sizeof(picture_obj_2001002));
    手持图片[32] = createTexture_ALL_FromMem(picture_obj_2001003, sizeof(picture_obj_2001003));
    手持图片[33] = createTexture_ALL_FromMem(picture_obj_2001004, sizeof(picture_obj_2001004));
    手持图片[34] = createTexture_ALL_FromMem(picture_obj_2001005, sizeof(picture_obj_2001005));
    手持图片[35] = createTexture_ALL_FromMem(picture_obj_2001006, sizeof(picture_obj_2001006));
    手持图片[36] = createTexture_ALL_FromMem(picture_obj_2001007, sizeof(picture_obj_2001007));
    手持图片[37] = createTexture_ALL_FromMem(picture_obj_2001008, sizeof(picture_obj_2001008));
    手持图片[38] = createTexture_ALL_FromMem(picture_obj_2001009, sizeof(picture_obj_2001009));
    手持图片[39] = createTexture_ALL_FromMem(picture_obj_2001010, sizeof(picture_obj_2001010));
    手持图片[53] = createTexture_ALL_FromMem(picture_obj_2001011, sizeof(picture_obj_2001011));

    手持图片[40] = createTexture_ALL_FromMem(picture_obj_2001012, sizeof(picture_obj_2001012));
    手持图片[41] = createTexture_ALL_FromMem(picture_obj_2001013, sizeof(picture_obj_2001013));
    手持图片[42] = createTexture_ALL_FromMem(picture_obj_2001014, sizeof(picture_obj_2001014));

    手持图片[43] = createTexture_ALL_FromMem(picture_obj_2002001, sizeof(picture_obj_2002001));
    手持图片[44] = createTexture_ALL_FromMem(picture_obj_2002002, sizeof(picture_obj_2002002));
    手持图片[45] = createTexture_ALL_FromMem(picture_obj_2002003, sizeof(picture_obj_2002003));
    手持图片[46] = createTexture_ALL_FromMem(picture_obj_2002004, sizeof(picture_obj_2002004));
    手持图片[47] = createTexture_ALL_FromMem(picture_obj_2002005, sizeof(picture_obj_2002005));
    手持图片[48] = createTexture_ALL_FromMem(picture_obj_2002006, sizeof(picture_obj_2002006));

    手持图片[49] = createTexture_ALL_FromMem(picture_obj_2003001, sizeof(picture_obj_2003001));
    手持图片[50] = createTexture_ALL_FromMem(picture_obj_2003002, sizeof(picture_obj_2003002));
    手持图片[51] = createTexture_ALL_FromMem(picture_obj_2004001, sizeof(picture_obj_2004001));
    手持图片[52] = createTexture_ALL_FromMem(picture_obj_2004002, sizeof(picture_obj_2004002));

    手持图片[10] = createTexture_ALL_FromMem(人机图片, sizeof(人机图片));
    手持图片[60] = createTexture_ALL_FromMem(图标, sizeof(图标));
    手持图片[61] = createTexture_ALL_FromMem(背景, sizeof(背景));
    手持图片[11] = createTexture_ALL_FromMem(真人图片, sizeof(真人图片));
    手持图片[12] = createTexture_ALL_FromMem(picture_盒子_png, sizeof(picture_盒子_png));
    手持图片[0] = createTexture_ALL_FromMem(picture_拳头_png, sizeof(picture_拳头_png));

    手持图片[101013] = createTexture_ALL_FromMem(picture_101013_png, sizeof(picture_101013_png));
    手持图片[102008] = createTexture_ALL_FromMem(picture_102008_png, sizeof(picture_102008_png));
    手持图片[106011] = createTexture_ALL_FromMem(picture_106011_png, sizeof(picture_106011_png));
    手持图片[107006] = createTexture_ALL_FromMem(picture_107006_png, sizeof(picture_107006_png));
    手持图片[107008] = createTexture_ALL_FromMem(picture_107008_png, sizeof(picture_107008_png));

    手持图片[3] = createTexture_ALL_FromMem(FunnelIcon4, sizeof(FunnelIcon4));
    手持图片[4] = createTexture_ALL_FromMem(FunnelIcon5, sizeof(FunnelIcon5));

    手持图片[101001] = createTexture_ALL_FromMem(picture_101001_png, sizeof(picture_101001_png));
    手持图片[101002] = createTexture_ALL_FromMem(picture_101002_png, sizeof(picture_101002_png));
    手持图片[101003] = createTexture_ALL_FromMem(picture_101003_png, sizeof(picture_101003_png));
    手持图片[101004] = createTexture_ALL_FromMem(picture_101004_png, sizeof(picture_101004_png));
    手持图片[101005] = createTexture_ALL_FromMem(picture_101005_png, sizeof(picture_101005_png));
    手持图片[101006] = createTexture_ALL_FromMem(picture_101006_png, sizeof(picture_101006_png));
    手持图片[101007] = createTexture_ALL_FromMem(picture_101007_png, sizeof(picture_101007_png));
    手持图片[101008] = createTexture_ALL_FromMem(picture_101008_png, sizeof(picture_101008_png));
    手持图片[101009] = createTexture_ALL_FromMem(picture_101009_png, sizeof(picture_101009_png));
    手持图片[101010] = createTexture_ALL_FromMem(picture_101010_png, sizeof(picture_101010_png));
    手持图片[101011] = createTexture_ALL_FromMem(picture_101011_png, sizeof(picture_101011_png));
    手持图片[101012] = createTexture_ALL_FromMem(picture_101012_png, sizeof(picture_101012_png));
    手持图片[102001] = createTexture_ALL_FromMem(picture_102001_png, sizeof(picture_102001_png));
    手持图片[102002] = createTexture_ALL_FromMem(picture_102002_png, sizeof(picture_102002_png));
    手持图片[102003] = createTexture_ALL_FromMem(picture_102003_png, sizeof(picture_102003_png));
    手持图片[102004] = createTexture_ALL_FromMem(picture_102004_png, sizeof(picture_102004_png));
    手持图片[102005] = createTexture_ALL_FromMem(picture_102005_png, sizeof(picture_102005_png));
    手持图片[102007] = createTexture_ALL_FromMem(picture_102007_png, sizeof(picture_102007_png));
    手持图片[102105] = createTexture_ALL_FromMem(picture_102105_png, sizeof(picture_102105_png));
    手持图片[103001] = createTexture_ALL_FromMem(picture_103001_png, sizeof(picture_103001_png));
    手持图片[103002] = createTexture_ALL_FromMem(picture_103002_png, sizeof(picture_103002_png));
    手持图片[103003] = createTexture_ALL_FromMem(picture_103003_png, sizeof(picture_103003_png));
    手持图片[103004] = createTexture_ALL_FromMem(picture_103004_png, sizeof(picture_103004_png));
    手持图片[103005] = createTexture_ALL_FromMem(picture_103005_png, sizeof(picture_103005_png));
    手持图片[103006] = createTexture_ALL_FromMem(picture_103006_png, sizeof(picture_103006_png));
    手持图片[103007] = createTexture_ALL_FromMem(picture_103007_png, sizeof(picture_103007_png));
    手持图片[103008] = createTexture_ALL_FromMem(picture_103008_png, sizeof(picture_103008_png));
    手持图片[103009] = createTexture_ALL_FromMem(picture_103009_png, sizeof(picture_103009_png));
    手持图片[103010] = createTexture_ALL_FromMem(picture_103010_png, sizeof(picture_103010_png));
    手持图片[103011] = createTexture_ALL_FromMem(picture_103011_png, sizeof(picture_103011_png));
    手持图片[103012] = createTexture_ALL_FromMem(picture_103012_png, sizeof(picture_103012_png));
    手持图片[103013] = createTexture_ALL_FromMem(picture_103013_png, sizeof(picture_103013_png));
    手持图片[103014] = createTexture_ALL_FromMem(picture_103014_png, sizeof(picture_103014_png));
    手持图片[103015] = createTexture_ALL_FromMem(picture_103015_png, sizeof(picture_103015_png));
    手持图片[103100] = createTexture_ALL_FromMem(picture_103100_png, sizeof(picture_103100_png));
    手持图片[103901] = createTexture_ALL_FromMem(picture_103901_png, sizeof(picture_103901_png));
    手持图片[103902] = createTexture_ALL_FromMem(picture_103902_png, sizeof(picture_103902_png));
    手持图片[103903] = createTexture_ALL_FromMem(picture_103903_png, sizeof(picture_103903_png));
    手持图片[104001] = createTexture_ALL_FromMem(picture_104001_png, sizeof(picture_104001_png));
    手持图片[104002] = createTexture_ALL_FromMem(picture_104002_png, sizeof(picture_104002_png));
    手持图片[104003] = createTexture_ALL_FromMem(picture_104003_png, sizeof(picture_104003_png));
    手持图片[104004] = createTexture_ALL_FromMem(picture_104004_png, sizeof(picture_104004_png));
    手持图片[104100] = createTexture_ALL_FromMem(picture_104100_png, sizeof(picture_104100_png));
    手持图片[105001] = createTexture_ALL_FromMem(picture_105001_png, sizeof(picture_105001_png));
    手持图片[105002] = createTexture_ALL_FromMem(picture_105002_png, sizeof(picture_105002_png));
    手持图片[105010] = createTexture_ALL_FromMem(picture_105010_png, sizeof(picture_105010_png));
    手持图片[106001] = createTexture_ALL_FromMem(picture_106001_png, sizeof(picture_106001_png));
    手持图片[106002] = createTexture_ALL_FromMem(picture_106002_png, sizeof(picture_106002_png));
    手持图片[106003] = createTexture_ALL_FromMem(picture_106003_png, sizeof(picture_106003_png));
    手持图片[106004] = createTexture_ALL_FromMem(picture_106004_png, sizeof(picture_106004_png));
    手持图片[106005] = createTexture_ALL_FromMem(picture_106005_png, sizeof(picture_106005_png));
    手持图片[106006] = createTexture_ALL_FromMem(picture_106006_png, sizeof(picture_106006_png));
    手持图片[106007] = createTexture_ALL_FromMem(picture_106007_png, sizeof(picture_106007_png));
    手持图片[106008] = createTexture_ALL_FromMem(picture_106008_png, sizeof(picture_106008_png));
    手持图片[106010] = createTexture_ALL_FromMem(picture_106010_png, sizeof(picture_106010_png));
    手持图片[107001] = createTexture_ALL_FromMem(picture_107001_png, sizeof(picture_107001_png));
    手持图片[107007] = createTexture_ALL_FromMem(picture_107007_png, sizeof(picture_107007_png));
    手持图片[108001] = createTexture_ALL_FromMem(picture_108001_png, sizeof(picture_108001_png));
    手持图片[108002] = createTexture_ALL_FromMem(picture_108002_png, sizeof(picture_108002_png));
    手持图片[108003] = createTexture_ALL_FromMem(picture_108003_png, sizeof(picture_108003_png));
    手持图片[108004] = createTexture_ALL_FromMem(picture_108004_png, sizeof(picture_108004_png));
    手持图片[602001] = createTexture_ALL_FromMem(picture_602001_png, sizeof(picture_602001_png));
    手持图片[602002] = createTexture_ALL_FromMem(picture_602002_png, sizeof(picture_602002_png));
    手持图片[602003] = createTexture_ALL_FromMem(picture_602003_png, sizeof(picture_602003_png));
    手持图片[602004] = createTexture_ALL_FromMem(picture_602004_png, sizeof(picture_602004_png));
}

#endif