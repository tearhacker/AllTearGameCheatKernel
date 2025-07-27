/////////内核读写/////////
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
#include <vector>  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
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
#include "morishima_fonts.hpp"

using namespace std;
int pid,px,py;
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


	//sleep(3);
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
    	int ID;
    	int PPID;
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
    		 //    printf("[+] 软链: %s  PID: %d\n", path, PPID);
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
    		         //   printf("[*] 设备路径: %s  设备 ID: %lu\n", dev_path, info.st_dev);
    		         //   printf("[*] 主设备号: %lu\n", major(info.st_rdev));
    		   //         printf("[*] 次设备号: %lu\n", minor(info.st_rdev));
    		            if(access(dev_path,F_OK) == 0){  //检查文件是否存在
    		               ID = open(dev_path,O_RDWR);
    		               if(ID != -1){
    		               //  printf("[+] 驱动挂载成功\n");
    		                 if(unlink(dev_path) == 0) {
    		                   // printf("[+] 驱动守护中\n");
    		                    auto end = std::chrono::high_resolution_clock::now();  // 获取结束时间
    		                    float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); //获毫秒
    		                    //printf("[+] 读取驱动用时: %.f ms\n", elapsed_ns);
    		                    return ID;
    		                    //return 0;
    		                 }
    		               }
    		            }  else { //驱动已经隐藏
    		              // printf("[+] 驱动已隐藏创建驱动中\n");
    		               mode_t mode = S_IFCHR | 0666; // 创建一个命名管道，权限为读写
    		               dev_t dev = makedev(major(info.st_rdev), minor(info.st_rdev));
    		               if(mknod(dev_path, mode, dev) != -1){
    		                 // printf("[+] mknod : %d 成功\n", major(info.st_rdev));
    		               }
    		               ID = open(dev_path,O_RDWR);
    		               if(ID != -1){
    		                  printf("[+] 驱动挂载成功\n\n");
    		                  {
    		                  system("touch /data/泪心源码使用协议.txt");
    		                  system("touch /data/local/tmp/泪心保护版权文件.txt");
    		                  
    		                  FILE* hh = fopen("/data/adb/泪心QQ2254013571", "r");//读取文件是否存在
if (hh == NULL)
{
system("touch /data/adb/泪心QQ2254013571");
}
    		                  }
    		                  if(unlink(dev_path) != -1){
    		                   // printf("[+] 驱动守护中\n");
    		                    auto end = std::chrono::high_resolution_clock::now();  // 获取结束时间
    		                    float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); //获毫秒
    		                    //printf("[+] 读取驱动用时: %.f ms\n", elapsed_ns);
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
    	printf("[-] 驱动挂载失败  请刷入qx11.4驱动\n");
    	//exit(1);
    	return -1;
   }
     //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
   char *GT() {
	// 打开目录
		//auto startqx = std::chrono::high_resolution_clock::now();  // 获取起始时间
		const char *dev_path = "/dev";
		DIR *dir = opendir(dev_path);
		printf("\033[33;1m");//黄色
		//printf("%s\n", ayf);
		if (dir == NULL){
			printf("\033[31;1m");//红色
			printf("无法打开/dev目录\n");
			return NULL;
		}

		char *files[] = { "wanbai", "CheckMe", "Ckanri", "lanran","video188"};
		struct dirent *entry;
		char *file_path = NULL;
		while ((entry = readdir(dir)) != NULL) {
			// 跳过当前目录和上级目录
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				continue;
			}

			size_t path_length = strlen(dev_path) + strlen(entry->d_name) + 2;
			file_path = (char *)malloc(path_length);
			snprintf(file_path, path_length, "%s/%s", dev_path, entry->d_name);
			for (int i = 0; i < 5; i++) {
				if (strcmp(entry->d_name, files[i]) == 0) {
					printf("\033[36;1m");//蓝色
					printf("[-] 驱动文件：%s\n", file_path);
					closedir(dir);
					return file_path;
				}
			}

			// 获取文件stat结构
			struct stat file_info;
			if (stat(file_path, &file_info) < 0) {
				free(file_path);
				file_path = NULL;
				continue;
			}

			// 跳过gpio接口
			if (strstr(entry->d_name, "gpiochip") != NULL) {
				free(file_path);
				file_path = NULL;
				continue;
			}

			// 检查是否为驱动文件
			if ((S_ISCHR(file_info.st_mode) || S_ISBLK(file_info.st_mode))
				&& strchr(entry->d_name, '_') == NULL && strchr(entry->d_name, '-') == NULL && strchr(entry->d_name, ':') == NULL) {
				// 过滤标准输入输出
				if (strcmp(entry->d_name, "stdin") == 0 || strcmp(entry->d_name, "stdout") == 0
					|| strcmp(entry->d_name, "stderr") == 0) {
					free(file_path);
					file_path = NULL;
					continue;
				}
				
				size_t file_name_length = strlen(entry->d_name);
				time_t current_time;
				time(&current_time);
				int current_year = localtime(&current_time)->tm_year + 1900;
				int file_year = localtime(&file_info.st_ctime)->tm_year + 1900;
				//跳过1980年前的文件
				if (file_year <= 1980) {
					free(file_path);
					file_path = NULL;
					continue;
				}
				
				time_t atime = file_info.st_atime;
				time_t ctime = file_info.st_ctime;
				// 检查最近访问时间和修改时间是否一致并且文件名是否是symbol文件
				if ((atime == ctime)/* && symbol_file(entry->d_name)*/) {
					//检查mode权限类型是否为S_IFREG(普通文件)和大小还有gid和uid是否为0(root)并且文件名称长度在7位或7位以下
					if ((file_info.st_mode & S_IFMT) == 8192 && file_info.st_size == 0
						&& file_info.st_gid == 0 && file_info.st_uid == 0 && file_name_length <= 9) {
						printf("\033[36;1m");//蓝色
						printf("[-] 驱动文件：%s\n", file_path);
          //  myInitDeviceDriverName=file_path;
						closedir(dir);
						auto endqx = std::chrono::high_resolution_clock::now();
						//float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(endqx - startqx).count(); //获毫秒
						//printf("[+] 读取驱动用时: %.1f ms\n", elapsed_ns);
						return file_path;
					}
				}
			}
			free(file_path);
			file_path = NULL;
		}
		closedir(dir);
		return NULL;
	}
	
