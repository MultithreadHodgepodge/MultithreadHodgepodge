CC := gcc
CFLAG := -pthread  -o
TARGET := ./threadpool

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
	$(CC) -c  $< $(CFLAG) $@

exe: clean all
	$(TARGET)

clean:
	rm $(TARGET) $(OBJS) >/dev/null 2>/dev/null || true 	
