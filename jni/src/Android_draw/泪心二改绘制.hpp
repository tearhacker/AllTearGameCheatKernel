//QQ2254013571开发绘制
//QQ2254013571
#include "include.h"

char imei[100] = "";//leixin666
//初始化游戏成功！
        //int 视野;
        //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
        
//关于启动功能需要的变量  临时变量值
float  godvalue = 1.7;
int block = 0;
int block2=0;
int tequan = 0;
int game = 0;
int fbl;	
int cnm_x,cnm_y;
long int BoxArray;

int 数量;
float 数量选择;        
long rotatingdraw=0;//回城
int 斩杀HP,dist;
long coorpage = 0; 
    long coor;    
    long page;     
    long x;        
    long y;        
    

  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 

void DrawInt() {
	
    // pid = getPID("com.tencent.tmgp.sgame");
   
	
	
	
   libGame_base = driver->getModuleBase((char*) "libGameCore.so");
   lil2cpp_base = driver->getModuleBase((char*)"libil2cpp.so");

        lil2cpp_basebss =getbss(pid,(char*)"libil2cpp.so"); //getallmo(pid,(char*)"libil2cpp.so",3)+0x84A1000;    //driver->getModuleBase("libil2cpp.so");    
    libGame_basebss=getbss(pid,(char*)"libGameCore.so"); //getallmo(pid,(char*)"libGameCore.so",2)+0x1EFE000;    //driver->getModuleBase("libil2cpp.so");                       
  
         //  libunity_basebss = libunity_base + 0x1330000;
	yxpx = screen_x;//screen_x
	yxpy = screen_y;//screen_y
}


void  获取矩阵()
{
//  矩阵0x471240  
    //0xB8  0x0   0x10  0x128       0x3E90D8+0xB8+0x0+0x10+0x100
    long temp = driver->read<uint64_t>(lil2cpp_basebss + 0x3E90D8);//8F547A8
    MatrixAddress = driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(temp + 0xB8) + 0x0) + 0x10) + 0x100;
    isGames = driver->read<float>(MatrixAddress);
    //判断敌方阵营id
    /*  ?  :   三目运算符  如果大于0就返回2 否则返回1 */
    foeComp = isGames > 0 ? 2 : 1;
    //LOGE("foeComp:%d",foeComp);
    //判断阵营，获取算法，判断方向
    rientation = foeComp == 1 ? -1 : 1;
    
        for (int i = 0; i < 16; i++)
        {
        
            dataTable.Matrix[i] = driver->read<float>(MatrixAddress + i * 4);
        }
} 
   int 本人X, 本人Y, 本人CD, 本人ID,人物大招最大CD;
void DrawPlayer()
{

    const float TXdx = yxpy * 0.017534f; //(头像)圈大小(22.5)半径
    const float soldiers_dx = yxpy * (double)0.001851851851851851; //(兵)大小(2.0f)半径
    const float CDjs_X = yxpx * 0.337250f; //绘制cd起
    const float CDjs_Y = yxpy * 0.006481f; //绘制cd起点Y(7)
    const float intervalcdX = yxpx * 0.025200f; //60(cd左右间隔)
    const float intervalcdY = yxpy * 0.032407f; //35(cd上下间隔)
    const float skills_dx = yxpy * (double)0.006481481481481481;
    const float skills_txt_dx = skills_dx * 4.0f;    //技能CD文字大小
   //  Wwra=yxpy / 10.2f * (1.574074075+(jiange*0.01));   // 间隔
           Wwra=yxpy / 10.2f * (1.874074075+(jiange*0.01));   // 间隔
                //设置五个头像对齐地图方式方法
    Wwr2 = 2400/2/11.2f*1.574074075;
    
        //共享王者启动传输内容
    //共享绘制房间号imei手机标识符
    
    FILE* fpp = popen("getprop ro.serialno", "r");
    read_line_without_newline(fpp, imei, sizeof(imei));
    pclose(fpp);
    std::string 设备id = imei;
    std::string gameDataStr = "";
    std::string character = "";// "不能动";
    std::string creeps = "";
    std::string soldier = "";
    pxx = ESPMenu.分辨率X / 2;//2712和1220
    pyy = ESPMenu.分辨率Y / 2;
    WwrShare = pxx / 11.2f * 1.574074075;
    float bingxianwwra=1440 / 10.2f * (1.574074075+(jiange*0.01));   // 间隔
    
    获取矩阵();
    /*
 对局判断0层  libGameCore.so:bss|0x18885c
矩阵5层  libil2cpp.so:bss[1][Cb]+0x3E90D8+0xB8+0x0+0x10+0x100
英雄血量7层  libGameCore.so:bss[1][Cb]+0x158918+0x238+0x0 数组遍历0x18*i  +0x168+0x98
英雄大招CD7层  libGameCore.so:bss[1][Cb]+0x1587E8+0x260+0x28+0x150+0x108+0xF8+0x3C
英雄二技能CD7层  ibGameCore.so:bss[1][Cb]+0x158638+0x3B0+0x248+0x150+0xF0+0xF8+0x3C
英雄一技能CD7层  libGameCore.so:bss[1][Cb]+0x158918+0x238+0x0+0x150+0xD8+0xF8+0x3C
英雄闪现7层  libGameCore.so:bss[1][Cb]+0x1589D0+0x2B0+0x150+0x150+0xF8+0x3C
英雄本身坐标5层  libGameCore.so:bss[1][Cb]+0x1587E8+0x260+0x28+0x248+0x10+0x0+0x10+0x0
蓝buff血量7层  libGameCore.so:bss[1][Cb]+0x158640+0x380+0x200+0x258+0x398+0x168+0x98
蓝buff实时坐标7层  libGameCore.so:bss[1][Cb]+0x158918+0x360+0x0+0x230+0x10+0x0
蓝buff实时CD7层  libGameCore.so:bss[1][Cb]+0x158918+0x320+0xC0+0x138+0x28+0x190+0x48+0x240
蓝buff固定CD7层  libGameCore.so:bss[1][Cb]+0x103D98+0x88+0x28+0x10+0x3B0+0x350+0x10+0x1E4
小兵坐标7层  libGameCore.so:bss[1][Cb]+0x103D98+0x20+0x198+0x308+0xE8+0x230+0x10+0x0
小兵血量7层  libGameCore.so:bss[1][Cb]+0x158918+0x2E0+0x18+0x328+0x330+0x0+0x168+0x98
上帝视角3层  libil2cpp.so:bss[1][Cb]+0x4DB0+0xB8+0xA0
*/

//0x158918+0x238+0x0 数组遍历0x18*i  +0x168+0x98
    long temp1 = driver->read<uint64_t>(libGame_basebss +  0x3F5828);
    long bingxiang1 = temp1 + 0x238;
    本人ID=driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang1)+0x68)+0x30);

    AroundNumbers =10;

