#include <draw.h>
#include <array>
#include "FONTS/Font.h"
#define PI 3.141592653589793238
#include<list>
#include<vector>
#include<string.h>
#include<pthread.h>
#include<thread>
#include<cstring>
#include<jni.h>
#include<unistd.h>
#include<fstream>
#include<iostream>
#include<dlfcn.h>
#include "FONTS/𝗜𝗠𝗚𝗨𝗜_𝗚𝗢𝗗.h"
#include "FONTS/New.h"
#include "stb_image.h"
#include "FONTS/obfuscate.h"
#include "oxorany.h"
#include "绘图.hpp"
#include "Layout.hpp"
#include "FONTS/天理.h"
#include "FONTS/背景.h"
#include "FONTS/悬浮窗.h"

#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};
std::string g_Token, g_Auth;

//DES 秋
//~~~~~~~~~~~~~~~~~~~ ~~~~~~~~~~~~~~~~~~\\
ImVec2 Pos; //窗口位置
ImTextureID FloatBall天理;//logo图片定义
ImTextureID FloatBall背景; //背景图片定义

ImTextureID FloatBall;
void DrawLogo(ImVec2 center, float size)
{
	ImGui::SetCursorPos({0, 180});
	ImDrawList *draw_list = ImGui::GetWindowDrawList();
	draw_list->AddImage(FloatBall,{center.x - size / 2, center.y - size / 2},{center.x + size / 2, center.y + size / 2});
}

//---------------<获取文件的内容>------------------//
#include <fstream>
#include <string>

// 定义一个函数来读取卡密到期时间
std::string GetKamiContent(const std::string& filePath) {
	
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "卡密文件未找到"; // 如果文件不存在，返回默认提示
    }

    std::string content;
    std::getline(file, content); // 假设卡密到期时间存储在文件的第一行
    file.close();
    return content;
}
//---------------<结束>------------------//


void SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = NULL, ImGuiSliderFlags flags = 0, float 光标x = 0) {
ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 10.0f); // 背景圆角
ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f); // 滑块圆角 
ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.86f, 0.86f, 0.86f, 1.0f)); // 滑条背景
ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.86f, 0.86f, 0.86f, 1.0f)); // 滑条激活背景
ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.86f, 0.86f, 0.86f, 1.0f)); // 滑条被点击背景颜色
ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.196f, 0.588f, 1.0f, 1.0f)); // 滑块手柄默认颜色
ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.196f, 0.588f, 1.0f, 1.0f)); // 滑块手柄激活颜色 
ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // 设置文本颜色
//  ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x + 10, ImGui::GetCursorPos().y));
ImGui::Text("%s", label); // 文本
ImGui::PopStyleColor(); // 释放文本颜色
ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // 设置滑条文本颜色
ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x, ImGui::GetCursorPos().y - 13.0f)); // 缩小上下间距
ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 光标x); // 设置光标位置
ImGui::SliderFloat(label, v, v_min, v_max, format, flags); // 创建滑条
ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPos().x, ImGui::GetCursorPos().y - 13.0f)); // 缩小上下间距
ImGui::PopStyleColor(6); // 释放颜色
ImGui::PopStyleVar(2); // 释放圆角
}

//DES 秋
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
EGLDisplay display = EGL_NO_DISPLAY;
EGLConfig config;
EGLSurface surface = EGL_NO_SURFACE;
EGLContext context = EGL_NO_CONTEXT;

uint32_t orientation = 0;
ANativeWindow *native_window;
int screen_x = 0, screen_y = 0;
int abs_ScreenX = 0, abs_ScreenY = 0;
int native_window_screen_x = 0, native_window_screen_y = 0;
android::ANativeWindowCreator::DisplayInfo displayInfo{0};
EGLDisplay display = EGL_NO_DISPLAY;

std::string loadTextFromFile1(const std::string& filename) {
    std::string content;
    std::ifstream file(filename);
    if (file.is_open()) {
        content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
    }
    return content;
}


bool AIMBUTTON;
bool BTBUTTON;
bool active = false;
bool down;
bool upp;
bool Bypass = true;
float FOVT;
float FOVTB;
int huitu;
bool isInitialized = (huitu != 0);
ImFont* F48 = nullptr;
ImFont* F50 = nullptr;
ImFont* JAAT = nullptr;
ImFont* SOCIAL = nullptr;
float menu[4] = { 250/255.f, 132/255.f, 86/255.f, 1.000f };
ImVec2 pos;
ImDrawList* draw;
enum heads {
    rage, antiaim, visuals, settings, skins, configs, scripts
};

enum sub_heads {
    general, accuracy, exploits, _general, advanced
};
bool INFO;
float density = -1;

timer FPS限制;
float FPF显示 = 0;
Screen full_screen;
int Orientation = 0;
//int screen_x = 0, screen_y = 0;
int init_screen_x = 0, init_screen_y = 0;
bool g_Initialized = false;
// ======================================================================== //
float FOVSize = 250;
float Skill = 4;
float Sland = 15000;
float sinstanthit = 100000;
static bool IgnoreBot = false;
// ======================================================================== //

//======================| 𝗖𝗢𝗠𝗕𝗢 𝗕𝗘𝗚𝗜𝗡 |==========================//

enum EAim {Distance = 0,Croshhair = 1};
enum EAimTarget {Head = 0,Chest = 1};
enum EAimTrigger {Any = 0,Shooting = 1,Scoping = 2,Both = 3,None = 4};
enum EEspUI {UI1 = 0,UI2 = 1,UI3 = 2};
enum EFova {Fova1 = 0,Fova2 = 1,Fova3 = 2};
enum EFov {Fov1 = 0,Fov2 = 1,Fov3 = 2};
enum EEspPline {Top = 0,Mid = 1,Buttom = 2,eno1 = 3,};
enum EEspBline {Middle = 0,Up = 1,Low = 2,no = 3,};

//======================| 𝗦𝗧𝗥𝗨𝗖𝗧 𝗖𝗢𝗡𝗙𝗜𝗚𝗦 |==========================//
static char s[64];
struct sConfig {

