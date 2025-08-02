float fov = 80;
float AimDistance = 1024;
float NumIo[50];
bool DrawIo[50];
struct AimStruct
{
    //Vector3A ObjAim;  
	//Vector3A MyObjAim;
    //Vector3A AimMovement;  
    float ScreenDistance = 0;
    float WodDistance = 0; 
}Aim[100];

int findminat()
{/*
    float min = NumIo[3];
    int minAt = 999;
    for (int i = 0; i < MaxPlayerCount; i++)
    {
        if (Aim[i].ScreenDistance < min && Aim[i].ScreenDistance != 0)
        {
            min = Aim[i].ScreenDistance;
            minAt = i;
        }
    }
    if (minAt == 999)
    {
        Gmin = -1;
        return -1;
    }
    Gmin = minAt;   
    WorldDistance = Aim[minAt].WodDistance;
    return minAt;*/
}

void *AimCalcu()
{
	/*diff[0]=0;
	diff[1]=0;
	diff[2]=0;
	float MyLastCoor[3];
	float MyNewCoor[3];
	while (1)
	{
		//AimBotCheck();
		if (Gmin == -1 || Gmin == 100)
		{
			continue;
		}
		//printf("%d\n",Gmin);
		//printf("%lx\n",Aim[Gmin].Ox);
		//memset(LastCoor, 0, 12);
		//vm_readv(Aim[Gmin].Ox,LastCoor,12);
	    MyLastCoor[0] = Aim[Gmin].MyObjAim.X;
		MyLastCoor[1] = Aim[Gmin].MyObjAim.Y;
	    MyLastCoor[2] = Aim[Gmin].MyObjAim.Z;
		LastCoor[0] = Aim[Gmin].ObjAim.X;
		LastCoor[1] = Aim[Gmin].ObjAim.Y;
		LastCoor[2] = Aim[Gmin].ObjAim.Z;
		//printf("Last:%f\n",LastCoor[0]);
		//printf("Last:%lx\n",Aim[Gmin].Ox);
		usleep(0.2*10000);
		//休眠
		//vm_readv(Aim[Gmin].Ox,NewCoor,12);
		//printf("New:%f\n",NewCoor[Gmin]);
		MyNewCoor[0] = Aim[Gmin].MyObjAim.X;
		MyNewCoor[1] = Aim[Gmin].MyObjAim.Y;
		MyNewCoor[2] = Aim[Gmin].MyObjAim.Z;
		NewCoor[0] = Aim[Gmin].ObjAim.X;
		NewCoor[1] = Aim[Gmin].ObjAim.Y;
		NewCoor[2] = Aim[Gmin].ObjAim.Z;
		//printf("Last:%f  New:%f\n",LastCoor[0],NewCoor[0]);
		
		for (int i=0;i<3;i++)
		{
			diff[i] = (NewCoor[i] - LastCoor[i]) + (MyNewCoor[i] - MyLastCoor[i]);
			if (diff[0] < -10000 || diff[0] > 10000)
			{
				//printf("diff:%f\n",diff[0]);
				continue;
				//return -1;
			}
			if (diff[1] < -10000 || diff[1] > 10000)
			{
				//printf("diff:%f\n",diff[0]);
				continue;
				//return -1;
			}
			if (diff[2] < -10000 || diff[2] > 10000)
			{
				//printf("diff:%f\n",diff[0]);
				continue;
				//return -1;
			}
			//printf("diff:%f\n",diff[i]);
			//0.2秒移动的距离
		}
		usleep(10000);
	}*/
}

float GetPitch(float Fov) 
{/*
    if (Fov > 75 && Fov <= 130)          // 不开镜
    {
        return (0.7f/30)*NumIo[4];
    }
    else if (Fov == 70 || Fov == 75)    // 机瞄 ，侧瞄
    {     
        return (2.5f/30)*NumIo[4];       
    }
    else if (Fov == 55 || Fov == 60)    // 红点 ，全息
    {
        return (2.5f/30)*NumIo[4];
    }   
    else if ((int)Fov == 44)    // 2倍
    {
        return (4.8f/30)*NumIo[4];
    }
    else if ((int)Fov == 26)    // 3倍
    {
        return (6.9f/30)*NumIo[4];
    }
    else if ((int)Fov == 20)    // 4倍
    {
        return (7.9f/30)*NumIo[4];
    }
    else if ((int)Fov == 13)    // 6倍
    {       
        return (13.2f/30)*NumIo[4];
    }
	return (2.5f/30)*NumIo[4];   // 8倍*/
}


void AimBotAuto(ImDrawList *Draw)
{   
    bool isDown = false;
    // 是否按下触摸
    double leenx = 0.0f;
    // x轴速度
    double leeny = 0.0f;
    // y轴速度     
    double de = 1.5f;
    // 顶部不可触摸区域
   
    double tx = NumIo[5], ty = NumIo[6];
    // 触摸点位置

    float SpeedMin = 2.0f;
    // 临时触摸速度

    double w = 0.0f, h = 0.0f, cmp = 0.0f;
    // 宽度 高度 正切

    double ScreenX = screen_x, ScreenY = screen_y;
    // 分辨率(竖屏)PS:滑屏用的坐标是竖屏状态下的

    double ScrXH = ScreenX / 2.0f;
    // 一半屏幕X

    double ScrYH = ScreenY / 2.0f;
    // 一半屏幕X

    static float TargetX = 0;
    static float TargetY = 0;
    // 触摸目标位置
    
  //  Vector3A obj;
    
    float NowCoor[3];
   
	Touch_Init(&screen_x,&screen_y);	
	
    while (1)
    {
        
        if (!DrawIo[20])
        {           
            if (isDown == true)
            {
                tx = NumIo[5], ty = NumIo[6];
                // 恢复变量 
                Touch_Up(8);
                // 抬起
                isDown = false;
            }
            usleep(NumIo[9] * 1000);
            continue;
        }
        
        findminat();
        // 获取目标

        if (Gmin == -1)
        {          
            if (isDown == true)
            {
                tx = NumIo[5], ty = NumIo[6];
                // 恢复变量 
                Touch_Up(8);
                // 抬起
                isDown = false;
            }
            usleep(NumIo[9] * 1000);
            continue;
        }
		
		
        fov = getFloat(getPtr64(getPtr64(oneself + 0x3e40) + 0x5c0) + 0x5d4);  // 自身FOV
		float yq = GetPitch(fov);
		      
        float ToReticleDistance = Aim[Gmin].ScreenDistance;              
        float FlyTime = WorldDistance / NumIo[11];
        float DropM = 500.0f * FlyTime * FlyTime; // 下坠

        int Firing = getDword(oneself + 0x1C48);
        int Aiming = getDword(oneself + 0x13F8);

	    NowCoor[0] = Aim[Gmin].ObjAim.X;
        NowCoor[1] = Aim[Gmin].ObjAim.Y;
        NowCoor[2] = Aim[Gmin].ObjAim.Z;
        obj.X = NowCoor[0] + (FlyTime /0.2 * diff[0]);
        obj.Y = NowCoor[1] + (FlyTime /0.2 * diff[1]);
        obj.Z = NowCoor[2] + (FlyTime /0.2 * diff[2]) + DropM;
        float cameras = matrix[3] * obj.X + matrix[7] * obj.Y + matrix[11] * obj.Z + matrix[15];        
		
        Vector2A vpvp = WorldToScreen(obj,matrix,cameras);             
		
        zm_y = vpvp.X;     
        zm_x = ScreenX - vpvp.Y;        
		
        if (zm_x <= 0 || zm_x >= ScreenX || zm_y <= 0 || zm_y >= ScreenY)
        {          
            if (isDown == true)
            {
                tx = NumIo[5], ty = NumIo[6];
                // 恢复变量 
                Touch_Up(8);
                // 抬起
                isDown = false;
            }
            usleep(NumIo[9] * 1000);
            continue;
        }

        if (ToReticleDistance <= NumIo[3])
        {                  
                  
            switch ((int)NumIo[0])
            {
                case 0:
                    if (Firing != 1)
                    {
                        if (isDown == true)
                        {
                            tx = NumIo[5], ty = NumIo[6];
                            // 恢复变量
                            Touch_Up(8);
                            isDown = false;
                        }                      
                        usleep(NumIo[9] * 1000);
                        continue;
                    }
                break;
                case 1:
                    if (Aiming != 1)
                    {
                        if (isDown == true)
                        {
                            tx = NumIo[5], ty = NumIo[6];
                            // 恢复变量
                            Touch_Up(8);
                            isDown = false;
                        }
                        usleep(NumIo[9] * 1000);
                        continue;
                    }
                break;
                case 2:
                    if (Firing == 0 && Aiming == 0)
                    {
                        if (isDown == true)
                        {
                            tx = NumIo[5], ty = NumIo[6];
                            // 恢复变量
                            Touch_Up(8);
                            isDown = false;
                        }
                        usleep(NumIo[9] * 1000);
                        continue;
                    }
                break;
            }         
                   
            if (isDown == false)
            {
				if (NumIo[10] == 0.0f)
                	Touch_Down(8,(int)tx, (int)ty);
				else
					Touch_Down(8,py*2-(int)tx, px*2-(int)ty);
                isDown = true;
            }

            if (zm_x > ScrXH)
            {
                TargetX = -(ScrXH - zm_x);
                TargetX /= NumIo[4];                                       
                if (TargetX + ScrXH > ScrXH * 2)
                    TargetX = 0;
            }
            if (zm_x < ScrXH)
            {
                TargetX = zm_x - ScrXH;
                TargetX /= NumIo[4];             
                if (TargetX + ScrXH < 0)
                    TargetX = 0;
            }
            if (zm_y > ScrYH)
            {
                TargetY = -(ScrYH - zm_y);
                TargetY /= NumIo[4];              
                if (TargetY + ScrYH > ScrYH * 2)
                    TargetY = 0;
            }
            if (zm_y < ScrYH)
            {
                TargetY = zm_y - ScrYH;
                TargetY /= NumIo[4];              
                if (TargetY + ScrYH < 0)
                    TargetY = 0;
            }
            
            if (TargetY >= 35 || TargetX >= 35 || TargetY <= -35 || TargetX <= -35)
            {
                if (isDown == true)
                {
                    tx = NumIo[5], ty = NumIo[6];
                    // 恢复变量
                    Touch_Up(8);
                    isDown = false;
                }
                usleep(NumIo[9] * 1000);
                continue;
            }           		
            tx += TargetX;
            ty += TargetY;		
			tx -= yq;
            if (tx >= NumIo[5] + NumIo[7] || tx <= NumIo[5] - NumIo[7]
                || ty >= NumIo[6] + NumIo[7] || ty <= NumIo[6] - NumIo[7])
            {
                // 只要滑屏达到了边界，直接还原至中心
                tx = NumIo[5], ty = NumIo[6];
                // 恢复变量
                Touch_Up(8);
                // 抬起            
				if (NumIo[10] == 0.0f)
                	Touch_Down(8,(int)tx, (int)ty);
			    else
					Touch_Down(8,py*2-(int)tx, px*2-(int)ty);
                // 按下             
            }         		           
			if (NumIo[10] == 0.0f)
           		Touch_Move(8,(int)tx, (int)ty);
		    else
		    	Touch_Move(8,py*2-(int)tx, px*2-(int)ty);
        }
        else
        {          
            if (isDown == true)
            {
                tx = NumIo[5], ty = NumIo[6];
                // 恢复变量 
                Touch_Up(8);
                // 抬起
                isDown = false;
            }
        }
        usleep(NumIo[9] * 1000);
    }
}
