#include <string.h>
#include "include.h"
#include "IsCharacter.h"
//#include "循环.h"
int 本人X, 本人Y, 本人CD, 本人ID,人物大招最大CD;
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
uintptr_t 对象坐标;
static uint64_t lil2cpp_base = 0;
static uint64_t libGame_base = 0;
static uint64_t libunity_base = 0;
static uint64_t libtersafe_base = 0;
uint64_t MatrixAddress = 0;//初始化矩阵地址
float isGames;//储存矩阵的值
int foeComp;//敌方阵营
int rientation = 0;//对局方向
int AroundNumbers = 0;//人头数量
int 视野=0;
int 自身视野=0;
bool 坐标解密1=false;
bool 坐标解密2=false;
bool 坐标解密3 = false;
bool 坐标解密4 = false;
long coordinatex, coordinatey;
//int 屏幕x;
//int 屏幕y;
long rotatingdraw=0;
int 惩戒伤害,dist,dist3=99999;


pid_t get_name_pid(char* name) {
    FILE* fp;
    pid_t pid;
    char cmd[0x100] = "pidof ";

    strcat(cmd, name);
    fp = popen(cmd,"r");
    fscanf(fp,"%d", &pid);
    pclose(fp);
    return pid;
}

struct Coord {
    float X;//X轴
    float Y;//Y轴
    float W;
    float H;
};
struct DynamicData {
    struct Coord coord;//获取xy坐标
};

/*

https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
https://t.me/dujiunb
*/


struct HeroTemp {
    struct Coord coord;//获取xy坐标
    int Hp;//当前血量
    int MaxHp;//最大血量
    int Id;//英雄id
    int Space;//大招cd
    int Skill;//召唤师技能cd
    int camp;//阵营id
    int HC;//回城
    int TB;//图标
    int TB4;//图标
    int confound;//坐标混淆
    int Space3;
    int space;
};

/**
 * 获取野怪xy和刷新时间
 */
struct Pve {
    uint64_t X;//X坐标地址
    uint64_t Y;//Y坐标地址
    uint64_t cd;//刷新时间
    uint64_t cc;
    uint64_t maxcd;
    uint64_t id;
};
/**
 * 获取野怪xy和刷新时间
 */
 
 struct PveTemp {
    struct Coord coord;//获取xy坐标
    int cd;//刷新时间
    int maxcd;
    int id;
    int hp;
    int maxhp;
};

/**
 * 获取兵线xy
 */
struct Pvc {
    uint64_t X;//X坐标地址
    uint64_t Y;//Y坐标地址
};
/**
 * 单个兵线
 */
struct CeTemp {
    struct Coord coord;//获取xy坐标
    int cd;
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


    const static ImColor Paint_purple = ImColor(255, 0, 255);  //紫色
    const static ImColor Paint_red = ImColor(255, 0, 0);       //红色
    const static ImColor Paint_white = ImColor(255, 255, 255); //白色
    const static ImColor Paint_lightblue = ImColor(0, 255, 255);   //浅蓝色
    const static ImColor Paint_yellow = ImColor(255, 255, 0);  //黄色
    const static ImColor Paint_green = ImColor(0, 255, 0);  //绿色

double Wwra = 0;    //转小地图算法




 struct Coord map_coord = {0};/*实际地图坐标*/
    struct Coord map_buff = {0};/*实际地图坐标*/


      
long coorpage = 0;
long offset = 0;

long cooroffest = 0;


//////////////


void DrawInit() {
    pid = 独久->获取进程ID((char*)"com.tencent.tmgp.sgame");
    独久->initialize(pid);
    if (pid == 0 || pid == -1) {
        puts("先打开游戏");
        exit(1);
    }
    libGame_base = 独久->获取基址头("libGameCore.so");
 
    libunity_base = 独久->获取基址头("libunity.so");            
    libtersafe_base = 独久->获取基址头("libtersafe.so");
     lil2cpp_base = 获取基址头("libil2cpp.so:bss");       
            
    ::yxpx = abs_ScreenX;     
    ::yxpy = abs_ScreenY;     
    
   
    
       
}
 
