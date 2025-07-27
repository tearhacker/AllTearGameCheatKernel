#include <string>
#include <iostream>
#include <string.h>
#include <cstdio>
#include <malloc.h>
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <sys/system_properties.h>
void DrawLogogirl(ImVec2 center, float size);
void ImGuiLayout1();
void ImGuiLayout2();
void ImGuiLayout3();
void ImGuiLayout4();
void lay5();
int MenuTab = 1;



ImGuiWindow *Window = nullptr;

bool IsLoGin = true, IsDown = false, IsWin = true;
ImVec2 ImagePos = {0, 0};

 

//王者触摸功能支持
int 自身视野;
int 屏幕x=1120;
int 屏幕y=440;
static bool showSubWindow = true;
ImVec2 召唤师技能触发坐标(1626,966);
ImVec2 技能自瞄触发坐标(1790,740);
bool 显示设置技能坐标=false;
int 设置坐标类型=0;




static bool 链接驱动;
int yxpx, yxpy, fenblxx = 0;
uintptr_t libbase;
long int libbase3;
long int libbase2;
    //#include "IsCharacter.h"
#define BYTE4 0x00000004
#define BYTE8 0x00000008
#define BYTE16 0x00000010
#define BYTE10 0x000000A
#define BYTE64 0x00000040
#define BYTE1024 0x00000400
uintptr_t unity;
uintptr_t unitybss;
uintptr_t GameCore;
uintptr_t GameCorebss;
uintptr_t il2cpp;
uintptr_t il2cppbss;
static uint64_t lil2cpp_base = 0;
static uint64_t libGame_base = 0;
static uint64_t libunity_base = 0;
static uint64_t lil2cpp_basebss = 0;
static uint64_t libGame_basebss = 0;
static uint64_t libunity_basebss = 0;
static uint64_t libtersafe_base = 0;
uint64_t MatrixAddress = 0;//初始化矩阵地址
float isGames;//储存矩阵的值
int foeComp;//敌方阵营
int rientation = 0;//对局方向
int AroundNumbers = 0;//人头数量

float hp1;
float aa;//计算和判断血量
float pos_y;//初始化裁剪坐标
float pos_x;
float myx, myy;//临时坐标
//绘制米数
char meter1[1000];
float meter;
//实时获取裁剪坐标
float my_pos_y;
float my_pos_x;
int 视野;
int huitu=0;//绘图启动
//人物绘制
 bool 血量 = false;
 bool 地图 = false;
// bool 特权 = false;
 bool 方框 = false;
 bool 自瞄 = false;
 bool 射线 = false;
 bool 距离 = false;
 bool 野怪 = false;
 bool 兵线 = false;
 bool 方框技能 = false;
 bool 顶上技能 = false;
 bool 上帝 = false;
 bool 眼位 = false;
 bool 龙触摸 = false;
 bool buff触摸 = false;
 bool 野血 = false;
 bool 框技 = false;
 bool 回城 = false;
 bool 自身判断 = false;
 bool 框头 = false;
 bool 技陷 = false;
 bool 斩杀 = false;
 bool 惩戒 = false;
bool 兵血 = false;
 /*地图参数调试
 地图小地图
 小地图参数*/
 int touxiangdaxiao = 0;//头像大小
int xiaodituxue = 3;//小地图血量大小 k60那个血圈大小
int jiange = -37;//小地图间隔
int SmallMapX = 33;
int SmallMapY = 7; //小地图头像位置
int monsterX=33;
int monsterY=7;
int SmallHPX = 9;
int SmallHPY = 34; //小地图血条位置
int dingshanghealth=21;

int BuffMapX = 0; //buff
 int BuffMapY = 0;
 int SmallSoldiX = 0; //兵线
 int SmallSoldiY = 0;
 int jinenglanz = 0;//技能栏左右
 int jinenglanzX = 0;//技能栏左右
 int jinenglanzY = 0;//技能栏左右
 /*开始王者结构体定义
 结构体
 王者 
 最下面是结构体*/