int opop=0;
    

  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
    //共享传输变量
    int herealx, herealy;int zyz, hcc;
    if( /* libGame_basebss +0x18885c ==1 */  1  )
{
        for (int i = 0; i < AroundNumbers; i++)
        {
            int ndh = i * 0x18;//人物结构体  数组 集合  0 1 2  3  0-10
    
    
long bingxiang6 =driver->read<uint64_t>(driver->read<uint64_t>(bingxiang1) + i * 0x18);

long bingxiang8 = driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(libGame_basebss +0x1e2f0) +0x0)+0x10)+0x0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
//自身视野  漏256搜索  隐藏视野 257  ca内存


        if( 惩戒 || 斩杀 ){
         //所有英雄只为遍历正确值
       int nid= driver->read<int>(bingxiang6 + 0x30);
       //自身英雄数据获取代码段
        if (nid == 本人ID){
                    本人X= (float)driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x248) + 0x10) + 0x0) + 0x60) + 0x0);   //y坐标0x248+0x10+0x0+0x10+0x0
                    本人Y= (float)driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x248) + 0x10) + 0x0) + 0x60) + 0x8);   //y坐标    
                    本人CD=driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x148) + 0x150) + 0x100) + 0xD4) / 8192000;                  //技能技能0x148) + 0x150) + 0x100) + 0xD4
            }
        }
           
               
                    
        int pand = 1;
        
        if (pand > 0)
            {

    int zhengxing = driver->read<int>(bingxiang6 + 0x3c);
    
    
   //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
                    
                    

if(zhengxing==foeComp){


                    //英雄 结构体  直接 血量 id 技能  大招 召唤师  冷却  坐标
                    //野怪结构体  时间  id   固定坐标    实体层 第二层结构体  血量 实时坐标 野怪动一下 这个坐标变动  
        // //////头像id↓代码
                dataTable.heroTemp[i].Id = driver->read<int>(bingxiang6 + 0x30);
        dataTable.heroTemp[i].Hp = driver->read<int>(driver->read<uint64_t>(bingxiang6 + 0x168) + 0xA8);    // 当前血量
        dataTable.heroTemp[i].MaxHp = driver->read<int>(driver->read<uint64_t>(bingxiang6 + 0x168) + 0xB0);  //最大血量
        dataTable.heroTemp[i].coord.X = (float) driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 +0x248) +0x10)+0x0)+0x60)+0x0);    //x坐标0x248+0x10+0x0+0x10+0x0
		dataTable.heroTemp[i].coord.Y = (float) driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 +0x248) +0x10)+0x0)+0x60)+0x8);    //y坐标
			//	0x150+0x108+0xF8+0x3C  英雄三技能
    人物大招最大CD = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x150) + 0x108) + 0xF8) + 0x3C) / 8192000;                   //技能
        dataTable.heroTemp[i].HC = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x148) + 0x168) + 0x180) + 0x20);
        //回城
        dataTable.heroTemp[i].Space1 = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x148) + 0xD8) + 0x100) + 0xD4) / 8192000;                  //技能0x148) + 0xD8) + 0x100) + 0xD4) 
        dataTable.heroTemp[i].TB1 = dataTable.heroTemp[i].Id * 100 + 10; //driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x148) + 0xD8) + 0x10) + 0x10);
        dataTable.heroTemp[i].Space2 = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x148) + 0xF0) + 0x100) + 0xD4) / 8192000;                  //技能0x148) + 0xF0) + 0x100) + 0xD4
        dataTable.heroTemp[i].TB2 = dataTable.heroTemp[i].Id * 100 + 20; //driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x148) + 0xF0) + 0x10) + 0x10);
        dataTable.heroTemp[i].Space3 = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x150) + 0x150) + 0xF8) + 0x3C) / 8192000;                 //  0x148) + 0x108) + 0x100) + 0xD4)
        dataTable.heroTemp[i].TB3 = dataTable.heroTemp[i].Id * 100 + 30; //driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x148) + 0x108) + 0x10) + 0x10);
        dataTable.heroTemp[i].Skill = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x150) + 0x150) + 0xF8) + 0x3C) / 8192000;                  //技能技能0x148) + 0x150) + 0x100) + 0xD4
        dataTable.heroTemp[i].TB4 = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x148) + 0x150) + 0xe0) + 0x10);//0x148) + 0x150) + 0x10) + 0x10);
        //   0x150+0x150+0xF8+0x3C  skill 召唤师技能 闪现  惩戒  精华净化  狂暴
       //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
        
              float hp1 = dataTable.heroTemp[i].Hp * 100 / dataTable.heroTemp[i].MaxHp;

    float aa = hp1*3.6;
                  //   ImColor 血量颜色;
                //     血量颜色 = ImColor(10,240,10,210);
            

        
        //触摸功能补充！！！
        if( 惩戒 || 斩杀 ){
        斩杀HP = (int)(dataTable.heroTemp[i].MaxHp-dataTable.heroTemp[i].Hp)*0.155;                  
         dist =getdistance(本人X, 本人Y, dataTable.heroTemp[i].coord.X, dataTable.heroTemp[i].coord.Y);
        }
        
           if (zhengxing == 1)
            {
                视野 = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x258) + 0x68) + 0x3C);
            }
            else {
                视野 = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang6 + 0x258) + 0x68) + 0x1C);
            }
            

                             
dataTable.DynamicData[i].coord.X = (dataTable.heroTemp[i].coord.X * rientation * Wwra / 50000.0f + Wwra);
dataTable.DynamicData[i].coord.Y = (dataTable.heroTemp[i].coord.Y * rientation * Wwra / 50000.0f * -1 + Wwra);
 
float pos_x = dataTable.DynamicData[i].coord.X + SmallMapX+94;
float pos_y = dataTable.DynamicData[i].coord.Y + SmallMapY+7;

map_coord = CalMatrixMem(dataTable.heroTemp[i].coord, dataTable.Matrix);
  map_coord.X = map_coord.X + SmallHPX;
