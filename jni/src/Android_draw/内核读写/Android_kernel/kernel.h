#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <malloc.h>
#include <math.h>
#include <thread>
#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <malloc.h>
#include <math.h>
#include <thread>
#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include <regex.h>
#define dev "/dev/"


class CDriver {
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
		OP_HIDE_PROCESS = 0x804,
	};
	
	
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
	
	public:
	CDriver() {
	    char *Fname = find(dev);
	    char path[35];
	    sprintf(path,"/dev/%s",Fname);
	    fd = open(path, O_RDWR); 
        if (fd == -1) {
              printf("\n[-] 驱动连接失败\n[-] 找不到驱动路径：%s\n",path);
        } else {
              printf("\n[-] 驱动连接成功。\n[-] 驱动路径：%s\n",path);
        }
    }

	~CDriver() {
		//wont be called
		if (fd > 0)
			close(fd);
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
	
	template <class T>
    T write2(long int addr, T value) {
        char lj[64];
        long int handle;
        sprintf(lj, "/proc/%d/mem", pid);
        handle = open(lj, O_RDWR | O_SYNC);
        if (handle == -1) {
            perror("open");
        return 0;
        }

       if (pwrite64(handle, &value, sizeof(T), addr) != sizeof(T)) {
            perror("[-]写入内存区域失败");
            close(handle);
            return 0;
       }
       close(handle);
       return 0;
    }
	
	long 读取指针(long 地址){
        unsigned long var = 0;
        var = this->read<long>(地址);
        if (var > 0xffffffffff)
        var=var%0x10000000000;
        return (var);
    }

	
	uintptr_t get_module_base(char* name) {
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
	
	void getUTF8(char * buf, unsigned long namepy) {
        unsigned short buf16[16] = { 0 };
        read(namepy, buf16, 28);
        unsigned short *pTempUTF16 = buf16;
        char *pTempUTF8 = buf;
        char *pUTF8End = pTempUTF8 + 32;
        while (pTempUTF16 < pTempUTF16 + 28) {
            if (*pTempUTF16 <= 0x007F && pTempUTF8 + 1 < pUTF8End) 
            {
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
    
    void hide_process() {
	    ioctl(fd, OP_HIDE_PROCESS);
	}
	
};

extern CDriver *driver;

