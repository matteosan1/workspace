CPP=g++
RM=rm
CFLAGS=-I/usr/local/include/net-snmp -pipe -O2 -Wall -W -fPIC 
LDFLAGS=-L/usr/local/lib -lnetsnmp 
TARGET=poll_wifi_client

SRCS := $(wildcard *.cpp)

all: *.cpp
	$(CPP) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean: $(EXEC)
	$(RM) $(TARGET) $(OBJS)

