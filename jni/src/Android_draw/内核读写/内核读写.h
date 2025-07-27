#include <sys/fcntl.h>
#include <sys/ioctl.h> 
#include <fstream>
#include <regex>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/sysmacros.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <dirent.h>
#include <malloc.h>
#include <thread>
#include <sys/mman.h>
#include <sys/uio.h>
#include <math.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <locale>
#include <string>
#include <dlfcn.h>
#include <sys/utsname.h>
#include "morishima_fonts.hpp"


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
size_t file_name_length;
int pid;
float px,py;
//我需要删除V9驱动
char del[256]="unlink   ";
char * delname;
#include "Android_kernel/MyDriver.h"//菜鸡驱动
//霸王龙
char*drivername;//随机设备节点
char path[256];


float top;
float MIDDLE;
int has_upper = 0;
int has_lower = 0;
int has_symbol = 0;
int has_digit = 0;
char* nh;
char* DEVICE_NAMEdragon;
#define orangedriver "/dev/XIHHYUE"//橘子驱动节点
#define DEVICE_NAMEhutao "/dev/k|bJEdWu]]"
//#define DEVICE_NAMEdragon "/dev/ywnsak"//霸王龙驱动
#define MAX_LINE_LENGTH 1024

void extractNumbers(const char *str, char *numStr) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (isdigit(str[i])) {
            numStr[j++] = str[i];
        }
    }
    numStr[j] = '\0'; // 添加字符串结束符
}


class c_driver {
private:
    int fd;
    pid_t pid;
    std::string devicePath;
   
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
        OP_HIDE_PROCESS = 0x804,
    };

	int symbol_file(const char *filename) {
		//判断文件名是否含小写并且不含大写不含数字不含符号
		int length = strlen(filename);
		for (int i = 0; i < length; i++) {
			if (islower(filename[i])) {
				has_lower = 1;
			} else if (isupper(filename[i])) {
				has_upper = 1;
			} else if (ispunct(filename[i])) {
				has_symbol = 1;
			} else if (isdigit(filename[i])) {
				has_digit = 1;
			}
		}
		return has_lower && !has_upper && !has_symbol && !has_digit;
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




//光速10.6qx开源对接   大牛开源
char* execCom(const char* shell)
{
    FILE *fp = popen(shell, "r");

    if (fp == NULL)
    {
        perror("popen failed");
        return NULL;
    }

    char buffer[256];
    char *result = (char *)malloc(1000); // allocate memory for the result string
    result[0] = '\0';                  // initialize as an empty string

    // Read and append output of the first command to result
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        strcat(result, buffer);
    }
    pclose(fp);
    return result;
}

// 修复createDriverNode和removeDeviceNode函数
void createDriverNode(char *path, int major_number, int minor_number)
{
    std::string command = "mknod " + std::string(path) + " c " + std::to_string(major_number) + " " + std::to_string(minor_number);
    system(command.c_str());
   // printf("[-] 创建 %s，主设备号：%d，次设备号：%d", path, major_number, minor_number);
}

