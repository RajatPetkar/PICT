section .data
    msg db "Enter String:" , 10,13
    lenmsg equ $-msg
    msg1 db "Length of string is: "
    lenmsg1 equ $-msg1

section .bss
    str1 resb 20
    result resb 20

%macro RW 3
    mov rax,%1
    mov rdi,%1
    mov rsi,%2
    mov rdx,%3
    syscall
%endmacro

section .text
    global _start

_start:

    RW 1,msg,lenmsg
    RW 0,str1,16

    mov rbx,rax
    mov rcx,16H
    mov rdi,result

    back:rol rbx,04H
    mov al,bl
    AND al,0fH
    cmp al,09
    jg b1
    add al,30H
    jmp b2

    b1: add al,37H

    b2:mov byte[rdi],al
    inc rdi
    dec rcx
    jnz back

    RW 1,result,16

    exit:
    mov rax,60
    mov rdi,0
    syscall
