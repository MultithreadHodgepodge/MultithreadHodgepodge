# module name
TARGET_MODULE := list_process
obj-m += $(TARGET_MODULE).o
OBJECT_TEST= client.o
TEST_SOURCE= client.c
# kernel lib path
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

CC = gcc

CONFIG_MODULE_SIG=n
# -C: where your keren source
# M : back to path M to build modules
all:
	make -C $(KERNELDIR) M=$(PWD) modules

test: $(OBJECT_TEST)
$(OBJECT_TEST): $(TEST_SOURCE)
	$(CC) -o $@ $^

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
	rm -rf ./$(OBJ_DIR)*.o