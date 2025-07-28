//#include "../内核读取/内核读写.hpp"
#include "../内核读取/内核读写.h"
#include <imgui.h>
#include <stb_image.h>


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
uintptr_t libbase;
float NumIo[50];
bool DrawIo[50];
bool 音量开关 = false;
static bool MemuSwitch = true, BallSwitch = false;
ImGuiStyle *Style = nullptr;
ImGuiWindow *Window = nullptr;
static bool IsLoGin = true, IsDown = false, IsWin = true;

int Color[3];
ImColor White, mid, dark;
int MenuTab = 1;
ImVec2 ImagePos = {0, 0};
ImTextureID testtexure;

bool ButtonTextColored(const ImVec4& col, const char* fmt, ...){ va_list args; va_start(args, fmt); ImGui::TextColoredV(col, fmt, args); va_end(args); return ImGui::IsItemClicked();}//缩小

ImTextureID createTexture(char* ImagePath)
{
    int w,h,n;
    stbi_uc * data = stbi_load(ImagePath, &w, &h, &n, 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if(n == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w , h , 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w , h , 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    ImTextureID image_id = texture;
    return image_id;
}

/*
    bool ImGui::SS_SwitchButton(const char* str_id, bool* v)
{
    bool ret = false;
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = 60;
    float width = 600;
    float radius = height * 0.5f;

    ImGui::InvisibleButton(str_id, ImVec2(width, height));
    if (ImGui::IsItemClicked()) *v = !*v,ret = true;
    ImGuiContext& gg = *GImGui;
    float ANIM_SPEED = 0.085f;
    if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
        float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);
    if (ImGui::IsItemHovered())
        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f)), height * 0.5f);
    else
        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f)), height * 0.50f);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), p.y + radius-0.f), radius -3.f, IM_COL32(255, 255, 255, 255));
    //文字
    RenderText(ImVec2(p.x + width*1.25f,  p.y + radius-15), str_id);
      

    return ret;
}*/

bool ImGui::SS_SwitchButton(const char* str_id, bool* v)
{
    bool ret = false;
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = 70;
    float width = 545;
    float radius = height * 0.5f;

    ImGui::InvisibleButton(str_id, ImVec2(width, height));
    if (ImGui::IsItemClicked()) {
        *v = !*v;
        ret = true;
    }
    ImGuiContext& gg = *GImGui;
    float ANIM_SPEED = 0.085f;
    if (gg.LastActiveId == gg.CurrentWindow->GetID(str_id)) {
        float t_anim = ImSaturate(gg.LastActiveIdTimer / ANIM_SPEED);
    }
    if (ImGui::IsItemHovered()) {
        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_ButtonActive] : ImVec4(0.78f, 0.78f, 0.78f, 1.0f)), height * 0.5f);
    } else {
        draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), ImGui::GetColorU32(*v ? colors[ImGuiCol_Button] : ImVec4(0.85f, 0.85f, 0.85f, 1.0f)), height * 0.50f);
    }
    draw_list->AddCircleFilled(ImVec2(p.x + radius + (*v ? 1 : 0) * (width - radius * 2.0f), p.y + radius), radius - 3.f, IM_COL32(255, 255, 255, 255));

    // 文字
    ImVec2 text_size = ImGui::CalcTextSize(str_id); // 计算文本的尺寸
    ImVec2 text_pos = ImVec2(p.x + (width - text_size.x) / 2.0f, p.y + (height - text_size.y) / 2.0f); // 计算文本的位置
    ImGui::SetCursorScreenPos(text_pos); // 设置ImGui的光标位置到文本位置
    ImGui::Text("%s", str_id); // 渲染文本

    return ret;
}


void DrawTexture(int x, int y, int w, int h, ImTextureID Image)
{
    ImGui::GetBackgroundDrawList()->AddImage(Image, ImVec2(x, y), ImVec2(x + w, y + h));
}

void 绘制加粗文本(float size, float x, float y, ImColor color, ImColor color1, const char* str)
{
    ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x-0.1, y-0.1), color1, str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x+0.1, y+0.1), color1, str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x, y), color, str);
}
void 绘制字体描边(float size,int x, int y, ImVec4 color, const char* str)
{
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x - 0.1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(color), str);
}
ImTextureID ImAgeHeadFile1(const unsigned char *buf, int len)
{
	int w, h, n;
	stbi_uc *data = stbi_png_load_from_memory(buf, len, &w, &h, &n, 0);
	GLuint texture;
	glGenTextures(1, &texture);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if (n == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);
	ImTextureID image_id = (ImTextureID) (GLuint *) texture;
	return image_id;
}

static int 屏幕方向 = 1;
bool 内透 = false;
static bool 惩戒 = false;
static bool 斩杀 = false;
static bool 惩戒附近 = false;
int yxpx,yxpy,fenblxx=0;
float 触摸位置大小=50.0f,惩戒x=972.0f,惩戒y=1510.0f;
//斩杀 = arr[18];
long int libbase3;
long int libbase2;
static bool 血量 = false;
static bool 地图 = false;
static bool 方框 = false;
static bool 自瞄 = false;
static bool 射线 = false;
static bool 距离 = false;
static bool 野怪 = false;
static bool 兵线 = false;
static bool 方框技能 = false;
static bool 顶上技能 = false;
static bool 上帝 = false;
static bool 视野方框 = false;
static bool 辅助方框 = false;
static bool 自身判断 = false;

static bool 最新 = false;
static bool 旧版 = false;