 Coord CalMatrixMem(struct Coord coor, const float Matrix[]) {
    struct Coord points = {0};
    float XM = coor.X / 1000.0f;
    float ZM = coor.Y / 1000.0f;
    if(Matrix[11]&&Matrix[15]&&Matrix[0]&&Matrix[12]&&Matrix[9]&&Matrix[13]&&Matrix[1]&&Matrix[5] &&Matrix[9]&&Matrix[13]){
    float radio = (float)fabs(ZM * Matrix[11] + Matrix[15]);
    points.X = 0.0f, points.Y = 0.0f, points.W = 0.0f, points.H = 0.0f;
    if (radio > 0) {
        points.X = yxpx/2 + (XM * Matrix[0] + Matrix[12]) / radio * yxpx/2;
        points.Y = yxpy/2 - (ZM * Matrix[9] + Matrix[13]) / radio * yxpy/2;
        points.W = yxpy/2 - (XM * Matrix[1] + 4.0f * Matrix[5] + ZM * Matrix[9] + Matrix[13]) / radio * yxpy/2;
        points.H = ((points.Y - points.W) / 2.0f);
    }
    return points;
    }
}
    
    
/**
 * 大地图转小地图坐标
 * @param foe
 * @return
 */
    


//共享绘制房间号
void read_line_without_newline(FILE* stream, char* buffer, size_t size) {
    fgets(buffer, size, stream);
    buffer[strcspn(buffer, "\n")] = '\0';
}




void DrawPlayer()
{

      if(MemuSwitch)
    {
        绘制触摸范围(惩戒y,惩戒x,触摸位置大小);
    }
    
const static float TXdx = yxpy * 0.017534f; //(头像)圈大小(22.5)半径
      const static float soldiers_dx = yxpy * (double)0.001851851851851851; //(兵)大小(2.0f)半径
    const static float CDjs_X = yxpx * 0.337250f; //绘制cd起
       const static float CDjs_Y = yxpy * 0.006481f; //绘制cd起点Y(7)
    const static float intervalcdX = yxpx * 0.025200f; //60(cd左右间隔)
    const static float intervalcdY = yxpy * 0.032407f; //35(cd上下间隔)

    
    
    const static float skills_dx = yxpy * (double)0.006481481481481481;
    const static float skills_txt_dx = skills_dx * 5.0f;    //技能CD文字大小
    Wwra=yxpy / 10.9f * (1.574074075+(jiange*0.01));   // 间隔
float    bxWwra=1440 / 10.2f * (1.574074075+(jiange*0.01));   // 间隔

  //共享王者启动传输内容
    //共享绘制房间号imei手机标识符
    
    char imei[100] = "";//leixin666
    
       FILE* fpp = popen("getprop ro.serialno", "r");
    read_line_without_newline(fpp, imei, sizeof(imei));
    pclose(fpp);
 //   printf("共享房间=   %s\n",imei);
    std::string 设备id = imei;
    std::string gameDataStr = "";
    std::string character = "";// "不能动";
    std::string creeps = "";
    std::string soldier = "";
   // pxx = ESPMenu.分辨率X / 2;//2712和1220
    pyy = ESPMenu.分辨率Y / 2;
    WwrShare = ESPMenu.分辨率X / 2 / 11.2f * 1.574074075;


    
    long temp = 独久->读取指针(lil2cpp_base+0xB822B8);//8F547A8
    
    
   
    MatrixAddress = 独久->读取指针(独久->读取指针(独久->读取指针(temp + 0xB8) + 0x0) + 0x10) + 0x100;
    isGames = 独久->读取浮点数(MatrixAddress);
    //判断敌方阵营id
    /*  ?  :   三目运算符  如果大于0就返回2 否则返回1 */
    foeComp = isGames > 0 ? 2 : 1;
    //LOGE("foeComp:%d",foeComp);
    //判断阵营，获取算法，判断方向
    rientation = foeComp == 1 ? -1 : 1;
    
        for (int i = 0; i < 16; i++)
        {
        
            dataTable.Matrix[i] = 独久->读取浮点数(MatrixAddress + i * 4);
        }
    
    
    
    //ImGui::GetBackgroundDrawList()->AddImage(createTexture1("/storage/emulated/0/105.png").textureId, ImVec2(100-25, 100-25), ImVec2(100+25, 100+25));

    long temp1 = 独久->读取指针(libGame_base +  0x3649AA8);
 //   printf("temp1 %f \n",temp1);
   long bingxiang8 = 独久->读取指针(独久->读取指针(独久->读取指针(libGame_base  + 0x3649AA8) +0x48)+0xD8);
    long bingxiang1 = temp1 + 0x150;
  
   
int opop=0;
    
        for (int i = 0; i < 10; i++)
        {
            
            		long bingxiang6 = 独久->读取指针(独久->读取指针(bingxiang1  +  i * 0x18)+0x68);
            		
        int pand = 1;
        
        if (pand > 0)
            {

    int zhengxing = 独久->读取整数(bingxiang6 + 0x3C);

if(zhengxing==foeComp){



        // //////头像id↓代码


                    dataTable.heroTemp[i].Id = 独久->读取指针(bingxiang6 + 0x30);
                  
dataTable.heroTemp[i].Hp =独久->读取整数(独久->读取指针(bingxiang6 + 0x160) + 0x98);  // 当前血量

    dataTable.heroTemp[i].MaxHp = 独久->读取整数(独久->读取指针(bingxiang6 + 0x160) + 0xa0);
int 斩杀HP=(int)(dataTable.heroTemp[i].MaxHp-dataTable.heroTemp[i].Hp)*0.155;

dataTable.heroTemp[i].HC =  独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6 +0x148) + 0x168) + 0x118) + 0x20);





if(zhengxing==2){
				 视野 = 独久->读取整数(独久->读取指针(独久->读取指针(bingxiang6 + 0x258) + 0x68)+0x1c);
				}else{
				 视野 = 独久->读取整数(独久->读取指针(独久->读取指针(bingxiang6 + 0x258) + 0x68)+0x3c);
				}
				
