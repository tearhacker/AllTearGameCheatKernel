#include "泪心二改绘制.hpp"
#include "内存图片/悬浮窗.h"


Screen full_screen;
bool BallSwitch = true;
bool MemuSwitch = true; //开关
static bool IsBall = true;
static float ANIM_SPEED = 0.02f;
static float Velua = IsBall ? 0.0f : 1.0f;


int Orientation = 0;
int abs_ScreenX = 0, abs_ScreenY = 0;
int native_window_screen_x = 0, native_window_screen_y = 0;
android::ANativeWindowCreator::DisplayInfo displayInfo{0};
int screen_x = 0, screen_y = 0;
int init_screen_x = 0, init_screen_y = 0;
bool g_Initialized = false;
EGLDisplay display = EGL_NO_DISPLAY;
EGLConfig config;
EGLSurface surface = EGL_NO_SURFACE;
EGLContext context = EGL_NO_CONTEXT;
ANativeWindow *native_window;

//修复问题找泪心 2254013571 QQ号
//或者QQ3849081700


int init_egl(int _screen_x, int _screen_y, bool log){

system ("settings put system block_untrusted_touches 0");
system ("settings put global block_untrusted_touches 0");
system ("settings put secure block_untrusted_touches 0");

/*
    string 防录屏;
    puts("\n\n[+] 是否开启防录屏?(y/n):");
    cin >> 防录屏;
    if(防录屏 == "y"){
    native_window = android::ANativeWindowCreator::Create("Ssage", _screen_x, _screen_y, true);
	}
	if(防录屏 == "n"){
	native_window = android::ANativeWindowCreator::Create("Ssage", _screen_x, _screen_y, false);
	}
*/
native_window = android::ANativeWindowCreator::Create("TearGame", _screen_x, _screen_y, false );
ANativeWindow_acquire(native_window);
display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
if (display == EGL_NO_DISPLAY) {
printf("eglGetDisplay error=%u\n", glGetError());
return -1;
}
if(log){
printf("eglGetDisplay ok\n");
}
if (eglInitialize(display, 0, 0) != EGL_TRUE) {
printf("eglInitialize error=%u\n", glGetError());
return -1;
}
if(log){
printf("eglInitialize ok\n");
}
EGLint num_config = 0;
const EGLint attribList[] = {
EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
EGL_BLUE_SIZE, 5,//-->delete
EGL_GREEN_SIZE, 6,//-->delete
EGL_RED_SIZE, 5,//-->delete
EGL_BUFFER_SIZE, 32,//-->new field
EGL_DEPTH_SIZE, 16,
EGL_STENCIL_SIZE, 8,
EGL_NONE
};
if (eglChooseConfig(display, attribList, nullptr, 0, &num_config) != EGL_TRUE) {
printf("eglChooseConfigerror=%u\n", glGetError());
return -1;
}
if(log){
printf("num_config=%d\n", num_config);
}
if (!eglChooseConfig(display, attribList, &config, 1, &num_config)) {
printf("eglChooseConfigerror=%u\n", glGetError());
return -1;
}
if(log){
printf("eglChooseConfig ok\n");
}
EGLint egl_format;
eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &egl_format);
ANativeWindow_setBuffersGeometry(native_window, 0, 0, egl_format);
const EGLint attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
context = eglCreateContext(display, config, EGL_NO_CONTEXT, attrib_list);
if (context == EGL_NO_CONTEXT) {
printf("eglCreateContexterror = %u\n", glGetError());
return -1;
}

surface = eglCreateWindowSurface(display, config, native_window, nullptr);
if (surface == EGL_NO_SURFACE) {
printf("eglCreateWindowSurfaceerror = %u\n", glGetError());
return -1;
}

if (!eglMakeCurrent(display, surface, surface, context)) {
printf("eglMakeCurrenterror = %u\n", glGetError());
return -1;
}

return 1;
}
//修复问题找泪心 2254013571 QQ号
//或者QQ3849081700

 void screen_config()
{
    ::displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
    ::screen_x = displayInfo.width;
    ::screen_y = displayInfo.height;
  
}
        



