#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>

#define DEV_LISTPROCESS_NAME "listprocess"
static dev_t listprocess_dev = 0;
static struct cdev *listprocess_cdev;
static struct class *listprocess_class;
static loff_t listprocess_device_lseek(struct file *file, loff_t offset, int orig)
{
    
}

static int listprocess_open(struct inode *inode, struct file *file){

}

static int listprocess_release(struct inode *inode, struct file *file){

}
static ssize_t listprocess_read(struct file *file,
                        char *buf,
                        size_t size,
                        loff_t *offset){

}
static ssize_t listprocess_write(struct file *file,
                         const char *buf,
                         size_t size,
                         loff_t *offset){

}
const struct file_operations listprocess_fops = {
    .owner = THIS_MODULE,
    .read = listprocess_read,
    .write = listprocess_write,
    .open = listprocess_open,
    .release = listprocess_release,
    .llseek = listprocess_device_lseek,
};
static int __init init_listprocess_dev(void){
    int rc = 0;
    rc=alloc_chrdev_region(&listprocess_dev,0,1,DEV_LISTPROCESS_NAME);
    if(rc<0){
        printk(KERN_ALERT"Failed to register the fibonacci char device. rc = %i",
               rc);
        return rc;
    }
    listprocess_cdev=cdev_alloc();
    if(listprocess_cdev==NULL){
        printk(KERN_ALERT"Failed to alloc cdev");
        rc=-1;
        goto failed_cdev;
    }
    listprocess_cdev->ops=&listprocess_fops;
    rc=cdev_add(listprocess_cdev,listprocess_dev,1);
    if(rc<0){
        printk(KERN_ALERT "Failed to add cdev");
        rc=-2;
        goto failed_cdev;
    }
    listprocess_class=class_create(THIS_MODULE,DEV_LISTPROCESS_NAME);
    if(!listprocess_class){
        printk(KERN_ALERT "Failed to create device class");
        rc = -3;
        goto failed_class_create;

    }
    if(!device_create(listprocess_class,NULL,listprocess_dev,NULL,DEV_LISTPROCESS_NAME)){
        printk(KERN_ALERT "Failed to create device");
        rc = -4;
        goto failed_class_create;
    }
    return rc;
failed_cdev:
    unregister_chrdev_region(listprocess_dev,1);
failed_class_create:
    cdev_del(listprocess_cdev);
failed_device_create:
    class_destroy(listprocess_class);
    return rc;
}

static void __exit exit_listprocess_dev(void){
    device_destroy(listprocess_class,listprocess_dev);
    class_destroy(listprocess_class);
    cdev_del(listprocess_cdev);
    unregister_chrdev_region(listprocess_dev,1);
}

module_init(init_listprocess_dev);
module_exit(exit_listprocess_dev);