			/*
			对象坐标=getcoor(bingxiang6);
				
	
				
				 float 坐标x= (float)独久->读取整数(对象坐标 + 0x0);
				 float 坐标y= (float)独久->读取整数(对象坐标 + 0x8);
			    if (坐标x && 坐标y) {
				 dataTable.heroTemp[i].coord.X =(float)坐标x;
				 dataTable.heroTemp[i].coord.Y =(float)坐标y;
				 }
				 */
			
dataTable.heroTemp[i].coord.X = (float) 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6 +0x240) +0x10)+0x0)+0x10)+0x0);    //x坐标
		dataTable.heroTemp[i].coord.Y = (float) 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6 +0x240) +0x10)+0x0)+0x10)+0x8);    //y坐标
				
                                   //召唤师图标和技能CD                             
        dataTable.heroTemp[i].Skill = 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6 + 0x148) + 0x150) + 0x110) + 0x3C) / 8192000;                  //技能技能0x148) + 0x150) + 0x100) + 0xD4
        dataTable.heroTemp[i].TB4 = 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6 + 0x148) + 0x150) + 0xe0) + 0x10);//0x148) + 0x150) + 0x60) + 0x10);
     
     dataTable.heroTemp[i].Space3 = 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6 + 0x148) + 0x108) + 0x110) + 0x3C) / 8192000;                 //  0x148) + 0x108) + 0x100) + 0xD4)
 
 
dataTable.DynamicData[i].coord.X = (dataTable.heroTemp[i].coord.X * rientation * Wwra / 50000.0f + Wwra);
dataTable.DynamicData[i].coord.Y = (dataTable.heroTemp[i].coord.Y * rientation * Wwra / 50000.0f * -1 + Wwra);
 
float pos_x = dataTable.DynamicData[i].coord.X + SmallMapX+94;
float pos_y = dataTable.DynamicData[i].coord.Y + SmallMapY+7;

map_coord = CalMatrixMem(dataTable.heroTemp[i].coord, dataTable.Matrix);
  map_coord.X = map_coord.X + SmallHPX;
