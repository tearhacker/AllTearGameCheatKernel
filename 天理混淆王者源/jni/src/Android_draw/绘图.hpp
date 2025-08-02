#include "IsCharacter.h"
#include "include.h"
#include <iomanip>
#include <ctime>
#include <arpa/inet.h>

#define BYTE4 0x00000004
#define BYTE8 0x00000008
#define BYTE16 0x00000010
#define BYTE10 0x000000A
#define BYTE64 0x00000040
#define BYTE1024 0x00000400

static uint64_t lil2cpp_base = 0;
static uint64_t lil2cpp_bss = 0;
static uint64_t libGame_base = 0;
static uint64_t libunity_base = 0;
static uint64_t libtersafe_base = 0;
static uint64_t duan_addr = 0;
static uint64_t rc_dxl_id = 0;  //初始化顶部技能存储血量颜色判断int 数据;
static uint64_t rc_xxl_id = 0;  //初始化小地图存储血量颜色判断

float offset_y = 25.0f; // 向下移动的距离
float thickness = 3.0f; // 长方形条的厚度（高度保持不变，宽度减半）
// 人物结构体基址数组
long bingxiang6[BYTE16];

int 一技能判断,二技能判断,三技能判断;

int minIndex = 0;
int minIndexN = 0;
bool Aim;
long AimTarget;
bool isMove;
Touch::touchObj *lastTouchObj;
extern float jnsize;

int small_hp;
int small_dist;
int select_mode = 1;
int IsVisible[BYTE16];

// 自身结构体基址
long localplayer;
bool isAimDown = false;
long localplayerCamp;
bool 自瞄视野判断 = false;
uint64_t OwnEntityDataAddress;

float minAngle = 90.0f;

uint64_t MatrixAddress = 0; // 初始化矩阵地址
float isGames;              // 储存矩阵的值
int foeComp;                // 敌方阵营
int rientation = 0;         // 对局方向
int AroundNumbers = 0;      // 人头数量
int 视野 = 0;
int 自身视野 = 0;
long coordinatex, coordinatey;
long rotatingdraw = 0;
float 距离敌人 = 0;
int 惩戒伤害 = 0;
bool 召唤师技能判断 = false;
uintptr_t 对象坐标;
long zuo[5];
int biao[5];
long zuobiao;
int j = 0;
int 坐标X = 0;
extern int socket_fd;

int dr;
int dr_x[5];
int dr_y[5];



struct Coord {
    float X; // X轴
    float Y; // Y轴
    float W;
    float H;
};
struct DynamicData {
    struct Coord coord; // 获取xy坐标
};

struct HeroTemp {
	int TB1;//图标
    int TB2;
    int TB3;
	int TB4;
    struct Coord coord; // 获取xy坐标
    int Hp;             // 当前血量
    int MaxHp;          // 最大血量
    int Id;             // 英雄id
    int Space;          // 大招cd;
    int Space2;          // 2技能cd
    int Space1;          // 1技能cd
	int Space3;
    int Spaceid;            //大招ID
    int Space2id;            //2技能ID
    int Space1id;            //1技能ID
    int Skill;          // 召唤师技能cd
    int camp;           // 阵营id
    int HC;             // 回城
    int TB;             // 图标
    int confound;       // 坐标混淆
};
/**
 * 获取野怪xy和刷新时间
 */
struct Pve {
    uint64_t X; // X坐标地址
    uint64_t Y; // Y坐标地址
    uint64_t id;
    uint64_t cd; // 刷新时间
    uint64_t cc;
    uint64_t maxcd;
    uint64_t hp;
    uint64_t maxhp;
};
/**
 * 获取野怪xy和刷新时间
 */

  struct YWTemp {
  struct Coord coord; // 获取xy坐标
  int cd;
};
 
struct YwTemp {
  struct Coord coord; // 获取X坐标
  uint64_t X; // X坐标地址
  uint64_t Y; // Y坐标地址
};

struct PveTemp {
    struct Coord coord; // 获取xy坐标
    int hp;
    int maxhp;
    int id;
    int cd; // 刷新时间
    int maxcd;
};

/**
     * 获取兵线xy
 */
struct Pvc {
    uint64_t X; // X坐标地址
    uint64_t Y; // Y坐标地址
};
/**
 * 单个兵线
 */
struct CeTemp {
    struct Coord coord; // 获取xy坐标
    int cd;
};

struct kl {
    struct Coord coord;//获取xy坐标
    struct Coord anim_coord;//获取xy坐标
};

typedef struct {
    float Matrix[BYTE16];                   // 相机矩阵
    struct HeroTemp heroTemp[BYTE16];       // 储存单个英雄
    struct DynamicData DynamicData[BYTE16]; // 储存单个英雄大地图
    struct Pve pve[BYTE1024];               // 储存野怪
    struct PveTemp pveTemp[BYTE1024];       // 储存野怪
    struct CeTemp CeTemp[BYTE1024];         // 储存兵线
    struct Pvc pvc[BYTE1024];               // 储存兵线
    struct YWTemp YWTemp[BYTE1024];         // 储存眼位
	struct YwTemp YwTemp[BYTE1024];
    struct kl kl[BYTE1024];
    int xbsl;                               // 小兵数量
    int ywsl; 
} DataTable;

DataTable dataTable; // 游戏数据表

const static ImColor Paint_chired = ImColor(219, 77, 110);   // 赤红
const static ImColor Paint_purple = ImColor(255, 0, 255);    // 紫色
const static ImColor Paint_red = ImColor(255, 0, 0);         // 红色
const static ImColor Paint_white = ImColor(255, 255, 255);   // 白色
const static ImColor Paint_lightblue = ImColor(0, 255, 255); // 浅蓝色
const static ImColor Paint_yellow = ImColor(255, 255, 0);    // 黄色
const static ImColor Paint_green = ImColor(0, 255, 0);       // 绿色
const static ImColor Paint_pink = ImColor(255, 192, 203); // 一个常见的粉色
const static ImColor Paint_orange = ImColor(255, 165, 0);      // 橙色
const static ImColor Paint_blue = ImColor(0, 0, 255);          // 蓝色
const static ImColor Paint_cyan = ImColor(0, 255, 255);        // 青色
const static ImColor Paint_magenta = ImColor(255, 0, 255);     // 品红色
const static ImColor Paint_black = ImColor(0, 0, 0);           // 黑色
const static ImColor Paint_gray = ImColor(128, 128, 128);      // 灰色
const static ImColor Paint_lightgray = ImColor(200, 200, 200); // 浅灰色
const static ImColor Paint_brown = ImColor(165, 42, 42);       // 褐色
const static ImColor Paint_peachpuff = ImColor(255, 218, 185); // 桃色
const static ImColor Paint_gold = ImColor(255, 215, 0);        // 金色
const static ImColor Paint_silver = ImColor(192, 192, 192);    // 银色
const static ImColor Paint_maroon = ImColor(128, 0, 0);        // 栗色
const static ImColor Paint_navy = ImColor(0, 0, 128);          // 海军蓝
const static ImColor Paint_teal = ImColor(0, 128, 128);        // 青绿色
const static ImColor Paint_lime = ImColor(0, 255, 0);          // 酸橙色
const static ImColor Paint_olive = ImColor(128, 128, 0);       // 橄榄绿

double Wwra = 0; // 转小地图算法

struct Coord 自身_coord = {0}; /*实际地图坐标*/
struct Coord map_coord = {0}; /*实际地图坐标*/
struct Coord map_buff = {0};  /*实际地图坐标*/
struct Coord YwTemp_coord = {0}; /*实际地图坐标*/
struct Coord Pvc_coord = {0}; /*实际地图坐标*/
struct Coord kl_coord = {0};
double 计算距离(ImVec2 thisXY, ImVec2 xy) {
    double distance = sqrt(pow(xy.x - thisXY.x, 2) + pow(xy.y - thisXY.y, 2));
    return distance;
}

float 计算浮点数(float x1, float y1, float x2, float y2)  {
    return sqrt(pow(y2 - y1, 2) + pow(x2 - x1, 2));
}

ImVec2 自身坐标;
ImVec2 自身距离;
ImVec2 目标坐标;
ImVec2 野怪坐标;
ImVec2 实体野怪;
ImVec2 自身实体视野;
ImVec2 野怪坐标缓存;

ImTextureID tubiaoid;
ImTextureID tubiaoid2;
ImTextureID tubiaoid3;
ImTextureID tubiaoid4;

long coorpage = 0;
long offset = 0;
long cooroffest = 0;
  void DrawInit(){
       int pid = getPID("com.tencent.tmgp.sgame");
   /*    
       if (pid == 0 || pid == -1) {
		   puts("先打开游戏");
           exit(1);
       }
       */
       libGame_base = getModuleBase( "libGameCore.so:bss");
       lil2cpp_base = getModuleBase("libil2cpp.so:bss");
       libtersafe_base = getModuleBase( "libtersafe.so"); 
       yxpx = screen_x;
       yxpy = screen_y;
       }


Coord CalMatrixMem(struct Coord coor, const float Matrix[]) {
    struct Coord points = {0};
    float XM = coor.X / 1000.0f;
    float ZM = coor.Y / 1000.0f;
    if (Matrix[11] && Matrix[15] && Matrix[0] && Matrix[12] && Matrix[9] && Matrix[13] &&
        Matrix[1] && Matrix[5] && Matrix[9] && Matrix[13]) {
        float radio = (float) fabs(ZM * Matrix[11] + Matrix[15]);
        points.X = 0.0f, points.Y = 0.0f, points.W = 0.0f, points.H = 0.0f;
        if (radio > 0) {
            points.X = yxpx / 2 + (XM * Matrix[0] + Matrix[12]) / radio * yxpx / 2;
            points.Y = yxpy / 2 - (ZM * Matrix[9] + Matrix[13]) / radio * yxpy / 2;
            points.W = yxpy / 2 -
                       (XM * Matrix[1] + 4.0f * Matrix[5] + ZM * Matrix[9] + Matrix[13]) / radio *
                       yxpy / 2;
            points.H = ((points.Y - points.W) / 2.0f);
        }
        return points;
    }
}

ImVec2 Lerp(const ImVec2& a, const ImVec2& b, float t) {
    return ImVec2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
}

int linearSearch(long arr[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            return 1; // 找到了
        }
    }
    return 0; // 没找到
}
int isApproximate(int num1, int num2, int error) {
    return fabs(num1 - num2) <= error;
}

// 判断数值是否接近数组中的任意一个数
int isApproximateInArray(int num, int array[], int error) {
    for (int i = 0; i < 5; i++) {
        if (isApproximate(num, array[i], error)) {
            return 1; // 找到接近的数
        }
    }
    return 0; // 未找到接近的数
}

std::pair<float, float> smoothPosition(int i, float currentPosX, float currentPosY, 
    std::vector<float>& prevPosX, std::vector<float>& prevPosY) {
    float targetPosX = currentPosX;
    float targetPosY = currentPosY;

    if (i < prevPosX.size() && i < prevPosY.size()) {
        targetPosX = prevPosX[i] + (currentPosX - prevPosX[i]) * 0.15f;
        targetPosY = prevPosY[i] + (currentPosY - prevPosY[i]) * 0.15f;
    }

    if (i >= prevPosX.size()) {
        prevPosX.resize(i + 1);
    }
    if (i >= prevPosY.size()) {
        prevPosY.resize(i + 1);
    }

    prevPosX[i] = targetPosX;
    prevPosY[i] = targetPosY;

    return std::make_pair(targetPosX, targetPosY);
}


/**
 * 大地图转小地图坐标
 * @param foe
 * @return
 */