    int Loot;
    int Skeleton;
    int Line;
    int RadarY;
    int RadarX;
    int IpadS;
    int Prid;
    struct sWIDGETS_EXPERT {
    EEspUI EUI;
    };
    sWIDGETS_EXPERT WIDGETS_EXPERT;
struct sAimMenu {
        bool Enable;
		int Meter;
        bool Pov;
		bool Pred;
		bool Recoil;
		bool Aimbot;
		int Cross;
		int Position;
        float Recc;
		EAimTarget Target;
        EAimTrigger Trigger;
        bool IgnoreKnocked;
        bool VisCheck;
		bool IgnoreBots;
		bool TargetLine;};
sAimMenu SilentAim{0};
sAimMenu AimBot{0}; 

struct sColorsESP {
	    float *PlayerVisLine;
        float *PlayerHideLine;
		float *BotVisLine;
		float *BotHideLine;
        float *PlayerVisSkeleton;
        float *PlayerHideSkeleton;
        float *BotVisSkeleton;
		float *BotHideSkeleton;
        float *PlayerVisBox;
        float *PlayerHideBox;
        float *BotVisBox;
        float *BotHideBox;
        float *PlayerRadar;
        float *BotRadar;
        float *PlayerAlert;
        float *BotAlert;
		float *Fov;
		float *Fova;
        };
    sColorsESP ColorsESP{0};
};
sConfig Config{0};

float AimSmooth = 1.0f;
static bool ic;

static bool Feu;
float sliderint;
bool Wallhax = false;
bool WideView = false;
bool FlashSdk = false;
bool Dark = false;
bool NoFog = false;
bool Blacksky = false;
bool RGB = false;
bool UnlimitedHp = false;
bool FastLanding = false;
bool Bypass1 = false;
bool ReportBlock = false;

#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

