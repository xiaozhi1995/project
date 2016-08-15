all:ser cli
ser:server.cpp common.cpp
	g++ -o $@ $^ -lpthread
cli:client.cpp common.cpp
	g++ -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f ser cli