map_coord.Y = map_coord.Y + SmallHPY;


        float hp1 = dataTable.heroTemp[i].Hp * 100 / dataTable.heroTemp[i].MaxHp;

    float aa = hp1*3.6;
    
                if (ESPMenu.是否开启共享) {
            //启用共享绘制传输变量
          int  zyz = 独久->读取整数(bingxiang6 + 0x3C);  //阵营           
          int  herealx = (int)(dataTable.heroTemp[i].coord.X * rientation * WwrShare / 50000 + WwrShare);
         int   herealy = (int)(dataTable.heroTemp[i].coord.Y * rientation * WwrShare / 50000 * -1 + WwrShare);

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
                + "," + std::to_string(人物大招最大CD)
                + "==";
                }
        
                  //   ImColor 血量颜色;
                //     血量颜色 = ImColor(10,240,10,210);
                
                
                ImTextureID handId;
                if(dataTable.heroTemp[i].Id>100&&dataTable.heroTemp[i].Id<600){
            
                handId =reinterpret_cast<ImTextureID>(贴图1.头像[dataTable.heroTemp[i].Id].textureId);
    }else{ 
        handId=reinterpret_cast<ImTextureID>(贴图1.头像[0].textureId);
    }
                
                
                if(aa>0){
                    
    if(血量){

                    //小头像血量
   ImGui::GetForegroundDrawList()->AddCircleArc({pos_x, pos_y},21+xiaodituxue, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
           if(视野==257){
   ImGui::GetForegroundDrawList()->AddCircleArc({pos_x, pos_y},21+xiaodituxue, ImVec2(0, aa), 颜色配置.血量颜色,  0, 5.5f);//红色血圈
   }else{
   ImGui::GetForegroundDrawList()->AddCircleArc({pos_x, pos_y},21+xiaodituxue, ImVec2(0, aa), Paint_purple,  0, 5.5f);//红色血圈//紫色无视野
   }
    }       
   
    rotatingdraw=rotatingdraw+3;  
    if(地图){
   //小头像
                    ImGui::GetForegroundDrawList()->AddImage( handId!= NULL ?  handId: 0 , {(int)pos_x - TXdx-touxiangdaxiao, (int)pos_y - TXdx-touxiangdaxiao}, {(int)pos_x + TXdx+touxiangdaxiao, (int)pos_y + TXdx+touxiangdaxiao});
                    
                        if(dataTable.heroTemp[i].HC == 1){       
ImGui::GetForegroundDrawList()->AddCircleArc({pos_x,pos_y},21+xiaodituxue,ImVec2(0+rotatingdraw,20+rotatingdraw),Paint_lightblue,9.5f,5.5f);
ImGui::GetForegroundDrawList()->AddCircleArc({pos_x,pos_y},21+xiaodituxue,ImVec2(20+rotatingdraw,40+rotatingdraw),Paint_purple,9.5f,5.5f);
ImGui::GetForegroundDrawList()->AddCircleArc({pos_x,pos_y},21+xiaodituxue,ImVec2(40+rotatingdraw,60+rotatingdraw),颜色配置.血量颜色,9.5f,5.5f);//顶上头像颜色
  
   }
}
                    
   if(自身判断){

   if(zhengxing==2){
				 自身视野 = 独久->读取整数(独久->读取指针(独久->读取指针(bingxiang8 + 0x258) + 0x68)+0x3c);
				}else{
				 自身视野 = 独久->读取整数(独久->读取指针(独久->读取指针(bingxiang8 + 0x258) + 0x68)+0x1c);
				}


	if(自身视野 ==257) {


ImGui::GetForegroundDrawList()->AddText(ImVec2(屏幕x, 屏幕y), Paint_red, "      [暴露]");
}
else{
ImGui::GetForegroundDrawList()->AddText(ImVec2(屏幕x, 屏幕y), Paint_green, "      [安全]");
}

   
   }
   
   
   
   if(方框){
   
         
               

                           
                                 
                                       
                                             
                                                   
                                                         
                                                               
                                                                     
                                                                           
                                                                                 
                                                                                       
                                                                                                   
   if(视野==257){
      if(视野方框){
      float current_hp_percentage = (float)dataTable.heroTemp[i].Hp / (float)dataTable.heroTemp[i].MaxHp;
      if (current_hp_percentage > 0.3f){
// 绘制外部方框
ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), 颜色配置.方框颜色, 0.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(155, 155, 155, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), 颜色配置.血量颜色,  0, 5.5f);//红色血圈
                    
                    }else{
                    
                    
                    ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), 颜色配置.血量颜色, 0.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(255, 0, 0, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), 颜色配置.血量颜色,  0, 5.5f);//红色血圈
                    
                    }
                
      }
   }else{
  //百分比30方框判断
  float current_hp_per = (float)dataTable.heroTemp[i].Hp / (float)dataTable.heroTemp[i].MaxHp;
          if (current_hp_per > 0.35f){
// 绘制外部方框
ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), 颜色配置.方框颜色, 0.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(155, 155, 155, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), 颜色配置.血量颜色,  0, 5.5f);//红色血圈
                    
                    }else{
                    
                    
                    ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), Paint_red, 0.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(255, 0, 0, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), 颜色配置.血量颜色,  0, 5.5f);//红色血圈
                    
                    }
                    
                    

    }
    }
    
                   
                                                       
 if(辅助方框){
 ImGui::GetForegroundDrawList()->AddRect(ImVec2(SmallMapX+80, SmallMapY-10), ImVec2(SmallMapX+2.73* rientation * Wwra , SmallMapY+2.13* rientation * Wwra ), 颜色配置.方框颜色, 5, 0);
 }                                                                         
                                                 
                                                                
                                                                                              
    if(射线){      
   if(视野==257){
      if(视野方框){
      ImGui::GetForegroundDrawList()->AddLine(ImVec2(yxpx/2, yxpy/2), ImVec2(map_coord.X, map_coord.Y + (-map_coord.H*1.0f)), 颜色配置.射线颜色, 1.5f);
      
      }
   }else{         
                    //射线
                     
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2(yxpx/2, yxpy/2), ImVec2(map_coord.X, map_coord.Y + (-map_coord.H*1.0f)), 颜色配置.射线颜色, 1.5f);
    }               
                 }   
                 
           
                    
    
    dataTable.heroTemp[i].Space = 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6+0x148)+0x108)+0x110)+0x3C)/8192000;
    
    
        dataTable.heroTemp[i].Skill = 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6+0x148)+0x150)+0x110)+0x3c)/8192000;          
        
        
        
        
                    dataTable.heroTemp[i].TB = 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bingxiang6+0x148) + 0x150) + 0xC8) + 0x10);//召唤师图标
                                           
                                           
                                if (dataTable.heroTemp[i].TB != 80102 && dataTable.heroTemp[i].TB != 80103 &&
            dataTable.heroTemp[i].TB != 80104 && dataTable.heroTemp[i].TB != 80105 &&
            dataTable.heroTemp[i].TB != 80107 && dataTable.heroTemp[i].TB != 80108 &&
            dataTable.heroTemp[i].TB != 80109 && dataTable.heroTemp[i].TB != 80110 &&
            dataTable.heroTemp[i].TB != 80115 && dataTable.heroTemp[i].TB != 80121 &&
            dataTable.heroTemp[i].TB != 80116 && dataTable.heroTemp[i].TB != 801162 
            ) {
            dataTable.heroTemp[i].TB = 0;
        }                  
                                           
                                           
                                           
                //方框里技能
   if (方框技能) {
   
   if(视野==257){
   if(视野方框){
                       if (dataTable.heroTemp[i].Space > 0) {
                        int intvalue = dataTable.heroTemp[i].Space;
                        string test = std::to_string(intvalue);
                        ImGui::GetForegroundDrawList()->AddText(NULL, (float)((double)(0.266777647) * map_coord.H), ImVec2((float)map_coord.X + (map_coord.H*0.6)+ (-map_coord.H*1.06f), (float)map_coord.Y - (map_coord.H*0.07f)+ (map_coord.H*0.3f)-40), Paint_red,//方框大招字体
                                      test.c_str());
                    } else {
                        

ImGui::GetForegroundDrawList()->AddLine(ImVec2((float)map_coord.X + (map_coord.H*0.7f)+ (-map_coord.H*1.17f), (float)map_coord.Y + (map_coord.H*-0.14f)+ (map_coord.H*0.3f)),
ImVec2((float)map_coord.X + (map_coord.H*0.7f)+ (-map_coord.H*0.95f), (float)map_coord.Y + (map_coord.H*-0.14f)+ (map_coord.H*0.3f)), Paint_green, 5);

ImGui::GetForegroundDrawList()->AddLine(ImVec2((float)map_coord.X + (map_coord.H*0.7f)+ (-map_coord.H*1.17f), (float)map_coord.Y + (map_coord.H*-0.14f)+ (map_coord.H*0.3f)),
ImVec2((float)map_coord.X + (map_coord.H*0.7f)+ (-map_coord.H*1.17f), (float)map_coord.Y + (map_coord.H*-0.36f)+ (map_coord.H*0.3f)), Paint_green, 5);
//方框直角

                        
                        
                        
                        
                        
                        
                        
                        
                    }
                    if (dataTable.heroTemp[i].Skill > 0) {
                        int intvalue = dataTable.heroTemp[i].Skill;
                        string test = std::to_string(intvalue);
                        ImGui::GetForegroundDrawList()->AddText(NULL, (float)((double)(0.266777647) * map_coord.H), ImVec2((float)map_coord.X + (map_coord.H*0.6)+ (-map_coord.H*0.3f)-20, (float)map_coord.Y - (map_coord.H*0.07f)+ (map_coord.H*0.3f)-40), Paint_red,//方框召唤师字体
                                      test.c_str());
                    } else {
                       // ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((float)map_coord.X + (map_coord.H*0.6)+ (-map_coord.H*0.3f), (float)map_coord.Y - (map_coord.H*0.008f)+ (map_coord.H*0.3f)), ImVec2((float)map_coord.X + (map_coord.H*0.8)+ (-map_coord.H*0.3f), (float)map_coord.Y + (map_coord.H*0.2f)+ (map_coord.H*0.3f)), Paint_red, 0); //实体方点
                   
                        ImTextureID tubiaoid;
                    if(dataTable.heroTemp[i].TB!=0){
                    if(dataTable.heroTemp[i].TB==801162){
                        tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-800000].textureId);
    
                    }else{
                    tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-80000].textureId);
    }
    
    }else{tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
    
                }
                    ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
    
