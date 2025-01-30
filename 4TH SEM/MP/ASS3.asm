section .data
arr db 10h, 25h, 5h, 10h, 15h   
len equ 5                       
msg db "Enter element of array :- ", 10,13
lenmsg equ $-msg               
msg2 db "  ",10,13
lenmsg2 equ $-msg2 

msg3 db "Largest no :- ",10,13
lenmsg3 equ $-msg3

section .bss
counter resb 1   
result resb 16              

%macro RW 4
    mov rax, %1                  
    mov rdi, %2                  
    mov rsi, %3                  
    mov rdx, %4                  
    syscall
%endmacro

section .text 
global _start

_start:
    RW 1, 1, msg, lenmsg          

   mov byte[counter],05
   mov rsi,arr
   back1:
   mov al,[rsi]
   push rsi
   call display
   pop rsi
   inc rsi
   dec byte[counter]
   jnz back1

; logic for largest number

RW 1, 1, msg3, lenmsg3
mov byte[counter],05H
mov al,0
mov rsi,arr
back3:cmp al,[rsi]
ja skip
mov al,[rsi]

skip:
inc rsi
dec byte[counter]
jnz back3
call display

exit:
mov rax,60
xor rdi,rdi
syscall

display:
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

    RW 1,1,result,16
    RW 1, 1, msg2, lenmsg2 
    ret
