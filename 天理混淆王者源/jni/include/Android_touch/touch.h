#ifndef NATIVESURFACE_TOUCH_H
#define NATIVESURFACE_TOUCH_H
#include <android/input.h>
#include <android/keycodes.h>
#include <cstring>
#include <cstdio>
#include <malloc.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sys/system_properties.h>
#include <linux/input.h>
#include <linux/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <linux/uinput.h>
#include <imgui.h>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <dirent.h>
#include "draw.h"
struct Vector2 {
    Vector2(float x, float y) {
        this->x = x;
        this->y = y;
    }
    Vector2() {}
    float x;
    float y;
    bool operator == (const Vector2 &t) const {
        if ( this->x == t.x && this->y == t.y ) return true;
        return false;
    }
    bool operator != (const Vector2 &t) const {
        if ( this->x != t.x || this->y != t.y ) return true;
        return false;
    }
};
using namespace std;
#define BITS_PER_LONG (sizeof(long) * 8)
#define test_bit(array, bit)    ((array[bit / BITS_PER_LONG] >> bit % BITS_PER_LONG) & 1)
#define NBITS(x)             ((((x)-1)/BITS_PER_LONG)+1)
int isa_event_device(const struct dirent* dir);
std::string getTouchScreenDevice();
Vector2 rotatePointx(uint32_t orientation, float x, float y, int32_t displayWidth = 0,int32_t displayHeight = 0);
Vector2 getTouchScreenDimension(int fd);
void touch_config();
void Init_touch_config();
void Touch_Init(int px, int py);
void Touch_Down(int x, int y);
void Touch_Move(int x, int y);
void Touch_Up();
#endif
