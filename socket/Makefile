OBJECT_SERVER=server.o
OBJECT_CLIENT=client.o
SERVER_SOURCE=server.c
CLIENT_SOURCE=client.c
CC = gcc
.PHONY: clean
CFLAGS= -pthread -g -O0 -o
all:$(OBJECT_SERVER) $(OBJECT_CLIENT)
$(OBJECT_SERVER) : $(SERVER_SOURCE) 
	$(CC) $(CFLAGS) $@ $^
$(OBJECT_CLIENT): $(CLIENT_SOURCE)
	$(CC) $(CFLAGS) $@ $^
clean:
	rm -rf $(OBJECT_SERVER) $(OBJECT_CLIENT) >/dev/null 2>/dev/null || true
	