void DrawPlayer() {


    const static float TXdx = yxpy * 0.017534f; //(头像)圈大小(22.5)半径
    const static float soldiers_dx = yxpy * (double) 0.001851851851851851; //(兵)大小(2.0f)半径
    const static float CDjs_X = yxpx * 0.337250f;      // 绘制cd起
    const static float CDjs_Y = yxpy * 0.006481f;      // 绘制cd起点Y(7)
    const static float intervalcdX = yxpx * 0.025200f; // 60(cd左右间隔)
    const static float intervalcdY = yxpy * 0.032407f; // 35(cd上下间隔)
    const static float skills_dx = yxpy * (double) 0.006481481481481481;
    const static float skills_txt_dx = skills_dx * 5.0f;   // 技能CD文字大小
    Wwra = yxpy / 10.9f * (1.574074075 + (jiange * 0.01)); // 间隔

  //共享绘图定义
  std::string 设备id = imei;
  std::string gameDataStr = "";
  std::string character = "";// "不能动";
  std::string creeps = "";
  std::string soldier = "";

    if (!isAimDown) {
        AimTarget = 0;
    }


    small_hp = -1;
    small_dist = -1;

    long temp = ReadValue(lil2cpp_base + 0x4712B8); // 8F547A8
    //矩阵数据cb

    MatrixAddress =
            ReadValue(ReadValue(ReadValue(temp + 0xb8) + 0x0) + 0x10) + 0x128;
    isGames = ReadFloat(MatrixAddress);
    // 判断敌方阵营id
    /*  ?  :   三目运算符  如果大于0就返回2 否则返回1 */
    foeComp = isGames > 0 ? 2 : 1;

    // LOGE("foeComp:%d",foeComp);
    // 判断阵营，获取算法，判断方向

   // if (ReadDword(libGame_base + 0x191E7C) != 0) { // 对局判断
    if (  true  ) { // 对局判断
   
        //开局数据已结束：:
        //int tem = ReadDword(libGame_base + 0x1DEC2D4);
        // printf("对局判断 %d \n",tem);
        rientation = foeComp == 1 ? -1 : 1;

        for (int i = 0; i < 16; i++) {
            dataTable.Matrix[i] = ReadFloat(MatrixAddress + i * 4);
        }

        // ImGui::GetBackgroundDrawList()->AddImage(createTexture1("/storage/emulated/0/105.png").textureId,
        // ImVec2(100-25, 100-25), ImVec2(100+25, 100+25));
//long temp12 = ReadDword(libGame_base + 0x1E02AA0);
        long temp1 = ReadValue(libGame_base + 0x165840);
        //坐标数据//
        //printf("temp1 %d \n",temp12);

        //selfDetermine
      //   long bingxiang8 = ReadValue(ReadValue(temp1 + 0x48) + 0xD8);
        long bingxiang8 = ReadValue(ReadValue(libGame_base + 0x165410) + 0x4D8);
  
        int 自身阵营=driver->read<int>(bingxiang8 + 0x3C);
        long bingxiang1 = temp1 + 0x238;   //0x120
        /*
      int
      自身ID=driver->read<int>(ReadValue(ReadValue(ReadValue(ReadValue(lil2cpp_base+0x8c470D8)
      +0xA0)+0x40)+0x50)+0x138);

      int
      测试ID=driver->read<int>(ReadValue(ReadValue(ReadValue(ReadValue(lil2cpp_base+0x264B0)
      +0xA0)+0x40)+0x170)+0x138);//libil2cpp.so:bss[1] + 0x264B0 -> + 0xA0 -> +
      0x40 -> + 0x170 -> + 0x138

            printf("ID : %d 测试: %d\n", 自身ID, 测试ID);
            */
        if (十人) {
            AroundNumbers = 20;
        } else {
            AroundNumbers = 10;
        }
        int dr = 0;
        int opop = 0;
        int 控制状态 = 0;
        int zhengxing;
        for (int i = 0; i < AroundNumbers; i++) {
            // int ndh = i * 0x18;

            //     long bingxiang6 =ReadValue( ReadValue(ReadValue(bingxiang1) +0x60
            //     )+ndh);

            // 存储平滑前的坐标
            std::vector<float> prevPosX(10, 0.0f);
            std::vector<float> prevPosY(10, 0.0f);

           // long bingxiang6 = ReadValue(ReadValue(bingxiang1 + i * 0x18) + 0x68);
            long bingxiang6 =ReadValue(ReadValue(bingxiang1) + i * 0x18);
  
            int pand = 1;

            if (pand > 0) {
                localplayer = bingxiang8;
                localplayerCamp = driver->read<int>(bingxiang8 + 0x3C);

                if (DrawIo[30]) {
                    if (localplayerCamp == 2) {
                        localplayerCamp = 1;
                    } else {
                        localplayerCamp = -1;

                    }
                } else {
                    if (localplayerCamp == 2) {
                        localplayerCamp = -1;
                    }
                }
                zhengxing = driver->read<int>(bingxiang6 + 0x3C);

                dataTable.heroTemp[i].Skill =
            driver->read<int>(
                ReadValue(ReadValue(ReadValue(bingxiang6 + 0x150) + 0x150) +
                          0xf8) +
                0x3c) /
            8192000;

                dataTable.heroTemp[i].TB = driver->read<int>(
            ReadValue(ReadValue(ReadValue(bingxiang6 + 0x150) + 0x150) + 0xC8) +
                        0x10);

                /*dataTable.heroTemp[i].TB = driver->read<int>(
            ReadValue(ReadValue(ReadValue(bingxiang6[i] + 0x148) + 0x150) + 0x110) +
            0x500);*/

                dataTable.heroTemp[i].Id = ReadValue(bingxiang6 + 0x30);

                //
                dataTable.DynamicData[i].coord.X =
                        (dataTable.heroTemp[i].coord.X * rientation * Wwra / 50000.0f +
                         Wwra);
                dataTable.DynamicData[i].coord.Y =
                        (dataTable.heroTemp[i].coord.Y * rientation * Wwra / 50000.0f * -1 +
                         Wwra);

                float pos_x = dataTable.DynamicData[i].coord.X + SmallMapX + 93;
                float pos_y = dataTable.DynamicData[i].coord.Y + SmallMapY + 6;

                map_coord = CalMatrixMem(dataTable.heroTemp[i].coord, dataTable.Matrix);
                map_coord.X = map_coord.X + SmallHPX;
                map_coord.Y = map_coord.Y + SmallHPY;
                
                
                
            if(dataTable.heroTemp[i].Id==125){
            for (int k=0; k < 10; k++){
	        long 元歌傀儡数组 = ReadValue(ReadValue(ReadValue(ReadValue(ReadValue(ReadValue(temp1 + 0x48) + 0x18)+0xc0)+0x68)+0x8+0x20*k)+0xD0);
	        
			int 元歌傀儡阵营 = driver->read<int>(元歌傀儡数组 + 0x3C);
			int 元歌傀儡id = driver->read<int>(元歌傀儡数组 + 0x30);
	    	int 傀儡血量 = driver->read<int>(ReadValue(元歌傀儡数组 + 0x168)+0x98);
			int 傀儡血量max = driver->read<int>(ReadValue(元歌傀儡数组 + 0x168)+0xA0);
			float 血量比 = 傀儡血量 * 100 / 傀儡血量max;
            float 血圈 = 血量比*3.6;
            int 傀儡视野;

            

		
			if(元歌傀儡id==225 && 元歌傀儡阵营!=自身阵营 &&血圈>0){
			
			
			
			
	        int 傀儡坐标x=driver->read<int>(ReadValue(ReadValue(ReadValue(元歌傀儡数组+0x2C0) + 0x30) +0x10)+0x0);//坐标输出的坐标
		    int 傀儡坐标y=driver->read<int>(ReadValue(ReadValue(ReadValue(元歌傀儡数组+0x2C0) + 0x30) +0x10)+0x8);//坐标输出的坐标
		     dataTable.kl[i].coord.X =(float)傀儡坐标x;
		     dataTable.kl[i].coord.Y =(float)傀儡坐标y;
		     
		     
if(计算浮点数(dataTable.kl[i].anim_coord.X,dataTable.kl[i].anim_coord.Y,dataTable.kl[i].coord.X,dataTable.kl[i].coord.Y)<10000){
dataTable.kl[i].anim_coord.X=ImLerp<float>(dataTable.kl[i].anim_coord.X,dataTable.kl[i].coord.X,0.15f);
dataTable.kl[i].anim_coord.Y=ImLerp<float>(dataTable.kl[i].anim_coord.Y,dataTable.kl[i].coord.Y,0.15f);
}else{
dataTable.kl[i].anim_coord.X=dataTable.kl[i].coord.X;
dataTable.kl[i].anim_coord.Y=dataTable.kl[i].coord.Y;
}

		     

		   float 傀儡X = (dataTable.kl[i].anim_coord.X * rientation * Wwra / 50000.0f + Wwra);
           float 傀儡Y = (dataTable.kl[i].anim_coord.Y * rientation * Wwra / 50000.0f * -1 + Wwra);
           float yg_x = 傀儡X + SmallMapX+94;
           float yg_y = 傀儡Y + SmallMapY+7;
           kl_coord = CalMatrixMem(dataTable.kl[i].anim_coord, dataTable.Matrix);
           kl_coord.X = kl_coord.X+傀儡x;
           kl_coord.Y = kl_coord.Y+傀儡y;

//ImGui::GetForegroundDrawList()->AddImage(

ImGui::GetForegroundDrawList()->AddImage(reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId), {(int)yg_x - TXdx-touxiangdaxiao, (int)yg_y - TXdx-touxiangdaxiao}, {(int)yg_x + TXdx+touxiangdaxiao, (int)yg_y + TXdx+touxiangdaxiao});
ImGui::GetForegroundDrawList()->AddCircleArc({yg_x, yg_y},21+xiaodituxue, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景    
ImGui::GetForegroundDrawList()->AddCircleArc({yg_x, yg_y},21+xiaodituxue, ImVec2(0, 血圈), Paint_red,  0, 5.5f);//红色血圈



ImDrawList* draw_list = ImGui::GetForegroundDrawList();
ImVec2 rect_min = ImVec2((int)kl_coord.X - (kl_coord.H*0.5f), (int)kl_coord.Y - (kl_coord.H*1.32f));
ImVec2 rect_max = ImVec2((int)kl_coord.X + (kl_coord.H*0.5), (int)kl_coord.Y + (kl_coord.H*0.2f));

draw_list->AddRectFilled(rect_min, rect_max, ImColor(255, 255, 0, 128), 0.0f, 0); // 填充半透明黄色
draw_list->AddRect(rect_min, rect_max, 颜色配置.方框颜色, 0.0f, 0, 2.0f); // 绘制方框

ImVec2 text_size = ImGui::CalcTextSize("傀儡"); // 计算文本尺寸
ImVec2 text_pos = ImVec2((rect_min.x + rect_max.x - text_size.x) / 2.0f, (rect_min.y + rect_max.y - text_size.y) / 2.0f);
draw_list->AddText(text_pos, ImColor(255, 255, 255), "傀儡");
}
}

}

                	 if (zhengxing != foeComp) {
    		       		 float 坐标x = (float)driver->read<int>(ReadValue(ReadValue(ReadValue(ReadValue(bingxiang6 + 0x248) + 0x10)) +0x60) + 0x0); // 坐标输出的坐
       			   	     float 坐标y = (float)driver->read<int>(ReadValue(ReadValue(ReadValue(ReadValue(bingxiang6 + 0x248) + 0x10)) +0x60) + 0x8); // 坐标输出的坐
                  	
					     坐标X = (int) 坐标x;

                  	     dataTable.heroTemp[i].coord.X = (int) 坐标x;
                   		 dataTable.heroTemp[i].coord.Y = (int) 坐标y;

                    float 自身判断 = 计算距离(
                            ImVec2(yxpx / 2, yxpy / 2),
                            ImVec2(map_coord.X, map_coord.Y + (-map_coord.H * 1.0f)));
                    

                    if (自身判断 <= 100 || 召唤师ID == dataTable.heroTemp[i].Id) {
                        召唤师技能ID = dataTable.heroTemp[i].TB;
                        召唤师技能 = 获取召唤师技能(dataTable.heroTemp[i].TB);
                        召唤师技能CD = dataTable.heroTemp[i].Skill;
                        召唤师ID = dataTable.heroTemp[i].Id;
                        //printf("%d", dataTable.heroTemp[i].Id);
                        召唤师 = PlayerCharacter(dataTable.heroTemp[i].Id);
                        自身坐标 = ImVec2(dataTable.heroTemp[i].coord.X,
                                          dataTable.heroTemp[i].coord.Y);

                        if (dataTable.heroTemp[i].Id == 133) {
                            召唤师技能CD = dataTable.heroTemp[i].Space;
                        }
                     
						控制状态=driver->read<int>(ReadValue(ReadValue(ReadValue(ReadValue(ReadValue(libGame_base + 0x383A0)+ 0x48) + 0xD8) + 0x108) + 0x110) +0x258);

                        if (dataTable.heroTemp[i].TB == 80108 ||
                            dataTable.heroTemp[i].TB == 80104 ||
                            dataTable.heroTemp[i].TB == 80116 ||
                            dataTable.heroTemp[i].TB == 80107 ||
                            dataTable.heroTemp[i].TB == 801162) {

                            if (召唤师技能CD == 0) {
                                召唤师技能判断 = true;
                            } else {
                                召唤师技能判断 = false;
                            }
                        }
                    }
                }

        
 if (zhengxing == foeComp) {
    static bool previousState = false;
    static float displayTime = 0.0f;
    const float displayDuration = 3.0f;
    
    if (dataTable.heroTemp[i].Id * 100 + 30 == 16930) {
        int value = driver->read<int>(ReadValue(ReadValue(ReadValue(bingxiang6 + 0x150) + 0x108) + 0xF8) + 0x3C);
        if (value != 0) {
            if (!previousState) {
                previousState = true;
                displayTime = ImGui::GetTime(); // 记录显示开始时间
            }
            
                // 显示提示语
            if (ImGui::GetTime() - displayTime <= displayDuration) {
                // 设置背景、边框和提示语
                ImU32 rectColor = IM_COL32(121, 170, 236, 150);
                ImGui::GetBackgroundDrawList()->AddRectFilled(
                    ImVec2((int)yxpx / 2 - 450, (int)55),
                    ImVec2((int)yxpx / 2 + 470, (int)145),
                    rectColor, 20, ImDrawFlags_RoundCornersAll);

                ImU32 borderColor = IM_COL32(0, 163, 255, 255);
                ImGui::GetBackgroundDrawList()->AddRect(
                    ImVec2((int)yxpx / 2 - 453, (int)52),
                    ImVec2((int)yxpx / 2 + 473, (int)148),
                    borderColor, 20, ImDrawFlags_RoundCornersAll, 3.f);

                std::string text = "          危险，后羿大招已发射！请注意";
                const char* cstr = text.c_str();
                ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 50, ImVec2((int)yxpx / 2 - 420, (int)70), ImColor(255, 255, 255, 255), cstr);
            } else {
                previousState = true; // 超过显示时间，重置状态
            }
        } else {
            previousState = false;
        }
    }
}

        if (zhengxing == foeComp) {
        /////头像id↓代码
        dataTable.heroTemp[i].Hp =
            driver->read<int>(ReadValue(bingxiang6 + 0x168) + 0xA8); // 当前血量
        
        dataTable.heroTemp[i].MaxHp =
            driver->read<int>(ReadValue(bingxiang6 + 0x168) + 0xB0);// 最大血量

        dataTable.heroTemp[i].HC = driver->read<int>(
            ReadValue(ReadValue(ReadValue(bingxiang6 + 0x150) + 0x168) + 0x168) + 0x20);// 回城数据

          if (zhengxing == 2) {
            视野 = driver->read<int>(
                ReadValue(ReadValue(bingxiang6 + 0x260) + 0x68) + 0x18);
            自身视野 = driver->read<int>(
                ReadValue(
                    ReadValue(bingxiang8 + 0x260) + 0x68) +
                0x18);
          } else {
            视野 = driver->read<int>(
                ReadValue(ReadValue(bingxiang6 + 0x260) + 0x68) + 0x38);
            自身视野 = driver->read<int>(
                ReadValue(
                    ReadValue(bingxiang8 + 0x260) + 0x68) +
                0x38);
          }
          
          
float baseIconSize = 64.0f; // 基础图标尺寸
float scaleWidth = 1.0f; // 宽度的缩放比例
float scaleHeight = 1.0f; // 高度的缩放比例
float iconWidth = baseIconSize * scaleWidth; // 计算图标宽度
float iconHeight = baseIconSize * scaleHeight; // 计算图标高度
          
          
          
          
          
          
          if (自身) {
              if (自身视野 == 257) {
                ImGui::GetForegroundDrawList()->AddImage(
    reinterpret_cast<ImTextureID>(其他贴图.图标[1].textureId),
    ImVec2(屏幕x + yxpx / 2 * 0.970833333333333333 - iconWidth / 2,
           屏幕y + yxpy / 2 * 0.787037037037037037 - iconHeight / 2),
    ImVec2(屏幕x + yxpx / 2 * 0.970833333333333333 + iconWidth / 2,
           屏幕y + yxpy / 2 * 0.787037037037037037 + iconHeight / 2));
              } else {

             /* 
               绘制字体描边(35.0f,
                    ImVec2(屏幕x + yxpx / 2 * 0.970833333333333333,
                           屏幕y + yxpy / 2 * 0.787037037037037037),
                    Paint_green, "[安全]");*/
              }
            }

        zuobiao = ReadValue(ReadValue(ReadValue(bingxiang6 + 0x248) + 0x10)) +0x60;
        zuobiao = ReadValue(zuobiao);
        
            prevPosX[i] = (float)dataTable.heroTemp[i].coord.X;
            prevPosY[i] = (float)dataTable.heroTemp[i].coord.Y;
            
          	float 坐标x = (float)driver->read<int>(zuobiao + 0x0);
            float 坐标y = (float)driver->read<int>(zuobiao + 0x8);
            if (坐标x && 坐标y) {
              float currentPosX = (float)坐标x;
              float currentPosY = (float)坐标y;
			  
			  float 人物跨度X = currentPosX - prevPosX[i];
			  if (人物跨度X < 0) {
			  	人物跨度X = 人物跨度X * -1;
			  }
			  float 人物跨度Y = currentPosY - prevPosY[i];
			  if (人物跨度Y < 0) {
			  	人物跨度Y = 人物跨度Y * -1;
			  }
			  //printf("X %.0f\tY %.0f\n", 人物跨度X, 人物跨度Y);
			  if (人物跨度X > 1000 || 人物跨度Y > 1000) {
			  	dataTable.heroTemp[i].coord.X = currentPosX;
                dataTable.heroTemp[i].coord.Y = currentPosY;
			  } else {
			  
			  
			  std::pair<float, float> smoothedCoords = smoothPosition(i, currentPosX, currentPosY, prevPosX, prevPosY);
    		  
    		  
    		  dataTable.heroTemp[i].coord.X = smoothedCoords.first;
              dataTable.heroTemp[i].coord.Y = smoothedCoords.second;
            }
            } else {
            dataTable.heroTemp[i].coord.X = 9500;
            dataTable.heroTemp[i].coord.Y = 9500;
            
            }
            // 存储平滑前的坐标
    
        
          

          目标坐标 = ImVec2(dataTable.heroTemp[i].coord.X,
                            dataTable.heroTemp[i].coord.Y);
          距离敌人 = 计算距离(自身坐标, 目标坐标);
          
          
          

          
          
          
          dr_x[dr] = dataTable.heroTemp[i].coord.X;
          dr_y[dr] = dataTable.heroTemp[i].coord.Y;
          dr++;
          


          float hp1 =
              dataTable.heroTemp[i].Hp * 100 / dataTable.heroTemp[i].MaxHp;

          float aa = hp1 * 3.6;
         
		  
    int 大招最大CD = driver->read<int>(ReadValue(ReadValue(ReadValue(人物数组 + 0x150) + 0x108) + 0xF8) + 0xDC) / 8192000; 
        dataTable.heroTemp[i].Space3 = driver->read<int>(ReadValue(ReadValue(ReadValue(bingxiang6 + 0x150) + 0x108) + 0xF8) + 0x3C) / 8192000;       
          
    dataTable.heroTemp[i].TB4 = ReadValue(ReadValue(ReadValue
    (bingxiang6 + 0x150) + 0x150) + 0xC8) + 0x10;//召唤师技能
          if (ESPMenu.是否开启共享) {
            //启用共享绘制传输变量
          int  zyz = driver->read<int>(bingxiang6 + 0x3C);  //阵营           
          int  herealx = (int)(dataTable.heroTemp[i].coord.X * rientation * 2400/2/11.2f*1.455 / 50000 + 2400/2/11.2f*1.455);
          int   herealy = (int)(dataTable.heroTemp[i].coord.Y * rientation * 2400/2/11.2f*1.455 / 50000 * -1 + 2400/2/11.2f*1.455);
          
            character += std::to_string(dataTable.heroTemp[i].Id)
                + "," + std::to_string(dataTable.heroTemp[i].Hp)
                + "," + std::to_string(dataTable.heroTemp[i].MaxHp)
                + "," + std::to_string(dataTable.heroTemp[i].Space3)
                + "," + std::to_string(dataTable.heroTemp[i].Skill)
                + "," + std::to_string(herealx - 20 + ESPMenu.小地图左右调整)//3技能时间
                + "," + std::to_string(herealy - 20 + ESPMenu.小地图上下调整)
                + "," + std::to_string(hp1)
                + "," + std::to_string(zhengxing)
                + "," + std::to_string(zyz)
                + "," + std::to_string(dataTable.heroTemp[i].HC)
               + "," + std::to_string(dataTable.heroTemp[i].TB4)
               + "," + std::to_string(大招最大CD)
                + "==";
                }


          ImTextureID handId;
          handId = reinterpret_cast<ImTextureID>(贴图1.头像[dataTable.heroTemp[i].Id].textureId);

          if (aa > 0 || dataTable.heroTemp[i].Id == 183) {
            if (血量) {
              if (视野 == 257) {
                if (头像常显) {
                  // 小头像血量
                  ImGui::GetForegroundDrawList()->AddCircleArc(
                      {pos_x, pos_y}, 21 + xiaodituxue, ImVec2(0, 360),
                      Paint_white, 0, 5.5f);
                  ImGui::GetForegroundDrawList()->AddCircleArc(
                      {pos_x, pos_y}, 21 + xiaodituxue, ImVec2(0, aa),
                      颜色配置.有视野血量颜色, 0, 5.5f);
                }
              } else {
                // 小头像血量
                ImGui::GetForegroundDrawList()->AddCircleArc(
                    {pos_x, pos_y}, 21 + xiaodituxue, ImVec2(0, 360),
                    Paint_white, 0, 5.5f);
                ImGui::GetForegroundDrawList()->AddCircleArc(
                    {pos_x, pos_y}, 21 + xiaodituxue, ImVec2(0, aa),
                    颜色配置.无视野血量颜色, 0, 5.5f);
              }
            }
             
			
			if (地图大招计时){
if (dataTable.heroTemp[i].Space > 0) {
 
 int intvalue = dataTable.heroTemp[i].Space;
                                string test = std::to_string(intvalue);
 
   ImGui::GetForegroundDrawList()->AddText(ImVec2(pos_x- 28, pos_y - 55), ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)),("大:" + test + "").c_str());//大招
   
      }else{
   }

}
          
            
            if (地图) {
              if (视野 == 257) {
                // 小头像
                if (头像常显) {
                  ImGui::GetForegroundDrawList()->AddImage(
                      handId != NULL ? handId : reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId),
                      {(int)pos_x - TXdx - touxiangdaxiao,
                       (int)pos_y - TXdx - touxiangdaxiao},
                      {(int)pos_x + TXdx + touxiangdaxiao,
                       (int)pos_y + TXdx + touxiangdaxiao});
                }
              } else {
              ImU32 darktx;
              if (暗化) {
              	darktx = IM_COL32(150, 150, 150, 255); // 128表示透明度，你可以根据需要调整
              } else {
              darktx = IM_COL32(255, 255, 255, 255); // 128表示透明度，你可以根据需要调整
              }
                ImGui::GetForegroundDrawList()->AddImage(
                    handId != NULL ? handId : reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId),
                    {(int)pos_x - TXdx - touxiangdaxiao,
                     (int)pos_y - TXdx - touxiangdaxiao},
                    {(int)pos_x + TXdx + touxiangdaxiao,
                     (int)pos_y + TXdx + touxiangdaxiao}, ImVec2(0, 0), ImVec2(1, 1), darktx);
                     //ImU32 darkColor = IM_COL32(0, 0, 0, 128); // 128表示透明度，你可以根据需要调整



                if (dataTable.heroTemp[i].HC == 1) {
                  ImGui::GetForegroundDrawList()->AddCircleArc(
                      {pos_x, pos_y}, 21 + xiaodituxue,
                      ImVec2(0 + rotatingdraw, 20 + rotatingdraw),
                      Paint_lightblue, 9.5f, 5.5f);
                  ImGui::GetForegroundDrawList()->AddCircleArc(
                      {pos_x, pos_y}, 21 + xiaodituxue,
                      ImVec2(20 + rotatingdraw, 40 + rotatingdraw),
                      Paint_purple, 9.5f, 5.5f);
                  ImGui::GetForegroundDrawList()->AddCircleArc(
                      {pos_x, pos_y}, 21 + xiaodituxue,
                      ImVec2(40 + rotatingdraw, 60 + rotatingdraw),
                      颜色配置.有视野血量颜色, 9.5f, 5.5f);
                }
              }
 
              
            }


            
            健康血量 = true;
if(((float)dataTable.heroTemp[i].Hp / (float)dataTable.heroTemp[i].MaxHp) <= zhanshaz) {健康血量 = false;}
            if (方框) {
               if (视野 == 257) {
                    if(视野方框){
                float current_hp_percentage = (float)dataTable.heroTemp[i].Hp / (float)dataTable.heroTemp[i].MaxHp;
      if (current_hp_percentage > 0.3f){
// 绘制外部方框
ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), 颜色配置.方框颜色, 20.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(255, 255, 255, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), Paint_red,  0, 5.5f);//红色血圈
                    
                    }else{
                    
                    
                    ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), Paint_red, 20.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(255, 0, 0, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), Paint_red,  0, 5.5f);//红色血圈
                    
                    }
                    
                    
                    
                    

            
                    
                    
                    
                    
                                float max_hp_percentage = 1.0f;
                              //float current_hp_percentage = (float)dataTable.heroTemp[i].Hp / (float)dataTable.heroTemp[i].MaxHp;
                                float bar_width = map_coord.H * 0.11f;  //血条宽度
                                float bar_height = map_coord.H * 1.24f;  //血条长度
                                float corner_radius = 3.0f;

                                // 绘制最大血量条边框
                                /*ImGui::GetForegroundDrawList()->AddRect(
                                    ImVec2((int)map_coord.X-8- bar_width / 2 - (-map_coord.H*0.65f), (int)map_coord.Y - (map_coord.H*1.35f)),
                                    ImVec2((int)map_coord.X-8 + bar_width / 2 - (-map_coord.H*0.65f), (int)map_coord.Y + bar_height - (map_coord.H*1.05f)),
                                    Paint_white,
                                    corner_radius
                                );*/

                                // 绘制最大血量条填充
                                    ImGui::GetForegroundDrawList()->AddRectFilled(
                                    ImVec2((int)map_coord.X-8 - bar_width / 2 + corner_radius - (-map_coord.H*0.65f), (int)map_coord.Y + corner_radius - (map_coord.H*1.35f)),
                                    ImVec2((int)map_coord.X-8 + bar_width / 2 - corner_radius - (-map_coord.H*0.65f), (int)map_coord.Y + bar_height - corner_radius - (map_coord.H*1.05f)),
                                    Paint_white,
                                    corner_radius
                                );

                                // 计算当前血量条的填充高度和起始位置
                                float current_hp_fill_height = bar_height * current_hp_percentage;
                                float fill_correction_factor = 1.32f;  // 初始修正因子为1.35

                                // 根据敌人剩余血量百分比动态调整修正因子的值
                                if (current_hp_percentage <= 0.85f) {
                                    fill_correction_factor = 1.05f;
                                }

                                float current_hp_fill_start_y = (int)map_coord.Y + bar_height - current_hp_fill_height - (map_coord.H * fill_correction_factor);

                                // 绘制当前血量条填充
                                ImGui::GetForegroundDrawList()->AddRectFilled(
                                    ImVec2((int)map_coord.X-8 - bar_width / 2 + corner_radius - (-map_coord.H * 0.65000000f), current_hp_fill_start_y),
                                    ImVec2((int)map_coord.X -8+ bar_width / 2 - corner_radius - (-map_coord.H * 0.65f), (int)map_coord.Y + bar_height - (map_coord.H * 1.05f)),
                                    Paint_red,
                                    corner_radius
                                );
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
                    
      
      }
   }else{
  //百分比30方框判断
  float current_hp_per = (float)dataTable.heroTemp[i].Hp / (float)dataTable.heroTemp[i].MaxHp;
          if (current_hp_per > 0.35f){
// 绘制外部方框
ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), 颜色配置.方框颜色, 20.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(255, 255, 255, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), Paint_red,  0, 5.5f);//红色血圈
                    
                    }else{
                    
                    
                    ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), Paint_red, 20.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(255, 0, 0, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), Paint_red,  0, 5.5f);//红色血圈
                    
                    }
                    
                    
                    
                    
                    
                                float max_hp_percentage = 1.0f;
                                float current_hp_percentage = (float)dataTable.heroTemp[i].Hp / (float)dataTable.heroTemp[i].MaxHp;
                                float bar_width = map_coord.H * 0.11f;  //血条宽度
                                float bar_height = map_coord.H * 1.24f;  //血条长度
                                float corner_radius = 3.0f;

                                // 绘制最大血量条边框
                                /*ImGui::GetForegroundDrawList()->AddRect(
                                    ImVec2((int)map_coord.X-8- bar_width / 2 - (-map_coord.H*0.65f), (int)map_coord.Y - (map_coord.H*1.35f)),
                                    ImVec2((int)map_coord.X-8 + bar_width / 2 - (-map_coord.H*0.65f), (int)map_coord.Y + bar_height - (map_coord.H*1.05f)),
                                    Paint_white,
                                    corner_radius
                                );*/

                                // 绘制最大血量条填充
                                ImGui::GetForegroundDrawList()->AddRectFilled(
                                    ImVec2((int)map_coord.X-8 - bar_width / 2 + corner_radius - (-map_coord.H*0.65f), (int)map_coord.Y + corner_radius - (map_coord.H*1.35f)),
                                    ImVec2((int)map_coord.X-8 + bar_width / 2 - corner_radius - (-map_coord.H*0.65f), (int)map_coord.Y + bar_height - corner_radius - (map_coord.H*1.05f)),
                                    Paint_white,
                                    corner_radius
                                );

                                // 计算当前血量条的填充高度和起始位置
                                float current_hp_fill_height = bar_height * current_hp_percentage;
                                float fill_correction_factor = 1.32f;  // 初始修正因子为1.35

                                // 根据敌人剩余血量百分比动态调整修正因子的值
                                if (current_hp_percentage <= 0.85f) {
                                    fill_correction_factor = 1.05f;
                                }

                                float current_hp_fill_start_y = (int)map_coord.Y + bar_height - current_hp_fill_height - (map_coord.H * fill_correction_factor);

                                // 绘制当前血量条填充
                                ImGui::GetForegroundDrawList()->AddRectFilled(
                                    ImVec2((int)map_coord.X-8 - bar_width / 2 + corner_radius - (-map_coord.H * 0.65000000f), current_hp_fill_start_y),
                                    ImVec2((int)map_coord.X -8+ bar_width / 2 - corner_radius - (-map_coord.H * 0.65f), (int)map_coord.Y + bar_height - (map_coord.H * 1.05f)),
                                    Paint_red,
                                    corner_radius
                                );
                    
                    
                    
                    
                    
                    
                    
    
    }
    }  //方框结束
              
    
    

            // 80//10
            if (辅助方框) {
              ImGui::GetForegroundDrawList()->AddRect(
                  ImVec2(SmallMapX + 78, SmallMapY - 10),
                  ImVec2(SmallMapX + 2.68 * rientation * Wwra,
                         SmallMapY + 2.13 * rientation * Wwra),
                  颜色配置.方框颜色, 5, 0);
            }
