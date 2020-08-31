%macro detect_socket_error 0
    cmp rax, 0
    jle socket_error
%endmacro

section .data
    socket_error_msg db "Socket error. Check connection details !",10,0
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
        sys_socket AF_INET, SOCK_STREAM, 0
        mov [socketfd], rax
        detect_socket_error
        
        printf string
        printfn [socketfd]
        new_line

        allocate_sockaddr_in AF_INET, 4444, 0
        mov [sockaddr_in_pointer], rax

                
        sys_connect [socketfd], [sockaddr_in_pointer]
        detect_socket_error
        printfn rax
        new_line

        jmp exit

    socket_error:    
        printf socket_error_msg

    exit:
        sys_exit 0
