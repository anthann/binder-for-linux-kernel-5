
# export env for mk.
CC=gcc-4.8
CXX=g++-4.8
TOPDIR=.

MODULES=
CLEANS=
INSTALLS=

-include binder-control/Makefile
-include libs/Makefile
-include servicemanager/Makefile 
-include test_service/Makefile
DESTDIR := $(TOPDIR)/build

.PHONY: all
all: $(MODULES)

clean: $(CLEANS)

install: $(INSTALLS)

