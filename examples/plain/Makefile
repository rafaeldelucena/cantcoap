INCLUDE= -I../../

#CXX=g++49
CXX=clang++
CXXFLAGS=-Wall -DDEBUG -std=c++11 $(INCLUDE)

#CC=gcc49
CC=clang
CFLAGS=-Wall -std=c99 -DDEBUG

default: server client gprs_gateway

server: ../../libcantcoap.a ../../nethelper.o server.cpp

client: ../../libcantcoap.a ../../nethelper.o client.cpp

gprs_gateway: ../../libcantcoap.a gprs_gateway.cpp

clean:
	rm server; rm client; rm gprs_gateway
