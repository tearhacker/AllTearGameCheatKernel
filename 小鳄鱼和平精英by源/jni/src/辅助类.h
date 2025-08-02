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
#ifndef 辅助类_H
#define 辅助类_H

#include <iostream>
#include <pthread.h>
#include <dirent.h>
#include <regex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <map>
#include <cstdio>
#include <stdio.h>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <dirent.h>
#include <regex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <map>
#include <cstdio>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <regex>

#include "./CPUaffinity/timer.h"
#include "obfuscate.h"

#define PI 3.141592653589793238


class Kernel {
private:
	int has_upper = 0;
	int has_lower = 0;
	int has_symbol = 0;
	int has_digit = 0;
	int fd;
	pid_t pid;

	typedef struct _COPY_MEMORY {
		pid_t pid;
		uintptr_t addr;
		void* buffer;
		size_t size;
	} COPY_MEMORY, *PCOPY_MEMORY;

	typedef struct _MODULE_BASE {
		pid_t pid;
		char* name;
		uintptr_t base;
	} MODULE_BASE, *PMODULE_BASE;

	enum OPERATIONS {
		OP_INIT_KEY = 0x800,
		OP_READ_MEM = 0x801,
		OP_WRITE_MEM = 0x802,
		OP_MODULE_BASE = 0x803,
	};

    

public:
    int get_dev();
    Kernel();
    ~Kernel();
    void 初始化读写(int pid);
    bool readv(uintptr_t addr, void *buffer, size_t size);
    bool writev(uintptr_t addr, void *buffer, size_t size);
    template<typename T>
    T Read(uintptr_t address);
    uintptr_t get_module_base(char* name);
    uintptr_t getPtr64(uintptr_t addr);
    uintptr_t getPtr32(uintptr_t addr);
    float getFloat(uintptr_t addr);
    int getDword(uintptr_t addr);
    int WriteDword(long int addr, int value);
    float WriteFloat(long int addr, float value);
    void writefloat(unsigned long addr,float data);
    void writeptr(unsigned long addr, uintptr_t data);
    void writedword(unsigned long addr, int data);
    int getPID(const char* packageName);
    void getUTF8(char * buf, unsigned long namepy);
    bool init_key(char* key);
    char *driver_path();
    int symbol_file(const char *filename);
    char getByte(unsigned long addr);
   
};


#include "Draw.h"
#include "imgui_impl_opengl3.h"
#include "结构体.h"
#include "骨骼.hpp"

class StringFloatMap
{
private:
    map<string, vector<float>> data;

public:
    void add(string key, float value1, float value2)
    {
        vector<float> values;
        values.push_back(value1);
        values.push_back(value2);
        data[key] = values;
    }

    void remove(string key)
    {
        data.erase(key);
    }

    bool exists(string key)
    {
        return data.find(key) != data.end();
    }

    string calculateKey(float 坐标X, float 坐标Y)
    {
        int maps = 999;
        string 键名;
        for (const auto &pair : data)
        {
            const vector<float> &values = pair.second;
            int result = (int)sqrt(pow(坐标X - values[0], 2) + pow(坐标Y - values[1], 2)) * 0.01;
            // printf("测试值:%f \n",result);
            if (result < maps)
            {
                // return pair.first;
                maps = result;
                键名 = pair.first;
                // break;
            }
        }
        if (maps < 20)
        {
            return 键名;
        }
        return ""; // 如果没有满足条件的键名，则返回空字符串
    }
};

class Timer
{
private:
    std::map<std::string, int> timers;

public:
    void addTimer(const std::string &name, int seconds)
    {
        if (timers.find(name) == timers.end())
        {
            timers[name] = seconds;
        }
    }

    void updateTimers()
    {
        for (auto &timer : timers)
        {
            timer.second++;
        }
    }

