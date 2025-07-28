#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include<fstream>
#include<iostream>
#include <iostream>
#include<thread>
#include <linux/input.h>
#include <linux/uinput.h>

#include <pthread.h>         // for thread(多线程)
#include "draw.h"
#include "Font.h"
#include "绘图.hpp"
#include "../颜色配置/颜色配置.h"

/**
by  独久
https://t.me/dujiunb

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
static int 录屏时长 = 20; // 默认时间为10秒
static std::atomic<bool> isRecording(false); // 全局变量
static std::atomic<int> recordingTimeElapsed(0); // 录制经过的时间
bool permeate_record = false;
bool g_Initialized = false;
EGLDisplay display = EGL_NO_DISPLAY;
EGLConfig config;
EGLSurface surface = EGL_NO_SURFACE;
EGLContext context = EGL_NO_CONTEXT;
ANativeWindow *native_window;
android::ANativeWindowCreator::DisplayInfo displayInfo{0};

int screen_x = 0, screen_y = 0;
int abs_ScreenX = 0, abs_ScreenY = 0;
int native_window_screen_x = 0, native_window_screen_y = 0;
bool MenuSic = true, BallSic = true;
bool IsBall = true;
//static bool IsLoGin = true, IsDown = false, IsWin = true;
int show_ChildMenu = 0;
int 一键开启 = 0;

void CardPanel(const char* title, const ImVec2& size, const ImVec4& bgColor, float cornerRadius,float padding, const std::function<void()>& contentFunction) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, bgColor);
    
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, cornerRadius);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(padding, padding));
    ImGui::BeginChild(title, size, true);
    if (contentFunction) {
        contentFunction();
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

    
    

int init_egl(int _screen_x, int _screen_y, bool log) {
    
    // 创建一个名为"AImGui"的原生窗口，指定屏幕宽度和高度
    FILE *fp;
    char buffer[1024];

    fp = popen("settings put system block_untrusted_touches 0", "r");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("[+] 正在执行指令信任所有触摸\n[+] %s", buffer);
    }
    pclose(fp);
//system ("settings put system block_untrusted_touches 0");

system ("settings put global block_untrusted_touches 0 > /dev/null 2>&1");
system ("settings put secure block_untrusted_touches 0 > /dev/null 2>&1");


bool sgfop;
    string sfflp;
    cout << "[+] 是否开启防录屏 1[开启] 2[关闭]: ";
    
    cin >> sfflp;
    if (sfflp == "1")
        sgfop = true;
    else
        sgfop = false;
   

if (sgfop)
{
printf("[+] 防录屏开启\n");
 ::native_window = android::ANativeWindowCreator::Create("AImGui", _screen_x, _screen_y, true);
	}
	
	if (!sgfop)//关闭方露萍
{
printf("[+] 防录屏关闭\n");
	
    
native_window = android::ANativeWindowCreator::Create("Ssage", _screen_x, _screen_y, false);
	}
    

    // 增加对原生窗口的引用计数
    ANativeWindow_acquire(native_window);
    // 获取默认的显示设备
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    // 检查是否成功获取显示设备
    if (display == EGL_NO_DISPLAY) {
        printf("[+] 获取显示设备失败，错误码=%u\n", glGetError());
        return false;
    }
    // 如果需要，打印日志信息
    if (log) {
        printf("[+] 获取显示设备成功\n");
    }
    // 初始化EGL显示设备
    if (eglInitialize(display, 0, 0) != EGL_TRUE) {
        printf("[+] 初始化EGL显示设备失败，错误码=%u\n", glGetError());
        return false;
    }
    // 如果需要，打印日志信息
    if (log) {
        printf("[+] 初始化EGL显示设备成功\n");
    }
    // 定义EGL配置属性列表
    EGLint attribList[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_BUFFER_SIZE, 32,    // 设置缓冲区大小为32位
        EGL_DEPTH_SIZE, 16,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };
    // 定义EGL上下文属性列表
    EGLint num_config = 0;
    const EGLint attrib_list[] = {
        EGL_CONTEXT_CLIENT_VERSION,
        3,
        EGL_NONE
    };

    // 如果需要，打印日志信息
    if (log) {
        printf("[+] 配置数量 = %d\n", num_config);
    }
    // 选择EGL配置
    if (eglChooseConfig(display, attribList, &config, 1, &num_config) != EGL_TRUE) {
        printf("[+] 选择EGL配置失败，错误码=%u\n", glGetError());
        return false;
    }
    // 如果需要，打印日志信息
    if (log) {
        printf("[+] 选择EGL配置成功\n");
    }
    // 获取EGL配置的格式
    EGLint egl_format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &egl_format);
    // 设置原生窗口的缓冲区几何形状
    ANativeWindow_setBuffersGeometry(native_window, 0, 0, egl_format);
    // 创建EGL上下文
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, attrib_list);
    if (context == EGL_NO_CONTEXT) {
        printf("[+] 创建EGL上下文失败，错误码=%u\n", glGetError());
        return false;
    }
    // 如果需要，打印日志信息
    if (log) {
        printf("[+] 创建EGL上下文成功\n");
    }
    // 创建EGL窗口表面
    surface = eglCreateWindowSurface(display, config, native_window, nullptr);
    if (surface == EGL_NO_SURFACE) {
        printf("[+] 创建EGL窗口表面失败，错误码=%u\n", glGetError());
        return false;
    }
    // 如果需要，打印日志信息
    if (log) {
        printf("[+] 创建EGL窗口表面成功\n");
    }
    // 将EGL上下文和表面设置为当前
    if (!eglMakeCurrent(display, surface, surface, context)) {
        printf("[+] 设置EGL上下文和表面为当前失败，错误码=%u\n", glGetError());
        return false;
    }
    // 如果需要，打印日志信息
    if (log) {
        printf("[+] 设置EGL上下文和表面为当前成功\n");
        printf("[+] 创建原生窗口成功\n");
    }
    return true;
}



char *读取文件(char *path)
{
	FILE *fp;
	if ((fp = fopen(path, "r")) == NULL)
	{
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	int filesize = ftell(fp);
	char *str;
	str = (char *)malloc(filesize);
	rewind(fp);
	fread(str, 1, filesize, fp);
	str[filesize] = '\0';
	fclose(fp);
	return str;
}


void 写出文件(char *aaa,char *bbb){
	
	system("mkdir -p  /storage/emulated/0/独久");
	std::ofstream ofs;
	
	
	ofs.open(aaa, std::ios::out);

	ofs << bbb 
		;

	ofs.close();
}




void 读取文件(){
char *ndhdh=读取文件("/storage/emulated/0/独久/小x");
			if(ndhdh){SmallMapX= atof(ndhdh);}
			char *ndhdh2=读取文件("/storage/emulated/0/独久/小y");
			if(ndhdh2){SmallMapY= atof(ndhdh2);}
	char *ndhdh3=读取文件("/storage/emulated/0/独久/大x");
			if(ndhdh3){SmallHPX= atof(ndhdh3);}
			char *ndhdh5=读取文件("/storage/emulated/0/独久/大y");
			if(ndhdh5){SmallHPY= atof(ndhdh5);}
	
			char *ndhdh6=读取文件("/storage/emulated/0/独久/头像大小");
			if(ndhdh6){touxiangdaxiao= atof(ndhdh6);}
			
			
			char *ndhdh7=读取文件("/storage/emulated/0/独久/小地图血量大小");
			if(ndhdh7){xiaodituxue= atof(ndhdh7);}
			
			char *ndhdh8=读取文件("/storage/emulated/0/独久/小地图头像间隔");
			if(ndhdh8){jiange= atof(ndhdh8);}
	
			string LoadFile = "/sdcard/独久/颜色配置";
	
	ReadDrawSet((总颜色 *)&颜色配置, LoadFile.c_str());
	
			
			
			char *ndhdh9=读取文件("/storage/emulated/0/独久/分辨率使用");
			if(ndhdh9){fenblxx= 1;}else{fenblxx=0;}
			
			char *ndhdh10=读取文件("/storage/emulated/0/独久/技能栏左右1");
			if(ndhdh10){jinenglanzX= atof(ndhdh10);}
			
			char *ndhdh12=读取文件("/storage/emulated/0/独久/技能栏上下1");
			if(ndhdh12){jinenglanzY= atof(ndhdh12);}
			
				char *ndhdh11=读取文件("/storage/emulated/0/独久/上帝高度");
			if(ndhdh11){shangdi= atof(ndhdh11);}
			
				char *ndhdh13=读取文件("/storage/emulated/0/独久/屏幕x");
			if(ndhdh13){屏幕x= atof(ndhdh13);}
			
				char *ndhdh14=读取文件("/storage/emulated/0/独久/屏幕y");
			if(ndhdh14){屏幕y= atof(ndhdh14);}


}
/**
by  独久
https://t.me/dujiunb


*/



