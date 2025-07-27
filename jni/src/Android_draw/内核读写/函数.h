float matrix[16] = { 0 }, angle, camera, r_x, r_y, r_w;
float px;
float py;
#define PI 3.141592653589793238
double sf = 180 / PI;
#include "定制读写.h"
typedef unsigned short UTF16;
typedef char UTF8;
typedef unsigned long long  kaddr;
uintptr_t Gname;
// 读取字符信息
void getUTF8(UTF8 * buf, unsigned long namepy){
UTF16 buf16[16] = { 0 };
驱动->读取(namepy, buf16, 28);
UTF16 *pTempUTF16 = buf16;
UTF8 *pTempUTF8 = buf;
UTF8 *pUTF8End = pTempUTF8 + 32;
while (pTempUTF16 < pTempUTF16 + 28){
if (*pTempUTF16 <= 0x007F && pTempUTF8 + 1 < pUTF8End){
*pTempUTF8++ = (UTF8) * pTempUTF16;
}else if (*pTempUTF16 >= 0x0080 && *pTempUTF16 <= 0x07FF && pTempUTF8 + 2 < pUTF8End){
*pTempUTF8++ = (*pTempUTF16 >> 6) | 0xC0;
*pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
}else if (*pTempUTF16 >= 0x0800 && *pTempUTF16 <= 0xFFFF && pTempUTF8 + 3 < pUTF8End){
*pTempUTF8++ = (*pTempUTF16 >> 12) | 0xE0;
*pTempUTF8++ = ((*pTempUTF16 >> 6) & 0x3F) | 0x80;
*pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
}else{
break;
}
pTempUTF16++;
}
}

// 计算骨骼
struct Vector2A {
float X;
float Y;
Vector2A() {
this->X = 0;
this->Y = 0;
}
Vector2A(float x, float y) {
this->X = x;
this->Y = y;
}
};

struct D2DVector {
float X;
float Y;
};
struct D3DVector {
float X;
float Y;
float Z;
};

struct Vector3A {
float X;
float Y;
float Z;
Vector3A() {
this->X = 0;
this->Y = 0;
this->Z = 0;
}
Vector3A(float x, float y, float z) {
this->X = x;
this->Y = y;
this->Z = z;
}
};

struct FMatrix {
float M[4][4];
};

class FRotator {
public:
FRotator() :Pitch(0.f), Yaw(0.f), Roll(0.f) {
}
FRotator(float _Pitch, float _Yaw, float _Roll) : Pitch(_Pitch), Yaw(_Yaw), Roll(_Roll) {
}
~FRotator() {
}
float Pitch;
float Yaw;
float Roll;
inline FRotator Clamp() {

if (Pitch > 180) {
Pitch -= 360;
} else {
if (Pitch < -180) {
Pitch += 360;
}
}
if (Yaw > 180) {
Yaw -= 360;
} else {
if (Yaw < -180) {
Yaw += 360;
}
}
if (Pitch > 89) {
Pitch = 89;
}
if (Pitch < -89) {
Pitch = -89;
}
while (Yaw < 180) {
Yaw += 360;
}
while (Yaw > 180) {
Yaw -= 360;
}
Roll = 0;
return FRotator(Pitch, Yaw, Roll);
}
inline float Length() {
return sqrtf(Pitch * Pitch + Yaw * Yaw + Roll * Roll);
}
FRotator operator+(FRotator v) {
return FRotator(Pitch + v.Pitch, Yaw + v.Yaw, Roll + v.Roll);
}
FRotator operator-(FRotator v) {
return FRotator(Pitch - v.Pitch, Yaw - v.Yaw, Roll - v.Roll);
}
};

struct Quat {
float X;
float Y;
float Z;
float W;
};


struct FTransform {
Quat Rotation;
Vector3A Translation;
float chunk;
Vector3A Scale3D;
};


float get_3D_Distance(float Self_x, float Self_y, float Self_z, float Object_x, float Object_y, float Object_z) {
float x, y, z;
x = Self_x - Object_x;
y = Self_y - Object_y;
z = Self_z - Object_z;
// 求平方根
return (float)(sqrt(x * x + y * y + z * z));
}