//射线
enum LINE {
line1 = 0,
line2 = 1,
line3 = 2
};
static LINE LINE;
//方框
enum BOX {
box1 = 0,
box2 = 1,
box3 = 2
};
static BOX BOX;
//自瞄部位


 
struct 颜色数据 {
ImVec4 设计颜色;
};
颜色数据 颜色[100];
ImVec4 设计颜色[100];
int 拼接(int a,int b) {
int t=9;
while(t<b)t=t*10+9;
t=(t+1)*a+b;
return t;
}
ImVec4 随机(){
int 红;
int 绿;
int 蓝;
红=(rand()%255+0);
绿=(rand()%255+0);
蓝=(rand()%255+0);
if(sizeof(红)==1||sizeof(红)==0)
红=拼接(红,红);
if(sizeof(绿)==1||sizeof(绿)==0)
绿=拼接(绿,绿);
if(sizeof(蓝)==1||sizeof(蓝)==0)
蓝=拼接(蓝,蓝);
return {(float)红/255.0f,(float)绿/255.0f,(float)蓝/255.0f,174/255.0f};
}
void 颜色初始化(){
srand((unsigned)time(NULL)); /*随机数*/
for(int 数量=0;数量<100;数量++){
设计颜色[数量]=随机();
}
}
ImVec4 获取颜色(int 序号){
return 设计颜色[序号-1];
}
ImVec4 队伍颜色(int 队伍){
if(队伍<=100 && 队伍>0)
return 获取颜色(队伍);
else
return {0/255.f,255/255.f,0/255.f,50/255.f};
}









//glory struct  body   



//王者游戏结构chao

  

struct 总颜色
{
    ImColor 血量颜色 = ImColor(0, 255, 0, 255);//血量颜色
    ImColor 射线颜色 = ImColor(255, 255, 255, 255);
    ImColor 方框颜色 = ImColor(255, 255, 255, 255);
};

总颜色 颜色配置;
static struct Color1
{
    ImColor Red = { 255 / 255.f, 0 / 255.f, 0 / 255.f, 255 / 255.f };
    ImColor Red_ = { 255 / 255.f, 0 / 255.f, 0 / 255.f, 50 / 255.f };
    ImColor Green = { 0 / 255.f, 255 / 255.f, 0 / 255.f, 255 / 255.f };
    ImColor Green_ = { 0 / 255.f, 255 / 255.f, 0 / 255.f, 50 / 255.f };
    ImColor 白色 = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f };
    ImColor White_ = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 180.f / 255.f };
    ImColor Black = { 0 / 255.f, 0 / 255.f, 0 / 255.f, 255.f / 255.f };
    ImColor Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };

} Color1;

struct stu
{
    int id;
    int hp;
};

struct Coord {
    float X;//X轴
    float Y;//Y轴
    float W;
    float H;
};
struct DynamicData {
    struct Coord coord;//获取xy坐标
};

struct HeroTemp {
    struct Coord coord;//获取xy坐标
    int Hp;//当前血量
    int MaxHp;//最大血量
    int Id;//英雄id
    int Space;
    int Space1;//大招cd
    int Space2;
    int Space3;
    int Spaceid;
    int Skill;//召唤师技能cd
    int Skill2;//召唤师技能cd2
    int camp;//阵营id
    int HC;//回城
    int TB;//图标
    int TB1;
    int TB2;//图标
    int TB3;
    int TB4;
    int confound;//坐标混淆
};
/**
 * 获取野怪xy和刷新时间
 */
struct Pve {
    uint64_t X;//X坐标地址
    uint64_t Y;//Y坐标地址
    uint64_t cd;//刷新时间
    uint64_t cc;//刷新时间
    uint64_t id;
    uint64_t hp;
    uint64_t maxhp;
    uint64_t maxcd;
};
/**
 * 获取野怪xy和刷新时间
 */

struct PveTemp {
    struct Coord coord;//获取xy坐标
    int cd;//刷新时间
    int id;
    int hp;
    int maxhp;
    int maxcd;

};


/**
 * 获取兵线xy
 */
struct Pvc {
    uint64_t X;//X坐标地址
    uint64_t Y;//Y坐标地址
    uint64_t hp;
    uint64_t maxhp;
};
/**
 * 单个兵线
 */
struct CeTemp {
    struct Coord coord;//获取xy坐标
    int cd;
    int hp;
    int maxhp;
    int team;
};

typedef struct {
    float Matrix[BYTE16];//相机矩阵
    struct HeroTemp heroTemp[BYTE16];//储存单个英雄
    struct DynamicData DynamicData[BYTE16];//储存单个英雄大地图
    struct Pve pve[BYTE1024];//储存野怪
    struct PveTemp pveTemp[BYTE1024];//储存野怪
    struct CeTemp CeTemp[BYTE1024];//储存兵线
    struct Pvc pvc[BYTE1024];//储存兵线
    int xbsl;//小兵数量
} DataTable;


