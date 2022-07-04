TARGET := rwdriver
TESTOBJ := client.o
TESTSRC := client.c
obj-m +=  $(TARGET).o

CPPCHECK := 1
CC := gcc
CFLAG := -O

KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: clean check
	make -C $(KERNELDIR) M=$(PWD) modules 
 
clean: uninstall
	  rm -f out *.mod.cmd  *.ko.cmd *.o  *.dwo  *.ko  *.mod *.mod.c  *.mod.dwo  *.mod.o  *.o  *.order  *.symvers  .$(TARGET).*  .modules.order.cmd  .Module.symvers.cm  >/dev/null 2>/dev/null || true


check:
ifeq ($(CPPCHECK), 1)
	cppcheck ./
endif

install:
	sudo insmod $(TARGET).ko  >/dev/null 2>/dev/null || true

uninstall:
	sudo rmmod $(TARGET) >/dev/null 2>/dev/null || true

test: all $(TESTOBJ) install use
$(TESTOBJ):$(TESTSRC)
	$(CC) -o $@ $^

use:
	sudo ./$(TESTOBJ) > out.txt
