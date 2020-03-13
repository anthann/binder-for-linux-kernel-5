MODULE_PATH_BINDER_CTL = binder-control
SOURCES_BINDER_CTL := binderfs.c
OBJS_BINDER_CTL := $(patsubst %.c,$(MODULE_PATH_BINDER_CTL)/%.o, $(SOURCES_BINDER_CTL))

MODULE_BINDER_CTL := $(MODULE_PATH_BINDER_CTL)/binder_ctl
CP_BINDER_CTL := cp_binder_ctl
CLEAN_BINDER_CTL := clean_binder_ctl

MODULES += $(MODULE_BINDER_CTL)
MODULES += $(CP_BINDER_CTL)
CLEANS += $(CLEAN_BINDER_CTL)

$(MODULE_BINDER_CTL): $(OBJS_BINDER_CTL)
	$(CC) -o $@ $^ -lexplain

$(OBJS_BINDER_CTL): %.o: %.c
	$(CC) -c -o $@ $<

$(CLEAN_BINDER_CTL):
	rm -f $(MODULE_PATH_BINDER_CTL)/*.o
	rm -f $(MODULE_BINDER_CTL)

$(CP_BINDER_CTL):
	mkdir -p $(DESTDIR)/bin
	cp -f $(MODULE_BINDER_CTL) $(DESTDIR)/bin/