    void checkAndRemoveTimers()
    {
        for (auto it = timers.begin(); it != timers.end();)
        {
            if (it->second == 1500)
            {
                it = timers.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    int getTimerSeconds(const std::string &name)
    {
        auto it = timers.find(name);
        if (it != timers.end())
        {
            return it->second;
        }
        return -1;
    }

    void removeTimer(const std::string &name)
    {
        timers.erase(name);
    }

    bool hasTimer(const std::string &name)
    { // 判断是否存在
        return timers.find(name) != timers.end();
    }

    void renameTimer(const std::string &oldName, const std::string &newName)
    {
        if (timers.find(oldName) != timers.end())
        {
            timers[newName] = timers[oldName];
            timers.erase(oldName);
        }
    }
};

class 计算
{
public:
    int 计算距离(D3DVector 自身坐标, D3DVector 对方坐标);
    D4DVector 计算屏幕坐标(float 矩阵[16], D3DVector 人物坐标, float px, float py);
    D2DVector 计算屏幕坐标2(float 矩阵[16], D3DVector 人物坐标, float px, float py);
    float 计算屏幕距离(D2DVector &坐标, float px, float py);
    骨骼数据 计算骨骼(float (&矩阵)[16], D3DVector (&骨骼)[17], float px, float py);
    D2DVector rotateCoord(float angle, float objRadar_x, float objRadar_y);
    D2DVector rotateCoord(D3DVector Enemy, D3DVector RealPerson);
};
// 绘图
class 绘图
{
    struct 颜色
    {
        ImColor 红色 = ImColor(255, 0, 0, 255);
        ImColor 白色 = ImColor(255, 255, 255, 255);
        ImColor 蓝色 = ImColor(0, 0, 255, 255);
        ImColor 绿色 = ImColor(0, 255, 0, 255);
        ImColor 黄色 = ImColor(255, 255, 0, 255);
        ImColor 黑色 = ImColor(0, 0, 0, 255);
    };

public:
    struct VecTor2
    {
        float x;
        float y;
        VecTor2()
        {
            this->x = 0;
            this->y = 0;
        }
        VecTor2(float x, float y)
        {
            this->x = x;
            this->y = y;
        }
        bool operator!=(const VecTor2 &Pos)
        {
            if (this->x != Pos.x || this->y != Pos.y)
            {
                return true;
            }
            return false;
        }
        VecTor2 operator+(float v) const
        {
            return VecTor2(x + v, y + v);
        }
        VecTor2 operator-(float v) const
        {
            return VecTor2(x - v, y - v);
        }
        VecTor2 operator*(float v) const
        {
            return VecTor2(x * v, y * v);
        }
        VecTor2 operator/(float v) const
        {
            return VecTor2(x / v, y / v);
        }
        VecTor2 &operator+=(float v)
        {
            x += v;
            y += v;
            return *this;
        }
        VecTor2 &operator-=(float v)
        {
            x -= v;
            y -= v;
            return *this;
        }
        VecTor2 &operator*=(float v)
        {
            x *= v;
            y *= v;
            return *this;
        }
        VecTor2 &operator/=(float v)
        {
            x /= v;
            y /= v;
            return *this;
        }
        VecTor2 operator+(const VecTor2 &v) const
        {
            return VecTor2(x + v.x, y + v.y);
        }
        VecTor2 operator-(const VecTor2 &v) const
        {
            return VecTor2(x - v.x, y - v.y);
        }
        VecTor2 operator*(const VecTor2 &v) const
        {
            return VecTor2(x * v.x, y * v.y);
        }
        VecTor2 operator/(const VecTor2 &v) const
        {
            return VecTor2(x / v.x, y / v.y);
        }
        VecTor2 &operator+=(const VecTor2 &v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }
        VecTor2 &operator-=(const VecTor2 &v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        VecTor2 &operator*=(const VecTor2 &v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }
        VecTor2 &operator/=(const VecTor2 &v)
        {
            x /= v.x;
            y /= v.y;
            return *this;
        }
    };
    struct VecTor3
    {
        float x;
        float y;
        float z;
        VecTor3()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
        }
        VecTor3(float x, float y, float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        bool operator!=(const VecTor3 &Pos)
        {
            if (this->x != Pos.x || this->y != Pos.y || this->z != Pos.z)
            {
                return true;
            }
            return false;
        }
        VecTor3 operator+(float v) const
        {
            return VecTor3(x + v, y + v, z + v);
        }
        VecTor3 operator-(float v) const
        {
            return VecTor3(x - v, y - v, z - v);
        }
        VecTor3 operator*(float v) const
        {
            return VecTor3(x * v, y * v, z * v);
        }
        VecTor3 operator/(float v) const
        {
            return VecTor3(x / v, y / v, z / v);
        }
        VecTor3 &operator+=(float v)
        {
            x += v;
            y += v;
            z += v;
            return *this;
        }
        VecTor3 &operator-=(float v)
        {
            x -= v;
            y -= v;
            z -= v;
            return *this;
        }
        VecTor3 &operator*=(float v)
        {
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }
        VecTor3 &operator/=(float v)
        {
            x /= v;
            y /= v;
            z /= v;
            return *this;
        }
        VecTor3 operator+(const VecTor3 &v) const
        {
            return VecTor3(x + v.x, y + v.y, z + v.z);
        }
        VecTor3 operator-(const VecTor3 &v) const
        {
            return VecTor3(x - v.x, y - v.y, z - v.z);
        }
        VecTor3 operator*(const VecTor3 &v) const
        {
            return VecTor3(x * v.x, y * v.y, z * v.z);
        }
        VecTor3 operator/(const VecTor3 &v) const
        {
            return VecTor3(x / v.x, y / v.y, z / v.z);
        }
        VecTor3 &operator+=(const VecTor3 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        VecTor3 &operator-=(const VecTor3 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        VecTor3 &operator*=(const VecTor3 &v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }
        VecTor3 &operator/=(const VecTor3 &v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }
    };

    struct VecTor4
    {
        float x;
        float y;
        float z;
        float w;
        VecTor4()
        {
            this->x = 0;
            this->y = 0;
            this->z = 0;
            this->w = 0;
        }
        VecTor4(float x, float y, float z, float w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
        bool operator!=(const VecTor4 &Pos)
        {
            if (this->x != Pos.x || this->y != Pos.y || this->z != Pos.z || this->w != Pos.w)
            {
                return true;
            }
            return false;
        }
        VecTor4 operator+(float v) const
        {
            return VecTor4(x + v, y + v, z + v, w + v);
        }
        VecTor4 operator-(float v) const
        {
            return VecTor4(x - v, y - v, z - v, w - v);
        }
        VecTor4 operator*(float v) const
        {
            return VecTor4(x * v, y * v, z * v, w * v);
        }
        VecTor4 operator/(float v) const
        {
            return VecTor4(x / v, y / v, z / v, w / v);
        }
        VecTor4 &operator+=(float v)
        {
            x += v;
            y += v;
            z += v;
            w += v;
            return *this;
        }
        VecTor4 &operator-=(float v)
        {
            x -= v;
            y -= v;
            z -= v;
            w -= v;
            return *this;
        }
        VecTor4 &operator*=(float v)
        {
            x *= v;
            y *= v;
            z *= v;
            w *= v;
            return *this;
        }
        VecTor4 &operator/=(float v)
        {
            x /= v;
            y /= v;
            z /= v;
            w /= v;
            return *this;
        }
        VecTor4 operator+(const VecTor4 &v) const
        {
            return VecTor4(x + v.x, y + v.y, z + v.z, w + v.w);
        }
        VecTor4 operator-(const VecTor4 &v) const
        {
            return VecTor4(x - v.x, y - v.y, z - v.z, w - v.w);
        }
        VecTor4 operator*(const VecTor4 &v) const
        {
            return VecTor4(x * v.x, y * v.y, z * v.z, w * v.w);
        }
        VecTor4 operator/(const VecTor4 &v) const
        {
            return VecTor4(x / v.x, y / v.y, z / v.z, w / v.w);
        }
        VecTor4 &operator+=(const VecTor4 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }
        VecTor4 &operator-=(const VecTor4 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }
        VecTor4 &operator*=(const VecTor4 &v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            w *= v.w;
            return *this;
        }
        VecTor4 &operator/=(const VecTor4 &v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            w /= v.w;
            return *this;
        }
    };

    颜色 颜色; // 颜色的类
    float PX, PY;
    float MIDDLE, BOTTOM, TOP;
    float left, right, top, top1, bottom;
    bool isAiming;
    void 初始化绘图(int X, int Y);
    void 初始化坐标(D4DVector &屏幕坐标, 骨骼数据 &骨骼);
    void 绘制方框(bool isboot);
    	void 绘制漏手(bool isboot);

    void 绘制预瞄点(bool isboot);
    
    void 绘制人数(int 人机, int 真人);
    void 绘制距离(int 距离, int 队伍);
    void 绘制射线(骨骼数据 &骨骼);
    void 绘制血量(float 最大血量, float 当前血量, bool isbot);
    void 绘制名字(string 名字, bool isboot, float 计时, bool 是否掐雷, char *类名, int 阵营, int Bonecount);
    void 绘制骨骼(骨骼数据 &骨骼, D4DVector &屏幕坐标, bool LineOfSightTo, float 距离);
    void 绘制手持(int 手持, int 状态, int 子弹, int 最大子弹);
    void 绘制车辆(D4DVector 屏幕坐标, int 距离, int CarrierID);
    void 绘制自瞄触摸范围(float 触摸范围, float 触摸范围X, float 触摸范围Y);
    void 绘制加粗文本(float size, float x, float y, ImColor color, ImColor color1, const char *str);
    void 绘制字体描边(float size, int x, int y, ImVec4 color, const char *str);
    void RenderRadarScan(ImDrawList *draw_list, ImVec2 center, float radius, int numSegments, float &rotationAngle, float lineLength);
    void 绘制瞄准信息();

    bool WorldTurnScreen(VecTor2 &Screen, VecTor3 World, float Matrix[]);

    void ExplosionRange(D3DVector Obj, ImColor color, float Range, float thickn, float Matrix[]);

    void Parabola(VecTor3 obj, float Matrix[]);
};
// 绘制
class 绘制
{

    struct ColorTable
    {
        float 方框颜色[4] = {1.0, 1.0, 1.0, 1.0};
        float 射线颜色[4] = {1.0, 1.0, 1.0, 1.0};
        float 骨骼颜色[4] = {1.0, 1.0, 1.0, 1.0};
        float 血量颜色[4] = {1.0, 0.0, 0.0, 1.0};
        float 距离颜色[4] = {1.0, 1.0, 1.0, 1.0};
        float 名称颜色[4] = {1.0, 1.0, 1.0, 1.0};
    };
    struct map_node
    {
        long int start_addr;   // 起始地址
        long int end_addr;     // 结束地址
        struct map_node *next; // 下一个节点
    };

    struct 压枪
    {
        float m416;
        float scar_l;
        float aug;
        float famas;
        float g36c;
        float m249;
        float akm;
        float m762;
        float 蜜獾;
        float pkm;
        float mg3;
        float mg_36;
        float p90;
        float uzi;
        float ump45;
        float vector;
        float 汤姆逊;
        float 野牛;
        float mini14;
        float sks;
        float m417;
        float mk20_h;
        float mk12;
        float vss;
        float 扫车 = 1.2f;
    };

public:
    float mk20, m417 = 1.0f;
    float 轻型压枪力度 = 1.f;
    float 拇指压枪力度 = 0.2f;
    float 垂直压枪力度 = 0.2f;
    float 直角压枪力度 = 0.2f;
    int 世界数量;
    float 骨骼距离限制 = 300;
    int 漏打模式, 防录屏, 自瞄模式, 无后台开关, 控制延迟;
    char 卡密[250];
    bool 漏打开关;
    bool Winorlose = false;
    ImVec2 Pos;
    int winWidth = 684;
    int winHeith = 896;

    bool 是否开启自瞄页面 = false;

    压枪 压枪力;
    压枪 预判度;
    float 握把[100];

    uintptr_t 解密数组;
    long int 解密模式 = 0x4000;

    int 被瞄准对象数量 = 0;

    FILE *numSave = nullptr;

    char 悬浮窗标题[200];

    ColorTable Colorset[2]; // 颜色配置
    int pid;
    bool 线程 = 0; // 用于判断更新数据显示是否加载
    float PX, PY;  // 绘制用的分辨率
    float 真实PX, 真实PY;
    bool Validate;
    Kernel 读写; // 创建读写结构体

    float 物资颜色[4] = {0.0, 1.0, 0.0, 1.0};
    float 车辆颜色[4] = {0.0, 1.0, 0.0, 1.0};
    float 手持颜色[4] = {1.0, 1.0, 1.0, 1.0};

    StringFloatMap 手雷类;
    Timer 计时器; // 计时器

    bool Shelter[14];

    地址 地址;
    开关 按钮;
    计算 计算;
    骨骼 *骨骼;
    绘图 绘图;
    自瞄 自瞄;
    备份 备份;
    std::mutex mtx;
    自瞄信息 自瞄函数[100];
    瞄准信息 被瞄信息[100];
    自身数据 自身数据; // 创建自身数据结构体
    对象地址 对象地址; // 创建对象地址结构体
    对象信息 对象信息; // 创建敌人信息结构体数组
    void 初始化绘制(string 包名, int 真实X, int 真实Y);
    void 自瞄主线程();
    void 驱动自瞄主线程();
    int findminat();
    void 更新地址数据();
    void 多线程更新地址();
    void 更新对象地址();
    void 更新对象数据();
    void 绘制载具信息();
    void 运行绘制();
    ImColor floatArrToImColor(float arr[4]);
    void hide_process();
    string getBoxName(int id);
    void OffScreen(ImDrawList *ImDraw, D4DVector Obj, float camear, ImU32 color, float Radius, float 距离);
    void GetTouch();
    void 保存配置();
    void 读取配置();
    bool 自瞄触发(float 距离);
    const char *getMaterialName(char *name);
    int Cloudcheck();
    const char *Level(char *name);
    int Acquisitionsite();
    D3DVector Missedtyping();
    void 掩体线程();
    void InitShoot();

    void InitMaps();
    void print_maps(struct map_node *head);
    void free_maps(struct map_node *head);
    void readmaps_v(struct map_node **head);
};

class 布局
{
public:
    // 布局UI
    void 开启悬浮窗();
    void 绘制悬浮窗();
    int 初始化程序();
};

#endif
