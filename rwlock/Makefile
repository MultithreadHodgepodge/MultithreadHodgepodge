CC := gcc
CFLAG := -pthread -g -o

TARGET := test_rwlock
SRC := rwlock.c test_rwlock.c
OBJ := test_rwlock.o

all:
	$(CC) $(SRC) $(CFLAG) $(OBJ)


%.o: %.c
	$(CC) -c %.o $< $(FLAG) $@

