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
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <cmath>
#include <linux/input.h>
#include <linux/uinput.h>

#include "src/辅助类.h"

#include "imgui.h"

#define maxE 5
#define maxF 10
#define UNGRAB 0
#define GRAB 1

int Touch_ID;
int Touch_I;
int Touch_I_bak;
int Touch_Global_SLOT;
int Touch_Temporary_SLOT;
int Touch_Temporary_SLOT_Bak;
Vector2 Touch_Clicks;

extern 绘制 绘制;

bool other_touch;

static uint32_t orientation = 0;
static float screenHeight = 0, screenWidth = 0;

struct touchObj {
  bool isDown = false;
  bool isTmpDown = false;
  int x = 0;
  int y = 0;
  int id = 0;
  int size1 = 0;
  int size2 = 0;
  int size3 = 0;
};
struct targ {
  int fdNum;
  float S2TX;
  float S2TY;
};
static struct {
  input_event downEvent[2]{{{}, EV_KEY, BTN_TOUCH,       1},
    {{}, EV_KEY, BTN_TOOL_FINGER, 1}};
  input_event event[512]{0};
} input;

static targ targF[maxE];

static touchObj Finger[maxE][maxF];

static int fdNum = 0, origfd[maxE], nowfd;

static float scale_x, scale_y;

static bool Touch_initialized = false;

static bool Touch_readOnly = false;

static bool checkDeviceIsTouch(int fd);
static void genRandomString(char *string, int length) {
  int flag, i;
  srand((unsigned) time(NULL) + length);
  for (i = 0; i < length - 1; i++) {
    flag = rand() % 3;
    switch (flag) {
      case 0:
      string[i] = 'A' + rand() % 26;
      break;
      case 1:
      string[i] = 'a' + rand() % 26;
      break;
      case 2:
      string[i] = '0' + rand() % 10;
      break;
      default:
      string[i] = 'x';
      break;
    }
  }
  string[length - 1] = '\0';
}

Vector2 Touch2Screen(const Vector2 &coord) {
  float x = coord.x, y = coord.y;
  float xt = x / scale_x;
  float yt = y / scale_y;
  
  if (other_touch) {
    switch (orientation) {
      case 1:
      x = xt;
      y = yt;
      break;
      case 2:
      y = yt;
      x = screenHeight - xt;
      break;
      case 3:
      x = screenHeight - xt;
      y = screenWidth - yt;
      break;
      default:
      y = xt;
      x = screenHeight - yt;
      break;
    }
  } else {
    switch (orientation) {
      case 1:
      x = yt;
      y = screenHeight - xt;
      break;
      case 2:
      x = screenHeight - xt;
      y = screenWidth - yt;
      break;
      case 3:
      y = xt;
      x = screenWidth - yt;
      break;
      default:
      x = xt;
      y = yt;
      break;
    }
  }
  return {x, y};
}

static void Upload() {
  static bool bTouch = false;
  static bool isFirstDown = true;
  while (bTouch);
  bTouch = true;
  int tmpCnt = 0, tmpCnt2 = 0, i, j;
  for (i = 0; i < fdNum; i++) {
    for (j = 0; j < maxF; j++) {
      if (Finger[i][j].isDown) {
        if (tmpCnt2++ > 10) {
          goto finish;
        }
        input.event[tmpCnt].type = EV_ABS;
        input.event[tmpCnt].code = ABS_X;
        input.event[tmpCnt].value = Finger[i][j].x;
        tmpCnt++;
        
        input.event[tmpCnt].type = EV_ABS;
        input.event[tmpCnt].code = ABS_Y;
        input.event[tmpCnt].value = Finger[i][j].y;
        tmpCnt++;
        
        input.event[tmpCnt].type = EV_ABS;
        input.event[tmpCnt].code = ABS_MT_POSITION_X;
        input.event[tmpCnt].value = Finger[i][j].x;
        tmpCnt++;
        
        input.event[tmpCnt].type = EV_ABS;
        input.event[tmpCnt].code = ABS_MT_POSITION_Y;
        input.event[tmpCnt].value = Finger[i][j].y;
        tmpCnt++;
        
        input.event[tmpCnt].type = EV_ABS;
        input.event[tmpCnt].code = ABS_MT_TRACKING_ID;
        input.event[tmpCnt].value = Finger[i][j].id;
        tmpCnt++;
        
        if (Finger[i][j].size1)
        {
          input.event[tmpCnt].type = EV_ABS;
          input.event[tmpCnt].code = ABS_MT_TOUCH_MAJOR;
          input.event[tmpCnt].value = Finger[i][j].size1;
          tmpCnt++;
        }
        if (Finger[i][j].size2)
        {
          input.event[tmpCnt].type = EV_ABS;
          input.event[tmpCnt].code = ABS_MT_WIDTH_MAJOR;
          input.event[tmpCnt].value = Finger[i][j].size2;
          tmpCnt++;
        }
        if (Finger[i][j].size3)
        {
          input.event[tmpCnt].type = EV_ABS;
          input.event[tmpCnt].code = ABS_MT_TOUCH_MINOR;
          input.event[tmpCnt].value = Finger[i][j].size3;
          tmpCnt++;
        }
        
        input.event[tmpCnt].type = EV_SYN;
        input.event[tmpCnt].code = SYN_MT_REPORT;
        input.event[tmpCnt].value = 0;
        tmpCnt++;
      }
    }
  }
  finish:
  bool is = false;
  if (tmpCnt == 0) {
    input.event[tmpCnt].type = EV_SYN;
    input.event[tmpCnt].code = SYN_MT_REPORT;
    input.event[tmpCnt].value = 0;
    tmpCnt++;
    if (!isFirstDown) {
      isFirstDown = true;
      input.event[tmpCnt].type = EV_KEY;
      input.event[tmpCnt].code = BTN_TOUCH;
      input.event[tmpCnt].value = 0;
      tmpCnt++;
      input.event[tmpCnt].type = EV_KEY;
      input.event[tmpCnt].code = BTN_TOOL_FINGER;
      input.event[tmpCnt].value = 0;
      tmpCnt++;
    }
  } else {
    is = true;
  }
  input.event[tmpCnt].type = EV_SYN;
  input.event[tmpCnt].code = SYN_REPORT;
  input.event[tmpCnt].value = 0;
  tmpCnt++;
  
  if (is && isFirstDown) {
    isFirstDown = false;
    write(nowfd, &input, sizeof(struct input_event) * (tmpCnt + 2));
  } else {
    write(nowfd, input.event, sizeof(struct input_event) * tmpCnt);
  }
  
  bTouch = false;
}

