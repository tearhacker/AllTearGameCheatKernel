
struct AimStruct
{//泪心 github tearhacker  电报 t.me/TearGame
    Vector3A 瞄准目标;  //目标
    Vector3A 自身目标; //自身目标
    float 准心最近距离 = 0;
    float 判断距离 = 0; 
}瞄准[100];
int 获取目标()
{   
    float 范围 =300;     
    int 范围2 = 999;
    for (int i = 0; i < 全部数量; i++)
    {
        if (瞄准[i].准心最近距离 < 范围 && 瞄准[i].准心最近距离 != 0)
        {
            范围 = 瞄准[i].准心最近距离;
            范围2 = i;
        }
    }
    if (范围2 == 999)
    {
        最近范围 = -1;
        return -1;
    }
    最近范围 = 范围2;   
    共量距离 = 瞄准[范围2].判断距离;
    return 范围2;
}
void AimBotAuto(ImDrawList *Draw)
{   
    bool 触摸开启 = false;
    double x轴速度 = 0.0f;
    double y轴速度 = 0.0f;
    double 顶部不可触摸区域 = 1.5f;
    double 瞄准点X = NumIo[5], 瞄准点Y = NumIo[6];
    double 分辨率X = screen_x, 分辨率Y = screen_y;
    double 一半屏幕X= 分辨率X / 2.0f;
    double 一半屏幕Y = 分辨率Y / 2.0f;
    static float 触摸目标X = 0;
    static float 触摸目标Y = 0;    
    Vector3A 敌人坐标;    
    float 现在目标[3];   
	Touch_Init(&screen_x,&screen_y);	
    while (1)
    {        
        if (!DrawIo[2])//触摸开启
        {           
            if (触摸开启 == true)
            {
                瞄准点X = NumIo[5], 瞄准点Y = NumIo[6]; 
                Touch_Up(8);
                触摸开启 = false;
            }
            usleep(NumIo[9] * 1000);
            continue;
        }        
        获取目标();       
        if (最近范围 == -1)
        {          
            if (触摸开启 == true)
            {
                瞄准点X = NumIo[5], 瞄准点Y = NumIo[6];
                Touch_Up(8);
                触摸开启 = false;
            }
            usleep(NumIo[9] * 1000);
            continue;
        }
        float 到准心距离 = 瞄准[最近范围].准心最近距离;
        int 开镜= 读取指针(对象指针 + 0x74);  //开镜
	    现在目标[0]=瞄准[最近范围].瞄准目标.X;
        现在目标[1]=瞄准[最近范围].瞄准目标.Z;
        现在目标[2]=瞄准[最近范围].瞄准目标.Y;
        敌人坐标.X = 现在目标[0];
        敌人坐标.Y = 现在目标[1]+0.7;
        敌人坐标.Z = 现在目标[2];
        float 自瞄相机 = matrix[3] * 敌人坐标.X + matrix[7] * 敌人坐标.Y + matrix[11] * 敌人坐标.Z + matrix[15];        
		
        Vector2A 预瞄点 = WorldToScreen(敌人坐标,matrix,自瞄相机);     
		//骨骼预瞄点=预瞄点;
		float AimDs = sqrt(pow(px - 预瞄点.X, 2) + pow(py - 预瞄点.Y, 2));//可以说是瞄准的地方
		
        自瞄Y = 预瞄点.X;     
        自瞄X = 分辨率X - 预瞄点.Y;        
		
        if (自瞄X <= 0 || 自瞄X >= 分辨率X || 自瞄Y <= 0 || 自瞄Y >= 分辨率Y)
        {          
            if (触摸开启 == true)
            {
                瞄准点X = NumIo[5], 瞄准点Y = NumIo[6];
                Touch_Up(8);
                触摸开启 = false;
            }
            usleep(NumIo[9] * 1000);
            continue;
        }

        if (到准心距离 <= NumIo[3])
        {                  
                  
            switch ((int)NumIo[0])
            {
                case 0:
                    if (开镜 != 0)
                    {
                        if (触摸开启 == true)
                        {
                            瞄准点X = NumIo[5], 瞄准点Y = NumIo[6];
                            Touch_Up(8);
                            触摸开启 = false;
                        }                      
                        usleep(NumIo[9] * 1000);
                        continue;
                    }
                break;
            }
                   
            if (触摸开启 == false)
            {
				if (NumIo[10] == 0.0f)
                	Touch_Down(8,(int)瞄准点X, (int)瞄准点Y);
				else
					Touch_Down(8,py*2-(int)瞄准点X, px*2-(int)瞄准点Y);
                触摸开启 = true;
            }
			
			float 自瞄速度 = NumIo[4];
			if (AimDs < 1)
				自瞄速度 = NumIo[4] / 0.09;		
			else if (AimDs < 2)
				自瞄速度 = NumIo[4] / 0.11;		
			else if (AimDs < 3)
				自瞄速度 = NumIo[4] / 0.12;	
			else if (AimDs < 5)
				自瞄速度 = NumIo[4] / 0.15;		
			else if (AimDs < 10)
				自瞄速度 = NumIo[4] / 0.25;		
			else if (AimDs < 15)
				自瞄速度 = NumIo[4] / 0.4;		
			else if (AimDs < 20)
				自瞄速度 = NumIo[4] / 0.5;
			else if (AimDs < 25)
				自瞄速度 = NumIo[4] / 0.6;		
			else if (AimDs < 30)
				自瞄速度 = NumIo[4] / 0.7;
	        else if (AimDs < 40)
				自瞄速度 = NumIo[4] / 0.75;
			else if (AimDs < 50)
				自瞄速度 = NumIo[4] / 0.8;
			else if (AimDs < 60)
				自瞄速度 = NumIo[4] / 0.85;
			else if (AimDs < 70)
				自瞄速度 = NumIo[4] / 0.9;
			else if (AimDs < 80)
				自瞄速度 = NumIo[4] / 0.95;	
			else if (AimDs < 90)
				自瞄速度 = NumIo[4] / 1.0;		
			else if (AimDs < 100)
				自瞄速度 = NumIo[4] / 1.05;
			else if (AimDs < 150)
				自瞄速度 = NumIo[4] / 1.25;
			else if (AimDs < 200)
				自瞄速度 = NumIo[4] / 1.5;
			else
				自瞄速度 = NumIo[4] / 1.55;					

            if (自瞄X > 一半屏幕X)
            {
                触摸目标X = -(一半屏幕X- 自瞄X);
                触摸目标X /= 自瞄速度;                                       
                if (触摸目标X + 一半屏幕X> 一半屏幕X* 2)
                    触摸目标X = 0;
            }
            if (自瞄X < 一半屏幕X)
            {
                触摸目标X = 自瞄X - 一半屏幕X;
                触摸目标X /= 自瞄速度;             
                if (触摸目标X + 一半屏幕X< 0)
                    触摸目标X = 0;
            }
            if (自瞄Y > 一半屏幕Y)
            {
                触摸目标Y = -(一半屏幕Y - 自瞄Y);
                触摸目标Y /= 自瞄速度;              
                if (触摸目标Y + 一半屏幕Y > 一半屏幕Y * 2)
                    触摸目标Y = 0;
            }
            if (自瞄Y < 一半屏幕Y)
            {
                触摸目标Y = 自瞄Y - 一半屏幕Y;
                触摸目标Y /= 自瞄速度;              
                if (触摸目标Y + 一半屏幕Y < 0)
                    触摸目标Y = 0;
            }
            
            if (触摸目标Y >= 35 || 触摸目标X >= 35 || 触摸目标Y <= -35 || 触摸目标X <= -35)
            {
                if (触摸开启 == true)
                {
                    瞄准点X = NumIo[5], 瞄准点Y = NumIo[6];
                    Touch_Up(8);
                    触摸开启 = false;
                }
                usleep(NumIo[9] * 1000);
                continue;
            }           		
            瞄准点X += 触摸目标X;
            瞄准点Y += 触摸目标Y;		
            if (瞄准点X >= NumIo[5] + NumIo[7] || 瞄准点X <= NumIo[5] - NumIo[7]
                || 瞄准点Y >= NumIo[6] + NumIo[7] || 瞄准点Y <= NumIo[6] - NumIo[7])
            {
                瞄准点X = NumIo[5], 瞄准点Y = NumIo[6];
                Touch_Up(8);        
				if (NumIo[10] == 0.0f)//左边右边
                	Touch_Down(8,(int)瞄准点X, (int)瞄准点Y);
			    else
					Touch_Down(8,py*2-(int)瞄准点X, px*2-(int)瞄准点Y);
            }         		           
			if (NumIo[10] == 0.0f)
           		Touch_Move(8,(int)瞄准点X, (int)瞄准点Y);
		    else
		    	Touch_Move(8,py*2-(int)瞄准点X, px*2-(int)瞄准点Y);
        }
        else
        {          
            if (触摸开启 == true)
            {
                瞄准点X = NumIo[5], 瞄准点Y = NumIo[6];
                Touch_Up(8);
                触摸开启 = false;
            }
        }
        usleep(NumIo[9] * 1000);
    }
}
