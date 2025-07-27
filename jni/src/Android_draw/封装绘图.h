//#include <stb_image.h>
//#include "内存图片/内存图片工具.h"
#include "内存图片/头文件.h"
//#include "内存图片/内存图片工具.h"

//添加图片
//#include <imgui.h>
//#include <stb_image.h>
#include "stb_image.h"
//http://t.me/TearGame
//http://t.me/TearGame
ImTextureID FloatBall,FloatBallmenu,FloatBallyulong;
ImTextureID offButton;
ImTextureID onButton;
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
    ImTextureID image_id = (ImTextureID) (GLuint *) texture;
    return image_id;
}



ImDrawList* draw;
//图片结构体
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



//补充高数初始化

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
	textureInfo.textureId=(ImTextureID)(GLuint *)texture;
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
    textureInfo.textureId =(GLuint *) texture;
    textureInfo.w = w;
    textureInfo.h = h;
    return textureInfo;
}



ImFont* font = nullptr;
void 绘制字体描边(float size,int x, int y, ImVec4 color, const char* str) {
ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x + 1.0, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x - 0.1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y + 1.0), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y - 1.0), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(color), str);
}
void 绘制加粗文本(float size, float x, float y, ImColor color, ImColor color1, const char* str){
ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x-0.8, y-0.8), color1, str);
ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x+0.8, y+0.8), color1, str);
ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x, y), color, str);
}

void Box4Line(ImDrawList *draw, float thicc, int x, int y, int w, int h, int color) {
int iw = w / 4;
int ih = h / 4;
// top
draw->AddRect(ImVec2(x, y),ImVec2(x + iw, y), color, thicc);
draw->AddRect(ImVec2(x + w - iw, y),ImVec2(x + w, y), color, thicc);
draw->AddRect(ImVec2(x, y),ImVec2(x, y + ih), color, thicc);
draw->AddRect(ImVec2(x + w - 1, y),ImVec2(x + w - 1, y + ih), color, thicc);;
// bottom
draw->AddRect(ImVec2(x, y + h),ImVec2(x + iw, y + h), color, thicc);
draw->AddRect(ImVec2(x + w - iw, y + h),ImVec2(x + w, y + h), color, thicc);
draw->AddRect(ImVec2(x, y + h - ih), ImVec2(x, y + h), color, thicc);
draw->AddRect(ImVec2(x + w - 1, y + h - ih), ImVec2(x + w - 1, y + h), color, thicc);
}

// 杂项
ImColor 浅蓝 = ImColor(ImVec4(36/255.f, 249/255.f, 217/255.f, 255/255.f));
ImColor 蓝色 = ImColor(ImVec4(170/255.f, 203/255.f, 244/255.f, 0.95f));
ImColor 白色 = ImColor(ImVec4(255/255.f, 255/255.f, 258/255.f, 0.95f));
ImColor 浅粉 = ImColor(ImVec4(255/255.f, 200/255.f, 250/255.f, 0.95f));
ImColor 黑色 = ImColor(ImVec4(0/255.f, 0/255.f, 0/255.f, 0.7f));
ImColor 半黑 = ImColor(ImVec4(0/255.f, 0/255.f, 0/255.f, 0.18f));
ImColor 血色 = ImColor(ImVec4(0/255.f, 249/255.f, 0/255.f, 0.35f));
ImColor 红色 = ImColor(ImVec4(233/255.f, 55/255.f, 51/255.f, 0.95f));
ImColor 绿色 = ImColor(ImVec4(50/255.f, 222/215.f, 50/255.f, 0.95f));
ImColor 黄色 = ImColor(ImVec4(255/255.f, 255/255.f, 0/255.f, 0.95f));
ImColor 橘黄 = ImColor(ImVec4(255/255.f, 150/255.f, 30/255.f, 0.95f));
ImColor 粉红 = ImColor(ImVec4(220/255.f, 108/255.f, 1202/255.f, 0.95f));
ImColor 紫色 = ImColor(ImVec4(169/255.f, 120/255.f, 223/255.f, 0.95f));
ImColor 空白 = ImColor(ImVec4(1.0/255.f, 1.0/255.f, 1.0/255.f, 0.0f));
ImColor 颜色1;
void DrawStrokeText(int x, int y, ImVec4 color, const char *str) {
ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x + 1, (float) y),
ImGui::ColorConvertFloat4ToU32(
ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x - 0.1f, (float) y),
ImGui::ColorConvertFloat4ToU32(
ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x, (float) y + 1),
ImGui::ColorConvertFloat4ToU32(
ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x, (float) y - 1),
ImGui::ColorConvertFloat4ToU32(
ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
ImGui::GetForegroundDrawList()->AddText(ImVec2((float) x, (float) y),
ImGui::ColorConvertFloat4ToU32(color),str);
}




