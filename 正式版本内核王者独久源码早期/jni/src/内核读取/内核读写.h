
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
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <map>
#include <vector>
#include <algorithm>
#include <dirent.h>
#include <unistd.h>
#include <chrono>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/kdev_t.h>
#include <sys/sysmacros.h>
#include <iostream>
#define FileCount 4
static const char *files[FileCount] = { "wanbai", "CheckMe", "Ckanri", "lanran" };
//#include "Android_kernel/MyDriver.h"
int pid;
float px,py;
long int Gname;
float X,Y,W;
//
 
class c_driver {
private:
int has_upper = 0;
	int has_lower = 0;
	int has_symbol = 0;
	int has_digit = 0;
    int fd;
    pid_t pid;

    typedef struct _COPY_MEMORY {
        pid_t pid;
        uintptr_t addr;
        void* buffer;
        size_t size;
    } COPY_MEMORY, *PCOPY_MEMORY;

    typedef struct _MODULE_BASE {
        pid_t pid;
        char* name;
        uintptr_t base;
    } MODULE_BASE, *PMODULE_BASE;

    enum OPERATIONS {
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
	int OpenFd(){
        DIR * dir;
    	struct dirent * ptr;
    	struct stat info;
    	dir = opendir("/proc");
    	ssize_t len;
    	char path[256];
    	char buffer[256];
    	char fd_path[256];
    	char fd_buffer[256];
    	char dev_path[256];
        char data_path[128];
		char brand[128];
    char model[128];
    char cpu[128];
    	int ID;
    	int PPID;
    	memset(brand, 0, sizeof(brand));
    memset(model, 0, sizeof(model));
    memset(cpu, 0, sizeof(cpu));
    	auto start = std::chrono::high_resolution_clock::now();  // 获取起始时间
    	while((ptr = readdir(dir)) != NULL){
    	   if(ptr->d_type == DT_DIR){
    	     sprintf(buffer,"/proc/%d/exe",atoi(ptr->d_name));
    		 //printf("文件夹: %s\n  路径: %s",ptr->d_name,buffer);
    	     len = readlink(buffer, path, sizeof(path) - 1);
    	     if (len != -1)   path[len] = '\0';
    	     char* stres = strrchr(path,'(deleted)');
    	     if(stres != NULL){
    	       sscanf(path, "/data/%s", &data_path);
    	       if(StrAlpha(data_path)){
    		     sscanf(buffer,"/proc/%d/exe",&PPID);
    		     printf("[+] 软链: %s  PID: %d\n", path, PPID);
    		     for(int i = 3;i<5;i++){
    		         sprintf(fd_path,"/proc/%d/fd/%d",PPID,i);
    		         len = readlink(fd_path, fd_buffer, sizeof(fd_buffer) - 1);
    		         char* stress = strrchr(fd_buffer,'(deleted)');
    		         if(stress != NULL){
    		            int fd_file = open(fd_path, O_RDONLY);
    		            if (fd_file == -1) {
    		               perror("open");
    		               close(fd_file);
    		               return EXIT_FAILURE;
    		            }
    		            if (fstat(fd_file, &info) == -1) {
    		               perror("fstat");
    		               close(fd_file);
    		               return 0;
    		            }
    		            sscanf(fd_buffer,"%s (deleted)", dev_path);
    		            printf("[*] 设备路径: %s  设备 ID: %lu\n", dev_path, info.st_dev);
    		            printf("[*] 主设备号: %lu\n", major(info.st_rdev));
    		            printf("[*] 次设备号: %lu\n", minor(info.st_rdev));
    		                		                // 获取品牌
  //  printf("\033[31m");
    __system_property_get("ro.product.brand", brand);
    printf("[-] 手机品牌：%s\n", brand);

    // 获取型号
    __system_property_get("ro.product.model", model);
    printf("[-] 手机型号：%s\n", model);

    // 获取处理器型号
    __system_property_get("ro.product.board", cpu);
    printf("[-] 处理器型号：%s\n", cpu);
    		            if(access(dev_path,F_OK) == 0){  //检查文件是否存在
    		               ID = open(dev_path,O_RDWR);
    		               if(ID != -1){
    		                 printf("[+] 驱动识别成功\n");
    		                 if(unlink(dev_path) == 0) {
    		                    printf("[+] 驱动守护中\n");
    		                    auto end = std::chrono::high_resolution_clock::now();  // 获取结束时间
    		                    float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); //获毫秒
    		                    printf("[+] 读取驱动用时: %.f ms\n", elapsed_ns);
    		                    return ID;
    		                    //return 0;
    		                 }
    		               }
    		            }  else { //驱动已经隐藏
    		               printf("[+] 驱动已隐藏创建驱动中\n");
    		               mode_t mode = S_IFCHR | 0666; // 创建一个命名管道，权限为读写
    		               dev_t dev = makedev(major(info.st_rdev), minor(info.st_rdev));
    		               if(mknod(dev_path, mode, dev) != -1){
    		                  printf("[+] mknod : %d 成功\n", major(info.st_rdev));
    		               }
    		               ID = open(dev_path,O_RDWR);
    		               if(ID != -1){
    		                  printf("[+] 驱动识别成功\n");
    		                  if(unlink(dev_path) != -1){
    		                    printf("[+] 驱动守护中\n");
    		                    auto end = std::chrono::high_resolution_clock::now();  // 获取结束时间
    		                    float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); //获毫秒
    		                    printf("[+] 读取驱动用时: %.f ms\n", elapsed_ns);
    		                    return ID;
    		                  }
    		               }
    		            }
    		            close(fd_file);
    		            break;
    		         }
    		     }
    		     break;
    		   }
    		 }
    	   }
    	}
    	closedir(dir);
    	    for (int i = 0; i < 10; i++) {
        printf("[+] 未识别到QX驱动程序\n");
    }
      
