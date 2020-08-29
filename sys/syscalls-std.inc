; Conditional compilation while others include that header
%ifndef SYSCALLS_STD_INC
%define SYSCALLS_STD_INC 0

%define SYS_EXIT 60
%define SYS_READ 0
%define SYS_WRITE 1

%define EXIT_SUCCESS_CODE 0
%define EXIT_ERROR_CODE 1

%macro sys_write 3
    push rdi
    push rsi
    push rdx

    mov rdi, %1
    mov rsi, %2
    mov rdx, %3

    call _sys_write

    pop rdx
    pop rsi
    pop rdi
%endmacro

%macro sys_read 3
    push rdi
    push rsi
    push rdx

    mov rdi, %1
    mov rsi, %2
    mov rdx, %3

    call _sys_read

    pop rdx
    pop rsi
    pop rdi
%endmacro

%macro sys_exit 1
    push rdi

    mov rdi, %1
    call _sys_exit
    
    pop rdi
%endmacro

;====================================
;       Write System call
;   rdi <---- file descriptor
;   rsi <---- source buffer offset
;   rdx <---- bytes to write the file
;====================================

_sys_write:
    push rax

    mov rax, SYS_WRITE
    syscall

    pop rax
ret

;====================================
;         Read System call
;   rdi <---- file descriptor
;   rsi <---- destenation buffer offset
;   rdx <---- bytes to read from the file
;====================================

_sys_read:
    push rax

    mov rax, SYS_READ
    syscall

    pop rax
ret

;====================================
;       Sys-Exit System call
;   rdi <---- exit code
;====================================

_sys_exit:
    push rax

    mov rax, SYS_EXIT
    syscall

    pop rax
ret

%endif
;SYSCALLS_STD_INC