//printf("距离  %.0f\n", 距离敌人);
            if (射线) {
              if (视野 == 257) {
                if (视野方框) {
                  if (距离敌人 > 0 && 距离敌人 < 26000) {
                    ImGui::GetForegroundDrawList()->AddLine(
                        ImVec2(yxpx / 2, yxpy / 2),
                        ImVec2(map_coord.X,
                               map_coord.Y + (-map_coord.H * 1.0f)),
                        颜色配置.射线颜色, 1.5f);
                  }
                }
              } else {
                // 射线
                if (距离敌人 > 0 && 距离敌人 < 26000) {
                  ImGui::GetForegroundDrawList()->AddLine(
                      ImVec2(yxpx / 2, yxpy / 2),
                      ImVec2(map_coord.X, map_coord.Y + (-map_coord.H * 1.0f)),
                      颜色配置.射线颜色, 1.5f);
                }
              }
            
	
	dataTable.heroTemp[i].TB1 =dataTable.heroTemp[i].Id*100+10;
    
    dataTable.heroTemp[i].TB2 =dataTable.heroTemp[i].Id*100+20;
    
    dataTable.heroTemp[i].TB3 =dataTable.heroTemp[i].Id*100+30;
	
	dataTable.heroTemp[i].TB = driver->read<int>(ReadValue(ReadValue(ReadValue(bingxiang6+0x150) + 0x150) + 0xC8) + 0x10);
	
	
			//1技能
            dataTable.heroTemp[i].Space1 = ReadDword(ReadValue(ReadValue(ReadValue(bingxiang6 + 0x150) + 0xD8) + 0xf8) + 0x3C) / 8192000;
            dataTable.heroTemp[i].Space1id =dataTable.heroTemp[i].Id*100+10;
            //2技能
            dataTable.heroTemp[i].Space2 = ReadDword(ReadValue(ReadValue(ReadValue(bingxiang6 + 0x150) + 0xF0) + 0xf8) + 0x3C) / 8192000;
            dataTable.heroTemp[i].Space2id =dataTable.heroTemp[i].Id*100+20;
            //大招
            dataTable.heroTemp[i].Space = ReadDword(ReadValue(ReadValue(ReadValue(bingxiang6 + 0x150) + 0x108) + 0xf8) + 0x3C) / 8192000;
            dataTable.heroTemp[i].Spaceid =dataTable.heroTemp[i].Id*100+30;

            
            当前血量 = (float)dataTable.heroTemp[i].Hp /
                       (float)dataTable.heroTemp[i].MaxHp;



            if (dataTable.heroTemp[i].TB != 80102 &&
                dataTable.heroTemp[i].TB != 80103 &&
                dataTable.heroTemp[i].TB != 80104 &&
                dataTable.heroTemp[i].TB != 80105 &&
                dataTable.heroTemp[i].TB != 80107 &&
                dataTable.heroTemp[i].TB != 80108 &&
                dataTable.heroTemp[i].TB != 80109 &&
                dataTable.heroTemp[i].TB != 80110 &&
                dataTable.heroTemp[i].TB != 80115 &&
                dataTable.heroTemp[i].TB != 80121 &&
                dataTable.heroTemp[i].TB != 80116 &&
                dataTable.heroTemp[i].TB != 801162) {
              dataTable.heroTemp[i].TB = 0;
            }
//大招
tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].Spaceid].textureId);
//2技能
tubiaoid3=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].Space2id].textureId);
//1技能
tubiaoid4=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].Space1id].textureId);
//字体
float text_zt = (float)((double)(0.266777647) * map_coord.H);

                         if (方框技能旧) {                
                            //英雄一技能 
                            if (dataTable.heroTemp[i].Space1 > 0) {
                            ImTextureID tubiaoid;
                            if(dataTable.heroTemp[i].TB1!=0){

                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB1-0].textureId);
                            
                            }else{
                            tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }
                            ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            //绘制技能贴图
                            ImGui::GetForegroundDrawList()->AddImage(
                            tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                            ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*1.2)), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*1.2)));

                            //绘制黑色背景
                            float circleRadius = map_coord.H * 0.16f;
                            ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 1.2));
                            ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                            ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);

                            //一技能倒计时
                            int intvalue = dataTable.heroTemp[i].Space1;
                            string test = std::to_string(intvalue);

                            ImGui::GetForegroundDrawList()->AddText(
                            NULL, (float)((double)(0.25) * map_coord.H), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*1.23f)), Paint_white,
                            test.c_str());
                            } else {
                            ImTextureID tubiaoid;
                            if(dataTable.heroTemp[i].TB1!=0){

                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB1-0].textureId);
                            
                            }else{
                            tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }
                            ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            //绘制技能贴图
                            ImGui::GetForegroundDrawList()->AddImage(
                            tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                            ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*1.2)), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*1.2)));
                            }
                            
                            


                              //英雄二技能 
                            if (dataTable.heroTemp[i].Space2 > 0) {

                            ImTextureID tubiaoid;
                            if(dataTable.heroTemp[i].TB2!=0){

                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB2-0].textureId);
                            
                            }else{
                            tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }
                            ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            //绘制二技能图片
                            ImGui::GetForegroundDrawList()->AddImage(
                            tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                            ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.85)), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.85)));

                            //绘制黑色背景
                            float circleRadius = map_coord.H * 0.16f;
                            ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 0.85));
                            ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                            ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);
