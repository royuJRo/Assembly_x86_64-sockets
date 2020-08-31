; Conditional compilation while others include that header
%ifndef SYSCALLS_SOCKETS_INC
%define SYSCALLS_SOCKETS_INC 0

; Including the base system calls(Those who responsible on I/O, standards, ect.).
%include "sys/syscalls-std.inc"

%define SYS_SOCKET 41
%define SYS_CONNECT 42

; Defining protocol's families(most of the times refer to third layer protocols(such IP(defined by AF_INET))).
%define AF_INET 2

; Defining protocol's type(most of the times refer to fourth layer protocols(such TCP(defined by SOCK_STREAM))).
%define SOCK_STREAM 1
; SOCK_DGRAM is for UDP protocol.
%define SOCK_DGRAM 2

;========================================
;       Allocate struct sockaddr_in
;              in the stack
;                 Macro
;
;   allocate_sockaddr_in socket_family(mostly AF_INET), host port(regular num), 32 bit IP address.
;
;   The macro changes rax, rdi, rsi, rdx, r10 values.
;   The macro returns in rax register the address in stack of our struct.
;========================================
%macro allocate_sockaddr_in 3
    mov rax, %1
    mov rdi, %2
    mov rsi, %3

    call _allocate_sockaddr_in
%endmacro


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
    mov qword [rsi], rdi ; hosting the file descriptor in memory.

    pop rdx
    pop rsi
    pop rdi
%endmacro

;====================================
;       Connect System call Macro
;   sys_connect file_descriptor(64 bit), pointer to sockaddr_in struct(64 bit)
;
;   The function returns the connection success in rax.(-1 in case of error)
;====================================
%macro sys_connect 2
    push rsi
    push rdi

    mov rdi, %1
    mov rsi, %2
    call _sys_connect

    pop rdi
    pop rsi
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

;====================================
;       Connect System call
;   rdi <---- socket's file descriptor.
;   rsi <---- pointet to the address to connect to.(struct sockaddr *uservaddr)
;
;   The function returns the connection success in rax.(-1 in case of error)
;====================================
_sys_connect:
    push rdx

    mov rax, SYS_CONNECT
    mov rdx, 16
    syscall

    pop rdx
ret

;========================================
;       Allocate struct sockaddr_in
;              in the stack
;   rax - connection family.(AF_INET for example)
;   rdi - port in regular numbers.(for example 4444)
;   rsi - the IP address.(in 32 bit format)
;
;   Registers rdx, r10 are changing their values through the subroutine.
;
;   The function returns in rax register the address in stack of our struct.
;========================================
_allocate_sockaddr_in:
    pop r10 ; getting the return address to r10 registe
    
    push qword 0 ; allocating sin.zero (64 bits of zero, 8 bytes)
    push dword 0 ; allocating the size of the 32 bit IP address in the stack.
    mov dword [rsp], esi ; moving the rsi 32 bit Ip address to the allocation.(by using it's 32 bit register esi)

    ; creating htons(port) activity and converting rdi to "Big Endian"
    mov rsi, rax ; moving the family arg to rsi for using rax(al and ah).
    mov rax, rdi ; moving the port number to rax
    xor rdx, rdx ; reseting the rdx register
    
    mov dl, al ; temp = al
    mov al , ah ; al = ah
    mov ah, dl ; ah = temp

    push ax ; allocating the port number in "Big Endian" format. 
    push si ; allocating the socket family to the struct sockaddr_in.
    lea rax, [rsp] ; moving the struct address to rax, as the return address of the subroutine.

    push r10 ; pusinng the subroutine return address.
ret


%endif
;SYSCALLS_SOCKETS_INC