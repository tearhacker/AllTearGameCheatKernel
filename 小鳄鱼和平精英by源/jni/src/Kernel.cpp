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
#include "辅助类.h"



#include "内置驱动/shua.h"


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
						printf("[-]驱动文件：%s\n", file_path);
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

int Kernel::symbol_file(const char *filename) {
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
		
    char *Kernel::driver_path() {
		// 打开目录
		const char *dev_path = "/dev";
		DIR *dir = opendir(dev_path);
		if (dir == NULL){
			printf("无法打开/dev目录\n");
			return NULL;
		}

		char *files[] = { "CheckMe", "Ckanri", "lanran","video188"};
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
					printf("驱动文件：%s\n", file_path);
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
						//printf("驱动文件：%s\n", file_path);
						closedir(dir);
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

bool Kernel::init_key(char* key) {
    char buf[0x100];
		strcpy(buf,key);
		if (ioctl(fd, OP_INIT_KEY, buf) != 0) {
			return false;
		}
		return true;
  }

#include <sys/utsname.h>

bool check_kernel_version(int target_major, int target_minor) {
        struct utsname buf;
        if (uname(&buf) != 0) {
            perror("uname error");
            return false;
        }

        int major = 0, minor = 0;
        if (sscanf(buf.release, "%d.%d", &major, &minor) != 2) {
            fprintf(stderr, "解析内核版本失败\n");
            return false;
        }

        return (major == target_major && minor >= target_minor);
    }
    
Kernel::Kernel() {

        char *GT驱动 = GT();
		fd = open(GT驱动, O_RDWR);
    /*
     shuaru();
        char *device_name = driver_path();
        

        if (!device_name) {
            fprintf(stderr, "[-] 找不到驱动\n");
            exit(EXIT_FAILURE);
        }

        fd = open(device_name, O_RDWR);
        free(device_name);

        if (fd == -1) {
            perror("[-] 打开失败");
            exit(EXIT_FAILURE);
        }   
     
        if (!check_kernel_version(6, 6)) {
            if (!Kernel::init_key("87359214603758412666")) {
                printf("[-] 你好像没有刷驱动哦…\n");
                exit(EXIT_FAILURE);
            }
        } else {
        
        }
        */
}

Kernel::~Kernel() {
  if (fd > 0)
  close(fd);
}

void Kernel::初始化读写(int pid) {
  this->pid = pid;
  if (this->pid <= 0) {
    cout << "[-] 选定进程失败\n";
  } else {
    cout << "[-] 读写初始化成功\n";
  }
}

bool Kernel::readv(uintptr_t addr, void *buffer, size_t size) {
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

bool Kernel::writev(uintptr_t addr, void *buffer, size_t size) {
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

uintptr_t Kernel::get_module_base(char* name) {
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

int Kernel::WriteDword(long int addr, int value)
{
	writev(addr, &value, 4);
	return 0;
}

float Kernel::WriteFloat(long int addr, float value)
{
	writev(addr, &value, 4);
	return 0;
}

template<typename T>
T Kernel::Read(uintptr_t addr) {
  T data;
  readv(addr, &data, sizeof(T));
  return data;
}

float Kernel::getFloat(uintptr_t addr) {
  float var = 0;
  readv(addr, &var, 4);
  return var;
}

int Kernel::getDword(uintptr_t addr) {
  int var = 0;
  readv(addr, &var, 4);
  return var;
}

uintptr_t Kernel::getPtr32(uintptr_t addr) {
  unsigned int var = 0;
  readv(addr & 0xFFFFFFFFFF, &var, 4);
  return (var & 0xFFFFFFFFFF);
}

uintptr_t Kernel::getPtr64(uintptr_t addr) {
  unsigned long var = 0;
  readv(addr, &var, 8);
  return (var);
}
char Kernel::getByte(unsigned long addr)
{
	char var = 0;
	readv(addr, &var, 1);
	return (var);
}

void Kernel::writefloat(unsigned long addr, float data) {
  writev(addr, &data, 4);
}

void Kernel::writedword(unsigned long addr, int data) {
  writev(addr, &data, 4);
}

void Kernel::writeptr(unsigned long addr, uintptr_t data) {
  writev(addr, &data, 8);
}

int Kernel::getPID(const char* packageName) {
  int id = -1;
  DIR* dir;
  FILE* fp;
  char filename[64];
  char cmdline[64];
  struct dirent* entry;
  dir = opendir("/proc");
  while ((entry = readdir(dir)) != NULL) {
    id = atoi(entry->d_name);
    if (id != 0) {
      sprintf(filename, "/proc/%d/cmdline", id);
      fp = fopen(filename, "r");
      if (fp) {
        fgets(cmdline, sizeof(cmdline), fp);
        fclose(fp);
        if (strcmp(packageName, cmdline) == 0) {
          return id;
        }
      }
    }
  }
  closedir(dir);
  return -1;
}

void Kernel::getUTF8(char * buf, unsigned long namepy) {
  unsigned short buf16[16] = { 0 };
  readv(namepy, buf16, 28);
  unsigned short *pTempUTF16 = buf16;
  char *pTempUTF8 = buf;
  char *pUTF8End = pTempUTF8 + 32;
  while (pTempUTF16 < pTempUTF16 + 28) {
    if (*pTempUTF16 <= 0x007F && pTempUTF8 + 1 < pUTF8End) {
      *pTempUTF8++ = (char) * pTempUTF16;
    } else if (*pTempUTF16 >= 0x0080 && *pTempUTF16 <= 0x07FF && pTempUTF8 + 2 < pUTF8End) {
      *pTempUTF8++ = (*pTempUTF16 >> 6) | 0xC0;
      *pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
    } else if (*pTempUTF16 >= 0x0800 && *pTempUTF16 <= 0xFFFF && pTempUTF8 + 3 < pUTF8End) {
      *pTempUTF8++ = (*pTempUTF16 >> 12) | 0xE0;
      *pTempUTF8++ = ((*pTempUTF16 >> 6) & 0x3F) | 0x80;
      *pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
    } else {
      break;
    }
    pTempUTF16++;
  }
}