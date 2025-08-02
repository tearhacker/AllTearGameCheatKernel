#include "kernel.h"
#include <imgui.h>
#include <stb_image.h>
uintptr_t libbase;
float NumIo[50];
bool DrawIo[50];
//int style_zx = 0;
int 内透=0;
ImTextureID ImAgeHeadFile(const unsigned char *buf, int len)
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
	//ImTextureID image_id = texture;
	ImTextureID image_id = (ImTextureID)(uintptr_t)texture; // 正确的类型转换
	return image_id;
}
void 绘制加粗文本(float size, float x, float y, ImColor color, ImColor color1, const char* str)
{
    ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x-0.1, y-0.1), color1, str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x+0.1, y+0.1), color1, str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x, y), color, str);
}
void 绘制字体描边(float size,ImVec2 坐标, ImVec4 color, const char* str)
{
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(坐标.x + 1, 坐标.y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(坐标.x - 0.1, 坐标.y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(坐标.x, 坐标.y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(坐标.x, 坐标.y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(坐标.x, 坐标.y), ImGui::ColorConvertFloat4ToU32(color), str);
}

ImTextureID 悬浮窗图标;


void 绘制触摸范围(float x,float y,float r){
ImGui::GetForegroundDrawList()->AddCircleArc({x, y},r, ImVec2(0, 360), ImColor(219, 77, 110),  0, 2.0f);//白底背景
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


int 傀儡x;
int 傀儡y;


int dsfkzy;
int 上下间隔;
int zhenlv = 0;//帧率
long int libbase3;
long int libbase2;
static bool 触摸驱动 = true;
static bool 地图大招计时 = false;
static bool 方框技能旧 = false;
static bool 关闭 = 1;
static bool 音量控制 = false;
static bool 小技能计时 = false;
static bool 头像常显 = true;
static bool 血量 = false;
static bool 地图 = false;
static int circleX = NumIo[46]; // 默认X坐标
static int circleY = NumIo[45]; // 默认Y坐标
static bool 方框2 = false;
static bool 方框 = false;
static bool 自瞄 = false;
static bool 射线 = false;
static bool 距离 = true;
static bool 野怪 = false;
static bool 兵线 = false;
static bool 方框技能 = false;
static bool 顶上技能 = false;
static bool 近景上帝 = false;
static bool 上帝 = false;
static bool 视野方框 = false;
static bool 自身 = false;
static bool 辅助方框 = false;
static bool 防录屏 = false;
static bool 自动斩杀 = false;
static bool 自动惩戒 = false;
static bool 自动净化 = false;
static bool 惩戒判断 = false;
static bool 智能不惩 = false;
static bool 智能斩杀 = true;  
static bool 绘制触摸 = false;
static bool 触摸缓冲 = false;
static bool 实体兵线 = false;
static bool 触摸 = false;
static bool 十人 = false;
static bool 血量判断 = false;
static bool 方框技能9= false;
static bool 健康血量 = true;
static bool 防掉框 = false;
static bool 解密 = false;
static bool 读取固定偏移 = true;
static bool 暗化 = true;
static bool 暴露视野不绘 = false;
static bool 圆弧血量 = false;
static bool 方框技能不绘 = false;
static int 防录屏开关=0;
static bool 长方血量 = 0;
static bool 绘图方框 = true;
static bool 眼位 = false;
static bool 不惩小野 = false;
static bool 实体眼位 = false;
static bool 方框技能2 = false;
static bool 技能3 = false;
static bool 国标视野 = false;
static bool shared = false;
bool 貂蝉减cd = false;
static float 貂蝉dd = 1334.0; //标准
static float 貂蝉大招dd = 250.0; //标准
static float 澜 = 2000.0; //标准
 static bool 野血 = false;
int qianxin = -1; // 
static bool 顶上技能2 = false;
static int jk = 0;
static int 屏幕方向 = 1;
int currentChoice = -1;
static bool stopFlag = false;
float 透明度 = 1.0f; // 默认不透明 float 特定字体大小 = 1.0f; // 默认字体大小
int yxpx,yxpy;
float 特定字体大小 = 1.0f; // 默认字体大小 
int 召唤师技能CD;
int 召唤师技能ID;
int 召唤师ID;
string 召唤师技能="未知";
string 召唤师="未知";



 struct 总颜色
{
ImColor 血量颜色 = ImColor(0,255,0,255);//血量颜色
ImColor 射线颜色 = ImColor(255,255,255,255);
ImColor 方框颜色 = ImColor(255,255,255,255);
ImColor 有视野血量颜色 = ImColor(0,255,0,255);
ImColor 无视野血量颜色 = ImColor(0,255,0,255);
};




总颜色 颜色配置;

//读取Set
int ReadDrawSet(总颜色 *myDrawSet,const char* Filename)
{
    FILE* pFile;

    pFile = fopen(Filename, "rb");
    if (pFile == NULL) {
        //printf("文件打开失败");
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
    	printf("\033[31;1m");//红色
        printf("创建文件失败");
        return 0;
    }

    fwrite(myDrawSet, sizeof(总颜色), 1, pFile);

    fclose(pFile);
    return 1;
}

int pdys;

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


float shangdi=0.1f;//上帝高度
int 屏幕x=0;
int 屏幕y=0;

int FPS=90;

int scale_factor = 1.5f;

int chengjie=0;
float zhansha=15;
int zhanshaz = zhansha/100;
int zhsX=1617;
int zhsY=965;
float 当前血量;

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


/*void 写出文件(char *aaa,char *bbb){
	
	system("mkdir -p  /storage/emulated/0/DES/配置");
	std::ofstream ofs;
	
	
	ofs.open(aaa, std::ios::out);

	ofs << bbb 
		;

	ofs.close();
}*/




bool 悬浮球 = false;
bool 悬浮窗 = true;

ImVec2 Pos; //窗口位置
static bool 窗口状态=false; //窗口状态
static bool 窗口状态item=false;
static bool IsBall = true;
ImVec2 ImagePos = {0, 0};





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
	//textureInfo.textureId=texture;
	ImTextureID image_id = (ImTextureID)(uintptr_t)texture; // 正确的类型转换
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

#include "Gerpicture/picture_obj0_png.h"

#include "Gerpicture/picture_obj105_png.h"
#include "Gerpicture/picture_obj106_png.h"
#include "Gerpicture/picture_obj107_png.h"
#include "Gerpicture/picture_obj108_png.h"
#include "Gerpicture/picture_obj109_png.h"
#include "Gerpicture/picture_obj110_png.h"
#include "Gerpicture/picture_obj111_png.h"
#include "Gerpicture/picture_obj112_png.h"
#include "Gerpicture/picture_obj113_png.h"
#include "Gerpicture/picture_obj114_png.h"
#include "Gerpicture/picture_obj115_png.h"
#include "Gerpicture/picture_obj116_png.h"
#include "Gerpicture/picture_obj117_png.h"
#include "Gerpicture/picture_obj118_png.h"
#include "Gerpicture/picture_obj119_png.h"
#include "Gerpicture/picture_obj120_png.h"
#include "Gerpicture/picture_obj121_png.h"
#include "Gerpicture/picture_obj123_png.h"
#include "Gerpicture/picture_obj124_png.h"
#include "Gerpicture/picture_obj125_png.h"
#include "Gerpicture/picture_obj126_png.h"
#include "Gerpicture/picture_obj127_png.h"
#include "Gerpicture/picture_obj128_png.h"
#include "Gerpicture/picture_obj129_png.h"
#include "Gerpicture/picture_obj130_png.h"
#include "Gerpicture/picture_obj131_png.h"
#include "Gerpicture/picture_obj132_png.h"
#include "Gerpicture/picture_obj133_png.h"
#include "Gerpicture/picture_obj134_png.h"
#include "Gerpicture/picture_obj135_png.h"
#include "Gerpicture/picture_obj136_png.h"
#include "Gerpicture/picture_obj137_png.h"
#include "Gerpicture/picture_obj139_png.h"
#include "Gerpicture/picture_obj140_png.h"
#include "Gerpicture/picture_obj141_png.h"
#include "Gerpicture/picture_obj142_png.h"
#include "Gerpicture/picture_obj144_png.h"
#include "Gerpicture/picture_obj146_png.h"
#include "Gerpicture/picture_obj148_png.h"
#include "Gerpicture/picture_obj149_png.h"
#include "Gerpicture/picture_obj150_png.h"
#include "Gerpicture/picture_obj152_png.h"
#include "Gerpicture/picture_obj153_png.h"
#include "Gerpicture/picture_obj154_png.h"
#include "Gerpicture/picture_obj155_png.h"
#include "Gerpicture/picture_obj156_png.h"
#include "Gerpicture/picture_obj157_png.h"
#include "Gerpicture/picture_obj162_png.h"
#include "Gerpicture/picture_obj163_png.h"
#include "Gerpicture/picture_obj166_png.h"
#include "Gerpicture/picture_obj167_png.h"
#include "Gerpicture/picture_obj168_png.h"
#include "Gerpicture/picture_obj169_png.h"
#include "Gerpicture/picture_obj170_png.h"
#include "Gerpicture/picture_obj171_png.h"
#include "Gerpicture/picture_obj173_png.h"
#include "Gerpicture/picture_obj174_png.h"
#include "Gerpicture/picture_obj175_png.h"
#include "Gerpicture/picture_obj176_png.h"
#include "Gerpicture/picture_obj177_png.h"
#include "Gerpicture/picture_obj178_png.h"
#include "Gerpicture/picture_obj179_png.h"
#include "Gerpicture/picture_obj180_png.h"
#include "Gerpicture/picture_obj182_png.h"
#include "Gerpicture/picture_obj183_png.h"
#include "Gerpicture/picture_obj184_png.h"
#include "Gerpicture/picture_obj186_png.h"
#include "Gerpicture/picture_obj187_png.h"
#include "Gerpicture/picture_obj189_png.h"
#include "Gerpicture/picture_obj190_png.h"
#include "Gerpicture/picture_obj191_png.h"
#include "Gerpicture/picture_obj192_png.h"
#include "Gerpicture/picture_obj193_png.h"
#include "Gerpicture/picture_obj194_png.h"
#include "Gerpicture/picture_obj195_png.h"
#include "Gerpicture/picture_obj196_png.h"
#include "Gerpicture/picture_obj197_png.h"
#include "Gerpicture/picture_obj198_png.h"
#include "Gerpicture/picture_obj199_png.h"
#include "Gerpicture/picture_obj312_png.h"
#include "Gerpicture/picture_obj501_png.h"
#include "Gerpicture/picture_obj502_png.h"
#include "Gerpicture/picture_obj503_png.h"
#include "Gerpicture/picture_obj504_png.h"
#include "Gerpicture/picture_obj505_png.h"
#include "Gerpicture/picture_obj506_png.h"
#include "Gerpicture/picture_obj507_png.h"
#include "Gerpicture/picture_obj508_png.h"
#include "Gerpicture/picture_obj509_png.h"
#include "Gerpicture/picture_obj510_png.h"
#include "Gerpicture/picture_obj511_png.h"
#include "Gerpicture/picture_obj513_png.h"
#include "Gerpicture/picture_obj515_png.h"
#include "Gerpicture/picture_obj517_png.h"
#include "Gerpicture/picture_obj519_png.h"
#include "Gerpicture/picture_obj518_png.h"
#include "Gerpicture/picture_obj521_png.h"
#include "Gerpicture/picture_obj522_png.h"
#include "Gerpicture/picture_obj523_png.h"
#include "Gerpicture/picture_obj524_png.h"
#include "Gerpicture/picture_obj525_png.h"
#include "Gerpicture/picture_obj527_png.h"
#include "Gerpicture/picture_obj528_png.h"
#include "Gerpicture/picture_obj529_png.h"
#include "Gerpicture/picture_obj531_png.h"
#include "Gerpicture/picture_obj533_png.h"
#include "Gerpicture/picture_obj534_png.h"
#include "Gerpicture/picture_obj536_png.h"
#include "Gerpicture/picture_obj537_png.h"
#include "Gerpicture/picture_obj538_png.h"
#include "Gerpicture/picture_obj540_png.h"
#include "Gerpicture/picture_obj542_png.h"
#include "Gerpicture/picture_obj544_png.h"
#include "Gerpicture/picture_obj545_png.h"
#include "Gerpicture/picture_obj548_png.h"
#include "Gerpicture/picture_obj564_png.h"
#include "Gerpicture/picture_obj514_png.h"
#include "Gerpicture/picture_obj563_png.h"
#include "Gerpicture/picture_obj558_png.h"
#include "Gerpicture/picture_obj159_png.h"
//#include "Gerpicture/picture_obj581_png.h"
#include "Gerpicture/picture_obj582_png.h"
#include "Gerpicture/picture_obj620_png.h"
#include "Gerpicture/背景图一.h"
#include "Gerpicture/图片.h"
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
HeadPortrait[159] = createTexturePNGFromMem(picture_obj159_PNG_H, sizeof(picture_obj159_PNG_H));
HeadPortrait[581] = createTexturePNGFromMem(picture_obj620_PNG_H, sizeof(picture_obj620_PNG_H));
HeadPortrait[582] = createTexturePNGFromMem(picture_obj582_PNG_H, sizeof(picture_obj582_PNG_H));
HeadPortrait[558] = createTexturePNGFromMem(picture_obj558_PNG_H, sizeof(picture_obj558_PNG_H));
HeadPortrait[620] = createTexturePNGFromMem(picture_obj620_PNG_H, sizeof(picture_obj620_PNG_H));
}


        struct 全部头像1
{
	TextureInfoa 头像[650];
	
};
全部头像1 贴图1;

void 获取头像2(){
	
	Loadpicture_obj(贴图1.头像);
	
}

#include "Gerpicture/picture_obj80102_png.h"
#include "Gerpicture/picture_obj80103_png.h"
#include "Gerpicture/picture_obj80104_png.h"
#include "Gerpicture/picture_obj80105_png.h"
#include "Gerpicture/picture_obj80107_png.h"
#include "Gerpicture/picture_obj80108_png.h"
#include "Gerpicture/picture_obj80109_png.h"
#include "Gerpicture/picture_obj80110_png.h"
#include "Gerpicture/picture_obj80115_png.h"
#include "Gerpicture/picture_obj80116_png.h"
#include "Gerpicture/picture_obj80121_png.h"
#include "Gerpicture/picture_obj801162_png.h"

#include "Gerpicture/picture_obj10510_png.h"
#include "Gerpicture/picture_obj10610_png.h"
#include "Gerpicture/picture_obj10710_png.h"
#include "Gerpicture/picture_obj10810_png.h"
#include "Gerpicture/picture_obj10910_png.h"
#include "Gerpicture/picture_obj11010_png.h"
#include "Gerpicture/picture_obj11110_png.h"
#include "Gerpicture/picture_obj11210_png.h"
#include "Gerpicture/picture_obj11310_png.h"
#include "Gerpicture/picture_obj11410_png.h"
#include "Gerpicture/picture_obj11510_png.h"
#include "Gerpicture/picture_obj11610_png.h"
#include "Gerpicture/picture_obj11710_png.h"
#include "Gerpicture/picture_obj11810_png.h"
#include "Gerpicture/picture_obj11910_png.h"
#include "Gerpicture/picture_obj12010_png.h"
#include "Gerpicture/picture_obj12110_png.h"
#include "Gerpicture/picture_obj12310_png.h"
#include "Gerpicture/picture_obj12410_png.h"
#include "Gerpicture/picture_obj12510_png.h"
#include "Gerpicture/picture_obj12610_png.h"
#include "Gerpicture/picture_obj12710_png.h"
#include "Gerpicture/picture_obj12810_png.h"
#include "Gerpicture/picture_obj12910_png.h"
#include "Gerpicture/picture_obj13010_png.h"
#include "Gerpicture/picture_obj13110_png.h"
#include "Gerpicture/picture_obj13210_png.h"
#include "Gerpicture/picture_obj13310_png.h"
#include "Gerpicture/picture_obj13410_png.h"
#include "Gerpicture/picture_obj13510_png.h"
#include "Gerpicture/picture_obj13610_png.h"
#include "Gerpicture/picture_obj13710_png.h"
#include "Gerpicture/picture_obj13910_png.h"
#include "Gerpicture/picture_obj14010_png.h"
#include "Gerpicture/picture_obj14110_png.h"
#include "Gerpicture/picture_obj14210_png.h"
#include "Gerpicture/picture_obj14410_png.h"
#include "Gerpicture/picture_obj14610_png.h"
#include "Gerpicture/picture_obj14810_png.h"
#include "Gerpicture/picture_obj14910_png.h"
#include "Gerpicture/picture_obj15010_png.h"
#include "Gerpicture/picture_obj15210_png.h"
#include "Gerpicture/picture_obj15310_png.h"
#include "Gerpicture/picture_obj15410_png.h"
#include "Gerpicture/picture_obj15510_png.h"
#include "Gerpicture/picture_obj15610_png.h"
#include "Gerpicture/picture_obj15710_png.h"
#include "Gerpicture/picture_obj15910_png.h"
#include "Gerpicture/picture_obj16210_png.h"
#include "Gerpicture/picture_obj16310_png.h"
#include "Gerpicture/picture_obj16610_png.h"
#include "Gerpicture/picture_obj16710_png.h"
#include "Gerpicture/picture_obj16810_png.h"
#include "Gerpicture/picture_obj16910_png.h"
#include "Gerpicture/picture_obj17010_png.h"
#include "Gerpicture/picture_obj17110_png.h"
#include "Gerpicture/picture_obj17310_png.h"
#include "Gerpicture/picture_obj17410_png.h"
#include "Gerpicture/picture_obj17510_png.h"
#include "Gerpicture/picture_obj17610_png.h"
#include "Gerpicture/picture_obj17710_png.h"
#include "Gerpicture/picture_obj17810_png.h"
#include "Gerpicture/picture_obj17910_png.h"
#include "Gerpicture/picture_obj18010_png.h"
#include "Gerpicture/picture_obj18210_png.h"
#include "Gerpicture/picture_obj18310_png.h"
#include "Gerpicture/picture_obj18410_png.h"
#include "Gerpicture/picture_obj18610_png.h"
#include "Gerpicture/picture_obj18710_png.h"
#include "Gerpicture/picture_obj18910_png.h"
#include "Gerpicture/picture_obj19010_png.h"
#include "Gerpicture/picture_obj19110_png.h"
#include "Gerpicture/picture_obj19210_png.h"
#include "Gerpicture/picture_obj19310_png.h"
#include "Gerpicture/picture_obj19410_png.h"
#include "Gerpicture/picture_obj19510_png.h"
#include "Gerpicture/picture_obj19610_png.h"
#include "Gerpicture/picture_obj19710_png.h"
#include "Gerpicture/picture_obj19810_png.h"
#include "Gerpicture/picture_obj19910_png.h"
#include "Gerpicture/picture_obj31210_png.h"
#include "Gerpicture/picture_obj50110_png.h"
#include "Gerpicture/picture_obj50210_png.h"
#include "Gerpicture/picture_obj50310_png.h"
#include "Gerpicture/picture_obj50410_png.h"
#include "Gerpicture/picture_obj50510_png.h"
#include "Gerpicture/picture_obj50610_png.h"
#include "Gerpicture/picture_obj50710_png.h"
#include "Gerpicture/picture_obj50810_png.h"
#include "Gerpicture/picture_obj50910_png.h"
#include "Gerpicture/picture_obj51010_png.h"
#include "Gerpicture/picture_obj51110_png.h"
#include "Gerpicture/picture_obj51310_png.h"
#include "Gerpicture/picture_obj51410_png.h"
#include "Gerpicture/picture_obj51510_png.h"
#include "Gerpicture/picture_obj51710_png.h"
#include "Gerpicture/picture_obj51810_png.h"
#include "Gerpicture/picture_obj51910_png.h"
#include "Gerpicture/picture_obj52110_png.h"
#include "Gerpicture/picture_obj52210_png.h"
#include "Gerpicture/picture_obj52310_png.h"
#include "Gerpicture/picture_obj52410_png.h"
#include "Gerpicture/picture_obj52510_png.h"
#include "Gerpicture/picture_obj52710_png.h"
#include "Gerpicture/picture_obj52810_png.h"
#include "Gerpicture/picture_obj52910_png.h"
#include "Gerpicture/picture_obj53110_png.h"
#include "Gerpicture/picture_obj53310_png.h"
#include "Gerpicture/picture_obj53410_png.h"
#include "Gerpicture/picture_obj53610_png.h"
#include "Gerpicture/picture_obj53710_png.h"
#include "Gerpicture/picture_obj53810_png.h"
#include "Gerpicture/picture_obj54010_png.h"
#include "Gerpicture/picture_obj54210_png.h"
#include "Gerpicture/picture_obj54410_png.h"
#include "Gerpicture/picture_obj54510_png.h"
#include "Gerpicture/picture_obj54810_png.h"
#include "Gerpicture/picture_obj56310_png.h"
#include "Gerpicture/picture_obj56410_png.h"
#include "Gerpicture/picture_obj62010_png.h"


#include "Gerpicture/picture_obj10520_png.h"
#include "Gerpicture/picture_obj10620_png.h"
#include "Gerpicture/picture_obj10720_png.h"
#include "Gerpicture/picture_obj10820_png.h"
#include "Gerpicture/picture_obj10920_png.h"
#include "Gerpicture/picture_obj11020_png.h"
#include "Gerpicture/picture_obj11120_png.h"
#include "Gerpicture/picture_obj11220_png.h"
#include "Gerpicture/picture_obj11320_png.h"
#include "Gerpicture/picture_obj11420_png.h"
#include "Gerpicture/picture_obj11520_png.h"
#include "Gerpicture/picture_obj11620_png.h"
#include "Gerpicture/picture_obj11720_png.h"
#include "Gerpicture/picture_obj11820_png.h"
#include "Gerpicture/picture_obj11920_png.h"
#include "Gerpicture/picture_obj12020_png.h"
#include "Gerpicture/picture_obj12120_png.h"
#include "Gerpicture/picture_obj12320_png.h"
#include "Gerpicture/picture_obj12420_png.h"
#include "Gerpicture/picture_obj12520_png.h"
#include "Gerpicture/picture_obj12620_png.h"
#include "Gerpicture/picture_obj12720_png.h"
#include "Gerpicture/picture_obj12820_png.h"
#include "Gerpicture/picture_obj12920_png.h"
#include "Gerpicture/picture_obj13020_png.h"
#include "Gerpicture/picture_obj13120_png.h"
#include "Gerpicture/picture_obj13220_png.h"
#include "Gerpicture/picture_obj13320_png.h"
#include "Gerpicture/picture_obj13420_png.h"
#include "Gerpicture/picture_obj13520_png.h"
#include "Gerpicture/picture_obj13620_png.h"
#include "Gerpicture/picture_obj13720_png.h"
#include "Gerpicture/picture_obj13920_png.h"
#include "Gerpicture/picture_obj14020_png.h"
#include "Gerpicture/picture_obj14120_png.h"
#include "Gerpicture/picture_obj14220_png.h"
#include "Gerpicture/picture_obj14420_png.h"
#include "Gerpicture/picture_obj14620_png.h"
#include "Gerpicture/picture_obj14820_png.h"
#include "Gerpicture/picture_obj14920_png.h"
#include "Gerpicture/picture_obj15020_png.h"
#include "Gerpicture/picture_obj15220_png.h"
#include "Gerpicture/picture_obj15320_png.h"
#include "Gerpicture/picture_obj15420_png.h"
#include "Gerpicture/picture_obj15520_png.h"
#include "Gerpicture/picture_obj15620_png.h"
#include "Gerpicture/picture_obj15720_png.h"
#include "Gerpicture/picture_obj15920_png.h"
#include "Gerpicture/picture_obj16220_png.h"
#include "Gerpicture/picture_obj16320_png.h"
#include "Gerpicture/picture_obj16620_png.h"
#include "Gerpicture/picture_obj16720_png.h"
#include "Gerpicture/picture_obj16820_png.h"
#include "Gerpicture/picture_obj16920_png.h"
#include "Gerpicture/picture_obj17020_png.h"
#include "Gerpicture/picture_obj17120_png.h"
#include "Gerpicture/picture_obj17320_png.h"
#include "Gerpicture/picture_obj17420_png.h"
#include "Gerpicture/picture_obj17520_png.h"
#include "Gerpicture/picture_obj17620_png.h"
#include "Gerpicture/picture_obj17720_png.h"
#include "Gerpicture/picture_obj17820_png.h"
#include "Gerpicture/picture_obj17920_png.h"
#include "Gerpicture/picture_obj18020_png.h"
#include "Gerpicture/picture_obj18220_png.h"
#include "Gerpicture/picture_obj18320_png.h"
#include "Gerpicture/picture_obj18420_png.h"
#include "Gerpicture/picture_obj18620_png.h"
#include "Gerpicture/picture_obj18720_png.h"
#include "Gerpicture/picture_obj18920_png.h"
#include "Gerpicture/picture_obj19020_png.h"
#include "Gerpicture/picture_obj19120_png.h"
#include "Gerpicture/picture_obj19220_png.h"
#include "Gerpicture/picture_obj19320_png.h"
#include "Gerpicture/picture_obj19420_png.h"
#include "Gerpicture/picture_obj19520_png.h"
#include "Gerpicture/picture_obj19620_png.h"
#include "Gerpicture/picture_obj19720_png.h"
#include "Gerpicture/picture_obj19820_png.h"
#include "Gerpicture/picture_obj19920_png.h"
#include "Gerpicture/picture_obj31220_png.h"
#include "Gerpicture/picture_obj50120_png.h"
#include "Gerpicture/picture_obj50220_png.h"
#include "Gerpicture/picture_obj50320_png.h"
#include "Gerpicture/picture_obj50420_png.h"
#include "Gerpicture/picture_obj50520_png.h"
#include "Gerpicture/picture_obj50620_png.h"
#include "Gerpicture/picture_obj50720_png.h"
#include "Gerpicture/picture_obj50820_png.h"
#include "Gerpicture/picture_obj50920_png.h"
#include "Gerpicture/picture_obj51020_png.h"
#include "Gerpicture/picture_obj51120_png.h"
#include "Gerpicture/picture_obj51320_png.h"
#include "Gerpicture/picture_obj51420_png.h"
#include "Gerpicture/picture_obj51520_png.h"
#include "Gerpicture/picture_obj51720_png.h"
#include "Gerpicture/picture_obj51820_png.h"
#include "Gerpicture/picture_obj51920_png.h"
#include "Gerpicture/picture_obj52120_png.h"
#include "Gerpicture/picture_obj52220_png.h"
#include "Gerpicture/picture_obj52320_png.h"
#include "Gerpicture/picture_obj52420_png.h"
#include "Gerpicture/picture_obj52520_png.h"
#include "Gerpicture/picture_obj52720_png.h"
#include "Gerpicture/picture_obj52820_png.h"
#include "Gerpicture/picture_obj52920_png.h"
#include "Gerpicture/picture_obj53120_png.h"
#include "Gerpicture/picture_obj53320_png.h"
#include "Gerpicture/picture_obj53420_png.h"
#include "Gerpicture/picture_obj53620_png.h"
#include "Gerpicture/picture_obj53720_png.h"
#include "Gerpicture/picture_obj53820_png.h"
#include "Gerpicture/picture_obj54020_png.h"
#include "Gerpicture/picture_obj54220_png.h"
#include "Gerpicture/picture_obj54420_png.h"
#include "Gerpicture/picture_obj54520_png.h"
#include "Gerpicture/picture_obj54820_png.h"
#include "Gerpicture/picture_obj56320_png.h"
#include "Gerpicture/picture_obj56420_png.h"
#include "Gerpicture/picture_obj58220_png.h"
#include "Gerpicture/picture_obj62020_png.h"


#include "Gerpicture/picture_obj10530_png.h"
#include "Gerpicture/picture_obj10630_png.h"
#include "Gerpicture/picture_obj10730_png.h"
#include "Gerpicture/picture_obj10830_png.h"
#include "Gerpicture/picture_obj10930_png.h"
#include "Gerpicture/picture_obj11030_png.h"
#include "Gerpicture/picture_obj11130_png.h"
#include "Gerpicture/picture_obj11230_png.h"
#include "Gerpicture/picture_obj11330_png.h"
#include "Gerpicture/picture_obj11430_png.h"
#include "Gerpicture/picture_obj11530_png.h"
#include "Gerpicture/picture_obj11630_png.h"
#include "Gerpicture/picture_obj11730_png.h"
#include "Gerpicture/picture_obj11830_png.h"
#include "Gerpicture/picture_obj11930_png.h"
#include "Gerpicture/picture_obj12030_png.h"
#include "Gerpicture/picture_obj12130_png.h"
#include "Gerpicture/picture_obj12330_png.h"
#include "Gerpicture/picture_obj12430_png.h"
#include "Gerpicture/picture_obj12530_png.h"
#include "Gerpicture/picture_obj12630_png.h"
#include "Gerpicture/picture_obj12730_png.h"
#include "Gerpicture/picture_obj12830_png.h"
#include "Gerpicture/picture_obj12930_png.h"
#include "Gerpicture/picture_obj13030_png.h"
#include "Gerpicture/picture_obj13130_png.h"
#include "Gerpicture/picture_obj13230_png.h"
#include "Gerpicture/picture_obj13330_png.h"
#include "Gerpicture/picture_obj13430_png.h"
#include "Gerpicture/picture_obj13530_png.h"
#include "Gerpicture/picture_obj13630_png.h"
#include "Gerpicture/picture_obj13730_png.h"
#include "Gerpicture/picture_obj13930_png.h"
#include "Gerpicture/picture_obj14030_png.h"
#include "Gerpicture/picture_obj14130_png.h"
#include "Gerpicture/picture_obj14230_png.h"
#include "Gerpicture/picture_obj14430_png.h"
#include "Gerpicture/picture_obj14630_png.h"
#include "Gerpicture/picture_obj14830_png.h"
#include "Gerpicture/picture_obj14930_png.h"
#include "Gerpicture/picture_obj15030_png.h"
#include "Gerpicture/picture_obj15230_png.h"
#include "Gerpicture/picture_obj15330_png.h"
#include "Gerpicture/picture_obj15430_png.h"
#include "Gerpicture/picture_obj15530_png.h"
#include "Gerpicture/picture_obj15630_png.h"
#include "Gerpicture/picture_obj15730_png.h"
#include "Gerpicture/picture_obj15930_png.h"
#include "Gerpicture/picture_obj16230_png.h"
#include "Gerpicture/picture_obj16330_png.h"
#include "Gerpicture/picture_obj16630_png.h"
#include "Gerpicture/picture_obj16730_png.h"
#include "Gerpicture/picture_obj16830_png.h"
#include "Gerpicture/picture_obj16930_png.h"
#include "Gerpicture/picture_obj17030_png.h"
#include "Gerpicture/picture_obj17130_png.h"
#include "Gerpicture/picture_obj17330_png.h"
#include "Gerpicture/picture_obj17430_png.h"
#include "Gerpicture/picture_obj17530_png.h"
#include "Gerpicture/picture_obj17630_png.h"
#include "Gerpicture/picture_obj17730_png.h"
#include "Gerpicture/picture_obj17830_png.h"
#include "Gerpicture/picture_obj17930_png.h"
#include "Gerpicture/picture_obj18030_png.h"
#include "Gerpicture/picture_obj18230_png.h"
#include "Gerpicture/picture_obj18330_png.h"
#include "Gerpicture/picture_obj18430_png.h"
#include "Gerpicture/picture_obj18630_png.h"
#include "Gerpicture/picture_obj18730_png.h"
#include "Gerpicture/picture_obj18930_png.h"
#include "Gerpicture/picture_obj19030_png.h"
#include "Gerpicture/picture_obj19130_png.h"
#include "Gerpicture/picture_obj19230_png.h"
#include "Gerpicture/picture_obj19330_png.h"
#include "Gerpicture/picture_obj19430_png.h"
#include "Gerpicture/picture_obj19530_png.h"
#include "Gerpicture/picture_obj19630_png.h"
#include "Gerpicture/picture_obj19730_png.h"
#include "Gerpicture/picture_obj19830_png.h"
#include "Gerpicture/picture_obj19930_png.h"
#include "Gerpicture/picture_obj31230_png.h"
#include "Gerpicture/picture_obj50130_png.h"
#include "Gerpicture/picture_obj50230_png.h"
#include "Gerpicture/picture_obj50330_png.h"
#include "Gerpicture/picture_obj50430_png.h"
#include "Gerpicture/picture_obj50530_png.h"
#include "Gerpicture/picture_obj50630_png.h"
#include "Gerpicture/picture_obj50730_png.h"
#include "Gerpicture/picture_obj50830_png.h"
#include "Gerpicture/picture_obj50930_png.h"
#include "Gerpicture/picture_obj51030_png.h"
#include "Gerpicture/picture_obj51130_png.h"
#include "Gerpicture/picture_obj51330_png.h"
#include "Gerpicture/picture_obj51430_png.h"
#include "Gerpicture/picture_obj51530_png.h"
#include "Gerpicture/picture_obj51730_png.h"
#include "Gerpicture/picture_obj51830_png.h"
#include "Gerpicture/picture_obj51930_png.h"
#include "Gerpicture/picture_obj52130_png.h"
#include "Gerpicture/picture_obj52230_png.h"
#include "Gerpicture/picture_obj52330_png.h"
#include "Gerpicture/picture_obj52430_png.h"
#include "Gerpicture/picture_obj52530_png.h"
#include "Gerpicture/picture_obj52730_png.h"
#include "Gerpicture/picture_obj52830_png.h"
#include "Gerpicture/picture_obj52930_png.h"
#include "Gerpicture/picture_obj53130_png.h"
#include "Gerpicture/picture_obj53330_png.h"
#include "Gerpicture/picture_obj53430_png.h"
#include "Gerpicture/picture_obj53630_png.h"
#include "Gerpicture/picture_obj53730_png.h"
#include "Gerpicture/picture_obj53830_png.h"
#include "Gerpicture/picture_obj54030_png.h"
#include "Gerpicture/picture_obj54230_png.h"
#include "Gerpicture/picture_obj54430_png.h"
#include "Gerpicture/picture_obj54530_png.h"
#include "Gerpicture/picture_obj54830_png.h"
#include "Gerpicture/picture_obj56330_png.h"
#include "Gerpicture/picture_obj56430_png.h"
#include "Gerpicture/picture_obj58230_png.h"
#include "Gerpicture/picture_obj62030_png.h"


void Loadpicture_obj2(TextureInfoa *HeadPortrait)
{

HeadPortrait[-1022] = createTexturePNGFromMem(背景图一, sizeof(背景图一));

HeadPortrait[0] = createTexturePNGFromMem(picture_obj0_PNG_H, sizeof(picture_obj0_PNG_H));
HeadPortrait[10530] = createTexturePNGFromMem(picture_obj10530_PNG_H, sizeof(picture_obj10530_PNG_H));
HeadPortrait[10630] = createTexturePNGFromMem(picture_obj10630_PNG_H, sizeof(picture_obj10630_PNG_H));
HeadPortrait[10730] = createTexturePNGFromMem(picture_obj10730_PNG_H, sizeof(picture_obj10730_PNG_H));
HeadPortrait[10830] = createTexturePNGFromMem(picture_obj10830_PNG_H, sizeof(picture_obj10830_PNG_H));
HeadPortrait[10930] = createTexturePNGFromMem(picture_obj10930_PNG_H, sizeof(picture_obj10930_PNG_H));
HeadPortrait[11030] = createTexturePNGFromMem(picture_obj11030_PNG_H, sizeof(picture_obj11030_PNG_H));
HeadPortrait[11130] = createTexturePNGFromMem(picture_obj11130_PNG_H, sizeof(picture_obj11130_PNG_H));
HeadPortrait[11230] = createTexturePNGFromMem(picture_obj11230_PNG_H, sizeof(picture_obj11230_PNG_H));
HeadPortrait[11330] = createTexturePNGFromMem(picture_obj11330_PNG_H, sizeof(picture_obj11330_PNG_H));
HeadPortrait[11430] = createTexturePNGFromMem(picture_obj11430_PNG_H, sizeof(picture_obj11430_PNG_H));
HeadPortrait[11530] = createTexturePNGFromMem(picture_obj11530_PNG_H, sizeof(picture_obj11530_PNG_H));
HeadPortrait[11630] = createTexturePNGFromMem(picture_obj11630_PNG_H, sizeof(picture_obj11630_PNG_H));
HeadPortrait[11730] = createTexturePNGFromMem(picture_obj11730_PNG_H, sizeof(picture_obj11730_PNG_H));
HeadPortrait[11830] = createTexturePNGFromMem(picture_obj11830_PNG_H, sizeof(picture_obj11830_PNG_H));
HeadPortrait[11930] = createTexturePNGFromMem(picture_obj11930_PNG_H, sizeof(picture_obj11930_PNG_H));
HeadPortrait[12030] = createTexturePNGFromMem(picture_obj12030_PNG_H, sizeof(picture_obj12030_PNG_H));
HeadPortrait[12130] = createTexturePNGFromMem(picture_obj12130_PNG_H, sizeof(picture_obj12130_PNG_H));
HeadPortrait[12330] = createTexturePNGFromMem(picture_obj12330_PNG_H, sizeof(picture_obj12330_PNG_H));
HeadPortrait[12430] = createTexturePNGFromMem(picture_obj12430_PNG_H, sizeof(picture_obj12430_PNG_H));
HeadPortrait[12530] = createTexturePNGFromMem(picture_obj12530_PNG_H, sizeof(picture_obj12530_PNG_H));
HeadPortrait[12630] = createTexturePNGFromMem(picture_obj12630_PNG_H, sizeof(picture_obj12630_PNG_H));
HeadPortrait[12730] = createTexturePNGFromMem(picture_obj12730_PNG_H, sizeof(picture_obj12730_PNG_H));
HeadPortrait[12830] = createTexturePNGFromMem(picture_obj12830_PNG_H, sizeof(picture_obj12830_PNG_H));
HeadPortrait[12930] = createTexturePNGFromMem(picture_obj12930_PNG_H, sizeof(picture_obj12930_PNG_H));
HeadPortrait[13030] = createTexturePNGFromMem(picture_obj13030_PNG_H, sizeof(picture_obj13030_PNG_H));
HeadPortrait[13130] = createTexturePNGFromMem(picture_obj13130_PNG_H, sizeof(picture_obj13130_PNG_H));
HeadPortrait[13230] = createTexturePNGFromMem(picture_obj13230_PNG_H, sizeof(picture_obj13230_PNG_H));
HeadPortrait[13330] = createTexturePNGFromMem(picture_obj13330_PNG_H, sizeof(picture_obj13330_PNG_H));
HeadPortrait[13430] = createTexturePNGFromMem(picture_obj13430_PNG_H, sizeof(picture_obj13430_PNG_H));
HeadPortrait[13530] = createTexturePNGFromMem(picture_obj13530_PNG_H, sizeof(picture_obj13530_PNG_H));
HeadPortrait[13630] = createTexturePNGFromMem(picture_obj13630_PNG_H, sizeof(picture_obj13630_PNG_H));
HeadPortrait[13730] = createTexturePNGFromMem(picture_obj13730_PNG_H, sizeof(picture_obj13730_PNG_H));
HeadPortrait[13930] = createTexturePNGFromMem(picture_obj13930_PNG_H, sizeof(picture_obj13930_PNG_H));
HeadPortrait[14030] = createTexturePNGFromMem(picture_obj14030_PNG_H, sizeof(picture_obj14030_PNG_H));
HeadPortrait[14130] = createTexturePNGFromMem(picture_obj14130_PNG_H, sizeof(picture_obj14130_PNG_H));
HeadPortrait[14230] = createTexturePNGFromMem(picture_obj14230_PNG_H, sizeof(picture_obj14230_PNG_H));
HeadPortrait[14430] = createTexturePNGFromMem(picture_obj14430_PNG_H, sizeof(picture_obj14430_PNG_H));
HeadPortrait[14630] = createTexturePNGFromMem(picture_obj14630_PNG_H, sizeof(picture_obj14630_PNG_H));
HeadPortrait[14830] = createTexturePNGFromMem(picture_obj14830_PNG_H, sizeof(picture_obj14830_PNG_H));
HeadPortrait[14930] = createTexturePNGFromMem(picture_obj14930_PNG_H, sizeof(picture_obj14930_PNG_H));
HeadPortrait[15030] = createTexturePNGFromMem(picture_obj15030_PNG_H, sizeof(picture_obj15030_PNG_H));
HeadPortrait[15230] = createTexturePNGFromMem(picture_obj15230_PNG_H, sizeof(picture_obj15230_PNG_H));
HeadPortrait[15330] = createTexturePNGFromMem(picture_obj15330_PNG_H, sizeof(picture_obj15330_PNG_H));
HeadPortrait[15430] = createTexturePNGFromMem(picture_obj15430_PNG_H, sizeof(picture_obj15430_PNG_H));
HeadPortrait[15530] = createTexturePNGFromMem(picture_obj15530_PNG_H, sizeof(picture_obj15530_PNG_H));
HeadPortrait[15630] = createTexturePNGFromMem(picture_obj15630_PNG_H, sizeof(picture_obj15630_PNG_H));
HeadPortrait[15730] = createTexturePNGFromMem(picture_obj15730_PNG_H, sizeof(picture_obj15730_PNG_H));
HeadPortrait[15930] = createTexturePNGFromMem(picture_obj15930_PNG_H, sizeof(picture_obj15930_PNG_H));
HeadPortrait[16230] = createTexturePNGFromMem(picture_obj16230_PNG_H, sizeof(picture_obj16230_PNG_H));
HeadPortrait[16330] = createTexturePNGFromMem(picture_obj16330_PNG_H, sizeof(picture_obj16330_PNG_H));
HeadPortrait[16630] = createTexturePNGFromMem(picture_obj16630_PNG_H, sizeof(picture_obj16630_PNG_H));
HeadPortrait[16730] = createTexturePNGFromMem(picture_obj16730_PNG_H, sizeof(picture_obj16730_PNG_H));
HeadPortrait[16830] = createTexturePNGFromMem(picture_obj16830_PNG_H, sizeof(picture_obj16830_PNG_H));
HeadPortrait[16930] = createTexturePNGFromMem(picture_obj16930_PNG_H, sizeof(picture_obj16930_PNG_H));
HeadPortrait[17030] = createTexturePNGFromMem(picture_obj17030_PNG_H, sizeof(picture_obj17030_PNG_H));
HeadPortrait[17130] = createTexturePNGFromMem(picture_obj17130_PNG_H, sizeof(picture_obj17130_PNG_H));
HeadPortrait[17330] = createTexturePNGFromMem(picture_obj17330_PNG_H, sizeof(picture_obj17330_PNG_H));
HeadPortrait[17430] = createTexturePNGFromMem(picture_obj17430_PNG_H, sizeof(picture_obj17430_PNG_H));
HeadPortrait[17530] = createTexturePNGFromMem(picture_obj17530_PNG_H, sizeof(picture_obj17530_PNG_H));
HeadPortrait[17630] = createTexturePNGFromMem(picture_obj17630_PNG_H, sizeof(picture_obj17630_PNG_H));
HeadPortrait[17730] = createTexturePNGFromMem(picture_obj17730_PNG_H, sizeof(picture_obj17730_PNG_H));
HeadPortrait[17830] = createTexturePNGFromMem(picture_obj17830_PNG_H, sizeof(picture_obj17830_PNG_H));
HeadPortrait[17930] = createTexturePNGFromMem(picture_obj17930_PNG_H, sizeof(picture_obj17930_PNG_H));
HeadPortrait[18030] = createTexturePNGFromMem(picture_obj18030_PNG_H, sizeof(picture_obj18030_PNG_H));
HeadPortrait[18230] = createTexturePNGFromMem(picture_obj18230_PNG_H, sizeof(picture_obj18230_PNG_H));
HeadPortrait[18330] = createTexturePNGFromMem(picture_obj18330_PNG_H, sizeof(picture_obj18330_PNG_H));
HeadPortrait[18430] = createTexturePNGFromMem(picture_obj18430_PNG_H, sizeof(picture_obj18430_PNG_H));
HeadPortrait[18630] = createTexturePNGFromMem(picture_obj18630_PNG_H, sizeof(picture_obj18630_PNG_H));
HeadPortrait[18730] = createTexturePNGFromMem(picture_obj18730_PNG_H, sizeof(picture_obj18730_PNG_H));
HeadPortrait[18930] = createTexturePNGFromMem(picture_obj18930_PNG_H, sizeof(picture_obj18930_PNG_H));
HeadPortrait[19030] = createTexturePNGFromMem(picture_obj19030_PNG_H, sizeof(picture_obj19030_PNG_H));
HeadPortrait[19130] = createTexturePNGFromMem(picture_obj19130_PNG_H, sizeof(picture_obj19130_PNG_H));
HeadPortrait[19230] = createTexturePNGFromMem(picture_obj19230_PNG_H, sizeof(picture_obj19230_PNG_H));
HeadPortrait[19330] = createTexturePNGFromMem(picture_obj19330_PNG_H, sizeof(picture_obj19330_PNG_H));
HeadPortrait[19430] = createTexturePNGFromMem(picture_obj19430_PNG_H, sizeof(picture_obj19430_PNG_H));
HeadPortrait[19530] = createTexturePNGFromMem(picture_obj19530_PNG_H, sizeof(picture_obj19530_PNG_H));
HeadPortrait[19630] = createTexturePNGFromMem(picture_obj19630_PNG_H, sizeof(picture_obj19630_PNG_H));
HeadPortrait[19730] = createTexturePNGFromMem(picture_obj19730_PNG_H, sizeof(picture_obj19730_PNG_H));
HeadPortrait[19830] = createTexturePNGFromMem(picture_obj19830_PNG_H, sizeof(picture_obj19830_PNG_H));
HeadPortrait[19930] = createTexturePNGFromMem(picture_obj19930_PNG_H, sizeof(picture_obj19930_PNG_H));
HeadPortrait[31230] = createTexturePNGFromMem(picture_obj31230_PNG_H, sizeof(picture_obj31230_PNG_H));
HeadPortrait[50130] = createTexturePNGFromMem(picture_obj50130_PNG_H, sizeof(picture_obj50130_PNG_H));
HeadPortrait[50230] = createTexturePNGFromMem(picture_obj50230_PNG_H, sizeof(picture_obj50230_PNG_H));
HeadPortrait[50330] = createTexturePNGFromMem(picture_obj50330_PNG_H, sizeof(picture_obj50330_PNG_H));
HeadPortrait[50430] = createTexturePNGFromMem(picture_obj50430_PNG_H, sizeof(picture_obj50430_PNG_H));
HeadPortrait[50530] = createTexturePNGFromMem(picture_obj50530_PNG_H, sizeof(picture_obj50530_PNG_H));
HeadPortrait[50630] = createTexturePNGFromMem(picture_obj50630_PNG_H, sizeof(picture_obj50630_PNG_H));
HeadPortrait[50730] = createTexturePNGFromMem(picture_obj50730_PNG_H, sizeof(picture_obj50730_PNG_H));
HeadPortrait[50830] = createTexturePNGFromMem(picture_obj50830_PNG_H, sizeof(picture_obj50830_PNG_H));
HeadPortrait[50930] = createTexturePNGFromMem(picture_obj50930_PNG_H, sizeof(picture_obj50930_PNG_H));
HeadPortrait[51030] = createTexturePNGFromMem(picture_obj51030_PNG_H, sizeof(picture_obj51030_PNG_H));
HeadPortrait[51130] = createTexturePNGFromMem(picture_obj51130_PNG_H, sizeof(picture_obj51130_PNG_H));
HeadPortrait[51330] = createTexturePNGFromMem(picture_obj51330_PNG_H, sizeof(picture_obj51330_PNG_H));
HeadPortrait[51430] = createTexturePNGFromMem(picture_obj51430_PNG_H, sizeof(picture_obj51430_PNG_H));
HeadPortrait[51530] = createTexturePNGFromMem(picture_obj51530_PNG_H, sizeof(picture_obj51530_PNG_H));
HeadPortrait[51730] = createTexturePNGFromMem(picture_obj51730_PNG_H, sizeof(picture_obj51730_PNG_H));
HeadPortrait[51830] = createTexturePNGFromMem(picture_obj51830_PNG_H, sizeof(picture_obj51830_PNG_H));
HeadPortrait[51930] = createTexturePNGFromMem(picture_obj51930_PNG_H, sizeof(picture_obj51930_PNG_H));
HeadPortrait[52130] = createTexturePNGFromMem(picture_obj52130_PNG_H, sizeof(picture_obj52130_PNG_H));
HeadPortrait[52230] = createTexturePNGFromMem(picture_obj52230_PNG_H, sizeof(picture_obj52230_PNG_H));
HeadPortrait[52330] = createTexturePNGFromMem(picture_obj52330_PNG_H, sizeof(picture_obj52330_PNG_H));
HeadPortrait[52430] = createTexturePNGFromMem(picture_obj52430_PNG_H, sizeof(picture_obj52430_PNG_H));
HeadPortrait[52530] = createTexturePNGFromMem(picture_obj52530_PNG_H, sizeof(picture_obj52530_PNG_H));
HeadPortrait[52730] = createTexturePNGFromMem(picture_obj52730_PNG_H, sizeof(picture_obj52730_PNG_H));
HeadPortrait[52830] = createTexturePNGFromMem(picture_obj52830_PNG_H, sizeof(picture_obj52830_PNG_H));
HeadPortrait[52930] = createTexturePNGFromMem(picture_obj52930_PNG_H, sizeof(picture_obj52930_PNG_H));
HeadPortrait[53130] = createTexturePNGFromMem(picture_obj53130_PNG_H, sizeof(picture_obj53130_PNG_H));
HeadPortrait[53330] = createTexturePNGFromMem(picture_obj53330_PNG_H, sizeof(picture_obj53330_PNG_H));
HeadPortrait[53430] = createTexturePNGFromMem(picture_obj53430_PNG_H, sizeof(picture_obj53430_PNG_H));
HeadPortrait[53630] = createTexturePNGFromMem(picture_obj53630_PNG_H, sizeof(picture_obj53630_PNG_H));
HeadPortrait[53730] = createTexturePNGFromMem(picture_obj53730_PNG_H, sizeof(picture_obj53730_PNG_H));
HeadPortrait[53830] = createTexturePNGFromMem(picture_obj53830_PNG_H, sizeof(picture_obj53830_PNG_H));
HeadPortrait[54030] = createTexturePNGFromMem(picture_obj54030_PNG_H, sizeof(picture_obj54030_PNG_H));
HeadPortrait[54230] = createTexturePNGFromMem(picture_obj54230_PNG_H, sizeof(picture_obj54230_PNG_H));
HeadPortrait[54430] = createTexturePNGFromMem(picture_obj54430_PNG_H, sizeof(picture_obj54430_PNG_H));
HeadPortrait[54530] = createTexturePNGFromMem(picture_obj54530_PNG_H, sizeof(picture_obj54530_PNG_H));
HeadPortrait[54830] = createTexturePNGFromMem(picture_obj54830_PNG_H, sizeof(picture_obj54830_PNG_H));
HeadPortrait[56330] = createTexturePNGFromMem(picture_obj56330_PNG_H, sizeof(picture_obj56330_PNG_H));
HeadPortrait[56430] = createTexturePNGFromMem(picture_obj56430_PNG_H, sizeof(picture_obj56430_PNG_H));
HeadPortrait[58130] = createTexturePNGFromMem(picture_obj62030_PNG_H, sizeof(picture_obj62030_PNG_H));
HeadPortrait[58230] = createTexturePNGFromMem(picture_obj58230_PNG_H, sizeof(picture_obj58230_PNG_H));
HeadPortrait[62030] = createTexturePNGFromMem(picture_obj62030_PNG_H, sizeof(picture_obj62030_PNG_H));


HeadPortrait[10520] = createTexturePNGFromMem(picture_obj10520_PNG_H, sizeof(picture_obj10520_PNG_H));
HeadPortrait[10620] = createTexturePNGFromMem(picture_obj10620_PNG_H, sizeof(picture_obj10620_PNG_H));
HeadPortrait[10720] = createTexturePNGFromMem(picture_obj10720_PNG_H, sizeof(picture_obj10720_PNG_H));
HeadPortrait[10820] = createTexturePNGFromMem(picture_obj10820_PNG_H, sizeof(picture_obj10820_PNG_H));
HeadPortrait[10920] = createTexturePNGFromMem(picture_obj10920_PNG_H, sizeof(picture_obj10920_PNG_H));
HeadPortrait[11020] = createTexturePNGFromMem(picture_obj11020_PNG_H, sizeof(picture_obj11020_PNG_H));
HeadPortrait[11120] = createTexturePNGFromMem(picture_obj11120_PNG_H, sizeof(picture_obj11120_PNG_H));
HeadPortrait[11220] = createTexturePNGFromMem(picture_obj11220_PNG_H, sizeof(picture_obj11220_PNG_H));
HeadPortrait[11320] = createTexturePNGFromMem(picture_obj11320_PNG_H, sizeof(picture_obj11320_PNG_H));
HeadPortrait[11420] = createTexturePNGFromMem(picture_obj11420_PNG_H, sizeof(picture_obj11420_PNG_H));
HeadPortrait[11520] = createTexturePNGFromMem(picture_obj11520_PNG_H, sizeof(picture_obj11520_PNG_H));
HeadPortrait[11620] = createTexturePNGFromMem(picture_obj11620_PNG_H, sizeof(picture_obj11620_PNG_H));
HeadPortrait[11720] = createTexturePNGFromMem(picture_obj11720_PNG_H, sizeof(picture_obj11720_PNG_H));
HeadPortrait[11820] = createTexturePNGFromMem(picture_obj11820_PNG_H, sizeof(picture_obj11820_PNG_H));
HeadPortrait[11920] = createTexturePNGFromMem(picture_obj11920_PNG_H, sizeof(picture_obj11920_PNG_H));
HeadPortrait[12020] = createTexturePNGFromMem(picture_obj12020_PNG_H, sizeof(picture_obj12020_PNG_H));
HeadPortrait[12120] = createTexturePNGFromMem(picture_obj12120_PNG_H, sizeof(picture_obj12120_PNG_H));
HeadPortrait[12320] = createTexturePNGFromMem(picture_obj12320_PNG_H, sizeof(picture_obj12320_PNG_H));
HeadPortrait[12420] = createTexturePNGFromMem(picture_obj12420_PNG_H, sizeof(picture_obj12420_PNG_H));
HeadPortrait[12520] = createTexturePNGFromMem(picture_obj12520_PNG_H, sizeof(picture_obj12520_PNG_H));
HeadPortrait[12620] = createTexturePNGFromMem(picture_obj12620_PNG_H, sizeof(picture_obj12620_PNG_H));
HeadPortrait[12720] = createTexturePNGFromMem(picture_obj12720_PNG_H, sizeof(picture_obj12720_PNG_H));
HeadPortrait[12820] = createTexturePNGFromMem(picture_obj12820_PNG_H, sizeof(picture_obj12820_PNG_H));
HeadPortrait[12920] = createTexturePNGFromMem(picture_obj12920_PNG_H, sizeof(picture_obj12920_PNG_H));
HeadPortrait[13020] = createTexturePNGFromMem(picture_obj13020_PNG_H, sizeof(picture_obj13020_PNG_H));
HeadPortrait[13120] = createTexturePNGFromMem(picture_obj13120_PNG_H, sizeof(picture_obj13120_PNG_H));
HeadPortrait[13220] = createTexturePNGFromMem(picture_obj13220_PNG_H, sizeof(picture_obj13220_PNG_H));
HeadPortrait[13320] = createTexturePNGFromMem(picture_obj13320_PNG_H, sizeof(picture_obj13320_PNG_H));
HeadPortrait[13420] = createTexturePNGFromMem(picture_obj13420_PNG_H, sizeof(picture_obj13420_PNG_H));
HeadPortrait[13520] = createTexturePNGFromMem(picture_obj13520_PNG_H, sizeof(picture_obj13520_PNG_H));
HeadPortrait[13620] = createTexturePNGFromMem(picture_obj13620_PNG_H, sizeof(picture_obj13620_PNG_H));
HeadPortrait[13720] = createTexturePNGFromMem(picture_obj13720_PNG_H, sizeof(picture_obj13720_PNG_H));
HeadPortrait[13920] = createTexturePNGFromMem(picture_obj13920_PNG_H, sizeof(picture_obj13920_PNG_H));
HeadPortrait[14020] = createTexturePNGFromMem(picture_obj14020_PNG_H, sizeof(picture_obj14020_PNG_H));
HeadPortrait[14120] = createTexturePNGFromMem(picture_obj14120_PNG_H, sizeof(picture_obj14120_PNG_H));
HeadPortrait[14220] = createTexturePNGFromMem(picture_obj14220_PNG_H, sizeof(picture_obj14220_PNG_H));
HeadPortrait[14420] = createTexturePNGFromMem(picture_obj14420_PNG_H, sizeof(picture_obj14420_PNG_H));
HeadPortrait[14620] = createTexturePNGFromMem(picture_obj14620_PNG_H, sizeof(picture_obj14620_PNG_H));
HeadPortrait[14820] = createTexturePNGFromMem(picture_obj14820_PNG_H, sizeof(picture_obj14820_PNG_H));
HeadPortrait[14920] = createTexturePNGFromMem(picture_obj14920_PNG_H, sizeof(picture_obj14920_PNG_H));
HeadPortrait[15020] = createTexturePNGFromMem(picture_obj15020_PNG_H, sizeof(picture_obj15020_PNG_H));
HeadPortrait[15220] = createTexturePNGFromMem(picture_obj15220_PNG_H, sizeof(picture_obj15220_PNG_H));
HeadPortrait[15320] = createTexturePNGFromMem(picture_obj15320_PNG_H, sizeof(picture_obj15320_PNG_H));
HeadPortrait[15420] = createTexturePNGFromMem(picture_obj15420_PNG_H, sizeof(picture_obj15420_PNG_H));
HeadPortrait[15520] = createTexturePNGFromMem(picture_obj15520_PNG_H, sizeof(picture_obj15520_PNG_H));
HeadPortrait[15620] = createTexturePNGFromMem(picture_obj15620_PNG_H, sizeof(picture_obj15620_PNG_H));
HeadPortrait[15720] = createTexturePNGFromMem(picture_obj15720_PNG_H, sizeof(picture_obj15720_PNG_H));
HeadPortrait[15920] = createTexturePNGFromMem(picture_obj15920_PNG_H, sizeof(picture_obj15920_PNG_H));
HeadPortrait[16220] = createTexturePNGFromMem(picture_obj16220_PNG_H, sizeof(picture_obj16220_PNG_H));
HeadPortrait[16320] = createTexturePNGFromMem(picture_obj16320_PNG_H, sizeof(picture_obj16320_PNG_H));
HeadPortrait[16620] = createTexturePNGFromMem(picture_obj16620_PNG_H, sizeof(picture_obj16620_PNG_H));
HeadPortrait[16720] = createTexturePNGFromMem(picture_obj16720_PNG_H, sizeof(picture_obj16720_PNG_H));
HeadPortrait[16820] = createTexturePNGFromMem(picture_obj16820_PNG_H, sizeof(picture_obj16820_PNG_H));
HeadPortrait[16920] = createTexturePNGFromMem(picture_obj16920_PNG_H, sizeof(picture_obj16920_PNG_H));
HeadPortrait[17020] = createTexturePNGFromMem(picture_obj17020_PNG_H, sizeof(picture_obj17020_PNG_H));
HeadPortrait[17120] = createTexturePNGFromMem(picture_obj17120_PNG_H, sizeof(picture_obj17120_PNG_H));
HeadPortrait[17320] = createTexturePNGFromMem(picture_obj17320_PNG_H, sizeof(picture_obj17320_PNG_H));
HeadPortrait[17420] = createTexturePNGFromMem(picture_obj17420_PNG_H, sizeof(picture_obj17420_PNG_H));
HeadPortrait[17520] = createTexturePNGFromMem(picture_obj17520_PNG_H, sizeof(picture_obj17520_PNG_H));
HeadPortrait[17620] = createTexturePNGFromMem(picture_obj17620_PNG_H, sizeof(picture_obj17620_PNG_H));
HeadPortrait[17720] = createTexturePNGFromMem(picture_obj17720_PNG_H, sizeof(picture_obj17720_PNG_H));
HeadPortrait[17820] = createTexturePNGFromMem(picture_obj17820_PNG_H, sizeof(picture_obj17820_PNG_H));
HeadPortrait[17920] = createTexturePNGFromMem(picture_obj17920_PNG_H, sizeof(picture_obj17920_PNG_H));
HeadPortrait[18020] = createTexturePNGFromMem(picture_obj18020_PNG_H, sizeof(picture_obj18020_PNG_H));
HeadPortrait[18220] = createTexturePNGFromMem(picture_obj18220_PNG_H, sizeof(picture_obj18220_PNG_H));
HeadPortrait[18320] = createTexturePNGFromMem(picture_obj18320_PNG_H, sizeof(picture_obj18320_PNG_H));
HeadPortrait[18420] = createTexturePNGFromMem(picture_obj18420_PNG_H, sizeof(picture_obj18420_PNG_H));
HeadPortrait[18620] = createTexturePNGFromMem(picture_obj18620_PNG_H, sizeof(picture_obj18620_PNG_H));
HeadPortrait[18720] = createTexturePNGFromMem(picture_obj18720_PNG_H, sizeof(picture_obj18720_PNG_H));
HeadPortrait[18920] = createTexturePNGFromMem(picture_obj18920_PNG_H, sizeof(picture_obj18920_PNG_H));
HeadPortrait[19020] = createTexturePNGFromMem(picture_obj19020_PNG_H, sizeof(picture_obj19020_PNG_H));
HeadPortrait[19120] = createTexturePNGFromMem(picture_obj19120_PNG_H, sizeof(picture_obj19120_PNG_H));
HeadPortrait[19220] = createTexturePNGFromMem(picture_obj19220_PNG_H, sizeof(picture_obj19220_PNG_H));
HeadPortrait[19320] = createTexturePNGFromMem(picture_obj19320_PNG_H, sizeof(picture_obj19320_PNG_H));
HeadPortrait[19420] = createTexturePNGFromMem(picture_obj19420_PNG_H, sizeof(picture_obj19420_PNG_H));
HeadPortrait[19520] = createTexturePNGFromMem(picture_obj19520_PNG_H, sizeof(picture_obj19520_PNG_H));
HeadPortrait[19620] = createTexturePNGFromMem(picture_obj19620_PNG_H, sizeof(picture_obj19620_PNG_H));
HeadPortrait[19720] = createTexturePNGFromMem(picture_obj19720_PNG_H, sizeof(picture_obj19720_PNG_H));
HeadPortrait[19820] = createTexturePNGFromMem(picture_obj19820_PNG_H, sizeof(picture_obj19820_PNG_H));
HeadPortrait[19920] = createTexturePNGFromMem(picture_obj19920_PNG_H, sizeof(picture_obj19920_PNG_H));
HeadPortrait[31220] = createTexturePNGFromMem(picture_obj31220_PNG_H, sizeof(picture_obj31220_PNG_H));
HeadPortrait[50120] = createTexturePNGFromMem(picture_obj50120_PNG_H, sizeof(picture_obj50120_PNG_H));
HeadPortrait[50220] = createTexturePNGFromMem(picture_obj50220_PNG_H, sizeof(picture_obj50220_PNG_H));
HeadPortrait[50320] = createTexturePNGFromMem(picture_obj50320_PNG_H, sizeof(picture_obj50320_PNG_H));
HeadPortrait[50420] = createTexturePNGFromMem(picture_obj50420_PNG_H, sizeof(picture_obj50420_PNG_H));
HeadPortrait[50520] = createTexturePNGFromMem(picture_obj50520_PNG_H, sizeof(picture_obj50520_PNG_H));
HeadPortrait[50620] = createTexturePNGFromMem(picture_obj50620_PNG_H, sizeof(picture_obj50620_PNG_H));
HeadPortrait[50720] = createTexturePNGFromMem(picture_obj50720_PNG_H, sizeof(picture_obj50720_PNG_H));
HeadPortrait[50820] = createTexturePNGFromMem(picture_obj50820_PNG_H, sizeof(picture_obj50820_PNG_H));
HeadPortrait[50920] = createTexturePNGFromMem(picture_obj50920_PNG_H, sizeof(picture_obj50920_PNG_H));
HeadPortrait[51020] = createTexturePNGFromMem(picture_obj51020_PNG_H, sizeof(picture_obj51020_PNG_H));
HeadPortrait[51120] = createTexturePNGFromMem(picture_obj51120_PNG_H, sizeof(picture_obj51120_PNG_H));
HeadPortrait[51320] = createTexturePNGFromMem(picture_obj51320_PNG_H, sizeof(picture_obj51320_PNG_H));
HeadPortrait[51420] = createTexturePNGFromMem(picture_obj51420_PNG_H, sizeof(picture_obj51420_PNG_H));
HeadPortrait[51520] = createTexturePNGFromMem(picture_obj51520_PNG_H, sizeof(picture_obj51520_PNG_H));
HeadPortrait[51720] = createTexturePNGFromMem(picture_obj51720_PNG_H, sizeof(picture_obj51720_PNG_H));
HeadPortrait[51820] = createTexturePNGFromMem(picture_obj51820_PNG_H, sizeof(picture_obj51820_PNG_H));
HeadPortrait[51920] = createTexturePNGFromMem(picture_obj51920_PNG_H, sizeof(picture_obj51920_PNG_H));
HeadPortrait[52120] = createTexturePNGFromMem(picture_obj52120_PNG_H, sizeof(picture_obj52120_PNG_H));
HeadPortrait[52220] = createTexturePNGFromMem(picture_obj52220_PNG_H, sizeof(picture_obj52220_PNG_H));
HeadPortrait[52320] = createTexturePNGFromMem(picture_obj52320_PNG_H, sizeof(picture_obj52320_PNG_H));
HeadPortrait[52420] = createTexturePNGFromMem(picture_obj52420_PNG_H, sizeof(picture_obj52420_PNG_H));
HeadPortrait[52520] = createTexturePNGFromMem(picture_obj52520_PNG_H, sizeof(picture_obj52520_PNG_H));
HeadPortrait[52720] = createTexturePNGFromMem(picture_obj52720_PNG_H, sizeof(picture_obj52720_PNG_H));
HeadPortrait[52820] = createTexturePNGFromMem(picture_obj52820_PNG_H, sizeof(picture_obj52820_PNG_H));
HeadPortrait[52920] = createTexturePNGFromMem(picture_obj52920_PNG_H, sizeof(picture_obj52920_PNG_H));
HeadPortrait[53120] = createTexturePNGFromMem(picture_obj53120_PNG_H, sizeof(picture_obj53120_PNG_H));
HeadPortrait[53320] = createTexturePNGFromMem(picture_obj53320_PNG_H, sizeof(picture_obj53320_PNG_H));
HeadPortrait[53420] = createTexturePNGFromMem(picture_obj53420_PNG_H, sizeof(picture_obj53420_PNG_H));
HeadPortrait[53620] = createTexturePNGFromMem(picture_obj53620_PNG_H, sizeof(picture_obj53620_PNG_H));
HeadPortrait[53720] = createTexturePNGFromMem(picture_obj53720_PNG_H, sizeof(picture_obj53720_PNG_H));
HeadPortrait[53820] = createTexturePNGFromMem(picture_obj53820_PNG_H, sizeof(picture_obj53820_PNG_H));
HeadPortrait[54020] = createTexturePNGFromMem(picture_obj54020_PNG_H, sizeof(picture_obj54020_PNG_H));
HeadPortrait[54220] = createTexturePNGFromMem(picture_obj54220_PNG_H, sizeof(picture_obj54220_PNG_H));
HeadPortrait[54420] = createTexturePNGFromMem(picture_obj54420_PNG_H, sizeof(picture_obj54420_PNG_H));
HeadPortrait[54520] = createTexturePNGFromMem(picture_obj54520_PNG_H, sizeof(picture_obj54520_PNG_H));
HeadPortrait[54820] = createTexturePNGFromMem(picture_obj54820_PNG_H, sizeof(picture_obj54820_PNG_H));
HeadPortrait[56320] = createTexturePNGFromMem(picture_obj56320_PNG_H, sizeof(picture_obj56320_PNG_H));
HeadPortrait[56420] = createTexturePNGFromMem(picture_obj56420_PNG_H, sizeof(picture_obj56420_PNG_H));
HeadPortrait[58120] = createTexturePNGFromMem(picture_obj62020_PNG_H, sizeof(picture_obj62020_PNG_H));
HeadPortrait[58220] = createTexturePNGFromMem(picture_obj58220_PNG_H, sizeof(picture_obj58220_PNG_H));
HeadPortrait[62020] = createTexturePNGFromMem(picture_obj62020_PNG_H, sizeof(picture_obj62020_PNG_H));

HeadPortrait[10510] = createTexturePNGFromMem(picture_obj10510_PNG_H, sizeof(picture_obj10510_PNG_H));
HeadPortrait[10610] = createTexturePNGFromMem(picture_obj10610_PNG_H, sizeof(picture_obj10610_PNG_H));
HeadPortrait[10710] = createTexturePNGFromMem(picture_obj10710_PNG_H, sizeof(picture_obj10710_PNG_H));
HeadPortrait[10810] = createTexturePNGFromMem(picture_obj10810_PNG_H, sizeof(picture_obj10810_PNG_H));
HeadPortrait[10910] = createTexturePNGFromMem(picture_obj10910_PNG_H, sizeof(picture_obj10910_PNG_H));
HeadPortrait[11010] = createTexturePNGFromMem(picture_obj11010_PNG_H, sizeof(picture_obj11010_PNG_H));
HeadPortrait[11110] = createTexturePNGFromMem(picture_obj11110_PNG_H, sizeof(picture_obj11110_PNG_H));
HeadPortrait[11210] = createTexturePNGFromMem(picture_obj11210_PNG_H, sizeof(picture_obj11210_PNG_H));
HeadPortrait[11310] = createTexturePNGFromMem(picture_obj11310_PNG_H, sizeof(picture_obj11310_PNG_H));
HeadPortrait[11410] = createTexturePNGFromMem(picture_obj11410_PNG_H, sizeof(picture_obj11410_PNG_H));
HeadPortrait[11510] = createTexturePNGFromMem(picture_obj11510_PNG_H, sizeof(picture_obj11510_PNG_H));
HeadPortrait[11610] = createTexturePNGFromMem(picture_obj11610_PNG_H, sizeof(picture_obj11610_PNG_H));
HeadPortrait[11710] = createTexturePNGFromMem(picture_obj11710_PNG_H, sizeof(picture_obj11710_PNG_H));
HeadPortrait[11810] = createTexturePNGFromMem(picture_obj11810_PNG_H, sizeof(picture_obj11810_PNG_H));
HeadPortrait[11910] = createTexturePNGFromMem(picture_obj11910_PNG_H, sizeof(picture_obj11910_PNG_H));
HeadPortrait[12010] = createTexturePNGFromMem(picture_obj12010_PNG_H, sizeof(picture_obj12010_PNG_H));
HeadPortrait[12110] = createTexturePNGFromMem(picture_obj12110_PNG_H, sizeof(picture_obj12110_PNG_H));
HeadPortrait[12310] = createTexturePNGFromMem(picture_obj12310_PNG_H, sizeof(picture_obj12310_PNG_H));
HeadPortrait[12410] = createTexturePNGFromMem(picture_obj12410_PNG_H, sizeof(picture_obj12410_PNG_H));
HeadPortrait[12510] = createTexturePNGFromMem(picture_obj12510_PNG_H, sizeof(picture_obj12510_PNG_H));
HeadPortrait[12610] = createTexturePNGFromMem(picture_obj12610_PNG_H, sizeof(picture_obj12610_PNG_H));
HeadPortrait[12710] = createTexturePNGFromMem(picture_obj12710_PNG_H, sizeof(picture_obj12710_PNG_H));
HeadPortrait[12810] = createTexturePNGFromMem(picture_obj12810_PNG_H, sizeof(picture_obj12810_PNG_H));
HeadPortrait[12910] = createTexturePNGFromMem(picture_obj12910_PNG_H, sizeof(picture_obj12910_PNG_H));
HeadPortrait[13010] = createTexturePNGFromMem(picture_obj13010_PNG_H, sizeof(picture_obj13010_PNG_H));
HeadPortrait[13110] = createTexturePNGFromMem(picture_obj13110_PNG_H, sizeof(picture_obj13110_PNG_H));
HeadPortrait[13210] = createTexturePNGFromMem(picture_obj13210_PNG_H, sizeof(picture_obj13210_PNG_H));
HeadPortrait[13310] = createTexturePNGFromMem(picture_obj13310_PNG_H, sizeof(picture_obj13310_PNG_H));
HeadPortrait[13410] = createTexturePNGFromMem(picture_obj13410_PNG_H, sizeof(picture_obj13410_PNG_H));
HeadPortrait[13510] = createTexturePNGFromMem(picture_obj13510_PNG_H, sizeof(picture_obj13510_PNG_H));
HeadPortrait[13610] = createTexturePNGFromMem(picture_obj13610_PNG_H, sizeof(picture_obj13610_PNG_H));
HeadPortrait[13710] = createTexturePNGFromMem(picture_obj13710_PNG_H, sizeof(picture_obj13710_PNG_H));
HeadPortrait[13910] = createTexturePNGFromMem(picture_obj13910_PNG_H, sizeof(picture_obj13910_PNG_H));
HeadPortrait[14010] = createTexturePNGFromMem(picture_obj14010_PNG_H, sizeof(picture_obj14010_PNG_H));
HeadPortrait[14110] = createTexturePNGFromMem(picture_obj14110_PNG_H, sizeof(picture_obj14110_PNG_H));
HeadPortrait[14210] = createTexturePNGFromMem(picture_obj14210_PNG_H, sizeof(picture_obj14210_PNG_H));
HeadPortrait[14410] = createTexturePNGFromMem(picture_obj14410_PNG_H, sizeof(picture_obj14410_PNG_H));
HeadPortrait[14610] = createTexturePNGFromMem(picture_obj14610_PNG_H, sizeof(picture_obj14610_PNG_H));
HeadPortrait[14810] = createTexturePNGFromMem(picture_obj14810_PNG_H, sizeof(picture_obj14810_PNG_H));
HeadPortrait[14910] = createTexturePNGFromMem(picture_obj14910_PNG_H, sizeof(picture_obj14910_PNG_H));
HeadPortrait[15010] = createTexturePNGFromMem(picture_obj15010_PNG_H, sizeof(picture_obj15010_PNG_H));
HeadPortrait[15210] = createTexturePNGFromMem(picture_obj15210_PNG_H, sizeof(picture_obj15210_PNG_H));
HeadPortrait[15310] = createTexturePNGFromMem(picture_obj15310_PNG_H, sizeof(picture_obj15310_PNG_H));
HeadPortrait[15410] = createTexturePNGFromMem(picture_obj15410_PNG_H, sizeof(picture_obj15410_PNG_H));
HeadPortrait[15510] = createTexturePNGFromMem(picture_obj15510_PNG_H, sizeof(picture_obj15510_PNG_H));
HeadPortrait[15610] = createTexturePNGFromMem(picture_obj15610_PNG_H, sizeof(picture_obj15610_PNG_H));
HeadPortrait[15710] = createTexturePNGFromMem(picture_obj15710_PNG_H, sizeof(picture_obj15710_PNG_H));
HeadPortrait[15910] = createTexturePNGFromMem(picture_obj15910_PNG_H, sizeof(picture_obj15910_PNG_H));
HeadPortrait[16210] = createTexturePNGFromMem(picture_obj16210_PNG_H, sizeof(picture_obj16210_PNG_H));
HeadPortrait[16310] = createTexturePNGFromMem(picture_obj16310_PNG_H, sizeof(picture_obj16310_PNG_H));
HeadPortrait[16610] = createTexturePNGFromMem(picture_obj16610_PNG_H, sizeof(picture_obj16610_PNG_H));
HeadPortrait[16710] = createTexturePNGFromMem(picture_obj16710_PNG_H, sizeof(picture_obj16710_PNG_H));
HeadPortrait[16810] = createTexturePNGFromMem(picture_obj16810_PNG_H, sizeof(picture_obj16810_PNG_H));
HeadPortrait[16910] = createTexturePNGFromMem(picture_obj16910_PNG_H, sizeof(picture_obj16910_PNG_H));
HeadPortrait[17010] = createTexturePNGFromMem(picture_obj17010_PNG_H, sizeof(picture_obj17010_PNG_H));
HeadPortrait[17110] = createTexturePNGFromMem(picture_obj17110_PNG_H, sizeof(picture_obj17110_PNG_H));
HeadPortrait[17310] = createTexturePNGFromMem(picture_obj17310_PNG_H, sizeof(picture_obj17310_PNG_H));
HeadPortrait[17410] = createTexturePNGFromMem(picture_obj17410_PNG_H, sizeof(picture_obj17410_PNG_H));
HeadPortrait[17510] = createTexturePNGFromMem(picture_obj17510_PNG_H, sizeof(picture_obj17510_PNG_H));
HeadPortrait[17610] = createTexturePNGFromMem(picture_obj17610_PNG_H, sizeof(picture_obj17610_PNG_H));
HeadPortrait[17710] = createTexturePNGFromMem(picture_obj17710_PNG_H, sizeof(picture_obj17710_PNG_H));
HeadPortrait[17810] = createTexturePNGFromMem(picture_obj17810_PNG_H, sizeof(picture_obj17810_PNG_H));
HeadPortrait[17910] = createTexturePNGFromMem(picture_obj17910_PNG_H, sizeof(picture_obj17910_PNG_H));
HeadPortrait[18010] = createTexturePNGFromMem(picture_obj18010_PNG_H, sizeof(picture_obj18010_PNG_H));
HeadPortrait[18210] = createTexturePNGFromMem(picture_obj18210_PNG_H, sizeof(picture_obj18210_PNG_H));
HeadPortrait[18310] = createTexturePNGFromMem(picture_obj18310_PNG_H, sizeof(picture_obj18310_PNG_H));
HeadPortrait[18410] = createTexturePNGFromMem(picture_obj18410_PNG_H, sizeof(picture_obj18410_PNG_H));
HeadPortrait[18610] = createTexturePNGFromMem(picture_obj18610_PNG_H, sizeof(picture_obj18610_PNG_H));
HeadPortrait[18710] = createTexturePNGFromMem(picture_obj18710_PNG_H, sizeof(picture_obj18710_PNG_H));
HeadPortrait[18910] = createTexturePNGFromMem(picture_obj18910_PNG_H, sizeof(picture_obj18910_PNG_H));
HeadPortrait[19010] = createTexturePNGFromMem(picture_obj19010_PNG_H, sizeof(picture_obj19010_PNG_H));
HeadPortrait[19110] = createTexturePNGFromMem(picture_obj19110_PNG_H, sizeof(picture_obj19110_PNG_H));
HeadPortrait[19210] = createTexturePNGFromMem(picture_obj19210_PNG_H, sizeof(picture_obj19210_PNG_H));
HeadPortrait[19310] = createTexturePNGFromMem(picture_obj19310_PNG_H, sizeof(picture_obj19310_PNG_H));
HeadPortrait[19410] = createTexturePNGFromMem(picture_obj19410_PNG_H, sizeof(picture_obj19410_PNG_H));
HeadPortrait[19510] = createTexturePNGFromMem(picture_obj19510_PNG_H, sizeof(picture_obj19510_PNG_H));
HeadPortrait[19610] = createTexturePNGFromMem(picture_obj19610_PNG_H, sizeof(picture_obj19610_PNG_H));
HeadPortrait[19710] = createTexturePNGFromMem(picture_obj19710_PNG_H, sizeof(picture_obj19710_PNG_H));
HeadPortrait[19810] = createTexturePNGFromMem(picture_obj19810_PNG_H, sizeof(picture_obj19810_PNG_H));
HeadPortrait[19910] = createTexturePNGFromMem(picture_obj19910_PNG_H, sizeof(picture_obj19910_PNG_H));
HeadPortrait[31210] = createTexturePNGFromMem(picture_obj31210_PNG_H, sizeof(picture_obj31210_PNG_H));
HeadPortrait[50110] = createTexturePNGFromMem(picture_obj50110_PNG_H, sizeof(picture_obj50110_PNG_H));
HeadPortrait[50210] = createTexturePNGFromMem(picture_obj50210_PNG_H, sizeof(picture_obj50210_PNG_H));
HeadPortrait[50310] = createTexturePNGFromMem(picture_obj50310_PNG_H, sizeof(picture_obj50310_PNG_H));
HeadPortrait[50410] = createTexturePNGFromMem(picture_obj50410_PNG_H, sizeof(picture_obj50410_PNG_H));
HeadPortrait[50510] = createTexturePNGFromMem(picture_obj50510_PNG_H, sizeof(picture_obj50510_PNG_H));
HeadPortrait[50610] = createTexturePNGFromMem(picture_obj50610_PNG_H, sizeof(picture_obj50610_PNG_H));
HeadPortrait[50710] = createTexturePNGFromMem(picture_obj50710_PNG_H, sizeof(picture_obj50710_PNG_H));
HeadPortrait[50810] = createTexturePNGFromMem(picture_obj50810_PNG_H, sizeof(picture_obj50810_PNG_H));
HeadPortrait[50910] = createTexturePNGFromMem(picture_obj50910_PNG_H, sizeof(picture_obj50910_PNG_H));
HeadPortrait[51010] = createTexturePNGFromMem(picture_obj51010_PNG_H, sizeof(picture_obj51010_PNG_H));
HeadPortrait[51110] = createTexturePNGFromMem(picture_obj51110_PNG_H, sizeof(picture_obj51110_PNG_H));
HeadPortrait[51310] = createTexturePNGFromMem(picture_obj51310_PNG_H, sizeof(picture_obj51310_PNG_H));
HeadPortrait[51410] = createTexturePNGFromMem(picture_obj51410_PNG_H, sizeof(picture_obj51410_PNG_H));
HeadPortrait[51510] = createTexturePNGFromMem(picture_obj51510_PNG_H, sizeof(picture_obj51510_PNG_H));
HeadPortrait[51710] = createTexturePNGFromMem(picture_obj51710_PNG_H, sizeof(picture_obj51710_PNG_H));
HeadPortrait[51810] = createTexturePNGFromMem(picture_obj51810_PNG_H, sizeof(picture_obj51810_PNG_H));
HeadPortrait[51910] = createTexturePNGFromMem(picture_obj51910_PNG_H, sizeof(picture_obj51910_PNG_H));
HeadPortrait[52110] = createTexturePNGFromMem(picture_obj52110_PNG_H, sizeof(picture_obj52110_PNG_H));
HeadPortrait[52210] = createTexturePNGFromMem(picture_obj52210_PNG_H, sizeof(picture_obj52210_PNG_H));
HeadPortrait[52310] = createTexturePNGFromMem(picture_obj52310_PNG_H, sizeof(picture_obj52310_PNG_H));
HeadPortrait[52410] = createTexturePNGFromMem(picture_obj52410_PNG_H, sizeof(picture_obj52410_PNG_H));
HeadPortrait[52510] = createTexturePNGFromMem(picture_obj52510_PNG_H, sizeof(picture_obj52510_PNG_H));
HeadPortrait[52710] = createTexturePNGFromMem(picture_obj52710_PNG_H, sizeof(picture_obj52710_PNG_H));
HeadPortrait[52810] = createTexturePNGFromMem(picture_obj52810_PNG_H, sizeof(picture_obj52810_PNG_H));
HeadPortrait[52910] = createTexturePNGFromMem(picture_obj52910_PNG_H, sizeof(picture_obj52910_PNG_H));
HeadPortrait[53110] = createTexturePNGFromMem(picture_obj53110_PNG_H, sizeof(picture_obj53110_PNG_H));
HeadPortrait[53310] = createTexturePNGFromMem(picture_obj53310_PNG_H, sizeof(picture_obj53310_PNG_H));
HeadPortrait[53410] = createTexturePNGFromMem(picture_obj53410_PNG_H, sizeof(picture_obj53410_PNG_H));
HeadPortrait[53610] = createTexturePNGFromMem(picture_obj53610_PNG_H, sizeof(picture_obj53610_PNG_H));
HeadPortrait[53710] = createTexturePNGFromMem(picture_obj53710_PNG_H, sizeof(picture_obj53710_PNG_H));
HeadPortrait[53810] = createTexturePNGFromMem(picture_obj53810_PNG_H, sizeof(picture_obj53810_PNG_H));
HeadPortrait[54010] = createTexturePNGFromMem(picture_obj54010_PNG_H, sizeof(picture_obj54010_PNG_H));
HeadPortrait[54210] = createTexturePNGFromMem(picture_obj54210_PNG_H, sizeof(picture_obj54210_PNG_H));
HeadPortrait[54410] = createTexturePNGFromMem(picture_obj54410_PNG_H, sizeof(picture_obj54410_PNG_H));
HeadPortrait[54510] = createTexturePNGFromMem(picture_obj54510_PNG_H, sizeof(picture_obj54510_PNG_H));
HeadPortrait[54810] = createTexturePNGFromMem(picture_obj54810_PNG_H, sizeof(picture_obj54810_PNG_H));
HeadPortrait[56310] = createTexturePNGFromMem(picture_obj56310_PNG_H, sizeof(picture_obj56310_PNG_H));
HeadPortrait[56410] = createTexturePNGFromMem(picture_obj56410_PNG_H, sizeof(picture_obj56410_PNG_H));
HeadPortrait[58110] = createTexturePNGFromMem(picture_obj62010_PNG_H, sizeof(picture_obj62010_PNG_H));
HeadPortrait[58210] = createTexturePNGFromMem(picture_obj62010_PNG_H, sizeof(picture_obj62010_PNG_H));
HeadPortrait[62010] = createTexturePNGFromMem(picture_obj62010_PNG_H, sizeof(picture_obj62010_PNG_H));


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
	

	
}


struct 技能图标
{
	TextureInfoa 头像[100000];//一定要大
	
};
技能图标 技能贴图;

void 获取图标(){
	
	Loadpicture_obj2(技能贴图.头像);
	
}

#include "Gerpicture/警告.h"
#include "Gerpicture/视野眼睛.h"

void Loadpicture_obj3(TextureInfoa *HeadPortrait)
{
HeadPortrait[0] = createTexturePNGFromMem(picture_obj0_PNG_H, sizeof(picture_obj0_PNG_H));
HeadPortrait[1] = createTexturePNGFromMem(警告, sizeof(警告));
HeadPortrait[2] = createTexturePNGFromMem(视野眼睛, sizeof(视野眼睛));
}

struct 其他图标
{
	TextureInfoa 图标[10];//一定要大
	
};
其他图标 其他贴图;

void 获取其他图标(){
	
	Loadpicture_obj3(其他贴图.图标);
	
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
	绘制字体描边(22.5,ImVec2(x1 - (textSize1.x / 2), bottom),ImColor(248,248,255),s.c_str());
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
//float ax, ay;
int prex1, prey1;
long a, objarrayaddr, libGameCore1, libil2cpp1, 兵线基址, 人物数组, 野怪数组, 兵线数组;
int 阵营1 = 0, fx1 = 0;
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
    int 分辨率X = 2257;//1220  2846

    int 小地图左右调整 = 12;//我的配置87   -3
    int 小地图上下调整 = 10;//   -4
    int 兵线左右调整 =  15;//我的配置6
    int 兵线上下调整 = -27;//31
    int 野怪左右调整 = 10;//我的配置-6
    int 野怪上下调整 =  18;//-1
    int FPS帧率 = 90;

};
sESPMenu ESPMenu;

   
 
 
     //共享传输变量
    int herealx, herealy;int zyz, hcc;   
    //传输变量  野怪传输
    int ygtime;
    int  buffid;
    int  buffx;
    int  buffy;
    long BUFFtemp;  //临时数组
    int 游戏时间;
    int xxx1, yyy1;
    int bui;
    long bbuff1;
        int bingx;
    int bingy;//兵线共享变量
    
    //共享绘制房间号
void read_line_without_newline(FILE* stream, char* buffer, size_t size) {
    fgets(buffer, size, stream);
    buffer[strcspn(buffer, "\n")] = '\0';
}

    
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
char imei[100] = "";//leixin666
int ret = -1;
int socket_fd;
struct sockaddr_in serveraddr;
char buffer[MAX_BUFFER_SIZE];
char homeBuffer[MAX_BUFFER_SIZE];
int numBytesReceived, homeBytesReceived;
std::string 共享房间ip = "103.112.96.5";//主机  
bool 是否开启共享 = true;
void createSocket() {//重要方法
	srand((unsigned int)time(NULL));  // 初始化随机数种子
    int num = rand() % 1000 + 1;  // 生成 1 到 10000 之间的随机数
    sprintf(imei, "%06d", num);  // 将数字转换为字符串并存储在 imei 中
    printf("\033[32;1m");	// 绿色
    printf("[+] 天理共享网站: http://103.112.96.5:6851/\n");
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("[+] 连接失败\n");
        exit(0);
    }
    if (socket_fd < 0) {
    printf("[+] 连接失败\n");
        exit(0);
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr((char*)共享房间ip.data());
    serveraddr.sin_port = htons(9999);
    ret = connect(socket_fd, (struct sockaddr*)&serveraddr, sizeof(struct sockaddr));
    if (ret < 0) {
    	
    	    for (int i = 0; i < 10; i++) {
        printf("[+] 连接失败\n");
    }
    	
    }
      
}

