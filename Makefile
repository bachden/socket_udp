CC := g++-12
SRC_DIR := src
BUILD_DIR := build

LIB := lib
INC := -I./include

OUTPUT := build
OUTPUT_SHARED_OBJS := $(OUTPUT)/shared/objs

shared: src/utils
	mkdir -p $(OUTPUT_SHARED_OBJS)
	for i in `find ./src/utils -type f -iregex ".*\.cpp"` ; do $(CC) -c $$i -o $(OUTPUT_SHARED_OBJS)/`basename $$i .cpp`.o $(INC) ; done 

udp_server: src/server.cpp shared
	$(CC) $(OUTPUT_SHARED_OBJS)/*.o $< -o $(OUTPUT)/$@ $(INC)

udp_client: src/client.cpp shared
	$(CC) $(OUTPUT_SHARED_OBJS)/*.o $< -o $(OUTPUT)/$@ $(INC)

all: udp_server udp_client

.PHONY: clean

clean:
	rm -fr $(OUTPUT_SHARED_OBJS)/* $(OUTPUT)/udp_client $(OUTPUT)/udp_server