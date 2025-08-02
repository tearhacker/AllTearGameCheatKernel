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
#include "图片调用.h"
#include "物资ID.h"
#include "辅助类.h"

extern 绘制 绘制;

std::map<int, TextureInfo> 手持图片;

static int getLength(const char* str) {
    int len = 0;
    while (*str) {
        if ((*str & 0xC0) != 0x80) {
            len++;
        }
        ++str;
    }
    return len;
}

void 绘图::初始化绘图(int X, int Y) {
    if (Y < X) {
        this->PX = X / 2;
        this->PY = Y / 2;
    } else {
        this->PX = Y / 2;
        this->PY = X / 2;
    }
}
void AddTextBold(ImDrawList *Draw,float size,int x, int y, ImVec4 color,ImVec4 color1, const char* str)
{
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(color1), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x - 0.1, y), ImGui::ColorConvertFloat4ToU32(color1), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(color1), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(color1), str);
    ImGui::GetBackgroundDrawList()->AddText(NULL, size,ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(color), str);
}
/* void 绘图::绘制瞄准信息()
{

  for (int i = 0; i < 绘制.被瞄准对象数量; i++)
  {
    string 距离显示 = to_string(static_cast<int>(绘制.被瞄信息[i].距离)) + "M";
    ImVec2 textSizeName = ImGui::CalcTextSize(绘制.被瞄信息[i].名字.c_str(), 0, 60);
    ImVec2 textSizeemploy = ImGui::CalcTextSize("使用", 0, 60);
    ImVec2 textSizeWeapon = ImGui::CalcTextSize(绘制.被瞄信息[i].瞄准武器.c_str(), 0, 60);
    ImVec2 textSizeAim = ImGui::CalcTextSize("瞄准您", 0, 60);
    ImVec2 textSizeDistance = ImGui::CalcTextSize(距离显示.c_str(), 0, 60);
    float startY = 200 + (50 * i);
    float spacing = 75.0f; // 调整间距的数值
    textSizeName.x += 12 * static_cast<float>(getLength(绘制.被瞄信息[i].名字.c_str()));
    textSizeWeapon.x += 9.375 * static_cast<float>(getLength(绘制.被瞄信息[i].瞄准武器.c_str()));
    // 枪械 9.375 名称 6.25
    float totalWidth = textSizeName.x + textSizeemploy.x + textSizeWeapon.x + textSizeAim.x + textSizeDistance.x + 4 * spacing;
    float startX = PX - totalWidth / 2;
    ImGui::GetBackgroundDrawList()->AddText(NULL, 50, ImVec2(startX, startY), ImColor(0, 0, 255), 绘制.被瞄信息[i].名字.c_str());
    ImGui::GetBackgroundDrawList()->AddText(NULL, 50, ImVec2(startX + textSizeName.x + 1 * spacing, startY), ImColor(255, 255, 255), "使用");
    ImGui::GetBackgroundDrawList()->AddText(NULL, 50, ImVec2(startX + textSizeName.x + textSizeemploy.x + 2 * spacing, startY), ImColor(255, 0, 0), 绘制.被瞄信息[i].瞄准武器.c_str());
    ImGui::GetBackgroundDrawList()->AddText(NULL, 50, ImVec2(startX + textSizeName.x + textSizeemploy.x + textSizeWeapon.x + 3 * spacing, startY), ImColor(255, 255, 255), "瞄准您");
    ImGui::GetBackgroundDrawList()->AddText(NULL, 50, ImVec2(startX + textSizeName.x + textSizeemploy.x + textSizeWeapon.x + textSizeAim.x + 4 * spacing, startY), ImColor(255, 255, 0), 距离显示.c_str());
  }
}
 */
