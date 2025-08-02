#include "辅助类.h"
#include "map"

class 骨骼
{
public:
  std::unordered_map<std::string, std::string> BossName;
  std::vector<std::string> BossArray;
  Kernel *读写;

  骨骼(Kernel *读写) : 读写(读写)
  {
    BossName = {
        {"Pawn_Escape_RD_Grenade_C", "巡卫长·玄铁"},
        {"Pawn_Escape_RD_RoyalGuards_C", "影卫·银星"},
        {"Pawn_Escape_Boss_Robocop_C", "V-34机械警"},
        {"Pawn_Escape_BOSS_Claws_C", "钢爪·安德烈"},
        {"Pawn_Escape_RD_SupplyBoss_C", "辎重使·墨守"},
    };
  }

  bool isBoss(char &className)
  {
    for (size_t i = 0; i < BossArray.size(); i++)
    {
      if (strstr((char *)className, BossArray[i].c_str()))
        return true;
    }
    return false;
  }

  bool getBossName(char &className, std::string &name)
  {
    auto point = this->BossName.find((char *)className);
    if (point != this->BossName.end())
    {
      name = point->second;
      return true;
    }
    return false;
  }

  FTransform getBone(uintptr_t addr)
  {
    FTransform transform;
    读写->readv(addr, &transform, sizeof(FTransform));
    return transform;
  }

  D3DVector MarixToVector(FMatrix matrix)
  {
    return D3DVector{matrix.M[3][0], matrix.M[3][1], matrix.M[3][2]};
  }