map_coord.Y = map_coord.Y + SmallHPY;


        
                
                
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
   ImGui::GetForegroundDrawList()->AddCircleArc({pos_x, pos_y},21+xiaodituxue, ImVec2(0, aa), Paint_red,  0, 5.5f);//红色血圈
    }       
   
    
    if(地图){
                        //小头像
                        if (视野 != 1) {
                            //小头像血量
                            ImGui::GetForegroundDrawList()->AddCircleArc({ pos_x, pos_y }, 21 + xiaodituxue, ImVec2(0, 360), Paint_white, 0, 5.5f);//白底背景
                            ImGui::GetForegroundDrawList()->AddCircleArc({ pos_x, pos_y }, 21 + xiaodituxue, ImVec2(0, aa), Paint_red, 0, 5.5f);//红色血圈
                        }
                        else {
                            //小头像血量
                            ImGui::GetForegroundDrawList()->AddCircleArc({ pos_x, pos_y }, 21 + xiaodituxue, ImVec2(0, 360), Paint_white, 0, 5.5f);//白底背景
                            ImGui::GetForegroundDrawList()->AddCircleArc({ pos_x, pos_y }, 21 + xiaodituxue, ImVec2(0, aa), Paint_purple, 0, 5.5f);//红色血圈   没有视野情况

                        }
                        ImGui::GetForegroundDrawList()->AddImage(handId != NULL ? handId : 0, { (int)pos_x - TXdx - touxiangdaxiao, (int)pos_y - TXdx - touxiangdaxiao }, { (int)pos_x + TXdx + touxiangdaxiao, (int)pos_y + TXdx + touxiangdaxiao });

}

    if(射线){         
                        if (视野 == 1) {
                            //ImGui::GetForegroundDrawList()->AddLine(ImVec2(yxpx/2, yxpy/2), ImVec2(map_coord.X, map_coord.Y + (-map_coord.H*1.0f)), Paint_purple, 0.5f);//没有射线情况
                        }
                        else {
                            ImGui::GetForegroundDrawList()->AddLine(ImVec2(yxpx / 2, yxpy / 2), ImVec2(map_coord.X, map_coord.Y + (-map_coord.H * 1.0f)), Paint_touming, 0.3f);
                        }
           }               
                    
                    
            //Touch::Down Up Move  Down   
                                   //添加自动斩杀
      if(斩杀&&dist<5000 && 斩杀HP>dataTable.heroTemp[i].Hp &&本人CD==0){                    
                             Touch::Down((float)(screen_y-召唤师技能触发坐标.y), (float)召唤师技能触发坐标.x);
                             usleep(500);
                             Touch::Up();
                          }     
                          
                            //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
                          if(自身判断){

   if(zhengxing==2){
				 自身视野 = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang8 + 0x258) + 0x68)+0x3c);
				}else{
				 自身视野 = driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(bingxiang8 + 0x258) + 0x68)+0x1c);
				}


	if(自身视野 ==257) {
	/*
        ImTextureID tear1;
      tear1=  reinterpret_cast<ImTextureID>(贴图1.头像[0].textureId);
            ImGui::GetForegroundDrawList()->AddImage( tear1,ImVec2{100, 100}, ImVec2{0, 0}, ImVec2{1, 1});
               ImGui::Image(offButton.textureId, ImVec2{100, 100}, ImVec2{0, 0}, ImVec2{1, 1});
	    */
         ImGui::GetForegroundDrawList()->AddText(ImVec2(屏幕x, 屏幕y), Paint_red, "      [暴露]");
}
else{
    /*
        ImTextureID tear21;
      tear21=  reinterpret_cast<ImTextureID>(贴图1.头像[7].textureId);
        //    ImGui::GetForegroundDrawList()->AddImage( tear21,{ ImVec2(屏幕x, 屏幕y) } ,{ ImVec2(屏幕x, 屏幕y) });
        ImGui::GetForegroundDrawList()->AddImage( tear21,ImVec2{100, 100}, ImVec2{0, 0}, ImVec2{1, 1});
           */
       ImGui::GetForegroundDrawList()->AddText(ImVec2(屏幕x, 屏幕y), Paint_green, "      [安全]");
}
   }
   
   
  //   if (视野 != 1) {}else{
   
   if(方框){      
   
                                       //百分比30方框判断
  float current_hp_per = (float)dataTable.heroTemp[i].Hp / (float)dataTable.heroTemp[i].MaxHp;
          if (current_hp_per > 0.35f){
// 绘制外部方框
ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), Paint_white, 0.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(155, 155, 155, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), Paint_red,  0, 5.5f);//红色血圈
                    
                    }else{
                    
                    
                    ImGui::GetForegroundDrawList()->AddRect(ImVec2((int)map_coord.X - (map_coord.H*0.5f), (int)map_coord.Y - (map_coord.H*1.32f)), ImVec2((int)map_coord.X + (map_coord.H*0.5), (int)map_coord.Y + (map_coord.H*0.2f)), Paint_red, 0.0f, 0, 2.0f); //方框[ ]

// 绘制内部方框，覆盖外部方框
ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((int)map_coord.X - (map_coord.H*0.5f) + 2.0f, (int)map_coord.Y - (map_coord.H*1.32f) + 2.0f), ImVec2((int)map_coord.X + (map_coord.H*0.5f) - 2.0f, (int)map_coord.Y + (map_coord.H*0.2f) - 2.0f), ImColor(255, 0, 0, 78));//方框内部填充

