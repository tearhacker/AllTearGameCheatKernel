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
#ifndef 结构体_H
#define 结构体_H

#include <cstring>
#include <iostream>
using namespace std;

class FRotator {
   public:
    FRotator()
        : Pitch(0.f), Yaw(0.f), Roll(0.f) {
    }
    FRotator(float _Pitch, float _Yaw, float _Roll)
        : Pitch(_Pitch), Yaw(_Yaw), Roll(_Roll) {
    }
    ~FRotator() {
    }
    float Pitch;
    float Yaw;
    float Roll;
    inline FRotator Clamp() {
        if (Pitch > 180) {
            Pitch -= 360;
        } else {
            if (Pitch < -180) {
                Pitch += 360;
            }
        }
        if (Yaw > 180) {
            Yaw -= 360;
        } else {
            if (Yaw < -180) {
                Yaw += 360;
            }
        }
        if (Pitch > 89) {
            Pitch = 89;
        }
        if (Pitch < -89) {
            Pitch = -89;
        }
        while (Yaw < 180) {
            Yaw += 360;
        }
        while (Yaw > 180) {
            Yaw -= 360;
        }
        Roll = 0;
        return FRotator(Pitch, Yaw, Roll);
    }
    inline float Length() {
        return sqrtf(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
    }
    FRotator operator+(FRotator v) {
        return FRotator(Pitch + v.Pitch, Yaw + v.Yaw, Roll + v.Roll);
    }
    FRotator operator-(FRotator v) {
        return FRotator(Pitch - v.Pitch, Yaw - v.Yaw, Roll - v.Roll);
    }
};

struct 开关 {
    bool 绘制;
    bool hide_process;
    bool 方框;
    bool 射线;
    bool 名字;
    bool 距离;
    bool 视角追踪;
    bool 忽略人机;
    bool 血量;
    int 血条绘图 = 0;
    bool 人数;
    bool 调试;
    bool 骨骼;
    bool 手持;
    int 手持绘图 = 0;
    bool 车辆;
    bool 载具血量;
    bool 载具油量;
    bool 盒子;
    bool 空投;
    bool 手雷预警;
    bool 被瞄预警;
    bool 背敌预警;
    bool 雷达;
    bool 人物加速;
    bool 隐藏方框背景;

    bool Debug;
    int Debug模式 = 0;

    bool 物资总开关;
    bool 其他物资;
    bool 显示步枪;
    bool 冲锋枪械;
    bool 狙击枪械;
    bool 散弹枪械;
    bool 显示子弹;
    bool 显示556子弹;
    bool 显示762子弹;
    bool 显示9mm子弹;
    bool 显示45mm子弹;
    bool 显示霰弹;
    bool 显示信号弹;
    bool 显示箭矢;
    bool 显示倍镜;
    bool 信号枪;
    bool 绘制召回;
    bool 显示扩容;
    bool 显示配件;
    bool 显示子弹袋;
    bool 显示箭袋;
    bool 显示激光瞄准器;
    bool 显示轻型握把;
    bool 显示半截握把;
    bool 显示UZI枪托;
    bool 显示狙击枪托;
    bool 显示步枪枪托;
    bool 显示狙击枪补偿器;
    bool 显示狙击枪消焰器;
    bool 显示狙击枪消音器;
    bool 显示步枪消音器;
    bool 显示步枪补偿器;
    bool 显示步枪消焰器;
    bool 显示冲锋枪消音器;
    bool 显示冲锋枪消焰器;
    bool 显示拇指握把;
    bool 显示垂直握把;
    bool 显示直角握把;
    bool 显示撞火枪托;
    bool 显示霰弹快速;
    bool 显示鸭嘴枪口;
    bool 显示霰弹收束;
    bool 显示药品;
    bool 显示医疗箱;
    bool 显示急救包;
    bool 显示绷带;
    bool 显示可乐;
    bool 显示肾上腺素;
    bool 显示止痛药;
    bool 显示防具;
    bool 显示三级头;
    bool 显示三级甲;
    bool 显示三级包;
    bool 投掷物品;
    bool 超级物资箱;
    bool 爆炸猎弓;

