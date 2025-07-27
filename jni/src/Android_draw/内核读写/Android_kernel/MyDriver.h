#ifndef MY_DRIVER_H
#define MY_DRIVER_H

#include "6_10.h"
#include "5_10.h"  
#include "5_15.h"                 
#include "5_10b.h"
#include "4_19_81.h"
#include "4_9_186.h"
#include "4_14_117.h"
#include "4_19_113.h"   
#include "4_14_180.h"   
#include "4_19_157.h"     
#include "4_14_186.h"   
#include "4_19_113c.h"   
#include "5_10-Pixel.h"       
#include "4_19_157b.h"       
#include "4_14_186b.h"
#include "4_14_186c.h"  
#include "5_4_61~256.h"
#include "5_4_86~256.h"             
#include "5_4_147~256.h"
#include "5_4_210-ColorOS-A13.h"  
#include "4_19_191-ColorOS-A13.h"  
#include "5_4_233-ColorOS-A14.h" 
#include "4_19_157-ColorOS-A13.h"  
#include "4_19_191-note12pro-A13.h"  
#include "xiaomi_sm8350-Voyager.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/utsname.h>

#define dev "/dev/"
#define kernelroute "/sys/devices/virtual/"

using namespace std;
//by 小菜鸡

char *new_str;
char *FileContent;

char *驱动名称;
char 驱动路径[40];

char *六字驱动名称;
char *HexadecimalStringFormatDriverName;

bool 菜单999 = false;
bool Pdum444 = false;
bool MemuSwitch666 = true;
int adum999 = 0;   //计时
int ktes9999 = 0;  //按下
int 输入;
  
int GetEventCounts() {
    DIR *dir = opendir("/dev/input/");
    dirent *ptr = nullptr;
    int count = 0;
    while ((ptr = readdir(dir)) != nullptr) {
        if (strstr(ptr->d_name, "event"))
            count++;
    }
    return count;
}
  
//设置时间
void mytime(int d) {
     int b = 0;
       for (int i = 0; i < d + 1; i++) { 
       sleep(1);
       b = b + 1;
       adum999 = b;
     }
     ktes9999 = 0;
}
   
   //判断时间到期
bool Pdum444time(int d) {
     thread* myThread = nullptr;
     if (ktes9999<=1 && ktes9999 != 0){
       myThread = new thread(mytime, d);
     }else if (ktes9999 >= d | adum999 == d && Pdum444) { 
       if (ktes9999 == d){
         delete myThread; 
       }
     exit(0);
     }else if (adum999 >= d){
       delete myThread; 
     }
     return Pdum444;
}
  
  //音量判断
int 音量() {
      int EventCount = GetEventCounts();
      if (EventCount < 0) {
        printf("未找到输入设备\n");
        return -1;
      }    
      int *fdArray = (int *)malloc(EventCount * sizeof(int));
      for (int i = 0; i < EventCount; i++) {
        char temp[128];
        sprintf(temp, "/dev/input/event%d", i);
        fdArray[i] = open(temp, O_RDWR | O_NONBLOCK);
      }
      input_event ev;
      while (1) {     	
        for (int i = 0; i < EventCount; i++) {
            memset(&ev, 0, sizeof(ev));
            read(fdArray[i], &ev, sizeof(ev));
            if (ev.type == EV_KEY && (ev.code == KEY_VOLUMEUP || ev.code == KEY_VOLUMEDOWN)) {
              if (ev.code == 115&&ev.value==1) {
                    //这里放悬浮窗开启的函数
                    MemuSwitch666=true;
                    printf("\n我按了音量[+]键!\n");
                    ktes9999 = ktes9999 + 1;
                    Pdum444time(5);   //记录按下音量键的次数不超过5
                    Pdum444 = true;
              } else if (ev.code == 114&&ev.value==1) {
                    printf("\n我按了音量[-]键!\n");
                    MemuSwitch666=false;
              } 
            }
        }
      }
      return 0;
}
  

class 叽叽叽 {
  private:
   
