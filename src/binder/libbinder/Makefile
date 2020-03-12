
# init for libbinder
MODULE_PATH_LBINDER := $(BINDER_ROOT_PATH)/libbinder

FLAGS_LBINDER := $(BINDER_FLAGS)
FLAGS_LBINDER += -Werror -Wall -Wextra -fPIC

INCLUDES_LBINDER := $(INCLUDES)
INCLUDES_LBINDER += -I./include
INCLUDES_LBINDER += -I $(BINDER_ROOT_PATH)/include
INCLUDES_LBINDER += -I liblog/include

SOURCES_LBINDER := $(wildcard $(MODULE_PATH_LBINDER)/*.cpp)
OBJS_LBINDER := $(patsubst %.cpp,%.o, $(SOURCES_LBINDER))

MODULE_LBINDER := $(MODULE_PATH_LBINDER)/libbinder.so
CP_LBINDER := cp_libbinder
CLEAN_LBINDER := clean_libbinder

LIBS_LBINDER := -L $(DESTDIR)/lib -llog -lutils

MODULES += $(MODULE_LBINDER)
MODULES += $(CP_LBINDER)
CLEANS += $(CLEAN_LBINDER)
INSTALLS += $(INSTALL_LBINDER)

# rules for libbinder
$(MODULE_LBINDER): $(OBJS_LBINDER)
	$(CC) -shared -o $@ $^ $(LIBS_LBINDER)

$(OBJS_LBINDER): %.o: %.cpp
	$(CC) $(FLAGS_LBINDER) $(INCLUDES_LBINDER) -c -o $@ $<

$(CLEAN_LBINDER):
	rm -f $(MODULE_PATH_LBINDER)/*.o
	rm -f $(MODULE_LBINDER)

$(CP_LBINDER):
	cp -f $(MODULE_LBINDER) $(DESTDIR)/lib