void 绘图::RenderRadarScan(ImDrawList* draw_list, ImVec2 center, float radius, int numSegments, float& rotationAngle, float lineLength) {
    ImVec2 outerCirclePos = ImVec2(center.x + radius * cos(rotationAngle), center.y + radius * sin(rotationAngle));
    draw_list->AddCircleFilled(center, radius, IM_COL32(255, 255, 255, 55), numSegments);
    draw_list->AddCircle(center, radius * 0.75f, IM_COL32_WHITE, numSegments);
    draw_list->AddCircle(center, radius * 0.5f, IM_COL32_WHITE, numSegments);
    draw_list->AddCircle(center, radius, IM_COL32_WHITE, numSegments);
    draw_list->AddLine(ImVec2(center.x - lineLength, center.y), ImVec2(center.x + lineLength, center.y), IM_COL32_WHITE);
    draw_list->AddLine(ImVec2(center.x, center.y - lineLength), ImVec2(center.x, center.y + lineLength), IM_COL32_WHITE);
    /*
    float lineAngle1 =  0.25f * 3.141592653589793238;
    float lineAngle2 =  -0.25f * 3.141592653589793238;
    ImVec2 line1Start(center.x + lineLength * cos(lineAngle1), center.y + lineLength * sin(lineAngle1));
    ImVec2 line1End(center.x - lineLength * cos(lineAngle1), center.y - lineLength * sin(lineAngle1));
    ImVec2 line2Start(center.x + lineLength * cos(lineAngle2), center.y + lineLength * sin(lineAngle2));
    ImVec2 line2End(center.x - lineLength * cos(lineAngle2), center.y - lineLength * sin(lineAngle2));
    draw_list->AddLine(line1Start, line1End, IM_COL32_WHITE);
    draw_list->AddLine(line2Start, line2End, IM_COL32_WHITE);
    draw_list->AddLine(center, outerCirclePos, IM_COL32_WHITE);
    float newRotationAngle = rotationAngle + 0.02f;
    float rotationAngle2 = rotationAngle;
    outerCirclePos = ImVec2(center.x + radius * cos(newRotationAngle), center.y + radius * sin(newRotationAngle));
    draw_list->AddLine(center, outerCirclePos, IM_COL32_WHITE);
    newRotationAngle = rotationAngle + 0.02f;
    outerCirclePos = ImVec2(center.x + radius * cos(newRotationAngle), center.y + radius * sin(newRotationAngle));
    draw_list->AddLine(center, outerCirclePos, IM_COL32_WHITE);
    ImU32 shadowColor = IM_COL32(220, 212, 202, 255);

    float alpha = 0.5f;
    shadowColor = IM_COL32(220, 212, 202, static_cast<int>(128 * alpha));
    outerCirclePos = ImVec2(center.x + radius * cos(rotationAngle2), center.y + radius * sin(rotationAngle2));
    //draw_list->AddLine(center, outerCirclePos, shadowColor);
    rotationAngle2-=0.02f;

    rotationAngle = newRotationAngle;
    */
}

void 绘图::初始化坐标(D4DVector& 屏幕坐标, 骨骼数据& 骨骼) {
    left = 骨骼.Head.X - 屏幕坐标.Z / 2;
    right = 骨骼.Head.X + 屏幕坐标.Z / 2;
    top = 骨骼.Pelvis.Y - ((骨骼.Head.X != 0) ? (骨骼.Pelvis.Y - 骨骼.Head.Y) : (骨骼.Pelvis.Y - 骨骼.Chest.Y)) - 屏幕坐标.Z / 5;
    bottom = (骨骼.Left_Ankle.Y < 骨骼.Right_Ankle.Y) ? (骨骼.Right_Ankle.Y + 屏幕坐标.Z / 10) : (骨骼.Left_Ankle.Y + 屏幕坐标.Z / 10);
    MIDDLE = 屏幕坐标.X + 屏幕坐标.Z / 2;
    BOTTOM = 屏幕坐标.Y + 屏幕坐标.Z;
    TOP = 屏幕坐标.Y - 屏幕坐标.Z;
    屏幕坐标.X += 屏幕坐标.Z / 2;  // 身位矫正，向右挪移半个身位
}

void 绘图::绘制方框(bool isboot) {
    /*
    ImGui::GetForegroundDrawList()->AddRect({ left, top }, { right, bottom }, ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[0] * 255 + 0.5),static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[1] * 255 + 0.5),static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[2] * 255 + 0.5),static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[3] * 255 + 0.5)), 0, 0, 绘制.按钮.方框粗细);
    */
    // 获取当前缩放比例（假设已经有这样一个函数或者变量）
    float 缩放比例 = 0.2f;  // 例如 1.0 代表不缩放。0.5代表缩放到原始的50%

    // 计算方块的边长，根据矩形的尺寸调整
    float 方块边长比例 = 0.8f;  // 方块边长占矩形宽度的比例（例如5%）
    float 方块长度 = (right - left) * 方块边长比例 * 缩放比例;

    // 设置方框的颜色
    ImColor 方框color = ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[0] * 255 + 0.5),
                                static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[1] * 255 + 0.5),
                                static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[2] * 255 + 0.5),
                                static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[3] * 255 + 0.5));

    // 绘制四角方块
    ImGui::GetForegroundDrawList()->AddLine({left, top}, {left + 方块长度, top}, 方框color, 绘制.按钮.方框粗细);
    ImGui::GetForegroundDrawList()->AddLine({right, top}, {right - 方块长度, top}, 方框color, 绘制.按钮.方框粗细);
    ImGui::GetForegroundDrawList()->AddLine({left, bottom}, {left + 方块长度, bottom}, 方框color, 绘制.按钮.方框粗细);
    ImGui::GetForegroundDrawList()->AddLine({right, bottom}, {right - 方块长度, bottom}, 方框color, 绘制.按钮.方框粗细);

    ImGui::GetForegroundDrawList()->AddLine({left, top}, {left, top + 方块长度}, 方框color, 绘制.按钮.方框粗细);
    ImGui::GetForegroundDrawList()->AddLine({right, top}, {right, top + 方块长度}, 方框color, 绘制.按钮.方框粗细);
    ImGui::GetForegroundDrawList()->AddLine({left, bottom}, {left, bottom - 方块长度}, 方框color, 绘制.按钮.方框粗细);
    ImGui::GetForegroundDrawList()->AddLine({right, bottom}, {right, bottom - 方块长度}, 方框color, 绘制.按钮.方框粗细);

    /*
    if (!绘制.按钮.隐藏方框背景) {
    ImVec2 innerTopLeft(left + 1, top + 1); // 内部矩形的左上角坐标，相对于外部方框
    ImVec2 innerBottomRight(right - 1, bottom - 1); // 内部矩形的右下角坐标，相对于外部方框
    ImU32 filledColor = ImGui::GetColorU32(ImVec4(0, 1, 0, 0.3)); // 转换为ImU32类型的颜色
    ImGui::GetForegroundDrawList()->AddRectFilled(innerTopLeft, innerBottomRight, ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[0] * 255 + 0.5),static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[1] * 255 + 0.5),static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].方框颜色[2] * 255 + 0.5),76.5)); // 绿色的内部矩形
    }
    */
}

