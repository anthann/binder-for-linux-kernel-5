MODULE_PATH_LIB := libs
MODULE_LIB := $(MODULE_PATH_LIB)/libbinder.a
INCLUDE_LIB := $(MODULE_PATH_LIB)/include/

CP_LIB := cp_lib

MODULES += $(MODULE_LIB)
MODULES += $(CP_LIB)
CLEANS += $(CLEAN_LLOG)

include $(MODULE_PATH_LIB)/cutils/Makefile
include $(MODULE_PATH_LIB)/utils/Makefile
include $(MODULE_PATH_LIB)/binder/Makefile

CFLAGS_LIB := -I$(INCLUDE_LIB) -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1
CXXFLAGS_LIB := $(CFLAGS_LIB) -std=c++11

$(MODULE_LIB): $(objects)
	ar cr $@ $^

clean:
	rm -f `find -name \*.o`

%.o : %.cpp
	$(CXX) $(CXXFLAGS_LIB) -c -o $@ $<
%.o : %.c
	$(CC) $(CFLAGS_LIB) -c -o $@ $<

$(CP_LIB):
	mkdir -p $(DESTDIR)/lib
	mv $(MODULE_LIB) $(DESTDIR)/lib/
	cp -r $(INCLUDE_LIB) $(DESTDIR)/