string exec(string command)
{
    char buffer[128];
    string result = "";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

int init_egl(int _screen_x, int _screen_y, bool log) {
	
        //	createSocket();//共享函数
    
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
bool sgfop = false;  
   
   FILE* file = fopen("/data/内部配置/防录屏", "r");
    if (file != NULL) {
        fclose(file);
        sgfop = true;
    } else {
    	sgfop = false;
	}  
   

if (sgfop)
{
 ::native_window = android::ANativeWindowCreator::Create("AImGui", _screen_x, _screen_y, true);
	}
	
	if (!sgfop)//关闭方露萍
{
	
    
  
    
    
    
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



int GetEventCount3()
{
    DIR *dir = opendir("/dev/input/");
    dirent *ptr = NULL;
    int count = 0;
    while ((ptr = readdir(dir)) != NULL)
    {
        if (strstr(ptr->d_name, "event"))
            count++;
    }
    return count ? count : -1;
}
bool kang = true;


//bool 悬浮窗 = true;



int 音量()
{
    int EventCount = GetEventCount3();
    if (EventCount < 0)
    {
        printf("未找到输入设备\n");
        return -1;
    }

    int *fdArray = (int *)malloc(EventCount * sizeof(int));

    for (int i = 0; i < EventCount; i++)
    {
        char temp[128];
        sprintf(temp, "/dev/input/event%d", i);
        fdArray[i] = open(temp, O_RDWR | O_NONBLOCK);
    }

    input_event ev;
    int count = 0; // 记录按下音量键的次数

    while (1)
    {
        for (int i = 0; i < EventCount; i++)
        {
            memset(&ev, 0, sizeof(ev));
            read(fdArray[i], &ev, sizeof(ev));
         if(音量控制){ 
            if (ev.type == EV_KEY && ev.code == KEY_VOLUMEUP && ev.value == 1 && kang == true)
            {
            
			    //tick= true;//
				
                // IsBall = false;
				悬浮球 = false;
				悬浮窗 = true;
            }
            else if (ev.type == EV_KEY && ev.code == KEY_VOLUMEDOWN && ev.value == 1 && kang == true)
            {
                // 这里放悬浮窗开启的函数
                
				//tick = false;//
				
                //IsBall = true;
				悬浮球 = 1;
				悬浮窗 = false;
            }
          }  
        }

        usleep(3000);
    }

    return 0;
}








void screen_config(){
/*
std::string window_size = exec("wm size");
sscanf(window_size.c_str(),"Physical size: %dx%d",&screen_x, &screen_y);*/
    displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
    std::string window_size;
    std::array<char,512>buffer;
    std::unique_ptr<FILE,decltype(&pclose)> pipe(popen("wm size","r"),pclose);
    while(fgets(buffer.data(),buffer.size(),pipe.get()) != nullptr){
        window_size += buffer.data();
    }
    if (window_size.size()>30){
       sscanf(window_size.c_str(),"Override size: %dx%d",&screen_x, &screen_y);
       if(screen_x <= 0 && screen_y <= 0){
         sscanf(window_size.c_str(),"%*s%*s%*s%*s%*s%dx%d", &screen_x, &screen_y);
         if(screen_x <= 0 && screen_y <= 0){
            screen_x = displayInfo.width;
            screen_y = displayInfo.height;
         }
       }
    } else { 
       sscanf(window_size.c_str(),"Physical size: %dx%d",&screen_x, &screen_y); 
       if(screen_x <= 0 && screen_y <= 0){
            screen_x = displayInfo.width;
            screen_y = displayInfo.height;
       }
    }
    ESPMenu.分辨率X = screen_x;
    ESPMenu.分辨率Y = screen_y;
full_screen.ScreenX = screen_x;
full_screen.ScreenY = screen_y;
//std::cout << "[+] 分辨率: " << screen_x << "x" << screen_y << std::endl;
std::thread *orithread = new std::thread([&] {
while(true){
   displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
    //Orientation = atoi(exec("dumpsys display | grep 'mCurrentOrientation' | cut -d'=' -f2").c_str());
    Orientation = displayInfo.orientation;
    Touch::setOrientation(Orientation);
if(Orientation == 0 || Orientation == 2){
screen_x = full_screen.ScreenX;
screen_y = full_screen.ScreenY;
}
if(Orientation == 1 || Orientation == 3){
screen_x = full_screen.ScreenY;
screen_y = full_screen.ScreenX;
}
std::this_thread::sleep_for(0.5s);
}
});
orithread->detach();
}



void ImGuiMenustyle()
{
	ImGuiStyle &style = ImGui::GetStyle();
    style.ScrollbarSize = 40; // 设置滚动条宽度
    style.ScaleAllSizes(1.3); // 设置控件内距
    style.WindowRounding = 0.5; // 设置边框圆角
    style.WindowRounding = 5.5f;
    style.FrameRounding = 2.0f;// 设置圆角
	//NumIoLoad("SaveNum");
	FPS = NumIo[12];
}

void 写出文件(char *aaa,char *bbb){
	
	system("mkdir -p /data/内部配置/颜色");
	std::ofstream ofs;
	
	ofs.open(aaa, std::ios::out);

	ofs << bbb;

	ofs.close();
}


int 读取() {
  char *ndhdh = 读取文件("/data/内部配置/头像X");
  if (ndhdh) {
    SmallMapX = atof(ndhdh);
  }

  char *ndhdh2 = 读取文件("/data/内部配置/头像Y");
  if (ndhdh2) {
    SmallMapY = atof(ndhdh2);
  }

  char *ndhdh3 = 读取文件("/data/内部配置/实体X");
  if (ndhdh3) {
    SmallHPX = atof(ndhdh3);
  }

  char *ndhdh5 = 读取文件("/data/内部配置/实体Y");
  if (ndhdh5) {
    SmallHPY = atof(ndhdh5);
  }

  char *ndhdh6 = 读取文件("/data/内部配置/头像大小");
  if (ndhdh6) {
    touxiangdaxiao = atof(ndhdh6);
  }

  char *ndhdh7 = 读取文件("/data/内部配置/血量大小");
  if (ndhdh7) {
    xiaodituxue = atof(ndhdh7);
  }

  char *ndhdh8 = 读取文件("/data/内部配置/地图比例");
  if (ndhdh8) {
    jiange = atof(ndhdh8);
  }

  char *ndhdh9 = 读取文件("/data/内部配置/技能栏X");
  if (ndhdh9) {
    jinenglanzX = atof(ndhdh9);
  }

  char *ndhdh10 = 读取文件("/data/内部配置/技能栏Y");
  if (ndhdh10) {
    jinenglanzY = atof(ndhdh10);
  }

  char *ndhdh11 = 读取文件("/data/内部配置/上帝");
  if (ndhdh11) {
    shangdi = atof(ndhdh11);
  }

  char *ndhdh12 = 读取文件("/data/内部配置/视野X");
  if (ndhdh12) {
    屏幕x = atof(ndhdh12);
  }

  char *ndhdh13 = 读取文件("/data/内部配置/视野Y");
  if (ndhdh13) {
    屏幕y = atof(ndhdh13);
  }

  char *ndhdh14 = 读取文件("/data/内部配置/斩杀值");
  if (ndhdh14) {
    zhansha = atof(ndhdh14);
  }
/*
  char *ndhdh16 = 读取文件("/data/内部配置/召唤师技能X");
  if (ndhdh16) {
    召唤师技能触发坐标.x = atof(ndhdh16);
  }

  char *ndhdh17 = 读取文件("/data/内部配置/召唤师技能Y");
  if (ndhdh17) {
    召唤师技能触发坐标.y = atof(ndhdh17);
  }
 */ 
  char *ndhdh18 = 读取文件("/data/内部配置/FPS");
  if (ndhdh18) {
    FPS = atof(ndhdh18);
  }

  string LoadFile = "/data/内部配置/颜色配置";
  pdys = ReadDrawSet((总颜色 *)&颜色配置, LoadFile.c_str());

  return pdys;
}




// Combo回调函数

   bool file_exists(const char *filename) {

    FILE *file = fopen(filename, "r");

    if (file) {

        fclose(file);

        return true;

    }

    return false;

} 
const char *file_path = "/data/内部配置/防录屏";

    bool file_found = file_exists(file_path);

    int style_zx = file_found ? 0 : 1;
    int 绘图 = 0;
    int zm = 0;

	

	
void ImGui_init()
{
  
    if (g_Initialized) {
        return;
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGuiStyle* style = &ImGui::GetStyle();
    	ImGui::StyleColorsDark();
        style->WindowPadding = ImVec2(0,0);
        style->Colors[ImGuiCol_WindowBg]              = ImColor(0, 0, 0, 0);
		style->WindowBorderSize = 0.0f;
		io.AnimationSpeed = 1;
    io.IniFilename = NULL;
    new std::thread(音量);
    //颜色设置
    ImGui_ImplAndroid_Init(native_window);
	
	
	
ImVec4 buttonColor = ImVec4(24.0f / 255.0f, 24.0f / 255.0f, 24.0f / 255.0f, 255.0f / 255.0f); // 与ImColor(24,24,24,255)相同的颜色
ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonColor);
ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColor);

// 设置圆角半径
float borderRadius = 1.5f; // 可以根据需要调整圆角大小

// 保存当前的圆角半径
ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, borderRadius);
ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, borderRadius);


ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.5f); // 设置边框大小
ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // 设置边框颜色为白色
	//悬浮球图片加载
    FloatBall = ImAgeHeadFile1(icon, sizeof(icon));

	//悬浮窗图片加载
    FloatBall天理 = ImAgeHeadFile1(天理, sizeof(天理));
    FloatBall背景 = ImAgeHeadFile1(背景, sizeof(背景));
   
    悬浮窗图标 = ImAgeHeadFile(图片数据, sizeof(图片数据)); 
    获取头像2();
    获取图标();
    获取其他图标();
    int pdys = 读取();
    ImGui_ImplOpenGL3_Init("#version 300 es");
    
        
    io.IniFilename = NULL;
    static ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    io.Fonts->AddFontFromMemoryTTF((void *) OPPOSans_H, OPPOSans_H_size, 32.0f, &font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    io.Fonts->AddFontDefault(&font_cfg);
    ImGui::GetStyle().ScaleAllSizes(3.0f);
    
    
        io.ConfigWindowsMoveFromTitleBarOnly = true;
        io.IniFilename = NULL;

        static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;
            ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;
            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;
			ImFontConfig cfg;
      cfg.SizePixels = ((float) density / 20.0f);
    //===================
	ImFontConfig font_config;
    font_config.PixelSnapH = false;
    font_config.OversampleH = 5;
    font_config.OversampleV = 5;
    font_config.RasterizerMultiply = 1.2f;
    static const ImWchar ranges[] ={ 0x0020, 0x00FF,  0x0400, 0x052F,  0x2DE0, 0x2DFF,  0xA640, 0xA69F,  0xE000, 0xE226,  0x2010, 0x205E,  0x0600, 0x06FF,  0xFE00, 0xFEFF,  0, };
	//========================𝗙𝗢𝗡𝗧𝗦
    font_config.GlyphRanges = ranges;
	io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom3), sizeof(Custom3), 25.f, &CustomFont);
	F48 = io.Fonts->AddFontFromMemoryTTF((void *)New1_data, New1_size, 25.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	JAAT = io.Fonts->AddFontFromMemoryTTF((void *)Chi_data, Chi_size, 25.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	F50 = io.Fonts->AddFontFromMemoryTTF((void *)F50_data, F50_size, 30.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	SOCIAL = io.Fonts->AddFontFromMemoryTTF((void *)F87_data, F87_size, 30.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	

//===============================| 𝗘𝗦𝗣 𝗖𝗢𝗟𝗢𝗥𝗦 |================================== //

        Config.ColorsESP.BotVisLine = CREATE_COLOR(255, 255, 255, 255);
		Config.ColorsESP.BotHideLine = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.PlayerVisLine = CREATE_COLOR(0, 255, 0, 255);
        Config.ColorsESP.PlayerHideLine = CREATE_COLOR(255, 0, 0, 255);
        Config.ColorsESP.BotVisBox = CREATE_COLOR(255, 255, 255, 255);
        Config.ColorsESP.BotHideBox = CREATE_COLOR(255, 255, 0, 255);
        Config.ColorsESP.PlayerVisBox = CREATE_COLOR(0, 0, 0, 255);
        Config.ColorsESP.PlayerHideBox = CREATE_COLOR(255, 0, 0, 255);
		Config.ColorsESP.BotVisSkeleton = CREATE_COLOR(255, 255, 255, 255);
		Config.ColorsESP.BotHideSkeleton = CREATE_COLOR(200, 200, 0, 255);
        Config.ColorsESP.PlayerVisSkeleton = CREATE_COLOR(0, 0, 255, 255);
        Config.ColorsESP.PlayerHideSkeleton = CREATE_COLOR(255, 0, 0, 255);
		Config.ColorsESP.BotRadar = CREATE_COLOR(255, 255, 255, 255);
		Config.ColorsESP.PlayerRadar = CREATE_COLOR(0, 255, 0, 255);
		Config.ColorsESP.BotAlert = CREATE_COLOR(255, 255, 0, 255);
		Config.ColorsESP.PlayerAlert = CREATE_COLOR(0, 255, 0, 255);
		Config.ColorsESP.Fov = CREATE_COLOR(255, 255, 255, 255);
		Config.ColorsESP.Fova = CREATE_COLOR(0, 0, 255, 255);
		FOVT = 4.5f;
		FOVTB = 4.7f;
        Config.SilentAim.Pred = true;
        Config.Prid = 600.0f;
        Config.SilentAim.TargetLine = true;
        Config.AimBot.TargetLine = true;
        Config.IpadS = 87.0f;
        Config.SilentAim.Cross  = 350.0f;
		Config.AimBot.Cross  = 400.0f;
		Config.SilentAim.Meter  = 400.0f;
		Config.AimBot.Meter  = 400.0f;
		Config.AimBot.Recc  = 1.01f;
        Config.RadarX = 2.3f;
		Config.RadarY = 100.0f;
        Config.Line = 1.4f;
        Config.Skeleton = 1.3f;
        Config.Loot = 99.0f;
    g_Initialized = true;	
}


void 绘制图标(ImVec2 中心点, float 尺寸)
{
    ImVec2 纹理尺寸 = ImVec2(尺寸, 尺寸);  // 调整图像大小
    ImVec2 左上角 = ImVec2(中心点.x - 纹理尺寸.x * 0.5f, 中心点.y - 纹理尺寸.y * 0.5f);
    ImVec2 右下角 = ImVec2(中心点.x + 纹理尺寸.x * 0.5f, 中心点.y + 纹理尺寸.y * 0.5f);
ImGui::GetWindowDrawList()->AddImage(悬浮窗图标, 左上角, 右下角, ImVec2(0, 0), ImVec2(1, 1));
}
int my_image_width = 80;
int my_image_height = 80;


/*
#define PI 3.141592653589793238
void drawHexagonStar(float x, float y, float size, float rotation, ImDrawList* drawList, ImU32 color){
const int numPoints = 6; // 六角星有6个顶点
ImVec2 center(x, y);
ImVec2 points[numPoints];
for (int i = 0; i < numPoints; i++)
{
float angle = rotation + 2 * PI * i / numPoints;
points[i] = ImVec2(center.x + size * cos(angle), center.y + size * sin(angle));
}
// 绘制两个大三角形
drawList->AddLine(points[0], points[2], color, 3.0f);
drawList->AddLine(points[2], points[4], color, 3.0f);
drawList->AddLine(points[4], points[0], color, 3.0f);
drawList->AddLine(points[1], points[3], color, 3.0f);
drawList->AddLine(points[3], points[5], color, 3.0f);
drawList->AddLine(points[5], points[1], color, 3.0f);
}

void DrawLogo(float x, float y, float size, float size2){
// 添加绘制六角星并旋转的代码
static float rotation = 0.0f; // 初始旋转角度
rotation += 0.005f; // 调整旋转速度
// 获取绘图列表
ImDrawList* drawList = ImGui::GetWindowDrawList();
// 在指定位置绘制一个黄色六角星，大小为size，旋转角度为rotation
drawHexagonStar(x, y, size, rotation, drawList, IM_COL32(255, 255, 0, 255));

// 添加绘制逆时针旋转的六角星的代码
static float rotation2 = 0.5f; // 初始旋转角度
rotation2 -= 0.1f; // 调整旋转速度
// 在指定位置绘制一个蓝色六角星，大小为size，旋转角度为rotation2
drawHexagonStar(x, y, size2, rotation2, drawList, IM_COL32(0, 255, 0, 255));

}
*/


#include <chrono>
#include <iomanip>
#include <sstream>

// 获取当前时间并格式化为字符串
std::string GetCurrentTime() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto now_c = system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %X"); // 格式化为年-月-日 时:分:秒
    return ss.str();
}

void 天理图片纹理(ImVec2 center) {
    // 获取当前悬浮窗的左上角位置
    ImVec2 windowPos = ImGui::GetWindowPos();
    // 计算图片的绘制位置（相对于悬浮窗的偏移）
    ImVec2 imgPos = ImVec2(windowPos.x + center.x +12, windowPos.y + center.y + 22);
    // 获取绘图列表
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    // 绘制图片，使用默认的宽高比例
    draw_list->AddImage(FloatBall天理, imgPos, ImVec2(imgPos.x +239, imgPos.y+68 ));
}

void 背景图片纹理(ImVec2 center) {
    // 获取当前悬浮窗的中心位置
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowCenter = ImVec2(windowPos.x + ImGui::GetWindowSize().x / 2, windowPos.y + ImGui::GetWindowSize().y / 2);
    // 计算图片的绘制位置（相对于悬浮窗的偏移）
    ImVec2 imgPos = ImVec2(windowCenter.x - 598 , windowCenter.y - 478);
    // 获取绘图列表
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    // 绘制图片，宽高比例
    draw_list->AddImage(FloatBall背景, imgPos, ImVec2(imgPos.x + 1200, imgPos.y + 970));
}


void tick(){
    ImGuiIO& io = ImGui::GetIO();
    if (display == EGL_NO_DISPLAY)
        return;
	
    // 从文件中读取卡密内容
    std::string kmFilePath = "/sdcard/.km"; // 卡密文件路径
    std::string g_kamiContent = GetKamiContent(kmFilePath);
	
    static ImVec4 clear_color = ImVec4(0, 0, 0, 0);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(init_screen_x, init_screen_y);
    ImGui::NewFrame();
	Colors::Borders = ImColor(60,60,60,255);
        Colors::BordersActive = ImColor(60,60,60,255);
		Colors::Text = ImColor(255,255,255,255/2);
        Colors::TextActive = ImColor(255,255,255,255);
        Colors::TextActiveNew = ImColor(255,255,255);
        Colors::TextNew = ImColor(255,255,255);
        Colors::FrameHovered = ImColor(0,0,0,255);
        Colors::FrameOpened = ImColor(0,0,0,255);
//===============================================| 𝗟𝗢𝗚𝗜𝗡 𝗣𝗔𝗚𝗘  |======================≠=================//
				ImVec2 pos;
                ImDrawList* draw;
                
                static int TAB = 1;
            	
				

				
			
                
                
static bool IsBall = true;
static float ANIM_SPEED = 0.25f;
static float Velua = IsBall ? 0.0f : 1.0f;


Velua = ImClamp(Velua + (io.DeltaTime / ANIM_SPEED) * (IsBall ? 1.0f : -1.0f), 0.0f, 1.0f);
if ((1190 * Velua) <= 1190 && (950 * Velua) <= 950) {
ImGui::SetWindowSize("##MORISHIMA CHEAT", {1190 * Velua, 950 * Velua});
} else if ((1190 * Velua) >= 100 && (950 * Velua) >= 100) {
ImGui::SetWindowSize("##MORISHIMA CHEAT", {1190 * Velua, 950 * Velua});
} if ((1190 * Velua) <= 100 && !IsBall) {BallSwitch = true;悬浮窗 = false;}
  if ((950 * Velua) <= 100 && !IsBall) {
  if (窗口状态item) {
      窗口状态 = true;
      窗口状态item = false;
    }
    悬浮球 = false;悬浮窗 = false;
  }
  

  if (悬浮球)
  {
    ImGui::SetNextWindowSize({200, 200});
 if (ImGui::Begin("悬浮", &悬浮球,  ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar))
    {
    if (关闭){
	   /*
       float starX = Pos.x + 50;
	   float starY = Pos.y + 50;
       float starSize = 40.0f; // 设置六角星的大小
       float starSize2 = 40.0f; 
	   */
       DrawLogo({Pos.x + 50, Pos.y + 50}, 70);         
   
    
    if (窗口状态) {
       ImGui::SetWindowPos("悬浮图片",Pos,ImGuiCond_Always);
       窗口状态 = false;
    }
      Pos = ImGui::GetWindowPos();
      ImDrawList* Draw = ImGui::GetWindowDrawList();
      static bool isDragging = false;
   if (ImGui::IsItemActive()) {
   if (!IsDown) {
      IsDown = true;
      ImagePos = ImGui::GetWindowPos();
   }
   } else if (IsDown) {
   IsDown = false;
if (ImagePos.x == ImGui::GetWindowPos().x && ImagePos.y == ImGui::GetWindowPos().y) {
   悬浮窗 = true;
   悬浮球 = false;
   ImGui::SetWindowPos("Tomato", Pos, ImGuiCond_Always);
   }
  }
 }
} 
   ImGui::End();
 }
  
                
				if(悬浮窗){
        		ImGui::SetNextWindowSize( ImVec2(1190, 950) );
        		ImGui::MainBegin( "Menu", nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration |  ImGuiWindowFlags_NoBackground);{
        		
        		if (窗口状态) {
                ImGui::SetWindowPos("Tomato",Pos,ImGuiCond_Always);
                窗口状态 = false;
                }
				
		    	const ImVec2 pos = ImGui::GetWindowPos();
                ImDrawList* draw = ImGui::GetWindowDrawList();
				
//=====================================| DRAWINGS |=================================//			
				draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 1), ImVec2(pos.x + 1190, pos.y + 950), ImColor(0,0,0,255), 12); 
				背景图片纹理(ImVec2(0, 0));
				draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 1), ImVec2(pos.x + 330, pos.y + 940), ImColor(24,24,24,205), 12, ImDrawFlags_RoundCornersLeft); //左边矩形背景
				draw->AddRectFilled(ImVec2(pos.x + 353, pos.y + 8), ImVec2(pos.x + 1030, pos.y + 100), ImColor(24,24,24,205), 12); //顶上背景1(卡密背景）
				draw->AddRectFilled(ImVec2(pos.x + 1050, pos.y + 8), ImVec2(pos.x + 1160, pos.y + 100), ImColor(24,24,24,205), 12); //顶上背景2(缩小背景)
                draw->AddRectFilled(ImVec2(pos.x + 30, pos.y + 800), ImVec2(pos.x + 300, pos.y + 900), ImColor(40,40,40,235), 12 ); //左边小矩形背景[下]
			    
				ImGui::SetCursorPos(ImVec2(360, -25));
				ImGui::SetWindowFontScale(1.3f);//字体大小   
				ImGui::TextColored(ImVec4(1.0f, 0.753f, 0.796f, 1.0f), "\n 当前邀请卡:  %s", g_kamiContent.c_str());
				ImGui::SetWindowFontScale(0.8f);//字体大小    
				ImGui::TextColored(ImVec4(0.9f, 0.9f, 0.9f, 0.8f), "                                                                <-内部版本-> 请低调使用 切勿截图乱发 如有发现直接删卡处理！！！");
				ImGui::SetWindowFontScale(1.0f);//字体大小   
                     
//=====================================| MAIN BUTTONS |=================================//
               
             
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 25, 10 });
                ImGui::SetCursorPos({ 15, 40});
               
		        ImGui::BeginGroup();{           
				天理图片纹理(ImVec2(30, 15));	
				
                ImGui::SetCursorPos({ 15, 140}); //位置函数                 
				std::string currentTime = GetCurrentTime();
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f),"%s", currentTime.c_str()); //当前时间      
				
				ImGui::SetCursorPos({ 15, 210}); //位置函数   
                if (ImGui::TAB("A","绘制", TAB != 1)) { TAB = 1; active = true; }
                if (ImGui::TAB("W","触摸", TAB != 2)) { TAB = 2; active = true; }
                if (ImGui::TAB("S","调节", TAB != 3)) { TAB = 3; active = true; }
                if (ImGui::TAB("P","功能", TAB != 4)) { TAB = 4; active = true; }
                if (ImGui::TAB("Y","退出", TAB != 5)) { TAB = 5; exit(0); }
                
                
				ImGui::SetCursorPos({ 30, 820});//位置函数   
                ImGui::SetWindowFontScale(0.8f);//字体大小    
				ImGui::TextColored(ImVec4(1.0f, 0.753f, 0.796f, 1.0f), "当前程序:王者荣耀(正式版)");
				ImGui::SetCursorPos({ 30, 855});//位置函数   
				ImGui::TextColored(ImVec4(1.0f, 0.753f, 0.796f, 1.0f), "版本号:V1.0");      
				ImGui::SetWindowFontScale(1.0f);//字体大小   
                            
                }ImGui::EndGroup();
                ImGui::PopStyleVar();	
                
                ImGui::SetCursorPos({ 950 - 75 - 75, 25});
                if(ImGui::OptButton("##ALERTS", ImVec2(50,50), false)){INFO = !INFO;}
                ImGui::SetCursorPos({ 950 - 75,  25});
                if(ImGui::OptButton("##HIDE", ImVec2(50,50), false)){
                窗口状态item = true;
                }
             
				
                ImGui::SetCursorPos(ImVec2(1053, 5));
                if (ImGui::TAB("Z", "\n    缩小", TAB != 6, true)) { //第四个参数开启使用自定义样式
                   悬浮窗 = false;
                   悬浮球 = true;
                }
				
 
				
                                
                                                       
                                                                      
                                                                                                    
                                                                                                    