// 计算旋转坐标
Vector2A rotateCoord(float angle, float objRadar_x, float objRadar_y) {
Vector2A radarCoordinate;
float s = sin(angle * PI / 180);
float c = cos(angle * PI / 180);
radarCoordinate.X = objRadar_x * c + objRadar_y * s;
radarCoordinate.Y = -objRadar_x * s + objRadar_y * c;
return radarCoordinate;
}

Vector2A WorldToScreen(Vector3A obj, float matrix[16], float ViewW) {
float x = px + (matrix[0] * obj.X + matrix[4] * obj.Y + matrix[8] * obj.Z + matrix[12]) / ViewW * px;
float y = py - (matrix[1] * obj.X + matrix[5] * obj.Y + matrix[9] * obj.Z + matrix[13]) / ViewW * py;
return Vector2A(x, y);
}

Vector3A MarixToVector(FMatrix matrix) {
return Vector3A(matrix.M[3][0], matrix.M[3][1], matrix.M[3][2]);
}

FMatrix MatrixMulti(FMatrix m1, FMatrix m2) {
FMatrix matrix = FMatrix();
for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
for (int k = 0; k < 4; k++) {
matrix.M[i][j] += m1.M[i][k] * m2.M[k][j];
}
}
}
return matrix;
}

FMatrix TransformToMatrix(FTransform transform) {
FMatrix matrix;
matrix.M[3][0] = transform.Translation.X;
matrix.M[3][1] = transform.Translation.Y;
matrix.M[3][2] = transform.Translation.Z;
float x2 = transform.Rotation.X + transform.Rotation.X;
float y2 = transform.Rotation.Y + transform.Rotation.Y;
float z2 = transform.Rotation.Z + transform.Rotation.Z;
float xx2 = transform.Rotation.X * x2;
float yy2 = transform.Rotation.Y * y2;
float zz2 = transform.Rotation.Z * z2;
matrix.M[0][0] = (1 - (yy2 + zz2)) * transform.Scale3D.X;
matrix.M[1][1] = (1 - (xx2 + zz2)) * transform.Scale3D.Y;
matrix.M[2][2] = (1 - (xx2 + yy2)) * transform.Scale3D.Z;
float yz2 = transform.Rotation.Y * z2;
float wx2 = transform.Rotation.W * x2;
matrix.M[2][1] = (yz2 - wx2) * transform.Scale3D.Z;
matrix.M[1][2] = (yz2 + wx2) * transform.Scale3D.Y;
float xy2 = transform.Rotation.X * y2;
float wz2 = transform.Rotation.W * z2;
matrix.M[1][0] = (xy2 - wz2) * transform.Scale3D.Y;
matrix.M[0][1] = (xy2 + wz2) * transform.Scale3D.X;
float xz2 = transform.Rotation.X * z2;
float wy2 = transform.Rotation.W * y2;
matrix.M[2][0] = (xz2 + wy2) * transform.Scale3D.Z;
matrix.M[0][2] = (xz2 - wy2) * transform.Scale3D.X;
matrix.M[0][3] = 0;
matrix.M[1][3] = 0;
matrix.M[2][3] = 0;
matrix.M[3][3] = 1;
return matrix;
}

FTransform getBone(unsigned long addr) {
FTransform transform;
驱动->读取(addr, &transform, 4 * 11);
return transform;
}

struct D3DXMATRIX {
float _11;
float _12;
float _13;
float _14;
float _21;
float _22;
float _23;
float _24;
float _31;
float _32;
float _33;
float _34;
float _41;
float _42;
float _43;
float _44;
};

struct D3DXVECTOR4 {
float X;
float Y;
float Z;
float W;
};

struct FTransform1 {
D3DXVECTOR4 Rotation;
D3DVector Translation;
D3DVector Scale3D;
};

