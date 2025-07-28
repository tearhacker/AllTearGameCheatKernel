LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := 独久王者内核.sh
LOCAL_CPPFLAGS := -w -std=c++17

LOCAL_C_INCLUDES +=$(LOCAL_PATH)/include
LOCAL_C_INCLUDES +=$(LOCAL_PATH)/include/Android_draw
LOCAL_C_INCLUDES +=$(LOCAL_PATH)/include/Android_touch
LOCAL_C_INCLUDES +=$(LOCAL_PATH)/include/ImGui
LOCAL_C_INCLUDES +=$(LOCAL_PATH)/include/native_surface
LOCAL_C_INCLUDES +=$(LOCAL_PATH)/include/native_surface/aosp


FILE_LIST += $(wildcard $(LOCAL_PATH)/src/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/src/绘制函数/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/src/触摸库/*.c*)
FILE_LIST += $(wildcard $(LOCAL_PATH)/src/ImGui库/*.c*)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_LDFLAGS += -lEGL -lGLESv2 -lGLESv3 -landroid -llog
include $(BUILD_EXECUTABLE)
