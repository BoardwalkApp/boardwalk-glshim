LOCAL_PATH := $(call my-dir)/../../../src
$(info $(LOCAL_PATH))
include $(CLEAR_VARS)  
LOCAL_LDLIBS := -lEGL -lGLESv1_CM -ldl
LOCAL_MODULE    := glshim
GL_SRC_FILES := $(wildcard $(LOCAL_PATH)/gl/*.c) $(wildcard $(LOCAL_PATH)/gl/wrap/*.c) $(wildcard $(LOCAL_PATH)/gl/math/*.c)
LOCAL_SRC_FILES := $(GL_SRC_FILES:$(LOCAL_PATH)/%=%)
$(info $(LOCAL_SRC_FILES))
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include $(LOCAL_PATH)/util
include $(BUILD_SHARED_LIBRARY)