D3DXMATRIX ToMatrixWithScale(D3DXVECTOR4 Rotation, D3DVector Translation, D3DVector Scale3D) {
D3DXMATRIX M;
float X2, Y2, Z2, xX2, Yy2, Zz2, Zy2, Wx2, Xy2, Wz2, Zx2, Wy2;
M._41 = Translation.X;
M._42 = Translation.Y;
M._43 = Translation.Z;
X2 = Rotation.X + Rotation.X;
Y2 = Rotation.Y + Rotation.Y;
Z2 = Rotation.Z + Rotation.Z;
xX2 = Rotation.X * X2;
Yy2 = Rotation.Y * Y2;
Zz2 = Rotation.Z * Z2;
M._11 = (1 - (Yy2 + Zz2)) * Scale3D.X;
M._22 = (1 - (xX2 + Zz2)) * Scale3D.Y;
M._33 = (1 - (xX2 + Yy2)) * Scale3D.Z;
Zy2 = Rotation.Y * Z2;
Wx2 = Rotation.W * X2;
M._32 = (Zy2 - Wx2) * Scale3D.Z;
M._23 = (Zy2 + Wx2) * Scale3D.Y;
Xy2 = Rotation.X * Y2;
Wz2 = Rotation.W * Z2;
M._21 = (Xy2 - Wz2) * Scale3D.Y;
M._12 = (Xy2 + Wz2) * Scale3D.X;
Zx2 = Rotation.X * Z2;
Wy2 = Rotation.W * Y2;
M._31 = (Zx2 + Wy2) * Scale3D.Z;
M._13 = (Zx2 - Wy2) * Scale3D.X;
M._14 = 0;
M._24 = 0;
M._34 = 0;
M._44 = 1;
return M;
}

char* 获取类名(long addr)
    {
    int id = 驱动->读取整数(addr + 0x18);
    long ye = 驱动->读取指针(Gname + (id / 0x4000) * 8);
    long xu = 驱动->读取指针(ye + (id % 0x4000) * 8);
    static char Item[256];
    驱动->读取(xu + 0xc, Item, sizeof(Item));
    return Item;
    }

FTransform1 ReadFTransform(long int address) {
FTransform1 Result;
Result.Rotation.X = 驱动->读取浮点数(address);// Rotation_X 
Result.Rotation.Y = 驱动->读取浮点数(address + 4);// Rotation_y
Result.Rotation.Z = 驱动->读取浮点数(address + 8);// Rotation_z
Result.Rotation.W = 驱动->读取浮点数(address + 12);// Rotation_w
Result.Translation.X = 驱动->读取浮点数(address + 16);// /Translation_X
Result.Translation.Y = 驱动->读取浮点数(address + 20);// Translation_y
Result.Translation.Z = 驱动->读取浮点数(address + 24);// Translation_z
Result.Scale3D.X = 驱动->读取浮点数(address + 32);;// Scale_X
Result.Scale3D.Y = 驱动->读取浮点数(address + 36);;// Scale_y
Result.Scale3D.Z = 驱动->读取浮点数(address + 40);;// Scale_z
return Result;
}

// 获取骨骼3d坐标
D3DVector D3dMatrixMultiply(D3DXMATRIX bonematrix, D3DXMATRIX actormatrix) {
D3DVector result;
result.X =
bonematrix._41 * actormatrix._11 + bonematrix._42 * actormatrix._21 +
bonematrix._43 * actormatrix._31 + bonematrix._44 * actormatrix._41;
result.Y =
bonematrix._41 * actormatrix._12 + bonematrix._42 * actormatrix._22 +
bonematrix._43 * actormatrix._32 + bonematrix._44 * actormatrix._42;
result.Z =
bonematrix._41 * actormatrix._13 + bonematrix._42 * actormatrix._23 +
bonematrix._43 * actormatrix._33 + bonematrix._44 * actormatrix._43;
return result;
}

D3DVector getBoneXYZ(long int humanAddr, long int boneAddr, int Part) {
// 获取Bone数据
FTransform1 Bone = ReadFTransform(boneAddr + Part * 48);
// 获取Actor数据
FTransform1 Actor = ReadFTransform(humanAddr);
D3DXMATRIX Bone_Matrix = ToMatrixWithScale(Bone.Rotation, Bone.Translation, Bone.Scale3D);
D3DXMATRIX Component_ToWorld_Matrix =
ToMatrixWithScale(Actor.Rotation, Actor.Translation, Actor.Scale3D);
D3DVector result = D3dMatrixMultiply(Bone_Matrix, Component_ToWorld_Matrix);
return result;
}

double ArcToAngle(double angle) {
return angle * (double)57.29577951308;
}

Vector2A CalcAngle(Vector3A D, Vector3A W) {
float x = W.X - D.X;
float y = W.Y - D.Y;
float z = W.Z - D.Z;
Vector2A PointingAngle;
PointingAngle.X = atan2(y, x) * 180 / PI;
PointingAngle.Y = atan2(z, sqrt(x * x + y * y)) * 180 / PI; 
return PointingAngle;
}
