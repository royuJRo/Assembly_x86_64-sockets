
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

;====================================
;       printf function Macro
;   printf integer(real, a register or memory effective address)
;
;   The macro is invoking printf classic function for a 64 bit integer using Linux's write system call.(Writing to the stdout fd)
;====================================
%macro printfn 1
    push rsi

    mov rsi, %1
    call _printfn

    pop rsi
%endmacro

;====================================
;         new_line Macro
;   The Macro prints "\n" to console
;====================================
%macro new_line 0
    call _new_line
%endmacro


%include "sys/syscalls-std.inc"

;====================================
;         printf function
;   rsi <---- destenation buffer offset
;
;   The function prints the string(defined as a string by ANSII)
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

;====================================
;         printfn function
;   rsi <---- destenation to 64 bit integer
;
;   The function prints the integer
;====================================
_printfn:

    mov rax, 0
    mov rdx, 0
    mov rcx, 3

    _initialize_printfn:
        push rax
    loop _initialize_printfn

    mov rbx, 21
    mov rcx, 10
    mov rax, rsi
    _converting_to_str_printfn:
        div rcx
        add rdx, 48 ; addind the value of '0'
        mov byte [rsp+rbx], dl

        mov rdx, 0
        dec rbx
        cmp rax, 0
        jne _converting_to_str_printfn

    lea rsi, [rsp+rbx+1]
    printf rsi

    mov rcx, 3
    _cleaning_printfn:
        pop rax
    loop _cleaning_printfn

ret

;====================================
;         new_line function
;   The funnction prints "\n" to console
;====================================
_new_line:
    push rax
    push rsi

    mov rax , 10
    push rax
    mov rsi, rsp
    printf rsi
    pop rax

    pop rsi
    pop rax

ret

%endif
;STD_IO_INC