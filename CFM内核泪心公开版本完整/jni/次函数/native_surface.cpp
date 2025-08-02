#include "include/native_surface.h"
void* get_createNativeWindow() {
    void *handle;
        if (get_android_api_level() == 33) { // 安卓13支持
            printf("安卓13\n");
            exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
            handle = dlblob(&native_surface_13_64, sizeof(native_surface_13_64)); // 64位支持
#else
            handle = dlblob(&native_surface_13_32, sizeof(native_surface_13_32)); // 32位支持 <<-- 其实很没必要 未测试
#endif
}else if (get_android_api_level() == /*__ANDROID_API_S__*/ 32) { // 安卓12.1支持
        printf("安卓12.1\n");
            exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
            handle = dlblob(&native_surface_12_1_64, sizeof(native_surface_12_1_64)); // 64位支持
#else
            handle = dlblob(&native_surface_12_1_32, sizeof(native_surface_12_1_32)); // 32位支持 <<-- 其实很没必要 未测试
#endif
}else if (get_android_api_level() == 31){ // 安卓12支持
        printf("安卓12\n");
        exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
        handle = dlblob(&native_surface_12_64, sizeof(native_surface_12_64)); // 64位支持
#elif
        handle = dlblob(&native_surface_12_32, sizeof(native_surface_12_32)); // 32位支持 <<-- 其实很没必要 未测试
#endif
    } else if (get_android_api_level() == 30) { // 安卓11支持
        printf("安卓11\n");
#ifdef __aarch64__
        handle = dlblob(&native_surface_11_64, sizeof(native_surface_11_64)); // 64位支持
#elif
        handle = dlblob(&native_surface_11_32, sizeof(native_surface_11_32)); // 32位支持 <<-- 其实很没必要 未测试
#endif
    } else if (get_android_api_level() == 29){ // 安卓10支持
        printf("安卓10\n");
#ifdef __aarch64__
        handle = dlblob(&native_surface_10_64, sizeof(native_surface_10_64)); // 64位支持
#elif
        handle = dlblob(&native_surface_10_32, sizeof(native_surface_10_32)); // 32位支持 <<-- 其实很没必要 未测试
#endif
    } else if (get_android_api_level() == 28){ // 安卓9支持
        printf("安卓9\n");
#ifdef __aarch64__
        handle = dlblob(&native_surface_9_64, sizeof(native_surface_9_64)); // 64位支持
#else
		handle = dlblob(&native_surface_9_32, sizeof(native_surface_9_32)); // 32位支持 <<-- 其实很没必要 未测试
#endif
    }else{
        printf("设备读取异常，您系统码为%d\n",get_android_api_level());
        exec_native_surface("settings put global block_untrusted_touches 0");
#ifdef __aarch64__
            handle = dlblob(&native_surface_13_64, sizeof(native_surface_13_64)); // 64位支持
#else
            handle = dlblob(&native_surface_13_32, sizeof(native_surface_13_32)); // 32位支持 <<-- 其实很没必要 未测试
#endif
}
    void *sy = dlsym(handle, "_Z18createNativeWindowPKcjj");
    if (sy != nullptr) {
        return sy;
    }else{
		sy = dlsym(handle, "_Z18createNativeWindowPKcjjb");      
		if (sy != nullptr) {
      		return sy;
   		}else{
       		sy = dlsym(handle, "_Z14getDisplayInfov");	
			if (sy != nullptr) {
      	  		return sy;
    		}else{
        		sy = dlsym(handle, "_Z12setSurfaceWHjj");
				if (sy != nullptr) {
        			return sy;
    			}else{
        			sy = dlsym(handle, "_Z10initRecordPKcfjj");
					if (sy != nullptr) {
        				return sy;
   	 				}else{
        				sy = dlsym(handle, "_Z9runRecordPbPFvPhmE");
						if (sy != nullptr) {
        					return sy;
    					}else{
        					sy = dlsym(handle, "_Z10stopRecordv");
							if (sy != nullptr) {
        						return sy;
    						}else{
        						sy = dlsym(handle, "_Z21getRecordNativeWindowv");						
								if (sy != nullptr) {
        							return sy;
								}else{
									printf("createNativeWindow _ null~\n");           
    								exit(0);
								}
							}
						}
					}
				}
			}
		}
	}
}
