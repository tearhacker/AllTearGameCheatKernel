#include <draw.h>
#include "头文件/函数.h"
#include "头文件/定函数.h"
#include "头文件/源码库.hpp"
#include "头文件/布局.h"
#include "头文件/触摸自瞄.hpp"
pid_t get_name_pid(char* name) {
    FILE* fp;
    pid_t pid;
    char cmd[0x100] = "pidof ";

    strcat(cmd, name);
    fp = popen(cmd,"r");
    fscanf(fp,"%d", &pid);
    pclose(fp);
    return pid;
}//泪心 github tearhacker  电报 t.me/TearGame

int DrawInt()
{
    
    pid = getPID("com.tencent.tmgp.cf");   
    if (pid <= 0){
    printf("绘制线程异常终止：获取游戏进程失败！(如确定游戏已运行那 就划掉后台反复开绘制测试)");
    exit(0);
    }//泪心 github tearhacker  电报 t.me/TearGame
    
    基址头 =GetModuleBase("libil2cpp.so",1);
  //  基址头2 = 获取基址头((char*)"libunity.so");
    return 0;
}


void DrawPlayer(ImDrawList *画图)
{
    py = screen_y/2;
    px = screen_x/2;
	float top,right,left,bottom,XLX,MIDDLE;
    if (DrawIo[20])       
    {         
    画图->AddRect({px - NumIo[3],py - NumIo[3]},{px + NumIo[3],py +NumIo[3]},红色);
    }   
	
	if (DrawIo[21])
    {	
    画图->AddRectFilled({0,0}, {px*2, py*2},ImColor(0,0,0,110));
    std::string ssf;  
    ssf += "触摸位置";
    auto textSize = ImGui::CalcTextSize(ssf.c_str(), 0, 25);
    画图->AddRectFilled({NumIo[6] - NumIo[7]/2, py*2 - NumIo[5] + NumIo[7]/2}, {NumIo[6] + NumIo[7]/2, py*2 - NumIo[5] - NumIo[7]/2},ImColor(255,0,0,120)); 
	画图->AddText(NULL,32,{NumIo[6] - (textSize.x / 2),py*2 - NumIo[5]},ImColor(255,255,255),ssf.c_str());                                                   
    }  //泪心 github tearhacker  电报 t.me/TearGame
    
    矩阵 = 读取指针(读取指针(读取指针(读取指针(读取指针(基址头+0xB939688) + 0x480) + 0xA0) + 0x10) + 0x10) + 0x310;
   // 数组 = 读取指针(读取指针(读取指针(读取指针(读取指针(基址头+0xAB18AC8)+0xA0)+0x30) + 0x10)+0x10);  
    数组 = 读取指针(读取指针(读取指针(读取指针(读取指针(读取指针(基址头 + 0xBAC29C8) + 0xA0) + 0x0) + 0x30) +0x28) + 0x70) + 0x10;
    对象阵列 = 数组+0x20;
   // 自身对象 = 读取指针(读取指针(读取指针(读取指针(读取指针(读取指针(基址头2 + 0x138E798) + 0x70) + 0x20)+ 0xA0)+ 0xB8)+ 0x60);
	自身队伍 = 2;
	if (DrawIo[1]){
	if(NumIo[49]==0){
    自身队伍 = 1;	
	}else if(NumIo[49]==1){
	自身队伍 = 2;		
	}
	}
	
	
    memset(matrix, 0, 16);
    vm_readv(矩阵, matrix, 16 * 4);
	人物数量=0;
    瞄准数量=0;
    for (int i = 0; i <15; i++)
    {
        对象指针 = 读取指针(对象阵列 + 8 * i);
            int  jgtpd = 读取整数(读取指针(对象指针 + 0x420) + 0x40);
   if(jgtpd == 1)
    {
      自身对象=对象指针;
    }//泪心 github tearhacker  电报 t.me/TearGame
    
        long int zjzzc = 读取指针(读取指针(读取指针(自身对象 + 0x3F8) + 0x20) + 0x10);
		long int zzc = 读取指针(读取指针(读取指针(对象指针 + 0x3F8) + 0x20) + 0x10);

        
        Vector3A 自身;
        vm_readv(zjzzc+0x324,&自身,sizeof(自身));
        Vector3A 敌人;
        vm_readv(zzc+0x324,&敌人,sizeof(敌人)); // 对象坐标      
		camera = matrix[3] * 敌人.X + matrix[7] * 敌人.Z + matrix[11] * 敌人.Y + matrix[15];
	    r_x = px + (matrix[0] * 敌人.X + matrix[4] * (敌人.Z) + matrix[8] * 敌人.Y + matrix[12]) / camera * px;	// 视角高
	    r_y = py - (matrix[1] * 敌人.X + matrix[5] * (敌人.Z + 0.5) + matrix[9] * 敌人.Y + matrix[13]) / camera * py;	// ;视角宽
	    r_w = py - (matrix[1] * 敌人.X + matrix[5] * (敌人.Z + 1.5) + matrix[9] * 敌人.Y + matrix[13]) / camera * py;							  
        X = r_x - (r_y - r_w) / 4;
        Y = r_y;
        W = (r_y - r_w) / 2;
		float XLX = r_x - (r_y - r_w) / 85;
        top = Y-W;
        bottom = Y+W;
		float MIDDLE = X + W/2;
        left = MIDDLE-(W/2);
        right = MIDDLE+(W/2);
		float pmjl = sqrt(pow(r_x - px, 2) + pow(r_y - py, 2));
        double 距离 =sqrt(pow(敌人.X - 自身.X, 2) + pow(敌人.Z - 自身.Z, 2) + pow(敌人.Y - 自身.Y, 2));
        
	    自身阵营=读取整数(读取指针(自身对象+0x420)+0x100);
        对象阵营=读取整数(读取指针(对象指针+0x420)+0x100);
        人物血量 =读取浮点数(对象指针 + 0x68)/(100.0f)*100;     
       
        if (自身阵营 == 对象阵营)
        {
           continue;
        }//泪心 github tearhacker  电报 t.me/TearGame
		
        if (对象阵营 <= 0)
        {
           continue;
        }      
		
        if (人物血量== 0)
        {
          continue;
        }//泪心 github tearhacker  电报 t.me/TearGame
		
		if (人物血量 < 0)
		{
		  continue;
		}//泪心 github tearhacker  电报 t.me/TearGame
		
		getUTF8(名字, 读取指针(读取指针(对象指针 + 0x428)+0x70)+0x14);
		
	
        if (W>0){
        if (DrawIo[20]){
        瞄准[瞄准数量].瞄准目标=敌人;
        瞄准[瞄准数量].自身目标 = 自身;
        瞄准[瞄准数量].判断距离 = 距离;
        瞄准[瞄准数量].准心最近距离 = sqrt(pow(px - r_x,2)+pow(py-(Y - W/1.5),1));
        //预瞄点👇
        画图->AddCircleFilled({px, py}, {3},白色);
        if(获取目标()==瞄准数量){       
	    DrawLine(px,py,MIDDLE,Y+W/2-20, 1.0f,0,1.0f,0.8f,3);
        }    
        瞄准数量++;
        }
        }
        if (W>0){
        if (DrawIo[10]){//这里表示DrawIo[10]	为ID对应的是透视启动键 然后他这个控号写在这些绘图外面，也就是包括绘图代码函数，所以这个代码控制下面这些绘图，也就是总开关
        
        if (DrawIo[1]){//这个是射线的开关ID
		ImGui::GetForegroundDrawList()->AddLine({px,px}, {MIDDLE, bottom},白色, {0.1});//射线画笔了
        }
        if (DrawIo[3]){//这个是方框的控制ID
		DrawRect(left,top,right,bottom,RectColor, 0, 2.2f);//这个是方框的画笔,RectColor是一个函数名他调用的是定义好的颜色变量
		}
        if (DrawIo[2]){
	    DrawRectFilled(X-5,Y+W-((Y+W)-(Y-W))*人物血量/100,X-10,Y+W,1.0f,0.86f,1.0f,1.0f);//血量画笔Y+后面这个1.0.086.1.0.1.0f是颜色代码，你可以自己去找相关的，网上可以查到
		}
        if (DrawIo[4]){
		std::string s;
		s += std::to_string((int)距离);s += "m";//这里是输出距离
		auto textSize = ImGui::CalcTextSize(s.c_str(), 0, 28.f);
	    ImGui::GetForegroundDrawList()->AddText(NULL, 25.f, {MIDDLE - 15, top - 45},白色, s.c_str());//画笔，白色也是函数名定义颜色变量
        
        //下面为名字的绘图
        char extra[250];
        sprintf(extra,"%s",名字);//输出名字
	    ImGui::GetForegroundDrawList()->AddText(NULL, 25.f, {MIDDLE - 30, top - 45},白色, extra);//名字画笔	  
        }
        //如果你想把名字和距离自己用用自己的一个开关，你就需要在上面标注的字体上面 加一个括号
        //然后名字绘图这里要添加一个if (你的控件ID){ 半边括号就行了 因为你下面已经有一个括号了 多一个就会报错了
        
       /*
        例子就是 if (控件ID){
         括号之间写你的事件   
        }       
              
        }*/
		}
        }//绘图区
		人物数量++;
		
}
        全部数量=瞄准数量;
        char extras[250];
        sprintf(extras, "PlayerCount:%d", 人物数量);
	    绘制字体描边(35.0f, px-100,140.0f, 白色, extras);   
}
