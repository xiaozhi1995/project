ROOT_PATH=$(shell pwd)

INCLUDE=-I$(ROOT_PATH)/lib/include
LIB=-L$(ROOT_PATH)/lib/lib

my_json:udp_data.o my_json.o
	g++ -o $@ $^  $(LIB)  -ljsoncpp

%.o:%.cpp
	g++ -c $< $(INCLUDE) -D_DEBUG_

.PHONY:clean
clean:
	rm -f my_json *.o
