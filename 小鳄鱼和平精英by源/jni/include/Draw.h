/*
    By 开源 公益分享
   搜集各个公益文件分享
    更多公益开源 文件 @BYYXnb
    TG @BYYXnb QQ群 427975011
    
源码捐赠链接
https://v.youxi186.com/shop/YIZ6ZA6X

源码捐赠地址2：
https://shop.pp13.cn/shop/byyxnb

公益网盘资源分享
https://www.123865.com/s/NxyZVv-K44U3?提取码：QWT6

QQ群过验证[有的文件需要]
https://www.123865.com/s/f4A7Vv-Pqc0A?提取码：9IVI

由于易支付漏洞 如果进不去
如您需拿卡 点击 联系我
赞助链接已重新更新 

〖如果你点开提示 站点停止运行或者进不去，那么解决办法有两个

1.复制链接去别的浏览器打开
2.清除你浏览器的数据即可
*/
#ifndef NATIVESURFACE_DRAW_H
#define NATIVESURFACE_DRAW_H
// System libs
#include <iostream>
#include <thread>
#include <chrono>
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
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES/gl.h>
#include <GLES3/gl3platform.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl32.h>

// User libs
#include "ImGui/ANativeWindowCreator.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_android.h"
#include "ImGui/TouchHelperA.h"

/*
#include "ImGui/imgui_impl_vulkan.h"
#include "Vulkan/VulkanUtils.h"
*/
#include "ImGui/imgui_impl_opengl3.h"

// namespace
using namespace std;
using namespace std::chrono_literals;

// 屏幕信息
extern android::ANativeWindowCreator::DisplayInfo displayInfo;

extern bool g_Initialized;
extern int Orientation;

extern ImGuiWindow *g_window;
// window创建的 大小
extern int native_window_screen_x, native_window_screen_y;
// 绝对屏幕X _ Y
extern int abs_ScreenX, abs_ScreenY;
// Func
bool init_egl(uint32_t _screen_x, uint32_t _screen_y, bool log = false);

bool initGUI_draw(uint32_t _screen_x, uint32_t _screen_y, bool log = false);

bool ImGui_init();

void screen_config();

void drawBegin();

void drawEnd();

void shutdown();

#endif //NATIVESURFACE_DRAW_H
