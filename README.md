# # Assembly_x86_64-sockets # #
A pure Assembly x86_64(Linux) project which I have been developing from scratch.
The project implements Sockets and standard libraries by using Assembly and the Linux kernel's system calls.

In the project I have been used the kernel's I/O system calls and the net system calls.

# Net system calls I have used :
  ```sys_socket```
  
  ```sys_connect```
  
  ```sys_accept```
  
  ```sys_shutdown```
  
  ```sys_bind```
  
  ```sys_listen```
  

# I/O system calls I have used : 
  ```sys_write```
  
  ```sys_read```
  
 And in addition to those syscall's implementation I have also used ```sys_exit``` to exit the program.
 
 
 Moreover, you might want to look at ```build``` file. This is a "costumize compiler" I have designed in attend to make
 the compilation much easier.
  