//int yxpx,yxpy,fenblxx=1;

 struct 总颜色
{
	ImColor 血量颜色 = ImColor(255,0,0,255);//血量颜色
ImColor 射线颜色 = ImColor(0,0,0,255);
ImColor 方框颜色 = ImColor(255,255,255,255);
};




总颜色 颜色配置;


void 绘制触摸范围(float x,float y,float r){
ImGui::GetForegroundDrawList()->AddCircleArc({x, y},r, ImVec2(0, 360), 颜色配置.血量颜色,  0, 2.0f);//白底背景
}

//读取Set
int ReadDrawSet(总颜色 *myDrawSet,const char* Filename)
{
    FILE* pFile;

    pFile = fopen(Filename, "rb");
    if (pFile == NULL) {
        printf("文件打开失败");
        return 0;
    }

    while (fread(myDrawSet, sizeof(总颜色), 1, pFile) == 1)
        //printf("%s : %f", book.title, book.value);
        fclose(pFile);
    return 1;
}

//保存Set
int SaveDrawSet(总颜色 *myDrawSet,const char *FileName)
{
    FILE* pFile;
    pFile = fopen(FileName, "wb");
    if (pFile == NULL) {
        printf("创建文件失败");
        return 0;
    }

    fwrite(myDrawSet, sizeof(总颜色), 1, pFile);

    fclose(pFile);
    return 1;
}
int touxiangdaxiao = 0;//头像大小
int xiaodituxue = 0;//小地图血量大小
int jiange = 0;//小地图间隔




int SmallMapX = 0;
int SmallMapY = 0; //小地图头像位置

int BuffMapX = 0; //buff
int BuffMapY = 0;

int SmallSoldiX = 0; //兵线
int SmallSoldiY = 0;

int SmallHPX = 0;
int SmallHPY = 0; //小地图血条位置


int jinenglanzX=0;//技能栏左右
int jinenglanzY=0;//技能栏上下


float shangdi=1.2f;//上帝高度
int 屏幕x=1120;
int 屏幕y=440;


long int 兵线数组地址;

char DrawPlayerCount[100];
Vector3 D;
Vector3 Z;
float AimX,AimY;
long int zmx,zmy,zmx1,zmy1;
int Health;
int PlayerId;
long int CameraAddress;

int SmallMapTeam;

struct stu
{
	int id;
	int hp;
};
bool operator<(const stu & a, const stu & b)
{
	return a.hp < b.hp;
}
int prex, prey;

int getdistance(int xx1, int yy1, int xx2, int yy2)
{
	return sqrt(pow(yy2 - yy1, 2) + pow(xx2 - xx1, 2));
}

int LoadPosition(int a[3], int b[3], int t)
{
	//传时间跟xyz
	//距离
	int distance = getdistance(a[1], a[2], b[1], b[2]);
	//使用时间
	int usetime = (b[3] - a[3]) * 1.0;
	//子弹速度
	int speed = distance / usetime * t + distance;
	int AimTime = speed / distance;
	//到人身上的距离
	
	//计算预判的坐标差
	int xadd = (b[1] - a[1]) * AimTime;
	int yadd = (b[2] - a[2]) * AimTime;
	if(b[1]-a[1] != 0)
	prex = a[1] + xadd;
	prey = a[2] + yadd;
	return 0;
}

int AimPosition(int SelfX, int SelfY)
{
	//这边开始算自瞄的了
	float AimLocation = sqrt(SelfX * SelfX + SelfY * SelfY);
	//这边没看懂反正应该是最终瞄准位置
	AimX = SelfX / AimLocation;
	AimY = SelfY / AimLocation; 
	return 0;
}

stu player[10];
int PlayerPosition[10][3];//自瞄的玩家坐标 一把游戏10人 坐标xyz
int hist[10][3];
int me = 0;
int maxdistan = 0;
int AimCharacter = 0; //瞄准人物
int Anticipation = 0;//预判距离


double Wwr = 1080/10.2f*1.574074075;
struct TextureInfo
{
    ImTextureID textureId;
    int x;
    int y;
    int w;
    int h;
};

struct TextureInfoa {
    uint *textureId;
    int x;
    int y;
    int w;
    int h;
};

static struct 颜色
{
	ImColor Red={255/255.f,0/255.f,0/255.f,255/255.f};
	ImColor Red_={255/255.f,0/255.f,0/255.f,50/255.f};
	ImColor Green={0/255.f,255/255.f,0/255.f,255/255.f};
	ImColor Green_={0/255.f,255/255.f,0/255.f,50/255.f};
	ImColor 白色={255/255.f,255/255.f,255/255.f,255.f/255.f};
    ImColor White_={255/255.f,255/255.f,255/255.f,180.f/255.f};
    ImColor Black={0/255.f,0/255.f,0/255.f,255.f/255.f};
	ImColor Yellow={1.0f, 1.0f, 0.0f,1.0f};
}颜色;


TextureInfo createTexture1(char* ImagePath)
{
	TextureInfo textureInfo;
	int w,h,n;
	stbi_uc * data = stbi_load(ImagePath,&w,&h,&n,0);
	GLuint texture;
	glGenTextures(1, &texture);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if(n==3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w , h , 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	} else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w , h , 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);
	textureInfo.textureId=texture;
	textureInfo.w=w;
	textureInfo.h=h;
	return textureInfo;
}

