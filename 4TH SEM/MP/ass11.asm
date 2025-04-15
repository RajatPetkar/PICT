section .data
    prompt: db "Enter a string: ", 0xA
    plen :  equ $ - prompt

    msg1 : db "Palindrome", 0xA
    msg1len : equ $ - msg1

    msg2 : db "Not Palindrome", 0xA
    msg2len : equ $ - msg2

section .bss
    str : resb 100       
    len : resb 1          

section .text
    global _start

_start:
    ; Print prompt
    mov rax, 1            
    mov rdi, 1           
    mov rdx, plen
    syscall

    ; Read input
    mov rax, 0            
    mov rdi, 0            
    mov rsi, str
    mov rdx, 100
    syscall
    mov [len], al        

   
    movzx rcx, byte [len]
    dec rcx              
    mov byte [str + rcx], 0  

    ; Setup pointers
    lea rsi, [str]      
    lea rdi, [str + rcx - 1]  

pal_check:
    cmp rsi, rdi
    jge show_palindrome

    mov al, [rsi]
    mov bl, [rdi]
    cmp al, bl
    jne show_not_palindrome

    inc rsi
    dec rdi
    jmp pal_check

show_palindrome:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg1
    mov rdx, msg1len
    syscall
    jmp exit

show_not_palindrome:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg2
    mov rdx, msg2len
    syscall

exit:
    mov rax, 60
    xor rdi, rdi
    syscall
