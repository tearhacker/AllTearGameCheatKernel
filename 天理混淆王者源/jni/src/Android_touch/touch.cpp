#include <touch.h>

#define maxF 10
#define UNGRAB 0
#define GRAB 1
#define CMD_RESULT_BUF_SIZE 1024
struct touchObj {
    bool isDown = false;
    int x = 0;
    int y = 0;
};

float touch_s;

struct touchObj Finger[maxF];

static pthread_t touchloop;

Vector2 touch_screen_size;

static struct input_event event[128];
int origfd, fd;
int tnum = 9;

void Upload()
{
    memset(event, 0, sizeof(struct input_event) * 128);
    int32_t tmpCnt = 0;
    for (int i = 0; i <= maxF - 1; i++)
    {
        if (Finger[i].isDown)
        {
            event[tmpCnt].type = EV_ABS;
            event[tmpCnt].code = ABS_MT_POSITION_X;
            event[tmpCnt].value = Finger[i].x;
            tmpCnt++;

            event[tmpCnt].type = EV_ABS;
            event[tmpCnt].code = ABS_MT_POSITION_Y;
            event[tmpCnt].value = Finger[i].y;
            tmpCnt++;

            event[tmpCnt].type = EV_SYN;
            event[tmpCnt].code = SYN_MT_REPORT;
            event[tmpCnt].value = 0;
            tmpCnt++;
        }
    }
    if (tmpCnt == 0)
    {
        event[tmpCnt].type = EV_SYN;
        event[tmpCnt].code = SYN_MT_REPORT;
        event[tmpCnt].value = 0;
        tmpCnt++;
    }

    event[tmpCnt].type = EV_SYN;
    event[tmpCnt].code = SYN_REPORT;
    event[tmpCnt].value = 0;
    tmpCnt++;

    write(fd, event, sizeof(struct input_event) * tmpCnt);
}

void *TypeA(void *) {
    struct input_event ie{};
    int latest = 0;
    struct input_event key{};
    while (read(origfd, &ie, sizeof(struct input_event))) {
        ImGuiIO& io = ImGui::GetIO();           
        if (ie.code == ABS_MT_SLOT) {
            latest = ie.value;
        }
        if (ie.code == ABS_MT_TRACKING_ID) {
            if (ie.value == -1) {
                Finger[latest].isDown = false;
                if (g_Initialized)
                {           
                    io.MouseDown[0] = false;
                }
            } else {
                Finger[latest].isDown = true;
                if (g_Initialized)
                {          
                    io.MouseDown[0] = true;
                }
            }
        }
        if (ie.code == ABS_MT_POSITION_X) {
            Finger[latest].x = ie.value;
        }
        if (ie.code == ABS_MT_POSITION_Y) {
            Finger[latest].y = ie.value;
        }
        if (ie.code == SYN_REPORT) {
            Upload();
        }
        if(g_Initialized){
            struct input_event oneevent;                    
            Vector2 point = rotatePointx(Orientation,(float)Finger[latest].x,(float)Finger[latest].y,touch_screen_size.x,touch_screen_size.y);
            io.MousePos = ImVec2((point.x * full_screen.ScreenX) / touch_screen_size.x,(point.y * full_screen.ScreenY) / touch_screen_size.y);
        }
        if (ie.code == KEY_APPSELECT) {
            key.type = ie.type;
            key.code = ie.code;
            key.value = ie.value;
            write(fd, &key, sizeof(key));
        }
        if (ie.code == KEY_BACK) {
            key.type = ie.type;
            key.code = ie.code;
            key.value = ie.value;
            write(fd, &key, sizeof(key));
        }
    }
    return 0;
}

int GetEventCount() {
    DIR *dir = opendir("/dev/input/");
    dirent *ptr = nullptr;
    int count = 0;
    while ((ptr = readdir(dir)) != nullptr) {
        if (strstr(ptr->d_name, "event"))
            count++;
    }
    return count;
}

int ExecuteCMD(const char *cmd, char *result) {
    int iRet = -1;
    char buf_ps[CMD_RESULT_BUF_SIZE];
    char ps[CMD_RESULT_BUF_SIZE] = {0};
    FILE *ptr;
    strcpy(ps, cmd);
    if ((ptr = popen(ps, "r")) != nullptr) {
        while (fgets(buf_ps, sizeof(buf_ps), ptr) != nullptr) {
            strcat(result, buf_ps);
            if (strlen(result) > 1000) {
                break;
            }
        }
        pclose(ptr);
        ptr = nullptr;
        iRet = 0;
    } else {
        printf("popen%serror\n", ps);
        iRet = -1;//
    }
    return iRet;
}

int GetEventId() {
    int EventCount = GetEventCount();
    char resu[4096]={};
    for (int i = 0; i < EventCount; i++) {
        memset(resu, 0, sizeof resu);
        char temp[128];
        sprintf(temp, "getevent -i /dev/input/event%d", i);
        ExecuteCMD(temp,resu);
        const char *str2 = "ABS (0003)";
        char *pos=strstr(resu, str2);
        if (pos != nullptr)
        {
            return i;
        }
    }
    return 3;
}

Vector2 getTouchScreenDimension1(int fd){
    int abs_x[6], abs_y[6] = {0};
    ioctl(fd, EVIOCGABS(ABS_MT_POSITION_X), abs_x);
    ioctl(fd, EVIOCGABS(ABS_MT_POSITION_Y), abs_y);
    return Vector2(abs_x[2], abs_y[2]);
}

