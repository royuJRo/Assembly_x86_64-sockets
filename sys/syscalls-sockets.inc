; Conditional compilation while others include that header
%ifndef SYSCALLS_SOCKETS_INC
%define SYSCALLS_SOCKETS_INC 0

; Including the base system calls(Those who responsible on I/O, standards, ect.).
%include "sys/syscalls-std.inc"

%define SYS_SOCKET 41

; Defining protocol's families(most of the times refer to third layer protocols(such IP(defined by AF_INET))).
%define AF_INET 2

; Defining protocol's type(most of the times refer to fourth layer protocols(such TCP(defined by SOCK_STREAM))).
%define SOCK_STREAM 1
; SOCK_DGRAM is for UDP protocol.
%define SOCK_DGRAM 2

;====================================
;       Socket System call Macro
;   sys_socket family(integer), type(integer), protocol(integer , mostly 0), file descriptor offset(Address
; , varrible offset)
;
;   The macro is invoking Linux's socket system call and storing the file descriptor in the address given
;   as the fourth parameter.
;
;====================================
%macro sys_socket 4
    push rdi
    push rsi
    push rdx

    mov rdi, %1 ; socket family
    mov rsi, %2 ; socket type
    mov rdx, %3 ; socket protocol
    call _sys_socket
    pop rdi ; getting the socket's file descriptor
    mov rsi, %4 ; getting the varrible which is hosting the file descriptor address.
    mov word [rsi], di ; hosting the file descriptor in memory.

    pop rdx
    pop rsi
    pop rdi
%endmacro

;====================================
;       Socket System call
;   rdi <---- socket family(integer)
;   rsi <---- socket type(integer)
;   rdx <---- socket protocol(o in most cases)
;
;   The function returns the socket's file descriptor using the stack
;====================================
_sys_socket:
    push rax

    mov rax, SYS_SOCKET
    syscall

    mov rdi, rax ; moving the file descriptor from the returned value of socket system call in rax.
    
    pop rax
    pop rsi ; getting the return address that in the stack in preperation for rerurning a value(socket
    ; file descriptor via stack)
    push rdi ; pushing the file descriptor for returning it later.
    push rsi ; pushing back the return address to stack.
ret

%endif
;SYSCALLS_SOCKETS_INC