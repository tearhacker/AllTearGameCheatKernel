
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>





int createAndWriteFile(const char *filepath, const char *content) {
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
    	printf("\033[31;1m");//红色
        printf("[!] 写入文件失败\n");
        return 1;
    }
    fprintf(file, "%s", content);
    fclose(file);

    return 0;
}

int fbl2400() {


	system("rm -f /data/内部配置/{头像大小,血量大小,地图比例,头像X,头像Y,实体X,实体Y,技能栏X,技能栏Y,视野X,视野Y} >/dev/null 2>&1");
    int result;

    // 检查目录是否存在，如果不存在则创建
    result = access("/data/内部配置", F_OK);
    if (result == -1) {
        // 目录不存在，则创建它
        result = mkdir("/data/内部配置", 0777); // 0777表示创建的目录权限为 rwxrwxrwx
        if (result == -1) {
        	printf("\033[31;1m");//红色
            printf("[!] 创建目录失败\n");
            return 1;
        }
    }

    // 创建并写入文件
    result = createAndWriteFile("/data/内部配置/头像Y", "11");
    if (result != 0)
        return result;

    result = createAndWriteFile("/data/内部配置/头像X", "46");
    if (result != 0)
        return result;

    result = createAndWriteFile("/data/内部配置/地图比例", "-1");
    if (result != 0)
        return result;
        
    result = createAndWriteFile("/data/内部配置/血量大小", "1");
    if (result != 0)
        return result;
        
    result = createAndWriteFile("/data/内部配置/头像大小", "1");
    if (result != 0)
        return result;
        
    result = createAndWriteFile("/data/内部配置/技能栏X", "15");
    if (result != 0)
        return result;
        
    result = createAndWriteFile("/data/内部配置/技能栏Y", "-4");
    if (result != 0)
        return result;
        
        
    printf("\033[36;1m");//蓝色
    printf("[-] 配置写入成功\n");
    return 0;
}


int fbl3200() {


	system("rm -f /data/内部配置/{头像大小,血量大小,地图比例,头像X,头像Y,实体X,实体Y,技能栏X,技能栏Y,视野X,视野Y} >/dev/null 2>&1");
    int result;

    // 检查目录是否存在，如果不存在则创建
    result = access("/data/内部配置", F_OK);
    if (result == -1) {
        // 目录不存在，则创建它
        result = mkdir("/data/内部配置", 0777); // 0777表示创建的目录权限为 rwxrwxrwx
        if (result == -1) {
            printf("\033[31;1m");//红色
            printf("[!] 创建目录失败\n");
            return 1;
        }
    }

    // 创建并写入文件
    result = createAndWriteFile("/data/内部配置/头像Y", "14");
    if (result != 0)
        return result;

    result = createAndWriteFile("/data/内部配置/头像X", "96");
    if (result != 0)
        return result;

   /* result = createAndWriteFile("/data/内部配置/地图比例", "-1");
    if (result != 0)
        return result;*/
        
    result = createAndWriteFile("/data/内部配置/血量大小", "7");
    if (result != 0)
        return result;
        
   /* result = createAndWriteFile("/data/内部配置/头像大小", "0");
    if (result != 0)
        return result;*/
   /*     
    result = createAndWriteFile("/data/内部配置/技能栏X", "15");
    if (result != 0)
        return result;
        
    result = createAndWriteFile("/data/内部配置/技能栏Y", "-4");
    if (result != 0)
        return result;
*/
    printf("\033[36;1m");//蓝色
    printf("[-] 配置写入成功\n");
    return 0;
}


int fbl1500() {


	system("rm -f /data/内部配置/{头像大小,血量大小,地图比例,头像X,头像Y,实体X,实体Y,技能栏X,技能栏Y,视野X,视野Y} >/dev/null 2>&1");
    int result;

    // 检查目录是否存在，如果不存在则创建
    result = access("/data/内部配置", F_OK);
    if (result == -1) {
        // 目录不存在，则创建它
        result = mkdir("/data/内部配置", 0777); // 0777表示创建的目录权限为 rwxrwxrwx
        if (result == -1) {
        	printf("\033[31;1m");//红色
            printf("[!] 创建目录失败\n");
            return 1;
        }
    }

    // 创建并写入文件
    result = createAndWriteFile("/data/内部配置/头像Y", "17");
    if (result != 0)
        return result;

    result = createAndWriteFile("/data/内部配置/头像X", "57");
    if (result != 0)
        return result;

    result = createAndWriteFile("/data/内部配置/地图比例", "-1");
    if (result != 0)
        return result;
        
    result = createAndWriteFile("/data/内部配置/血量大小", "1");
    if (result != 0)
        return result;
        
    result = createAndWriteFile("/data/内部配置/头像大小", "1");
    if (result != 0)
        return result;
   /*     
    result = createAndWriteFile("/data/内部配置/技能栏X", "15");
    if (result != 0)
        return result;
        
    result = createAndWriteFile("/data/内部配置/技能栏Y", "-4");
    if (result != 0)
        return result;
*/
	printf("\033[36;1m");//蓝色
    printf("[-] 配置写入成功\n");
    return 0;
}