int 数据() {
    DIR *dir = opendir("/dev/input/");
    dirent *ptr = NULL;
    int count = 0;
    while ((ptr = readdir(dir)) != NULL) {
        if (strstr(ptr->d_name, "event"))
            count++;
    }
    return count ? count : -1;
}


int 音量() {
    int EventCount = 数据();
    if (EventCount < 0) {
        printf("未找到输入设备\n");
        return -1;
    }

    int *fdArray = (int *)malloc(EventCount * sizeof(int));

    for (int i = 0; i < EventCount; i++) {
        char temp[128];
        sprintf(temp, "/dev/input/event%d", i);
        fdArray[i] = open(temp, O_RDWR | O_NONBLOCK);
    }


    input_event ev;
    int count = 0; // 记录按下音量键的次数

    while (1) {
        for (int i = 0; i < EventCount; i++) {
            memset(&ev, 0, sizeof(ev));
            read(fdArray[i], &ev, sizeof(ev));
            if (ev.type == EV_KEY && (ev.code == KEY_VOLUMEUP || ev.code == KEY_VOLUMEDOWN)) {
           if(DrawIo[19])
              {
                 if (ev.code == 115&&ev.value==1) {//音量➕
               IsBall = true;
    				MenuSic = true;
    				BallSic = false;
					

                } else if (ev.code == 114&&ev.value==1) {
                IsBall=false;
      //   ImGui::SetWindowPos("Ball",p,ImGuiCond_Always);
                }  
                }
            }
            usleep(1000);
        }
        usleep(500);
    }
       usleep(1500);
    return 0;
}


