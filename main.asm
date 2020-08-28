
section .data
    string db "Hello world !", 10, 0

section .data
    global _start

    %include "std/stdio.inc"

    _start:
        printf string

    exit:
        sys_exit 0