DataTable dataTable;//游戏数据表

const static ImColor Paint_touming = ImColor(254, 253, 252);  //透明
const static ImColor Paint_purple = ImColor(255, 0, 255);  //紫色
const static ImColor Paint_red = ImColor(255, 0, 0);       //红色
const static ImColor Paint_white = ImColor(255, 255, 255); //白色
const static ImColor Paint_lightblue = ImColor(0, 255, 255);   //浅蓝色
const static ImColor Paint_yellow = ImColor(255, 255, 0);  //黄色
const static ImColor Paint_green = ImColor(0, 255, 0);  //绿色

double Wwra = 0, Wwr2 = 0;    //转小地图算法


struct Coord bingxian_coord = { 0 };/*实际野怪坐标*/
struct Coord yg_coord = { 0 };/*实际野怪坐标*/
struct Coord map_coord = { 0 };/*实际地图坐标*/
struct Coord map_buff = { 0 };/*实际地图坐标*/
long int 兵线数组地址;
//王者数据开始补充 结构体
//王者数据开始补充
stu player[10];
int PlayerPosition[10][3];//自瞄的玩家坐标 一把游戏10人 坐标xyz
int hist[10][3];
int me = 0;
 
double Wwr = 1080 / 10.2f * 1.574074075;
char DrawPlayerCount[100];
 
int Health;
int PlayerId;
long int CameraAddress;

int SmallMapTeam;





//触摸相关距离
int getdistance(int xx1, int yy1, int xx2, int yy2)
{
	return sqrt(pow(yy2 - yy1, 2) + pow(xx2 - xx1, 2));
}

bool checkIncircle(float x, float y, float circlex, float circley, float r)
{
	float distance = getdistance(x, y, circlex, circley);
	return distance <= r;
}





//计算矩阵  王者
//王者矩阵计算
Coord CalMatrixMem(struct Coord coor, const float Matrix[]) {
    struct Coord points = { 0 };
    float XM = coor.X / 1000.0f;
    float ZM = coor.Y / 1000.0f;
    if (Matrix[11] && Matrix[15] && Matrix[0] && Matrix[12] && Matrix[9] && Matrix[13] && Matrix[1] && Matrix[5] && Matrix[9] && Matrix[13]) {
        float radio = (float)fabs(ZM * Matrix[11] + Matrix[15]);
        points.X = 0.0f, points.Y = 0.0f, points.W = 0.0f, points.H = 0.0f;
        if (radio > 0) {
            points.X = yxpx / 2 + (XM * Matrix[0] + Matrix[12]) / radio * yxpx / 2;
            points.Y = yxpy / 2 - (ZM * Matrix[9] + Matrix[13]) / radio * yxpy / 2;
            points.W = yxpy / 2 - (XM * Matrix[1] + 4.0f * Matrix[5] + ZM * Matrix[9] + Matrix[13]) / radio * yxpy / 2;
            points.H = ((points.Y - points.W) / 2.0f);
        }
        return points;
    }
}
//计算矩阵



//王者共享内容

//共享菜单全部   
int pxx = 0, pyy = 0; double WwrShare = 0.0;//临时分辨率
bool 初始化 = false;
bool Touchinit = true;
int Screen_X, Screen_Y;
int xytable[10][10];
int hist1[10][10];
int me1 = 0;
float ax, ay;
int prex1, prey1;
long a, objarrayaddr, libGameCore1, libil2cpp1, 兵线基址, 人物数组, 野怪数组, 兵线数组, 矩阵;
int 阵营1 = 0, fx1 = 0;


struct sESPMenu {
    bool 绘制调试 = false;
    bool 全部关闭;
    bool 是否开启共享;
    bool 全部开启;
    bool 显示头像;
    bool 保存调试配置到云端;
    bool 技能计时;
    bool 野怪计时;
    bool 显示兵线;
    bool 回城判断;
    bool 敌人视野;
    int 分辨率Y = 2456;//2712  
    int 分辨率X = 2456;//1220  2846

    int 小地图左右调整 = -7;//我的配置87   -3
    int 小地图上下调整 = -4;//   -4
    int 兵线左右调整 = 9;//我的配置6
    int 兵线上下调整 = -27;//31
    int 野怪左右调整 = -9;//我的配置-6
    int 野怪上下调整 = -5;//-1
    int FPS帧率 = 120;

};
sESPMenu ESPMenu;