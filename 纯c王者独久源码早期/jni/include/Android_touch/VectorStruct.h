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


inline bool isInRange(const Vector2 &target, const Vector2 &min, const Vector2 &max) {
    return target.x > min.x && target.x < max.x && target.y > min.y && target.y < max.y;
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