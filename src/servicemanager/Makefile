MODULE_PATH_SM := servicemanager
MODULE_SM := $(MODULE_PATH_SM)/service_manager
CLEAN_SM := clean_sm
CP_SM := cp_sm

MODULES += $(MODULE_SM)
MODULES += $(CP_SM)
CLEANS += $(CLEAN_SM)

SM_SOURCES := \
	binder.c \
	service_manager.c 

SM_OBJS := $(patsubst %.c,$(MODULE_PATH_SM)/%.o, $(SM_SOURCES))

$(MODULE_SM): $(SM_OBJS)
	$(CC) -o $@ $^

$(CLEAN_SM):
	rm -f $(MODULE_PATH_SM)/*.o 

%.o: %.c
	$(CC) -I$(INCLUDE_LIB) $(CFLAGS_LIB) -c -o $@ $<

$(CP_SM):
	mkdir -p $(DESTDIR)/bin
	mv $(MODULE_SM) $(DESTDIR)/bin/