  FMatrix MatrixMulti(const FMatrix &m1, const FMatrix &m2)
  {
    FMatrix matrix;
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        matrix.M[i][j] = 0;
        for (int k = 0; k < 4; k++)
        {
          matrix.M[i][j] += m1.M[i][k] * m2.M[k][j];
        }
      }
    }
    return matrix;
  }

  FMatrix TransformToMatrix(FTransform transform)
  {
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

  D3DXMATRIX ToMatrixWithScale(D3DXVECTOR4 Rotation, D3DVector Translation, D3DVector Scale3D)
  {
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

  FTransform1 ReadFTransform(long int address)
  {
    FTransform1 Result;
    Result.Rotation.X = 读写->getFloat(address);         // Rotation_X
    Result.Rotation.Y = 读写->getFloat(address + 4);     // Rotation_y
    Result.Rotation.Z = 读写->getFloat(address + 8);     // Rotation_z
    Result.Rotation.W = 读写->getFloat(address + 12);    // Rotation_w
    Result.Translation.X = 读写->getFloat(address + 16); // /Translation_X
    Result.Translation.Y = 读写->getFloat(address + 20); // Translation_y
    Result.Translation.Z = 读写->getFloat(address + 24); // Translation_z
    Result.Scale3D.X = 读写->getFloat(address + 32);
    ; // Scale_X
    Result.Scale3D.Y = 读写->getFloat(address + 36);
    ; // Scale_y
    Result.Scale3D.Z = 读写->getFloat(address + 40);
    ; // Scale_z
    return Result;
  }

  // 获取骨骼3d坐标
  D3DVector D3dMatrixMultiply(D3DXMATRIX bonematrix, D3DXMATRIX actormatrix)
  {
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

  D3DVector getBoneXYZ(long int humanAddr, long int boneAddr, int Part)
  {
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

  D2DVector getPointingAngle(long int SelfAddress, float object_x, float object_y, float object_z, float Self_x, float Self_y, float Self_z, D3DVector Movement, float distance, float 预判力度)
  {
    D2DVector PointingAngle;
    float bulletVelocity = 读写->getFloat(读写->getPtr64(读写->getPtr64(SelfAddress + 0xf18) + 0x9b8) + 0x1334); // 子弹速度
    float FlyTime = distance / (bulletVelocity * 0.01f) * 预判力度;

    // float FlyTime = (distance >= 60) ? (distance / (bulletVelocity * 0.01f) * 预判力度) : (distance / (bulletVelocity * 0.0055f) * 预判力度);

    float DropM = 500.0f * FlyTime * FlyTime;
    float zbcx = object_x + (Movement.X * FlyTime) - Self_x;
    float zbcy = object_y + (Movement.Y * FlyTime) - Self_y;
    float zbcz = object_z + (Movement.Z * FlyTime * FlyTime) - Self_z;
    long int pfg = sqrt((zbcx * zbcx) + (zbcy * zbcy));
    PointingAngle.X = atan2(zbcy, zbcx) * 180 / 3.141592653589793238;
    PointingAngle.Y = atan2(zbcz, pfg) * 180 / 3.141592653589793238;
    return PointingAngle;
  }

  void 更新骨骼数据(uintptr_t MeshAddress, uintptr_t Bone, D3DVector (&骨骼坐标)[17], int Bonecount, int Team, char *类名)
  {
    FTransform meshtrans = getBone(MeshAddress);
    FMatrix c2wMatrix = TransformToMatrix(meshtrans);
    // std::vector<int> boneIndices = {5, 4, 1, 11, (Bonecount == 68) ? 33 : 32, 12, (Bonecount == 68) ? 34 : 33, (Bonecount == 68) ? 13 : 63, (Bonecount == 68) ? 35 : 62, (Bonecount == 68) ? 55 : 53, (Bonecount == 68) ? 59 : 56, (Bonecount == 68) ? 56 : 53, (Bonecount == 68) ? 60 : 57, (Bonecount == 68) ? 57 : 54, (Bonecount == 68) ? 61 : 58};

    std::vector<int> boneIndices;
    bool isboss = isBoss(*类名);
    if (!isboss)
    {

      if (Bonecount == 68)
      {
        boneIndices = {5, 4, 1, 11, 33, 12, 34, 13, 35, 55, 59, 56, 60, 57, 61};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 70)
      {
        boneIndices = {5, 4, 1, 6, 34, 7, 35, 8, 36, 55, 59, 56, 60, 57, 61};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 72)
      {
        boneIndices = {5, 4, 1, 12, 34, 13, 35, 14, 36, 57, 61, 58, 62, 59, 63};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (strstr(类名, "BPPawn_Escape_BOSS_Claws") != 0 && Bonecount == 65)
      {
        boneIndices = {5, 4, 0, 6, 27, 7, 28, 8, 29, 50, 57, 51, 58, 52, 59};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 63)
      {
        boneIndices = {5, 4, 0, 8, 30, 9, 31, 10, 32, 50, 54, 51, 55, 52, 56};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 64)
      {
        boneIndices = {5, 4, 0, 7, 29, 8, 30, 9, 31, 51, 57, 52, 58, 53, 59};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 38)
      {
        boneIndices = {5, 4, 0, 7, 17, 9, 19, 11, 21, 27, 34, 28, 35, 30, 36};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 30)
      {
        boneIndices = {5, 4, 0, 9, 14, 10, 15, 11, 16, 18, 22, 19, 23, 20, 24};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 26)
      {
        boneIndices = {5, 4, 0, 13, 6, 14, 7, 15, 8, 21, 18, 22, 19, 23, 20};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 27)
      {
        boneIndices = {5, 4, 0, 7, 10, 8, 11, 9, 12, 14, 18, 15, 19, 16, 20};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 46)
      {
        boneIndices = {5, 4, 0, 21, 8, 22, 9, 23, 10, 35, 40, 36, 41, 38, 44};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 42)
      {
        boneIndices = {16, 15, 0, 20, 31, 21, 32, 22, 33, 3, 8, 4, 9, 5, 10};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 76)
      {
        boneIndices = {5, 4, 0, 7, 27, 8, 28, 9, 29, 48, 52, 49, 53, 50, 54};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (Bonecount == 61)
      {
        boneIndices = {5, 4, 0, 6, 27, 7, 28, 8, 29, 48, 52, 49, 53, 50, 54};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else
      {
        boneIndices = {5, 4, 1, 11, 32, 12, 33, 63, 62, 53, 56, 53, 57, 54, 58};
      }
    }
    else
    {
      std::string name;
      getBossName(*类名, name);
      if (name == "钢爪·安德烈")
      {
        boneIndices = {5, 4, 1, 28, 7, 29, 8, 30, 9, 57, 50, 58, 51, 59, 52};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
      else if (name == "巡卫长·玄铁" || name == "V-34机械警" || name == "辎重使·墨守" || name == "影卫·银星")
      {
        boneIndices = {5, 4, 1, 28, 7, 29, 8, 30, 9, 52, 48, 53, 49, 54, 50};
        // 头,胸,盆骨,左肩膀,右肩膀,左手肘,右手肘,左手腕,右手腕,左大腿,右大腿,左膝盖,右膝盖,左脚腕,右脚腕
      }
    }

    for (size_t i = 0; i < boneIndices.size(); i++)
    {
      FTransform boneTrans = getBone(Bone + boneIndices[i] * 48);
      FMatrix boneMatrix = TransformToMatrix(boneTrans);
      骨骼坐标[i] = MarixToVector(MatrixMulti(boneMatrix, c2wMatrix));
    }
    骨骼坐标[0].Z += 7; // 脖子长度
    if (骨骼坐标[13].Z < 骨骼坐标[14].Z)
    {
      骨骼坐标[14].Z = 骨骼坐标[13].Z;
    }
  }
};