//=====================================| TAB-1 |=================================//
                
                
		   ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 25, 12 });
		   if (TAB == 1){
	           ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 0)); // 黑色边框	        
		        	        	        
		       ImGui::SetCursorPos( ImVec2( 350, 110  ) );  
           if (ImGui::BeginChild("##第一", ImVec2(0, 0), true,  ImGuiWindowFlags_NavFlattened)) 
    		  { 
               
		        
          ImGui::SetCursorPos( ImVec2( 0, 7  ) );
          ImGui::MenuChild( "天理1", ImVec2(815, 110) );{ 
		    ImGui::SetCursorPos( ImVec2( 7,-5) );
		  // 根据当前状态动态更新按钮标签
		  const char* buttonLabel = isInitialized ? "游戏总开关        ｜ 开启" : "游戏总开关        ｜ 关闭";

		  // 设置按钮文本颜色
		  ImVec4 textColor = isInitialized ? ImVec4(0.0f, 1.0f, 0.0f, 1.0f) : ImVec4(1.0f, 0.0f, 0.0f, 1.0f); //开关按钮的字体颜色

		  // 保存当前的文本颜色样式
		  ImGuiStyle& style = ImGui::GetStyle();
		  ImVec4 oldTextColor = style.Colors[ImGuiCol_Text];

		  // 设置新的文本颜色
		  style.Colors[ImGuiCol_Text] = textColor;

			// 按钮逻辑
			if (ImGui::Button(buttonLabel, ImVec2(800, 100)))
			{
  			  // 切换状态
  			  isInitialized = !isInitialized;

   			 // 根据状态设置变量值
   			 if (isInitialized)
   			 {
				 // 开启状态
				 DrawInit();
       			 huitu = 1;
       			 血量 = 1;
        		 地图 = 1;
       			 射线 = 1;
       			 辅助方框 = 1;
       			 视野方框 = 1;
      		     方框 = 1;
     		     野怪 = 1;
      		     野血 = 1;
       			 兵线 = 1;
       			 实体兵线 = 1;
        		 方框技能 = 1;
        		 顶上技能 = 1;
        		 自身 = 1;   
   			 }
   			 else
   			 {
       			 // 关闭状态
      			  huitu = 0;
    			  血量 = 0;
     			  地图 = 0;
      			  射线 = 0;
      			  辅助方框 = 0;
     			  视野方框 = 0;
     			  方框 = 0;
       			  野怪 = 0;
       			  野血 = 0;
        		  兵线 = 0;
       			  实体兵线 = 0;
        		  方框技能 = 0;
        		  顶上技能 = 0;
       			  自身 = 0;
    			 }
			 }
	    // 恢复原来的文本颜色
	    style.Colors[ImGuiCol_Text] = oldTextColor;
        }ImGui::EndChild( );
		
        ImGui::SetCursorPos( ImVec2( 0, 90 + 46  ) );
        ImGui::MenuChild( "天理2", ImVec2(400, 80 - 80 + 80) );{ 
		if (ImGui::Combo("实体绘图", &绘图, "实体绘图1\0实体绘图2\0")) {
        if (绘图 == 0) {
            方框技能= true;
            方框技能旧= false; 
        } else if (绘图 == 1) {
            方框技能旧= true;
            方框技能= false; 
            }
          }                                                             
        }ImGui::EndChild( );       
		
        ImGui::SetCursorPos( ImVec2( 420, 90 + 46 ) );
        ImGui::MenuChild( "天理3", ImVec2(400, 80 - 80 + 80) );{           
        if (ImGui::Combo("过录屏", &style_zx, "过录屏开(重启辅助生效)\0过录屏关(重启辅助生效)\0")) {
    	if (style_zx == 0) {
   		    system("touch /data/内部配置/防录屏 >/dev/null 2>&1");
   		    } else if (style_zx == 1) {
   		    remove("/data/内部配置/防录屏");
            }
          }
        }ImGui::EndChild( ); 
		
        ImGui::SetCursorPos( ImVec2( 0, 180 + 60 ) );
        ImGui::MenuChild( "天理4", ImVec2(400, 80 - 80 + 80) );{           
        ImGui::Checkbox("射线开关", &射线);
                           }ImGui::EndChild( ); 
						   
        ImGui::SetCursorPos( ImVec2( 420, 180 + 60 ) );
        ImGui::MenuChild( "天理5", ImVec2(400, 80 - 80 + 80) );{           
        ImGui::Checkbox("人物血量", &血量);
                           }ImGui::EndChild( );                                     
              
        ImGui::SetCursorPos( ImVec2( 0, 270 + 60 ) );
        ImGui::MenuChild( "天理6", ImVec2(400, 80 - 80 + 80) );{           
        ImGui::Checkbox("自身视野", &自身);
                           }ImGui::EndChild( );          
              
        ImGui::SetCursorPos( ImVec2( 420, 270 + 60 ) );
        ImGui::MenuChild( "天理8", ImVec2(400, 80 - 80 + 80) );{           
        ImGui::Checkbox("兵线绘制", &兵线);
                           }ImGui::EndChild( );  
						   
        ImGui::SetCursorPos( ImVec2( 0, 360 + 60 ) );
        ImGui::MenuChild( "天理9", ImVec2(400, 80 - 80 + 80) );{           
        ImGui::Checkbox("野怪计时", &野怪);
                           }ImGui::EndChild( );    
						   
        ImGui::SetCursorPos( ImVec2( 420, 360 + 60 ) );
        ImGui::MenuChild( "天理10", ImVec2(400, 80 - 80 + 80) );{ 
        ImGui::Checkbox("小地图辅助对齐方框", &辅助方框);
        }ImGui::EndChild( );                                            
            
              ImGui::SetCursorPos( ImVec2( 0, 450 + 60 ) );
        ImGui::MenuChild( "天理11", ImVec2(400, 80 - 80 + 80) );{           
              ImGui::Checkbox("英雄技能计时", &顶上技能);
                           }ImGui::EndChild( );           
                
               ImGui::SetCursorPos( ImVec2( 420, 450 + 60 ) );
        ImGui::MenuChild( "天理12", ImVec2(400, 80 - 80 + 80) );{           
              ImGui::Checkbox("地图头像", &地图);
                           }ImGui::EndChild( );  
                ImGui::SetCursorPos( ImVec2( 0, 540 + 60 ) );
        ImGui::MenuChild( "天理13", ImVec2(400, 80 - 80 + 80) );{           
              ImGui::Checkbox("方框开关", &方框);
                           }ImGui::EndChild( );             
                              
                ImGui::SetCursorPos( ImVec2( 420, 540 + 60 ) );
        ImGui::MenuChild( "天理14", ImVec2(400, 80 - 80 + 80) );{           
              ImGui::Checkbox("野怪实体血量", &野血);
                           }ImGui::EndChild( );                    
                                       
   ImGui::SetCursorPos( ImVec2( 0, 630 + 60 ) );
        ImGui::MenuChild( "天理15", ImVec2(400, 80 - 80 + 80) );{           
              ImGui::Checkbox("一,二技能开关", &小技能计时);
                           }ImGui::EndChild( );      
   
   ImGui::SetCursorPos( ImVec2( 420, 630 + 60 ) );
        ImGui::MenuChild( "天理16", ImVec2(400, 80 - 80 + 80) );{           
              ImGui::Checkbox("小地图大招计时开关", &地图大招计时);
                           }ImGui::EndChild( ); 
   
   
               
                                   }

                    ImGui::EndChild( );    
             
                           
                }//1窗口
                
                
              