TextureInfoa createTexturePNGFromMem(const unsigned char *buf,int len) {
	TextureInfoa textureInfo;
    int w, h, n;
    stbi_uc *data = stbi_png_load_from_memory(buf, len, &w, &h, &n, 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (n == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data);
    textureInfo.textureId = (GLuint *) texture;
    textureInfo.w = w;
    textureInfo.h = h;
    return textureInfo;
}


#include "../头像照片/picture_obj0_png.h"
#include "../头像照片/picture_obj105_png.h"
#include "../头像照片/picture_obj106_png.h"
#include "../头像照片/picture_obj107_png.h"
#include "../头像照片/picture_obj108_png.h"
#include "../头像照片/picture_obj109_png.h"
#include "../头像照片/picture_obj110_png.h"
#include "../头像照片/picture_obj111_png.h"
#include "../头像照片/picture_obj112_png.h"
#include "../头像照片/picture_obj113_png.h"
#include "../头像照片/picture_obj114_png.h"
#include "../头像照片/picture_obj115_png.h"
#include "../头像照片/picture_obj116_png.h"
#include "../头像照片/picture_obj117_png.h"
#include "../头像照片/picture_obj118_png.h"
#include "../头像照片/picture_obj119_png.h"
#include "../头像照片/picture_obj120_png.h"
#include "../头像照片/picture_obj121_png.h"
#include "../头像照片/picture_obj123_png.h"
#include "../头像照片/picture_obj124_png.h"
#include "../头像照片/picture_obj125_png.h"
#include "../头像照片/picture_obj126_png.h"
#include "../头像照片/picture_obj127_png.h"
#include "../头像照片/picture_obj128_png.h"
#include "../头像照片/picture_obj129_png.h"
#include "../头像照片/picture_obj130_png.h"
#include "../头像照片/picture_obj131_png.h"
#include "../头像照片/picture_obj132_png.h"
#include "../头像照片/picture_obj133_png.h"
#include "../头像照片/picture_obj134_png.h"
#include "../头像照片/picture_obj135_png.h"
#include "../头像照片/picture_obj136_png.h"
#include "../头像照片/picture_obj137_png.h"
#include "../头像照片/picture_obj139_png.h"
#include "../头像照片/picture_obj140_png.h"
#include "../头像照片/picture_obj141_png.h"
#include "../头像照片/picture_obj142_png.h"
#include "../头像照片/picture_obj144_png.h"
#include "../头像照片/picture_obj146_png.h"
#include "../头像照片/picture_obj148_png.h"
#include "../头像照片/picture_obj149_png.h"
#include "../头像照片/picture_obj150_png.h"
#include "../头像照片/picture_obj152_png.h"
#include "../头像照片/picture_obj153_png.h"
#include "../头像照片/picture_obj154_png.h"
#include "../头像照片/picture_obj155_png.h"
#include "../头像照片/picture_obj156_png.h"
#include "../头像照片/picture_obj157_png.h"
#include "../头像照片/picture_obj162_png.h"
#include "../头像照片/picture_obj163_png.h"
#include "../头像照片/picture_obj166_png.h"
#include "../头像照片/picture_obj167_png.h"
#include "../头像照片/picture_obj168_png.h"
#include "../头像照片/picture_obj169_png.h"
#include "../头像照片/picture_obj170_png.h"
#include "../头像照片/picture_obj171_png.h"
#include "../头像照片/picture_obj173_png.h"
#include "../头像照片/picture_obj174_png.h"
#include "../头像照片/picture_obj175_png.h"
#include "../头像照片/picture_obj176_png.h"
#include "../头像照片/picture_obj177_png.h"
#include "../头像照片/picture_obj178_png.h"
#include "../头像照片/picture_obj179_png.h"
#include "../头像照片/picture_obj180_png.h"
#include "../头像照片/picture_obj182_png.h"
#include "../头像照片/picture_obj183_png.h"
#include "../头像照片/picture_obj184_png.h"
#include "../头像照片/picture_obj186_png.h"
#include "../头像照片/picture_obj187_png.h"
#include "../头像照片/picture_obj189_png.h"
#include "../头像照片/picture_obj190_png.h"
#include "../头像照片/picture_obj191_png.h"
#include "../头像照片/picture_obj192_png.h"
#include "../头像照片/picture_obj193_png.h"
#include "../头像照片/picture_obj194_png.h"
#include "../头像照片/picture_obj195_png.h"
#include "../头像照片/picture_obj196_png.h"
#include "../头像照片/picture_obj197_png.h"
#include "../头像照片/picture_obj198_png.h"
#include "../头像照片/picture_obj199_png.h"
#include "../头像照片/picture_obj312_png.h"
#include "../头像照片/picture_obj501_png.h"
#include "../头像照片/picture_obj502_png.h"
#include "../头像照片/picture_obj503_png.h"
#include "../头像照片/picture_obj504_png.h"
#include "../头像照片/picture_obj505_png.h"
#include "../头像照片/picture_obj506_png.h"
#include "../头像照片/picture_obj507_png.h"
#include "../头像照片/picture_obj508_png.h"
#include "../头像照片/picture_obj509_png.h"
#include "../头像照片/picture_obj510_png.h"
#include "../头像照片/picture_obj511_png.h"
#include "../头像照片/picture_obj513_png.h"
#include "../头像照片/picture_obj515_png.h"
#include "../头像照片/picture_obj517_png.h"
#include "../头像照片/picture_obj519_png.h"
#include "../头像照片/picture_obj518_png.h"
#include "../头像照片/picture_obj521_png.h"
#include "../头像照片/picture_obj522_png.h"
#include "../头像照片/picture_obj523_png.h"
#include "../头像照片/picture_obj524_png.h"
#include "../头像照片/picture_obj525_png.h"
#include "../头像照片/picture_obj527_png.h"
#include "../头像照片/picture_obj528_png.h"
#include "../头像照片/picture_obj529_png.h"
#include "../头像照片/picture_obj531_png.h"
#include "../头像照片/picture_obj533_png.h"
#include "../头像照片/picture_obj534_png.h"
#include "../头像照片/picture_obj536_png.h"
#include "../头像照片/picture_obj537_png.h"
#include "../头像照片/picture_obj538_png.h"
#include "../头像照片/picture_obj540_png.h"
#include "../头像照片/picture_obj542_png.h"
#include "../头像照片/picture_obj544_png.h"
#include "../头像照片/picture_obj545_png.h"
#include "../头像照片/picture_obj548_png.h"
#include "../头像照片/picture_obj564_png.h"
#include "../头像照片/picture_obj514_png.h"
#include "../头像照片/picture_obj563_png.h"
#include "../头像照片/picture_obj581_png.h"
#include "../头像照片/picture_obj582_png.h"
#include "../头像照片/picture_obj159_png.h"

void Loadpicture_obj(TextureInfoa *HeadPortrait)
{
    HeadPortrait[0] = createTexturePNGFromMem(picture_obj0_PNG_H, sizeof(picture_obj0_PNG_H));
    HeadPortrait[105] = createTexturePNGFromMem(picture_obj105_PNG_H, sizeof(picture_obj105_PNG_H));
HeadPortrait[106] = createTexturePNGFromMem(picture_obj106_PNG_H, sizeof(picture_obj106_PNG_H));
HeadPortrait[107] = createTexturePNGFromMem(picture_obj107_PNG_H, sizeof(picture_obj107_PNG_H));
HeadPortrait[108] = createTexturePNGFromMem(picture_obj108_PNG_H, sizeof(picture_obj108_PNG_H));
HeadPortrait[109] = createTexturePNGFromMem(picture_obj109_PNG_H, sizeof(picture_obj109_PNG_H));
HeadPortrait[110] = createTexturePNGFromMem(picture_obj110_PNG_H, sizeof(picture_obj110_PNG_H));
HeadPortrait[111] = createTexturePNGFromMem(picture_obj111_PNG_H, sizeof(picture_obj111_PNG_H));
HeadPortrait[112] = createTexturePNGFromMem(picture_obj112_PNG_H, sizeof(picture_obj112_PNG_H));
HeadPortrait[113] = createTexturePNGFromMem(picture_obj113_PNG_H, sizeof(picture_obj113_PNG_H));
HeadPortrait[114] = createTexturePNGFromMem(picture_obj114_PNG_H, sizeof(picture_obj114_PNG_H));
HeadPortrait[115] = createTexturePNGFromMem(picture_obj115_PNG_H, sizeof(picture_obj115_PNG_H));
HeadPortrait[116] = createTexturePNGFromMem(picture_obj116_PNG_H, sizeof(picture_obj116_PNG_H));
HeadPortrait[117] = createTexturePNGFromMem(picture_obj117_PNG_H, sizeof(picture_obj117_PNG_H));
HeadPortrait[118] = createTexturePNGFromMem(picture_obj118_PNG_H, sizeof(picture_obj118_PNG_H));
HeadPortrait[119] = createTexturePNGFromMem(picture_obj119_PNG_H, sizeof(picture_obj119_PNG_H));
HeadPortrait[120] = createTexturePNGFromMem(picture_obj120_PNG_H, sizeof(picture_obj120_PNG_H));
HeadPortrait[121] = createTexturePNGFromMem(picture_obj121_PNG_H, sizeof(picture_obj121_PNG_H));
HeadPortrait[123] = createTexturePNGFromMem(picture_obj123_PNG_H, sizeof(picture_obj123_PNG_H));
HeadPortrait[124] = createTexturePNGFromMem(picture_obj124_PNG_H, sizeof(picture_obj124_PNG_H));
HeadPortrait[125] = createTexturePNGFromMem(picture_obj125_PNG_H, sizeof(picture_obj125_PNG_H));
HeadPortrait[126] = createTexturePNGFromMem(picture_obj126_PNG_H, sizeof(picture_obj126_PNG_H));
HeadPortrait[127] = createTexturePNGFromMem(picture_obj127_PNG_H, sizeof(picture_obj127_PNG_H));
HeadPortrait[128] = createTexturePNGFromMem(picture_obj128_PNG_H, sizeof(picture_obj128_PNG_H));
HeadPortrait[129] = createTexturePNGFromMem(picture_obj129_PNG_H, sizeof(picture_obj129_PNG_H));
HeadPortrait[130] = createTexturePNGFromMem(picture_obj130_PNG_H, sizeof(picture_obj130_PNG_H));
HeadPortrait[131] = createTexturePNGFromMem(picture_obj131_PNG_H, sizeof(picture_obj131_PNG_H));
HeadPortrait[132] = createTexturePNGFromMem(picture_obj132_PNG_H, sizeof(picture_obj132_PNG_H));
HeadPortrait[133] = createTexturePNGFromMem(picture_obj133_PNG_H, sizeof(picture_obj133_PNG_H));
HeadPortrait[134] = createTexturePNGFromMem(picture_obj134_PNG_H, sizeof(picture_obj134_PNG_H));
HeadPortrait[135] = createTexturePNGFromMem(picture_obj135_PNG_H, sizeof(picture_obj135_PNG_H));
HeadPortrait[136] = createTexturePNGFromMem(picture_obj136_PNG_H, sizeof(picture_obj136_PNG_H));
HeadPortrait[137] = createTexturePNGFromMem(picture_obj137_PNG_H, sizeof(picture_obj137_PNG_H));
HeadPortrait[139] = createTexturePNGFromMem(picture_obj139_PNG_H, sizeof(picture_obj139_PNG_H));
HeadPortrait[140] = createTexturePNGFromMem(picture_obj140_PNG_H, sizeof(picture_obj140_PNG_H));
HeadPortrait[141] = createTexturePNGFromMem(picture_obj141_PNG_H, sizeof(picture_obj141_PNG_H));
HeadPortrait[142] = createTexturePNGFromMem(picture_obj142_PNG_H, sizeof(picture_obj142_PNG_H));
HeadPortrait[144] = createTexturePNGFromMem(picture_obj144_PNG_H, sizeof(picture_obj144_PNG_H));
HeadPortrait[146] = createTexturePNGFromMem(picture_obj146_PNG_H, sizeof(picture_obj146_PNG_H));
HeadPortrait[148] = createTexturePNGFromMem(picture_obj148_PNG_H, sizeof(picture_obj148_PNG_H));
HeadPortrait[149] = createTexturePNGFromMem(picture_obj149_PNG_H, sizeof(picture_obj149_PNG_H));
HeadPortrait[150] = createTexturePNGFromMem(picture_obj150_PNG_H, sizeof(picture_obj150_PNG_H));
HeadPortrait[152] = createTexturePNGFromMem(picture_obj152_PNG_H, sizeof(picture_obj152_PNG_H));
HeadPortrait[153] = createTexturePNGFromMem(picture_obj153_PNG_H, sizeof(picture_obj153_PNG_H));
HeadPortrait[154] = createTexturePNGFromMem(picture_obj154_PNG_H, sizeof(picture_obj154_PNG_H));
HeadPortrait[155] = createTexturePNGFromMem(picture_obj155_PNG_H, sizeof(picture_obj155_PNG_H));
HeadPortrait[156] = createTexturePNGFromMem(picture_obj156_PNG_H, sizeof(picture_obj156_PNG_H));
HeadPortrait[157] = createTexturePNGFromMem(picture_obj157_PNG_H, sizeof(picture_obj157_PNG_H));
HeadPortrait[162] = createTexturePNGFromMem(picture_obj162_PNG_H, sizeof(picture_obj162_PNG_H));
HeadPortrait[163] = createTexturePNGFromMem(picture_obj163_PNG_H, sizeof(picture_obj163_PNG_H));
HeadPortrait[166] = createTexturePNGFromMem(picture_obj166_PNG_H, sizeof(picture_obj166_PNG_H));
HeadPortrait[167] = createTexturePNGFromMem(picture_obj167_PNG_H, sizeof(picture_obj167_PNG_H));
HeadPortrait[168] = createTexturePNGFromMem(picture_obj168_PNG_H, sizeof(picture_obj168_PNG_H));
HeadPortrait[169] = createTexturePNGFromMem(picture_obj169_PNG_H, sizeof(picture_obj169_PNG_H));
HeadPortrait[170] = createTexturePNGFromMem(picture_obj170_PNG_H, sizeof(picture_obj170_PNG_H));
HeadPortrait[171] = createTexturePNGFromMem(picture_obj171_PNG_H, sizeof(picture_obj171_PNG_H));
HeadPortrait[173] = createTexturePNGFromMem(picture_obj173_PNG_H, sizeof(picture_obj173_PNG_H));
HeadPortrait[174] = createTexturePNGFromMem(picture_obj174_PNG_H, sizeof(picture_obj174_PNG_H));
HeadPortrait[175] = createTexturePNGFromMem(picture_obj175_PNG_H, sizeof(picture_obj175_PNG_H));
HeadPortrait[176] = createTexturePNGFromMem(picture_obj176_PNG_H, sizeof(picture_obj176_PNG_H));
HeadPortrait[177] = createTexturePNGFromMem(picture_obj177_PNG_H, sizeof(picture_obj177_PNG_H));
HeadPortrait[178] = createTexturePNGFromMem(picture_obj178_PNG_H, sizeof(picture_obj178_PNG_H));
HeadPortrait[179] = createTexturePNGFromMem(picture_obj179_PNG_H, sizeof(picture_obj179_PNG_H));
HeadPortrait[180] = createTexturePNGFromMem(picture_obj180_PNG_H, sizeof(picture_obj180_PNG_H));
HeadPortrait[182] = createTexturePNGFromMem(picture_obj182_PNG_H, sizeof(picture_obj182_PNG_H));
HeadPortrait[183] = createTexturePNGFromMem(picture_obj183_PNG_H, sizeof(picture_obj183_PNG_H));
HeadPortrait[184] = createTexturePNGFromMem(picture_obj184_PNG_H, sizeof(picture_obj184_PNG_H));
HeadPortrait[186] = createTexturePNGFromMem(picture_obj186_PNG_H, sizeof(picture_obj186_PNG_H));
HeadPortrait[187] = createTexturePNGFromMem(picture_obj187_PNG_H, sizeof(picture_obj187_PNG_H));
HeadPortrait[189] = createTexturePNGFromMem(picture_obj189_PNG_H, sizeof(picture_obj189_PNG_H));
HeadPortrait[190] = createTexturePNGFromMem(picture_obj190_PNG_H, sizeof(picture_obj190_PNG_H));
HeadPortrait[191] = createTexturePNGFromMem(picture_obj191_PNG_H, sizeof(picture_obj191_PNG_H));
HeadPortrait[192] = createTexturePNGFromMem(picture_obj192_PNG_H, sizeof(picture_obj192_PNG_H));
HeadPortrait[193] = createTexturePNGFromMem(picture_obj193_PNG_H, sizeof(picture_obj193_PNG_H));
HeadPortrait[194] = createTexturePNGFromMem(picture_obj194_PNG_H, sizeof(picture_obj194_PNG_H));
HeadPortrait[195] = createTexturePNGFromMem(picture_obj195_PNG_H, sizeof(picture_obj195_PNG_H));
HeadPortrait[196] = createTexturePNGFromMem(picture_obj196_PNG_H, sizeof(picture_obj196_PNG_H));
HeadPortrait[197] = createTexturePNGFromMem(picture_obj197_PNG_H, sizeof(picture_obj197_PNG_H));
HeadPortrait[198] = createTexturePNGFromMem(picture_obj198_PNG_H, sizeof(picture_obj198_PNG_H));
HeadPortrait[199] = createTexturePNGFromMem(picture_obj199_PNG_H, sizeof(picture_obj199_PNG_H));
HeadPortrait[312] = createTexturePNGFromMem(picture_obj312_PNG_H, sizeof(picture_obj312_PNG_H));
HeadPortrait[501] = createTexturePNGFromMem(picture_obj501_PNG_H, sizeof(picture_obj501_PNG_H));
HeadPortrait[502] = createTexturePNGFromMem(picture_obj502_PNG_H, sizeof(picture_obj502_PNG_H));
HeadPortrait[503] = createTexturePNGFromMem(picture_obj503_PNG_H, sizeof(picture_obj503_PNG_H));
HeadPortrait[504] = createTexturePNGFromMem(picture_obj504_PNG_H, sizeof(picture_obj504_PNG_H));
HeadPortrait[505] = createTexturePNGFromMem(picture_obj505_PNG_H, sizeof(picture_obj505_PNG_H));
HeadPortrait[506] = createTexturePNGFromMem(picture_obj506_PNG_H, sizeof(picture_obj506_PNG_H));
HeadPortrait[507] = createTexturePNGFromMem(picture_obj507_PNG_H, sizeof(picture_obj507_PNG_H));
HeadPortrait[508] = createTexturePNGFromMem(picture_obj508_PNG_H, sizeof(picture_obj508_PNG_H));
HeadPortrait[509] = createTexturePNGFromMem(picture_obj509_PNG_H, sizeof(picture_obj509_PNG_H));
HeadPortrait[510] = createTexturePNGFromMem(picture_obj510_PNG_H, sizeof(picture_obj510_PNG_H));
HeadPortrait[511] = createTexturePNGFromMem(picture_obj511_PNG_H, sizeof(picture_obj511_PNG_H));
HeadPortrait[513] = createTexturePNGFromMem(picture_obj513_PNG_H, sizeof(picture_obj513_PNG_H));
HeadPortrait[515] = createTexturePNGFromMem(picture_obj515_PNG_H, sizeof(picture_obj515_PNG_H));
HeadPortrait[517] = createTexturePNGFromMem(picture_obj517_PNG_H, sizeof(picture_obj517_PNG_H));
HeadPortrait[519] = createTexturePNGFromMem(picture_obj519_PNG_H, sizeof(picture_obj519_PNG_H));
HeadPortrait[518] = createTexturePNGFromMem(picture_obj518_PNG_H, sizeof(picture_obj518_PNG_H));
HeadPortrait[521] = createTexturePNGFromMem(picture_obj521_PNG_H, sizeof(picture_obj521_PNG_H));
HeadPortrait[522] = createTexturePNGFromMem(picture_obj522_PNG_H, sizeof(picture_obj522_PNG_H));
HeadPortrait[523] = createTexturePNGFromMem(picture_obj523_PNG_H, sizeof(picture_obj523_PNG_H));
HeadPortrait[524] = createTexturePNGFromMem(picture_obj524_PNG_H, sizeof(picture_obj524_PNG_H));
HeadPortrait[525] = createTexturePNGFromMem(picture_obj525_PNG_H, sizeof(picture_obj525_PNG_H));
HeadPortrait[527] = createTexturePNGFromMem(picture_obj527_PNG_H, sizeof(picture_obj527_PNG_H));
HeadPortrait[528] = createTexturePNGFromMem(picture_obj528_PNG_H, sizeof(picture_obj528_PNG_H));
HeadPortrait[529] = createTexturePNGFromMem(picture_obj529_PNG_H, sizeof(picture_obj529_PNG_H));
HeadPortrait[531] = createTexturePNGFromMem(picture_obj531_PNG_H, sizeof(picture_obj531_PNG_H));
HeadPortrait[533] = createTexturePNGFromMem(picture_obj533_PNG_H, sizeof(picture_obj533_PNG_H));
HeadPortrait[534] = createTexturePNGFromMem(picture_obj534_PNG_H, sizeof(picture_obj534_PNG_H));
HeadPortrait[536] = createTexturePNGFromMem(picture_obj536_PNG_H, sizeof(picture_obj536_PNG_H));
HeadPortrait[537] = createTexturePNGFromMem(picture_obj537_PNG_H, sizeof(picture_obj537_PNG_H));
HeadPortrait[538] = createTexturePNGFromMem(picture_obj538_PNG_H, sizeof(picture_obj538_PNG_H));
HeadPortrait[540] = createTexturePNGFromMem(picture_obj540_PNG_H, sizeof(picture_obj540_PNG_H));
HeadPortrait[542] = createTexturePNGFromMem(picture_obj542_PNG_H, sizeof(picture_obj542_PNG_H));
HeadPortrait[544] = createTexturePNGFromMem(picture_obj544_PNG_H, sizeof(picture_obj544_PNG_H));
HeadPortrait[545] = createTexturePNGFromMem(picture_obj545_PNG_H, sizeof(picture_obj545_PNG_H));
HeadPortrait[548] = createTexturePNGFromMem(picture_obj548_PNG_H, sizeof(picture_obj548_PNG_H));
HeadPortrait[564] = createTexturePNGFromMem(picture_obj564_PNG_H, sizeof(picture_obj564_PNG_H));
HeadPortrait[514] = createTexturePNGFromMem(picture_obj514_PNG_H, sizeof(picture_obj514_PNG_H));
HeadPortrait[563] = createTexturePNGFromMem(picture_obj563_PNG_H, sizeof(picture_obj563_PNG_H));
HeadPortrait[581] = createTexturePNGFromMem(picture_obj581_PNG_H, sizeof(picture_obj581_PNG_H));
HeadPortrait[582] = createTexturePNGFromMem(picture_obj582_PNG_H, sizeof(picture_obj582_PNG_H));
HeadPortrait[159] = createTexturePNGFromMem(picture_obj159_PNG_H, sizeof(picture_obj159_PNG_H));
}


TextureInfoa djjddjnd [600]={};
        struct 全部头像1
{
	TextureInfoa 头像[650];
	
};
全部头像1 贴图1;

void 获取头像2(){
	
	Loadpicture_obj(贴图1.头像);
	
}






#include "../头像照片/picture_obj80102_png.h"
#include "../头像照片/picture_obj80103_png.h"
#include "../头像照片/picture_obj80104_png.h"
#include "../头像照片/picture_obj80105_png.h"
#include "../头像照片/picture_obj80107_png.h"
#include "../头像照片/picture_obj80108_png.h"
#include "../头像照片/picture_obj80109_png.h"
#include "../头像照片/picture_obj80110_png.h"
#include "../头像照片/picture_obj80115_png.h"
#include "../头像照片/picture_obj80116_png.h"
#include "../头像照片/picture_obj80121_png.h"
#include "../头像照片/picture_obj801162_png.h"
#include "../头像照片/picture_obj999_png.h"


void Loadpicture_obj2(TextureInfoa *HeadPortrait)
{
    HeadPortrait[102] = createTexturePNGFromMem(picture_obj80102_PNG_H, sizeof(picture_obj80102_PNG_H));
    HeadPortrait[103] = createTexturePNGFromMem(picture_obj80103_PNG_H, sizeof(picture_obj80103_PNG_H));
	HeadPortrait[104] = createTexturePNGFromMem(picture_obj80104_PNG_H, sizeof(picture_obj80104_PNG_H));
    HeadPortrait[105] = createTexturePNGFromMem(picture_obj80105_PNG_H, sizeof(picture_obj80105_PNG_H));
	
	HeadPortrait[107] = createTexturePNGFromMem(picture_obj80107_PNG_H, sizeof(picture_obj80107_PNG_H));
    HeadPortrait[108] = createTexturePNGFromMem(picture_obj80108_PNG_H, sizeof(picture_obj80108_PNG_H));
	HeadPortrait[109] = createTexturePNGFromMem(picture_obj80109_PNG_H, sizeof(picture_obj80109_PNG_H));
    HeadPortrait[110] = createTexturePNGFromMem(picture_obj80110_PNG_H, sizeof(picture_obj80110_PNG_H));
	
	HeadPortrait[115] = createTexturePNGFromMem(picture_obj80115_PNG_H, sizeof(picture_obj80115_PNG_H));
    HeadPortrait[116] = createTexturePNGFromMem(picture_obj80116_PNG_H, sizeof(picture_obj80116_PNG_H));
	
	HeadPortrait[121] = createTexturePNGFromMem(picture_obj80121_PNG_H, sizeof(picture_obj80121_PNG_H));
    HeadPortrait[1162] = createTexturePNGFromMem(picture_obj801162_PNG_H, sizeof(picture_obj801162_PNG_H));
	
	HeadPortrait[0] = createTexturePNGFromMem(picture_obj999_PNG_H, sizeof(picture_obj999_PNG_H));

	
}


struct 技能图标
{
	TextureInfoa 头像[1500];
	
};
技能图标 技能贴图;

void 获取图标(){
	
	Loadpicture_obj2(技能贴图.头像);
	
}



TextureInfo 获取头像(int 次数)
{
	char 路径[1024];
	sprintf(路径,"/storage/emulated/0/MT2/%d.png",次数);
	return createTexture1(路径);
}

struct 全部头像
{
	TextureInfo 头像[650];
	
};
全部头像 贴图;

TextureInfo 头像贴图(int 值)
{
	return 贴图.头像[值];
}


void 获取头像()
{
	for(int i = 0;i<622;i+=1)
	{
		贴图.头像[i] = 获取头像(i);
	}
}

void 绘制头像(TextureInfo textureInfo,int x, int y)
{
	ImGui::GetBackgroundDrawList()->AddImage(textureInfo.textureId, ImVec2(x-textureInfo.w/2, y -textureInfo.y), ImVec2(x-textureInfo.w/2 + textureInfo.w/2.55, y-textureInfo.y + textureInfo.h/2.55));
}

void 方框头像(TextureInfo textureInfo,int x, int y)
{
	ImGui::GetBackgroundDrawList()->AddImage(textureInfo.textureId, ImVec2(x-textureInfo.w/2, y -textureInfo.y), ImVec2(x-textureInfo.w/2 + textureInfo.w/2.55, y-textureInfo.y + textureInfo.h/2.55));
}

void 绘制技能(TextureInfo textureInfo,int x,int y,int 大招CD,int 技能CD,int 回城判断)
{
	ImGui::GetBackgroundDrawList()->AddImage(textureInfo.textureId,ImVec2(x-textureInfo.w/2,y-textureInfo.y),ImVec2(x-textureInfo.w/2+textureInfo.w/2,y-textureInfo.y+textureInfo.h/2));
	
	char 大招计时[64];
	sprintf(大招计时,"%d",大招CD);
	
	char 技能计时[64];
	sprintf(技能计时,"%d",技能CD);
	
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(740.f,73.f),颜色.白色,"大招:");
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(740.f,116.f),颜色.白色,"技能:");
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(740.f,159.f),颜色.白色,"回城:");
		
	if(大招CD!=0)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(x-40,y-55),颜色.白色,大招计时);
	}
	else
	{
		ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x-35,y-45),13.0f,颜色.Green);
	}
	if(技能CD!=0)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(x-40,y-15),颜色.白色,技能计时);
	}
	else
	{
		ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(x-35,y-5),13.0f,颜色.Green);
	}
	if(回城判断 == 0)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(x-40,y+25),颜色.白色,"否");
	}
	else
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(x-40,y+25),颜色.白色,"是");
	}
}




