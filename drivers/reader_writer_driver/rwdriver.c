#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/interrupt.h>

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
static size_t eno;
/* #define status */
enum { 
    CDEV_NOT_USED = 0, 
    CDEV_EXCLUSIVE_OPEN = 1, 
};



typedef struct reader_writer_buffer {
	char msg[BUF_LEN];
	unsigned int size;
	rwlock_t myrwlock;
} RW_buffer;


RW_buffer *buff;


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
	pr_info("------------------------------\n");
	printk(KERN_INFO "This is rwdriver\n");

	

	/* get unused major num */
	rwdriver_major = register_chrdev(0, DEVICE_NAME, &fops); 
	if (rwdriver_major < 0) {
		eno = 1;
		pr_alert("Registering char device failed with %u\n", rwdriver_major);
		return rwdriver_major;
	}

	pr_info("I was assigned major number %u\n", rwdriver_major);
	
	cls = class_create(THIS_MODULE, DEVICE_NAME);
	if (!cls) {
		eno = 2;
		printk(KERN_ERR "cls create fail\n");
		goto cls_fail;
	}
	if(!device_create(cls, NULL, MKDEV(rwdriver_major, 0), NULL, DEVICE_NAME)) {
		eno = 3;
		printk(KERN_ERR "device_create failed\n");
		goto device_fail;
	}
	
	pr_info("Device create on /dev/%s\n", DEVICE_NAME);

	buff = kmalloc(sizeof(RW_buffer), GFP_KERNEL);
	if (!buff) {
		eno = 4;
		printk(KERN_ERR "No memory for buff\n");
		goto buff_fail;
	}

	/* initialize buff object */
	buff->size = 0;
	rwlock_init(&buff->myrwlock);
	return SUCCESS;

buff_fail:
	device_destroy(cls, MKDEV(rwdriver_major, 0));
device_fail:
	class_destroy(cls);
cls_fail:	
	/* Unregister the device */
	unregister_chrdev(rwdriver_major, DEVICE_NAME);
	
	return eno;
}

static void __exit exit_function(void)
{
	device_destroy(cls, MKDEV(rwdriver_major, 0));
	class_destroy(cls);
	
	/* Unregister the device */
	unregister_chrdev(rwdriver_major, DEVICE_NAME);
	
	if (!buff)
		kfree(buff);
	
	printk(KERN_INFO "rwdriver out\n");
	pr_info("------------------------------\n");
}

static int rwdriver_open(struct inode *inode, struct file *file) 
{
	pr_info("%s open\n", DEVICE_NAME);
	return SUCCESS;
}

static int rwdriver_release(struct inode *inode, struct file *file) 
{
	pr_info("%s close", DEVICE_NAME);
	return 0;
}

static ssize_t rwdriver_read(struct file *filp, /* see include/linux/fs.h   */ 
                           char __user *buffer, /* buffer to fill with data */ 
                           size_t len, /* length of the buffer     */ 
                           loff_t *offset) 
{
	
	if (!buff) {
		printk(KERN_ERR "No rw_buffer\n");
		return -1;
	}

	unsigned long flags;

	len = (buff->size > len)? len : buff->size;

	read_lock_irqsave(&buff->myrwlock, flags);
	pr_info("Read Locked\n");

	snprintf(buffer, len, buff->msg);

	read_unlock_irqrestore(&buff->myrwlock, flags);
	pr_info("Read Unlocked\n");
	return 0;
}

static ssize_t rwdriver_write(struct file *filp, const char __user *buffer, 
                            size_t len, loff_t *off) 
{
	if (!buff) {
		printk(KERN_ERR "No rw_buffer\n");
		return -1;
	}

	unsigned long flags;

	len = (BUF_LEN > len)?len:BUF_LEN;

	write_lock_irqsave(&buff->myrwlock, flags);
	pr_info("Write Locked\n");

	snprintf(buff->msg, len, buffer);

	pr_info("buffer contains: %s\n", buff->msg);
	write_unlock_irqrestore(&buff->myrwlock, flags);
	
	pr_info("Write Unlocked\n");

	buff->size = len;
	return 0;
}

module_init(init_function);
module_exit(exit_function);

MODULE_AUTHOR("Peter.K ");
MODULE_LICENSE("Dual MIT/GPL");