//二技能倒计时
                            int intvalue = dataTable.heroTemp[i].Space2;
                            string test = std::to_string(intvalue);

                            ImGui::GetForegroundDrawList()->AddText(
                            NULL, (float)((double)(0.25) * map_coord.H), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.93f)), Paint_white,
                            test.c_str()); //大招计时
                            } else {
                            ImTextureID tubiaoid;
                            if(dataTable.heroTemp[i].TB2!=0){

                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB2-0].textureId);
                            
                            }else{
                            tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }

                            ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                            ImGui::GetForegroundDrawList()->AddImage(
                            tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                            ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.85)), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.85)));
                            }
                            
                            
                            
                            //英雄大招 
                            if (dataTable.heroTemp[i].Space3 > 0) {

                            // 绘制大招
                            ImTextureID tubiaoid;
                            if(dataTable.heroTemp[i].TB3!=0){

                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB3-0].textureId);
                            
                            }else{
                            tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }

                            ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                            //绘制大招图片
                            ImGui::GetForegroundDrawList()->AddImage(
                            tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                            ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.5)), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.5)));


                            //绘制黑色背景
                            float circleRadius = map_coord.H * 0.16f;
                            ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 0.5));
                            ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                            ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);

                            int intvalue = dataTable.heroTemp[i].Space3;
                            string test = std::to_string(intvalue);

                            ImGui::GetForegroundDrawList()->AddText(
                            NULL, (float)((double)(0.25) * map_coord.H), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.58f)), Paint_white,
                            test.c_str()); //大招计时


                            } else {
                            ImTextureID tubiaoid;
                            if(dataTable.heroTemp[i].TB3!=0){

                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB3-0].textureId);
                            
                            }else{
                            tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }

                            ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                            ImGui::GetForegroundDrawList()->AddImage(
                            tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                            ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.5)), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.5)));
                            
     // 绘制白色边框圆


                                                   
                            }
                            


                            //召唤师技能 
                            if (dataTable.heroTemp[i].Skill > 0) {

                            ImTextureID tubiaoid;
      if(dataTable.heroTemp[i].TB!=0){
                            if(dataTable.heroTemp[i].TB==53391 or dataTable.heroTemp[i].TB==53395 or dataTable.heroTemp[i].TB==53393){
                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-0].textureId);
                            }else{
                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-80000].textureId);
                            }
                            }else{
                            tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }

                            ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                            ImGui::GetForegroundDrawList()->AddImage(
                            tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                            ImVec2((float)map_coord.X -(map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.15)), 
                            ImVec2((float)map_coord.X +(map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.15)));


                            //绘制黑色背景
                            float circleRadius = map_coord.H * 0.16f;
                            ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 0.15));
                            ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                            ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);


                           // 召唤师技能cd倒计时
                            int intvalue = dataTable.heroTemp[i].Skill;
                            string test = std::to_string(intvalue);

                            ImGui::GetForegroundDrawList()->AddText(
                            NULL, (float)((double)(0.25) * map_coord.H), 
                            ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.20f)), Paint_white,
                            test.c_str());
                            } else {
                            // 召唤师cd完成
                            ImTextureID tubiaoid;
                            if(dataTable.heroTemp[i].TB!=0){
                            if(dataTable.heroTemp[i].TB==53391 or dataTable.heroTemp[i].TB==53395 or dataTable.heroTemp[i].TB==53393){
                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4-0].textureId);
                            }else{
                            tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-80000].textureId);
                            }
                            }else{
                            tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }

                            ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                            ImGui::GetForegroundDrawList()->AddImage(
                            tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                            ImVec2((float)map_coord.X -(map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.15)), 
                            ImVec2((float)map_coord.X +(map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.15)));
                            
          // 绘制白色边框圆

                            
                            }

                            }////方框计时
                    

    // 方框里技能
    if (方框技能) {
          //英雄大招
                                if (dataTable.heroTemp[i].Space > 0) {                            
                                int intvalue = dataTable.heroTemp[i].Space;
                                string test = std::to_string(intvalue);
                                ImVec2 text_position = ImVec2((float)map_coord.X + (map_coord.H * 0.52), (float)map_coord.Y - (map_coord.H * -0.362));
                                ImGui::GetForegroundDrawList()->AddText(NULL, (float)((double)(0.26) * map_coord.H), text_position, Paint_red,test.c_str()); //大招计时
                                
                                } else {                                
                                ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2((float)map_coord.X + (map_coord.H * 0.62), (float)map_coord.Y - (map_coord.H * -0.46)), map_coord.H * 0.12, Paint_red );                                                 
                                }
        
                                
                            /*  注释：
                                - `ImVec2` 第一个参数是圆的中心位置，这里保持与原矩形的中心相同。
                                - 第二个参数是圆的半径，取以前矩形的半长 `(map_coord.H * 0.16)`。
                                - 第三个参数是颜色。
                                */


                                //英雄二技能 
                                if (dataTable.heroTemp[i].Space2 > 0) {                             
                                //二技能倒计时
                                int intvalue = dataTable.heroTemp[i].Space2;
                                string test = std::to_string(intvalue);

                                ImVec2 text_position = ImVec2((float)map_coord.X + (map_coord.H * -0.025), (float)map_coord.Y - (map_coord.H * -0.362));
                                ImGui::GetForegroundDrawList()->AddText(NULL, (float)((double)(0.26) * map_coord.H), text_position, Paint_green,test.c_str());
                               
                                } else {                                                          
                                ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2((float)map_coord.X + (map_coord.H * 0.05), (float)map_coord.Y - (map_coord.H * -0.46)), map_coord.H * 0.12, Paint_green );                                                 
                                }



                                //英雄一技能 
                                if (dataTable.heroTemp[i].Space1 > 0) {                             
                                //一技能倒计时
                                int intvalue = dataTable.heroTemp[i].Space1;
                                string test = std::to_string(intvalue);
                                ImVec2 text_position = ImVec2((float)map_coord.X + (map_coord.H * -0.60), (float)map_coord.Y - (map_coord.H * -0.362));
                                ImGui::GetForegroundDrawList()->AddText(NULL, (float)((double)(0.26) * map_coord.H), text_position, Paint_green,test.c_str());
                               
                                } else {                           
                                ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2((float)map_coord.X + (map_coord.H * -0.53), (float)map_coord.Y - (map_coord.H * -0.46)), map_coord.H * 0.12, Paint_green );                                                 
                              
								}

   
        if (dataTable.heroTemp[i].Skill > 0) {
            ImTextureID handId = (dataTable.heroTemp[i].TB != 0) ?
                                 reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB - (dataTable.heroTemp[i].TB == 801162 ? 800000 : 80000)].textureId) :
                                 reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

            ImVec2 pos = ImVec2(map_coord.X - map_coord.H * 0.2f, map_coord.Y - map_coord.H * 0.2f - map_coord.H * 1.0f + 50); // 往下移动50个单位
            ImVec2 size = ImVec2(map_coord.X + map_coord.H * 0.2f, map_coord.Y + map_coord.H * 0.2f - map_coord.H * 1.0f + 50); // 往下移动50个单位

            ImGui::GetForegroundDrawList()->AddImage(handId ? handId : 0, pos, size);
            ImVec2 center = ImVec2((pos.x + size.x) * 0.5f, (pos.y + size.y) * 0.5f);
            float radius = (size.x - pos.x) * 0.5f;

            ImGui::GetForegroundDrawList()->AddCircleFilled(center, radius, IM_COL32(0, 0, 0, 150));
            ImGui::GetForegroundDrawList()->AddText(NULL, 0.25f * map_coord.H,
                                                    ImVec2(pos.x + map_coord.H * 0.1f, pos.y + map_coord.H * 0.1f + 50), // 往下移动50个单位
                                                    Paint_white, std::to_string(dataTable.heroTemp[i].Skill).c_str());
        } else {
            ImTextureID handId = (dataTable.heroTemp[i].TB != 0) ?
                                 reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB - (dataTable.heroTemp[i].TB == 801162 ? 800000 : 80000)].textureId) :
                                 reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

            ImVec2 pos = ImVec2(map_coord.X - map_coord.H * 0.2f, map_coord.Y - map_coord.H * 0.2f - map_coord.H * 1.0f + 50); // 往下移动50个单位
            ImVec2 size = ImVec2(map_coord.X + map_coord.H * 0.2f, map_coord.Y + map_coord.H * 0.2f - map_coord.H * 1.0f + 50); // 往下移动50个单位

            ImGui::GetForegroundDrawList()->AddImage(handId ? handId : 0, pos, size);
        }
    }
}  //方框结束


                         if (自动净化) {
                            if (控制状态 != 0 &&
                                距离敌人 <= 12000) {
                                if (召唤师ID == 133 && 召唤师技能CD == 0) {
                                    //触摸缓冲 = true;
                                    if (屏幕方向 == 3) {
                                        Touch::Down(zhsY, yxpx - zhsX);
                                    } else if (屏幕方向 == 1) {
                                        Touch::Down(yxpy - zhsY, zhsX);
                                    }
                                    //std::thread t([&]() {
                                    usleep(1000 * 5);
                                    Touch::Up();

                                } else if (召唤师技能判断) {
                                    //触摸缓冲 = true;
                                    if (屏幕方向 == 3) {
                                        Touch::Down(zhsY, yxpx - zhsX);
                                    } else if (屏幕方向 == 1) {
                                        Touch::Down(yxpy - zhsY, zhsX);
                                    }
                                    //std::thread t([&]() {
                                    usleep(1000 * 5);
                                    Touch::Up();
                                }
                                // std::this_thread::sleep_for(1);
                                //usleep(1000 * 500);
                                //触摸缓冲 = false;
                                //});
                                // 启动线程
                                //t.detach(); // 或者 t.detach();
                            }
                        }


                        if (自动斩杀) {
                            float 当前血量 = (float) dataTable.heroTemp[i].Hp /
                                             (float) dataTable.heroTemp[i].MaxHp;
                            if (!智能斩杀) {
                                if (当前血量 > 0 && 当前血量 < zhanshaz) {
                                    血量判断 = true;
                                } else {
                                    血量判断 = false;
                                }
                            } else {
                                float 智能斩杀 = (float) dataTable.heroTemp[i].Hp -
                                                 ((float) dataTable.heroTemp[i].MaxHp -
                                                  (float) dataTable.heroTemp[i].Hp) *
                                                 0.15;
                                if (智能斩杀 < 0) {
                                    血量判断 = true;
                                } else {
                                    血量判断 = false;
                                }
                            }
                            if (血量判断 && 召唤师技能ID == 80108 && 召唤师技能判断 &&
                                距离敌人 <= 5000 && 视野 == 257 && !触摸缓冲) {
                                触摸缓冲 = true;
                                if (屏幕方向 == 3) {
                                    Touch::Down(zhsY, yxpx - zhsX);
                                } else if (屏幕方向 == 1) {
                                    Touch::Down(yxpy - zhsY, zhsX);
                                }
                                std::thread t([&]() {
                                    usleep(1000 * 5);
                                    Touch::Up();
                                    // std::this_thread::sleep_for(1);
                                    usleep(1000 * 200);
                                    触摸缓冲 = false;
                                });
                                // 启动线程
                                t.detach(); // 或者 t.detach();
                            }
                        }
                    } // 血量大于0

          
          
         // TODO：顶上技能       
         if (顶上技能) {
            float Theoffset_X = CDjs_X + jinenglanzX; // 113
            float Theoffset_Y = CDjs_Y + jinenglanzY; //-4
            float CDdrawXY[5][2] = {
                {(float)(Theoffset_X + intervalcdX * opop), (float)(Theoffset_Y + intervalcdY * 0)},
                {(float)(Theoffset_X + intervalcdX * opop), (float)(Theoffset_Y + (TXdx / 2) + intervalcdY * 1)},
                {(float)(Theoffset_X + intervalcdX * opop), (float)(Theoffset_Y + TXdx + intervalcdY * 2)},
                {(float)(Theoffset_X + intervalcdX * opop), (float)(Theoffset_Y + (TXdx * 1.5) + intervalcdY * 3)},
                {(float)(Theoffset_X + intervalcdX * opop), (float)(Theoffset_Y + (TXdx * 2) + intervalcdY * 4)}
                };

            const float _txt_X = Theoffset_X - (TXdx * 3.6f);

            CDdrawXY[1][0] = CDdrawXY[1][0] + (TXdx / 14.0f); // x 二次改变偏移
            CDdrawXY[0][1] = CDdrawXY[0][1] + (TXdx) + (TXdx / 5.0f);
            CDdrawXY[1][1] = CDdrawXY[1][1] + (TXdx * 1.25) + (TXdx / 5.0f); // 绘制头像
            CDdrawXY[2][1] = CDdrawXY[2][1] + (TXdx * 1.5) + (TXdx / 5.0f);
            CDdrawXY[3][1] = CDdrawXY[3][1] + (TXdx * 1.75) + (TXdx / 5.0f);
            CDdrawXY[4][1] = CDdrawXY[4][1] + (TXdx * 2) + (TXdx / 5.0f);
            
            int CD数组 = 0;
            
            
            
            ImU32 darkColor;
            if (hp1 <= 0) {
                darkColor = IM_COL32(150, 150, 150, 255); // 128表示透明度，你可以根据需要调整
              } else {
                darkColor = IM_COL32(255, 255, 255, 255); // 128表示透明度，你可以根据需要调整
              }
              
ImU32 translucentWhiteColor = IM_COL32(255, 255, 255, 128); // 白色，半透明



// 计算扩大后的矩形坐标

ImVec2 topLeft = {CDdrawXY[CD数组][0] - TXdx - 5, CDdrawXY[CD数组][1] - TXdx - 5};

ImVec2 bottomRight = {CDdrawXY[CD数组][0] + TXdx + 5, CDdrawXY[CD数组][1] + TXdx + 5};



// 绘制白色半透明矩形

ImGui::GetForegroundDrawList()->AddRectFilled(

    topLeft,

     bottomRight,

    translucentWhiteColor);
// 绘制技能贴图头像
ImGui::GetForegroundDrawList()->AddImage(
    handId != NULL ? handId : reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId),
    {CDdrawXY[CD数组][0] - TXdx, CDdrawXY[CD数组][1] - TXdx},
    {CDdrawXY[CD数组][0] + TXdx, CDdrawXY[CD数组][1] + TXdx}, ImVec2(0, 0), ImVec2(1, 1), darkColor);