//=====================================| TAB-2 |=================================//
				
			
       if (TAB == 2){       
		  ImGui::SetCursorPos( ImVec2( 350, 110 ) );
          ImGui::MenuChild("##第二", ImVec2(810, 800));
{
    if (触摸驱动) {
        绘制触摸 = true;
        ImGui::Text("当前分辨率: %dx%d", screen_x, screen_y);  
        ImGui::Separator(); // 横线分割       
        ImGui::Text("帧率 %.1f FPS", ImGui::GetIO().Framerate);
        ImGui::Text("召唤师: %s ", 召唤师.c_str());
        ImGui::Text("技能: %s", 召唤师技能.c_str());
        ImGui::Separator();
        ImGui::Checkbox("自动斩杀", &自动斩杀);
        if (自动斩杀) {
            自动惩戒 = false;
            自动净化 = false;
        }
        ImGui::Checkbox("自动惩戒", &自动惩戒); 
        if (自动惩戒) {
            自动斩杀 = false;
            自动净化 = false;
        }
        ImGui::Checkbox("自动解控", &自动净化);
        if (自动净化) {
            自动斩杀 = false;
            自动惩戒 = false;         
        }
        ImGui::ItemSize(ImVec2(0, 1));
        ImGui::Separator();
        if (自动惩戒) {
            ImGui::Checkbox("附近有人时惩戒", &智能不惩);
            ImGui::Separator();
        }
        if (自动斩杀) {
            ImGui::Checkbox("自动计算斩杀线", &智能斩杀);
            if (!智能斩杀) {
                if (ImGui::SliderFloat("斩杀百分比", &zhansha, 10.0f, 20.0f, "%.1f", 2)) {
                    char urlls[2560];
                    sprintf(urlls, "%.1f", zhansha);
                    写出文件("/data/内部配置/斩杀值", urlls);
                }
            }
            ImGui::Separator();
        }
        ImGui::ItemSize(ImVec2(0, 1));
        if (ImGui::SliderInt("触摸位置X轴", &zhsX, 1, 3000, "%.0f", 2)) {
            char urlls[2560];
            sprintf(urlls, "%d", zhsX);
            写出文件("/data/内部配置/召唤师技能X", urlls);
        }
        if (ImGui::SliderInt("触摸位置Y轴", &zhsY, 1, 3000, "%.0f", 2)) {
            char urlls[2560];
            sprintf(urlls, "%d", zhsY);
            写出文件("/data/内部配置/召唤师技能Y", urlls);
        }
    }
}
ImGui::EndChild(); // 闭合 ImGui::MenuChild
    }    
                
                
                