//在方框内部绘制斜线网格线


   
   //方框里头像
       ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {(int)map_coord.X - (map_coord.H*0.2f), (int)map_coord.Y - (map_coord.H*0.2f)+ (-map_coord.H*1.0f)}, {(int)map_coord.X + (map_coord.H*0.2f), (int)map_coord.Y + (map_coord.H*0.2f)+ (-map_coord.H*1.0f)});
         
       
       //方框里血量
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X,(int) map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, 360), Paint_white,  0, 5.5f);//白底背景
                    ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2((int)map_coord.X, (int)map_coord.Y+ (-map_coord.H*1.0f)),(map_coord.H*0.22f)>0 ? (map_coord.H*0.22f) : 1, ImVec2(0, aa), Paint_red,  0, 5.5f);//红色血圈
                    
                    }

    }               
    

                                  
                                           
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
   if (框技) {
                
                        /*                                                                     //英雄大招 
                                if (dataTable.heroTemp[i].Space3 > 0) {                             int intvalue = dataTable.heroTemp[i].Space3;
                                string test = std::to_string(intvalue);

                                ImGui::GetForegroundDrawList()->AddText(
                                NULL, (float)((double)(0.25) * map_coord.H), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.20f)), Paint_red,
                                test.c_str()); //大招计时
                                } else {                                

                                ImGui::GetForegroundDrawList()->AddRectFilled(
                                ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.15)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.15)),
                                Paint_red, 0); //实体方点
                                                               //第4个参数 控制长度高度  竖   第一个参数小数为横  宽度   
                                                               //第三个参数   控制宽度  横
                                                                 //第的二个参数  第二个小数控制 竖 高度                 
                                }






                                //英雄二技能 
                                if (dataTable.heroTemp[i].Space2 > 0) {                             
                                //二技能倒计时
                                int intvalue = dataTable.heroTemp[i].Space2;
                                string test = std::to_string(intvalue);

                                ImGui::GetForegroundDrawList()->AddText(
                                NULL, (float)((double)(0.25) * map_coord.H), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.58f)), Paint_green,
                                test.c_str()); //大招计时
                                } else {
                                

                                
                                ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.5)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.5)),
                                Paint_green, 0); //实体方点                                                           
                                }



                                                           //英雄一技能 
                                if (dataTable.heroTemp[i].Space1 > 0) {
                                
                                //一技能倒计时
                                int intvalue = dataTable.heroTemp[i].Space1;
                                string test = std::to_string(intvalue);

                                ImGui::GetForegroundDrawList()->AddText(
                                NULL, (float)((double)(0.25) * map_coord.H), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.93f)), Paint_green,
                                test.c_str());
                                } else {
                                
                                ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.85)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.85)),
                                    Paint_green, 0); //实体方点
                                //绘制点点
                                }

*/
                                                                      //召唤师技能 
                           
                           
                        if (dataTable.heroTemp[i].Skill > 0) {

                            ImTextureID tubiaoid;
                            if (dataTable.heroTemp[i].TB4 != 0) {
                                if (dataTable.heroTemp[i].TB4 == 801162) {
                                    tubiaoid = reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4 - 800000].textureId);
                                }
                                else {
                                    tubiaoid = reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4 - 80000].textureId);
                                }
                            }
                            else {
                                tubiaoid = reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }

                            ImTextureID tubiaoid2 = reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                            ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid != NULL ? tubiaoid : tubiaoid2,
                                ImVec2((float)map_coord.X - (map_coord.H * 0.16) + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 0.16) - (map_coord.H * 1.2)),
                                ImVec2((float)map_coord.X + (map_coord.H * 0.16) + (map_coord.H * 0.95), (float)map_coord.Y + (map_coord.H * 0.16) - (map_coord.H * 1.2)));


                            //绘制黑色背景
                            float circleRadius = map_coord.H * 0.16f;
                            ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 1.2));
                            ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                            ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);

                            // 召唤师技能cd倒计时
                            int intvalue = dataTable.heroTemp[i].Skill;
                            string test = std::to_string(intvalue);

                            ImGui::GetForegroundDrawList()->AddText(
                                NULL, (float)((double)(0.25) * map_coord.H),
                                ImVec2((float)map_coord.X + (map_coord.H * 0.6) - (-map_coord.H * 0.25f), (float)map_coord.Y - (map_coord.H * 0.07f) - (map_coord.H * 1.23f)), Paint_white,
                                test.c_str());
                        }
                        else {
                            // 召唤师cd完成
                            ImTextureID tubiaoid;
                            if (dataTable.heroTemp[i].TB4 != 0) {
                                if (dataTable.heroTemp[i].TB4 == 801162) {
                                    tubiaoid = reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4 - 800000].textureId);
                                }
                                else {
                                    tubiaoid = reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4 - 80000].textureId);
                                }
                            }
                            else {
                                tubiaoid = reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                            }

                            ImTextureID tubiaoid2 = reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                            ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid != NULL ? tubiaoid : tubiaoid2,
                                ImVec2((float)map_coord.X - (map_coord.H * 0.16) + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 0.16) - (map_coord.H * 1.2)),
                                ImVec2((float)map_coord.X + (map_coord.H * 0.16) + (map_coord.H * 0.95), (float)map_coord.Y + (map_coord.H * 0.16) - (map_coord.H * 1.2)));
                        }
                    
                    
                    
                    
                                                                    //英雄大招 
                                if (dataTable.heroTemp[i].Space3 > 0) {

                                // 绘制大招
                                ImTextureID tubiaoid;
                                if(dataTable.heroTemp[i].TB3!=0){
                                if(dataTable.heroTemp[i].TB3==801162){
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB3-800000].textureId);
                                }else{
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB3-0].textureId);
                                }
                                }else{
                                tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                }

                                ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                                //绘制大招图片
                                ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                                ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.15)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.15)));


                                //绘制黑色背景
                                float circleRadius = map_coord.H * 0.16f;
                                ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 0.15));
                                ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                                ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);

                                int intvalue = dataTable.heroTemp[i].Space3;
                                string test = std::to_string(intvalue);

                                ImGui::GetForegroundDrawList()->AddText(
                                NULL, (float)((double)(0.25) * map_coord.H), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.20f)), Paint_white,
                                test.c_str()); //大招计时


                                } else {
                                ImTextureID tubiaoid;
                                if(dataTable.heroTemp[i].TB3!=0){
                                if(dataTable.heroTemp[i].TB3==801162){
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB3-800000].textureId);
                                }else{
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB3-0].textureId);
                                }
                                }else{
                                tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                }

                                ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                                ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                                ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.15)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.15)));
                                }



                                //英雄二技能 
                                if (dataTable.heroTemp[i].Space2 > 0) {

                                ImTextureID tubiaoid;
                                if(dataTable.heroTemp[i].TB2!=0){
                                if(dataTable.heroTemp[i].TB2==801162){
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB2-800000].textureId);
                                }else{
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB2-0].textureId);
                                }
                                }else{
                                tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                }
                                ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                //绘制二技能图片
                                ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                                ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.5)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.5)));

                                //绘制黑色背景
                                float circleRadius = map_coord.H * 0.16f;
                                ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 0.5));
                                ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                                ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);

                                //二技能倒计时
                                int intvalue = dataTable.heroTemp[i].Space2;
                                string test = std::to_string(intvalue);

                                ImGui::GetForegroundDrawList()->AddText(
                                NULL, (float)((double)(0.25) * map_coord.H), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.58f)), Paint_white,
                                test.c_str()); //大招计时
                                } else {
                                ImTextureID tubiaoid;
                                if(dataTable.heroTemp[i].TB2!=0){
                                if(dataTable.heroTemp[i].TB2==801162){
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB2-800000].textureId);
                                }else{
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB2-0].textureId);
                                }
                                }else{
                                tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                }

                                ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                                ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                                ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.5)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.5)));
                                }



                                //英雄一技能 
                                if (dataTable.heroTemp[i].Space1 > 0) {
                                ImTextureID tubiaoid;
                                if(dataTable.heroTemp[i].TB1!=0){
                                if(dataTable.heroTemp[i].TB1==801162){
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB1-800000].textureId);
                                }else{
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB1-0].textureId);
                                }
                                }else{
                                tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                }
                                ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                //绘制技能贴图
                                ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                                ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.85)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.85)));

                                //绘制黑色背景
                                float circleRadius = map_coord.H * 0.16f;
                                ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 0.85));
                                ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                                ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);

                                //一技能倒计时
                                int intvalue = dataTable.heroTemp[i].Space1;
                                string test = std::to_string(intvalue);

                                ImGui::GetForegroundDrawList()->AddText(
                                NULL, (float)((double)(0.25) * map_coord.H), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*0.93f)), Paint_white,
                                test.c_str());
                                } else {
                                ImTextureID tubiaoid;
                                if(dataTable.heroTemp[i].TB1!=0){
                                if(dataTable.heroTemp[i].TB1==801162){
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB1-800000].textureId);
                                }else{
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB1-0].textureId);
                                }
                                }else{
                                tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                }
                                ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                //绘制技能贴图
                                ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                                ImVec2((float)map_coord.X - (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*0.85)), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*0.85)));
                                }

                                //召唤师技能 
                                if (dataTable.heroTemp[i].Skill > 0) {

                                ImTextureID tubiaoid;
                                if(dataTable.heroTemp[i].TB4!=0){
                                if(dataTable.heroTemp[i].TB4==801162){
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4-800000].textureId);
                                }else{
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4-80000].textureId);
                                }
                                }else{
                                tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                }

                                ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                                ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                                ImVec2((float)map_coord.X -(map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*1.2)), 
                                ImVec2((float)map_coord.X +(map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*1.2)));


                                //绘制黑色背景
                                float circleRadius = map_coord.H * 0.16f;
                                ImVec2 circleCenter = ImVec2((float)map_coord.X + (map_coord.H * 0.95), (float)map_coord.Y - (map_coord.H * 1.2));
                                ImU32 circleColor = IM_COL32(0, 0, 0, 100);
                                ImGui::GetForegroundDrawList()->AddCircleFilled(circleCenter, circleRadius, circleColor);


                                // 召唤师技能cd倒计时
                                int intvalue = dataTable.heroTemp[i].Skill;
                                string test = std::to_string(intvalue);

                                ImGui::GetForegroundDrawList()->AddText(
                                NULL, (float)((double)(0.25) * map_coord.H), 
                                ImVec2((float)map_coord.X + (map_coord.H*0.6) - (-map_coord.H*0.25f), (float)map_coord.Y - (map_coord.H*0.07f) - (map_coord.H*1.23f)), Paint_white,
                                test.c_str());
                                } else {
                                // 召唤师cd完成
                                ImTextureID tubiaoid;
                                if(dataTable.heroTemp[i].TB4!=0){
                                if(dataTable.heroTemp[i].TB4==801162){
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4-800000].textureId);
                                }else{
                                tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4-80000].textureId);
                                }
                                }else{
                                tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
                                }

                                ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);

                                ImGui::GetForegroundDrawList()->AddImage(
                                tubiaoid!= NULL ?  tubiaoid: tubiaoid2, 
                                ImVec2((float)map_coord.X -(map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y -(map_coord.H*0.16) - (map_coord.H*1.2)), 
                                ImVec2((float)map_coord.X +(map_coord.H*0.16) + (map_coord.H*0.95), (float)map_coord.Y +(map_coord.H*0.16) - (map_coord.H*1.2)));
                                }
            

                
                }  //结束框技
   
          //      }
            
                
                
                    }//血量大于0
                    
    
    rotatingdraw=rotatingdraw+3;  //回城条显示
                           //TODO：顶上技能
            if (顶上技能) {
            
                    if(dataTable.heroTemp[i].HC == 1){       
ImGui::GetForegroundDrawList()->AddCircleArc({pos_x,pos_y},21+xiaodituxue,ImVec2(0+rotatingdraw,20+rotatingdraw),Paint_lightblue,9.5f,5.5f);
ImGui::GetForegroundDrawList()->AddCircleArc({pos_x,pos_y},21+xiaodituxue,ImVec2(20+rotatingdraw,40+rotatingdraw),Paint_purple,9.5f,5.5f);
ImGui::GetForegroundDrawList()->AddCircleArc({pos_x,pos_y},21+xiaodituxue,ImVec2(40+rotatingdraw,60+rotatingdraw),Paint_white,9.5f,5.5f);
     }
     
     
                float Theoffset_X = CDjs_X + SmallMapX+jinenglanzX+113;
			    float Theoffset_Y = CDjs_Y + SmallMapY+jinenglanzY-4;
                float CDdrawXY[3][2] = {
								{(float)(Theoffset_X +  intervalcdX * opop), (float)(Theoffset_Y + intervalcdY * 0)},
								{(float)(Theoffset_X +  intervalcdX * opop), (float)(Theoffset_Y + (TXdx/2) + intervalcdY * 1)},
								{(float)(Theoffset_X +  intervalcdX * opop), (float)(Theoffset_Y + TXdx + intervalcdY * 2)}
								};
								
                const float _txt_X = Theoffset_X - (TXdx * 3.6f);
                
                if (opop == 0) {
                    ImGui::GetForegroundDrawList()->AddText(NULL, 28.0f, ImVec2((float)_txt_X-10.0f, (float)(CDdrawXY[0][1] + (TXdx/2))), Paint_red, "大招:");
                  //  ImGui::GetForegroundDrawList()->AddText(NULL, 28.0f, ImVec2((float)_txt_X, (float)(CDdrawXY[1][1] + (TXdx/2))), Paint_red, "头像:");
                    ImGui::GetForegroundDrawList()->AddText(NULL, 28.0f, ImVec2((float)_txt_X-10.0f, (float)(CDdrawXY[2][1] + (TXdx/2))), Paint_red, "召唤:");

                }
                CDdrawXY[1][0] = CDdrawXY[1][0] + (TXdx/14.0f); // x 二次改变偏移

                CDdrawXY[0][1] = CDdrawXY[0][1] + (TXdx) + (TXdx/5.0f);
                CDdrawXY[1][1] = CDdrawXY[1][1] + (TXdx) + (TXdx/5.0f);//绘制头像
                CDdrawXY[2][1] = CDdrawXY[2][1] + (TXdx) + (TXdx/5.0f);
                /*if (0==1) //显示回城
                    local_DrawHome(draw, CDdrawXY[1][0], CDdrawXY[1][1], renderScale, color);
float aa = hp*3.6;*/
                ImGui::GetForegroundDrawList()->AddImage(handId!= NULL ?  handId: 0, {CDdrawXY[1][0] - TXdx, CDdrawXY[1][1] - TXdx}, {CDdrawXY[1][0] + TXdx, CDdrawXY[1][1] + TXdx});//顶上头像
                ImGui::GetForegroundDrawList()->AddCircleArc(ImVec2(CDdrawXY[1][0], CDdrawXY[1][1]),dingshanghealth, ImVec2(0, aa), Paint_yellow,  0, 5);//红色圈边
                if (dataTable.heroTemp[i].Space3 > 0) { //绘制大招
                    int intvalue = dataTable.heroTemp[i].Space3;
                    string test = std::to_string(intvalue);
                    ImGui::GetForegroundDrawList()->AddText(NULL, skills_txt_dx, ImVec2(CDdrawXY[0][0] - (TXdx/1.4), (CDdrawXY[0][1] - (TXdx/1.2))), Paint_white,test.c_str());
                } else {
                    ImGui::GetForegroundDrawList()->AddRect(ImVec2((float)CDdrawXY[0][0] - skills_dx, (float)CDdrawXY[0][1] - skills_dx), ImVec2((float)CDdrawXY[0][0] + skills_dx, (float)CDdrawXY[0][1] + skills_dx), Paint_red, skills_dx, 0, skills_dx*2);
                }
                if (dataTable.heroTemp[i].Skill > 0) { //绘制召唤
                    int intvalue = dataTable.heroTemp[i].Skill;
                    string test = std::to_string(intvalue);
                    ImGui::GetForegroundDrawList()->AddText(NULL, skills_txt_dx, ImVec2(CDdrawXY[2][0] - (TXdx/1.4), (CDdrawXY[2][1] - (TXdx/1.2))), Paint_white,test.c_str());
                } else {
                   // ImGui::GetForegroundDrawList()->AddRect(ImVec2((float)CDdrawXY[2][0] - skills_dx, (float)CDdrawXY[2][1] - skills_dx), ImVec2((float)CDdrawXY[2][0] + skills_dx, (float)CDdrawXY[2][1] + skills_dx), Paint_red, skills_dx, 0, skills_dx*2);
                    
                    ImTextureID tubiaoid;
                    if(dataTable.heroTemp[i].TB4!=0){
                    if(dataTable.heroTemp[i].TB4==801162){
                        tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4-800000].textureId);
    
                    }else{
                    tubiaoid=reinterpret_cast<ImTextureID>(技能贴图.头像[dataTable.heroTemp[i].TB4-80000].textureId);
    }
    }else{tubiaoid =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
    
                }
                    ImTextureID tubiaoid2 =reinterpret_cast<ImTextureID>(技能贴图.头像[0].textureId);
    
                
                    ImGui::GetForegroundDrawList()->AddImage(tubiaoid!= NULL ?  tubiaoid: tubiaoid2, {(float)CDdrawXY[2][0] - TXdx, CDdrawXY[2][1] - TXdx}, {(float)CDdrawXY[2][0] + TXdx, CDdrawXY[2][1] + TXdx});//顶上头像
           
                    
                }
                if (hp1 <= 0)
                  //  ImGui::GetForegroundDrawList()->AddLine(ImVec2((CDdrawXY[1][0] - TXdx), (CDdrawXY[1][1] - TXdx)), ImVec2((CDdrawXY[1][0] + TXdx), (CDdrawXY[1][1] + TXdx)), Paint_red, 10.0f);
                    ImGui::GetForegroundDrawList()->AddText(NULL, 80, ImVec2(CDdrawXY[1][0] - (TXdx/1.2)+7, CDdrawXY[1][1] - (TXdx/0.45)), Paint_red,"x");
           
            
             
               }   //顶上技能结束了
                
                      //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
                    opop++;
                    
                    
                    


}





        }
    
    
    
    } //英雄大循环结束
 
    

