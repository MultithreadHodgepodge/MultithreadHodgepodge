#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>

/*  Prototypes - this would normally go in a .h file */ 
static int rwdriver_open(struct inode *, struct file *); 
static int rwdriver_release(struct inode *, struct file *); 
static ssize_t rwdriver_read(struct file *, char __user *, size_t, loff_t *); 
static ssize_t rwdriver_write(struct file *, const char __user *, size_t, loff_t *);

/* /dev/DEVICE_NAME */
#define DEVICE_NAME "rwdriver" 
#define SUCCESS 0
#define BUF_LEN 80

static unsigned int num_of_dev = 1;
static unsigned int rwdriver_major = 0;
static struct cdev rwdriver_cdev;

/* #define status */
enum { 
    CDEV_NOT_USED = 0, 
    CDEV_EXCLUSIVE_OPEN = 1, 
};

/* lock the driver when use */
static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED);

struct kernel_buffer {
	char msg[BUF_LEN];
	unsigned int size;
};

static struct class *cls;

/* VFS register the driver method */
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open  = rwdriver_open,
	.release = rwdriver_release,
	.read  = rwdriver_read,
	.write = rwdriver_write,
};


/* __init in <init.h> */
static int __init init_function(void) 
{
	printk(KERN_INFO "This is rwdriver\n");

	/* get unused major num */
	rwdriver_major = register_chrdev(0, DEVICE_NAME, &fops); 
	if (rwdriver_major < 0) {
		pr_alert("Registering char device failed with %u\n", rwdriver_major);
		return rwdriver_major;
	}

	pr_info("I was assigned major number %u\n", rwdriver_major);
	
	cls = class_create(THIS_MODULE, DEVICE_NAME);
	device_create(cls, NULL, MKDEV(rwdriver_major, 0), NULL, DEVICE_NAME);

	pr_info("Device create on /dev/%s\n", DEVICE_NAME);

	return SUCCESS;
}

static void __exit exit_function(void)
{
	device_destroy(cls, MKDEV(rwdriver_major, 0));
	class_destroy(cls);

	/* Unregister the device */
	unregister_chrdev(rwdriver_major, DEVICE_NAME);

	printk(KERN_INFO "rwdriver out\n");
}

/* TODO: implement mutithread reader-writer problem */
static int rwdriver_open(struct inode *inode, struct file *file) 
{
	return SUCCESS;
}

/* TODO: implement mutithread reader-writer problem */
static int rwdriver_release(struct inode *inode, struct file *file) 
{
	return 0;
}

/* TODO: implement mutithread reader-writer problem */
static ssize_t rwdriver_read(struct file *filp, /* see include/linux/fs.h   */ 
                           char __user *buffer, /* buffer to fill with data */ 
                           size_t length, /* length of the buffer     */ 
                           loff_t *offset) 
{
	return 0;
}

/* TODO: implement mutithread reader-writer problem */
static ssize_t rwdriver_write(struct file *filp, const char __user *buff, 
                            size_t len, loff_t *off) 
{
	return 0;
}

module_init(init_function);
module_exit(exit_function);

MODULE_AUTHOR("Peter.K ");
MODULE_LICENSE("Dual MIT/GPL");

