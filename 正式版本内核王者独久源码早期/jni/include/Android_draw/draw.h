#ifndef NATIVESURFACE_DRAW_H
#define NATIVESURFACE_DRAW_H
/**
by  独久
https://t.me/dujiunb


*/
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
#include <EGL/eglext.h>
#include <GLES3/gl3platform.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl32.h>
//#include "悬浮球.h"
#include "ANativeWindowCreator.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"
#include "TouchHelperA.h"//触摸
//#include "touch.h"

// namespace
using namespace std;
using namespace std::chrono_literals;

extern bool g_Initialized;
extern EGLDisplay display;
extern EGLConfig config;
extern EGLSurface surface;
extern EGLContext context;
extern ANativeWindow *native_window;


// 视图XY
extern int native_window_screen_x, native_window_screen_y;
extern int screen_x, screen_y;
// 屏幕信息
extern android::ANativeWindowCreator::DisplayInfo displayInfo;
// 绝对屏幕X _ Y
extern int abs_ScreenX, abs_ScreenY;



extern void screen_config();
extern int init_egl(int _screen_x,int _screen_y, bool log = false);
extern void ImGui_init();

extern void drawBegin();
extern void tick();
extern void drawEnd();
extern void shutdown();

void AimBotAuto(ImDrawList *Draw);
void createSocket() ;
void DrawPlayer();
void DrawInit();
int DrawInt();

int 音量();

#endif