ImGui::GetForegroundDrawList()->AddImage(tubiaoid!= NULL ?  tubiaoid: tubiaoid2, ImVec2((float)map_coord.X +(map_coord.H*0.16)+(map_coord.H*0.3), (float)map_coord.Y -(map_coord.H*0.16)), ImVec2((float)map_coord.X -(map_coord.H*0.16)+(map_coord.H*0.3), (float)map_coord.Y +(map_coord.H*0.16)));//方框召唤师技能
   
   
   
   }
   }
   }else{
                    if (dataTable.heroTemp[i].Space > 0) {
                        int intvalue = dataTable.heroTemp[i].Space;
                        string test = std::to_string(intvalue);
                        ImGui::GetForegroundDrawList()->AddText(NULL, (float)((double)(0.266777647) * map_coord.H), ImVec2((float)map_coord.X + (map_coord.H*0.6)+ (-map_coord.H*1.06f), (float)map_coord.Y - (map_coord.H*0.07f)+ (map_coord.H*0.3f)-40), Paint_red,//方框大招字体
                                      test.c_str());
                    } else {
                        ImGui::GetForegroundDrawList()->AddLine(ImVec2((float)map_coord.X + (map_coord.H*0.7f)+ (-map_coord.H*1.17f), (float)map_coord.Y + (map_coord.H*-0.14f)+ (map_coord.H*0.3f)),
ImVec2((float)map_coord.X + (map_coord.H*0.7f)+ (-map_coord.H*0.95f), (float)map_coord.Y + (map_coord.H*-0.14f)+ (map_coord.H*0.3f)), Paint_green, 5);

ImGui::GetForegroundDrawList()->AddLine(ImVec2((float)map_coord.X + (map_coord.H*0.7f)+ (-map_coord.H*1.17f), (float)map_coord.Y + (map_coord.H*-0.14f)+ (map_coord.H*0.3f)),
ImVec2((float)map_coord.X + (map_coord.H*0.7f)+ (-map_coord.H*1.17f), (float)map_coord.Y + (map_coord.H*-0.36f)+ (map_coord.H*0.3f)), Paint_green, 5);
//方框直角


                    }
                    if (dataTable.heroTemp[i].Skill > 0) {
                        int intvalue = dataTable.heroTemp[i].Skill;
                        string test = std::to_string(intvalue);
                        ImGui::GetForegroundDrawList()->AddText(NULL, (float)((double)(0.266777647) * map_coord.H), ImVec2((float)map_coord.X + (map_coord.H*0.6)+ (-map_coord.H*0.3f)-20, (float)map_coord.Y - (map_coord.H*0.07f)+ (map_coord.H*0.3f)-40), Paint_red,//召唤师技能字体
                                      test.c_str());
                    } else {
                       // ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((float)map_coord.X + (map_coord.H*0.6)+ (-map_coord.H*0.3f), (float)map_coord.Y - (map_coord.H*0.008f)+ (map_coord.H*0.3f)), ImVec2((float)map_coord.X + (map_coord.H*0.8)+ (-map_coord.H*0.3f), (float)map_coord.Y + (map_coord.H*0.2f)+ (map_coord.H*0.3f)), Paint_red, 0); //实体方点
                   
                        ImTextureID tubiaoid;
                    if(dataTable.heroTemp[i].TB!=0){
                    if(dataTable.heroTemp[i].TB==801162){
                        tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-800000].textureId);
    
                    }else{
                    tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-80000].textureId);
    }
    
    }else{tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
    
                }
                    ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
    
