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
#include <math.h>

#ifndef GAMEHELPER_VECTORSTRUCT_H
#define GAMEHELPER_VECTORSTRUCT_H

struct Vector2 {
    float x;
    float y;

    inline Vector2() : x(0), y(0) {};

    inline Vector2(const float x, const float y) : x(x), y(y) {};


    inline Vector2 operator+(const Vector2 &other) const {
        return Vector2(x + other.x, y + other.y);
    }

    inline Vector2 operator+(const float other) const {
        return Vector2(x + other, y + other);
    }

    inline Vector2 operator-(const Vector2 &other) const {
        return Vector2(x - other.x, y - other.y);
    }

    inline Vector2 operator-(const float other) const {
        return Vector2(x - other, y - other);
    }

    inline Vector2 operator*(const Vector2 &other) const {
        return Vector2(x * other.x, y * other.y);
    }

    inline Vector2 operator*(const float value) const {
        return Vector2(x * value, y * value);
    }

    inline Vector2 operator/(const Vector2 &other) const {
        if (other.x != 0 && other.y != 0) {
            return Vector2(x / other.x, y / other.y);
        }
        return Vector2();
    }

    inline Vector2 operator/(const float value) const {
        if (value != 0) {
            return Vector2(x / value, y / value);
        }
        return Vector2();
    }

    inline Vector2 operator-() const {
        return Vector2(-x, -y);
    }

    inline Vector2 &operator+=(const Vector2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    }