void 绘制血条(float leftx,float lefty,int hp)
{
	float TXdx = 0.020834f*(py*2);
	float cc = TXdx*1.10f;
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(leftx-cc,lefty+TXdx),ImVec2(leftx-cc+hp*cc/50-0.5f,lefty+TXdx+7),ImColor{0/255.f,255/255.f,0/255.f,255/255.f},2,ImDrawFlags_RoundCornersAll);
}

void 绘制野怪计时(int X, int Y, const char *data)
{
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(X-60, Y-110), ImColor {1.0f, 1.0f, 1.0f, 1.0f},data);
}

void 绘制人数(int playercount)
{
	char extra[100];
    sprintf(extra, "%d",playercount);
    ImGui::GetForegroundDrawList()->AddText({2400 /2-5, 100}, ImColor(225,255,255), extra); 
}

void 绘制距离(float x1, float bottom, float Distance)
{
	std::string s;
	s += std::to_string((int)Distance);
	s += "米";
	auto textSize1 = ImGui::CalcTextSize(s.c_str(), 0, 29);
	绘制字体描边(22.5,x1 - (textSize1.x / 2), bottom,ImColor(248,248,255),s.c_str());
}


//王者共享内容

//共享菜单全部   
int pxx = 0, pyy = 0; double WwrShare = 0.0;//临时分辨率
bool 初始化 = false;
bool Touchinit = true;
int Screen_X, Screen_Y;
int xytable[10][10];
int hist1[10][10];
int me1 = 0;
float ax, ay;
int prex1, prey1;
long a, objarrayaddr, libGameCore1, libil2cpp1, 兵线基址, 人物数组, 野怪数组, 兵线数组, 矩阵;
int 阵营1 = 0, fx1 = 0;
int 一键开启共享=false;

