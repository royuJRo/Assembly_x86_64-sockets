
section .data
    string db "The socket file descriptor is : ", 0

section .bss
    socketfd resq 1
    sockaddr_in_pointer resq 1

section .data
    global _start

    %include "std/stdio.inc"
    %include "sys/syscalls-sockets.inc"
    %include "sys/syscalls-std.inc"

    _start:
        sys_socket AF_INET, SOCK_STREAM, 0, socketfd
        
        printf string
        printfn [socketfd]
        new_line

        allocate_sockaddr_in AF_INET, 4444, 0
        mov [sockaddr_in_pointer], rax
        
        sys_connect [socketfd], [sockaddr_in_pointer]

        sys_write [socketfd], string, 10
       
        
    exit:
        sys_exit 0
