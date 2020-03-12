
# init for servicemanager
MODULE_PATH_SM := servicemanager

FLAGS_SM := $(CFLAGS)
FLAGS_SM += -Wall -Wextra -Werror

INCLUDES_SM := $(INCLUDES)
INCLUDES_SM += -Iinclude
INCLUDES_SM += -Iliblog/include

SOURCES_SM := binder.c service_manager.c
OBJS_SM := $(patsubst %.c,$(MODULE_PATH_SM)/%.o, $(SOURCES_SM))

LIBS_SM := -L $(DESTDIR)/lib -llog

MODULE_SM := $(MODULE_PATH_SM)/servicemanager
CP_SM := cp_sm
CLEAN_SM := clean_sm

MODULES += $(MODULE_SM)
MODULES += $(CP_SM)
CLEANS += $(CLEAN_SM)

# rules for servicemanager
$(MODULE_SM): $(OBJS_SM)
	$(CC) $(FLAGS_SM) -o $@ $^ $(LIBS_SM)

$(OBJS_SM): %.o: %.c
	$(CC) $(FLAGS_SM) $(INCLUDES_SM) -c -o $@ $<

$(CLEAN_SM):
	rm -f $(MODULE_PATH_SM)/*.o
	rm -f $(MODULE_SM)

$(CP_SM):
	mkdir -p $(DESTDIR)/bin
	cp -f $(MODULE_SM) $(DESTDIR)/bin
