
section .data
    string db "Hello world !", 10, 0

section .bss
    socketfd resw 1

section .data
    global _start

    %include "std/stdio.inc"
    %include "sys/syscalls-sockets.inc"

    _start:
        printf string
        sys_socket AF_INET, SOCK_STREAM, 0, socketfd

    exit:
        sys_exit 0
