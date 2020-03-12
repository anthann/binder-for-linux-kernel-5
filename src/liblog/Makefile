
# init for liblog
MODULE_PATH_LLOG := liblog

FLAGS_LLOG := $(CFLAGS)
FLAGS_LLOG += -Wall -Wextra -Werror -fPIC

INCLUDES_LLOG := $(INCLUDES)
INCLUDES_LLOG += -Iliblog/include

SOURCES_LLOG := Log.c
OBJS_LLOG := $(patsubst %.c,$(MODULE_PATH_LLOG)/%.o, $(SOURCES_LLOG))

MODULE_LLOG := $(MODULE_PATH_LLOG)/liblog.so
CLEAN_LLOG := clean_LLOG
CP_LLOG := cp_liblob

MODULES += $(MODULE_LLOG)
MODULES += $(CP_LLOG)
CLEANS += $(CLEAN_LLOG)

# rules for liblog
$(MODULE_LLOG): $(OBJS_LLOG)
	$(CC) -shared -o $@ $^

$(OBJS_LLOG): %.o: %.c
	$(CC) $(FLAGS_LLOG) $(INCLUDES_LLOG) -c -o $@ $<

$(CP_LLOG):
	mkdir -p $(DESTDIR)/lib
	cp -f $(MODULE_LLOG) $(DESTDIR)/lib
	cp -r liblog/include $(DESTDIR)/

$(CLEAN_LLOG):
	rm -f $(MODULE_PATH_LLOG)/*.o
	rm -f $(MODULE_LLOG)

