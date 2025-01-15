section .data
msg db "Enter element of array :- " , 10
lenmsg equ $-msg
msg2 db "Element of array :- " , 10
lenmsg2 equ $-msg2

section .bss
Array resb 200
counter resb 1

section .text
global _start



_start:
mov rax,1
mov rdi,1
mov rsi,msg
mov rdx ,lenmsg
syscall

mov rbp,Array
mov byte[counter],5

loop1:
    mov rax,0
    mov rdi,0
    mov rsi,rbp
    mov rdx,17
    syscall

    add rbp,17

    dec byte[counter]
    jnz loop1

mov rax,60
mov rdi,0


mov rax,1
mov rdi,1
mov rsi,msg2
mov rdx ,lenmsg2
syscall

mov rbp,Array
mov byte[counter],5

loop2:
    mov rax,1
    mov rdi,1
    mov rsi,rbp
    mov rdx,17
    syscall

    add rbp,17

    dec byte[counter]
    jnz loop2

mov rax,60
mov rdi,0
syscall
