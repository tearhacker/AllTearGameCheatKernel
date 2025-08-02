#ifndef NATIVESURFACE_MEMREAD_H
#define NATIVESURFACE_MEMREAD_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/syscall.h>
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

// 支持的搜索类型
enum
{
	DWORD,
	FLOAT,
	BYTE,
	WORD,
	QWORD,
	XOR,
	DOUBLE,
};

long int 基址头;

int pid;
// syscall内存读写
#if defined(__arm__)
int process_vm_readv_syscall = 376;
int process_vm_writev_syscall = 377;
#elif defined(__aarch64__)
int process_vm_readv_syscall = 270;
int process_vm_writev_syscall = 271;
#elif defined(__i386__)
int process_vm_readv_syscall = 347;
int process_vm_writev_syscall = 348;
#else
int process_vm_readv_syscall = 310;
int process_vm_writev_syscall = 311;
#endif

ssize_t process_v(pid_t __pid, const struct iovec *__local_iov, unsigned long __local_iov_count,
				  const struct iovec *__remote_iov, unsigned long __remote_iov_count,
				  unsigned long __flags, bool iswrite)
{
	return syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), __pid,
				   __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

int getProcessID(const char *packageName)
{
	int id = -1;
	DIR *dir;
	FILE *fp;
	char filename[64];
	char cmdline[64];
	struct dirent *entry;
	dir = opendir("/proc");
	while ((entry = readdir(dir)) != NULL)
	{
		id = atoi(entry->d_name);
		if (id != 0)
		{
			sprintf(filename, "/proc/%d/cmdline", id);
			fp = fopen(filename, "r");
			if (fp)
			{
				fgets(cmdline, sizeof(cmdline), fp);
				fclose(fp);
				if (strcmp(packageName, cmdline) == 0)
				{
					return id;
				}
			}
		}
	}
	closedir(dir);
	return -1;
}

bool mem_addr_virtophy(unsigned long vaddr)
{
	int fh = 1;
	int pageSize = getpagesize();

	// 虚拟地址相对于0X0经过的页面数
	unsigned long v_pageIndex = vaddr / pageSize;
	// 在pagemap文件中的偏移量
	unsigned long pfn_item_offset = v_pageIndex * sizeof(uint64_t);

	// 页内偏移量
	unsigned long page_offset = vaddr % pageSize;
	uint64_t item = 0;
	char filename[32];
	snprintf(filename, sizeof(filename), "/proc/%d/pagemap", getProcessID);
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		// printf("open failed\n");
		return false;
	}

	if (lseek(fd, pfn_item_offset, SEEK_SET) < 0)
	{
		printf("lseek failed\n");
		return false;
	}

	if (read(fd, &item, sizeof(uint64_t)) != sizeof(uint64_t))
	{
		printf("read failed\n");
		return false;
	}

	if (0 == (item & (((uint64_t) 1) << 63)))
	{
		fh = 0;
		printf("page is not present");
        return false;
	}
	close(fd);
	return true;
}



// 进程读写内存
bool pvm(void *address, void *buffer, size_t size, bool iswrite)
{
	struct iovec local[1];
	struct iovec remote[1];
	local[0].iov_base = buffer;
	local[0].iov_len = size;
	remote[0].iov_base = address;
	remote[0].iov_len = size;
	if (pid < 0)
	{
		return false;
	}
	ssize_t bytes = process_v(pid, local, 1, remote, 1, 0, iswrite);
	return bytes == size;
}

// 读取内存
bool vm_readv(unsigned long address, void *buffer, size_t size)
{
	return pvm(reinterpret_cast < void *>(address), buffer, size, false);
}

// 写入内存
bool vm_writev(unsigned long address, void *buffer, size_t size)
{
	return pvm(reinterpret_cast < void *>(address), buffer, size, true);
}

// 获取F类内存
float 读取浮点数(unsigned long addr)
{
	float var = 0;
	vm_readv(addr, &var, 4);
	return (var);
}


// 获取D类内存
int 读取整数(unsigned long addr)
{
	int var = 0;
	vm_readv(addr, &var, 4);
	return (var);
}

// 获取指针(32位游戏)
unsigned int 读取指针32(unsigned int addr)
{
	if (mem_addr_virtophy(addr) || addr == 0x0000000000 || addr == 0 || addr == 0x000){
        return 0;
    }
	unsigned int var = 0;
	vm_readv(addr, &var, 4);
	return (var);
}

// 获取指针(64位游戏)
unsigned long 读取指针(unsigned long addr){
	if (mem_addr_virtophy(addr) || addr == 0x0000000000 || addr == 0 || addr == 0x000){
        return 0;
    }
	unsigned long var = 0;
	vm_readv(addr & 0xFFFFFFFFFF, &var, 8);
	return (var & 0xFFFFFFFFFF);
}


void getname(uintptr_t gname,int oid,char name[]){
    int page = oid / 0x4000;
    int index = oid % 0x4000;
    uintptr_t pa=读取指针(gname+page*8);
    uintptr_t in=读取指针(pa+index*8);
    vm_readv(in+0xE,name,32);
}

