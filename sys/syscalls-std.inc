; Conditional compilation while others include that header
%ifndef SYSCALLS_STD_INC
%define SYSCALLS_STD_INC 0

%define SYS_EXIT 60
%define SYS_READ 0
%define SYS_WRITE 1

%define EXIT_SUCCESS_CODE 0
%define EXIT_ERROR_CODE 1

;====================================
;       Write System call Macro
;   sys_write file descriptor, offset buffer(the buffer the is writing to the file), bytes num(the num of bytes we are writing)
;
;   The macro is invoking Linux's write system call and writes into the file descriptor's file
;====================================
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

;====================================
;       Read System call Macro
;   sys_read file descriptor, offset buffer(the buffer it's reading), bytes num(the num of bytes we are reading)
;
;   The macro is invoking Linux's read system call and reads from the file descriptor's file
;====================================
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

;====================================
;       Exit System call Macro
;   sys_exit exit_code
;
;   The macro is invoking Linux's exit system call and exit the process with the arg exit code.
;====================================
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
