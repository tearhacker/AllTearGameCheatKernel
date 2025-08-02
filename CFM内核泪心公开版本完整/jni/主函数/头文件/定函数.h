#include "function.h"
#include "图标.h"
#include "图标字体.h"
#include <touch.h>
#include <array>
int style_idx = 0;
float NumIo[50];
bool DrawIo[50];//泪心 github tearhacker  电报 t.me/TearGame
string SaveDir;
FILE *numSave = nullptr;
ImColor 红色=ImColor(255,0,0,255);
ImColor 白色=ImColor(255,255,255,255);
ImColor 绿色=ImColor(0,255,0,255);
ImColor 粉色=ImColor(226,145,163,255);
ImColor 紫色=ImColor(15,67,255,255);
ImColor 黄色=ImColor(200,255,0,255);
ImColor 黑色=ImColor(0,0,0,255);
ImColor 蓝色=ImColor(0,167,241,255);
ImColor 棕色=ImColor(144,144,144,255);
ImColor 灰色=ImColor(10,40,40,205);
ImColor 空白=ImColor(0,0,0,0);
ImColor 人机血量颜色=ImColor(255,0,0,60);
ImColor 真人血量颜色=ImColor(0,255,0,60);
ImColor 浅蓝 = ImColor(ImVec4(36/255.f, 249/255.f, 217/255.f, 255/255.f));
ImColor 浅粉 = ImColor(ImVec4(255/255.f, 200/255.f, 250/255.f, 0.95f));
ImColor 半黑 = ImColor(ImVec4(0/255.f, 0/255.f, 0/255.f, 0.18f));
ImColor 血色 = ImColor(ImVec4(0/255.f, 249/255.f, 0/255.f, 0.35f));
ImColor 橘黄 = ImColor(ImVec4(255/255.f, 150/255.f, 30/255.f, 0.95f));
ImColor 粉红 = ImColor(ImVec4(220/255.f, 108/255.f, 1202/255.f, 0.95f));
ImColor 青绿 = ImColor(ImVec4(145/255.f,232/255.f,135/255.f,255/255.f));
ImColor RandomColor()
{
    int R, G, B, A = 180;
    R = (random() % 255);
    G = (random() % 255);
    B = (random() % 255);
    return ImColor(R, G, B, A);
}

ImColor ColorArr[100];
void 随机颜色函数()
{
    for(int i = 0; i < 100; i++) {
        ColorArr[i] = RandomColor();
    }
}
ImColor 随机颜色(int Num)
{
    if(Num < 99 && Num > 0) {
        return ColorArr[Num];
    } else {
        return ImColor(67, 205, 128, 150);
    }
}

void 绘制字体描边(float size,int x, int y, ImVec4 color, const char* str)
{
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x - 0.1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(color), str);
}

void 绘制四角方框(float X,float top,float W,float bottom)
{
ImGui::GetBackgroundDrawList()->AddLine({X, top}, {X+(W/4), top}, 白色, 2.5f);
ImGui::GetBackgroundDrawList()->AddLine({X+W, top}, {X+W-(W/4), top},白色, 2.5f);
ImGui::GetBackgroundDrawList()->AddLine({X, top}, {X, top+(W/4)},白色, 2.5f);
ImGui::GetBackgroundDrawList()->AddLine({X+W, top}, {X+W, top+(W/4)},白色, 2.5f);
ImGui::GetBackgroundDrawList()->AddLine({X, bottom}, {X+(W/4), bottom},白色, 2.5f);
ImGui::GetBackgroundDrawList()->AddLine({X+W, bottom}, {X+W-(W/4), bottom},白色, 2.5f);
ImGui::GetBackgroundDrawList()->AddLine({X, bottom}, {X, bottom-(W/4)},白色, 2.5f);
ImGui::GetBackgroundDrawList()->AddLine({X+W, bottom}, {X+W, bottom-(W/4)},白色, 2.5f);      
}

void DrawLine(float startx, float starty, float endx, float endy, float a, float r, float g, float b, float thickness) {
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(startx, starty), ImVec2(endx, endy), ImColor(r, g, b, a), thickness);
}

ImColor RectColor = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
float RectThickness = 2.0f;
float RectRounding  = 0.0f;


void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b, float rounding, float thickness) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), rounding, ImDrawFlags_RoundCornersAll, thickness);
}

void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b, float thickness) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), RectRounding, ImDrawFlags_RoundCornersAll, thickness);
}