//传输变量  野怪传输
    int ygtime;
    int  buffid;
    int  buffx;
    int  buffy;
    long BUFFtemp;  //临时数组
    int 游戏时间;
    int xxx1, yyy1;
    int bui;
    long bbuff1;
    uint64_t BuffAddress;//buff数量地址
uint64_t BxAddress;//兵线数量地址
uint64_t bxAddress;//兵线属性首位置
uint64_t Buffsl;//buff坐标数量
int 惩戒伤害 =driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(lil2cpp_basebss + 0x3CF328)+0xB8)+0x100)+ 0x158)+0x1F4);      
   //printf("惩戒伤害%d\n",惩戒伤害); 
int maxyghp;      
if(野怪){
      long temp2 = driver->read<uint64_t>(libGame_basebss + 0x1E18);    //libGameCore.so:bss+0x1E18+0x3B8+0x88+0x120+0x18*i   从0到30   10个英雄  0 10  遍历数组  当前 第二个 第三个  当前数组(自身数组)自身结构体  英雄本身      (i*0x18)    
        BuffAddress =  driver->read<uint64_t>(driver->read<uint64_t>(driver->read<uint64_t>(temp2 + 0x3B0) + 0x88)+0x120) ;
        for (int i = 0; i < 21; i++) {
             dataTable.pve[i].cd = driver->read<uint64_t>((u_long)(BuffAddress + i * 0x18)) + 0x240;
            dataTable.pve[i].maxcd = driver->read<uint64_t>((u_long)(BuffAddress + i * 0x18)) + 0x1e4;
            dataTable.pve[i].cc = driver->read<uint64_t>((u_long)(BuffAddress + i * 0x18));
            dataTable.pve[i].id = dataTable.pve[i].cc + 0xC0;       //标识 序号
            dataTable.pve[i].X = dataTable.pve[i].cc + 0x2b8;   //固定坐标 
            dataTable.pve[i].Y = dataTable.pve[i].cc + 0x2c0;
            //实体坐标  非小地图坐标
            // 228  10  0  和8
             dataTable.pve[i].hp = driver->read<uint64_t>(driver->read<uint64_t>(dataTable.pve[i].cc + 0x3A0) + 0x168) + 0xA8;  //血量  实体层 0x168  0x98
            dataTable.pve[i].maxhp = driver->read<uint64_t>(driver->read<uint64_t>(dataTable.pve[i].cc + 0x3A0) + 0x168) + 0xB0;
              

        
        }   //第一次for循环
        
        for (int i = 0; i < 21; i++) {
            dataTable.pveTemp[i].cd = driver->read<int>(dataTable.pve[i].cd) / 1000;
            dataTable.pveTemp[i].maxcd = driver->read<int>(dataTable.pve[i].maxcd) / 1000;
            dataTable.pveTemp[i].coord.X = (float) driver->read<int>(dataTable.pve[i].X);
            dataTable.pveTemp[i].coord.Y = (float) driver->read<int>(dataTable.pve[i].Y);
            yg_coord = CalMatrixMem(dataTable.pveTemp[i].coord, dataTable.Matrix);
             dataTable.pveTemp[i].id = driver->read<int>(dataTable.pve[i].id);
             dataTable.pveTemp[i].maxhp =driver->read<int>(dataTable.pve[i].maxhp);      
             dataTable.pveTemp[i].hp = driver->read<int>(dataTable.pve[i].hp);
             
             

	
	if(野血){
	
	                     //绘制全局野怪血量
        int hpyg=dataTable.pveTemp[i].hp;
        string yggealth=std::to_string(hpyg);
        std::string s1;
				s1 += "[";
				s1 += std::to_string((int)dataTable.pveTemp[i].hp);
				s1 += "/";
				s1 += std::to_string((int)dataTable.pveTemp[i].maxhp);
				s1 += "]";
				
				
        if(dataTable.pveTemp[i].hp)
        {
  /*      ImGui::GetForegroundDrawList()->AddRect({yg_coord.X - 63, yg_coord.Y - 29}, {yg_coord.X + 59, yg_coord.Y - 17},ImColor(255, 255, 255, 255),0,0, 1.5f);
		ImGui::GetForegroundDrawList()->AddRectFilled({yg_coord.X - 62, yg_coord.Y - 28}, {yg_coord.X - 62 + (1.2f*dataTable.pveTemp[i].hp/dataTable.pveTemp[i].maxhp*100), yg_coord.Y - 18},Paint_green, 1);        
        ImGui::GetForegroundDrawList()->AddRect({yg_coord.X, yg_coord.Y}, {yg_coord.X, yg_coord.Y},ImColor(255, 255, 255, 255),0,0, 1.5f);
	*/
				
    	ImGui::GetForegroundDrawList()->AddText(NULL, 18.f, {yg_coord.X, yg_coord.Y},ImColor(255,255,0,255), s1.c_str());
        }
          //  ImGui::GetForegroundDrawList()->AddText(NULL, 30.0f, ImVec2((float)(yg_coord.X), (float)(yg_coord.Y)), Paint_green, yggealth.c_str());//野怪血量全局显示文本
       }
             
                            //惩戒野怪
                                                        if(惩戒&&dataTable.pveTemp[i].hp >0){                                                
                                                 if (dataTable.pveTemp[i].id  == 166018 ||dataTable.pveTemp[i].id  == 166012 ||  dataTable.pveTemp[i].id  == 1660221 || dataTable.pveTemp[i].id  == 166022 || dataTable.pveTemp[i].id  == 266010 || dataTable.pveTemp[i].id  == 266011){                                                                                         
                                                      int dist2 =getdistance(本人X, 本人Y, dataTable.pveTemp[i].coord.X, dataTable.pveTemp[i].coord.Y);                                                                                                                                                                                  
                                                 
                                                      if(本人CD==0&& dist2<8000 && 惩戒伤害>dataTable.pveTemp[i].hp ){
                                                      Touch::Down((float)(screen_y-召唤师技能触发坐标.y), (float)召唤师技能触发坐标.x);
                                                        usleep(500);
                                                         Touch::Up();
                                                      }
                                                       }
                                                       }  //结果结束了
                                                       
                                                       
             
             //野怪真实位置
            dataTable.pveTemp[i].coord.X = (float)(dataTable.pveTemp[i].coord.X * rientation * Wwra / 50000.0f + Wwra);
            dataTable.pveTemp[i].coord.Y = (float)(dataTable.pveTemp[i].coord.Y * rientation * Wwra / 50000.0f  * -1 + Wwra);
        }
       
            for (int i = 0; i <21; i++) {
                
                                                if(dataTable.pveTemp[i].cd == 70 || dataTable.pveTemp[i].cd == 90 || dataTable.pveTemp[i].cd == 0 || dataTable.pveTemp[i].cd == 60){
                                                    continue;
                                                }
                                                if(dataTable.pveTemp[i].cd>90){continue;}
                                                if(dataTable.pveTemp[i].cd > 0) {
                                                    int intvalue = dataTable.pveTemp[i].cd;
                                                    string test = std::to_string(intvalue);
                                                    string tests = std::to_string(intvalue+4);
                                                    
                                                if(  dataTable.pveTemp[i].id  == 266010 || dataTable.pveTemp[i].id  == 266011   )
                                                {
                                                ImGui::GetForegroundDrawList()->AddText(NULL, 26.0f, ImVec2((float) (dataTable.pveTemp[i].coord.X +monsterX - 6.0+94),(float) (dataTable.pveTemp[i].coord.Y+monsterY - 7.9+7)),Paint_red, tests.c_str());                                                   
                                                }else{                                                
                                                ImGui::GetForegroundDrawList()->AddText(NULL, 26.0f, ImVec2((float) (dataTable.pveTemp[i].coord.X +monsterX - 6.0+94),(float) (dataTable.pveTemp[i].coord.Y+monsterY - 7.9+7)),Paint_yellow,test.c_str());                                           
                                                }
                                                
                                               
                                                }
            }
            
        
	}
	
	
	
	
	
	    int bingx;
    int bingy;//兵线共享变量
    //兵线数组  抓血量  5层就够了libGameCore.so:bss[1][Cb]+0x158918+0x2E0+0x18+0x328+0x330+0x0+0x168+0x98

    long temp5 = driver->read<uint64_t>(libGame_basebss + 0x158918);

   // BxAddress = driver->read<uint64_t>(driver->read<uint64_t>(temp5 + 0x138)+0x108); //0x138 0x108  0x0    //2E0+0x0  第二种常用
            BxAddress = driver->read<uint64_t>(temp5 + 0x2E0); //0x138 0x108  0x0    //2E0+0x0  第二种常用
    long cont = 0;
    for (int l = 0; l < 50; l++) {
     bxAddress = driver->read<uint64_t>(BxAddress + ( l * 0x18));
       // int temp = driver->read<int>(bxAddress + 0x3C);
     //   int hp = driver->read<int>(driver->read<uint64_t>(bxAddress + 0x160) + 0xA0);
        dataTable.CeTemp[cont].hp =driver->read<int>(driver->read<uint64_t>(bxAddress + 0x168) + 0xA8);
        dataTable.CeTemp[cont].maxhp =driver->read<int>(driver->read<uint64_t>(bxAddress + 0x168) + 0xB0);
        dataTable.CeTemp[cont].team =driver->read<int>(bxAddress + 0x3C); //自我阵营
        dataTable.CeTemp[cont].coord.X = (float)driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(bxAddress + 0x230) + 0x60) + 0x0);//0x228) + 0xd8) + 0x10) + 0x0);
        dataTable.CeTemp[cont].coord.Y = (float)driver->read<int>(driver->read<uint64_t>(driver->read<uint64_t>(bxAddress + 0x230) + 0x60) + 0x8);
        
                            if(兵血)  //小兵实体
                {
                        if (dataTable.CeTemp[cont].hp  == 0) {}else{
                        

                                if (dataTable.CeTemp[cont].team == foeComp) {
                        
                //获取实体兵线xyz坐标
            bingxian_coord = CalMatrixMem(dataTable.CeTemp[cont].coord, dataTable.Matrix);
        std::string s1;
				s1 += "[";
				s1 += std::to_string((int)dataTable.CeTemp[cont].hp);
						s1 += "]";
					
						
						
        		ImGui::GetForegroundDrawList()->AddRect(ImVec2((float)bingxian_coord.X, bingxian_coord.Y), ImVec2(bingxian_coord.X+5, bingxian_coord.Y+5), Paint_white, soldiers_dx, 0, soldiers_dx*10);
     	
        			// ImGui::GetForegroundDrawList()->AddText(NULL, 18.f, {bingxian_coord.X, bingxian_coord.Y},ImColor(255,255,0,255), s1.c_str());
        			                      	}
        			                          }   //兵线血量不为0
			                }
        

        if (dataTable.CeTemp[cont].coord.X == 0 || dataTable.CeTemp[cont].coord.Y == 0) { continue; }
        int 兵线X = dataTable.CeTemp[cont].coord.X * rientation * bingxianwwra / 50000 + bingxianwwra;
        int 兵线Y = dataTable.CeTemp[cont].coord.Y * rientation * bingxianwwra / 50000 * -1 + bingxianwwra;

        if (dataTable.CeTemp[cont].hp  == 0) { continue; }
        if (dataTable.CeTemp[cont].team == foeComp) {

            if (dataTable.CeTemp[cont].hp  != 0)
            {
                if (dataTable.CeTemp[cont].coord.X == 0 || dataTable.CeTemp[cont].coord.Y == 0) { continue; }
                dataTable.CeTemp[cont].coord.X = dataTable.CeTemp[cont].coord.X * rientation * Wwra / 50000.0f + Wwra;
                dataTable.CeTemp[cont].coord.Y = dataTable.CeTemp[cont].coord.Y * rientation * Wwra / 50000.0f * -1 + Wwra;
                  if (ESPMenu.是否开启共享) {
                  //定义传输兵线
                bingx = 兵线X* 1.0;
                bingy = 兵线Y* 1.0;
                soldier += std::to_string(bingx + ESPMenu.兵线左右调整) + "," + std::to_string(bingy + ESPMenu.兵线左右调整) + "," + std::to_string(dataTable.CeTemp[cont].team) + "==";
               }
                 cont++;
            }
        }


    }

    if (兵线) {
        dataTable.xbsl = cont;
        for (int i = 0; i < dataTable.xbsl; i++) {
            float x = dataTable.CeTemp[i].coord.X + SmallMapX + 94;
            float y = dataTable.CeTemp[i].coord.Y + SmallMapY + 7;
            ImGui::GetForegroundDrawList()->AddRect(ImVec2((float)x - soldiers_dx, (float)y - soldiers_dx), ImVec2((float)x + soldiers_dx, (float)y + soldiers_dx), Paint_red, soldiers_dx, 0, soldiers_dx * 2);
       

			                
			                
			                
          }
    }

	
	}//绘图判断
	else{
	//绘制游戏对局等待的信息  绘制文字 图案等内容
	}
	    
    
    

}