// 顶上头像

            //ImU32 color = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::GetForegroundDrawList()->AddCircleArc(
                ImVec2(CDdrawXY[CD数组][0], CDdrawXY[CD数组][1]), TXdx, ImVec2(0, 360),
                darkColor, 0, 5);

            ImGui::GetForegroundDrawList()->AddCircleArc(
                ImVec2(CDdrawXY[CD数组][0], CDdrawXY[CD数组][1]), TXdx, ImVec2(0, aa),
                颜色配置.有视野血量颜色, 0, 5);
                
                
                
                if (小技能计时) {
//一技能
            CD数组++;
           ImTextureID tubiaoid4;
              tubiaoid4=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].Space1id].textureId);
              ImU32 Space1Color;
              int intvalue3 = dataTable.heroTemp[i].Space1;
              if (intvalue3 > 0) {
                Space1Color = IM_COL32(150, 150, 150, 255); // 128表示透明度，你可以根据需要调整
              } else {
                Space1Color = IM_COL32(255, 255, 255, 255); // 128表示透明度，你可以根据需要调整
              }
              ImGui::GetForegroundDrawList()->AddImage(
                tubiaoid4 != NULL ? tubiaoid4 : reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId),
                {CDdrawXY[CD数组][0] - TXdx, CDdrawXY[CD数组][1] - TXdx},
                {CDdrawXY[CD数组][0] + TXdx, CDdrawXY[CD数组][1] + TXdx}, ImVec2(0, 0), ImVec2(1, 1), Space1Color); // 顶上技能
            /*    ImGui::GetForegroundDrawList()->AddCircleFilled(center, radius, green_color);
ImGui::GetForegroundDrawList()->AddCircle(
    ImVec2((float)CDdrawXY[CD数组][0], CDdrawXY[CD数组][1]), // 圆心位置
    TXdx, // 半径
    IM_COL32(255, 255, 255, 255), // 白色
    0, // 不填充
    1.5f); // 线宽*/
    ImGui::GetForegroundDrawList()->AddCircle(
    ImVec2((float)CDdrawXY[CD数组][0], CDdrawXY[CD数组][1]), // 圆心位置
    TXdx, // 半径
    IM_COL32(255, 255, 255, 255), // 白色
    0, // 不填充
    1.5f); // 线宽
            if (intvalue3 > 0) { // 绘制大招
              string test1 = std::to_string(intvalue3);
              ImVec2 Space1Size = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, 0, test1.c_str());//字体居中
              ImGui::GetForegroundDrawList()->AddText(
                  NULL, skills_txt_dx,
                  ImVec2(CDdrawXY[CD数组][0] - Space1Size.x * 0.55f, CDdrawXY[CD数组][1] - Space1Size.y * 0.5f),
                  Paint_white, test1.c_str());
              
            }

      // ImGui::GetForegroundDrawList()->AddCircle({(float)CDdrawXY[3][0], CDdrawXY[3][1]}, TXdx, IM_COL32(255, 255, 255, 255), 0, 4.0f);            
           //二技能
           CD数组++;
           ImTextureID tubiaoid3;
              tubiaoid3=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].Space2id].textureId);
              ImU32 Space2Color;
              int intvalue2 = dataTable.heroTemp[i].Space2;
              if (intvalue2 > 0) {
                Space2Color = IM_COL32(150, 150, 150, 255); // 128表示透明度，你可以根据需要调整
              } else {
                Space2Color = IM_COL32(255, 255, 255, 255); // 128表示透明度，你可以根据需要调整
              }
              ImGui::GetForegroundDrawList()->AddImage(
                tubiaoid3 != NULL ? tubiaoid3 : reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId),
                {CDdrawXY[CD数组][0] - TXdx, CDdrawXY[CD数组][1] - TXdx},
             {CDdrawXY[CD数组][0] + TXdx, CDdrawXY[CD数组][1] + TXdx}, ImVec2(0, 0), ImVec2(1, 1), Space2Color); // 顶上技能
             ImGui::GetForegroundDrawList()->AddCircle(
    ImVec2((float)CDdrawXY[CD数组][0], CDdrawXY[CD数组][1]), // 圆心位置
    TXdx, // 半径
    IM_COL32(255, 255, 255, 255), // 白色
    0, // 不填充
    1.5f); // 线宽

            if (intvalue2 > 0) { // 绘制大招
              string test2 = std::to_string(intvalue2);
              ImVec2 Space2Size = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, 0, test2.c_str());//字体居中
              ImGui::GetForegroundDrawList()->AddText(
                  NULL, skills_txt_dx,
                  ImVec2(CDdrawXY[CD数组][0] - Space2Size.x * 0.55f, CDdrawXY[CD数组][1] - Space2Size.y * 0.5f),
                  Paint_white, test2.c_str());
            }
            
            }

