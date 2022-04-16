# module name
TARGET_MODULE := list_process
obj-m += $(TARGET_MODULE).o

# kernel lib path
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

# -C: where your keren source
# M : back to path M to build modules
all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean