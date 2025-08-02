LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := aaa.sh
LOCAL_CFLAGS := -w -s -Wno-error=format-security -fvisibility=hidden -fpermissive -fexceptions
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all,-llog
LOCAL_CPPFLAGS += -w -s -Wno-error=format-security -fvisibility=hidden -Werror -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fpermissive -Wall -fexceptions
LOCAL_CFLAGS := -std=c++17


# 如果你想高强度且不嫌打包时间慢可以使用下面.
# #SLOW PROTECTION + BIG SIZE :
# LOCAL_CPPFLAGS += -mllvm -sub -mllvm -sub_loop=3 -mllvm -sobf -mllvm -split -mllvm -split_num=3 -mllvm -bcf -mllvm -bcf_loop=1 -mllvm -bcf_prob=10 -mllvm -fla

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/ImGui
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/My_Utils
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/T3_authentication
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/curl
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/drivers
LOCAL_C_INCLUDES += $(LOCAL_PATH)/src

FILE_LIST += $(wildcard $(LOCAL_PATH)/src/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/src/drivers/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/src/ImGui/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/include/T3_authentication/*.c*)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)   
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv1_CM -lGLESv2 -lGLESv3

LOCAL_LDFLAGS := -L$(LOCAL_PATH)/include/lib
LOCAL_LDLIBS += -lcurl

LOCAL_STATIC_LIBRARIES := imgui_static
LOCAL_LDFLAGS += $(LOCAL_PATH)/lib/*.a
include $(BUILD_EXECUTABLE) #可执行文件

include $(CLEAR_VARS)
LOCAL_MODULE := imgui_static
LOCAL_SRC_FILES := src/CPUaffinity/libPikachu.a
include $(PREBUILT_STATIC_LIBRARY)  


# 控制流扁平化
# -mllvm -fla：激活控制流扁平化
# -mllvm -split：激活基本块分割。在一起使用时改善展平。
# -mllvm -split_num=3：如果激活了传递，则在每个基本块上应用3次。默认值：1

# 指令替换
# -mllvm -sub：激活指令替换
# -mllvm -sub_loop=3：如果激活了传递，则在函数上应用3次。默认值：1

# 虚假控制流程
# -mllvm -bcf：激活虚假控制流程
# -mllvm -bcf_loop=3：如果激活了传递，则在函数上应用3次。默认值：1
# -mllvm -bcf_prob=40：如果激活了传递，基本块将以40％的概率进行模糊处理。默认值：30

# 字符串加密
# -mllvm -sobf：编译时候添加选项开启字符串加密
# -mllvm -seed=0xabcdefg：指定随机数生成器种子流程

# 如果你对强度没有要求，只是单纯的简单混淆，可以使用下面这个.
# #FAST PROTECTION + SMALL SIZE:
# LOCAL_CPPFLAGS += -mllvm -sub -mllvm -sobf -mllvm -split -mllvm -bcf  -mllvm -fla 

# 如果你想高强度且不嫌打包时间慢可以使用下面.
# #SLOW PROTECTION + BIG SIZE :
# LOCAL_CPPFLAGS += -mllvm -sub -mllvm -sub_loop=3 -mllvm -sobf -mllvm -split -mllvm -split_num=3 -mllvm -bcf -mllvm -bcf_loop=1 -mllvm -bcf_prob=10 -mllvm -fla
