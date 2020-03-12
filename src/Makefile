
# export env for mk.
CC=gcc-7
CXX=g++-7
TOPDIR=.

MODULES=
CLEANS=
INSTALLS=

DESTDIR := $(TOPDIR)/build

-include liblog/Makefile
-include servicemanager/Makefile
-include binder/Makefile
-include binder-control/Makefile

.PHONY: all
all: $(MODULES)

clean: $(CLEANS)

install: $(INSTALLS)

