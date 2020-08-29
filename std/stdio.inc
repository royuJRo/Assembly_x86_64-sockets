
; Conditional compilation while others include that header
%ifndef STD_IO_INC
%define STD_IO_INC 0

%define STDOUT 1
%define STDIN 0
%define STDERR 2


;====================================
;       printf function Macro
;   printf string offset(a offset of string to print)
;
;   The macro is invoking printf classic function using Linux's write system call.(Writing to the stdout fd)
;====================================
%macro printf 1
    push rsi

    mov rsi, %1
    call _printf

    pop rsi
%endmacro


%include "sys/syscalls-std.inc"

;====================================
;         printf function
;   rsi <---- destenation buffer offset
;====================================
_printf:
    push rdi
    push rdx

    _continue_printf:
    cmp byte [rsi], 0
    je _exit_printf

    mov rdi, STDOUT
    mov rdx, 1

    call _sys_write

    inc rsi

    jmp _continue_printf

    _exit_printf:

    pop rdx
    pop rdi

    ret







%endif
;STD_IO_INC