void  封装色彩(){
ImGuiStyle& style = ImGui::GetStyle();

    // 设置背景为透明灰色
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.3f);



// 设置基础颜色
style.Colors[ImGuiCol_Text] = ImColor(0.90f, 0.90f, 0.90f, 1.00f); // 字体颜色，浅灰白色


// 边框和分隔符
style.Colors[ImGuiCol_Border] = ImColor(0.50f, 0.50f, 0.50f, 0.60f); // 边框颜色，中性灰色
style.Colors[ImGuiCol_Separator] = ImColor(0.40f, 0.40f, 0.40f, 1.00f); // 分隔符颜色，稍深的灰色

// 按钮颜色
style.Colors[ImGuiCol_Button] = ImColor(0.30f, 0.30f, 0.30f, 1.00f); // 按钮颜色，深灰色
style.Colors[ImGuiCol_ButtonHovered] = ImColor(0.40f, 0.40f, 0.40f, 0.85f); // 悬停颜色，中性灰色
style.Colors[ImGuiCol_ButtonActive] = ImColor(0.50f, 0.50f, 0.50f, 0.70f); // 点击颜色，亮灰色

// 标签页颜色
style.Colors[ImGuiCol_Tab] = ImColor(0.20f, 0.20f, 0.20f, 1.00f); // 标签颜色，深灰色
style.Colors[ImGuiCol_TabHovered] = ImColor(0.30f, 0.30f, 0.30f, 1.00f); // 悬停颜色，中性灰色
style.Colors[ImGuiCol_TabActive] = ImColor(0.40f, 0.40f, 0.40f, 1.00f); // 激活颜色，亮灰色