static void *TypeA(void *arg) {
  targ tmp = *(targ *) arg;
  int i = tmp.fdNum;
  float S2TX = tmp.S2TX;
  float S2TY = tmp.S2TY;
  int latest = 0;
  input_event inputEvent[64]{0};
  
  timer touchFPS;
  touchFPS.SetFps(800);
  touchFPS.AotuFPS_init();
  touchFPS.setAffinity();
  
  while (Touch_initialized) {
    ImGuiIO &io = ImGui::GetIO();
    auto readSize = (int32_t) read(origfd[i], inputEvent, sizeof(inputEvent));
    if (readSize <= 0 || (readSize % sizeof(input_event)) != 0) {
      continue;
    }
    size_t count = size_t(readSize) / sizeof(input_event);
    for (size_t j = 0; j < count; j++) {
      input_event &ie = inputEvent[j];
      if (ie.type == EV_ABS) {
        if (ie.code == ABS_MT_SLOT) {
          latest = ie.value;
          Touch_Temporary_SLOT = ie.value;
          Touch_I++;
          continue;
        }
        if (ie.code == ABS_MT_TRACKING_ID) {
          if (ie.value == -1) {
            Finger[i][latest].isDown = false;
            io.MouseDown[0] = false;
            Touch_Temporary_SLOT_Bak = Touch_Temporary_SLOT;
            Touch_ID = -1;
          } else {
            Finger[i][latest].id = (i * 2 + 1) * maxF + latest;
            Touch_ID = ie.value;
            Touch_I_bak = Touch_I;
            Touch_Temporary_SLOT_Bak = Touch_Temporary_SLOT;
            Finger[i][latest].isDown = true;
            io.MouseDown[0] = true;
          }
          Touch_I++;
          continue;
        }
        if (ie.code == ABS_MT_POSITION_X) {
          Finger[i][latest].id = (i * 2 + 1) * maxF + latest;
          Finger[i][latest].x = (int) (ie.value * S2TX);
          if(Touch_I == Touch_I_bak+1) {
            Touch_Clicks.x = (float) ie.value * S2TX;
          }
          Touch_I++;
          Finger[i][latest].isTmpDown = true;
          continue;
        }
        if (ie.code == ABS_MT_POSITION_Y) {
          Finger[i][latest].id = (i * 2 + 1) * maxF + latest;
          Finger[i][latest].y = (int) (ie.value * S2TY);
          
          if(Touch_I == Touch_I_bak+2)
          {
            Touch_Clicks.y = (float) ie.value * S2TY;
            Touch_Clicks = Touch2Screen(Touch_Clicks);
          }
          Touch_I++;
          Finger[i][latest].isTmpDown = true;
          continue;
        }
        if (ie.code == ABS_MT_TOUCH_MAJOR)
        {
          Finger[i][latest].id = (i * 2 + 1) * maxF + latest;
          Finger[i][latest].size1 = ie.value;
          Finger[i][latest].isTmpDown = true;
          continue;
        }
        if (ie.code == ABS_MT_WIDTH_MAJOR)
        {
          Finger[i][latest].id = (i * 2 + 1) * maxF + latest;
          Finger[i][latest].size2 = ie.value;
          Finger[i][latest].isTmpDown = true;
          continue;
        }
        if (ie.code == ABS_MT_TOUCH_MINOR)
        {
          Finger[i][latest].id = (i * 2 + 1) * maxF + latest;
          Finger[i][latest].size3 = ie.value;
          Finger[i][latest].isTmpDown = true;
          continue;
        }
        
      }
      
      
      float x = Finger[i][latest].x, y = Finger[i][latest].y;
      float xt = x / scale_x;
      float yt = y / scale_y;
      if (other_touch) {
        switch (orientation) {
          case 1:
          x = xt;
          y = yt;
          break;
          case 2:
          y = yt;
          x = screenHeight - xt;
          break;
          case 3:
          x = screenHeight - xt;
          y = screenWidth - yt;
          break;
          default:
          y = xt;
          x = screenHeight - yt;
          break;
        }
      } else {
        switch (orientation) {
          case 1:
          x = yt;
          y = screenHeight - xt;
          break;
          case 2:
          x = screenHeight - xt;
          y = screenWidth - yt;
          break;
          case 3:
          y = xt;
          x = screenWidth - yt;
          break;
          default:
          x = xt;
          y = yt;
          break;
        }
      }
      io.MousePos = {x, y};
      
      
      if (io.MousePos.x <= 绘制.Pos.x + 绘制.winWidth && io.MousePos.y <= 绘制.Pos.y + 绘制.winHeith && io.MousePos.x >= 绘制.Pos.x && io.MousePos.y >= 绘制.Pos.y)
      {
        Finger[i][latest].isDown = false;
        Finger[i][latest].isTmpDown = false;
      }
      
      if (ie.type == EV_SYN)
      {
        if (ie.code == SYN_REPORT)
        {
          if (Finger[i][latest].isTmpDown)
          Upload();
          continue;
        }
        continue;
      }
      
      
    }
    touchFPS.SetFps((int)绘制.自瞄.触摸采样率);
    touchFPS.AotuFPS();
  }
  return nullptr;
}


