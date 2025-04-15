section .data
    prompt1: db "Enter string: ", 0
    prompt2: db "Enter character: ", 0
    result:  db "Count: ", 0
    newline: db 10

section .bss
    str:   resb 100
    char:  resb 2
    count: resb 1

section .text
    global _start

_start:
    ; Print string prompt
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt1
    mov rdx, 13       ; Length of prompt1
    syscall

    ; Read string
    mov rax, 0
    mov rdi, 0
    mov rsi, str
    mov rdx, 100
    syscall

    ; Print character prompt
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt2
    mov rdx, 17       ; Length of prompt2
    syscall

    ; Read character
    mov rax, 0
    mov rdi, 0
    mov rsi, char
    mov rdx, 2
    syscall

    ; Count character occurrences
    xor rcx, rcx      ; Counter = 0
    mov rsi, str      ; String pointer
    mov al, [char]    ; Character to find

count_loop:
    cmp byte [rsi], 0
    je print_result
    cmp byte [rsi], al
    jne skip
    inc rcx
skip:
    inc rsi
    jmp count_loop

print_result:
    ; Convert count to ASCII
    add cl, '0'
    mov [count], cl

    ; Print result message
    mov rax, 1
    mov rdi, 1
    mov rsi, result
    mov rdx, 7        ; Length of "Count: "
    syscall

    ; Print count
    mov rax, 1
    mov rdi, 1
    mov rsi, count
    mov rdx, 1
    syscall

    ; Print newline
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    ; Exit
    mov rax, 60
    xor rdi, rdi
    syscall