ImGui::GetForegroundDrawList()->AddImage(tubiaoid!= NULL ?  tubiaoid: tubiaoid2, ImVec2((float)map_coord.X +(map_coord.H*0.16)+(map_coord.H*0.3), (float)map_coord.Y -(map_coord.H*0.16)), ImVec2((float)map_coord.X -(map_coord.H*0.16)+(map_coord.H*0.3), (float)map_coord.Y +(map_coord.H*0.16)));//方框召唤师技能
           
                        
                        }
                        }
                }
   
                
            
                
                
                    }//血量大于0
                    
                    
                    
                    
                    
                    
                    
                       //TODO：顶上技能
            if (顶上技能) {
                float Theoffset_X = CDjs_X + SmallMapX+jinenglanzX+113;
			    float Theoffset_Y = CDjs_Y + SmallMapY+jinenglanzY-4;
                float CDdrawXY[3][2] = {
								{(float)(Theoffset_X +  intervalcdX * opop), (float)(Theoffset_Y + intervalcdY * 0)},
								{(float)(Theoffset_X +  intervalcdX * opop), (float)(Theoffset_Y + (TXdx/2) + intervalcdY * 1)},
								{(float)(Theoffset_X +  intervalcdX * opop), (float)(Theoffset_Y + TXdx + intervalcdY * 2)}
								};
								
								
								
								
								
                const float _txt_X = Theoffset_X - (TXdx * 3.6f);
                if (opop == 0) {
                    ImGui::GetForegroundDrawList()->AddText(NULL, 28.0f, ImVec2((float)_txt_X-10.0f, (float)(CDdrawXY[0][1] + (TXdx/2))), Paint_red, "");//修改大招
                  //  draw->AddText(NULL, 28.0f, ImVec2((float)_txt_X, (float)(CDdrawXY[1][1] + (TXdx/2))), Paint_red, "头像:");
                    ImGui::GetForegroundDrawList()->AddText(NULL, 28.0f, ImVec2((float)_txt_X-10.0f, (float)(CDdrawXY[2][1] + (TXdx/2))), Paint_red, "");//修改召唤师

                }
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                CDdrawXY[1][0] = CDdrawXY[1][0] + (TXdx/14.0f); // x 二次改变偏移

                CDdrawXY[0][1] = CDdrawXY[0][1] + (TXdx) + (TXdx/5.0f);
                CDdrawXY[1][1] = CDdrawXY[1][1] + (TXdx) + (TXdx/5.0f);//绘制头像
                CDdrawXY[2][1] = CDdrawXY[2][1] + (TXdx) + (TXdx/5.0f);
                /*if (0==1) //显示回城
                    local_DrawHome(draw, CDdrawXY[1][0], CDdrawXY[1][1], renderScale, color);
float aa = hp*3.6;*/
                ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {CDdrawXY[1][0] - TXdx, CDdrawXY[1][1] - TXdx}, {CDdrawXY[1][0] + TXdx, CDdrawXY[1][1] + TXdx});//顶上头像
                

                ImU32 color = ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2(CDdrawXY[1][0], CDdrawXY[1][1]), 21, ImVec2(0, 360), color, 0, 5); // 顶上白色底圆边



                
                ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2(CDdrawXY[1][0], CDdrawXY[1][1]),21, ImVec2(0, aa), 颜色配置.血量颜色,  0, 5);//顶上红色血圈边
                
                
                
                if (dataTable.heroTemp[i].Space > 0) { //绘制大招
                    int intvalue = dataTable.heroTemp[i].Space;
                    string test = std::to_string(intvalue);
                    ImGui::GetForegroundDrawList()->AddText(NULL, skills_txt_dx, ImVec2(CDdrawXY[0][0] - (TXdx/1.4), (CDdrawXY[0][1] - (TXdx/1.2))), Paint_white,test.c_str());
                } else {
                    ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2((float)CDdrawXY[0][0], (float)CDdrawXY[0][1]+23), skills_dx, Paint_green);//顶上技能颜色圆形
                 
                 
               // ImGui::GetForegroundDrawList()->AddTriangleFilled(ImVec2((float)CDdrawXY[0][0], (float)CDdrawXY[0][1]+23+1.1*skills_dx), ImVec2((float)CDdrawXY[0][0]-1.1*skills_dx, (float)CDdrawXY[0][1]+23-1.1*skills_dx), ImVec2((float)CDdrawXY[0][0]+1.1*skills_dx, (float)CDdrawXY[0][1]+23-1.1*skills_dx), Paint_green);//顶上技能颜色△三角形


                 
                 
                 
                }
                if (dataTable.heroTemp[i].Skill > 0) { //绘制召唤
                    int intvalue = dataTable.heroTemp[i].Skill;
                    string test = std::to_string(intvalue);
                    ImGui::GetForegroundDrawList()->AddText(NULL, skills_txt_dx, ImVec2(CDdrawXY[2][0] - (TXdx/1.4), (CDdrawXY[2][1] - (TXdx/1.2))), Paint_white,test.c_str());
                } else {
                   // ImGui::GetForegroundDrawList()->AddRect(ImVec2((float)CDdrawXY[2][0] - skills_dx, (float)CDdrawXY[2][1] - skills_dx), ImVec2((float)CDdrawXY[2][0] + skills_dx, (float)CDdrawXY[2][1] + skills_dx), Paint_red, skills_dx, 0, skills_dx*2);
                    
                    ImTextureID tubiaoid;
                    if(dataTable.heroTemp[i].TB!=0){
                    if(dataTable.heroTemp[i].TB==801162){
                        tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-800000].textureId);
    
                    }else{
                    tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB-80000].textureId);
    }
    }else{tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
    
                }
                    ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
    
                
                    ImGui::GetForegroundDrawList()->AddImage(tubiaoid!= NULL ?  tubiaoid: tubiaoid2, {(float)CDdrawXY[2][0] - TXdx, CDdrawXY[2][1] - TXdx}, {(float)CDdrawXY[2][0] + TXdx, CDdrawXY[2][1] + TXdx});//顶上头像
                    
                    