bool Touch_Init(int w, int h, uint32_t orientation_, bool readOnly) {
  char temp[128];
  DIR *dir = opendir("/dev/input/");
  dirent *ptr = NULL;
  int eventCount = 0;
  while ((ptr = readdir(dir)) != NULL) {
    if (strstr(ptr->d_name, "event"))
    eventCount++;
  }
  struct input_absinfo abs, absX[maxE], absY[maxE];
  int fd, i, tmp1, tmp2;
  int screenX, screenY, minCnt = eventCount + 1;
  fdNum = 0;
  for (i = 0; i <= eventCount; i++) {
    sprintf(temp, "/dev/input/event%d", i);
    fd = open(temp, O_RDWR);
    if (fd < 0) {
      continue;
    }
    if (checkDeviceIsTouch(fd)) {
      tmp1 = ioctl(fd, EVIOCGABS(ABS_MT_POSITION_X), &absX[fdNum]);
      tmp2 = ioctl(fd, EVIOCGABS(ABS_MT_POSITION_Y), &absY[fdNum]);
      if (tmp1 == 0 && tmp2 == 0) {
        origfd[fdNum] = fd;
        if (!readOnly) {
          ioctl(fd, EVIOCGRAB, GRAB);
        }
        if (i < minCnt) {
          screenX = absX[fdNum].maximum;
          screenY = absY[fdNum].maximum;
          minCnt = i;
        }
        fdNum++;
        if (fdNum >= maxE)
        break;
      }
    } else {
      close(fd);
    }
  }
  
  if (minCnt > eventCount) {
    puts("获取屏幕驱动失败");
    return false;
  }
  
  if (!readOnly) {
    struct uinput_user_dev ui_dev;
    nowfd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (nowfd <= 0) {
      return false;
    }
    
    int string_len = rand() % 10 + 5;
    char string[string_len];
    memset(&ui_dev, 0, sizeof(ui_dev));
    
    genRandomString(string, string_len);
    strncpy(ui_dev.name, string, UINPUT_MAX_NAME_SIZE);
    
    ui_dev.id.bustype = 0;
    ui_dev.id.vendor = rand() % 10 + 5;
    ui_dev.id.product = rand() % 10 + 5;
    ui_dev.id.version = rand() % 10 + 5;
    
    ioctl(nowfd, UI_SET_PROPBIT, INPUT_PROP_DIRECT);
    
    ioctl(nowfd, UI_SET_EVBIT, EV_ABS);
    ioctl(nowfd, UI_SET_ABSBIT, ABS_X);
    ioctl(nowfd, UI_SET_ABSBIT, ABS_Y);
    ioctl(nowfd, UI_SET_ABSBIT, ABS_MT_POSITION_X);
    ioctl(nowfd, UI_SET_ABSBIT, ABS_MT_POSITION_Y);
    ioctl(nowfd, UI_SET_ABSBIT, ABS_MT_TRACKING_ID);
    ioctl(nowfd, UI_SET_ABSBIT, ABS_MT_TOUCH_MAJOR);
    ioctl(nowfd, UI_SET_ABSBIT, ABS_MT_WIDTH_MAJOR);
    ioctl(nowfd, UI_SET_ABSBIT, ABS_MT_TOUCH_MINOR);
    ioctl(nowfd, UI_SET_EVBIT, EV_SYN);
    ioctl(nowfd, UI_SET_EVBIT, EV_KEY);
    ioctl(nowfd, UI_SET_KEYBIT, BTN_TOOL_FINGER);
    ioctl(nowfd, UI_SET_KEYBIT, BTN_TOUCH);
    
    // 设置设备属性，禁止其他程序访问
    ioctl(nowfd, UI_SET_PROPBIT, INPUT_PROP_DIRECT);
    
    
    
    genRandomString(string, string_len);
    ioctl(nowfd, UI_SET_PHYS, string);
    
    sprintf(temp, "/dev/input/event%d", minCnt);
    fd = open(temp, O_RDWR);
    if (fd) {
      struct input_id id;
      if (!ioctl(fd, EVIOCGID, &id)) {
        ui_dev.id.bustype = id.bustype;
        ui_dev.id.vendor = id.vendor;
        ui_dev.id.product = id.product;
        ui_dev.id.version = id.version;
      }
      uint8_t *bits = NULL;
      ssize_t bits_size = 0;
      int res, j, k;
      while (1) {
        res = ioctl(fd, EVIOCGBIT(EV_KEY, bits_size), bits);
        if (res < bits_size)
        break;
        bits_size = res + 16;
        bits = (uint8_t *) realloc(bits, bits_size * 2);
      }
      for (j = 0; j < res; j++) {
        for (k = 0; k < 8; k++)
        if (bits[j] & 1 << k) {
          if (j * 8 + k == BTN_TOUCH || j * 8 + k == BTN_TOOL_FINGER)
          continue;
          ioctl(nowfd, UI_SET_KEYBIT, j * 8 + k);
        }
      }
      free(bits);
    }
    ui_dev.absmin[ABS_MT_POSITION_X] = 0;
    ui_dev.absmax[ABS_MT_POSITION_X] = screenX;
    ui_dev.absmin[ABS_MT_POSITION_Y] = 0;
    ui_dev.absmax[ABS_MT_POSITION_Y] = screenY;
    ui_dev.absmin[ABS_X] = 0;
    ui_dev.absmax[ABS_X] = screenX;
    ui_dev.absmin[ABS_Y] = 0;
    ui_dev.absmax[ABS_Y] = screenY;
    ui_dev.absmin[ABS_MT_TOUCH_MAJOR] = 0;
    ui_dev.absmax[ABS_MT_TOUCH_MAJOR] = 255;
    ui_dev.absmin[ABS_MT_WIDTH_MAJOR] = 0;
    ui_dev.absmax[ABS_MT_WIDTH_MAJOR] = 255;
    ui_dev.absmin[ABS_MT_TOUCH_MINOR] = 0;
    ui_dev.absmax[ABS_MT_TOUCH_MINOR] = 255;
    ui_dev.absmin[ABS_MT_TRACKING_ID] = 0;
    ui_dev.absmax[ABS_MT_TRACKING_ID] = 65535;
    write(nowfd, &ui_dev, sizeof(ui_dev));
    
    if (ioctl(nowfd, UI_DEV_CREATE)) {
      return false;
    }
    //ioctl(nowfd, UI_DEV_DESTROY);//创建成功后尝试注销
    
  }
  Touch_initialized = true;
  Touch_readOnly = readOnly;
  
  pthread_t t;
  for (i = 0; i < fdNum; i++) {
    targF[i].fdNum = i;
    targF[i].S2TX = (float) screenX / (float) absX[i].maximum;
    targF[i].S2TY = (float) screenY / (float) absY[i].maximum;
    pthread_create(&t, NULL, TypeA, &targF[i]);
  }
  fdNum++;
  ::screenWidth = w;
  ::screenHeight = h,
  ::orientation = orientation_;
  if (::orientation == 1 || ::orientation == 3) {
    ::scale_x = (float) screenX / h;
    ::scale_y = (float) screenY / w;
  } else {
    ::scale_x = (float) screenX / w;
    ::scale_y = (float) screenY / h;
  }
  system("chmod 000 -R /proc/bus/input/*");
  return true;
}
void UpdateScreenData(int w, int h, uint32_t orientation_) {
  ::screenWidth = w;
  ::screenHeight = h,
  ::orientation = orientation_;
}
static bool checkDeviceIsTouch(int fd) {
  uint8_t *bits = NULL;
  ssize_t bits_size = 0;
  int res, j, k;
  bool itmp = false, itmp2 = false, itmp3 = false;
  struct input_absinfo abs{};
  while (true) {
    res = ioctl(fd, EVIOCGBIT(EV_ABS, bits_size), bits);
    if (res < bits_size)
    break;
    bits_size = res + 16;
    bits = (uint8_t *) realloc(bits, bits_size * 2);
  }
  for (j = 0; j < res; j++) {
    for (k = 0; k < 8; k++)
    if (bits[j] & 1 << k && ioctl(fd, EVIOCGABS(j * 8 + k), &abs) == 0) {
      if (j * 8 + k == ABS_MT_SLOT) {
        itmp = true;
        continue;
      }
      if (j * 8 + k == ABS_MT_POSITION_X) {
        itmp2 = true;
        continue;
      }
      if (j * 8 + k == ABS_MT_POSITION_Y) {
        itmp3 = true;
        continue;
      }
    }
  }
  free(bits);
  return itmp && itmp2 && itmp3;
}

void Touch_Down(float x, float y) {
  touchObj &touch = Finger[0][9];
  touch.id = 8;
  touch.x = (int) (x * scale_x);
  touch.y = (int) (y * scale_y);
  touch.isDown = true;
  touch.size1 = 8;
  touch.size2 = 8;
  touch.size3 = 8;
  Upload();
}
void Touch_Move(float x, float y) {
  Touch_Down(x, y);
}
void Touch_Up() {
  //printf("测试 %d / %d\n",maxE,maxF);
  touchObj &touch = Finger[0][9];
  touch.isDown = false;
  Upload();
  Upload();
}