void savesettings(){
                //添加配置
        char *ndhdh10=读取文件("/data/local/tmp/泪心glory配置/技能栏左右1");
            if(ndhdh10){jinenglanzX= atof(ndhdh10);}
            
            char *ndhdh11=读取文件("/data/local/tmp/泪心glory配置/技能栏上下1");
            if(ndhdh11){jinenglanzY= atof(ndhdh11);}
            char *ndhdh=读取文件("/data/local/tmp/泪心glory配置/小x1");
            if(ndhdh){SmallMapX= atof(ndhdh);}
            char *ndhdh2=读取文件("/data/local/tmp/泪心glory配置/小y1");
            if(ndhdh2){SmallMapY= atof(ndhdh2);}
            char *ndhdh3=读取文件("/data/local/tmp/泪心glory配置/大x1");
            if(ndhdh3){SmallHPX= atof(ndhdh3);}
            char *ndhdh5=读取文件("/data/local/tmp/泪心glory配置/大y1");
            if(ndhdh5){SmallHPY= atof(ndhdh5);}
            char *ndhdh991=读取文件("/data/local/tmp/泪心glory配置/头像间隔");
            if(ndhdh991){jiange= atof(ndhdh991);}
            char *ndhdh992=读取文件("/data/local/tmp/泪心glory配置/血量大小");
            if(ndhdh992){xiaodituxue= atof(ndhdh992);}
            char *ndhdh993=读取文件("/data/local/tmp/泪心glory配置/头像大小");
            if(ndhdh993){touxiangdaxiao= atof(ndhdh993);}
             char *ndhdh6669=读取文件("/data/local/tmp/泪心glory配置/顶上技能血");
            if(ndhdh6669){dingshanghealth= atof(ndhdh6669);}
            char *ndhds6669=读取文件("/data/local/tmp/泪心glory配置/小地图野怪左右");
            if(ndhds6669){monsterX= atof(ndhds6669);}
            char *ndhda993=读取文件("/data/local/tmp/泪心glory配置/小地图野怪上下");
            if(ndhda993){monsterY= atof(ndhda993);}
            
            
            //触摸功能  自身视野功能  召唤师技能触发坐标.x
            char *ndhdh9922=读取文件("/data/local/tmp/泪心glory配置/触摸位置x");
            if(ndhdh9922){召唤师技能触发坐标.x= atof(ndhdh9922);}
            char *ndhdh9933=读取文件("/data/local/tmp/泪心glory配置/触摸位置y");
            if(ndhdh9933){召唤师技能触发坐标.y= atof(ndhdh9933);}
            
                        //屏幕功能
            char *ndhdh99222=读取文件("/data/local/tmp/泪心glory配置/屏幕x");
            if(ndhdh99222){屏幕x= atof(ndhdh99222);}
            char *ndhdh99333=读取文件("/data/local/tmp/泪心glory配置/屏幕y");
            if(ndhdh99333){屏幕y= atof(ndhdh99333);}
            
            /*共享分辨率x调整
            共享兵线左右调整
            共享野怪上下调整
            共享野怪左右调整
            共享上下调整
            共享左右调整*/
               char *ndhdh6=读取文件("/data/local/tmp/泪心glory配置/共享左右调整");
            if(ndhdh6){ESPMenu.小地图左右调整= atof(ndhdh6);}
               char *ndhdh7=读取文件("/data/local/tmp/泪心glory配置/共享上下调整");
            if(ndhdh7){ESPMenu.小地图上下调整= atof(ndhdh7);}
               char *ndhdh8=读取文件("/data/local/tmp/泪心glory配置/共享兵线左右调整");
            if(ndhdh8){ESPMenu.兵线左右调整= atof(ndhdh8);}
            char *ndhdh91=读取文件("/data/local/tmp/泪心glory配置/共享野怪左右调整");
            if(ndhdh91){ESPMenu.野怪左右调整= atof(ndhdh91);}
            char *ndhdh101=读取文件("/data/local/tmp/泪心glory配置/共享野怪上下调整");
            if(ndhdh101){ESPMenu.野怪上下调整= atof(ndhdh101);}
            char *ndhdh111=读取文件("/data/local/tmp/泪心glory配置/共享分辨率x调整");
            if(ndhdh111){ESPMenu.分辨率X= atof(ndhdh111);}
}


//泪心源码@TearGame

//修复问题找泪心 2254013571 QQ号
//或者QQ3849081700