ImGui::GetForegroundDrawList()->AddCircle({(float)CDdrawXY[2][0], CDdrawXY[2][1]}, TXdx, IM_COL32(128, 0, 128, 255), 0, 5.0f); // 绘制紫色圆圈
                    
                    
                    
                    
           
                    
                }
                if (hp1 <= 0)
                  //  draw->AddLine(ImVec2((CDdrawXY[1][0] - TXdx), (CDdrawXY[1][1] - TXdx)), ImVec2((CDdrawXY[1][0] + TXdx), (CDdrawXY[1][1] + TXdx)), Paint_red, 10.0f);
                    ImGui::GetForegroundDrawList()->AddText(NULL, 80, ImVec2(CDdrawXY[1][0] - (TXdx/1.2)-7, CDdrawXY[1][1] - (TXdx/0.45)), Paint_red,"x");//顶上xxxxx
            }
                
                    
                    opop++;
                    
                    
                    


}





        }
    
    
    
    }
    
    
        if (上帝) {
    //上帝so = 独久->获取基址头("libil2cpp.so");
		         long sdaddr = 独久->读取指针(独久->读取指针(lil2cpp_base + 0x7770) + 0xB8) + 0x50;
            独久->write<float>(sdaddr, shangdi);
                      
                      }       
    
    
    uint64_t BuffAddress;//buff数量地址
uint64_t BxAddress;//兵线数量地址
uint64_t bxAddress;//兵线属性首位置
uint64_t Buffsl;//buff坐标数量
    