void 绘图::绘制人数(int 人机, int 真人) {
    /*
    std::string str1;
    std::string str2;
    if (人机 == 0 && 真人==0) {
    str2 += "0";
    str1 += "0";
    ImGui::GetForegroundDrawList()->AddImage(手持图片[10].textureId, {(PX), 70}, {(PX)+115, 125});
    ImGui::GetForegroundDrawList()->AddImage(手持图片[11].textureId, {(PX)-120,70}, {(PX), 125});
    } else {
    str2 += std::to_string((int)人机);
    str1 += std::to_string((int)真人);
    ImGui::GetForegroundDrawList()->AddImage(手持图片[10].textureId, {(PX), 70}, {(PX)+115, 125});
    ImGui::GetForegroundDrawList()->AddImage(手持图片[11].textureId, {(PX)-120,70}, {(PX), 125});
    }
    auto textSiz = ImGui::CalcTextSize(str2.c_str(),0,40);
    ImGui::GetForegroundDrawList()->AddText(nullptr, 40, {PX - (textSiz.x / 2)+72, 96.0f-(textSiz.y / 2)}, 颜色.白色, str2.c_str());
    auto textSize = ImGui::CalcTextSize(str1.c_str(),0,40);
    ImGui::GetForegroundDrawList()->AddText(nullptr, 40, {PX - (textSize.x / 2)-30, 96.0f-(textSize.y / 2)}, 颜色.白色, str1.c_str());
    */
    /*
    float rounding = 5.0f;  // 调整这个值以改变圆角的大小
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(PX - 100-30, 90), ImVec2(PX - 100 + 95, 90 + 35-5), ImColor(77, 135, 185), rounding);
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(PX - 100-30, 120), ImVec2(PX - 100 + 95, 120 + 60*1.5), ImColor(0, 0, 0, 112), rounding);
    float newWidth = 130.0f; // 设置新的宽度
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(PX + 5, 90), ImVec2(PX + 5 + newWidth, 90 + 35-5), ImColor(255, 77, 135), rounding);
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(PX + 5, 120), ImVec2(PX + 5 + newWidth, 120 + 60*1.5), ImColor(0, 0, 0, 112), rounding);

    // 绘制文本
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(PX - 90, 90), ImColor(255,255,255), "玩家");
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(PX + 90/2, 90), ImColor(255,255,255), "人机");

    int 测试 = 20;
    // 使用 snprintf 代替 sprintf

    //单位数 真人78.5 人机60
    //双位数 真人88.5 人机50
    char content[32];
    float 真人占位,人机占位;
    if (真人 > 9) {
      真人占位 = 88.5;
    }else {
      真人占位 = 78.5;
    }
    snprintf(content, sizeof(content), "%d", 真人);
    ImGui::GetBackgroundDrawList()->AddText(NULL,55,ImVec2(PX - 真人占位, 140), ImColor(255,255,255), content);

    if (人机 > 9) {
      人机占位 = 50;
    }else {
      人机占位 = 60;
    }
    snprintf(content, sizeof(content), "%d", 人机);
    ImGui::GetBackgroundDrawList()->AddText(NULL,55,ImVec2(PX + 人机占位, 140), ImColor(255,255,255), content);
    */
    // int 总人数 = 真人 + 人机;
    // string a = std::to_string(总人数);
    // auto Size = ImGui::CalcTextSize(a.c_str(), 0, 60);
    // 绘制加粗文本(70, PX - (Size.x), 100, ImColor(0, 0, 0, 255), ImColor(0, 0, 0, 255), a.c_str()); // 前面为大小，后面为上下

    string a = std::to_string(真人);
    auto Size = ImGui::CalcTextSize(a.c_str(), 0, 60);
    绘制加粗文本(70, PX - (Size.x) - 50, 100, ImColor(255, 0, 0, 255), ImColor(255, 0, 0, 255), a.c_str());  // 前面为大小，后面为上下

    a = "";
    a = std::to_string(人机);
    Size = ImGui::CalcTextSize(a.c_str(), 0, 60);
    绘制加粗文本(70, PX - (Size.x) + 60, 100, ImColor(0, 255, 0, 255), ImColor(0, 255, 0, 255), a.c_str());  // 前面为大小，后面为上下
}

