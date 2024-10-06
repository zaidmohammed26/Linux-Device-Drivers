#include<linux/init.h>
#include<linux/module.h>
#include<linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZAID");
MODULE_DESCRIPTION("Basic Driver to implement a read system call");

struct proc_dir_entry *proc_entry;

ssize_t	driver1_read(struct file * file_pointer, char * user_buffer, size_t count, loff_t *offset){
    char msg[]="YOO!!";
    size_t len=strlen(msg);
    if(*offset>=len)
    return 0;
    int result=copy_to_user(user_buffer,msg+(*offset),2);
    *offset+=2;
    printk("success read");
    return 2;
}

struct proc_ops driver1_proc_ops = {
    .proc_read = driver1_read
};
static int driver1_init(void){
     proc_entry=proc_create("driver1_proc", 0,NULL, &driver1_proc_ops );
     printk("success init");
    return 0;
}

static void driver1_exit(void){
    proc_remove(proc_entry);
    printk("success cleanup");
}

module_init(driver1_init); 
module_exit(driver1_exit); 