    	return -1;
   }
  public:
	c_driver(){
		fd = OpenFd();
	}

    ~c_driver() {
        //wont be called
        if (fd > 0)
            close(fd);
    }
pid_t 获取进程ID(char* name) {
    FILE* fp;
    pid_t pid;
    char cmd[0x100] = "pidof ";

    strcat(cmd, name);
    fp = popen(cmd,"r");
    fscanf(fp,"%d", &pid);
    pclose(fp);
    return pid;
}

    void initialize(pid_t pid) {
        this->pid = pid;
    }

    bool init_key(char* key) {
        char buf[0x100];
        strcpy(buf,key);
        if (ioctl(fd, OP_INIT_KEY, buf) != 0) {
            return false;
        }
        return true;
    }

    bool read(uintptr_t addr, void *buffer, size_t size) {
        COPY_MEMORY cm;
        cm.pid = this->pid;
        cm.addr = addr&0xFFFFFFFFFF;
        cm.buffer = buffer;
        cm.size = size;

        if (ioctl(fd, OP_READ_MEM, &cm) != 0) {
            return false;
        }
        return true;
    }

    bool write(uintptr_t addr, void *buffer, size_t size) {
        COPY_MEMORY cm;

        cm.pid = this->pid;
        cm.addr = addr;
        cm.buffer = buffer;
        cm.size = size;

        if (ioctl(fd, OP_WRITE_MEM, &cm) != 0) {
            return false;
        }
        return true;
    }


 
    
    int 是否可读(uintptr_t addr)
{
    if (addr < 0x1000000000 || addr>0xefffffffff || addr % 0x8 != 0)
        return 0;
    return 1;
}
    
    long 读取指针(long 地址){
    long res;
    if (this->read(地址,&res,sizeof(uintptr_t))){
        return res;
        }
    return {};
    }
    float 读取浮点数(long 地址){
    float var;
    
    if (this->read(地址,&var,sizeof(var))){
         return var;
        }
    return {};
    }
    int 读取整数(long 地址){
         int data;
    
    if (this->read(地址,&data,sizeof(data))){
         return data;
        }
    return {};
    }
    
    
    template <typename T>
    T read(uintptr_t addr) {
        T res;
		
        if (this->read(addr, &res, sizeof(T)))
		{
		    //  long low = res & 0xffffffff;
            return res;
			}
        return {};
    }
    
    
    template <typename T>
    bool write(uintptr_t addr,T value) {
        return this->write(addr, &value, sizeof(T));
    }
    char* 获取类名(long addr)
    {
    int id = this->读取整数(addr + 0x10);
    long ye = this->读取指针(Gname + (id / 0x4000) * 4);
    long xu = this->读取指针(ye + (id % 0x4000) * 4);
    static char Item[256];
    read(xu + 0x8, Item, sizeof(Item));
    return Item;
    }
    uintptr_t 获取基址头(char* name) {
        MODULE_BASE mb;
        char buf[0x5000];
        strcpy(buf,name);
        mb.pid = this->pid;
        mb.name = buf;

        if (ioctl(fd, OP_MODULE_BASE, &mb) != 0) {
            return 0;
        }
        return mb.base;
    }
};

