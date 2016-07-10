ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
DATA_POOL=$(ROOT_PATH)/data_pool
LIB=$(ROOT_PATH)/lib
PLUGIN=$(ROOT_PATH)/plugin
CONF=$(ROOT_PATH)/conf
WINDOW=$(ROOT_PATH)/window

SERVER_BIN=udp_server
CLIENT_BIN=udp_client

INCLUDE=-I$(COMM) -I$(DATA_POOL) -I$(LIB)/include -I$(WINDOW)
LIB_JSON=-L$(LIB)/lib
CC=g++
FLAGS=-D_DEBUG_
LDFLAGS=-lpthread -ljsoncpp #-static

SER_SRC=$(shell ls -R $(SERVER) | grep -E '*.cpp')
SER_SRC+=$(shell ls -R $(COMM) | grep -E '*.cpp')
SER_SRC+=$(shell ls -R $(DATA_POOL) | grep -E '*.cpp')
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell ls -R $(CLIENT) | grep -E '*.cpp')
CLI_SRC+=$(shell ls -R $(COMM) | grep -E '*.cpp')
CLI_SRC+=$(shell ls -R $(WINDOW) | grep -E '*.cpp')
CLI_OBJ=$(CLI_SRC:.cpp=.o)

.PHONY: all
all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SER_OBJ)
	@$(CC) -o $@ $^  $(LIB_JSON) $(LDFLAGS)
	@echo "Linking [ $^ ] to [ $@ ] ... done."
$(CLIENT_BIN):$(CLI_OBJ)
	@$(CC) -o $@ $^ $(LIB_JSON) $(LDFLAGS) -lncurses -static
	@echo "Linking [ $^ ] to [ $@ ] ... done."
%.o:$(COMM)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
#@echo "Compling [ $< ] to [ $@ ] .... done."
	@echo "Compling [ $(shell basename $<) ]  to [ $@ ] .... done."
%.o:$(SERVER)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
#	@echo "Compling [ $< ] to [ $@ ] .... done."
	@echo "Compling [ $(shell basename $<) ]  to [ $@ ] .... done."
%.o:$(CLIENT)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "Compling [ $(shell basename $<) ]  to [ $@ ] .... done."
#@echo "Compling [ $< ] to [ $@ ] .... done."
%.o:$(DATA_POOL)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "Compling [ $(shell basename $<) ]  to [ $@ ] .... done."
%.o:$(WINDOW)/%.cpp
	@$(CC) -c $< $(INCLUDE) $(FLAGS)
	@echo "Compling [ $(shell basename $<) ]  to [ $@ ] .... done."

.PHONY:clean
clean:
	@rm -rf *.o $(SERVER_BIN) $(CLIENT_BIN) output
	@echo "clean ... done."

.PHONY:output
output: all
	@mkdir -p output/server
	@mkdir -p output/server/lib
	@mkdir -p output/server/log
	@mkdir -p output/server/conf
	@mkdir -p output/client
	@cp -f $(SERVER_BIN) output/server/
	@cp -f $(CLIENT_BIN) output/client/
	@cp -f $(PLUGIN)/server_ctl.sh output/server/
	@cp -f $(PLUGIN)/client_ctl.sh output/client/
	@cp -f $(CONF)/server.conf output/server/conf

.PHONY:debug
debug:
	@echo $(SER_SRC)
	@echo $(SER_OBJ)

#lib
#log