//ImGui::GetForegroundDrawList()->AddCircle({(float)CDdrawXY[4][0], CDdrawXY[4][1]}, TXdx, IM_COL32(255, 255, 255, 255), 0, 4.0f); 
           //大招
           CD数组++;
           ImTextureID tubiaoid;
              tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].Spaceid].textureId);
              ImU32 SpaceColor;
              int intvalue = dataTable.heroTemp[i].Space;
              if (intvalue > 0) {
                SpaceColor = IM_COL32(150, 150, 150, 255); // 128表示透明度，你可以根据需要调整
              } else {
                SpaceColor = IM_COL32(255, 255, 255, 255); // 128表示透明度，你可以根据需要调整
              }
              
// 假设你已经定义了合适的颜色变量 `SpaceColor` 和其他必要的变量
// ...

// 获取当前的绘图列表
ImDrawList* drawList = ImGui::GetForegroundDrawList();

// 绘制技能贴图头像
drawList->AddImage(
    tubiaoid != NULL ? tubiaoid : reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId),
    {CDdrawXY[CD数组][0] - TXdx, CDdrawXY[CD数组][1] - TXdx},
    {CDdrawXY[CD数组][0] + TXdx, CDdrawXY[CD数组][1] + TXdx}, ImVec2(0, 0), ImVec2(1, 1), SpaceColor);

// 定义白色不实心圆的颜色值
ImU32 circleColor = IM_COL32(255, 255, 255, 255); // 白色，不透明

// 计算圆的中心点和半径
ImVec2 center = ImVec2(CDdrawXY[CD数组][0], CDdrawXY[CD数组][1]);
float radius = TXdx; // 假设 TXdx 是圆的半径