  char *kernel()
  {
    struct utsname unameData;      
    if (uname(&unameData) == 0){
        return unameData.release; //sysname：操作系统名称  nodename：计算机网络名称  release：操作系统发行版本  version：操作系统内核版本  machine：硬件架构  domainname：域名
    }else{
        printf("[-]无法获取内核版本。");
        return NULL;
    }
  }

  void write(const char *文件路径, unsigned long 偏移, const char *内容) {      
    FILE *文件 = fopen(文件路径, "rb+");
    if (文件 == NULL) {
        printf("无法打开文件: %s\n", 文件路径);
        return;
    }
    fseek(文件, 偏移, SEEK_SET);
    size_t 大小 = strlen(内容);
    unsigned char *缓冲 = (unsigned char *)malloc(大小 / 2);
    for (size_t i = 0; i < 大小; i += 2) {
        sscanf(内容 + i, "%2hhx", &缓冲[i / 2]);
    }
    fwrite(缓冲, 1, 大小 / 2, 文件);
    free(缓冲);
    fclose(文件);
  }
  
  char *转换16进制(const char *十六进制内容) {
    // 检查输入字符串是否为空
    if (十六进制内容 == NULL) {
        return NULL;
    }

    // 计算转换后的字符串长度
    size_t 长度 = strlen(十六进制内容) / 2; // 每两个十六进制字符对应一个字节
    if (长度 == 0) {
        return "";
    }

    // 分配内存以存储转换后的UTF-8字符串
    char *utf8字符串 = (char *)malloc((长度 + 1) * sizeof(char)); // +1 为了存储字符串结束符 '\0'
    if (utf8字符串 == NULL) {
        return NULL; // 内存分配失败
    }

    // 转换十六进制到UTF-8
    for (size_t i = 0, j = 0; i < strlen(十六进制内容); i += 2, j++) {
        // 读取十六进制的两个字符
        uint8_t 高位 = 0x10 * (uint8_t)(十六进制内容[i] - '0');
        if (十六进制内容[i] >= 'A' && 十六进制内容[i] <= 'F') {
            高位 = 0x10 * (10 + (十六进制内容[i] - 'A'));
        } else if (十六进制内容[i] >= 'a' && 十六进制内容[i] <= 'f') {
            高位 = 0x10 * (10 + (十六进制内容[i] - 'a'));
        }

        uint8_t 低位 = (uint8_t)(十六进制内容[i + 1] - '0');
        if (十六进制内容[i + 1] >= 'A' && 十六进制内容[i + 1] <= 'F') {
            低位 = 10 + (十六进制内容[i + 1] - 'A');
        } else if (十六进制内容[i + 1] >= 'a' && 十六进制内容[i + 1] <= 'f') {
            低位 = 10 + (十六进制内容[i + 1] - 'a');
        }

        // 将十六进制转换为UTF-8字节
        utf8字符串[j] = 高位 + 低位;
    }

    // 字符串结束符
    utf8字符串[长度] = '\0';

    return utf8字符串;
  }
  
  // 将单个字节转换为其十六进制表示的字符串
  void byteToHex(uint8_t byte, char *hexStr) {
    static const char hexDigits[] = "0123456789ABCDEF";
    hexStr[0] = hexDigits[byte / 16]; // 取高四位
    hexStr[1] = hexDigits[byte % 16]; // 取低四位
    hexStr[2] = '\0'; // 字符串结束符
  }

  // 将UTF-8字符串转换为十六进制字符串
  char *Utf8ToHex(const char *utf8Str) {
    if (utf8Str == NULL) {
        return NULL;
    }

    size_t length = strlen(utf8Str);
    size_t hexLength = length * 2 + 1; // 每个字节变两个字符，加1为字符串结束符
    char *hexStr = (char *)malloc(hexLength * sizeof(char));
    if (hexStr == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        byteToHex((uint8_t)utf8Str[i], hexStr + i * 2);
    }

    return hexStr;
  }
  
