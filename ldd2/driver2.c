#include<linux/module.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>

MODULE_LICENSE("GPL");

char driver_name[]="my_driver2";
char driver_buff[1024];
int device_size=1024;
int ret;
static dev_t mydev;
static struct cdev my_cdev;

int drv_open(struct inode *i,struct file *f){
    printk("open entry point\n");
    return 0;
}


ssize_t drv_write(struct file *f, const char *ubuff, size_t size, loff_t *offset) {
    printk("write entry point\n");
    if (size > device_size) {
        printk("Error: size exceeds device buffer size\n");
        return -EINVAL;  
    }

    int ret = copy_from_user(driver_buff, ubuff, size);
    if (ret) {
        printk("Failed to copy data to user space\n");
        return -EFAULT;  
    }
    driver_buff[size]='\0';

    f->f_pos += size;  
    printk("Data received from user space: %s\n", driver_buff);
    return size;  
}

ssize_t drv_read(struct file *f, char *ubuff, size_t size, loff_t *offset) {
    printk("Read entry point\n");

    if (*offset >= device_size) {
        return 0;  
    }

    size_t to_read = min(size, (size_t)(device_size - *offset));
    int ret = copy_to_user(ubuff, driver_buff + *offset, to_read);
    
    if (ret) {
        printk("Failed to copy data to user space\n");
        return -EFAULT;  
    }

    *offset += to_read;  
    return to_read;  
}

int drv_close(struct inode *i,struct file *f){
    printk("close entry point");
    return 0;
}

loff_t drv_lseek(struct file *f,loff_t off,int whence){
    loff_t newpos;
    printk("Lseek entry point\n");
    switch(whence){
        case 0:
            newpos = off;
            break;
        case 1:
            newpos=f->f_pos+off;
            break;
        case 2:
            newpos=device_size+off;
            break;
    }
    if(newpos<0)
    return -EINVAL;
    f->f_pos=newpos;
    return newpos;
}

struct file_operations fops={
    .open=drv_open,
    .write=drv_write,
    .read=drv_read,
    .release=drv_close,
    .llseek=drv_lseek
};

int init_module(void){
    printk("init module");
    ret = alloc_chrdev_region(&mydev,0,1,driver_name);
    if(ret<0){
        return -1;
    }
    cdev_init(&my_cdev, &fops);  
    my_cdev.owner = THIS_MODULE;

    ret = cdev_add(&my_cdev, mydev, 1);  
    if (ret < 0) {
        printk("Failed to add cdev\n");
        unregister_chrdev_region(mydev, 1);
        return ret;
    }
    printk("allocated major number=%d and minor number=%d",MAJOR(mydev),MINOR(mydev));
    return 0;
}

void cleanup_module(){
    printk("cleanup_module");
    cdev_del(&my_cdev);
    unregister_chrdev_region(mydev,1);
}