void ImGui_init(){
    if (g_Initialized){
        return;
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
    
	获取头像2();
	获取图标();
	读取文件();
	ImGui::白色();
	添加选项照片();
	
    ImGui_ImplAndroid_Init(native_window);
    ImGui_ImplOpenGL3_Init("#version 300 es");
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    io.Fonts->AddFontFromMemoryTTF((void *) font_v, font_v_size, 28.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    io.Fonts->AddFontDefault(&font_cfg);
    ImGui::GetStyle().ScaleAllSizes(3.0f);
    g_Initialized = true;
}




    static float velocity = 1.0f;
//void (xy, 双龙大小, 线条大小, 双龙是否缠绕, 红龙长短, 颜色1, 颜色2, 旋转速度, 长度)
void SpinnerIngYang(const ImVec2& centre, float radius, float thickness, bool reverse, float yang_detlta_r, const ImColor &colorI = 0xffffffff, const ImColor &colorY = 0xffffffff, float speed = 2.8f, float angle = IM_PI * 0.7f) {
      // Render
    const size_t num_segments = ImGui::GetForegroundDrawList()->_CalcCircleAutoSegmentCount(radius);
    float startI = (float)ImGui::GetTime() * speed;
    float startY = (float)ImGui::GetTime() * (speed + (yang_detlta_r > 0.f ? ImClamp(yang_detlta_r * 0.5f, 0.5f, 2.f) : 0.f));

    const float angle_offset = angle / num_segments;
    const float th = thickness / num_segments;
    for (size_t i = 0; i < num_segments; ++i) {
        const float a = startI + (i * angle_offset);
        const float a1 = startI + ((i + 1) * angle_offset);
        ImGui::GetForegroundDrawList()->AddLine(
                ImVec2(centre.x + ImCos(a) * radius, centre.y + ImSin(a) * radius),
                ImVec2(centre.x + ImCos(a1) * radius, centre.y + ImSin(a1) * radius),
                colorI,
                th * i
        );
    }
    const float ai_end = startI + (num_segments * angle_offset);
    ImVec2 circle_i_center{centre.x + ImCos(ai_end) * radius, centre.y + ImSin(ai_end) * radius};
    ImGui::GetForegroundDrawList()->AddCircleFilled(circle_i_center, thickness / 2.f, colorI, (int)num_segments);
    const float rv = reverse ? -1.f : 1.f;
    const float yang_radius = (radius - yang_detlta_r + 10);
    for (size_t i = 0; i < num_segments; ++i) {
        const float a = startY + IM_PI + (i * angle_offset);
        const float a1 = startY + IM_PI + ((i+1) * angle_offset);
        ImGui::GetForegroundDrawList()->AddLine(
                ImVec2(centre.x + ImCos(a * rv) * yang_radius, centre.y + ImSin(a * rv) * yang_radius),
                ImVec2(centre.x + ImCos(a1 * rv) * yang_radius, centre.y + ImSin(a1 * rv) * yang_radius),
                colorY,
                th * i
        );
    }
    const float ay_end = startY + IM_PI + (num_segments * angle_offset);
    ImVec2 circle_y_center{centre.x + ImCos(ay_end * rv) * yang_radius, centre.y + ImSin(ay_end * rv) * yang_radius};
    ImGui::GetForegroundDrawList()->AddCircleFilled(circle_y_center, thickness / 2.f, colorY, (int)num_segments);
}

///////////
int huitu=0;
void tick() {
      ImGuiIO& io = ImGui::GetIO();
      static ImVec4 clear_color = ImVec4(0, 0, 0, 0);
      ImGuiStyle& style = ImGui::GetStyle();
      ImGuiStyle& styleRef = *Style; // 解引用指针
      ImGuiStyle Style;
///////////

	static float ANIM_SPEED = 0.4f;
    static float Velua = IsBall ? 0.0f : 1.0f;

   // ImVec4 clear_color = ImVec4(255.0f / 255.f, 179.0f / 255.f, 0.0f / 255.f, 1.00f);
    //ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, { 0, 0 } );

	static ImVec2 ImagePos = {0, 0};
	//ImGui::PushFont( ImGui::GetIO( ).Fonts->Fonts[3] );
  
	Velua = ImClamp(Velua + (ImGui::GetIO().DeltaTime / ANIM_SPEED) * (IsBall ? 1.f : -1.f), 0.f, 1.f);
	if (850 * Velua <= 850) {
    	ImGui::SetWindowSize("Tomato", {850 * Velua, 520});
    } else if (850 * Velua >= 100) {
    	ImGui::SetWindowSize("Tomato", {850 * Velua, 520});
    }
	if (850 * Velua <= 100 && !IsBall) BallSic = true, MenuSic = false;
	if (BallSic && 850 * Velua <= 70)
	{
	  
                   
		if (ImGui::Begin("Ball", &BallSic, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground))
        {
        
        	  
                   
			auto Pos = ImGui::GetWindowPos();
		
			SpinnerIngYang(ImVec2(Pos.x+50, Pos.y+50), 50, 20, true, 35.0f, ImColor(255, 255, 255), ImColor(255, 0, 0), 2.0f * velocity, IM_PI * 0.8f); //双龙戏珠

			if (ImGui::IsItemActive()) {
    			if (!IsDown) {
    				IsDown = true;
    				ImagePos = ImGui::GetWindowPos();
    			}
    		} else if (IsDown) {
				IsDown = false;
    			if(ImagePos.x == ImGui::GetWindowPos().x && ImagePos.y == ImGui::GetWindowPos().y) {
    				IsBall = true;
    				MenuSic = true;
    				BallSic = false;
    			    ImGui::SetWindowPos("Tomato", Pos, ImGuiCond_Always);
    			}
    		}
		}
		ImGui::End();
	}
         if (MenuSic && 850 * Velua >= 70){
         {
           ImGui::Begin( "Tomato", &MenuSic, ImGuiWindowFlags_NoDecoration );
         {
       
        ImVec2 p = ImGui::GetWindowPos( );
		//设置窗口大小
        ImGui::SetWindowSize( { 850, 520} );
      
       
       if (ImGui::BeginChild("##左侧菜单标题", ImVec2(170, 0), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NavFlattened));
        {
    auto Pos = ImGui::GetWindowPos();
    SpinnerIngYang(ImVec2(Pos.x+95, Pos.y+70), 50, 20, true, 35.0f, ImColor(255, 255, 255), ImColor(255, 0, 0), 2.0f * velocity, IM_PI * 0.8f); //双龙戏珠
            
        ImGui::SetCursorPos({0, 140});
        ImGui::Separator();
        ImGui::ItemSize(ImVec2(0, 1));
                
                   ImVec4 ImVec44023292e = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    			CardPanel("Card3", ImVec2(170, 350), ImVec44023292e, 20,20, [&]() {
    	        ImGui::SetCursorPosX(3);//数值越大越靠右边边
                if (ImGui::Button("         主页", ImVec2(160, 85)))
    			{
    				show_ChildMenu = 0;					
    			}
    			ImGui::SameLine(9);	
			   ImGui::Image(FloatBallwc, ImVec2(80 + 0.0,80 + 0.0));    	
			    
			    ImGui::SetCursorPosX(3);
    			if (ImGui::Button("         绘图", ImVec2(160, 85)))
    			{
    				show_ChildMenu = 1;					
    			}
    			ImGui::SameLine(9);	
			    ImGui::Image(FloatBallwv, ImVec2(80 + 0.0,80 + 0.0));    	
			    
			    ImGui::SetCursorPosX(3);
    			if (ImGui::Button("         设置", ImVec2(160, 85)))
    			{
    				show_ChildMenu = 2;					
    			}
    			ImGui::SameLine(9);	
			    ImGui::Image(FloatBallwt, ImVec2(80 + 0.0,80 + 0.0));    	
			    
    			  ImGui::EndChild();
    			});
    			}
    
    ImGui::SameLine();
      


    if (ImGui::BeginChild("##右菜单", ImVec2(-1, -1), false))
                {
                
                ImGui::Text("王者 %c", "|/-\\"[(int)(ImGui::GetTime() / 0.04f) & 2]);
                ImGui::SameLine();
                ImGui::Text("独久");    		
    			ImGui::SameLine();				
	   
            if (ImGui::GetWindowWidth() - 420 > 0)
             {
    		  ImGui::InvisibleButton("缩小", {ImGui::GetWindowWidth() - 420, 0});
    		  ImGui::SameLine();
    		}
    		if (ButtonTextColored(Style.Colors[ImGuiCol_Button],"[截图]")) {
               system("su -c screencap -p /sdcard/独久/独久截屏.jpg");
    		}
    		ImGui::SameLine();    	
    	if (ButtonTextColored(Style.Colors[ImGuiCol_Separator],"[退出]")) {
        exit(0);

    		}
    		ImGui::SameLine();    				
    		  if (ButtonTextColored(Style.Colors[ImGuiCol_Separator],"[缩小]")) {
    		IsBall=false;
         ImGui::SetWindowPos("Ball",p,ImGuiCond_Always);
    		}
    		ImGui::ItemSize(ImVec2(0, 2));
    	    ImGui::Separator();
                
                	    
        if (!show_ChildMenu) {
    			if (ImGui::BeginChild("##绘图", ImVec2(0, 0), false,  ImGuiWindowFlags_NavFlattened)) 
        {
        ImVec4 ImVec44023292e = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    			CardPanel("Card3", ImVec2(-1, -1), ImVec44023292e, 20,20, [&]() {
    //	ImGui::SameLine(+100.0f);
    	
       ImGui::Text("分辨率: %dx%d", abs_ScreenX, abs_ScreenY);
       ImGui::SameLine();
       ImGui::Text( "渲染%.3fms 帧率%.1f", 1000.0f / ImGui::GetIO().Framerate,ImGui::GetIO().Framerate );
      //  ImGui::SliderFloat("", &godvalue, 0, 3, "%.2f", 1);
    // ImGui::SameLine();
    
    float r[60];       
        for(int i=0;i<20;i++){
        r[i]=rand()%70+60;                       
           }
        ImGui::PlotLines("Frame Times", r, 19);
        
      static float progress = 0.0f, progress_dir = 1.0f;
                progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
            if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
            if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
             ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));
        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ImGui::Text("进度条");

		
		if(ImGui::SliderFloat("", &shangdi, 1.2f, 2.2f, "%.2f", 1.0f))
                      {char urlls[2560];
	                  sprintf(urlls, "%.2f", shangdi);	
	                  写出文件("/storage/emulated/0/独久/上帝高度",urlls);}
		
		ImGui::SameLine();
    
              
              if (ImGui::Button("上帝")){
              上帝=true;
              }
               
       

     /*   
         if(huitu==0){
           if(ImGui::Button("获取进程与模块",{-1,70}))
           {
          DrawInit();
          huitu=1;
           }
          }else{
           if(ImGui::Button("获取模块进程成功",{-1,70}))
          {

          }
          }*/
          /*
          if(一键开启共享==false){
          if(ImGui::Button("开启共享",{-1,70}))
          {
          ESPMenu.是否开启共享=true;
          一键开启共享=true;
          }
          }else{
             if(ImGui::Button("关闭共享",{-1,70}))
             {
             ESPMenu.是否开启共享=false;
          一键开启共享=false;
             }
          }*/
          
        ImGui::SS_SwitchButton("人物共享", &ESPMenu.是否开启共享);
        ImGui::ItemSize(ImVec2(0, 5));
    	ImGui::SS_SwitchButton("音量键控制悬浮窗", &DrawIo[19]);
          

          });


                      /**
by  独久
https://t.me/dujiunb


*/
		 
      
      
        }
        }else if (show_ChildMenu == 1) {
                 if (MenuSic && 400 * Velua >= 70){
    			if (ImGui::BeginChild("绘图", ImVec2(0, 0), false,  ImGuiWindowFlags_NavFlattened)) 
    			{
    			ImVec4 ImVec44023292e = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    			CardPanel("Card3", ImVec2(-1, -1), ImVec44023292e, 20,20, [&]() {
   // 	ImGui::SameLine(+100.0f);

                      ImGui::Text("=================绘图==================");
                /*
                    if(一键开启==0){
if(ImGui::Button("开启辅助", ImVec2(-1, 75))){

一键开启=1;血量=1;地图=1;射线=1;视野方框=1;方框=1;野怪=1;兵线=1;方框技能=1;顶上技能=1;上帝=0;自身判断=1;}
}else{
if(ImGui::Button("关闭绘制", ImVec2(-1, 75))){
一键开启=0;血量=0;地图=0;射线=0;方框=0;野怪=0;兵线=0;方框技能=0;顶上技能=0;视野方框=0;上帝=0;自身判断=0;}						  
}*/
                      if(huitu==0){
if(ImGui::Button("开启辅助", ImVec2(-1, 70))){
DrawInit();
huitu=1;血量=1;地图=1;射线=1;视野方框=1;方框=1;野怪=1;兵线=1;方框技能=1;顶上技能=1;上帝=0;自身判断=1;}
}else{
if(ImGui::Button("关闭绘制", ImVec2(-1, 70))){
huitu=0;血量=0;地图=0;射线=0;方框=0;野怪=0;兵线=0;方框技能=0;顶上技能=0;视野方框=0;上帝=0;自身判断=0;}						  
}
                      ImGui::Separator();
                      ImGui::Checkbox("地图头像", &地图);
					  ImGui::SameLine();
					  ImGui::Checkbox("人物方框", &方框);
					  ImGui::SameLine();
					  ImGui::Checkbox("方框技能", &方框技能);
					  ImGui::Separator();
					  ImGui::Checkbox("顶上技能", &顶上技能);
					  ImGui::SameLine();
					  ImGui::Checkbox("显示兵线", &兵线);
		              ImGui::SameLine();
					  ImGui::Checkbox("显示野怪", &野怪);
					  ImGui::Separator();
					  ImGui::Checkbox("显示射线", &射线);
		              ImGui::SameLine();
					  ImGui::Checkbox("漏人不绘", &视野方框);
			     	  ImGui::SameLine();
					  ImGui::Checkbox("自身视野", &自身判断);
					  
				//	  ImGui::Checkbox("斩杀", &斩杀);
					  
					//  ImGui::Checkbox("惩戒", &惩戒);
					  
					//  ImGui::Separator();
    char imei[100]="";//leixin666
    FILE *fpp = popen("getprop ro.serialno", "r");
   read_line_without_newline(fpp, imei, sizeof(imei));
    pclose(fpp);
/*ImGui::BulletText("卡密: %s", fileContent2.c_str());
ImGui::BulletText("设备码: %s", fileContent1.c_str());
ImGui::BulletText("卡密到期时间: %s", fileContent3.c_str());*/
ImGui::BulletText("房间号:%s",imei);
ImGui::SameLine();
 ImGui::BulletText("网页:38.55.232.31");
//ImGui::Text("=======================================");
});
}
}
}else if (show_ChildMenu == 2) {
    			if (ImGui::BeginChild("绘图", ImVec2(0, 0), false,  ImGuiWindowFlags_NavFlattened)) 
    			{
      
      if(ImGui::CollapsingHeader("绘制位置调整"))
{
		if(ImGui::SliderInt("自身视野X", &屏幕x,-2000,3500,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", 屏幕x);		
		写出文件("/storage/emulated/0/独久/屏幕x",urlls);}
		
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
		if(ImGui::SliderInt("自身视野Y", &屏幕y,-1000,1000,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", 屏幕y);		
		写出文件("/storage/emulated/0/独久/屏幕y",urlls);}               
		
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
		if(ImGui::SliderInt("小地图头像大小", &touxiangdaxiao,-300,300,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", touxiangdaxiao);		
		写出文件("/storage/emulated/0/独久/头像大小",urlls);}
			
      //  ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素		
		if(ImGui::SliderInt("小地图血量大小", &xiaodituxue,-80,80,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", xiaodituxue);
		写出文件("/storage/emulated/0/独久/小地图血量大小",urlls);}
			
    //    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素		
		if(ImGui::SliderInt("小地图头像间隔", &jiange,-100,100,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", jiange);
		写出文件("/storage/emulated/0/独久/小地图头像间隔",urlls);}
		
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
	 if(ImGui::SliderInt("头像X", &SmallMapX,-300,300,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", SmallMapX);
		写出文件("/storage/emulated/0/独久/小x",urlls);}
		
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
     if(ImGui::SliderInt("头像Y", &SmallMapY,-300,300,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", SmallMapY);
		写出文件("/storage/emulated/0/独久/小y",urlls);}
	
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
     if(ImGui::SliderInt("大地图X", &SmallHPX,-300,300,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", SmallHPX);
		写出文件("/storage/emulated/0/独久/大x",urlls);}
		
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
     if(ImGui::SliderInt("大地图Y", &SmallHPY,-300,300,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", SmallHPY);
		写出文件("/storage/emulated/0/独久/大y",urlls);}
					  
	//    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素		  
	 if(ImGui::SliderInt("技能左右", &jinenglanzX,-2000,2000,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", jinenglanzX);
		写出文件("/storage/emulated/0/独久/技能栏左右1",urlls);}
		
		//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
	 if(ImGui::SliderInt("技能上下", &jinenglanzY,-500,500,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", jinenglanzY);
		写出文件("/storage/emulated/0/独久/技能栏上下1",urlls);}
		
		//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 9); // 将光标位置向上移动300个像素
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
        ImGui::ColorEdit3("血量颜色",(float*)&颜色配置.血量颜色);
		//ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
        ImGui::ColorEdit3("射线颜色",(float*)&颜色配置.射线颜色);
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
	    ImGui::ColorEdit3("方框颜色",(float*)&颜色配置.方框颜色);
	    ImGui::Separator();
	    }
	        if(ImGui::CollapsingHeader("共享绘图调整"))
         {
         if(ImGui::SliderInt("共享左右调整", &ESPMenu.小地图左右调整,-150,300)){char urlls[2560];
        sprintf(urlls, "%d", ESPMenu.小地图左右调整);
        写出文件("/storage/emulated/0/颜色/共享左右调整",urlls);}
        	if(ImGui::SliderInt("共享上下调整", &ESPMenu.小地图上下调整,-200,200)){char urlls[2560];
        sprintf(urlls, "%d", ESPMenu.小地图上下调整);
        写出文件("/storage/emulated/0/颜色/共享上下调整",urlls);}
        if(ImGui::SliderInt("共享野怪左右调整", &ESPMenu.野怪左右调整,-200,200)){char urlls[2560];
        sprintf(urlls, "%d", ESPMenu.野怪左右调整);
        写出文件("/storage/emulated/0/颜色/共享野怪左右调整",urlls);}
                if(ImGui::SliderInt("共享野怪上下调整", &ESPMenu.野怪上下调整,-200,200)){char urlls[2560];
        sprintf(urlls, "%d", ESPMenu.野怪上下调整);
        写出文件("/storage/emulated/0/颜色/共享野怪上下调整",urlls);}
                if(ImGui::SliderInt("共享兵线左右调整", &ESPMenu.兵线左右调整,-200,200)){char urlls[2560];
        sprintf(urlls, "%d", ESPMenu.兵线左右调整);
        写出文件("/storage/emulated/0/颜色/共享兵线左右调整",urlls);}
                if(ImGui::SliderInt("共享分辨率x调整", &ESPMenu.分辨率X,1000,4000)){char urlls[2560];
        sprintf(urlls, "%d", ESPMenu.分辨率X);
        写出文件("/storage/emulated/0/颜色/共享分辨率x调整",urlls);}
         }
	    
	    if(ImGui::CollapsingHeader("录屏配置"))
        {
        ImGui::SliderInt("自定义录制秒数", &录屏时长, 1, 360);
											if (ImGui::Button("录制精彩操作", ImVec2(-1, 75))) {
											if (!isRecording.load()) {
											isRecording.store(true);
											recordingTimeElapsed.store(0); // 开始时重置时间
											std::thread([](int 录屏时长) {
											// 非阻塞式开始录制
											std::string command = "screenrecord --time-limit " + std::to_string(录屏时长) + " /sdcard/独久/独久CF录制.mp4 &";
											system(command.c_str());

											for (int i = 0; i < 录屏时长 && isRecording.load(); ++i) {
											std::this_thread::sleep_for(std::chrono::seconds(1));
											recordingTimeElapsed.fetch_add(1);
											}

											isRecording.store(false);
											}, 录屏时长).detach();
											}
											}
											
								
											if (ImGui::Button("取消录制操作", ImVec2(-1, 75)) && isRecording.load()) {
											system("pkill -l SIGINT screenrecord");
											isRecording.store(false);
											}
        ImGui::Separator();
        }
        
        
        
        if(ImGui::CollapsingHeader("内存功能"))
{
	    ImGui::TextColored(ImVec4(0.0f, 0.7f, 0.2f, 1.0f), " [内透一定要挂端口或者防]  [关闭内透退出游戏]  [发现内透想关闭及时退出游戏]  ");
	                 if (ImGui::Button("全局内透",{-1,75})){
              内透=true;
              }
              ImGui::Separator();
              }
              if(ImGui::CollapsingHeader("使用说明"))
              {
              
              ImGui::Text("没什么想说的，注意演戏，少次举报");    		
              ImGui::TextColored(ImGui::GetStyle().Colors[ImGuiCol_Text],"作者: 独久\n技术支持:八月  泪心");
              ImGui::Separator();
              
              }
	    
	        if (ImGui::Button("保存配置",{-1, 75})) {
        string SaveFile ;                 
        SaveFile = "/sdcard/独久/颜色配置";
		SaveDrawSet((总颜色 *)&颜色配置, SaveFile.c_str());
        }
		
		// ImGui::SameLine();
    if (ImGui::Button("删除颜色配置",{-1, 75})) {
        system("rm /sdcard/独久/颜色配置");
                    }

                    
	    
        }
        }

                      

     
      }
                    
                }
           
                ImGui::EndChild();
                ImGui::PopStyleVar(1);
            }
            ImGui::End();
        }
        
        	if (isRecording.load()) {
        int elapsed = recordingTimeElapsed.load();
        std::string watermarkText = "录制时间: " + std::to_string(elapsed) + " 秒";

        // 设置窗口透明度
        ImGui::SetNextWindowBgAlpha(0.4f); // 完全透明

        // 设置窗口位置
        ImGui::SetNextWindowPos(ImVec2(10 + 1050, 10));


        // 创建窗口
        ImGui::Begin("RecordingTimeWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("%s", watermarkText.c_str());
        ImGui::End();
    }
    
		if (IsWin)
		{
			IsWin = false;
            IsLoGin = false;
            BallSwitch = false;
            ImGui::SetWindowSize("Ball", {100.0f, 100.0f});
        } 
		

	/*****绘制帧率*****/
	
  char fkhs[1000];
    sprintf(fkhs,"%.1f FPS",ImGui::GetIO().Framerate);
    ImGui::GetForegroundDrawList()->AddText(ImVec2(300, 1000),ImColor(225,255,255),fkhs);
    ImGui::GetForegroundDrawList()->AddText(ImVec2(90, 1000),ImColor(225,255,255),"独久");
    /*****结束*****/
	if(huitu==1){
	DrawPlayer(); //调用绘图  直接写在这边的话有点影响观看了
	/*std::thread t(DrawPlayer);  // 创建一个新的线程，并指定要执行的函数
t.detach();  // 分离新线程，使其在后台执行
std::this_thread::sleep_for(std::chrono::seconds(1));*/
	}
}




void screen_config() {
    ::displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
    ::screen_x = displayInfo.width;
    ::screen_y = displayInfo.height;
}



void drawBegin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(native_window_screen_x, native_window_screen_y);
    ImGui::NewFrame();
    
    screen_config();
    
    static uint32_t orientation = -1;
    if (orientation != displayInfo.orientation) {
        orientation = displayInfo.orientation;
        Touch::setOrientation(displayInfo.orientation);
        //cout << " width:" << displayInfo.width << " height:" << displayInfo.height << " orientation:" << displayInfo.orientation << endl;
    }    
}

void drawEnd() {
    ImGuiIO &io = ImGui::GetIO();
    glViewport(0.0f, 0.0f, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT); // GL_DEPTH_BUFFER_BIT
    glFlush();
    if (display == EGL_NO_DISPLAY) {
        return;
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    eglSwapBuffers(display, surface);
}

void shutdown() {
    if (!g_Initialized) {
        return;
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    if (display != EGL_NO_DISPLAY){
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context != EGL_NO_CONTEXT){
            eglDestroyContext(display, context);
        }
        if (surface != EGL_NO_SURFACE){
            eglDestroySurface(display, surface);
        }
        eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
    ANativeWindow_release(native_window);
}