/*
  unsigned int 读取指针(unsigned int addr) {
   unsigned int var = 0; vm_readv(addr, &var, 8); return (var); }
   
   
void writedword(unsigned int addr, int data) {
   vm_writev(addr, &data, 4); 
   } 

// 写入F类内存
void 写入F内存(unsigned long addr, float data)
{
	vm_writev(addr, &data, 4);
}
*/

// 根据类型判断类型所占字节大小
size_t judgSize(int type)
{
	switch (type)
	{
	case DWORD:
	case FLOAT:
	case XOR:
		return 4;
	case BYTE:
		return sizeof(char);
	case WORD:
		return sizeof(short);
	case QWORD:
		return sizeof(long);
	case DOUBLE:
		return sizeof(double);
	}
	return 4;
}
size_t  preadv(long address, void *buffer, size_t size)
{
	struct iovec iov_ReadBuffer, iov_ReadOffset;
	iov_ReadBuffer.iov_base = buffer;
	iov_ReadBuffer.iov_len = size;
	iov_ReadOffset.iov_base = (void *)address;
	iov_ReadOffset.iov_len = size;
	return syscall(SYS_process_vm_readv, pid, &iov_ReadBuffer, 1, &iov_ReadOffset, 1, 0);
}
size_t  pwritev(long address, void *buffer, size_t size)
{
	struct iovec iov_WriteBuffer, iov_WriteOffset;
	iov_WriteBuffer.iov_base = buffer;
	iov_WriteBuffer.iov_len = size;
	iov_WriteOffset.iov_base = (void *)address;
	iov_WriteOffset.iov_len = size;
	return syscall(SYS_process_vm_writev, pid, &iov_WriteBuffer, 1, &iov_WriteOffset, 1, 0);
}
template < class T > int edit(T value,long address,int type,bool debug)
{
	if(-1 == pwritev(address,&value,judgSize(type)))
	{
		if(debug)
		printf("修改失败-> addr:%p\n",address);
		return -1;
	}else
	{
		if(debug)
		printf("修改成功-> addr:%p\n",address);
		return 1;
	}
	return -1;
}


// 获取进程
int getPID(const char *packageName)
{
	int id = -1;
	DIR *dir;
	FILE *fp;
	char filename[64];
	char cmdline[64];
	struct dirent *entry;
	dir = opendir("/proc");
	while ((entry = readdir(dir)) != NULL)
	{
		id = atoi(entry->d_name);
		if (id != 0)
		{
			sprintf(filename, "/proc/%d/cmdline", id);
			fp = fopen(filename, "r");
			if (fp)
			{
				fgets(cmdline, sizeof(cmdline), fp);
				fclose(fp);
				if (strcmp(packageName, cmdline) == 0)
				{
					return id;
				}
			}
		}
	}
	closedir(dir);
	return -1;
}

// 获取基址
unsigned long get_module_base(int pid, const char *module_name)
{
	FILE *fp;
	unsigned long addr = 0;
	char *pch;
	char filename[64];
	char line[1024];
	snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name))
			{
				pch = strtok(line, "-");
				addr = strtoul(pch, NULL, 16);
				if (addr == 0x8000)
					addr = 0;
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}

uintptr_t GetModuleBase(char *name, int index)
    {
        int f = 0, ii = 0, iii = 0;
        long start = 0, end = 0;
        char line[1024] = {0};
        char fname[128];
        char dname[128];
        if (strstr(name, "bss") != NULL) {
            sscanf(name, "%[^:]", dname);
            f++;
        } else {
            sprintf(dname, "%s", name);
        }
        sprintf(fname, "/proc/%d/maps", pid);
        FILE *p = fopen(fname, "r");
        if (p)
        {
            while (fgets(line, sizeof(line), p))
            {
                if (strstr(line, dname) != NULL)
                {
                    iii++;
                    if (f == 0)
                    {
                        if (iii == index)
                        {
                            if (sizeof(long) == 8) {
                                sscanf(line, "%lx-%lx", &start, &end);
                            } else {
                                sscanf(line, "%x-%x", &start, &end);
                            }
                            break;
                        }
                    } else {
                        ii++;
                    }
                }
                if (ii > 0) {
                    if (strstr(line, "[anon:.bss]") != NULL) {
                        if (sizeof(long) == 8) {
                            sscanf(line, "%lx-%lx", &start, &end);
                        } else {
                            sscanf(line, "%x-%x", &start, &end);
                        }
                        break;
                    }
                }
            }
            fclose(p);
        }
        return start;
    }

long getbss(const char *name)
{
	FILE *fp;
	int cnt = 0;
	long start;
	char tmp[256];
	fp = NULL;
	char line[1024];
	char fname[128];
	sprintf(fname, "/proc/%d/maps", pid);
	fp = fopen(fname, "r");
	while (!feof(fp))
	{
		fgets(tmp, 256, fp);
		if (cnt == 1)
		{
			if (strstr(tmp, "[anon:.bss]") != NULL)
			{
				sscanf(tmp, "%lx-%*lx", &start);
				break;
			}
			else
			{
				cnt = 0;
			}
		}
		if (strstr(tmp, name) != NULL)
		{
			cnt = 1;
		}
	}
	return start;
}

// 获取进程是否运行




#endif
