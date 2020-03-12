BINDER_ROOT_PATH := binder

BINDER_FLAGS := $(CFLAGS)
BINDER_FLAGS += -D__ANDROID__ -Wno-unused-parameter -std=c++11


include $(BINDER_ROOT_PATH)/libutils/Makefile
include $(BINDER_ROOT_PATH)/libbinder/Makefile


CP_BINDER_INCLUDE := cp_binder_include
MODULES += $(CP_BINDER_INCLUDE)

$(CP_BINDER_INCLUDE):
	cp -r $(BINDER_ROOT_PATH)/include $(DESTDIR)/
