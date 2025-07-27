LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# 模块定义（去掉.sh后缀，使用纯英文名称）
LOCAL_MODULE := TearGameSgameinit.sh

# 编译选项
LOCAL_CPPFLAGS := -w -std=c++17

# 包含路径
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/include/Android_draw \
    $(LOCAL_PATH)/include/Android_read \
    $(LOCAL_PATH)/include/Android_shm \
    $(LOCAL_PATH)/include/Android_touch \
    $(LOCAL_PATH)/include/ImGui \
    $(LOCAL_PATH)/include/native_surface \
    $(LOCAL_PATH)/include/native_surface/aosp

# 源文件收集（更可靠的方式）
MY_SRC_PATH := $(LOCAL_PATH)/src
LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/*.cpp)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/*.c)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/Android_draw/*.cpp)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/Android_draw/*.c)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/Android_read/*.cpp)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/Android_read/*.c)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/Android_shm/*.cpp)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/Android_shm/*.c)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/Android_touch/*.cpp)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/Android_touch/*.c)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/ImGui/*.cpp)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/ImGui/*.c)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/native_surface/*.cpp)) \
    $(subst $(LOCAL_PATH)/,,$(wildcard $(MY_SRC_PATH)/native_surface/*.c))

# 链接库
LOCAL_LDLIBS := -lEGL -lGLESv2 -lGLESv3 -landroid -llog

# 构建为可执行文件
include $(BUILD_EXECUTABLE)