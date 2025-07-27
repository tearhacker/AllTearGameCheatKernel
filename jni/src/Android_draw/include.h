//#include "内核读写/函数.h"
//QQ2254013571开发绘制
//QQ2254013571
#include <draw.h>
#include "封装绘图.h"
#include "结构体.h"
#include "内核读写/定制读写.hpp"
#include <TouchHelperA.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>
#include <chrono>// 假设您已经有了这些数据结构定义// 
#define PI 3.141592653589793238
float NumIo[50];
bool DrawIo[50];
string SaveDir;
FILE *numSave = nullptr;
float inttouchx = 300;
float inttouchy = 500;  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
int FPS=120;
timer FPS限制;
float FPF显示;  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
float 游戏;
 /*
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
*/
//文件操作
void read_line_without_newline(FILE* stream, char* buffer, size_t size) {
    fgets(buffer, size, stream);
    buffer[strcspn(buffer, "\n")] = '\0';
}

void 写出文件(char *aaa,char *bbb){
	
	system("mkdir -p  /data/local/tmp/泪心glory配置");
	std::ofstream ofs;
	
	
	ofs.open(aaa, std::ios::out);

	ofs << bbb 
		;

	ofs.close();
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
   //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 


//游戏相关功能实现
void  delcache()
{
system("rm -rf /data/data/com.tencent.tmgp.sgame/files/ano_tmp");
system("rm -rf rm -rf /data/user/0/com.tencent.tmgp.sgame/files/ano_tmp");
system("rm -rf filedir storage/emulated/0/Android/data/com.tencent.tmgp.sgame/files/logs");
//system("rm -r /data/data/com.tencent.tmgp.sgame/databases/ ");
system("rm -rf filedir storage/emulated/0/Android/data/com.tencent.tmgp.sgame/cache/");
system("rm -rf /data/data/com.tencent.tmgp.sgame/shared_prefs/");

printf("王者缓存封号已经删除！\n");
}
void startGame()
{
    system("pkill -f com.tencent.mobileqq");
    system("am start -n com.tencent.tmgp.sgame/com.tencent.tmgp.sgame.SGameActivity");

}


string exec(string command) {
char buffer[128];
string result = "";
// Open pipe to file
FILE* pipe = popen(command.c_str(), "r");
if (!pipe) {
return "popen failed!";
}
// read till end of process:
while (!feof(pipe)) {
// use buffer to read and add to result
if (fgets(buffer, 128, pipe) != nullptr){
result += buffer;
}
}
pclose(pipe);
return result;
}



static float tm = 127/255.f;
static ImVec4 arr[] = {{144/255.f,238/255.f,144/255.f,tm},{135/255.f,206/255.f,255/255.f,tm},{255/255.f,0/255.f,0/255.f,tm},{0/255.f,255/255.f,0/255.f,tm},{0 /255.f,255/255.f, 127/255.f,tm}
                      ,{255/255.f,182/255.f,193/255.f,tm},{218/255.f,112/255.f,214/255.f,tm},{248/255.f,248/255.f,255/255.f,tm},{0/255.f,255/255.f,255/255.f,tm},{255/255.f,165/255.f,0/255.f,tm}
                      ,{153/255.f,204/255.f,255/255.f,tm},{204/255.f,255/255.f,153/255.f,tm},{255/255.f,255/255.f,153/255.f,tm},{255/255.f,153/255.f,153/255.f,tm},{153/255.f,153/255.f,204/255.f,tm}
                      ,{204/255.f,204/255.f,204/255.f,tm},{102/255.f,204/255.f,153/255.f,tm},{255/255.f,102/255.f,0/255.f,tm},{102/255.f,204/255.f,204/255.f,tm},{153/255.f,204/255.f,255/255.f,tm}
};
static int length = sizeof(arr)/16;




//主页菜单
void DrawLogomenu(ImVec2 center, float size)
{
	ImGui::SetCursorPos({0, 180});
	ImDrawList *draw_list = ImGui::GetWindowDrawList();
	draw_list->AddImage(FloatBall,{center.x - size / 2, center.y - size / 2},{center.x + size / 2, center.y + size / 2});
	
}
void DrawLogoyulong(ImVec2 center, float size)
{
	ImGui::SetCursorPos({0, 180});
	ImDrawList *draw_list = ImGui::GetWindowDrawList();
	draw_list->AddImage(FloatBallyulong,{center.x - size / 2, center.y - size / 2},{center.x + size / 2, center.y + size / 2});
	
}