  //创建文件
  void create(const char *文件名){
    char str[128];
    strcpy(str, 文件名);
    int len = strlen(str);
    int last_slash_index = -1;
    for (int i = 0; i < len; i++) {
        if (str[i] == '/') {
            last_slash_index = i;
        }
    }
    str[last_slash_index] = '\0'; // 替换最后一个 / 为字符串结束符
    mkdir(str, 0777);
    FILE *file = fopen(文件名, "w");
    fclose(file);
  }
  
  //随机字符串
  char* generate_random_string(int length) {
    char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_length = sizeof(charset) - 1;
    srand(time(NULL));
    char* random_string = (char*)malloc((length + 1) * sizeof(char));
    if (random_string == NULL) {
        printf("内存分配失败\n");
    }
    for (int i = 0; i < length; i++) {
        random_string[i] = charset[rand() % charset_length];
    }
    random_string[length] = '\0';
    return random_string;
  }
  
  //随机字符串2
  char* generate_random_string2(int length) {
    char charset[] = "1234567890";
    int charset_length = sizeof(charset) - 1;
    srand(time(NULL));
    char* random_string = (char*)malloc((length + 1) * sizeof(char));
    if (random_string == NULL) {
        printf("内存分配失败\n");
    }
    for (int i = 0; i < length; i++) {
        random_string[i] = charset[rand() % charset_length];
    }
    random_string[length] = '\0';
    return random_string;
  }
  
  
  //执行命令
  char* execCom(const char* shell)
  {
    FILE *fp = popen(shell, "r");
    if (fp == NULL){
        perror("popen failed");
        return NULL;
    }
    char buffer[256];
    char *result = (char *)malloc(1000); 
    result[0] = '\0';     
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        strcat(result, buffer);
    }
    pclose(fp);
    return result;
  }
  
  
  //查找字符串中的数字
  int find_first_comma_number(const char *str) {
    int num = 0;
    int found = 0;
    while (*str) {
        if (isdigit(*str)) {
            num = num * 10 + (*str - '0'); 
            found = 1;
        } else if (*str == ',' && found) {
            break; 
        } else if (!isdigit(*str)) {
            num = 0;
        }
        str++;
    }
    if (found) {
        return num;
    } else {
        return -1; // 如果没有找到数字，返回 -1
    }
  }
  
  //创建驱动节点😤
  void createDriverNode(char *path, int major_number, int minor_number) {
    const int max_command_size = 128;
    char command[max_command_size];
    int len = snprintf(command, max_command_size, "mknod %s c %d %d", path, major_number, minor_number);
    if (len >= max_command_size) {
        printf("[-] Error: Command buffer too small.\n");
        return;
    }
    int result = system(command);
    if (result == 0) {
        printf("\n\n[+] 创建 %s，主设备号：%d，次设备号：%d\n", path, major_number, minor_number);
    } else {
        printf("\n\n[-] 创建 %s 失败，主设备号：%d，次设备号：%d\n", path, major_number, minor_number);
    }
  }  
  
  
  // 搜索并替换
  char* search_and_replace(const char *str, const char *search, const char *replace) {
      if (!str || !search || !replace)
      {
          fprintf(stderr, "Invalid input parameters\n");
        return NULL;
      }

      size_t search_len = strlen(search);
      size_t replace_len = strlen(replace);
      size_t new_len = strlen(str); // 原始字符串长度

      // 计算需要替换的次数
      const char *pos = str;
      size_t count = 0;
      
      while ((pos = strstr(pos, search)) != NULL) 
      {
          count++;
          pos += search_len;
      }

      // 计算新字符串的长度
      new_len += (replace_len - search_len) * count;

      // 分配新字符串的内存空间
      char *result = (char*)malloc((new_len + 1) * sizeof(char));
      if (!result) {
          fprintf(stderr, "Memory allocation failed\n");
          return NULL;
      }
      

      // 构建新字符串
      char *dst = result;
      const char *src = str;
      while (*src) {
          const char *found = strstr(src, search);
          if (found) {
              // 复制搜索词之前的字符串部分
              memcpy(dst, src, found - src);
              dst += (found - src);

              // 复制替换字符串
              memcpy(dst, replace, replace_len);
              dst += replace_len;

              // 跳过已替换的搜索词
              src = found + search_len;
          } else {
              // 复制剩余的字符串
              memcpy(dst, src, strlen(src));
              dst += strlen(src);
              break;
          }
      }
      *dst = '\0'; // 确保新字符串以 null 字符结尾
      return result;
  }
  
  
  // 写字符串到文件
  void writeStringToFile(const char *str, const char *filename) {
      FILE *file = fopen(filename, "w");
      
      if (file == NULL)
      {
          perror("[1]在打开文件的时候出错了!\n");
          exit(EXIT_FAILURE);
      }
      
      fprintf(file, "%s", str);
      fclose(file);
  }

  
  // 替换缓冲区
  int replaceInBuffer(char *buffer, int bufferSize, const char *oldString, const char *newString) {
      char *found = buffer;
      int replacements = 0;
      int oldLength = strlen(oldString);
      int newLength = strlen(newString);

      while ((found = strstr(found, oldString)) != NULL) 
      {
          // 确保替换后的字符串不会超出缓冲区边界
          if ((found + oldLength) + newLength > (buffer + bufferSize))
          {
              break;
          }

          // 移动后面的字符
          memmove(found + newLength, found + oldLength, bufferSize - (found - buffer) - oldLength + 1);
          // 复制新字符串到找到的位置
          memcpy(found, newString, newLength);
          found += newLength; // 移动到新字符串的末尾，以便继续搜索
          replacements++;
      }

      return replacements;
  }
  

  // 替换并打印内容。
  void replaceAndPrintContent(const char *filename, const char *oldString, const char *newString) {
        FILE *file = fopen(filename, "r+");
        
        if (file == NULL) 
        {
            perror("[2]在打开文件的时候出错了!\n");
            exit(EXIT_FAILURE);
        }

        // 读取文件内容到内存
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);
        char *buffer = (char *)malloc(fileSize + 1);
        
        if (buffer == NULL) 
        {
            perror("出错问题：分配内存!\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        size_t bytesRead = fread(buffer, 1, fileSize, file);
        
        if (bytesRead != fileSize) {
            perror("在读取文件的时候出错了!");
            free(buffer);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        
        buffer[bytesRead] = '\0'; // 确保字符串以 null 结尾

        int replacements = replaceInBuffer(buffer, fileSize, oldString, newString);

        // 将修改后的内容写回文件
        fseek(file, 0, SEEK_SET);
        fwrite(buffer, 1, fileSize, file);
        fclose(file);

        free(buffer);

        printf("当前替换总次数: %d\n", replacements);
  }
  

  // 读取文件内容
  char* read_file_content(const char* file_path) {
        FILE *file = fopen(file_path, "r"); // 打开文件，以只读方式
        
        if (file == NULL)
        {
            perror("[3]在打开文件的时候出错了！\n");
        return NULL;
        }

        fseek(file, 0, SEEK_END); // 移动文件指针到文件末尾
        long file_size = ftell(file); // 获取文件大小
        fseek(file, 0, SEEK_SET); // 将文件指针重新定位到文件开头

        // 为文件内容分配内存
        char *file_content = (char*) malloc((file_size + 1) * sizeof(char));
        
        if (file_content == NULL) 
        {
            fclose(file);
            perror("分配内存失败！\n");
            return NULL;
        }

        // 读取文件内容
        size_t num_read = fread(file_content, sizeof(char), file_size, file);
        
        if (num_read != file_size) 
        {
            free(file_content);
            fclose(file);
            perror("在读取文件的时候出错了!\n");
            return NULL;
        }

        // 添加字符串结束符
        file_content[file_size] = '\0';

        fclose(file); // 关闭文件
        return file_content;
  }
  
  
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
        
        closedir(dir); // 遍历完关闭目录
        return NULL; // 没有找到
  }
  
  
  //判断目标
  bool JudgeTarget(const char *str) { 
        if (str == NULL) 
        {
            return false;
        }

        int len = strlen(str);

        if (len == 30) 
        {
            if (str[30] == '\0') 
            {
                return true;
            }
        }

    return false;
  }
  
  
  // 下一步
  void Next(){
      printf("\033[30;1m");
    
      char 原版驱动路径[20];
      sprintf(原版驱动路径, "/dev/%s", 六字驱动名称);
    
      execCom("insmod /data/内核/Green.ko");  //安装内核模块
    
      char result[20];
      sprintf(result, "ls -l /dev/%s", 六字驱动名称);
    
      char *output = execCom(result);
    
      printf("\n内核驱动信息：%s\n", output);
    
      unlink(原版驱动路径);
    
      int 主设备号 = find_first_comma_number(output);
    
      printf("\n主设备号：%d\n", 主设备号);
    
     if (主设备号 == -1){
         printf("\033[35;1m\n");
         printf("[-]刷入失败！\n");
         sleep(1.6);
         printf("[-]刷入失败！\n");
         sleep(1.6);
         printf("[-]刷入失败！\n");
         sleep(1.6);
         printf("[-]刷入失败！\n");
         sleep(1.6);
         printf("[-]部署失败！\n");
         exit(1);
     }
     
     驱动名称 = generate_random_string(30);
     sprintf(驱动路径, "/dev/%s", 驱动名称);
     
     createDriverNode(驱动路径, 主设备号, 0); 
     sleep(1.5);     //让程序睡1.5秒😘
  }


  public:
  叽叽叽() {
        
    六字驱动名称 = generate_random_string2(6);
    HexadecimalStringFormatDriverName = Utf8ToHex(六字驱动名称);    
    
    if (JudgeTarget(find(dev))){
      goto 终点;
      菜单999 = false;
    }else{
        printf("\n内置驱动自动刷入 请勿碰到手机 一加系列不支持\n\n");
        sleep(1);
        new thread(音量);
        sleep(3);
      
      菜单999 = true;
    }
    
    开始:
    if (菜单999){   
    printf("\033[31;1m\n");
    printf("\n正在启动Green内核驱动安装……\n");
    
    puts("\033[33;31m******************************************************************\033[0m");
	char *kernel_version = kernel();
    printf("\033[30;1m");
    printf("当前内核版本：%s\n", kernel_version);
    puts("\033[33;31m******************************************************************\033[0m");   
    
    printf("\033[39;1m\n");
    sleep(0.6);
    create("/data/内核/Green.ko");
    
    printf("\033[30;1m\n");
    printf("\n[1] 4.14.117.h      \n[2] 4.19.113.h          \n[3] 4.19.191-ColorOS-A13.h         \n[4] 5.10.h\n               \n[5] 5.4.233-ColorOS-A14.h\n");
    printf("\n[6] 4.14.180.h     \n[7] 4.19.113c.h         \n[8] 4.19.191-note12pro-A13.h        \n[9] 5.10b.h              \n[10] 5.4.61~256.h\n");
    printf("\n[11] 4.14.186.h    \n[12] 4.19.81.h          \n[13] 4.19.157-ColorOS-A13.h        \n[14] 5.15.h               \n[15] 5.4.86~256.h\n");
    printf("\n[16] 4.14.186b.h   \n[17] 4.19.157.h         \n[18] 5.4.210-ColorOS-A13.h         \n[29] 4.9.186.h          \n[20] 6.10.h\n");
    printf("\n[21] 4.14.186c.h   \n[22] 4.19.157b.h        \n[23] 5.10-Pixel.h                  \n[24] 5.4.147~256.h       \n[25]xiaomi.sm8350-Voyager.h\n");
    }
    
    if(MemuSwitch666){
       if (strncmp(kernel(), "4.14.117", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 1;
         goto 输入;
       }else if (strncmp(kernel(), "4.14.180", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 6;
         goto 输入;
       }else if (strncmp(kernel(), "4.14.186", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 11;
         goto 输入;
       }else if (strncmp(kernel(), "4.14.113", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 2;
         goto 输入;
       }else if (strncmp(kernel(), "4.19.81", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 12;
         goto 输入;
       }else if (strncmp(kernel(), "4.19.157", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 17;
         goto 输入;
       }else if (strncmp(kernel(), "4.19.191", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 8;
         goto 输入;
       }else if (strncmp(kernel(), "5.4.210", 7) == 0){  //填写自己的内核版本判断安装
         输入 = 18;
         goto 输入;
       }else if (strncmp(kernel(), "5.10", 4) == 0){  //填写自己的内核版本判断安装
         输入 = 4;
         goto 输入;
       }else if (strncmp(kernel(), "5.15", 4) == 0){  //填写自己的内核版本判断安装
         输入 = 14;
         goto 输入;
       }else if (strncmp(kernel(), "4.9.186", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 29;
         goto 输入;
       }else if (strncmp(kernel(), "6.10", 4) == 0){  //填写自己的内核版本判断安装
         输入 = 20;
         goto 输入;
       }/*else if (strncmp(kernel(), "5.10.136", 8) == 0){  //填写自己的内核版本判断安装
         输入 = 0;
         goto 输入;
       }*/
    }else if (!MemuSwitch666){
    printf("\n\n请输入您对应的内核版本序号:");
    scanf("%d", &输入);
    goto 输入;
    }
    输入:
    switch (输入) {
    case 1:
        
        new_str = search_and_replace(xcj414117, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 2:
        
        new_str = search_and_replace(xcj419113, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 3:
        
        new_str = search_and_replace(xcj419191ColorOSA13, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 4:
        
        new_str = search_and_replace(xcj510, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 5:
        
        new_str = search_and_replace(xcj54233ColorOSA14, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 6:
        
        new_str = search_and_replace(xcj414180, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 7:
        
        new_str = search_and_replace(xcj419113c, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 8:
        
        new_str = search_and_replace(xcj419191note12proA13, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 9:
        
        new_str = search_and_replace(xcj510b, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 10:
        
        new_str = search_and_replace(xcj5461256, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 11:
        
        new_str = search_and_replace(xcj414186, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 12:
        
        new_str = search_and_replace(xcj41981, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 13:
        
        new_str = search_and_replace(xcj419157ColorOSA13, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 14:
        
        new_str = search_and_replace(xcj515, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 15:
        
        new_str = search_and_replace(xcj5486256, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 16:
        
        new_str = search_and_replace(xcj414186b, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 17:    
        new_str = search_and_replace(xcj419157, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 18:
        new_str = search_and_replace(xcj54210ColorOSA13, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 19:
        new_str = search_and_replace(xcj49186, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 20:

        new_str = search_and_replace(xcj610, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 21:

        new_str = search_and_replace(xcj414186c, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 22:
        
        new_str = search_and_replace(xcj419157b, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 23:
        
        new_str = search_and_replace(xcj510Pixel, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 24:
        
        new_str = search_and_replace(xcj54147256, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    case 25:
        
        new_str = search_and_replace(xcjxiaomism8350Voyager, "小菜鸡", HexadecimalStringFormatDriverName);
        write("/data/内核/Green.ko", 0, new_str);
        printf("\n来自底层随机的内核驱动名称：%s\n",六字驱动名称);
        Next();
        break;
        
    default:
    
        printf("输入有误，请重新输入！");
        goto 输入;
        break;
    }

    
    printf("\033[35;1m\n");
    printf("[-]刷入成功！\n");
    sleep(0.6);
    printf("[-]刷入成功！\n");
    sleep(0.6);
    printf("[-]刷入成功！\n");
    sleep(0.6);
    printf("[-]刷入成功！\n");
    sleep(0.6);
    printf("[-]完成部署！\n");
   // sleep(1.6);
    终点:
    printf("\033[31;1m");
  //  printf("\n[-]正在开启「悬浮窗」中……\n");
    sleep(0.6);
    printf("\033[39;1m\n");
    execCom("rm -rf /data/内核");  //删掉存于设备上的Green内核文件
  }
  
};

extern 叽叽叽 *小菜鸡;


#endif