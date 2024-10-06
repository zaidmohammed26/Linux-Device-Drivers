#include<stdio.h>
#include<fcntl.h>

int main(){
    int fd,num;
    char buf[30];
    fd=open("/dev/my_driver2_file",O_RDWR);
    if (fd < 0) {
        printf("Failed to open the device");
        return -1;
    }
    write(fd,"Hello World",11);
    // lseek(fd,0,SEEK_SET);
    read(fd,buf,sizeof(buf));
    printf("data recieved is: %s\n",buf);

    close(fd);
    return 0;
}