// 删除驱动节点
// 新的函数，用于删除设备节点
void removeDeviceNode(char* path) {
        // printf("%s\n",path);
        if (unlink(path) == 0) {
          //  printf("[-] 驱动安全守护已激活\n");
             // cerr << "已删除设备节点：" << devicePath << endl;
        } else {
            printf("[-] 驱动安全守护执行错误\n");
             // perror("删除设备节点时发生错误");
        }
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
    		               dev_t dev123 = makedev(major(info.st_rdev), minor(info.st_rdev));
    		               if(mknod(dev_path, mode, dev123) != -1){
    		                 // printf("[+] mknod : %d 成功\n", major(info.st_rdev));
    		               }
    		               ID = open(dev_path,O_RDWR);
    		               if(ID != -1){
    		                  printf("[+] 驱动挂载成功\n注意菜单打开方式 当前免费请勿贩卖\n");
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
    	printf("[-] 驱动挂载失败\n");
    	exit(1);
    	return -1;
   }







char*drivername;//随机设备节点
char path[256];
  //获取随机设备驱动中
    void getxuehua(){
    	printf("\033[35;1m");		// 粉红色
	printf("qx5雪花驱动系列！\n");
DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir("/dev");
    if (dir == NULL) {
      //  perror("Error opening directory");
      printf("打开失败");
        //return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
      //  char path[256];
        sprintf(path, "/dev/%s", entry->d_name);

        if (stat(path, &fileStat) < 0) {
         // printf("打开失败因为没有这个文件");;
            continue;
        }

        // Check if the file has crw permissions, starts with specific strings, and has a name length of 6
        if ((fileStat.st_mode & S_IFMT) == S_IFCHR &&
            (fileStat.st_mode & S_IRUSR) &&
            (fileStat.st_mode & S_IWUSR) &&
            (strncmp(entry->d_name, "vid", 3) != 0) &&
            (strncmp(entry->d_name, "std", 3) != 0) &&
            (strncmp(entry->d_name, "tty", 3) != 0) &&
            (strncmp(entry->d_name, "gps", 3) != 0) &&
            (strncmp(entry->d_name, "acc", 3) != 0) &&
            (strncmp(entry->d_name, "bin", 3) != 0) &&
            (strncmp(entry->d_name, "sen", 3) != 0) &&
            (strncmp(entry->d_name, "MAIN", 3) != 0) && 
            (strncmp(entry->d_name, "uinp", 3) != 0) &&
            (strncmp(entry->d_name, "apu", 3) != 0) &&    
            (strncmp(entry->d_name, "ran", 3) != 0) && 
            (strncmp(entry->d_name, "ash", 3) != 0) &&
            (strncmp(entry->d_name, "mtd", 3) != 0) &&        
            
        strncmp(entry->d_name, "std", 3) != 0
        &&
        strncmp(entry->d_name, "sys", 3) != 0
        &&
        strncmp(entry->d_name, "gps", 3) != 0
        &&
        strncmp(entry->d_name, "gun", 3) != 0
        &&
        strncmp(entry->d_name, "hwm", 3) != 0
        &&
        strncmp(entry->d_name, "loop", 4) != 0
        &&
        strncmp(entry->d_name, "input", 5) != 0
        &&
        strncmp(entry->d_name, "radio", 5) != 0
        &&
        strncmp(entry->d_name, "media", 5) != 0
        &&
        strncmp(entry->d_name, "binder", 6) != 0
        &&
        strncmp(entry->d_name, "membuf", 6) != 0
        &&
        strncmp(entry->d_name, "254", 3) != 0
        &&
        strncmp(entry->d_name, "camlog", 6) != 0
        &&
        strncmp(entry->d_name, "event", 5) != 0
        &&
        strncmp(entry->d_name, "rfkill", 6) != 0
        &&
        strncmp(entry->d_name, "mmc1", 4) != 0
        &&
        strncmp(entry->d_name, "extcon", 6) != 0
        &&
        strncmp(entry->d_name, "bt-dev", 6) != 0
        &&
        strncmp(entry->d_name, "ashmem", 6) != 0
        &&
        strncmp(entry->d_name, "ir_spi", 6) != 0
        &&
        strncmp(entry->d_name, "uinput", 6) != 0
        &&
        strncmp(entry->d_name, "hidraw", 6) != 0
        &&
        strncmp(entry->d_name, "time", 4) != 0
        &&
        strncmp(entry->d_name, "mtd0", 4) != 0
        &&
        strncmp(entry->d_name, "dummy0", 6) != 0
        &&
        strncmp(entry->d_name, "nq-", 3) != 0
        &&
        strncmp(entry->d_name, "ftrace", 6) != 0
        &&
        strncmp(entry->d_name, "hwmon0", 6) != 0
        &&
        strncmp(entry->d_name, "random", 6) != 0
        &&
        strncmp(entry->d_name, "tp_dev", 6) != 0
        &&
        strncmp(entry->d_name, "wakeup", 6) != 0
        &&
        strncmp(entry->d_name, "video", 5) != 0
        &&
        strncmp(entry->d_name, "fg1_", 4) != 0
        &&
        strncmp(entry->d_name, "tx_mac", 6) != 0
        &&
        strncmp(entry->d_name, "sp_ssr", 6) != 0
        &&
        strncmp(entry->d_name, "gun",3) != 0
        &&
        strncmp(entry->d_name, "radio", 5) != 0
        &&
        strncmp(entry->d_name, "drm",3) != 0
        &&
        strncmp(entry->d_name, "apusys", 6) != 0
        &&
        strncmp(entry->d_name, "tfa", 3) != 0
        &&
        strncmp(entry->d_name, "tz_", 3) != 0
        &&
        strncmp(entry->d_name, "mml", 3) != 0
        &&
        strncmp(entry->d_name, "mdm", 3) != 0
        &&
        strncmp(entry->d_name, "common", 6) != 0
        &&
        strncmp(entry->d_name, "gunyah", 6) != 0

        &&
        strncmp(entry->d_name, "rx_", 3) != 0
        &&
        strncmp(entry->d_name, "f_midi",6) != 0
        &&
        strncmp(entry->d_name, "tty", 3) != 0
            &&
            (strncmp(entry->d_name, "med", 3) != 0) && 
            (strncmp(entry->d_name, "ipa", 3) != 0) &&    

            (strncmp(entry->d_name, "gbt", 3) != 0) &&    
            (strncmp(entry->d_name, "gun", 3) != 0) && 
            (strncmp(entry->d_name, "mau", 3) != 0) &&   

            (strncmp(entry->d_name, "mem", 3) != 0) &&  
            (strncmp(entry->d_name, "rfk", 3) != 0) &&     
                                                          (strncmp(entry->d_name, "qbt", 3) != 0) &&           
                                                          (strncmp(entry->d_name, "sp", 2) != 0) &&   
                                                          (strncmp(entry->d_name, "nq", 2) != 0) &&                                             (strncmp(entry->d_name, "pt", 2) != 0) &&                                            
            (strlen(entry->d_name) == 6)) {
            //printf("%s\n", path);
            drivername=path;//雪花设备名
           printf("雪花设备%s\n",drivername);
            break;
            //如果雪花加载了驱动，那么必然是第一个，没有为什么就是第一个
        }
    }

    closedir(dir);
   // return  drivername;
    
}
//获取随机设备驱动结束




void 专属驱动GT()
{
printf("\033[33;3m");	
printf("特别版驱动正在自动刷入中...\n");
   struct utsname unameData;
   int result;
   result = uname(&unameData);
   if (result == 0)
   {
      printf(("你的内核版本:%s\n"), unameData.release);
   }
   if(strstr(unameData.release,("5.15"))!=0){
      printf(("已兼容的内核版本5.15\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/GTDriver/515.ko  --output /data/local/tmp/gt515.ko"));
    system ("chmod +x  /data/local/tmp/gt515.ko");
    system("su -c insmod  /data/local/tmp/gt515.ko");
    }
    else
    if(strstr(unameData.release,("5.10"))!=0){
    printf(("已兼容的内核版本5.10\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/GTDriver/510.ko  --output /data/local/tmp/gt510.ko"));
    system ("chmod +x  /data/local/tmp/gt510.ko");
    system("su -c insmod  /data/local/tmp/gt510.ko");
  
   return ;
    }
    else
    if(strstr(unameData.release,("6.1"))!=0){
    printf(("已兼容的内核版本6.10\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/GTDriver/61.ko  --output /data/local/tmp/gt61.ko"));
    system ("chmod +x  /data/local/tmp/gt61.ko");
    system("su -c insmod  /data/local/tmp/gt61.ko");
   return ;
    }
    else
    if(strstr(unameData.release,("4.14"))!=0)
    {
    printf(("已兼容的内核版本414186\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/GTDriver/414186.ko  --output /data/local/tmp/gt414186.ko"));
    system ("chmod +x  /data/local/tmp/gt414186.ko");
    system("su -c insmod  /data/local/tmp/gt414186.ko");
    return;
    }
    else
    if(strstr(unameData.release,("4.9"))!=0)
    {
    printf(("已兼容的内核版本49186\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/GTDriver/49186.ko  --output /data/local/tmp/gt49186.ko"));
    system ("chmod +x  /data/local/tmp/gt49186.ko");
    system("su -c insmod  /data/local/tmp/gt49186.ko");
    }
    else
        if(strstr(unameData.release,("4.19"))!=0){
            printf(("已兼容的内核版本419113\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/GTDriver/419113.ko  --output /data/local/tmp/gt419113.ko"));
    system ("chmod +x  /data/local/tmp/gt419113.ko");
    system("su -c insmod  /data/local/tmp/gt419113.ko");
    return;            
        }else
    printf("请主动刷驱动");
    return;
}



void 内核版本()
{
printf("自动刷入内核支持5.10 4.14.186  4.9.186  4.19.xxx  5.15   请k40g找我刷kernelsu软件  k40游戏手机使用面具将会拉闸180天,请换ksu\n");
   struct utsname unameData;
   int result;
   result = uname(&unameData);
   if (result == 0)
   {
      printf(("你的内核版本:%s\n"), unameData.release);
   }
   if(strstr(unameData.release,("5.15"))!=0){
      printf(("已兼容的内核版本5.15\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx/515.sh  --output /data/local/tmp/515.sh"));
    system ("chmod +x  /data/local/tmp/515.sh");
    system("su -c /data/local/tmp/515.sh");
    }
    else
    if(strstr(unameData.release,("5.10"))!=0){
    printf(("已兼容的内核版本5.10\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx/510.sh  --output /data/local/tmp/510.sh"));
    system ("chmod +x  /data/local/tmp/510.sh");
    system("su -c /data/local/tmp/510.sh");
   return ;
    }
    else
    if(strstr(unameData.release,("6.1"))!=0){
    printf("\033[33;1m");		// 黄色
    printf(("小米14和小米14p内核6.1内核版本号\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx/61.sh  --output /data/local/tmp/61.sh"));
    system ("chmod +x  /data/local/tmp/61.sh");
    system("su -c /data/local/tmp/61.sh");
   return ;
    }
    else
    if(strstr(unameData.release,("4.14"))!=0)
    {
    printf(("已兼容的内核版本4.14.186\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx/414186.sh  --output /data/local/tmp/414186.sh"));
    system ("chmod +x  /data/local/tmp/414186.sh");
    system("su -c /data/local/tmp/414186.sh");
    
  //  system(("su -c rm -rf /data/local/tmp/驱动.sh"));
    return;
    }
    else
    if(strstr(unameData.release,("4.9"))!=0)
    {
    printf(("已兼容的内核版本4.9\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx/414186.sh  --output /data/local/tmp/414186.sh"));
    system ("chmod +x  /data/local/tmp/414186.sh");
    system("su -c /data/local/tmp/414186.sh");
    return;
    }
    else
        if(strstr(unameData.release,("4.19"))!=0){
            printf(("已兼容的内核版本4.19\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx/41981.sh  --output /data/local/tmp/41981.sh"));
    system ("chmod +x  /data/local/tmp/41981.sh");
    system("su -c /data/local/tmp/41981.sh");
    return;            
        }else
    printf("请主动刷驱动");
    return;
}

void 霸王龙驱动(){

system(("echo -e 正在为你挂载霸王龙驱动"));

FILE *hh=fopen("/data/local/tmp/stabledriver.sh","r");//读取文件是否存在
if (hh == NULL)
{
printf("文件没有下载,正在下载文件....\n");
system(("curl https://99778.cn/wp/down.php/029276f1e538c51842cdea828c0cfdd4.sh  --output /data/local/tmp/stabledriver.sh"));
//system ("");
}
printf("文件下载完成请重新打开刷入对应驱动数字,否则重启\n\n\n");
    system ("chmod +x  /data/local/tmp/stabledriver.sh");
    system("su -c /data/local/tmp/stabledriver.sh");
    return;           
    }
    
    
    
    

    
    
    
    
    
    
    


void qx112自动刷入()
{
printf("正在刷入tg防检测魔改qx11.2完美驱动 支持5.1 5.15 6.1  4.14.186  5.4自动刷入驱动\n");
   struct utsname unameData;
   int result;
   result = uname(&unameData);
   if (result == 0)
   {
      printf(("你的内核版本:%s\n"), unameData.release);
   }
   if(strstr(unameData.release,("5.15"))!=0){
      printf(("已兼容的内核版本5.15\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx112/tg515.sh  --output /data/local/tmp/tg515.sh"));
    system ("chmod +x  /data/local/tmp/tg515.sh");
    system("su -c /data/local/tmp/tg515.sh");
    }
    else
    if(strstr(unameData.release,("5.10"))!=0){
    printf(("已兼容的内核版本5.10\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx112/tg112510.sh  --output /data/local/tmp/tg510.sh"));
    system ("chmod +x  /data/local/tmp/tg510.sh");
    system("su -c /data/local/tmp/tg510.sh");
   return ;
    }else 
    if
    (strstr(unameData.release,("5.4"))!=0)
    {
    printf("下载文件在data/local/tmp");
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx112/tg54147.sh  --output /data/local/tmp/qx112关于54147版本.sh"));
    system ("chmod +x  /data/local/tmp/qx112关于54147版本.sh");
    system("su -c /data/local/tmp/qx112关于54147版本.sh");
    }
    else
    if(strstr(unameData.release,("6.1"))!=0){
    printf("\033[33;1m");		// 黄色
    printf(("小米14和小米14p内核6.1内核版本号\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx112/tg61.sh  --output /data/local/tmp/tg61.sh"));
    system ("chmod +x  /data/local/tmp/tg61.sh");
    system("su -c /data/local/tmp/tg61.sh");
   return ;
    }
    else
    if(strstr(unameData.release,("4.14"))!=0)
    {
    printf(("已兼容的内核版本4.14.186\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx112/tg414186.sh  --output /data/local/tmp/tg414186.sh"));
    system ("chmod +x  /data/local/tmp/tg414186.sh");
    system("su -c /data/local/tmp/tg414186.sh");
    
  //  system(("su -c rm -rf /data/local/tmp/驱动.sh"));
    return;
    }
    else
    if(strstr(unameData.release,("4.9"))!=0)
    {
    printf(("已兼容的内核版本4.9\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx112/tg49186.sh  --output /data/local/tmp/tg49186.sh"));
    system ("chmod +x  /data/local/tmp/tg49186.sh");
    system("su -c /data/local/tmp/tg49186.sh");
    return;
    }
    else
        if(strstr(unameData.release,("4.19"))!=0){
            printf(("已兼容的内核版本4.19\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx112/tg41957.sh  --output /data/local/tmp/tg41957.sh"));
    system ("chmod +x  /data/local/tmp/tg41957.sh");
    system("su -c /data/local/tmp/tg41957.sh");
    return;            
        }else
    printf("请主动刷驱动");
    return;
}

    
     
void qx113自动刷入()
{
printf("正在刷入泪心魔改qx11.3完美驱动 支持5.1 5.15 6.1  4.14.186  5.4自动刷入驱动\n");
   struct utsname unameData;
   int result;
   result = uname(&unameData);
   if (result == 0)
   {
      printf(("你的内核版本:%s\n"), unameData.release);
   }
   if(strstr(unameData.release,("5.15"))!=0){
      printf(("已兼容的内核版本5.15\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx13/515.sh  --output /data/local/tmp/tg515.sh"));
    system ("chmod +x  /data/local/tmp/tg515.sh");
    system("su -c /data/local/tmp/tg515.sh");
    }
    else
    if(strstr(unameData.release,("5.10"))!=0){
    printf(("已兼容的内核版本5.10\n"));
    system(("echo -e 正在为你挂载泪心魔改驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx13/510.sh  --output /data/local/tmp/tg510.sh"));
    system ("chmod +x  /data/local/tmp/tg510.sh");
    system("su -c /data/local/tmp/tg510.sh");
   return ;
    }else 
    if
    (strstr(unameData.release,("5.4"))!=0)
    {
    printf("下载文件在data/local/tmp");
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx13/5417.sh  --output /data/local/tmp/qx112关于54147版本.sh"));
    system ("chmod +x  /data/local/tmp/qx112关于54147版本.sh");
    system("su -c /data/local/tmp/qx112关于54147版本.sh");
    }
    else
    if(strstr(unameData.release,("6.1"))!=0){
    printf("\033[33;1m");		// 黄色
    printf(("小米14和小米14p内核6.1内核版本号\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx13/61.sh  --output /data/local/tmp/tg61.sh"));
    system ("chmod +x  /data/local/tmp/tg61.sh");
    system("su -c /data/local/tmp/tg61.sh");
   return ;
    }
    else
    if(strstr(unameData.release,("4.14"))!=0)
    {
    printf(("已兼容的内核版本4.14.186\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx13/414186.sh  --output /data/local/tmp/tg414186.sh"));
    system ("chmod +x  /data/local/tmp/tg414186.sh");
    system("su -c /data/local/tmp/tg414186.sh");
    
  //  system(("su -c rm -rf /data/local/tmp/驱动.sh"));
    return;
    }
    else
    if(strstr(unameData.release,("4.9"))!=0)
    {
    printf(("已兼容的内核版本4.9\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx13/61.sh  --output /data/local/tmp/tg49186.sh"));
    system ("chmod +x  /data/local/tmp/tg49186.sh");
    system("su -c /data/local/tmp/tg49186.sh");
    return;
    }
    else
        if(strstr(unameData.release,("4.19"))!=0){
            printf(("已兼容的内核版本4.19\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx13/419157.sh  --output /data/local/tmp/tg41957.sh"));
    system ("chmod +x  /data/local/tmp/tg41957.sh");
    system("su -c /data/local/tmp/tg41957.sh");
    return;            
        }else
    printf("请主动刷驱动");
    return;
}

void zeze()
{
printf("泽泽定制驱动 只有5.10和5.15内核版本号\n");
   struct utsname unameData;
   int result;
   result = uname(&unameData);
   if (result == 0)
   {
      printf(("你的内核版本:%s\n"), unameData.release);
   }
   if(strstr(unameData.release,("5.15"))!=0){
      printf(("已兼容的内核版本5.15\n"));
    system(("echo -e 正在为你挂载驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx/515zeze.sh  --output /data/local/tmp/zeze515.sh"));
    system ("chmod +x  /data/local/tmp/zeze515.sh");
    system("su -c /data/local/tmp/zeze515.sh");
    }
    else
    if(strstr(unameData.release,("5.10"))!=0){
    printf(("已兼容的内核版本5.10\n"));
    system(("echo -e 正在为你泽泽驱动"));
    system(("curl https://gitee.com/thoughtful123/for-tear-glory/raw/master/driverqx/510zeze.sh  --output /data/local/tmp/zeze510.sh"));
    system ("chmod +x  /data/local/tmp/zeze510.sh");
    system("su -c /data/local/tmp/zeze510.sh");
   return ;
    }
    }


void hide_process()
    {
    ioctl(fd,OP_HIDE_PROCESS);
    }




   //小菜鸡对接驱动
                                                          #define devxxx "/dev/"
 char* find(const char* directory_path) {
        DIR* dir = opendir(directory_path); // 打开目录        
        if (dir == NULL) 
        {
        perror("无法打开目录");
        return NULL;
        }        
        struct dirent* entry;        
        while ((entry = readdir(dir)) != NULL)
        {
            if (strlen(entry->d_name) == 30)
            {
                closedir(dir);
                return strdup(entry->d_name); 
            }
        }        
        closedir(dir); // 遍历完了关闭打开的目录
        return NULL; // 什么也没找到
    }                                                                                 
    void  conncaiji()
    {
    char *Fname = find(devxxx);
	    char path[35];
	    sprintf(path,"/dev/%s",Fname);
	    fd = open(path, O_RDWR); 
        if (fd == -1) {
              printf("\n[-] 驱动连接失败\n[-] 找不到驱动路径：%s\n",path);
        } else {
        printf("\n[-] 驱动连接成功。\n");
            //  printf("\n[-] 驱动连接成功。\n[-] 驱动路径：%s\n",path);
        }
    }                                 
    
void 内核版本显示(){
struct utsname unameData;
int result;
result = uname(&unameData);
if (result == 0) {
printf(("\n 您手机的内核版本Kernel_version:%s"), unameData.release);
}
}

    c_driver(){
    
    printf("\033[35;1m");	
   // printf("(其它)输入一加安装一加专用驱动(输入一加)\n");
   
   printf("\033[32;1m");		// 绿色
   
/*   printf("选择1自动刷入qx11.3泪心魔改驱动\n");
   printf("\033[33;5m");	//黄色
   printf("选择2GT驱动(高危级)\n");
   printf("\033[35;1m");	
   printf("选择3刷入泽泽驱动(使用qx11.3对接方式)\n");
   printf("选择0取消自动刷入驱动\n");
   printf("温馨提示：霸王龙驱动文件下载完毕后请重新打开辅助重新选择2,否则刷入驱动重启！\n");
    printf("\n输入1-3确认自动刷入驱动,0取消刷入:");
			int 驱动选择;
			scanf("%d",&驱动选择);
	if(驱动选择==1){
	qx113自动刷入();
	}
	
    if(驱动选择==2)
    {
    专属驱动GT();
    }

			if(驱动选择==3)
    {
    zeze();
    }
			
	if(驱动选择==0)
    {
    //霸王龙驱动();
    printf("\n取消自动刷入驱动成功,请主动刷入想玩的驱动!\n");
    //exit(0);
    }
    
    */
   

printf("\033[35;1m");		// 粉红色
    printf("qx11.4或者qx10.6驱动好点  或者使用内置驱动  反正必须刷驱动\n ");
    内核版本显示();
        printf("\n1.选择1光速对接qx雪花驱动"); 
    printf("\n2.小菜鸡驱动(内置)");
    int 选择值;
    printf("\n请输入对接驱动方案(右下角im唤醒键盘):");
     scanf("%d",&选择值);
     if(选择值==1){
	 fd= OpenFd();
	}
      else if(选择值==2)
    {
      叽叽叽 *小菜鸡 = new 叽叽叽();       // 顺序一，刷入内核。
	  conncaiji();
    }else{
    printf("请输入1重新链接驱动  退出程序中！");
    exit(0);
    }
    
    
    
    


    
  }    
	
	
 
	
    
    ~c_driver() {
        if (fd > 0)
            close(fd);
			
    }
	
	bool isMemoryTrap(uintptr_t addr) {
 if (addr < 0x10000000 || addr > 0xFFFFFFFFFF || addr % 4 != 0) {
        return false;
    }

    static int pageSize = getpagesize();
    unsigned char vec = 0;
    unsigned long start = addr & (~(pageSize - 1));
#if __aarch64__
    

#elif __arm__
    register int64_t r7 asm("r7") = SYS_mincore;
    register int64_t r0 asm("r0") = start;
    register int64_t r1 asm("r1") = pageSize;
    register int64_t r2 asm("r2") = (int64_t)&vec;

    asm volatile("swi #0"
    : "=r"(r0)
    : "r"(r7),"0"(r0),"r"(r1),"r"(r2)
    : "memory", "cc");

#endif
    //return vec == 1;
     return true;
      
    
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
    
    char *string_char(string str)
{
    return const_cast < char *>(str.c_str());
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
    }int 是否可读(uintptr_t addr)
{
    if (addr < 0x1000000000 || addr>0xefffffffff || addr % 0x8 != 0)
        return 0;
    return 1;
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
    long 读取指针(long 地址){
    long res;
    if (this->read(地址,&res,sizeof(uintptr_t))){
		if(isMemoryTrap(res)){
			return res;
		}
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
    bool write(uintptr_t addr,T value) {
        return this->write(addr, &value, sizeof(T));
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
int symbol_file(const char *filename)
{
	int length = strlen(filename);

	for (int i = 0; i < length; i++)
	{
		if (isupper(filename[i]))
		{
			has_upper = 1;
		}
		else if (islower(filename[i]))
		{
			has_lower = 1;
		}
		else if (ispunct(filename[i]))
		{
			has_symbol = 1;
		}
		else if (isdigit(filename[i]))
		{
			has_digit = 1;
		}
	}

	return has_upper && has_lower && !has_symbol && !has_digit;
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


static c_driver *driver = new c_driver();


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