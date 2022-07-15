CC := gcc
CFLAG := -pthread  -o
TARGET := ./threadpool
LIST_SOURCE:=../list/list.c
LIST_OBJ:= list.o
# find all c file 
SRCS := $(wildcard *.c)

# OBJS == all SRCS.o 
OBJS := $(SRCS:.c=.o)
SOURCE:= $(shell find  -name '*.c')

all: $(OBJS) 
	$(CC) $(OBJS) $(CFLAG) $(TARGET)

#GNU Make pattern rule: if %.o is not exist, use %.c and rule make a %.o file
# all c file will be compile into object file
# gcc -c := compile but link
%.o: %.c 
	$(CC)  $< $(LIST_SOURCE) $(CFLAG) $@

exe: clean all
	$(TARGET)

clean:
	rm $(TARGET) $(OBJS) >/dev/null 2>/dev/null || true 	
