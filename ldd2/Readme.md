# About 
This is a basic device driver. It is built in C using makefile.<br>
This project has a simple driver which implements some system calls like read, write and llseek.<br>
The driver is assigned a major and minor number which are then used to create a device file in /dev folder.<br>
This folder also has an app.c which is an application which can make file operations on the device file from the User Space, which will then be processed by the driver2.c.<br>
<br>
# Steps to add the driver to your linux kernel:-<br>
- You must have sudo permissions.
- Run the make command on the shell to create the .ko file.<br>
  ```shell
  make
  ```
- Run the insmod command to insert the .ko module to the kernel.
  ```shell
  insmod driver2.ko
  ```
- To check if the module is inserted.
  ```shell
  lsmod
  ```
- To check the major number of the driver
  ```shell
  cat /proc/devices | grep my_driver2
  ```
- Now, we have to create a device file in the /dev folder
  ```shell
  mknod /dev/my_driver2_file c (major number) 0
  ```
- Compile and run the application to get the ouput.
  ```shell
  gcc app.c
  ./a.out
  ```
- You should now see the output.
- Lastly remove your module from the kernel and remove the device file.
  ```shell
  rmmod driver2
  rm /dev/my_driver2_file
  ```
