%macro print 2
    mov rax, 1
    mov rdi, 1
    mov rsi, %1
    mov rdx, %2
    syscall
%endmacro

%macro exit 0
    mov rax, 60
    xor rdi, rdi
    syscall
%endmacro

section .data
    message db "Factorial: ", 0
    len equ $ - message
    result db "Result: ", 0
    res_len equ $ - result

section .bss
    num resb 20     ; enough space to store 64-bit number as string

section .text
    global _start

_start:

    pop rcx
    cmp rcx, 2
    jl no_argument

    pop rdi        ; Skip program name
    pop rdi        ; Get argv[1] (number)

    ; Convert ASCII to integer in r8
    xor r8, r8
    xor rax, rax

convert_loop:
    movzx rax, byte [rdi]
    cmp al, 0
    je convert_done
    sub al, '0'
    imul r8, r8, 10
    add r8, rax
    inc rdi
    jmp convert_loop

convert_done:
    mov r9, r8      ; Store original number for factorial

    ; Compute factorial
    dec r8
    cmp r8, 1
    jl factorial_end

factorial_loop:
    imul r9, r8
    dec r8
    cmp r8, 1
    jge factorial_loop

factorial_end:
    print message, len

    mov rsi, num
    mov rax, r9
    call int_to_str

    mov rdx, num + 20
    sub rdx, rsi
    print rsi, rdx

    exit

no_argument:
    print result, res_len
    exit

; Converts integer in RAX to string at RSI
int_to_str:
    add rsi, 20
    mov rcx, 10

.loop_convert:
    xor rdx, rdx
    div rcx
    add dl, '0'
    dec rsi
    mov [rsi], dl
    test rax, rax
    jnz .loop_convert
    ret