//=====================================| TAB-3 |=================================//
				           
                
                if (TAB == 3){
                ImGui::SetCursorPos( ImVec2( 350, 110  ) ); 
                ImGui::MenuChild( "##第三", ImVec2(400, 665) );{
                
                if (ImGui::SliderInt("地图左右", &SmallMapX, -200, 200, "%.0f", 2)) {
                char urlls[2560];
                sprintf(urlls, "%d", SmallMapX);
                写出文件("/data/内部配置/头像X", urlls);
              }

              if (ImGui::SliderInt("地图上下", &SmallMapY, -200, 200, "%.0f", 2)) {
                char urlls[2560];
                sprintf(urlls, "%d", SmallMapY);
                写出文件("/data/内部配置/头像Y", urlls);
              }

              if (ImGui::SliderInt("头像大小", &touxiangdaxiao, -300, 300,
                                   "%.0f", 2)) {
                char urlls[2560];
                sprintf(urlls, "%d", touxiangdaxiao);
                写出文件("/data/内部配置/头像大小", urlls);
              }

              if (ImGui::SliderInt("血量大小", &xiaodituxue, -80, 80, "%.0f",
                                   2)) {
                char urlls[2560];
                sprintf(urlls, "%d", xiaodituxue);
                写出文件("/data/内部配置/血量大小", urlls);
              }

              if (ImGui::SliderInt("实体左右", &SmallHPX, -300, 300, "%.0f", 2)) {
                char urlls[2560];
                sprintf(urlls, "%d", SmallHPX);
                写出文件("/data/内部配置/实体X", urlls);
              }
              if (ImGui::SliderInt("实体上下", &SmallHPY, -300, 300, "%.0f", 2)) {
                char urlls[2560];
                sprintf(urlls, "%d", SmallHPY);
                写出文件("/data/内部配置/实体Y", urlls);
              }

               
 
              
                
                Config.AimBot.Recoil = true;          




                }ImGui::EndChild( );
        
        
                ImGui::SetCursorPos( ImVec2( 760, 110  ) ); 
                ImGui::MenuChild( "天理窗口15", ImVec2(400, 665) );{
                
             if (ImGui::SliderInt("技能栏左右", &jinenglanzX, -2000, 2000, "%.0f",
                                   2)) {
                char urlls[2560];
                sprintf(urlls, "%d", jinenglanzX);
                写出文件("/data/内部配置/技能栏X", urlls);
              }
          
                
                
           if (ImGui::SliderInt("技能栏上下", &jinenglanzY, -500, 500, "%.0f",
                                   2)) {
                char urlls[2560];
                sprintf(urlls, "%d", jinenglanzY);
                写出文件("/data/内部配置/技能栏Y", urlls);
              }

              if (ImGui::SliderInt("自身视野左右", &屏幕x, -100, 100, "%.0f", 2)) {
                char urlls[2560];
                sprintf(urlls, "%d", 屏幕x);
                写出文件("/data/内部配置/视野X", urlls);
              }

              if (ImGui::SliderInt("自身视野上下", &屏幕y, -200, 200, "%.0f", 2)) {
                char urlls[2560];
                sprintf(urlls, "%d", 屏幕y);
                写出文件("/data/内部配置/视野Y", urlls);
              }
			  
			  
              if (ImGui::SliderInt("地图比例", &jiange, -100, 100, "%.0f", 2)) {
                char urlls[2560];
                sprintf(urlls, "%d", jiange);
                写出文件("/data/内部配置/地图比例", urlls);
              }
              
   /*           
       if (ImGui::SliderInt("技能计时大小1", &yxpx, 0.1, 3, "%.0f", 1.5)) {
                char urlls[2560];
                sprintf(urlls, "%d", yxpx);
                写出文件("/data/内部配置/技能计时大小1", urlls);
              } 
       
     if (ImGui::SliderInt("技能计时大小2", &yxpy, 0.1, 3, "%.0f", 1.5)) {
                char urlls[2560];
                sprintf(urlls, "%d", yxpy);
                写出文件("/data/内部配置/技能计时大小2", urlls);
              }                
                   */                           
               }ImGui::EndChild( );  
				   
			   ImGui::SetCursorPos( ImVec2( 350, 790 ) ); 
               ImGui::MenuChild( "天理窗口11", ImVec2(810, 120) );{
               ImGui::Checkbox("音量控制悬浮窗", &音量控制);
               if (音量控制){
                  关闭=false;
                  }else{
                  关闭=true;
               }
               }ImGui::EndChild( ); 
				   
             }
                
