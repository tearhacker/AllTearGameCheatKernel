#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include <dirent.h>
#include <cstring>
#include <cstdlib>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/uio.h>
#include <dirent.h>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <sys/mman.h>
#include <ctime>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <sys/prctl.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <linux/ptrace.h>
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
