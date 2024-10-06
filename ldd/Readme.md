# About 
This is a basic device driver. It is built in C with make utility.<br>
This project has a simple driver which implements one system call which is read().<br>
The driver reads from a proc file which is created in the init_module itself.<br>
This folder also has a app.py which is an application which can call the read() on the proc file from the User Space, which will then be processed by the driver1.c.<br>
<br>
# Steps to add the driver to your linux kernel:-<br>
- You must have sudo permissions.
- Run the make command on the shell to create the .ko file.<br>
  ```shell
  make
  ```
- Run the insmod command to insert the .ko module to the kernel.
  ```shell
  insmod driver1.ko
  ```
- To check if the module is inserted.
  ```shell
  lsmod
  ```
- Run the python app to get the ouput.
  ```shell
  python3 app.py
  ```
- You should now see the output.
- You can also use cat command to call read().
  ```shell
  cat /proc/driver1_proc
  ```
- Lastly remove your module from the kernel.
  ```shell
  rmmod driver2
  ```