    bool 绘制信号枪;
    bool 绘制金插;
    bool 绘制宝箱;
    bool 绘制药箱;
    bool 绘制武器箱;
    bool 头甲包显示;  // 耐久
    bool 盒子物资;
    bool 背包容量;
    bool 头甲包显示2;
    bool 隐藏已开启;

    float 速度值 = 1.15;
    float 雷达X = 300;
    float 雷达Y = 400;
    float rotationAngle = 0.0f;

    float 方框粗细 = 1.0f;
    float 射线粗细 = 0.1f;
    float 骨骼粗细 = 2.0f;

    float 第一人称 = 125;
    float 第三人称 = 100;
    float 开镜广角 = 10;

    // float 追踪概率 = 35.0;

    bool 自瞄选项;

    int 帧率选项 = 90;
    unsigned int 当前帧率 = 90;

    int VehicleID;

    float 测试数值 = 0.0f;
};

struct 地址 {
    uintptr_t libdi;
    uintptr_t libue4;
    uintptr_t 世界地址;
    uintptr_t 类地址;
    uintptr_t 解密地址;
    uintptr_t 自身地址;
    uintptr_t 矩阵地址;
    uintptr_t 矩阵地址_Tol;
    uintptr_t 数组地址;
};

struct FMatrix {
    float M[4][4];
};

struct D2DVector {
    float X;
    float Y;
    D2DVector() {
        this->X = 0;
        this->Y = 0;
    }
    D2DVector(float x, float y) {
        this->X = x;
        this->Y = y;
    }
};

struct D3DVector {
    float X;
    float Y;
    float Z;
    D3DVector() {
        this->X = 0;
        this->Y = 0;
        this->Z = 0;
    }
    D3DVector(float x, float y, float z) {
        this->X = x;
        this->Y = y;
        this->Z = z;
    }
};

struct D4DVector {
    float X;
    float Y;
    float Z;
    float W;
    D4DVector() {
        this->X = 0;
        this->Y = 0;
        this->Z = 0;
        this->W = 0;
    }
    D4DVector(float x, float y, float z, float w) {
        this->X = x;
        this->Y = y;
        this->Z = z;
        this->W = w;
    }
};

struct 自瞄信息 {
    D3DVector 瞄准坐标;
    D3DVector 人物向量;
    float 准心距离 = 10000;
    float 距离 = 10000;
    D2DVector 对象骨骼;
    long int Bone;
    long int Human;
    int 血量;
    string 名字;
    float 头;
    float 甲;
    int 阵营;
    long 头甲包地址;
    D3DVector 骨骼坐标[17];
};

struct 瞄准信息 {
    float 距离;
    string 名字;
    string 瞄准武器;
};

struct FTransform {
    D4DVector Rotation;
    D3DVector Translation;
    float chunk;
    D3DVector Scale3D;
};

struct 备份 {
    float 自瞄速度 = 0.f;  //&绘制.自瞄.自瞄速度
    float 压枪力度 = 0.f;  //&绘制.自瞄.压枪力度
    float mk20压枪 = 0.f;  //&绘制.mk20
};

struct 自瞄 {
    bool 初始化;
    bool 触摸位置;
    bool 动态自瞄;
    bool 准星射线;
    bool 倒地不瞄;
    bool 掉血自瞄;
    bool 自瞄控件;
    bool 喷子自瞄;
    bool 狙击自瞄;
    bool 人机不瞄;
    bool 框内自瞄;
    bool 软锁自瞄;
    bool 隐藏自瞄圈;
    bool 随机触摸点;

