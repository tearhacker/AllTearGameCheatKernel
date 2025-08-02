LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CPP_EXTENSION := .cpp .cc
LOCAL_CPPFLAGS := -w -std=c++17

LOCAL_C_INCLUDES += $(LOCAL_PATH)/次函数/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/次函数/include/aosp

#LOCAL_CFLAGS += -mllvm -sobf -mllvm -sub -mllvm -bcf 

#LOCAL_LDFLAGS += $(LOCAL_PATH)/lib/*.a

FILE_LIST += $(wildcard $(LOCAL_PATH)/次函数/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/主函数/*.c*)
LOCAL_MODULE :=CFM内核.sh

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lGLESv3 -lGLESv1_CM -lz
include $(BUILD_EXECUTABLE)
