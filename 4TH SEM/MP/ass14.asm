section .data
    prompt:      db "Enter a number: ", 0
    result_msg:  db "Sum of digits: ", 0
    newline:     db 10

section .bss
    num:    resb 20
    sum:    resb 4      ; Will store ASCII digits

section .text
    global _start

_start:
    ; Print prompt
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt
    mov rdx, 16         ; Length of prompt
    syscall

    ; Read number
    mov rax, 0
    mov rdi, 0
    mov rsi, num
    mov rdx, 20
    syscall

    ; Calculate sum of digits
    xor rcx, rcx        ; RCX will store sum
    mov rsi, num

sum_loop:
    mov al, [rsi]
    test al, al         ; Check for null terminator
    jz convert_sum
    
    cmp al, '0'
    jb next_char
    cmp al, '9'
    ja next_char
    
    sub al, '0'        ; Convert ASCII to digit
    add cl, al         ; Add to sum (using CL for 8-bit addition)

next_char:
    inc rsi
    jmp sum_loop

convert_sum:
    ; Convert sum to ASCII (assuming sum < 100)
    mov al, cl
    mov bl, 10
    div bl             ; AL = quotient, AH = remainder
    
    add al, '0'
    add ah, '0'
    
    mov [sum], al      ; Tens digit
    mov [sum+1], ah    ; Ones digit
    mov byte [sum+2], 0 ; Null terminator

print_result:
    ; Print result message
    mov rax, 1
    mov rdi, 1
    mov rsi, result_msg
    mov rdx, 15        ; Length of result_msg
    syscall

    ; Print sum (either 1 or 2 digits)
    cmp cl, 10
    jb single_digit
    
    ; Two digits
    mov rax, 1
    mov rdi, 1
    mov rsi, sum
    mov rdx, 2
    syscall
    jmp print_newline

single_digit:
    ; One digit
    mov rax, 1
    mov rdi, 1
    mov rsi, sum+1     ; Skip tens digit if <10
    mov rdx, 1
    syscall

print_newline:
    ; Print newline
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

exit:
    ; Exit
    mov rax, 60
    xor rdi, rdi
    syscall