    int 自瞄条件 = 0;
    int 充电口方向 = 0;
    int 瞄准优先 = 0;
    int 瞄准部位 = 0;
    int 喷子自瞄条件 = 0;
    float 自瞄范围 = 150.0f;
    float 动态范围 = 200.0f;
    float 触摸范围 = 200.0f;
    float 压枪力度 = 2.15f;
    float 三倍压枪 = 0.f;
    float 自瞄速度 = 20.f;
    float 预判力度 = 1.45f;
    float 扫车预判 = 0.f;

    int 瞄准目标;
    float 触摸范围X = 1500.0f;
    float 触摸范围Y = 650.0f;

    int 瞄准对象数量 = 0;
    int 瞄准总数量 = 0;

    float 掉血自瞄数率 = 8.0f;

    float 喷子距离限制 = 5.0f;
    float 趴下位置调节 = 1.0f;
    float 触摸采样率 = 800;

    float 腰射距离限制 = 25.0f;
    float 自瞄距离限制 = 300.0f;
};

struct 骨骼数据 {
    D2DVector Head;            // 头部
    D2DVector Chest;           // 胸部
    D2DVector Pelvis;          // 盆骨
    D2DVector Left_Shoulder;   // 左肩膀
    D2DVector Right_Shoulder;  // 右肩膀
    D2DVector Left_Elbow;      // 左手肘
    D2DVector Right_Elbow;     // 右手肘
    D2DVector Left_Wrist;      // 左手腕
    D2DVector Right_Wrist;     // 右手腕
    D2DVector Left_Thigh;      // 左大腿
    D2DVector Right_Thigh;     // 右大腿
    D2DVector Left_Knee;       // 左膝盖
    D2DVector Right_Knee;      // 右膝盖
    D2DVector Left_Ankle;      // 左脚腕
    D2DVector Right_Ankle;     // 右脚腕
};

struct 自身数据 {
    D3DVector 坐标;
    D2DVector 准星;
    D3DVector 视角;
    float 矩阵[16];
    int 自身队伍;
    int 自身状态;
    int 开火;
    int 开镜;
    int 手持;
    int 手持id;
    int 手持握把;
    float Fov;
    float 子弹速度;
    uintptr_t 驱动自瞄地址;
    float 后坐力数据;
    float 准星Y;
    float 相机朝向;
    float 人物高度;

    float 头;
    float 甲;
};

// 地址结构体
struct 对象地址 {
    long 敌人地址;
    long 物品地址[1000];
    long 车辆地址[50];
};

struct 敌人信息 {
    D3DVector 坐标;
    D3DVector 真实坐标;
    D3DVector 向量;
    D3DVector 骨骼坐标[17];
    D2DVector 雷达;
    bool isboot;
    int 队伍;
    int 状态;
    int 距离;
    int 手持;
    float 当前血量;
    float 最大血量;
    bool 乘坐载具;
    string 名字;
    float Rotator;
    float 头;
    float 甲;
    long 头甲包地址;
    int 子弹数量, 子弹最大数量;
};
struct 物品信息 {
    D3DVector 坐标;
    int 物品;
    int 距离;
};

struct 车辆信息 {
    D3DVector 坐标;
    int 车辆;
    int 距离;
};

// 数据结构体
struct 对象信息 {
    int isCanRead;
    int 敌人数量;
    int 物品数量;
    int 车辆数量;
    敌人信息 敌人信息;
    物品信息 物品信息[1000];
    车辆信息 车辆信息[50];
};

struct D3DXMATRIX {
    float _11;
    float _12;
    float _13;
    float _14;
    float _21;
    float _22;
    float _23;
    float _24;
    float _31;
    float _32;
    float _33;
    float _34;
    float _41;
    float _42;
    float _43;
    float _44;
};

struct D3DXVECTOR4 {
    float X;
    float Y;
    float Z;
    float W;
};

struct FTransform1 {
    D3DXVECTOR4 Rotation;
    D3DVector Translation;
    D3DVector Scale3D;
};

#endif