long 获取基址头(char * name) 

{
	char*phgsr;
	char jjjj_N[64];
	long startaddr = 0;
	char path[256],line[1024];
	bool bssOF = false,LastIsSo = false;
	strcpy(jjjj_N,name);
	phgsr = strtok(jjjj_N,":");
	name = phgsr;
	phgsr = strtok(NULL,":");
	if(phgsr)
	{if(strcmp(phgsr,"bss")==0)	
			{
			bssOF = true;
		}
	}
	sprintf(path,"/proc/%d/maps",pid);
	FILE*p = fopen(path,"r");
	if(p)
	{
		while(fgets(line,sizeof(line),p))
		{
			if(LastIsSo)
			{
				if(strstr(line,"[anon:.bss]")!=NULL)
				{
					sscanf(line,"%lx-%*lx",&startaddr);
					break;
				}
				else
				{
					LastIsSo = false;
				}
			}
			if(strstr(line,name)!=NULL)
			{
				if(!bssOF)
				{
					sscanf(line,"%lx-%*lx",&startaddr);
					break;
				}
				else
				{
					LastIsSo = true;
				}
			}
		}
		fclose(p);
	}
	return startaddr;
}


static c_driver *独久 = new c_driver();


struct Vector2A {
    float X;
    float Y;

    Vector2A() {
        this->X = 0;
        this->Y = 0;
    }

    Vector2A(float x, float y) {
        this->X = x;
        this->Y = y;
    }
};


struct Vector3A {
    float X;
    float Y;
    float Z;

    Vector3A() {
        this->X = 0;
        this->Y = 0;
        this->Z = 0;
    }

    Vector3A(float x, float y, float z) {
        this->X = x;
        this->Y = y;
        this->Z = z;
    }

};

struct Vector3{
    //这边重定义一个xzy形式的坐标(因为u3d是xzy);
    float X;
    float Z;
    float Y;

    Vector3() {
        this->X = 0;
        this->Z = 0;
        this->Y = 0;
    }

    Vector3(float x, float z, float y) {
        this->X = x;
        this->Z = z;
        this->Y = y;
    }

};

Vector2A WorldToScreen(Vector3A obj, float matrix[16], float ViewW)
{
    float x =
        px + (matrix[0] * obj.X + matrix[4] * obj.Y + matrix[8] * obj.Z + matrix[12]) / ViewW * px;
    float y =
        py - (matrix[1] * obj.X + matrix[5] * obj.Y + matrix[9] * obj.Z + matrix[13]) / ViewW * py;

    return Vector2A(x, y);
}

//static CDriver* driver = new CDriver();