int RT驱动proc节点()
 {
    struct dirent *de;
    DIR *dr = opendir("/proc");
    int fd = -1;
    char *device_path = NULL;

    if (dr == NULL) {
        printf("Could not open /proc directory\n");
        return -1;
    }

    while ((de = readdir(dr)) != NULL) {
        // 过滤掉不符合条件的目录项
        // 过滤掉不符合条件的目录项
        if (strlen(de->d_name) != 6 || 
            strcmp(de->d_name, "NVTSPI") == 0 || 
            strcmp(de->d_name, "ccci_log") == 0 || 
            strcmp(de->d_name, "aputag") == 0 || 
            strcmp(de->d_name, "asound") == 0 || 
            strcmp(de->d_name, "clkdbg") == 0 || 
            strcmp(de->d_name, "driver") == 0 || 
            strcmp(de->d_name, "millet") == 0 || 
            strcmp(de->d_name, "swinfo") == 0 || 
            strcmp(de->d_name, "vmkmsg") == 0 || 
            strcmp(de->d_name, "freeze") == 0 || 
            strcmp(de->d_name, "sensor") == 0 ||
            strcmp(de->d_name, "crypto") == 0 || 
            strcmp(de->d_name, "modules") == 0 || 
            strcmp(de->d_name, "mounts") == 0 || 
            strcmp(de->d_name, "pidmap") == 0 || 
            strcmp(de->d_name, "phoenix") == 0 || 
            strcmp(de->d_name, "uptime") == 0 || 
            strcmp(de->d_name, "kpdpwr") == 0 || 
            strcmp(de->d_name, "pmicWd") == 0 || 
            strcmp(de->d_name, "vmstat") == 0) {
            continue;
        }

        // 检查目录项名称是否为6个字母数字字符
        int is_valid = 1;
        for (int i = 0; i < 6; i++) {
            if (!isalnum(de->d_name[i])) {
                is_valid = 0;
                break;
            }
        }

        if (is_valid) {
            device_path = (char*)malloc(11 + strlen(de->d_name));
            if (device_path == NULL) {
                printf("内存分配失败\n");
                closedir(dr);
                return -1;
            }
            sprintf(device_path, "/proc/%s", de->d_name);

            // 检查路径是否为普通文件并尝试打开
            struct stat sb;
            if (stat(device_path, &sb) == 0 && S_ISREG(sb.st_mode)) {
                fd = open(device_path, O_RDWR);
                free(device_path);
                if (fd >= 0) {
                    break;
                }
            } else {
                free(device_path);
            }
        }
    }

    closedir(dr);

    if (fd < 0) {
        printf("\033[32;1m[-]RT驱动PROC推荐驱动获取失败，正在准备对接Hook系列驱动！\n\033[0m"); // 绿色
        printf("\033[32;1m[+]hook驱动请自己刷入，且并非适配全部手机！\n\033[0m"); // 绿色
        printf("~~~~~~~-----------~~~~~------------------------------\n");
        fd = -2;
        //printf("\033[32;1mRT驱动PROC推荐驱动获取失败，正在准备对接Hook系列驱动！\n\033[0m"); // 绿色
        //exit(EXIT_FAILURE);
    } else {
       // driver_type = 1;
        printf("\033[32;1m"); // 绿色
        printf("已经识别到PROC新RT驱动节点并成功打开:%s\n",device_path);
    }

    return fd;
}

	
	int 泪心全驱动()
{
auto startqx = std::chrono::high_resolution_clock::now();  // 获取起始时间
		char *GT驱动 = GT();
		fd = open(GT驱动, O_RDWR);
		auto endqx = std::chrono::high_resolution_clock::now();
		float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(endqx - startqx).count(); //获毫秒
		if (fd > 0) {
			printf("[+] 读取驱动用时: %.f ms\n", elapsed_ns);
			printf("[+] GT/Rt驱动挂载成功\n");
		}
		free(GT驱动);
		if (fd == -1) {
		printf("\033[31;1m");//红色    	   		
    	printf("[-] GT驱动挂载失败,正在对接RT节点proc驱动！\n");
    	// exit(1);
    	    fd = RT驱动proc节点();
		
		  //@TearGame  泪心电报 http://t.me/TearGame        泪心QQ游戏群聊 435539500
 
    
   		
    	}
    	return  fd;
}
	
	public:
	c_driver() {
	fd= OpenFd();
	if(fd==-1)
	{
	泪心全驱动();
	}
      
	}
	~c_driver() {
		//wont be called
		if (fd > 0)
			
			close(fd);
	}

	pid_t initialize(char* name) {
	FILE* fp;
    pid_t pid;
    char cmd[0x100] = "pidof ";

    strcat(cmd, name);
    fp = popen(cmd,"r");
    fscanf(fp,"%d", &pid);
    pclose(fp);
		this->pid = pid;//局部变量this
	 return pid;
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
	addr=addr&0xFFFFFFFFFFFF;
		COPY_MEMORY cm;

		cm.pid = this->pid;
		cm.addr = addr;
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

	template <typename T>
	T read(uintptr_t addr) {
		T res;
		if (this->read(addr, &res, sizeof(T)))
			return res;
		return {};
	}

	template <typename T>
	bool write(uintptr_t addr,T value) {
		return this->write(addr, &value, sizeof(T));
	}

	uintptr_t getModuleBase(char* name) {
		MODULE_BASE mb;
		char buf[0x100];
		strcpy(buf,name);
		mb.pid = this->pid;
		mb.name = buf;

		if (ioctl(fd, OP_MODULE_BASE, &mb) != 0) {
			return 0;
		}
		return mb.base;
	}
};

