# module name
TARGET_MODULE := list_process
obj-m += $(TARGET_MODULE).o
OBJECT_TEST= client.o
TEST_SOURCE= client.c
# kernel lib path
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

CPPCHECK := 1

CC = gcc

# -C: where your keren source
# M : back to path M to build modules
all: check	
	make -C $(KERNELDIR) M=$(PWD) modules

test: $(OBJECT_TEST) all install
$(OBJECT_TEST): $(TEST_SOURCE)
	$(CC) -o $@ $^

install:
ifeq ($(shell lsmod | grep hello), )
	sudo insmod $(TARGET_MODULE).ko
endif

uninstall:
ifneq ($(shell lsmod | grep hello), )
	sudo rmmod $(TARGET_MODULE)
endif

check:
ifeq ($(CPPCHECK), 1)
	cppcheck $(TARGET_MODULE).c
endif

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
	rm -rf ./$(OBJ_DIR)*.o