struct sESPMenu {
    bool 绘制调试 = false;
    bool 全部关闭;
    bool 是否开启共享;
    bool 全部开启;
    bool 显示头像;
    bool 保存调试配置到云端;
    bool 技能计时;
    bool 野怪计时;
    bool 显示兵线;
    bool 回城判断;
    bool 敌人视野;
    int 分辨率Y = 2456;//2712  
    int 分辨率X = 2456;//1220  2846

    int 小地图左右调整 = -7;//我的配置87   -3
    int 小地图上下调整 = -4;//   -4
    int 兵线左右调整 = 9;//我的配置6
    int 兵线上下调整 = -27;//31
    int 野怪左右调整 = -9;//我的配置-6
    int 野怪上下调整 = -5;//-1
    int FPS帧率 = 120;

};
sESPMenu ESPMenu;


//共享头文件
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>

#define MAX_BUFFER_SIZE 1024
int ret = -1;
int socket_fd;
struct sockaddr_in serveraddr;
char buffer[MAX_BUFFER_SIZE];
char homeBuffer[MAX_BUFFER_SIZE];
int numBytesReceived, homeBytesReceived;
std::string 共享房间ip = "38.55.232.31";//主机  
bool 是否开启共享 = true;
void createSocket() {//重要方法
	

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        exit(0);
    }
    if (socket_fd < 0) {
    printf("[+] 连接失败，请迅速联系开发者\n");
        exit(0);
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr((char*)共享房间ip.data());
    serveraddr.sin_port = htons(9999);
    ret = connect(socket_fd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));
    if (ret < 0) {
    
    
          exit(0);
            
    }
 printf("[+] 共享服务器连接成功\n[+] 共享服务器http://38.55.232.31/\n");
}