static c_driver *driver = new c_driver();

/////////完/////////////
/////////完/////////////

uintptr_t getbss(int pid, const char* name) {
    FILE* fp = NULL;
    int cnt = 0;
    long start = 0;
    char tmp[256];
    char fname[128];

    // 构建文件名
    snprintf(fname, sizeof(fname), "/proc/%d/maps", pid);

    // 打开文件
    fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("找不到游戏进程");
        // printf("找不到游戏进程");
        return 0; // 返回0表示失败
    }

    // 读取文件内容
    while (fgets(tmp, sizeof(tmp), fp)) {
        if (cnt == 1) {
            if (strstr(tmp, "[anon:.bss]") != NULL) {
                sscanf(tmp, "%lx-%*lx", &start);
                break;
            }
            else {
                cnt = 0;
            }
        }
        if (strstr(tmp, name) != NULL) {
            cnt = 1;
        }
    }

    // 关闭文件
    fclose(fp);

    return start;
}

long getallmo(int pid,const char* name, int index)
{
	int i = 0;
	long start = 0, end = 0;
    char line[1024] = {0};
    char fname[128];
	sprintf(fname, "/proc/%d/maps", pid);
    FILE *p = fopen(fname, "r");
    if (p)
    {
        while (fgets(line, sizeof(line), p))
        {
            if (strstr(line, name) != NULL)
            {
                i++;
                if (i==index) {
                    sscanf(line, "%lx-%lx", &start,&end);
                    break;
                }
            }
        }
        fclose(p);
    }
    return start;
}
pid_t get_name_pid(char* name) {
    FILE* fp;
    pid_t pid;
    char cmd[0x100] = "pidof ";

    strcat(cmd, name);
    fp = popen(cmd,"r");
    fscanf(fp,"%d", &pid);
    pclose(fp);
    return pid;
}

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

