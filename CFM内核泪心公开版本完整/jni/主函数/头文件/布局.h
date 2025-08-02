void tick()
{   //泪心 github tearhacker  电报 t.me/TearGame
    static bool show_ChildMenu1 = true;
    static bool show_ChildMenu2 = false;
    static bool show_ChildMenu3 = false;
    
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle &Style = ImGui::GetStyle();
    
    if (display == EGL_NO_DISPLAY)
    return;
    Style.WindowMinSize = ImVec2(700, 700);//设置窗口初始大小700和800   
    static ImVec4 clear_color = ImVec4(0, 0, 0, 0);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(init_screen_x, init_screen_y);
    ImGui::NewFrame();
    {
		
            ImGui::Begin(ICON_FA_ASTERISK" CFM ESP 内核版本 ");{
            if (ImGui::BeginChild("左侧主菜单", ImVec2(250, 0), false,ImGuiWindowFlags_None));    
            {   
            
            ImGui::BulletText("Meun Bar");  
            if (ImGui::Button( "主页面板",ImVec2(245,85)))
            {
                show_ChildMenu1 = true;
                show_ChildMenu2 = false;
                show_ChildMenu3 = false;
            }
            ImGui::Spacing();
            if (ImGui::Button( "调试面板",ImVec2(245,85)))
            {
                show_ChildMenu1 = false;
                show_ChildMenu2 = true;
                show_ChildMenu3 = false;
            }
            ImGui::Spacing();           
            if(ImGui::Button("退出程序",ImVec2(245,85)))
            {
                exit(0);
            }
            ImGui::EndChild();
		    }
            ImGui::SameLine();
            if(show_ChildMenu1){
            if (ImGui::BeginChild("子菜单0", ImVec2(0, 0), false, ImGuiWindowFlags_None));
            {
			ImGui::Text("矩阵 %p",矩阵);
			ImGui::Text("阵列 %p",对象阵列);
			ImGui::Text(ICON_FA_USER_CIRCLE " by:树  演戏上分即可");
			if (ImGui::Combo("", &style_idx, "白色主题\0蓝色主题\0紫色主题\0"))
            {
            switch (style_idx)
            {
              case 0: ImGui::StyleColorsLight(); break;
              case 1: ImGui::StyleColorsDark(); break;
              case 2: ImGui::StyleColorsClassic(); break;
            }
            }
            if (style_idx == 0){
            ImGui::StyleColorsLight();
            }
            if (style_idx == 1){
            ImGui::StyleColorsDark();
            }
            if (style_idx == 2){
            ImGui::StyleColorsClassic();
            }
			ImGui::Text("帧率平均值 %.3f ms/帧率 %.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			if (ImGui::Button("\xef\x81\x82 初始",{100,55}))   
			{    
		    int intauto = DrawInt();
	        if (intauto == 0)
		    {
			cshzt = true;
			DrawIo[0] = true;
			}
			}
            
            if(人物)
            {
            if (ImGui::Button(ICON_FA_GAMEPAD"透视[已启动]",{160,55}))   
            {    
            DrawIo[10]=false;
            人物 = false;
            }
            }else{
            if (ImGui::Button(ICON_FA_GAMEPAD"透视[未启动]",{160,55}))   
            {    
            DrawIo[10]=true;        
            人物 = true;
            }
            }
            ImGui::Text("阵容选择(对局内开启)");
            ImGui::RadioButton("警方", &NumIo[49], 0.0f); 
            ImGui::SameLine();
		    ImGui::RadioButton("匪方", &NumIo[49], 1.0f);
            }
            ImGui::Text("ESP");
            ImGui::Checkbox("人物射线  ", &DrawIo[1]);//DrawIo[1]是一个开关ID，下面以此类推，每个ID都不能相同 所以有不同的数字命名
            ImGui::SameLine();
            ImGui::Checkbox("人物血量", &DrawIo[2]);               
            ImGui::Checkbox("人物方框  ", &DrawIo[3]);               
            ImGui::SameLine();
            ImGui::Checkbox("人物信息", &DrawIo[4]);
            }
            ImGui::SameLine();
            if(show_ChildMenu2){
            if (ImGui::BeginChild("子菜单0", ImVec2(0, 0), false, ImGuiWindowFlags_None));
            {
            if(触摸自瞄)
            {
            if (ImGui::Button(ICON_FA_CROSSHAIRS"自瞄[已启动]",{160,55}))   
            {    
            DrawIo[20]=false;
            触摸自瞄 = false;
            }
            }else{
            if (ImGui::Button(ICON_FA_CROSSHAIRS"自瞄[未启动]",{160,55}))   
            {    
            DrawIo[20]=true;        
            触摸自瞄 = true;
            }
            }	   
		    ImGui::Checkbox("触摸位置", &DrawIo[21]);
		    ImGui::SliderFloat("自瞄范围", &NumIo[3], 0.0f, 500.0f,"%.1f",1);     
            ImGui::SliderFloat("自瞄速度", &NumIo[4],0.1f,50.0f,"%.2f",2);
	        ImGui::SliderFloat("子弹速度", &NumIo[11],500.0f,1200.0f,"%.0f",3);
		    ImGui::SliderFloat("平滑力度", &NumIo[9],0.1f,30.0f,"%.1f",3);
           }
           }
           }          


    }
	if(cshzt)
   	DrawPlayer(ImGui::GetForegroundDrawList()); 	
    ImGui::Render();  
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    eglSwapBuffers(display, surface);
}

void shutdown()
{
    if (!g_Initialized) {
        return;
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    if (display != EGL_NO_DISPLAY){
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context != EGL_NO_CONTEXT){
            eglDestroyContext(display, context);
        }
        if (surface != EGL_NO_SURFACE){
            eglDestroySurface(display, surface);
        }
        eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
    ANativeWindow_release(native_window);
}
