
# init for libutils
MODULE_PATH_LUTILS := $(BINDER_ROOT_PATH)/libutils

FLAGS_LUTILS := $(BINDER_FLAGS)
FLAGS_LUTILS += -Wall -Werror -fPIC
#FLAGS_LUTILS += -Wall -Wextra -Werror -fPIC

INCLUDES_LUTILS := $(INCLUDES)
INCLUDES_LUTILS += -I $(BINDER_ROOT_PATH)/include
INCLUDES_LUTILS += -I liblog/include

SOURCES_LUTILS := $(wildcard $(MODULE_PATH_LUTILS)/*.cpp)
OBJS_LUTILS := $(patsubst %.cpp,%.o, $(SOURCES_LUTILS))

MODULE_LUTILS := $(MODULE_PATH_LUTILS)/libutils.so
CP_LUTILS := cp_libutils

LIBS_LUTILS := -L $(DESTDIR)/lib -llog

MODULES += $(MODULE_LUTILS)
MODULES += $(CP_LUTILS)
CLEANS += $(CLEAN_LUTILS)

# rules for libutils
$(MODULE_LUTILS): $(OBJS_LUTILS)
	$(CC) -shared -o $@ $^ $(LIBS_LUTILS)

$(OBJS_LUTILS): %.o: %.cpp
	$(CC) $(FLAGS_LUTILS) $(INCLUDES_LUTILS) -c -o $@ $<

$(CLEAN_LUTILS):
	rm -f $(MODULE_PATH_LUTILS)/*.o
	rm -f $(MODULE_LUTILS)

$(CP_LUTILS):
	cp -f $(MODULE_LUTILS) $(DESTDIR)/lib

