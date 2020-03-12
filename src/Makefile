
# export env for mk.
CC=gcc-7
CXX=g++-7
TOPDIR=.

MODULES=
CLEANS=
INSTALLS=

DESTDIR := $(TOPDIR)/build
CP_DRIVER_INCLUDE := cp_driver_include

-include liblog/Makefile
-include servicemanager/Makefile
-include binder/Makefile
-include binder-control/Makefile
MODULES += $(CP_DRIVER_INCLUDE)

.PHONY: all
all: $(MODULES)

clean: $(CLEANS)

install: $(INSTALLS)


$(CP_DRIVER_INCLUDE):
	cp -r include $(DESTDIR)/