void ImGui_init(){
if (g_Initialized){
return;
}
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO();
io.IniFilename = NULL;
        封装色彩();
FloatBall = ImAgeHeadFile(icon, sizeof(icon));
FloatBallmenu= ImAgeHeadFile(menuicon, sizeof(menuicon));
FloatBallyulong= ImAgeHeadFile(悬浮球玉龙, sizeof(悬浮球玉龙));

ImGui_ImplAndroid_Init(native_window);
ImGui_ImplOpenGL3_Init("#version 300 es");
io.Fonts->AddFontFromMemoryTTF((void*)Morishima_data, Morishima_size, 38.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
ImGui::GetStyle().ScaleAllSizes(3.0f);


g_Initialized = true;


加载图片();
获取头像2();
获取图标();

//泪心源码@TearGame
savesettings();

}

//泪心源码@TearGame  卡网 自己找
//泪心源码@TearGame

//泪心源码@TearGame

void 上帝god()
{//泪心源码@TearGame
   //   long int god_address = driver->read<uint64_t>(driver->read<uint64_t>(lil2cpp_basebss + 0x5F80) + 0xB8) + 0x28C;
    //0x38450)+0x11A4
    //printf("%x",god_address);
    long int god_address = driver->read<uint64_t>(driver->read<uint64_t>(lil2cpp_basebss + 0x4DB0) + 0xB8) + 0xA0;  //0x4DB0+0xB8+0xA0
    driver->write<float>(god_address, godvalue);
}
void 上帝tear正常()
{
    long int a1 = driver->read<uint64_t>(driver->read<uint64_t>(lil2cpp_basebss + 0x5F80) + 0xB8) + 0x28C;
   driver->write<float>(a1,godvalue);//
}



 
//菜单绘制演示
void start()
{

if (display == EGL_NO_DISPLAY)
return;

ImGui_ImplOpenGL3_NewFrame();
ImGui_ImplAndroid_NewFrame(init_screen_x, init_screen_y);
screen_config();    
    static uint32_t orientation = -1;
    if (orientation != displayInfo.orientation) {
        orientation = displayInfo.orientation;
        Touch::setOrientation(displayInfo.orientation);
        //cout << " width:" << displayInfo.width << " height:" << displayInfo.height << " orientation:" << displayInfo.orientation << endl;
    }                  //原来值init_screen_x init_screen_y
        ImGui_ImplAndroid_NewFrame(native_window_screen_x, native_window_screen_y);
        ImGui::NewFrame();
}
void end()
{
ImGuiIO& io = ImGui::GetIO();
static ImVec4 clear_color = ImVec4(0, 0, 0, 0);
glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
eglSwapBuffers(display, surface);
}
void tick() {
  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
        
start();
  
///////////悬浮窗口呢
        {
ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
		
        Velua = ImClamp(Velua + (io.DeltaTime / ANIM_SPEED) * (IsBall ? 1.0f : -1.0f), 0.0f, 1.0f);
        if ((1150 * Velua) <= 1150 && (850 * Velua) <= 850) {
            ImGui::SetWindowSize("定制绘制", {900 * Velua, 720 * Velua});
        } else if ((850 * Velua) >= 100 && (850 * Velua) >= 100) {
            ImGui::SetWindowSize("定制绘制", {900 * Velua, 720 * Velua});
        } if ((1150 * Velua) <= 100 && !IsBall) {BallSwitch = true;MemuSwitch = false;}
        
if (BallSwitch)//悬浮球调整
{
    style.WindowRounding = 80.0f;
    if (ImGui::Begin("Ball", &BallSwitch,  ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar))
    {
        auto Pos = ImGui::GetWindowPos();
        Window = ImGui::GetCurrentWindow();
        
        
          DrawLogoyulong({Pos.x + 50, Pos.y + 50}, 70);
                 ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 size = ImGui::GetWindowSize();
        ImVec2 center = ImVec2(Pos.x + size.x / 2+2, Pos.y - 50 + size.y / 2-2);
       draw_list->AddCircle(center, size.x / 3, IM_COL32(148, 148, 148, 255), 40, 6.1f); // Add a thicker purple circle surrounding the ball
  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
        //自我悬浮窗多重设计
        //任性悬浮窗设计化
        
      
        if (ImGui::IsItemActive()) {
            if (!IsDown) {
                IsDown = true;
                ImagePos = ImGui::GetWindowPos();
            }
        } else if (IsDown) {
            IsDown = false;
            if(ImagePos.x == ImGui::GetWindowPos().x && ImagePos.y == ImGui::GetWindowPos().y) {
                IsBall = true;
                MemuSwitch = true;
                BallSwitch = false;
                ImGui::SetWindowPos("定制绘制", Pos, ImGuiCond_Always);
            }
        }
    }
    ImGui::End();
}
        }
        //悬浮窗已经完毕
  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
//@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
if (MemuSwitch) {

if (ImGui::Begin("定制绘制", &MemuSwitch, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar))
        {
				    //  ImGui::SetWindowSize({680, 650});
       
        		
        if (ImGui::BeginChild("##左侧菜单标题", ImVec2(170, 0), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NavFlattened));
        {
        /*
        auto Pos = ImGui::GetWindowPos();
  SpinnerIngYang(ImVec2(Pos.x+95, Pos.y+70), 50, 20, true, 35.0f, ImColor(255, 255, 255), ImColor(255, 0, 0), 2.0f * velocity, IM_PI * 0.8f); //双龙戏珠
        ImGui::SetCursorPos({0, 140});
        ImGui::Separator();
        ImGui::ItemSize(ImVec2(0, 1));
                */
                auto Pos = ImGui::GetWindowPos();
        		Window = ImGui::GetCurrentWindow();
             DrawLogomenu({Pos.x + 90, Pos.y + 90}, 130);
            
                
                if (ImGui::Button("主页", ImVec2(170, 105)))
    			{
    				MenuTab = 1;					
    			}

			    
    			if (ImGui::Button("绘图", ImVec2(170, 105)))
    			{
    				MenuTab = 2;
    			}
    		
    			if (ImGui::Button("设置", ImVec2(170, 105)))
    			{
    				MenuTab = 3;
    			}
    			
    			if (ImGui::Button("退出", ImVec2(170, 105)))
    			{
    				exit(0);
    			}
    		
    			  ImGui::EndChild();
    			
    			}
                
                                
                ImGui::SameLine();
                
          if (ImGui::BeginChild("##右菜单", ImVec2(-1, -1), false))
                {

    		ImGui::InvisibleButton("缩小", {ImGui::GetWindowWidth() - 125, 0});
    		
    		ImGui::SameLine();    				
    		  if (ImGui::ButtonTextColored(ImColor(255,0,255),"[缩小]")) {
    		//ImGui::SetWindowPos("悬浮图片", ImGui::GetWindowPos(), ImGuiCond_Always);
        //窗口状态item = true;
        IsBall = false;
    		}
    			if (ImGui::BeginChild("##绘图", ImVec2(0, 0), false,  ImGuiWindowFlags_NavFlattened)) 
        {
        switch (MenuTab) {
           
           case 1: {
            
           
           if(huitu==0){
if(ImGui::Button("开启辅助", ImVec2(-1, 75))){DrawInt();
                      huitu=1;血量=1;地图=1;射线=1;方框=1;野怪=1;兵线=1;方框技能=1;顶上技能=1;框头=1;回城=1;技陷=1;       自身判断=1;框技=0;野血=0;}
}else{
if(ImGui::Button("关闭绘制", ImVec2(-1, 75))){
huitu=0;血量=0;地图=0;射线=0;方框=0;野怪=0;兵线=0;方框技能=0;顶上技能=0;眼位=0;框技=0;框头=0;回城=0;技陷=0;                      }						  
}

 ImGui::Checkbox("射线", &射线);
ImGui::SameLine();
 ImGui::Checkbox("框技", &框技);
ImGui::SameLine();
ImGui::Checkbox("方框", &方框);
ImGui::SameLine();
ImGui::Checkbox("野血", &野血);

//ImGui::SameLine();
ImGui::Checkbox("兵线", &兵线);
ImGui::SameLine();
ImGui::Checkbox("兵血", &兵血);

ImGui::SameLine();
ImGui::Checkbox("野怪", &野怪);


ImGui::SameLine();
ImGui::Checkbox("地图", &地图);
					  
			if(ImGui::SliderFloat("", &godvalue, 1.2f, 2.2f, "%.2f", 1.0f))
                      {char urlls[2560];
	                  sprintf(urlls, "%.2f", godvalue);	
	                  写出文件("/storage/emulated/0/颜色/泪心绘制配置文件",urlls);
	                  写出文件("/storage/emulated/0/颜色/上帝高度",urlls);}
			 ImGui::SameLine();
			 if(ImGui::Button("设置上帝", ImVec2(-1, 55))){
                                上帝tear正常();
                                }
 
		    if (ImGui::Button("删除配置",{-1, 90})) {
        system("rm -rf /data/local/tmp/泪心glory配置/");
                    }		
					  
        }break;
        
        case 2:
        {
    
 if(ImGui::SliderInt("野怪左右", &monsterX,-300,300,"%.0f",2)){char urlls[2560];        sprintf(urlls, "%d", SmallMapX);        写出文件("/data/local/tmp/泪心glory配置/小地图野怪左右",urlls);}
        if(ImGui::SliderInt("野怪上下", &monsterY,-300,300,"%.0f",2)){char urlls[2560];        sprintf(urlls, "%d", SmallMapY);                写出文件("/data/local/tmp/泪心glory配置/小地图野怪上下",urlls);}

       
     if(ImGui::SliderInt("头像大小", &touxiangdaxiao,-50,50,"%.0f",2)){char urlls[2560];
        sprintf(urlls, "%d", touxiangdaxiao);

        写出文件("/data/local/tmp/泪心glory配置/头像大小",urlls);}
      if(ImGui::SliderInt("血量大小", &xiaodituxue,-50,50,"%.0f",2)){char urlls[2560];
        sprintf(urlls, "%d", xiaodituxue);
        写出文件("/data/local/tmp/泪心glory配置/血量大小",urlls);}        
             if(ImGui::SliderInt("顶上技能血", &dingshanghealth,-50,50,"%.0f",2)){char urlls[2560];
        sprintf(urlls, "%d", dingshanghealth);
        写出文件("/data/local/tmp/泪心glory配置/顶上技能血",urlls);}
      if(ImGui::SliderInt("地图缩放", &jiange,-100,100,"%.0f",2)){char urlls[2560];
        sprintf(urlls, "%d", jiange);

        写出文件("/data/local/tmp/泪心glory配置/头像间隔",urlls);}
        
                        if(ImGui::SliderInt("自身视野X", &屏幕x,-2000,3500,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", 屏幕x);		
		写出文件("/data/local/tmp/泪心glory配置/屏幕x",urlls);}
		
	//	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 544); // 将光标位置向右移动300个像素
		if(ImGui::SliderInt("自身视野Y", &屏幕y,-700,700,"%.0f",2)){char urlls[2560];
		sprintf(urlls, "%d", 屏幕y);		
		写出文件("/data/local/tmp/泪心glory配置/屏幕y",urlls);}              
		
    if (ImGui::SliderInt("头像X", &SmallMapX, -300, 300, "%.0f", 2)) {
        char urlls[2560];
        sprintf(urlls, "%d", SmallMapX);
        写出文件("/data/local/tmp/泪心glory配置/小x1", urlls);
    }
    if (ImGui::SliderInt("头像Y", &SmallMapY, -300, 300, "%.0f", 2)) {
        char urlls[2560];
        sprintf(urlls, "%d", SmallMapY);

        写出文件("/data/local/tmp/泪心glory配置/小y1", urlls);
    }
    if (ImGui::SliderInt("实体X", &SmallHPX, -300, 300, "%.0f", 2)) {
        char urlls[2560];
        sprintf(urlls, "%d", SmallHPX);

        写出文件("/data/local/tmp/泪心glory配置/大x1", urlls);
    }
    if (ImGui::SliderInt("实体Y", &SmallHPY, -300, 300, "%.0f", 2)) {
        char urlls[2560];
        sprintf(urlls, "%d", SmallHPY);

        写出文件("/data/local/tmp/泪心glory配置/大y1", urlls);
    }


    if (ImGui::SliderInt("技能左右", &jinenglanzX, -2000, 2000, "%.0f", 2)) {
        char urlls[2560];
        sprintf(urlls, "%d", jinenglanzX);

        写出文件("/data/local/tmp/泪心glory配置/技能栏左右1", urlls);
    }

    if (ImGui::SliderInt("技能上下", &jinenglanzY, -500, 500, "%.0f", 2)) {
        char urlls[2560];
        sprintf(urlls, "%d", jinenglanzY);

        写出文件("/data/local/tmp/泪心glory配置/技能栏上下1", urlls);
    }
    
			}break;
        
        case 3:
        {           
        
		ImGui::TextColored(ImColor(255,105,0), "已支持王者国际服S赛季");				
		ImGui::TextColored(ImVec4(1.0f, 1.0f,1.0f, 1.0f), "内存入口:%p",lil2cpp_basebss);
        ImGui::TextColored(ImVec4(0.6f, 0.0f, 1.0f, 1.0f), "矩阵入口:%p",MatrixAddress);

    				
		 

        	}break;
        	
        	
        	//共享谨慎 暂时不用
       case 4:
        {           
        		 

            
        	}break; 
        	
        	
        	
        }//swtich选择菜单栏目
        ImGui::EndChild();
        }//绘制菜单主要选项
                ImGui::EndChild();
                }//右菜单结束了
    		
    	
                
            }
            ImGui::End();


}

if(huitu==1){
	DrawPlayer(); //调用绘图  直接写在这边的话有点影响观看了

	}



ImGui::Render();

end();
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



//QQ2254013571开发绘制
//QQ2254013571