if(野怪){
    
    //              ReadZZ(ReadZZ(ReadZZ(ReadZZ(ReadZZ(ReadZZ(libbuff) + 0xf0) + 0x108) + 0x138)+0x88)+0x120)+0x0;
       long temp2 = 独久->读取指针(libGame_base + 0x3649428);
        BuffAddress = 独久->读取指针(独久->读取指针(独久->读取指针(temp2 + 0x3b0)+ 0x88)+0x120)+0x0;
        for (int i = 0; i < 21; i++) {
            dataTable.pve[i].cd = 独久->读取指针((u_long)(BuffAddress + i * 0x18)) + 0x240;
            dataTable.pve[i].maxcd = 独久->读取指针((u_long)(BuffAddress + i * 0x18)) + 0x1e4;
            dataTable.pve[i].cc = 独久->读取指针((u_long)(BuffAddress + i * 0x18));
                dataTable.pve[i].id = dataTable.pve[i].cc + 0xC0;
     dataTable.pve[i].X = dataTable.pve[i].cc + 0x2b8;
            dataTable.pve[i].Y = dataTable.pve[i].cc + 0x2c0;
        
                if (ESPMenu.是否开启共享) {
                    //共享全源数据
       // bbuff1 = Driver->读取指针(野怪数组 + i * 0x18);
       int buffid = 独久->读取整数(dataTable.pve[i].id);
      int  ygtime = 独久->读取整数(dataTable.pve[i].cd ) / 1000;
       int xxx1 = 独久->读取整数(dataTable.pve[i].X);
      int  yyy1 = 独久->读取整数(dataTable.pve[i].Y);
      float  buffx = xxx1 * rientation * WwrShare / 50000.0f + WwrShare;
      float  buffy = yyy1 * rientation * WwrShare / 50000.0f * -1 + WwrShare;
        //传输野怪数据
        creeps += std::to_string(0)
            + "," + std::to_string(ygtime)
            + "," + std::to_string(buffid)
            + "," + std::to_string(buffx + ESPMenu.野怪左右调整)
            + "," + std::to_string(buffy + ESPMenu.野怪上下调整)
            + "==";
        //传输野怪数据完毕
        }
     
        }
        
        for (int i = 0; i < 21; i++) {
            dataTable.pveTemp[i].cd = 独久->读取整数(dataTable.pve[i].cd) / 1000;
            dataTable.pveTemp[i].maxcd = 独久->读取整数(dataTable.pve[i].maxcd) / 1000;
            dataTable.pveTemp[i].coord.X = (float) 独久->读取整数(dataTable.pve[i].X);
            dataTable.pveTemp[i].coord.Y = (float) 独久->读取整数(dataTable.pve[i].Y);
            dataTable.pveTemp[i].coord.X = (float)(dataTable.pveTemp[i].coord.X * rientation * Wwra / 50000.0f + Wwra);
            dataTable.pveTemp[i].coord.Y = (float)(dataTable.pveTemp[i].coord.Y * rientation * Wwra / 50000.0f  * -1 + Wwra);
        }
        if(1==1){
            for (int i = 0; i <21; i++) {
                
                if(dataTable.pveTemp[i].cd ==90||dataTable.pveTemp[i].cd == 70||dataTable.pveTemp[i].maxcd >90||dataTable.pveTemp[i].maxcd ==60||dataTable.pveTemp[i].cd ==0){
                    continue;}
                if(dataTable.pveTemp[i].cd !=90||dataTable.pveTemp[i].cd !=70) {
                    
                    int intvalue = dataTable.pveTemp[i].cd;
                    string test = std::to_string(intvalue);
                    ImGui::GetForegroundDrawList()->AddText(NULL, 25.0f, ImVec2((float) (dataTable.pveTemp[i].coord.X +SmallMapX - 6.0+94),(float) (dataTable.pveTemp[i].coord.Y +SmallMapY - 7.9+7)),ImColor(255, 255, 255),test.c_str());
                }
            }
            
        }
	}
	
	
	
	int bingx,bingy;
if(兵线){
    
    int number;//兵线数量
    
    long temp5 = 独久->读取指针(libGame_base + 0x379F620);
    BxAddress = 独久->读取指针(独久->读取指针(temp5 + 0x138) + 0x108);
    number = 50;
    
    
    long cont = 0;
    for (int l = 0; l < number; l++){
        bxAddress = 独久->读取指针(BxAddress +( l * 0x18));
        int temp = 独久->读取整数(bxAddress + 0x3c);
        if (temp == foeComp) {
        int bxxl = 独久->读取整数(独久->读取指针(bxAddress + 0x160)+0x98);

                dataTable.CeTemp[cont].coord.X = (float) 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bxAddress +0x2b8 )+ 0x30) + 0x10) + 0x0);
                dataTable.CeTemp[cont].coord.Y = (float) 独久->读取整数(独久->读取指针(独久->读取指针(独久->读取指针(bxAddress +0x2b8 )+ 0x30) + 0x10) + 0x8);
                if (dataTable.CeTemp[cont].coord.X == 0 || dataTable.CeTemp[cont].coord.Y == 0) {continue;}
                int 兵线X   = dataTable.CeTemp[cont].coord.X * rientation * bxWwra / 50000.0f + bxWwra;
                int 兵线Y= dataTable.CeTemp[cont].coord.Y * rientation * bxWwra / 50000.0f * -1 + bxWwra;
                
                 if (bxxl<=0) {continue;}
                dataTable.CeTemp[cont].coord.X = dataTable.CeTemp[cont].coord.X * rientation * Wwra / 50000.0f + Wwra;
                dataTable.CeTemp[cont].coord.Y = dataTable.CeTemp[cont].coord.Y * rientation * Wwra / 50000.0f * -1 + Wwra;
                
               if (ESPMenu.是否开启共享) {
                
                    
                  //定义传输兵线
                bingx = 兵线X * 0.7;
                bingy = 兵线Y * 0.7;
                soldier += std::to_string(bingx + ESPMenu.兵线左右调整) + "," + std::to_string(bingy + ESPMenu.兵线左右调整) + "," + std::to_string(temp) + "==";
               }
                cont++;
            
        }
    }
    dataTable.xbsl = cont;
    
    
    
    
            for(int i = 0; i < dataTable.xbsl;i++){
                float x = dataTable.CeTemp[i].coord.X + SmallMapX+94;
                float y = dataTable.CeTemp[i].coord.Y + SmallMapY+7;
                ImGui::GetForegroundDrawList()->AddRect(ImVec2((float)x - soldiers_dx, (float)y - soldiers_dx), ImVec2((float)x + soldiers_dx, (float)y + soldiers_dx), Paint_red, soldiers_dx, 0, soldiers_dx*2);
            }
        }
    
    
    
    
	    if (ESPMenu.是否开启共享) {
        gameDataStr = "gameData" + 设备id + "[==][==]" + character + "---" + creeps + "---" + soldier;
        char* gameData = (char*)gameDataStr.data();  //设备
        send(socket_fd, gameData, strlen(gameData), 0);
    }
    
    

    
}