void 加载图片(){
}

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
HeadPortrait[159] = createTexturePNGFromMem(picture_obj159_PNG_H, sizeof(picture_obj159_PNG_H));
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
HeadPortrait[514] = createTexturePNGFromMem(picture_obj514_PNG_H, sizeof(picture_obj514_PNG_H));
HeadPortrait[515] = createTexturePNGFromMem(picture_obj515_PNG_H, sizeof(picture_obj515_PNG_H));
HeadPortrait[518] = createTexturePNGFromMem(picture_obj518_PNG_H, sizeof(picture_obj518_PNG_H));
HeadPortrait[519] = createTexturePNGFromMem(picture_obj519_PNG_H, sizeof(picture_obj519_PNG_H));
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
HeadPortrait[563] = createTexturePNGFromMem(picture_obj563_PNG_H, sizeof(picture_obj563_PNG_H));
HeadPortrait[564] = createTexturePNGFromMem(picture_obj564_PNG_H, sizeof(picture_obj564_PNG_H));

}

void Loadpicture_obj2(TextureInfoa *HeadPortrait)
{

HeadPortrait[56330] = createTexturePNGFromMem(picture_obj56330_PNG_H, sizeof(picture_obj56330_PNG_H));
HeadPortrait[56320] = createTexturePNGFromMem(picture_obj56320_PNG_H, sizeof(picture_obj56320_PNG_H));
HeadPortrait[56310] = createTexturePNGFromMem(picture_obj56310_PNG_H, sizeof(picture_obj56310_PNG_H));
HeadPortrait[51930] = createTexturePNGFromMem(picture_obj51930_PNG_H, sizeof(picture_obj51930_PNG_H));
HeadPortrait[51920] = createTexturePNGFromMem(picture_obj51920_PNG_H, sizeof(picture_obj51920_PNG_H));
HeadPortrait[51910] = createTexturePNGFromMem(picture_obj51910_PNG_H, sizeof(picture_obj51910_PNG_H));
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
HeadPortrait[51830] = createTexturePNGFromMem(picture_obj51830_PNG_H, sizeof(picture_obj51830_PNG_H));
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
HeadPortrait[56430] = createTexturePNGFromMem(picture_obj56430_PNG_H, sizeof(picture_obj56430_PNG_H));
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
HeadPortrait[51820] = createTexturePNGFromMem(picture_obj51820_PNG_H, sizeof(picture_obj51820_PNG_H));
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
HeadPortrait[56420] = createTexturePNGFromMem(picture_obj56420_PNG_H, sizeof(picture_obj56420_PNG_H));
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
HeadPortrait[51810] = createTexturePNGFromMem(picture_obj51810_PNG_H, sizeof(picture_obj51810_PNG_H));
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
HeadPortrait[56410] = createTexturePNGFromMem(picture_obj56410_PNG_H, sizeof(picture_obj56410_PNG_H));

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

HeadPortrait[2]=createTexturePNGFromMem(tearyao, sizeof(tearyao));//LOL图标美服
HeadPortrait[3]=createTexturePNGFromMem(teardata, sizeof(teardata));//泪心QQ头像

}


TextureInfoa djjddjnd [666]={};
        struct 全部头像1
{
	TextureInfoa 头像[666];
	
};
全部头像1 贴图1;

void 获取头像2(){
	
	Loadpicture_obj(贴图1.头像);
	
}




struct 技能图标
{
	TextureInfoa 头像[111111];
	
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
	TextureInfo 头像[111111];
	
};
全部头像 贴图;

TextureInfo 头像贴图(int 值)
{
	return 贴图.头像[值];
}


void 获取头像()
{
	for(int i =0;i<12111;i+=1)
	{
		贴图.头像[i] = 获取头像(i);
	}
		
}

