void 绘图::绘制距离(int 距离, int 队伍) {
    // string s = "[" + to_string((int)队伍) + "]";
    string 距离文本 = to_string((int)距离) + "M";
    // auto 队伍文本大小 = ImGui::CalcTextSize(s.c_str(), 0, 26);
    // auto 距离文本大小 = ImGui::CalcTextSize(距离文本.c_str(), 0, 26);
    // float 总宽度 = 队伍文本大小.x + 距离文本大小.x;
    // float 起始位置 = MIDDLE - (总宽度 / 2);
    // float 队伍位置 = 起始位置;
    // float 距离位置 = 队伍位置 + 队伍文本大小.x;

    // string a = GetHol(状态);
    auto Size = ImGui::CalcTextSize(距离文本.c_str(), 0, 18);
    // 绘制加粗文本(26,MIDDLE - (Size.x / 2),bottom, 颜色.白色,颜色.白色, a.c_str());

    // 绘制加粗文本(26, 队伍位置, top - 33, ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].阵营颜色[0] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].阵营颜色[1] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].阵营颜色[2] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].阵营颜色[3] * 255 + 0.5)), ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].阵营颜色[0] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].阵营颜色[1] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].阵营颜色[2] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].阵营颜色[3] * 255 + 0.5)), s.c_str());
    绘制加粗文本(18, MIDDLE - (Size.x / 4), bottom, ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].距离颜色[0] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].距离颜色[1] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].距离颜色[2] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].距离颜色[3] * 255 + 0.5)), ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].距离颜色[0] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].距离颜色[1] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].距离颜色[2] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].距离颜色[3] * 255 + 0.5)), 距离文本.c_str());
}

void 绘图::绘制射线(骨骼数据& 骨骼) {
    ImGui::GetForegroundDrawList()->AddLine({PX, 0}, {骨骼.Head.X, top - 70}, ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].射线颜色[0] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].射线颜色[1] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].射线颜色[2] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].射线颜色[3] * 255 + 0.5)), 绘制.按钮.射线粗细);  // 使用白色，并增加线宽
}

void 绘图::绘制名字(string 名字, bool isboot, float 计时, bool 是否掐雷, char* 类名, int 阵营, int Bonecount){
    string a = "[" + to_string((int)阵营) + "]";
    a += " ";
    a += (isboot && 阵营 != -1) ? "人机" : 名字;
    // a+= "[骨骼数"+ to_string(Bonecount) +"]";
    if (strstr(类名, "BOSS") != 0) {
        a += "[BOSS]";
    }
  if(是否掐雷) {
    //a += " 计时-[" + to_string((float)计时) + "]";
    char buffer[50];
    float 计时保留一位小数点 = static_cast<float>(计时);
    std::sprintf(buffer, "%.1f", 计时保留一位小数点);
    a += " 计时-[" + std::string(buffer) + "]";
  }
  AddTextBold(ImGui::GetBackgroundDrawList(), 20, MIDDLE - 55,top - 38,ImColor(255,255,255,255), ImColor(0,0,0,255),a.c_str());
  ImGui::GetBackgroundDrawList()->AddRectFilled({MIDDLE - 90, top - 42}, {MIDDLE - 60, top - 15},ImColor(128, 0, 128, 255), 4, 0);

  std::string s;
    s += std::to_string((int)阵营);
    auto textSize1 = ImGui::CalcTextSize(s.c_str(), 0, 30);
    AddTextBold(ImGui::GetBackgroundDrawList(),22  , MIDDLE - 70 - (textSize1.x / 2), top - 38, ImColor(255,255,255,255),ImColor(0,0,0,255), s.c_str());
}