void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, ImColor &color, float thickness) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), color, RectRounding, ImDrawFlags_RoundCornersAll, thickness);
}

void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, ImColor &color, float rounding, float thickness) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), color, rounding, ImDrawFlags_RoundCornersAll, thickness);
}

void DrawRect(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b) {
    ImGui::GetBackgroundDrawList()->AddRect(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), RectRounding, ImDrawFlags_RoundCornersAll, RectThickness);
}




ImColor RectFilledColor = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
 //默认四角半径
float   RectFilledRounding = 0.0f;
void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b, float rounding) {
  ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), rounding);
}

void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, float a, float r, float g, float b) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), ImColor(r, g, b, a), RectFilledRounding);
}

void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, ImColor &color, float rounding) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), color, rounding);
}

void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY, ImColor &color) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), color, RectFilledRounding);
}


void DrawRectFilled(float upper_leftX, float upper_leftY, float lower_rightX, float lower_rightY) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(upper_leftX, upper_leftY), ImVec2(lower_rightX, lower_rightY), RectFilledColor, RectFilledRounding);
}


bool cshzt=false;
bool 人物=false,载具=false,触摸自瞄=false,绘制骨骼,绘制血量,瞄准射线,阵容;
void *handle;
EGLDisplay display = EGL_NO_DISPLAY;
EGLConfig config;
EGLSurface surface = EGL_NO_SURFACE;
NativeWindowType native_window;
NativeWindowType (*createNativeWindow)(const char *surface_name ,uint32_t screen_width ,uint32_t screen_height);
EGLContext context = EGL_NO_CONTEXT;
float inttouchx = 300,inttouchy = 500;
Screen full_screen;
int Orientation = 0;
int screen_x = 0, screen_y = 0;
int init_screen_x = 0, init_screen_y = 0;
bool g_Initialized = false;

void ImGuiMenustyle()
{
auto io = &ImGui::GetIO();
static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
ImFontConfig icons_config;
ImFontConfig CustomFont;
CustomFont.FontDataOwnedByAtlas = false;
icons_config.MergeMode = true;
icons_config.PixelSnapH = true;
icons_config.OversampleH = 2.5;
icons_config.OversampleV = 2.5;
io->Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 23.0f, &icons_config, icons_ranges);
NumIo[3] = 300.0f;//自瞄范围
NumIo[4] = 10.0f;//自瞄速度
NumIo[6] = 1400.0f;//瞄准点Y
NumIo[5] = 650.0f;//瞄准点X
NumIo[7] = 150.0f;  //触摸范围
NumIo[0] = 0.0f;//瞄准方式|开火
NumIo[9] = 8.0f; //平滑力度
NumIo[10] = 0.0f; //判断充电口
NumIo[11] = 600.0f;//子弹速度
NumIo[24] = 6.0f;//fov瞄准
NumIo[26] = 18.0f;//枪械瞄准
}
static ImFont *Font_Big ;
void ImGui_init()
{
    if (g_Initialized) {
        return;
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;   
    ImGui::StyleColorsDark();
    ImGui_ImplAndroid_Init(native_window);
    ImGui_ImplOpenGL3_Init("#version 100");	
    io.Fonts->AddFontFromMemoryTTF((void *) OPPOSans_H, OPPOSans_H_size,25.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    ImGui::GetStyle().ScaleAllSizes(3.0f);
	ImGuiMenustyle();
    g_Initialized = true;	
}



float MIDDLE;
float XLX;
float top;
float bottom;
float left;
float right;
float X,Y,W;
float pmjl;

float DropM;
float 雷达视角;
long int VehiclePointer;
long int lib2cpp,unity,数组, 对象阵列, 矩阵, 自身对象, 对象指针;
int 自身队伍;
int 对象阵营,人机判断,死亡判断,自身阵营;
int 人物手持;
float 人物血量;
char 名字[100]; 
int 真人数量,人机数量,人物数量;
float 骨骼头部,转头部,骨骼膝盖;
uintptr_t 数量;
float 自瞄X,自瞄Y;
float MaxDistance = 300;
float FOV;
int 共量距离;
int 瞄准数量 = 0;
int 全部数量 = 0;
/* 人物数量 */
int ToReticleDistance;//到准心距离
float SlideX = 400.0f;//滑动位置X
float SlideY = 1200.0f;//滑动位置Y
int 最近范围=-1;
Vector2A 骨骼预瞄点;
float obj_x, obj_y, obj_z;
#define TIME 0.1

