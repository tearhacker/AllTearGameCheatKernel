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
#include "辅助类.h"

int 计算::计算距离(D3DVector 自身坐标,D3DVector 对方坐标){
	return (int)sqrt(pow(自身坐标.X-对方坐标.X,2)
		+pow(自身坐标.Y-对方坐标.Y,2)
		+pow(自身坐标.Z-对方坐标.Z,2))*0.01;
}

D2DVector 计算::rotateCoord(float angle, float objRadar_x, float objRadar_y)
{
	D2DVector radarCoordinate;
	float s = sin(angle * 3.141592653589793238 / 180);
	float c = cos(angle * 3.141592653589793238 / 180);
	radarCoordinate.X = objRadar_x * c + objRadar_y * s;
	radarCoordinate.Y = -objRadar_x * s + objRadar_y * c;
	return radarCoordinate;
}

D2DVector 计算::rotateCoord(D3DVector Enemy, D3DVector RealPerson)
{
    float x = RealPerson.X - Enemy.X;
    float y = RealPerson.Y - Enemy.Y;
    float z = RealPerson.Z - Enemy.Z;
	D2DVector radarCoordinate;
	radarCoordinate.X = atan2(y,x)*180/3.141592653589793238;
	radarCoordinate.Y = atan2(z,sqrt(x*x+y*y)) * 180 / 3.141592653589793238;
	return radarCoordinate;
}

D4DVector 计算::计算屏幕坐标(float 矩阵[16],D3DVector 人物坐标,float px,float py){
	D4DVector 屏幕坐标;
	float camear_r = 矩阵[3] * 人物坐标.X + 矩阵[7] * 人物坐标.Y + 矩阵[11] * 人物坐标.Z + 矩阵[15];
	float r_x = px + (矩阵[0] * 人物坐标.X + 矩阵[4] * 人物坐标.Y + 矩阵[8] * 人物坐标.Z +矩阵[12]) / camear_r * px;
	float r_y = py - (矩阵[1] * 人物坐标.X + 矩阵[5] * 人物坐标.Y + 矩阵[9] * (人物坐标.Z - 5) +矩阵[13]) / camear_r * py;
	float r_z = py - (矩阵[1] * 人物坐标.X + 矩阵[5] * 人物坐标.Y + 矩阵[9] * (人物坐标.Z + 205) +矩阵[13]) / camear_r * py;
	屏幕坐标.X = r_x-(r_y-r_z)/4;
	屏幕坐标.Y = r_y;
	屏幕坐标.Z = (r_y-r_z)/2;
	屏幕坐标.W = r_y-r_z;
	return 屏幕坐标;
}

D2DVector 计算::计算屏幕坐标2(float 矩阵[16],D3DVector 人物坐标,float px,float py){
	D2DVector 屏幕坐标;
	float camear_r = 矩阵[3] * 人物坐标.X + 矩阵[7] * 人物坐标.Y + 矩阵[11] * 人物坐标.Z + 矩阵[15];
	屏幕坐标.X = px + (矩阵[0] * 人物坐标.X + 矩阵[4] * 人物坐标.Y + 矩阵[8] * 人物坐标.Z + 矩阵[12]) / camear_r * px;
    屏幕坐标.Y = py - (矩阵[1] * 人物坐标.X + 矩阵[5] * 人物坐标.Y + 矩阵[9] * 人物坐标.Z + 矩阵[13]) / camear_r * py;
	return 屏幕坐标;
}


float 计算::计算屏幕距离(D2DVector &坐标,float px,float py){
return sqrt(pow(px - 坐标.X, 2) + pow(py - 坐标.Y, 2));
}


骨骼数据 计算::计算骨骼(float (&矩阵)[16],D3DVector (&骨骼)[17],float px,float py){
骨骼数据 temp=
{计算屏幕坐标2(矩阵,骨骼[0],px,py)
,计算屏幕坐标2(矩阵,骨骼[1],px,py)
,计算屏幕坐标2(矩阵,骨骼[2],px,py)
,计算屏幕坐标2(矩阵,骨骼[3],px,py)
,计算屏幕坐标2(矩阵,骨骼[4],px,py)
,计算屏幕坐标2(矩阵,骨骼[5],px,py)
,计算屏幕坐标2(矩阵,骨骼[6],px,py)
,计算屏幕坐标2(矩阵,骨骼[7],px,py)
,计算屏幕坐标2(矩阵,骨骼[8],px,py)
,计算屏幕坐标2(矩阵,骨骼[9],px,py)
,计算屏幕坐标2(矩阵,骨骼[10],px,py)
,计算屏幕坐标2(矩阵,骨骼[11],px,py)
,计算屏幕坐标2(矩阵,骨骼[12],px,py)
,计算屏幕坐标2(矩阵,骨骼[13],px,py)
,计算屏幕坐标2(矩阵,骨骼[14],px,py)};
return temp;
}