// 绘制白色不实心圆
drawList->AddCircle(center, radius, circleColor, 0, 1.5f); // 0 表示不填充，2.0f 表示线宽








            if (intvalue > 0) { // 绘制大招
              string test = std::to_string(intvalue);
              ImVec2 SpaceSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, 0, test.c_str());//字体居中
              ImGui::GetForegroundDrawList()->AddText(
                  NULL, skills_txt_dx,
                  ImVec2(CDdrawXY[CD数组][0] - SpaceSize.x * 0.55f, CDdrawXY[CD数组][1] - SpaceSize.y * 0.5f),
                  Paint_white, test.c_str());
            }
           
  // ImGui::GetForegroundDrawList()->AddCircle({(float)CDdrawXY[5][0], CDdrawXY[5][1]}, TXdx, IM_COL32(255, 255, 255, 255), 0, 4.0f);           
            //召唤师
            
            
            CD数组++;
              ImTextureID tubiaoid2;
              ImU32 SkillColor;
              int intvalue1 = dataTable.heroTemp[i].TB;
              int intvalue1_ = dataTable.heroTemp[i].Skill;
                if (intvalue1 == 801162) {
                  tubiaoid2 = reinterpret_cast<ImTextureID>(
                      技能贴图.头像[intvalue1- 800000]
                          .textureId);

                } else if (intvalue1 >= 80102 && intvalue1 <= 80121) {
                  tubiaoid2 = reinterpret_cast<ImTextureID>(
                      技能贴图.头像[intvalue1 - 80000]
                          .textureId);
                } else {
                  tubiaoid2 = reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                }

              
              if (intvalue1_ > 0) {
                SkillColor = IM_COL32(150, 150, 150, 255); // 128表示透明度，你可以根据需要调整
              } else {
                SkillColor = IM_COL32(255, 255, 255, 255); // 128表示透明度，你可以根据需要调整
              }
              ImGui::GetForegroundDrawList()->AddImage(
                  tubiaoid2,
                  {(float)CDdrawXY[CD数组][0] - TXdx, CDdrawXY[CD数组][1] - TXdx},
                  {(float)CDdrawXY[CD数组][0] + TXdx, CDdrawXY[CD数组][1] + TXdx}, ImVec2(0, 0), ImVec2(1, 1), SkillColor); // 顶上召唤师技能
    ImGui::GetForegroundDrawList()->AddCircle(
    ImVec2((float)CDdrawXY[CD数组][0], CDdrawXY[CD数组][1]), // 圆心位置
    TXdx, // 半径
    IM_COL32(255, 255, 255, 255), // 白色
    0, // 不填充
    1.5f); // 线宽
               
            if (intvalue1_ > 0) { // 绘制召唤计时
              string test = std::to_string(intvalue1_);
              ImVec2 SkillSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, 0, test.c_str());//字体居中
              ImGui::GetForegroundDrawList()->AddText(
                  NULL, skills_txt_dx,
                  ImVec2(CDdrawXY[CD数组][0] - SkillSize.x * 0.55f, CDdrawXY[CD数组][1] - SkillSize.y * 0.5f),
                  Paint_white, test.c_str());
            }                        
          } // 血量大于0
          opop++;
        }
      }
    }//10次循环结束


		   if (上帝) {         
		         long sdaddr = ReadValue(ReadValue(lil2cpp_base+0x5F80)+0xB8)+0x28C;
				      driver->write<float>(sdaddr,shangdi);//自定义数值//正式服
			   }
    
    
        uint64_t BuffAddress; // buff数量地址
        uint64_t BxAddress;   // 兵线数量地址
        uint64_t bxAddress;   // 兵线属性首位置
        uint64_t yanwei;   
        uint64_t yanweiss;   
        uint64_t Buffsl;      // buff坐标数量



      if (野怪) {
            int 野怪距敌 = 0;
            int 距离野怪 = 0;
            bool 野怪距敌判断 = false;

            long temp2 = ReadValue(libGame_base + 0x1E18);
            BuffAddress =
                    ReadValue(ReadValue(ReadValue(temp2 + 0x3B8) + 0x88) + 0x120);
            // printf("START\n");
            for (int i = 0; i < 23; i++) {
                std::vector<float> pvePosX(21, 0.0f);
                std::vector<float> pvePosY(21, 0.0f);
				             
     if (ESPMenu.是否开启共享) {
        //共享全源数据
        // bbuff1 = Driver->读取指针(野怪数组 + i * 0x18);
        buffid = driver->read<int>(dataTable.pve[i].id);
        ygtime = driver->read<int>(dataTable.pve[i].cd ) / 1000;
        xxx1 = driver->read<int>(dataTable.pve[i].X);
        yyy1 = driver->read<int>(dataTable.pve[i].Y);
        buffx = xxx1 * rientation * 2400/2/11.2f*1.455 / 50000.0f + 2400/2/11.2f*1.455;
        buffy = yyy1 * rientation * 2400/2/11.2f*1.455 / 50000.0f * -1 + 2400/2/11.2f*1.455;
        //传输野怪数据
        creeps += std::to_string(0)
            + "," + std::to_string(ygtime)
            + "," + std::to_string(buffid)
            + "," + std::to_string(buffx + ESPMenu.野怪左右调整)
            + "," + std::to_string(buffy + ESPMenu.野怪上下调整)
            + "==";
        //传输野怪数据完毕
        }  
				
        pvePosX[i] = dataTable.pveTemp[i].coord.X;
        pvePosY[i] = dataTable.pveTemp[i].coord.Y;
        dataTable.pve[i].cd =
            ReadValue((u_long)(BuffAddress + i * 0x18)) + 0x240;
        dataTable.pve[i].maxcd =
            ReadValue((u_long)(BuffAddress + i * 0x18)) + 0x1e4;
        dataTable.pve[i].cc = ReadValue((u_long)(BuffAddress + i * 0x18));
        dataTable.pve[i].id = dataTable.pve[i].cc + 0xC0;
        long int 实体指针=ReadValue(dataTable.pve[i].cc+0x3a0);
        dataTable.pve[i].X = ReadValue(ReadValue(实体指针+0x230)+0x60)+0x0;
        dataTable.pve[i].Y = ReadValue(ReadValue(实体指针+0x230)+0x60)+0x8;
        dataTable.pve[i].hp =
            ReadValue(实体指针 + 0x168) + 0xA8;
        dataTable.pve[i].maxhp =
            ReadValue(实体指针 + 0x168) + 0xB0;

            //  int 惩戒   = driver->read<int>(ReadValue(ReadValue(ReadValue(ReadValue(ReadValue(lil2cpp_base+0x2e47b8) + 0xB8) + 0x0) + 0x20) + 0x28) + 0x21c);
			 int 惩戒  = driver->read<int>(ReadValue(ReadValue(ReadValue(ReadValue(ReadValue(lil2cpp_base + 0x2E2E08) + 0xB8) + 0x2E0) + 0x20) + 0x18) + 0x234 );
	
              if (召唤师ID == 183) {
                    惩戒伤害 = 惩戒 * 1.25;
                } else {
                    惩戒伤害 = 惩戒;
                }
                //旧(上帝so+0xB6B820)+0xB8)+0x50)+0x20)+0x20)+0x1E0);
//libil2cpp.so:bss + 0xDD68 -> 0xB8 -> 0x2B0 -> 0x260 -> 0x20 -> 0x1E0
//新libil2cpp.so:bss[1] + 0x4E8980 -> + 0xB8 -> + 0x10 -> + 0x20 -> + 0x20 -> + 0x1E0
                dataTable.pveTemp[i].cd = driver->read<int>(dataTable.pve[i].cd) / 1000;
                dataTable.pveTemp[i].maxcd =
                        driver->read<int>(dataTable.pve[i].maxcd) / 1000;
                dataTable.pveTemp[i].id = driver->read<int>(dataTable.pve[i].id);
                if (dataTable.pveTemp[i].id == 0) { continue; }
                int 固定坐标X = ReadDword(dataTable.pve[i].cc + 0x2b8);
                int 固定坐标Y = ReadDword(dataTable.pve[i].cc + 0x2b8+8);
                float pveX =
                        (float) driver->read<int>(dataTable.pve[i].X);
                float pveY =
                        (float) driver->read<int>(dataTable.pve[i].Y);

                float 野怪跨度X = pveX - pvePosX[i];
                if (野怪跨度X < 0) {
                    野怪跨度X = 野怪跨度X * -1;
                }
                float 野怪跨度Y = pveY - pvePosY[i];
                if (野怪跨度Y < 0) {
                    野怪跨度Y = 野怪跨度Y * -1;
                }
                //printf("X %.0f\tY %.0f\n", 野怪跨度X, 野怪跨度Y);
                if (野怪跨度X > 1000 || 野怪跨度Y > 1000) {
                    dataTable.pveTemp[i].coord.X = pveX;
                    dataTable.pveTemp[i].coord.Y = pveY;
                } else {

                    std::pair<float, float> pvesmoothedCoords = smoothPosition(i, pveX, pveY,
                                                                               pvePosX, pvePosY);

                    dataTable.pveTemp[i].coord.X = pvesmoothedCoords.first;
                    dataTable.pveTemp[i].coord.Y = pvesmoothedCoords.second;
                }


                //int 野怪距敌 = 计算距离(ImVec2(dataTable.pveTemp[i].coord.X,
                //dataTable.pveTemp[i].coord.Y), 目标坐标);
                dataTable.pveTemp[i].hp = driver->read<int>(dataTable.pve[i].hp);
                dataTable.pveTemp[i].maxhp = driver->read<int>(dataTable.pve[i].maxhp);
                //printf("hp %d  maxhp %d\n", dataTable.pveTemp[i].hp, dataTable.pveTemp[i].maxhp);
                map_buff = CalMatrixMem(dataTable.pveTemp[i].coord, dataTable.Matrix);
                map_buff.X = map_buff.X + SmallHPX;
                map_buff.Y = map_buff.Y + SmallHPY;
                实体野怪 = ImVec2((int) map_coord.X, (int) map_coord.Y);
                ImVec2 固定野怪 = ImVec2((int) pveX, (int) pveY);
                距离野怪 = 计算距离(自身坐标, 固定野怪);
                //printf("距离野怪 %d\n",距离野怪);
                // printf("X %.0f  Y %.0f\n", (float)dataTable.pveTemp[i].coord.X,
                // (float)dataTable.pveTemp[i].coord.Y); printf("X %.0f  Y %.0f\n",
                // (float)map_buff.X, (float)map_buff.Y);
                float pvegdX =
                        (float) (固定坐标X * rientation * Wwra /
                                 50000.0f +
                                 Wwra);
                float pvegdY =
                        (float) (固定坐标Y * rientation * Wwra /
                                 50000.0f * -1 +
                                 Wwra);
           

                if (自动惩戒 && 召唤师技能判断 && dataTable.pveTemp[i].hp > 0) {
                    // printf("自动惩戒已开启\n");
                    if (dataTable.pveTemp[i].id == 166018 ||
                        dataTable.pveTemp[i].id == 166009 ||
                        dataTable.pveTemp[i].id == 166012 ||
                        dataTable.pveTemp[i].id == 1660221 ||
                        dataTable.pveTemp[i].id == 166022 ||
                        dataTable.pveTemp[i].id == 266010 ||
                        dataTable.pveTemp[i].id == 266011 ||

                        dataTable.pveTemp[i].id == 1010350 ||
                        dataTable.pveTemp[i].id == 1010351 ||
                        dataTable.pveTemp[i].id == 1010334 ||
                        dataTable.pveTemp[i].id == 1010336 ||
                        dataTable.pveTemp[i].id == 1010335 ||
                        dataTable.pveTemp[i].id == 1010333) {

                        for (int l = 0; l < 5; l++) {
                            野怪距敌 = 计算距离(固定野怪, ImVec2(dr_x[l], dr_y[l]));
                            //printf("野怪距敌 %d\n", 野怪距敌);
                            //printf("X坐标 %d\tY坐标 %d\t距敌 %d\t距自 %d\n", dr_x[l], dr_y[l], 野怪距敌, 距离野怪);
            

                        }


                        if (智能不惩) {
                            if (距离野怪 < 5900 && dataTable.pveTemp[i].hp <= 惩戒伤害 &&
                                野怪距敌判断 && !触摸缓冲) {
                                惩戒判断 = true;
                            } else {
                                惩戒判断 = false;
                            }
                        } else {
                            if (距离野怪 < 5900 && dataTable.pveTemp[i].hp > 0 &&
                                dataTable.pveTemp[i].hp <= 惩戒伤害 && !触摸缓冲) {
                                惩戒判断 = true;
                            } else {
                                惩戒判断 = false;
                            }
                        }

                        if (惩戒判断) {
                            // printf("点击惩戒\n");
                            触摸缓冲 = true;
                            if (屏幕方向 == 3) {
                                Touch::Down(zhsY, yxpx - zhsX);
                            } else if (屏幕方向 == 1) {
                                Touch::Down(yxpy - zhsY, zhsX);
                            }
                            std::thread cj([&]() {
                                usleep(1000 * 5);
                                Touch::Up();
                                // std::this_thread::sleep_for(1);
                                usleep(1000 * 250);
                                触摸缓冲 = false;
                            });
                            // 启动线程
                            cj.detach(); // 或者 t.detach();
                        }
                    }
                }
				
             if (野血){
                if (dataTable.pveTemp[i].hp > 0 &&
                    dataTable.pveTemp[i].cd == dataTable.pveTemp[i].maxcd) {        
                if (dataTable.pveTemp[i].hp < dataTable.pveTemp[i].maxhp) {         
                    string text = std::to_string(dataTable.pveTemp[i].hp);

				   ImVec2 textSize2 = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, 0, text.c_str());
				   ImVec2 textPos2 = ImVec2((float)(pvegdX + SmallMapX - 6.0 + 93) - textSize2.x * 0.5f, (float)(pvegdY + SmallMapY - 7.9 + 6) - textSize2.y * 0.25f); // 计算居中位置
        		   ImGui::GetForegroundDrawList()->AddText(
           		   NULL, 31.0f,
           	 	   textPos2,
                   ImColor(0, 255, 255), text.c_str());      
                }            
                   string text1 = std::to_string(dataTable.pveTemp[i].hp);      
     		       ImVec2 topLeft((int)map_buff.X - (map_buff.H * 0.5f), (int)map_buff.Y - (map_buff.H * 0.075f));
				   ImVec2 bottomRight = ImVec2((int)map_buff.X + (map_buff.H * 0.5f), (int)map_buff.Y + (map_buff.H * 0.075f));
				   
				   // 使用黑色绘制实心矩形
			       ImGui::GetForegroundDrawList()->AddRectFilled(topLeft, bottomRight, IM_COL32(0, 0, 0, 255));
	  
			 float buff_hp = (float)dataTable.pveTemp[i].hp / (float)dataTable.pveTemp[i].maxhp - 0.5f;
           
			 // 绘制长条形的血条
			    if (dataTable.pveTemp[i].hp <= 惩戒伤害 && dataTable.pveTemp[i].hp != dataTable.pveTemp[i].maxhp) {
			  	   ImGui::GetForegroundDrawList()->AddRectFilled(topLeft, ImVec2((int)map_buff.X + (map_buff.H * buff_hp), (int)map_buff.Y + (map_buff.H * 0.07f)), ImColor(255, 0, 0, 150), 0);//红色
				   } else {
				   ImGui::GetForegroundDrawList()->AddRectFilled(topLeft, ImVec2((int)map_buff.X + (map_buff.H * buff_hp), (int)map_buff.Y + (map_buff.H * 0.07f)), Paint_green, 0);//绿
				   }
			    
				   // 计算被方括号包裹的文本的大小
			       ImVec2 textSize = ImGui::CalcTextSize(("[" + text1 + "]").c_str());
                   ImVec2 textPos((topLeft.x + bottomRight.x - textSize.x) * 0.5f, topLeft.y - textSize.y - 5.0f);

                   // 绘制血条的边框
		           ImGui::GetForegroundDrawList()->AddRect(topLeft, bottomRight, ImColor(255, 255, 255), 0);  // 使用白色绘制边框
                   ImGui::GetForegroundDrawList()->AddText(NULL, 25.0f, textPos, ImColor(255, 255, 255), text1.c_str());
                   }                
               }

    if (dataTable.pveTemp[i].cd == 0 ||
                    dataTable.pveTemp[i].cd == dataTable.pveTemp[i].maxcd ||
                    dataTable.pveTemp[i].cd > 240 || dataTable.pveTemp[i].id == 166009 ||
                    dataTable.pveTemp[i].id == 1010333 || dataTable.pveTemp[i].id == 166018 ||
                    dataTable.pveTemp[i].id == 1010335 || dataTable.pveTemp[i].id == 166012 ||
                    dataTable.pveTemp[i].id == 1010334 || dataTable.pveTemp[i].id == 166022 ||
                    dataTable.pveTemp[i].id == 1010336 || dataTable.pveTemp[i].id == 1660221) {
                    //166009/1010333/166018/1010335/166012/1010334/166022/1010336/1660221
                    continue;
                } else {

                    string text = std::to_string(dataTable.pveTemp[i].cd);

                    ImVec2 textSize2 = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(),
                                                                       FLT_MAX, 0, text.c_str());
                    ImVec2 textPos2 = ImVec2(
                            (float) (pvegdX + SmallMapX - 6.0 + 93) - textSize2.x * 0.5f,
                            (float) (pvegdY + SmallMapY - 7.9 + 6) - textSize2.y * 0.25f); // 计算居中位置
                    ImGui::GetForegroundDrawList()->AddText(
                            NULL, 31.0f,
                            textPos2,
                            ImColor(255, 255, 255), text.c_str());
                }
            }
        }
		
        if (野怪) {

            dataTable.pveTemp[1].coord.X = -55000 + 2500;
            dataTable.pveTemp[1].coord.Y = -55000 + 2500;

            Pvc_coord = CalMatrixMem(dataTable.pveTemp[1].coord, dataTable.Matrix);
            Pvc_coord.X = Pvc_coord.X + SmallHPX;
            Pvc_coord.Y = Pvc_coord.Y + SmallHPY;

            std::string txt = "";// 可以填入文字（泉水位置显示文字)
            ImVec2 textSize = ImGui::CalcTextSize(txt.c_str());
            ImVec2 textPos(Pvc_coord.X - textSize.x * 0.5f, Pvc_coord.Y - textSize.y * 0.5f);
            绘制字体描边(34.0f,
                         textPos,
                         ImColor(0, 255, 255), txt.c_str());
            }
      
       if (兵线) {
            int number; // 兵线数量
            long temp5 = ReadValue(libGame_base + 0x165840);
           //    BxAddress = ReadValue(temp5 + 0x2e0);
                 BxAddress = ReadValue(ReadValue(temp5 + 0x138) + 0x108);
            number = 50;

            long cont = 0;
            for (int l = 0; l < number; l++) {
                bxAddress = ReadValue(BxAddress + (l * 0x18));
                int temp = driver->read<int>(bxAddress + 0x3c);
                if (temp == foeComp) {

                  int bxxl = driver->read<int>(ReadValue(bxAddress + 0x168) + 0xA8);

          dataTable.CeTemp[cont].coord.X = (float)driver->read<int>(
              ReadValue(ReadValue(bxAddress + 0x230) + + 0x60) +
              0x0);
          dataTable.CeTemp[cont].coord.Y = (float)driver->read<int>(
              ReadValue(ReadValue(bxAddress + 0x230) + + 0x60) +
              0x8); 
                    if (dataTable.CeTemp[cont].coord.X == 0 ||
                        dataTable.CeTemp[cont].coord.Y == 0) {
                        continue;
                    }
                    if (bxxl <= 0) {
                        continue;
                    } 
                    Pvc_coord = CalMatrixMem(dataTable.CeTemp[cont].coord, dataTable.Matrix);
                    Pvc_coord.X = Pvc_coord.X + SmallHPX;
                    Pvc_coord.Y = Pvc_coord.Y + SmallHPY;

                    if (实体兵线) {
                        ImGui::GetForegroundDrawList()->AddCircleFilled(
                                ImVec2(Pvc_coord.X, Pvc_coord.Y), 8.0f,
                                ImColor(0, 255, 255), 32);
                    }
                    dataTable.CeTemp[cont].coord.X =
                            dataTable.CeTemp[cont].coord.X * rientation * Wwra / 50000.0f +
                            Wwra;
                    dataTable.CeTemp[cont].coord.Y = dataTable.CeTemp[cont].coord.Y *
                                                     rientation * Wwra / 50000.0f *
                                                     -1 +
                                                     Wwra;
													 
				                                               
             if (ESPMenu.是否开启共享) {
                bingx = dataTable.CeTemp[cont].coord.X * 0.7;
                bingy = dataTable.CeTemp[cont].coord.X * 0.7;
                        
                  //定义传输兵线
                bingx = (dataTable.CeTemp[cont].coord.X  * rientation * 2400/2/11.2f*1.455 / 50000 + 2400/2/11.2f*1.455);
                bingy =    (dataTable.CeTemp[cont].coord.Y * 2400/2/11.2f*1.455 / 50000 * -1 + 2400/2/11.2f*1.455);
                soldier += std::to_string(bingx + ESPMenu.兵线左右调整) + "," + std::to_string(bingy + ESPMenu.兵线左右调整) + "," + std::to_string(temp) + "==";
               }                                                                       
													 
                    cont++;
                }
            }
            dataTable.xbsl = cont;

            for (int i = 0; i < dataTable.xbsl; i++) {
                float x = dataTable.CeTemp[i].coord.X + SmallMapX + 93;
                float y = dataTable.CeTemp[i].coord.Y + SmallMapY + 6;
                ImGui::GetForegroundDrawList()->AddRect(
                        ImVec2((float) x - soldiers_dx, (float) y - soldiers_dx),
                        ImVec2((float) x + soldiers_dx, (float) y + soldiers_dx), Paint_red,
                        soldiers_dx, 0, soldiers_dx * 2);
            }
        }

		
    
    //眼位（默认开启）
	if(1==1){ //默认1==1开    
      int number;  
      long cont = 0;
   
	for (int l = 0; l < 32; l++){
        long 眼位数组 = ReadValue(ReadValue(ReadValue(libGame_base + +0x195968)+ 0x320)+l * 0x18);
        int temp = driver->read<int>(眼位数组 + 0x3c);  
        int 眼位ID = driver->read<int>(眼位数组 + 0x30);
     
     if (temp == foeComp) {
        if(眼位ID==19610||眼位ID==50004||眼位ID==17702){//19610, 50004, 50003百里，黄忠,二哈ID判断   
        int ywxl = driver->read<int>(ReadValue(眼位数组 + 0x168)+0x98);
            dataTable.YWTemp[cont].coord.X = (float) driver->read<int>(ReadValue(ReadValue(眼位数组 +0x230 )+ 0x10) + 0x0);
            dataTable.YWTemp[cont].coord.Y = (float) driver->read<int>(ReadValue(ReadValue(眼位数组 +0x230 ) + 0x10) + 0x8);
              if (dataTable.YWTemp[cont].coord.X == 0 || dataTable.YWTemp[cont].coord.Y == 0) {continue;}
              if (ywxl<=0) {continue;}
			
			    //眼位实体
			    struct Coord 眼位实体= {0};
                眼位实体.X=dataTable.YWTemp[cont].coord.X;
                眼位实体.Y=dataTable.YWTemp[cont].coord.Y;
                眼位实体=CalMatrixMem(眼位实体,dataTable.Matrix);
				
    bool 实体眼位 = true;
    if (实体眼位) {
       string Text = "";
       Text += to_string(ywxl);
       auto Size = ImGui::CalcTextSize(Text.c_str(), 0, 25);
       ImGui::GetForegroundDrawList()->AddCircleFilled({眼位实体.X - 8, 眼位实体.Y + (-眼位实体.H * 0.30f)}, 28, Paint_blue);  
       // 在圆圈的正中间添加白色的 "眼" 字
       ImVec2 textPos = {眼位实体.X - 8 - 16, 眼位实体.Y + (-眼位实体.H * 0.30f) - 17};
       ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), 40, textPos, ImColor(255, 255, 255, 255), "陷阱");
    }	
				
       dataTable.YWTemp[cont].coord.X = dataTable.YWTemp[cont].coord.X * rientation * Wwra / 50000.0f + Wwra;
       dataTable.YWTemp[cont].coord.Y = dataTable.YWTemp[cont].coord.Y * rientation * Wwra / 50000.0f * -1 + Wwra;
       cont++;          
       }
    }//判断结束
 }
       dataTable.ywsl = cont;
     
    for(int i = 0; i < dataTable.ywsl;i++){
       float x = dataTable.YWTemp[i].coord.X + SmallMapX+94;
       float y = dataTable.YWTemp[i].coord.Y + SmallMapY+7;
       ImGui::GetForegroundDrawList()->AddRect(ImVec2((float)x - soldiers_dx, (float)y - soldiers_dx), ImVec2((float)x + soldiers_dx, (float)y + soldiers_dx), Paint_red, soldiers_dx, 0, soldiers_dx*2);
       }
    }
    
    if (绘制触摸) {
      ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(zhsX, zhsY), 50.0f,Paint_red, 32);
      //绘制触摸 = false;
    }
    
    } else {
    // 假设 yxpx 和 yxpy 是屏幕的宽度和高度
float screenWidth = yxpx;
float screenHeight = yxpy;

// 假设这是在你的渲染循环中，例如在每一帧的更新函数中

// 定义方框的位置和大小
ImVec2 boxPos = ImVec2(0.0375f * screenWidth + 800.0f, (0.925925925925925925f - 0.90f) * screenHeight);
ImVec2 boxSize = ImVec2(600.0f, 110.0f); // 你可以根据需要调整大小

// 定义方框的颜色
ImColor boxColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ImVec4(255/255.f, 150/255.f, 30/255.f, 0.5f); // 半透明蓝色

// 定义圆角的半径
float rounding = 10.0f; // 你可以根据需要调整圆角的半径

// 在ImGui的绘制列表中添加一个圆角方框


// 定义半透明背景的颜色
ImColor bgColor = ImColor(255, 255, 255, 0); // 白色，50%透明度

// 在方框内部添加一个半透明的背景，使其填满整个方框
ImGui::GetForegroundDrawList()->AddRectFilled(boxPos, ImVec2(boxPos.x + boxSize.x, boxPos.y + boxSize.y), bgColor, rounding); // 使用方框的完整大小和圆角半径

// 获取文本的尺寸
const char* text = "欢迎使用内部版本等待进入对局中...";
ImVec2 textSize = ImGui::CalcTextSize(text);

// 计算文本的起始位置，使其居中
ImVec2 textPos = ImVec2(
    boxPos.x + (boxSize.x - textSize.x) / 2.0f, // 水平居中
    boxPos.y + (boxSize.y - textSize.y) / 2.5f  // 垂直居中
);

// 定义文本的颜色
ImColor textColor = ImColor(255,255,0); // 黄色

// 在ImGui的绘制列表中添加文本
ImGui::GetForegroundDrawList()->AddText(textPos, textColor, text);

// 获取当前时间
std::time_t now = std::time(nullptr);
std::tm tm = *std::localtime(&now);

// 格式化时间字符串，包括年月日
std::ostringstream oss;
oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); // 格式为年-月-日 小时:分钟:秒
std::string timeStr = oss.str();

// 获取时间文本的尺寸
ImVec2 timeTextSize = ImGui::CalcTextSize(timeStr.c_str());

// 计算时间文本的起始位置，使其与欢迎文本对齐
ImVec2 timeTextPos = ImVec2(
    boxPos.x + (boxSize.x - timeTextSize.x) / 2.0f, // 水平居中
    textPos.y + textSize.y + 6.0f // 垂直位置在欢迎文本下方10像素
);

// 定义时间文本的颜色
ImColor timeTextColor = ImColor(255,0,0); // 粉红色

// 在ImGui的绘制列表中添加时间文本
ImGui::GetForegroundDrawList()->AddText(timeTextPos, timeTextColor, timeStr.c_str());


  }

  if (ESPMenu.是否开启共享) {
        gameDataStr = 
        "gameData" + 设备id + 
        "[==][==]" + character + 
        "---" + creeps + 
        "---" + soldier;
        char* gameData = (char*)gameDataStr.data();  //设备
        send(socket_fd, gameData, strlen(gameData), 0);
    }

  
}