//=====================================| TAB-4 |=================================//
                           	   
		       
                
             if (TAB == 4){
                ImGui::SetCursorPos( ImVec2( 350, 110  ) ); 
                ImGui::MenuChild( "##第四", ImVec2(810, 365) );{        
                ImGui::ColorEdit3("射线颜色", (float *)&颜色配置.射线颜色);
				ImGui::ColorEdit3("方框颜色", (float *)&颜色配置.方框颜色);
				ImGui::ColorEdit3("有视野血量颜色", (float *)&颜色配置.有视野血量颜色);
                ImGui::ColorEdit3("无视野血量颜色", (float *)&颜色配置.无视野血量颜色);
                }
				ImGui::SetCursorPos( ImVec2( 10,250) );
        	    if (ImGui::OptButton1("保存颜色配置", {790, 85})) {
                string SaveFile;
                SaveFile = "/data/内部配置/颜色配置";
                pdys = SaveDrawSet((总颜色 *)&颜色配置, SaveFile.c_str());                                                     
                }ImGui::EndChild( );         
               

                ImGui::SetCursorPos( ImVec2( 350, 490  ) ); 
                ImGui::MenuChild( "WORLD ESP-88", ImVec2(810, 150) );{              
                ImGui::SetCursorPos( ImVec2( 185,0) );
				ImGui::Text(("天理绘制共享<房间号> : %s"),imei);
                ImGui::Checkbox("共享开关", &ESPMenu.是否开启共享);                          
                }ImGui::EndChild( );			
           
                                     
               ImGui::SetCursorPos( ImVec2( 350, 655  ) ); 
               ImGui::MenuChild( "天理窗口12", ImVec2(810, 255 ) );{   
               if (ImGui::SliderFloat("视距调节", &shangdi, 0.0f, 2.5f, "%.2f", 2)) {
                  char urlls[2560];
                  sprintf(urlls, "%.2f", shangdi);
                  写出文件("/data/内部配置/上帝", urlls);
                  }
                  ImGui::Text("");  
                  ImGui::Checkbox("视距开关", &上帝);             
                  }ImGui::EndChild( );    
				
                }
                
                
                
     
              
//=====================================| WIDGETS_EXPERT |=================================//
                
				//================
                //================
                }//函数
                }//悬浮窗
                ImGui::End();//悬浮窗
                
     	        ImGui::GetForegroundDrawList()->AddText(ImVec2(90, 1000), ImColor(255, 255, 255, 255), "@天理\nhttps://t.me/tianlinb888");
                
                
                
            if (huitu == 1) {
         DrawPlayer(); 
          }
          
          if (Orientation != displayInfo.orientation) {
             
             Touch::setOrientation(Orientation);
          }
    ImGui::Render();  
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    eglSwapBuffers(display, surface);
}

void shutdown(){
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

