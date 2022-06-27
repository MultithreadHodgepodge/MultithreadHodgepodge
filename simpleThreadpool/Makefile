CC := gcc
CFLAG := -pthread -o
TARGET := ./threadpool
SOURCE := main.c

all: 
	$(CC) $(LISTLIB) $(SOURCE) $(CFLAG) $(TARGET)

exe: clean all
	$(TARGET)

clean:
	rm $(TARGET) >/dev/null 2>/dev/null || true 	