void Touch_Init(int px, int py) {
    char origI[256];
    sprintf(origI, "/dev/input/event%d", GetEventId());
    origfd = open(origI, O_RDWR);
    struct input_absinfo absX, absY;
    ioctl(origfd, EVIOCGABS(ABS_MT_POSITION_X), &absX);
    ioctl(origfd, EVIOCGABS(ABS_MT_POSITION_Y), &absY);
    touch_screen_size = getTouchScreenDimension1(origfd); // + 1.0f;
    touch_s = (touch_screen_size.x + touch_screen_size.y) / (px + py);
    struct uinput_user_dev ui_dev;
    int uinp_fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (uinp_fd <= 0)
    {
        printf("could not open uinput, %s\n", strerror(errno));
        return;
    }

    memset(&ui_dev, 0, sizeof(ui_dev));
    strncpy(ui_dev.name, "VirtualTouch", UINPUT_MAX_NAME_SIZE);
    ui_dev.id.bustype = BUS_USB;
    ui_dev.id.vendor = 0x1341;
    ui_dev.id.product = 0x0001;
    ui_dev.id.version = 5;

    ui_dev.absmin[ABS_MT_POSITION_X] = 0;
    ui_dev.absmax[ABS_MT_POSITION_X] = absX.maximum;
//  TouchSize.Y = absX.maximum;
    ui_dev.absmin[ABS_MT_POSITION_Y] = 0;
    ui_dev.absmax[ABS_MT_POSITION_Y] = absY.maximum;
//  TouchSize.X = absY.maximum;
    ioctl(uinp_fd, UI_SET_PROPBIT, INPUT_PROP_DIRECT);

    ioctl(uinp_fd, UI_SET_EVBIT, EV_ABS);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_MT_POSITION_X);
    ioctl(uinp_fd, UI_SET_ABSBIT, ABS_MT_POSITION_Y);
    ioctl(uinp_fd, UI_SET_EVBIT, EV_SYN);
    ioctl(uinp_fd, UI_SET_EVBIT, EV_KEY);
    ioctl(uinp_fd, UI_SET_KEYBIT, KEY_BACK);
    ioctl(uinp_fd, UI_SET_KEYBIT, KEY_APPSELECT);

    write(uinp_fd, &ui_dev, sizeof(ui_dev));

    if (ioctl(uinp_fd, UI_DEV_CREATE))
    {
        printf("Unable to create UINPUT device.\n");
        return;
    }

    fd = uinp_fd;

    if (ioctl(origfd, EVIOCGRAB, GRAB))
    {
        printf("Handle error.\n");
        return;
	}   
    pthread_create(&touchloop, nullptr, TypeA, nullptr);
}

void Touch_Down(int x, int y) {
    Finger[tnum].x = x*touch_s;
    Finger[tnum].y = y*touch_s;
    Finger[tnum].isDown = true;
    Upload();
}

void Touch_Move(int x, int y) {
    Finger[tnum].x = x*touch_s;
    Finger[tnum].y = y*touch_s;
    Finger[tnum].isDown = true;
    Upload();
}

void Touch_Up() {
    Finger[tnum].isDown = false;
    Upload();
}


int isa_event_device(const struct dirent* dir) {
    return strncmp("event", dir->d_name, 5) == 0;
}

std::string getTouchScreenDevice() {
    struct dirent** namelist;
    int i, ndev;
    ndev = scandir("/dev/input", &namelist, isa_event_device, alphasort);
    if(ndev <= 0){
        return "";
    }
    for(i = 0; i < ndev; i++){
        char fname[64];
        int fd = -1;
        unsigned long keybit[NBITS(KEY_CNT)];
        unsigned long propbit[INPUT_PROP_MAX];
        snprintf(fname, sizeof(fname), "%s/%s", "/dev/uinput", namelist[i]->d_name);
        fd = open(fname, O_RDONLY);
        if(fd < 0){
            continue;
        }
        memset(keybit, 0, sizeof(keybit));
        memset(propbit, 0, sizeof(propbit));
        ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybit)), keybit);
        ioctl(fd, EVIOCGPROP(INPUT_PROP_MAX), propbit);
        close(fd);
        free(namelist[i]);
        if(test_bit(propbit, INPUT_PROP_DIRECT) && (test_bit(keybit, BTN_TOUCH) || test_bit(keybit, BTN_TOOL_FINGER))){
            return std::string(fname);
        } else if(test_bit(keybit, BTN_TOUCH) || test_bit(keybit, BTN_TOOL_FINGER)){
            return std::string(fname);
        }
    }
    return "";
}

Vector2 rotatePointx(uint32_t orientation, float x, float y, int32_t displayWidth,int32_t displayHeight) {
    if (orientation == 0) {
        return Vector2(x, y);
    }
    Vector2 xy(x, y);
    if (orientation == 3) {
        xy.x = (float)displayHeight - y;
        xy.y = x;
    } else if (orientation == 2) {
        xy.x = (float)displayWidth - x;
        xy.y =(float) displayHeight - y;
    } else if (orientation == 1) {
        xy.x = y;
        xy.y =(float) displayWidth - x;
    }
    return xy;
}

Vector2 getTouchScreenDimension(int fd){
    int abs_x[6], abs_y[6] = {0};
    ioctl(fd, EVIOCGABS(ABS_MT_POSITION_X), abs_x);
    ioctl(fd, EVIOCGABS(ABS_MT_POSITION_Y), abs_y);
    return Vector2(abs_x[2], abs_y[2]);
}

void touch_config(){
    std::string device = getTouchScreenDevice();
    if (device.length() < 2) {       
    }
    int touch_device_fd = open("/dev/uinput", O_RDWR | O_SYNC | O_NONBLOCK);
    if (touch_device_fd < 0) {       
    }   
    while(true) {      
        std::this_thread::sleep_for(0.0001s);
    }
    pthread_exit(0);
}

void Init_touch_config() {
    std::thread touch_thread(touch_config);
    touch_thread.detach();
}
