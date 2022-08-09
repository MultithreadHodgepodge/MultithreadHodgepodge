OBJECT_SERVER=server.o
OBJECT_CLIENT=client.o
SERVER_SOURCE=server.c
CLIENT_SOURCE=client.c
RANDINT=$(shell python -c 'from random import randint; print(randint(0, 1));')
CC = gcc
.PHONY: clean
CFLAGS= -pthread -g -O0 -o
all:$(OBJECT_SERVER) $(OBJECT_CLIENT)
$(OBJECT_SERVER) : $(SERVER_SOURCE) 
	$(CC) $(CFLAGS) $@ $^
$(OBJECT_CLIENT): $(CLIENT_SOURCE)
	$(CC) $(CFLAGS) $@ $^
runserver:
	./$(OBJECT_SERVER)
runclient:
	for i in 1 to 1000 ; do \
		./$(OBJECT_CLIENT) $(RANDINT); \
	done
clean:
	rm -rf $(OBJECT_SERVER) $(OBJECT_CLIENT) >/dev/null 2>/dev/null || true
	