// 滑块、复选框和框架背景
style.Colors[ImGuiCol_FrameBg] = ImColor(0.25f, 0.25f, 0.25f, 0.90f); // 滑块背景色，较深的灰色
style.Colors[ImGuiCol_FrameBgHovered] = ImColor(0.35f, 0.35f, 0.35f, 1.00f); // 悬停背景色，较浅的灰色
style.Colors[ImGuiCol_FrameBgActive] = ImColor(0.45f, 0.45f, 0.45f, 1.00f); // 点击背景色，浅灰色
style.Colors[ImGuiCol_CheckMark] = ImColor(0.70f, 0.70f, 0.70f, 1.00f); // 复选框的√颜色，淡灰色

// 滑块颜色
style.Colors[ImGuiCol_SliderGrab] = ImColor(0.60f, 0.60f, 0.60f, 0.80f); // 滑块颜色，灰色
style.Colors[ImGuiCol_SliderGrabActive] = ImColor(0.70f, 0.70f, 0.70f, 0.90f); // 拖动时颜色，较亮的灰色

// 滚动条颜色
style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0.12f, 0.12f, 0.12f, 0.75f); // 背景颜色，深灰色
style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(0.35f, 0.35f, 0.35f, 0.85f); // 滚动条颜色，暗灰色
style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0.45f, 0.45f, 0.45f, 0.90f); // 悬停颜色，中灰色
style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0.55f, 0.55f, 0.55f, 1.00f); // 点击颜色，浅灰色

// 标题栏颜色
style.Colors[ImGuiCol_Header] = ImColor(0.30f, 0.30f, 0.30f, 1.00f); // 标题栏颜色，深灰色
style.Colors[ImGuiCol_HeaderHovered] = ImColor(0.40f, 0.40f, 0.40f, 1.00f); // 悬停颜色，中灰色
style.Colors[ImGuiCol_HeaderActive] = ImColor(0.50f, 0.50f, 0.50f, 1.00f); // 点击颜色，亮灰色

// 圆角设置
style.GrabRounding = 10.0f;
style.FrameRounding = 10.0f;
style.ScrollbarRounding = 12.0f;

// 边框和填充设置
style.FrameBorderSize = 1.0f; // 边框大小
style.WindowBorderSize = 1.0f; // 窗口边框大小
style.WindowTitleAlign = ImVec2(0.5, 0.5); // 标题居中

// 滚动条设置
style.ScrollbarSize = 18.0f;
style.ScrollbarRounding = 12.0f;
}