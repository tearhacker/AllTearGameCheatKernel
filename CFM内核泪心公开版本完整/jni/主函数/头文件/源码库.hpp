string exec(string command)
{//泪心 github tearhacker  电报 t.me/TearGame
    char buffer[128];
    string result = "";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

int init_egl(int _screen_x, int _screen_y, bool log) {
    
    native_window =
            android::ANativeWindowCreator::Create("泪心", _screen_x, _screen_y, false);
    ANativeWindow_acquire(native_window);
    // ANativeWindow_acquire(native_window);
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        printf("eglGetDisplay error=%u\n", glGetError());
        return -1;
    }
    if (log) {
        printf("eglGetDisplay ok\n");
    }
    if (eglInitialize(display, 0, 0) != EGL_TRUE) {
        printf("eglInitialize error=%u\n", glGetError());
        return -1;
    }
    if (log) {
        printf("eglInitialize ok\n");
    }
    EGLint num_config = 0;
    const EGLint attribList[] = {EGL_SURFACE_TYPE,
                                 EGL_WINDOW_BIT,
                                 EGL_RENDERABLE_TYPE,
                                 EGL_OPENGL_ES2_BIT,
                                 EGL_BLUE_SIZE,
                                 5, //-->delete
                                 EGL_GREEN_SIZE,
                                 6, //-->delete
                                 EGL_RED_SIZE,
                                 5, //-->delete
                                 EGL_BUFFER_SIZE,
                                 32, //-->new field
                                 EGL_DEPTH_SIZE,
                                 16,
                                 EGL_STENCIL_SIZE,
                                 8,
                                 EGL_NONE};
    if (eglChooseConfig(display, attribList, nullptr, 0, &num_config) !=
        EGL_TRUE) {
        printf("eglChooseConfig  error=%u\n", glGetError());
        return -1;
    }
    if (log) {
        printf("num_config=%d\n", num_config);
    }
    if (!eglChooseConfig(display, attribList, &config, 1, &num_config)) {
        printf("eglChooseConfig  error=%u\n", glGetError());
        return -1;
    }
    if (log) {
        printf("eglChooseConfig ok\n");
    }
    EGLint egl_format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &egl_format);
    ANativeWindow_setBuffersGeometry(native_window, 0, 0, egl_format);
    const EGLint attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, attrib_list);
    if (context == EGL_NO_CONTEXT) {
        printf("eglCreateContext  error = %u\n", glGetError());
        return -1;
    }
    if (log) {
        printf("eglCreateContext ok\n");
    }
    surface = eglCreateWindowSurface(display, config, native_window, nullptr);
    if (surface == EGL_NO_SURFACE) {
        printf("eglCreateWindowSurface  error = %u\n", glGetError());
        return -1;
    }
    if (log) {
        printf("eglCreateWindowSurface ok\n");
    }
    if (!eglMakeCurrent(display, surface, surface, context)) {
        printf("eglMakeCurrent  error = %u\n", glGetError());
        return -1;
    }
    if (log) {
        printf("eglMakeCurrent ok\n");
    }
    return 1;
}

void screen_config()
{
    std::string window_size = exec("wm size");
    sscanf(window_size.c_str(),"Physical size: %dx%d",&screen_x, &screen_y);
    full_screen.ScreenX = screen_x;
    full_screen.ScreenY = screen_y;
    std::thread *orithread = new std::thread([&] {
        while(true){
            Orientation = atoi(exec("dumpsys display | grep 'mCurrentOrientation' | cut -d'=' -f2").c_str());
            if(Orientation == 0 || Orientation == 2) {
                screen_x = full_screen.ScreenX;
                screen_y = full_screen.ScreenY;
            }
            if(Orientation == 1 || Orientation == 3) {
                screen_x = full_screen.ScreenY;
                screen_y = full_screen.ScreenX;
            }
            std::this_thread::sleep_for(0.5s);
        }
    });
    orithread->detach();
}
bool drawimguitick = false;

void Getxfctouch()
{
	for(;;)
	{
		usleep(2000);	
		ImGuiIO& iooi = ImGui::GetIO();
		if (iooi.MouseDown[0] && point2.x <= inttouchx + 80 && point2.y <= inttouchy + 80 && point2.x >= inttouchx - 80 && point2.y >= inttouchy - 80)
		{			
			usleep(55000);		
			if (iooi.MouseDown[0] && point2.x <= inttouchx + 80 && point2.y <= inttouchy + 80 && point2.x >= inttouchx - 80 && point2.y >= inttouchy - 80)
			{
				while (iooi.MouseDown[0])
				{
					inttouchx = point2.x;
					inttouchy = point2.y;
					usleep(500);		
				}
			}
			if (drawimguitick)
			{
				drawimguitick = false;
			}else{
				drawimguitick = true;		
			}
		}
	}
}

void Getxfctouch2()
{
	for(;;)
	{
		usleep(2000);	
		ImGuiIO& ioooi = ImGui::GetIO();
		if (DrawIo[21] && ioooi.MouseDown[0] && point2.x <= NumIo[6] + NumIo[7] && point2.y <= py*2 - NumIo[5] + NumIo[7] && point2.x >= NumIo[6] - NumIo[7] && point2.y >= py*2 - NumIo[5] - NumIo[7])
		{			
			usleep(55000);		
			if (ioooi.MouseDown[0] && point2.x <= NumIo[6] + NumIo[7] && point2.y <= py*2 - NumIo[5] + NumIo[7] && point2.x >= NumIo[6] - NumIo[7] && point2.y >= py*2 - NumIo[5] - NumIo[7])
			{
				while (ioooi.MouseDown[0])
				{
					NumIo[6] = point2.x;
					NumIo[5] = py*2 - point2.y;
					usleep(500);		
				}
			}		
		}
	}
}