    inline Vector2 &operator-=(const Vector2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    inline Vector2 &operator+=(const float value) {
        x += value;
        y += value;
        return *this;
    }

    inline Vector2 &operator-=(const float value) {
        x -= value;
        y -= value;
        return *this;
    }

    inline Vector2 &operator*=(const float value) {
        x *= value;
        y *= value;
        return *this;
    }

    inline Vector2 &operator*=(const Vector2 &other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    inline Vector2 &operator/=(const float &value) {
        x /= value;
        y /= value;
        return *this;
    }

    inline Vector2 &operator=(const Vector2 &other) {
        x = other.x;
        y = other.y;
        return *this;
    }

    inline bool operator==(const Vector2 &other) const {
        return x == other.x && y == other.y;
    }

    inline bool operator!=(const Vector2 &other) const {
        return x != other.x || y != other.y;
    }

    inline float operator[](int index) const {
        return (&x)[index];
    }

    inline float &operator[](int index) {
        return (&x)[index];
    }

    inline bool NotHaveZero() {
        return x != 0 && y != 0;
    }

    inline void zero() {
        x = y = 0;
    }

    inline float length() {
        return sqrt(x * x + y * y);
    }

};

struct Vector3 {
    float x;
    float y;
    float z;

    inline Vector3() : x(0), y(0), z(0) {}

    inline Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    inline  explicit Vector3(float value) : x(value), y(value), z(value) {}

    inline Vector3 operator+(const Vector3 &other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    inline Vector3 operator+(const float other) const {
        return Vector3(x + other, y + other, z + other);
    }

    inline Vector3 operator-(const Vector3 &other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    inline Vector3 operator-(const float other) const {
        return Vector3(x - other, y - other, z - other);
    }

    inline Vector3 operator*(const Vector3 &other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    inline Vector3 operator*(const float value) const {
        return Vector3(x * value, y * value, z * value);
    }

    inline Vector3 operator/(const float value) const {
        if (value != 0) {
            return Vector3(x / value, y / value, z / value);
        }
        return Vector3();
    }

    inline Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    inline Vector3 &operator+=(const Vector3 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    inline Vector3 &operator-=(const Vector3 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    inline Vector3 &operator+=(const float value) {
        x += value;
        y += value;
        z += value;
        return *this;
    }

    inline Vector3 &operator-=(const float value) {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }

    inline Vector3 &operator*=(const float value) {
        x *= value;
        y *= value;
        z *= value;
        return *this;
    }

    inline Vector3 &operator*=(const Vector3 &other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    inline Vector3 &operator/=(const float &value) {
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    inline Vector3 &operator=(const Vector3 &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    inline bool operator==(const Vector3 &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    inline bool operator!=(const Vector3 &other) const {
        return x != other.x || y != other.y || z != other.z;
    }

    inline float operator[](int index) const {
        return (&x)[index];
    }

    inline float &operator[](int index) {
        return (&x)[index];
    }

    inline void Zero() {
        x = y = z = 0;
    }

    inline float length() const {
        return sqrt(x * x + y * y + z * z);
    }

    inline bool isValid() const {
        return x != 0 && y != 0 && z != 0 && !isnan(x) && !isnan(y) && !isnan(z);
    }

    static inline float dot(const Vector3 &a, const Vector3 &b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static inline bool inRange(const Vector3 &target, const Vector3 &min, const Vector3 &max) {
        return target.x > min.x && target.x < max.x && target.y > min.y && target.y < max.y &&
               target.z > min.z && target.z < max.z;
    }
};

struct Vector4 {
    float x;
    float y;
    float z;
    float w;

    inline Vector4() : x(0), y(0), z(0), w(0) {}

    inline Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    inline explicit Vector4(float value) : x(value), y(value), z(value), w(value) {}

    inline Vector4 operator+(const Vector4 &other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    inline Vector4 operator+(const float other) const {
        return Vector4(x + other, y + other, z + other, w + other);
    }

    inline Vector4 operator-(const Vector4 &other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    inline Vector4 operator-(const float other) const {
        return Vector4(x - other, y - other, z - other, w - other);
    }

    inline Vector4 operator*(const float value) const {
        return Vector4(x * value, y * value, z * value, w * value);
    }

    inline Vector4 operator*(const Vector4 &other) const {
        return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
    }

    inline Vector4 operator/(const float value) const {
        if (value != 0) {
            return Vector4(x / value, y / value, z / value, w / value);
        }
        return Vector4();
    }


    inline Vector4 operator-() const {
        return Vector4(-x, -y, -z, -w);
    }

    inline Vector4 &operator+=(const Vector4 &other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    inline Vector4 &operator-=(const Vector4 &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    inline Vector4 &operator+=(const float value) {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }

    inline Vector4 &operator-=(const float value) {
        x -= value;
        y -= value;
        z -= value;
        w -= value;
        return *this;
    }

    inline Vector4 &operator*=(const float value) {
        x *= value;
        y *= value;
        z *= value;
        w *= value;
        return *this;
    }

    inline Vector4 &operator*=(const Vector4 &other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    }

    inline Vector4 &operator/=(const float value) {
        x /= value;
        y /= value;
        z /= value;
        w /= value;
        return *this;
    }

    inline Vector4 &operator=(const Vector4 &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    inline bool operator==(const Vector4 &other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    inline bool operator!=(const Vector4 &other) const {
        return x != other.x || y != other.y || z != other.z || w != other.w;
    }

    inline float operator[](int index) const {
        return (&x)[index];
    }

    inline float &operator[](int index) {
        return (&x)[index];
    }

    inline void Zero() {
        x = y = z = w = 0;
    }

    inline bool NotHaveZero() {
        return x != 0 && y != 0 && z != 0 && w != 0;
    }

    inline float length() {
        return sqrt(x * x + y * y + z * z + w * w);
    }

};

inline Vector4 vec4_mult(const Vector4 &vec, const Vector4 &vec2) {
    return vec * vec2;
}

inline Vector4 vec4_piu(const Vector4 &vec, const Vector4 &vec2) {
    return vec + vec2;
}

inline Vector4 vec4_meno(const Vector4 &vec, const Vector4 &vec2) {
    return vec - vec2;
}

inline float q2djl(const Vector2 &vec, const Vector2 &vec2) {
    return (vec - vec2).length();
}

inline float q3djl(const Vector3 &vec, const Vector3 &vec2) {
    return (vec - vec2).length();
}

inline bool isInRange(const Vector2 &target, const Vector2 &min, const Vector2 &max) {
    return target.x > min.x && target.x < max.x && target.y > min.y && target.y < max.y;
}

inline bool isInRange(const Vector3 &target, const Vector3 &min, const Vector3 &max) {
    return target.x > min.x && target.x < max.x && target.y > min.y && target.y < max.y && target.z > min.z &&
           target.z < max.z;
}

struct _Int2 {
    int x;
    int y;
};

struct _Int3 {
    int x;
    int y;
    int z;
};


#endif