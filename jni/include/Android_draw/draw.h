#ifndef NATIVESURFACE_DRAW_H
#define NATIVESURFACE_DRAW_H
  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
#include <iostream>
#include <thread>
#include <chrono>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <android/native_window.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"
#include <EGL/eglext.h>
#include <GLES3/gl3platform.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl32.h>
#include <sys/system_properties.h>
#include "ANativeWindowCreator.h"
#include<iostream>
#include<ctime>
#include "timer.h"
  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
using namespace std;
using namespace std::chrono_literals;
extern void *handle;// 动态库方案


extern EGLDisplay display;
extern EGLConfig config;
extern EGLSurface surface;
extern ANativeWindow *native_window;
extern EGLContext context;
struct Screen {
    float ScreenX;
    float ScreenY;
};
extern int FPS;
extern timer FPS限制;
extern float FPF显示;
extern bool 菜单;
extern int 进程进程;
extern float NumIo[50];
extern Screen full_screen;

// 屏幕信息
extern android::ANativeWindowCreator::DisplayInfo displayInfo;
// 绝对屏幕X _ Y
extern int abs_ScreenX, abs_ScreenY;
// 视图XY
extern int native_window_screen_x, native_window_screen_y;

extern int Orientation;
extern int screen_x, screen_y;
extern int init_screen_x, init_screen_y;
extern bool g_Initialized;
string exec(string command);
int init_egl(int _screen_x,int _screen_y, bool log = false);
void screen_config();
void screen_config2();
void shutdown();
void tick();
void ImGui_init();
void DrawPlayer( );
//  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
//void DrawPlayer();  QQ群435539500
void AimBotAuto();
void Getxfctouch();
void touch1();
void *AimCalcu();
void 游戏进程();
void DrawInt();
//int DrawInt();
void 分辨率();
#endif