void 绘图::绘制血量(float 最大血量, float 当前血量, bool isbot) {
    float 血量 = 当前血量 / 最大血量 * 100;
    if (绘制.按钮.血条绘图 == 0) {
        // 默认样式绘图
        ImColor color = (血量 <= 40)   ? ImColor(235, 0, 0)
                        : (血量 <= 70) ? ImColor(220, 220, 0)
                                       : ImColor(0, 255, 0);

        ImGui::GetForegroundDrawList()->AddRectFilled({MIDDLE - 62, top - 13}, {MIDDLE - 62 + 1.13 * 血量, top - 7}, color, 2);
    } else if (绘制.按钮.血条绘图 == 1) {
        // ios样式
        std::string duo;
        duo += std::to_string((int)血量);
        auto textSize = ImGui::CalcTextSize(duo.c_str(), 0, 25);
        float aa = 血量 * 3.6;
        ImGui::GetForegroundDrawList()->AddCircleArc({MIDDLE, top - 75}, 20, {0, aa}, ImColor(10, 240, 10, 210), 0, 5);
        ImGui::GetForegroundDrawList()->AddText(NULL, 20, {MIDDLE - (textSize.x / 4), top - 65 - (textSize.y / 2)}, ImColor(255, 255, 255), duo.c_str());

    } else if (绘制.按钮.血条绘图 == 2) {
        // oe样式
        std::string duo;
        duo += std::to_string((int)血量);
        auto textSize = ImGui::CalcTextSize(duo.c_str(), 0, 25);
        const float 血量条宽度 = 1.13f * 血量;
        const ImVec2 背景左上 = {MIDDLE - 62, top - 75};
        const ImVec2 背景右下 = {MIDDLE + 52, top - 55};
        const ImVec2 血量左上 = {MIDDLE - 62, top - 75};
        const ImVec2 血量右下 = {MIDDLE - 62 + 血量条宽度, top - 55};
        const ImU32 背景颜色 = ImColor(255, 255, 255, 100);
        ImColor fillColor = ImColor(0, 255, 0, 255);
        fillColor.Value.w = 0.5f;
        const ImU32 血量颜色 = fillColor;
        ImGui::GetForegroundDrawList()->AddRectFilled(背景左上, 背景右下, 背景颜色, 30);
        ImGui::GetForegroundDrawList()->AddRectFilled(血量左上, 血量右下, 血量颜色, 30);
        ImGui::GetForegroundDrawList()->AddRect(背景左上, 背景右下, ImColor(0, 0, 0, 200), 30, 0, 1.5);
    }

    /*
      string duo;
      duo += to_string((int)当前血量);
      auto textSize = ImGui::CalcTextSize(duo.c_str(), 0, 25);
      float 血量 = 当前血量 / 最大血量 * 100;
      const float 血量条宽度 = 1.13f * 血量;
      // const ImVec2 背景左上 = {MIDDLE - 62, top - 36};
      // const ImVec2 背景右下 = {MIDDLE + 52, top - 33};
      const ImVec2 血量左上 = {MIDDLE - 62, top - 10};
      const ImVec2 血量右下 = {MIDDLE - 62 + 血量条宽度, top - 7};
      // const ImU32 背景颜色 = ImColor(255, 255, 255, 100);
      ImColor fillColor = ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].血量颜色[0] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].血量颜色[1] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].血量颜色[2] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].血量颜色[3] * 255 + 0.5));
      // fillColor.Value.w = 0.5f; //血条透明度
      ImU32 血量颜色 = fillColor;
      if (isbot) {
          血量颜色 = ImColor(0, 255, 0, 255);
      }

    // ImGui::GetForegroundDrawList()->AddRectFilled(背景左上, 背景右下, 背景颜色, 1);
    ImGui::GetForegroundDrawList()->AddRectFilled(血量左上, 血量右下, 血量颜色, 2);
    // ImGui::GetForegroundDrawList()->AddRect(背景左上, 背景右下, ImColor(0, 0, 0, 200), 0, 0, 2.0);
*/
    /*
    ImVec2 topLeft = 背景左上;
    ImVec2 bottomRight = 背景右下;

    float lineWidth = 1.5f;
    ImColor lineColor(0, 0, 0, 235); // 分割线的颜色

    float rectWidth = bottomRight.x - topLeft.x;
    float segmentWidth = rectWidth / 5;

    float line1X = topLeft.x + segmentWidth; // 第一条分割线的 X 坐标
    float line2X = topLeft.x + segmentWidth * 2; // 第二条分割线的 X 坐标
    float line3X = topLeft.x + segmentWidth * 3; // 第三条分割线的 X 坐标
    float line4X = topLeft.x + segmentWidth * 4; // 第四条分割线的 X 坐标

    ImGui::GetForegroundDrawList()->AddLine(ImVec2(line1X, topLeft.y), ImVec2(line1X, bottomRight.y), lineColor, lineWidth);
    ImGui::GetForegroundDrawList()->AddLine(ImVec2(line2X, topLeft.y), ImVec2(line2X, bottomRight.y), lineColor, lineWidth);
    ImGui::GetForegroundDrawList()->AddLine(ImVec2(line3X, topLeft.y), ImVec2(line3X, bottomRight.y), lineColor, lineWidth);
    ImGui::GetForegroundDrawList()->AddLine(ImVec2(line4X, topLeft.y), ImVec2(line4X, bottomRight.y), lineColor, lineWidth);
    */
}

