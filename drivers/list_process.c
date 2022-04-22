#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>

#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include<linux/slab.h>
#define DEV_LISTPROCESS_NAME "listprocess"
static dev_t listprocess_dev = 0;
static struct cdev *listprocess_cdev;
static struct class *listprocess_class;
struct task_struct *task;        /*    Structure defined in sched.h for tasks/processes    */
struct task_struct *task_child;        /*    Structure needed to iterate through task children    */
struct list_head *list;            /*    Structure needed to iterate through the list in each task->children struct    */
MODULE_LICENSE("GPL");
static loff_t listprocess_device_lseek(struct file *file, loff_t offset, int orig)
{
    return offset;
}

static int listprocess_open(struct inode *inode, struct file *file){
    return 0;
}

static int listprocess_release(struct inode *inode, struct file *file){
    return 0;
}
static ssize_t listprocess_read(struct file *file,
                        char *buf,
                        size_t size,
                        loff_t *offset){
    //printk(KERN_INFO "%s","LOADING MODULE\n");    /*    good practice to log when loading/removing modules    */
    char *comm_list=(char *)kmalloc( size, GFP_KERNEL);;
    int i=0;
    for_each_process( task ){            /*    for_each_process() MACRO for iterating through each task in the os located in linux\sched\signal.h    */
        if(i>100) break;
        comm_list[i++]=task->comm;
        printk(KERN_INFO "\nPARENT PID: %d PROCESS: %s STATE: %ld",task->pid, task->comm, task->state);/*    log parent id/executable name/state    */
        list_for_each(list, &task->children){                        /*    list_for_each MACRO to iterate through task->children    */

            task_child = list_entry( list, struct task_struct, sibling );    /*    using list_entry to declare all vars in task_child struct    */
    
            printk(KERN_INFO "\nCHILD OF %s[%d] PID: %d PROCESS: %s STATE: %ld",task->comm, task->pid, /*    log child of and child pid/name/state    */
                task_child->pid, task_child->comm, task_child->state);
                comm_list[i++]=task_child->comm;
        }
        printk("-----------------------------------------------------");    /*for aesthetics*/
    }   
    
    memcpy(buf,comm_list,100);
    buf[i]='\0';
    return 0;
}
static ssize_t listprocess_write(struct file *file,
                         const char *buf,
                         size_t size,
                         loff_t *offset){
    return 0;
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
    rc=alloc_chrdev_region(&listprocess_dev,0,1,DEV_LISTPROCESS_NAME);//register device number and name
    if(rc<0){
        printk(KERN_ALERT"Failed to register the fibonacci char device. rc = %i",
               rc);
        return rc;
    }
    listprocess_cdev=cdev_alloc(); //allocate a cdev structure
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
        goto failed_device_create;
    }
    return rc;


failed_device_create:
    class_destroy(listprocess_class);
failed_class_create:
    cdev_del(listprocess_cdev);
failed_cdev:
    unregister_chrdev_region(listprocess_dev,1);
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
MODULE_LICENSE("GPL");