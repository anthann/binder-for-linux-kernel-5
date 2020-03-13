MODULE_PATH_TEST := test_service
MODULE_TEST_SERVER := $(MODULE_PATH_SM)/test_server
MODULE_TEST_CLIENT := $(MODULE_PATH_SM)/test_client
CLEAN_TEST := clean_test
CP_TEST := cp_test

MODULES += $(MODULE_TEST_SERVER)
MODULES += $(MODULE_TEST_CLIENT)
MODULES += $(CP_TEST)
CLEANS += $(CLEAN_TEST)

test_server_sources := \
	IBasicService.cpp \
	server.cpp 

test_client_sources := \
	IBasicService.cpp \
	client.cpp 

TEST_SERVER_OBJS := $(patsubst %.cpp,$(MODULE_PATH_TEST)/%.o, $(test_server_sources))
TEST_CLIENT_OBJS := $(patsubst %.cpp,$(MODULE_PATH_TEST)/%.o, $(test_client_sources))


$(MODULE_TEST_SERVER): $(TEST_SERVER_OBJS)
	$(CXX) $(CXXFLAGS_LIB)  $(CXXFLAGS_LIB) -o $@ $^ -I$(INCLUDE_LIB) -L$(DESTDIR)/lib -lbinder -lpthread

$(MODULE_TEST_CLIENT): $(TEST_CLIENT_OBJS)
	$(CXX) $(CXXFLAGS_LIB)  $(CXXFLAGS_LIB) -o $@ $^ -I$(INCLUDE_LIB) -L$(DESTDIR)/lib -lbinder -lpthread

$(CLEAN_TEST):
	rm -f $(MODULE_PATH_TEST)/*.o 

%.o: %.cpp
	$(CXX) $(CXXFLAGS_LIB) -c -o $@ $< -I$(INCLUDE_LIB)

$(CP_TEST):
	mkdir -p $(DESTDIR)/bin
	mv $(MODULE_TEST_SERVER) $(DESTDIR)/bin/
	mv $(MODULE_TEST_CLIENT) $(DESTDIR)/bin/