void 绘图::绘制手持(int 手持, int 状态, int 子弹, int 最大子弹) {
    if (绘制.按钮.手持绘图 == 1) {
        手持 = heldconversion(手持);
        if (手持图片.find(手持) != 手持图片.end()) {
            float addY = 0;
            if (绘制.按钮.血条绘图 == 1) {
                addY = 40;
            } else if (绘制.按钮.血条绘图 == 2) {
                addY = 30;
            }
            ImGui::GetForegroundDrawList()->AddImage(手持图片[手持].textureId, ImVec2(MIDDLE - 75 * 0.7f, top - 135 * 0.7f - addY), ImVec2(MIDDLE + 75 * 0.7f, top - 100 * 0.7f - addY), ImVec2(0, 0), ImVec2(1, 1), ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)));

            string b = " [" + to_string(子弹) + "/" + to_string(最大子弹) + "]";
            auto textSize = ImGui::CalcTextSize(b.c_str(), 0, 20);
            ImColor color = ImColor(static_cast<int>(绘制.手持颜色[0] * 255 + 0.5), static_cast<int>(绘制.手持颜色[1] * 255 + 0.5), static_cast<int>(绘制.手持颜色[2] * 255 + 0.5), static_cast<int>(绘制.手持颜色[3] * 255 + 0.5));
            绘制加粗文本(20, MIDDLE - (textSize.x / 4), top - 52, color, color, b.c_str());
        }
    } else {
        string b = GetHolGunItem(手持);
        b += " [" + to_string(子弹) + "/" + to_string(最大子弹) + "]";
        auto textSize = ImGui::CalcTextSize(b.c_str(), 0, 20);
        ImColor color = ImColor(static_cast<int>(绘制.手持颜色[0] * 255 + 0.5), static_cast<int>(绘制.手持颜色[1] * 255 + 0.5), static_cast<int>(绘制.手持颜色[2] * 255 + 0.5), static_cast<int>(绘制.手持颜色[3] * 255 + 0.5));
        绘制加粗文本(20, MIDDLE - (textSize.x / 4), top - 52, color, color, b.c_str());
    }

    string a = GetHol(状态);
    auto Size = ImGui::CalcTextSize(a.c_str(), 0, 20);
    绘制加粗文本(20, MIDDLE - (Size.x / 4), top - 74, 颜色.白色, 颜色.白色, a.c_str());
}

