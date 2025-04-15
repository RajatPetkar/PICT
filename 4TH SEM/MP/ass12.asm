section .data
    prompt: db "Enter a string: ", 0xA
    plen : equ $ - prompt

    result : db "Word count: "
    rlen :  equ $ - result

    newline db 0xA

section .bss
    str : resb 100
    count :resb 1

section .text
    global _start

_start:
    ; Show prompt
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt
    mov rdx, plen
    syscall

    ; Read input
    mov rax, 0
    mov rdi, 0
    mov rsi, str
    mov rdx, 100
    syscall
    mov rbx, rax       

   
    dec rbx
    mov byte [str + rbx], 0

    ; Initialize
    xor rcx, rcx       
    xor r8b, r8b      
    lea rsi, [str]

next_char:
    mov al, [rsi]
    cmp al, 0
    je done

    cmp al, ' '
    je is_space

    cmp r8b, 0         
    jne skip_inc

    inc rcx            

skip_inc:
    mov r8b, 1
    jmp advance

is_space:
    mov r8b, 0

advance:
    inc rsi
    jmp next_char

done:
    ; Convert word count in rcx to ASCII for display
    add cl, '0'
    mov [count], cl   

    ; Print result label
    mov rax, 1
    mov rdi, 1
    mov rsi, result
    mov rdx, rlen
    syscall

    ; Print count
    mov rax, 1
    mov rdi, 1
    mov rsi, count     
    mov rdx, 1
    syscall


    ; Newline
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    ; Exit
    mov rax, 60
    xor rdi, rdi
    syscall
