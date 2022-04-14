# module name
TARGET_MODULE := list_process
obj_m := $(TARGET_MODULE).o

# kernel lib path
KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

# -C: where your keren source
# M : back to path M to build modules
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean