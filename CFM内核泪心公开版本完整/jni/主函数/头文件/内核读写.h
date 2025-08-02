#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include<ctype.h>
#include "过缺页.h"
#include "字体.h"
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <map>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <chrono>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/kdev_t.h>
#include <sys/sysmacros.h>
#include <iostream>
#include <ctime>
#define FileCount 4
const char *files[FileCount] = { "wanbai", "CheckMe", "Ckanri", "lanran" };


uintptr_t 基址头;
uintptr_t 基址头2;
pid_t 进程=0;



class c_driver{
  private:
	int has_upper = 0;
	int has_lower = 0;
	int has_symbol = 0;
	int has_digit = 0;
	int fd;
	pid_t 进程;

	typedef struct _COPY_MEMORY{
		pid_t 进程;
		uintptr_t 地址;
		void *buffer;
		size_t size;
	} COPY_MEMORY, *PCOPY_MEMORY;

	typedef struct _MODULE_BASE{
		pid_t 进程;
		char *name;
		uintptr_t 基址头;
        uintptr_t 基址头2;
	} MODULE_BASE, *PMODULE_BASE;

	enum OPERATIONS{
		OP_INIT_KEY = 0x800,
		OP_READ_MEM = 0x801,
		OP_WRITE_MEM = 0x802,
		OP_MODULE_BASE = 0x803,
	};

int symbol_file(const char *filename){
	int length = strlen(filename);
	for (int i = 0; i < length; i++){
		if (isupper(filename[i])){
			has_upper = 1;
		}
		else if (islower(filename[i])){
			has_lower = 1;
		}
		else if (ispunct(filename[i])){
			has_symbol = 1;
		}
		else if (isdigit(filename[i])){
			has_digit = 1;
		}
	}

	return has_upper && has_lower && !has_symbol && !has_digit;
	}
	bool StrAlpha(const char *str){
	       for(int i = 0;i<6;i++){
	           if(!isalpha(str[i])){
	             return false;
	           }
	       }
	       return true;
	}
	
	int getMEN(char *path)
	{
		FILE *file = fopen(path, "r");
		int zero, neko;
		if (file == NULL)
		{
			return 0;
		}
		char line[256];
		while (fgets(line, sizeof(line), file))
		{
			if (sscanf(line, "%d:%d", &neko, &zero) == 2 && zero == 0)
			{
				fclose(file);
				return neko;
			}
		}
		fclose(file);
		return 0;
	}
	
		int has_digit1(char *str)
	{
		int i, len;
		len = strlen(str);
		for (i = 0; i < len; i++)
		{
			if (isdigit((unsigned char)str[i]))
			{
				return 1;
			}
		}
		return 0;
	}
	

	

    
public:
    c_driver() : fd(-1), 进程(0) {

            
	}
	
	
	
    }

	~c_driver(){
		if (fd > 0)
			close(fd);
	}

	void 初始化(pid_t 进程){
		this->进程 = 进程;
	}

	bool 读取(uintptr_t 地址, void *buffer, size_t size){
	if (地址 <= 0x10000000 || 地址 % 4 != 0 || 地址 >= 0x10000000000){
	 return 0;
}
		COPY_MEMORY cm;
		cm.进程 = this->进程;
		cm.地址 = 地址;
		cm.buffer = buffer;
		cm.size = size;
		if (ioctl(fd, OP_READ_MEM, &cm) != 0){
			return false;
		}
		return true;
	}
	
	bool 写入(uintptr_t 地址, void *buffer, size_t size){
		COPY_MEMORY cm;
		cm.进程 = this->进程;
		cm.地址 = 地址;
		cm.buffer = buffer;
		cm.size = size;
		if (ioctl(fd, OP_WRITE_MEM, &cm) != 0){
			return false;
		}
		return true;
	}

	template < typename T > T 读取(uintptr_t 地址){
		T res;
		if (this->读取(地址, &res, sizeof(T)))
		return res;
		return{
		};
	}

	template < typename T > bool 写入(uintptr_t 地址, T value){
		return this->写入(地址, &value, sizeof(T));
	}
	
    long 读取指针(long 地址){
    if (地址 <= 0x10000000 || 地址 % 4 != 0 || 地址 >= 0x10000000000){
		 return 0;
	 }
    long res;
    if (this->读取(地址,&res,sizeof(uintptr_t))){
    return res;
    }
    return {};
}
    
    float 读取浮点数(long 地址){
    if (地址 < 0xFFFFFF){
     return 0;
    }
    float var;
    if (this->读取(地址&0xFFFFFFFFFF,&var,sizeof(var))){
    return var;
      }
    return {};
}
    
   
    int 读取整数(long 地址){
    if (地址 <= 0x10000000 || 地址 % 4 != 0 || 地址 >= 0x10000000000){
     return 0;
	}
    int 数据;
    if (this->读取(地址&0xFFFFFFFFFF,&数据,sizeof(数据))){
    return 数据;
    }
    return {};
    }
    
	
	// 写入F类内存
	void 写入F类内存(unsigned long 地址, float 数据){
	this->写入(地址, &数据, 4);
}
    // 写入D类内存
    void 写入D类内存(unsigned long 地址, int 数据){
	this->写入(地址, &数据, 4);
}

	pid_t 获取进程(char *name){
	FILE *fp;
	pid_t 进程;
	char cmd[0x100] = "pidof ";
	strcat(cmd, name);
	fp = popen(cmd, "r");
	fscanf(fp, "%d", &进程);
	pclose(fp);
	return 进程;
}

    uintptr_t 获取基址头(char *name){
    MODULE_BASE mb;
	char buf[0x100];
	strcpy(buf, name);
	mb.进程 = this->进程;
	mb.name = buf;
	if (ioctl(fd, OP_MODULE_BASE, &mb) != 0){
   	return 0;
	}
		return mb.基址头;
        return mb.基址头2;
}
	
	


	
};//结束

static c_driver *驱动 = new c_driver();