void 绘图::绘制骨骼(骨骼数据& 骨骼, D4DVector& 屏幕坐标, bool LineOfSightTo, float 距离) {
    // ImColor 骨骼color = ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].骨骼颜色[0] * 255 + 0.5),static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].骨骼颜色[1] * 255 + 0.5),static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].骨骼颜色[2] * 255 + 0.5),static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].骨骼颜色[3] * 255 + 0.5));

    ImColor 骨骼color;
    if (LineOfSightTo) {
        骨骼color = ImColor(static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].骨骼颜色[0] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].骨骼颜色[1] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].骨骼颜色[2] * 255 + 0.5), static_cast<int>(绘制.Colorset[(int)绘制.对象信息.敌人信息.isboot].骨骼颜色[3] * 255 + 0.5));
    } else {
        骨骼color = ImColor(0, 255, 0, 100);
    }

    // ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(骨骼.Head.X, 骨骼.Head.Y), 屏幕坐标.W/13, 骨骼color, 0, 绘制.按钮.骨骼粗细);
    if (距离 < 绘制.骨骼距离限制) {
        if (sqrt(pow(骨骼.Chest.X - 骨骼.Pelvis.X, 2) + pow(骨骼.Chest.Y - 骨骼.Pelvis.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Chest.X, 骨骼.Chest.Y}, {骨骼.Pelvis.X, 骨骼.Pelvis.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Chest.X - 骨骼.Left_Shoulder.X, 2) + pow(骨骼.Chest.Y - 骨骼.Left_Shoulder.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Chest.X, 骨骼.Chest.Y}, {骨骼.Left_Shoulder.X, 骨骼.Left_Shoulder.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Left_Shoulder.X - 骨骼.Left_Elbow.X, 2) + pow(骨骼.Left_Shoulder.Y - 骨骼.Left_Elbow.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Left_Shoulder.X, 骨骼.Left_Shoulder.Y}, {骨骼.Left_Elbow.X, 骨骼.Left_Elbow.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Left_Elbow.X - 骨骼.Left_Wrist.X, 2) + pow(骨骼.Left_Elbow.Y - 骨骼.Left_Wrist.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Left_Elbow.X, 骨骼.Left_Elbow.Y}, {骨骼.Left_Wrist.X, 骨骼.Left_Wrist.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Chest.X - 骨骼.Right_Shoulder.X, 2) + pow(骨骼.Chest.Y - 骨骼.Right_Shoulder.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Chest.X, 骨骼.Chest.Y}, {骨骼.Right_Shoulder.X, 骨骼.Right_Shoulder.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Right_Shoulder.X - 骨骼.Right_Elbow.X, 2) + pow(骨骼.Right_Shoulder.Y - 骨骼.Right_Elbow.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Right_Shoulder.X, 骨骼.Right_Shoulder.Y}, {骨骼.Right_Elbow.X, 骨骼.Right_Elbow.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Right_Elbow.X - 骨骼.Right_Wrist.X, 2) + pow(骨骼.Right_Elbow.Y - 骨骼.Right_Wrist.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Right_Elbow.X, 骨骼.Right_Elbow.Y}, {骨骼.Right_Wrist.X, 骨骼.Right_Wrist.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Pelvis.X - 骨骼.Left_Thigh.X, 2) + pow(骨骼.Pelvis.Y - 骨骼.Left_Thigh.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Pelvis.X, 骨骼.Pelvis.Y}, {骨骼.Left_Thigh.X, 骨骼.Left_Thigh.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Left_Thigh.X - 骨骼.Left_Knee.X, 2) + pow(骨骼.Left_Thigh.Y - 骨骼.Left_Knee.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Left_Thigh.X, 骨骼.Left_Thigh.Y}, {骨骼.Left_Knee.X, 骨骼.Left_Knee.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Left_Knee.X - 骨骼.Left_Ankle.X, 2) + pow(骨骼.Left_Knee.Y - 骨骼.Left_Ankle.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Left_Knee.X, 骨骼.Left_Knee.Y}, {骨骼.Left_Ankle.X, 骨骼.Left_Ankle.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Pelvis.X - 骨骼.Right_Thigh.X, 2) + pow(骨骼.Pelvis.Y - 骨骼.Right_Thigh.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Pelvis.X, 骨骼.Pelvis.Y}, {骨骼.Right_Thigh.X, 骨骼.Right_Thigh.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Right_Thigh.X - 骨骼.Right_Knee.X, 2) + pow(骨骼.Right_Thigh.Y - 骨骼.Right_Knee.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Right_Thigh.X, 骨骼.Right_Thigh.Y}, {骨骼.Right_Knee.X, 骨骼.Right_Knee.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
        if (sqrt(pow(骨骼.Right_Knee.X - 骨骼.Right_Ankle.X, 2) + pow(骨骼.Right_Knee.Y - 骨骼.Right_Ankle.Y, 2)) < 100) {
            ImGui::GetForegroundDrawList()->AddLine({骨骼.Right_Knee.X, 骨骼.Right_Knee.Y}, {骨骼.Right_Ankle.X, 骨骼.Right_Ankle.Y}, 骨骼color, 绘制.按钮.骨骼粗细);
        }
    }
}

void 绘图::绘制自瞄触摸范围(float 触摸范围, float 触摸范围X, float 触摸范围Y) {
    auto textSize = ImGui::CalcTextSize("触摸位置,长按拖动", 0, 30);
    ImGui::GetForegroundDrawList()->AddRectFilled({触摸范围X - 触摸范围 / 2, PY * 2 - 触摸范围Y + 触摸范围 / 2}, {触摸范围X + 触摸范围 / 2, PY * 2 - 触摸范围Y - 触摸范围 / 2}, ImColor(255, 0, 0, 120));
    ImGui::GetForegroundDrawList()->AddText(NULL, 30, {触摸范围X - (textSize.x / 2), PY * 2 - 触摸范围Y}, ImColor(255, 255, 255), "触摸位置,长按拖动");
}

void 绘图::绘制字体描边(float size, int x, int y, ImVec4 color, const char* str) {
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, ImVec2(x + 1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, ImVec2(x - 0.1, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, ImVec2(x, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, ImVec2(x, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, 1.0f)), str);
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(color), str);
}

void 绘图::绘制加粗文本(float size, float x, float y, ImColor color, ImColor color1, const char* str) {
    // ImGui::GetBackgroundDrawList()->AddText(nullptr, size, ImVec2(x - 0.1, y - 0.1), color1, str);
    // ImGui::GetBackgroundDrawList()->AddText(nullptr, size, ImVec2(x + 0.1, y + 0.1), color1, str);
    ImGui::GetBackgroundDrawList()->AddText(nullptr, size, ImVec2(x, y), color, str);
}

bool 绘图::WorldTurnScreen(VecTor2& Screen, VecTor3 World, float Matrix[]) {
    float Camera = Matrix[3] * World.x + Matrix[7] * World.y + Matrix[11] * World.z + Matrix[15];
    if (Camera < 0.03) {
        return false;
    }
    Screen.x = PX + (Matrix[0] * World.x + Matrix[4] * World.y + Matrix[8] * World.z + Matrix[12]) / Camera * PX;
    Screen.y = PY - (Matrix[1] * World.x + Matrix[5] * World.y + Matrix[9] * World.z + Matrix[13]) / Camera * PY;
    return true;
}

// 爆炸范围
void 绘图::ExplosionRange(D3DVector Obj, ImColor color, float Range, float thickn, float Matrix[]) {
    VecTor3 l1, l2, l3, l4, l5, l6, l7, l8;
    VecTor2 lw1, lw2, lw3, lw4, lw5, lw6, lw7, lw8;
    l1 = VecTor3(Obj.X - Range, Obj.Y - Range, Obj.Z);
    l2 = VecTor3(Obj.X, Obj.Y - Range, Obj.Z);
    l3 = VecTor3(Obj.X + Range, Obj.Y - Range, Obj.Z);
    l4 = VecTor3(Obj.X - Range, Obj.Y, Obj.Z);
    l5 = VecTor3(Obj.X + Range, Obj.Y, Obj.Z);
    l6 = VecTor3(Obj.X - Range, Obj.Y + Range, Obj.Z);
    l7 = VecTor3(Obj.X, Obj.Y + Range, Obj.Z);
    l8 = VecTor3(Obj.X + Range, Obj.Y + Range, Obj.Z);
    WorldTurnScreen(lw1, l1, Matrix);
    WorldTurnScreen(lw2, l2, Matrix);
    WorldTurnScreen(lw3, l3, Matrix);
    WorldTurnScreen(lw4, l4, Matrix);
    WorldTurnScreen(lw5, l5, Matrix);
    WorldTurnScreen(lw6, l6, Matrix);
    WorldTurnScreen(lw7, l7, Matrix);
    WorldTurnScreen(lw8, l8, Matrix);

    // 绘制曲线
    ImGui::GetForegroundDrawList()->AddBezierCubic({lw4.x, lw4.y}, {lw1.x, lw1.y}, {lw2.x, lw2.y}, {lw2.x, lw2.y}, color, thickn);
    ImGui::GetForegroundDrawList()->AddBezierCubic({lw2.x, lw2.y}, {lw3.x, lw3.y}, {lw5.x, lw5.y}, {lw5.x, lw5.y}, color, thickn);
    ImGui::GetForegroundDrawList()->AddBezierCubic({lw5.x, lw5.y}, {lw8.x, lw8.y}, {lw7.x, lw7.y}, {lw7.x, lw7.y}, color, thickn);
    ImGui::GetForegroundDrawList()->AddBezierCubic({lw7.x, lw7.y}, {lw6.x, lw6.y}, {lw4.x, lw4.y}, {lw4.x, lw4.y}, color, thickn);
}

void 绘图::Parabola(VecTor3 obj, float Matrix[]) {
    static std::vector<VecTor3> grenadePath;  // 将 grenadePath 声明为静态局部变量
    // 创建一个新的游戏内坐标点
    VecTor3 newGrenadePosition;
    newGrenadePosition = obj;

    // 添加新位置到路径
    grenadePath.push_back(newGrenadePosition);

    // 限制路径点的数量，例如最多存储 100 个点
    if (grenadePath.size() > 100) {
        grenadePath.erase(grenadePath.begin(), grenadePath.begin() + grenadePath.size() - 100);
    }
    VecTor2 screenPos;
    // 准备绘制路径

    std::vector<VecTor2> screenPath;  // 存储转换后的屏幕坐标
    for (const VecTor3& pos : grenadePath) {
        // 将每个游戏内坐标转换为屏幕坐标
        float Camera = Matrix[3] * pos.x + Matrix[7] * pos.y + Matrix[11] * pos.z + Matrix[15];
        screenPos.x = PX + (Matrix[0] * pos.x + Matrix[4] * pos.y + Matrix[8] * pos.z + Matrix[12]) / Camera * PX;
        screenPos.y = PY - (Matrix[1] * pos.x + Matrix[5] * pos.y + Matrix[9] * pos.z + Matrix[13]) / Camera * PY;
        // WorldToScreen(&screenPos ,pos);
        screenPath.push_back(screenPos);
    }

    // 绘制路径
    if (screenPath.size() > 1) {
        // 反转路径点，因为我们是从尾部开始绘制的
        std::reverse(screenPath.begin(), screenPath.end());

        for (size_t i = 0; i < screenPath.size() - 1; ++i) {
            // 绘制线段连接每个点
            // ImGui::GetForegroundDrawList()->AddLine({screenPath[i].x, screenPath[i].y}, {screenPath[i + 8].x, screenPath[i + 8].y}, color, );
            ImGui::GetForegroundDrawList()->AddCircleFilled({screenPath[i].x, screenPath[i].y}, 3, ImColor(0, 255, 0, 255), 3);
        }
    }
}