ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
COMM=$(ROOT_PATH)/comm
DATA_POOL=$(ROOT_PATH)/data_pool

SERVER_BIN=udp_server
CLIENT_BIN=udp_client

INCLUDE=-I$(COMM)
INCLUDE+=-I$(DATA_POOL)
CC=g++
FLAGS=
LDFLAGS=-lpthread#-static

SER_SRC=$(shell  ls -r $(SERVER) | grep -E '*.cpp')
SER_SRC+=$(shell ls -r $(COMM) | grep -E '*.cpp')
SER_SRC+=$(shell ls -r $(DATA_POOL) | grep -E '*.cpp')
SER_OBJ=$(SER_SRC:.cpp=.o)

CLI_SRC=$(shell  ls -r $(CLIENT) | grep -E '*.cpp')
CLI_SRC+=$(shell ls -r $(COMM) | grep -E '*.cpp')
CLI_OBJ=$(CLI_SRC:.cpp=.o)


.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SER_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
$(CLIENT_BIN):$(CLI_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o:$(COMM)/%.cpp
	$(CC) -c $< $(INCLUDE)

%.o:$(DATA_POOL)/%.cpp
	$(CC) -c $< $(INCLUDE)

%.o:$(SERVER)/%.cpp
	$(CC) -c $< $(INCLUDE)

%.o:$(CLIENT)/%.cpp
	$(CC) -c $< $(INCLUDE)

.PHONY:clean
clean:
	rm -f *.o $(SERVER_BIN)  $(CLIENT_BIN)

