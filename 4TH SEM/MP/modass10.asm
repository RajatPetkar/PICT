section .data
    msg_usage db "Usage: ./factorial <number between 0 and 20>", 0xA
    msg_usage_len equ $ - msg_usage
    msg_result db "The factorial is: "
    msg_result_len equ $ - msg_result
    newline db 0xA, 0      

section .bss
    input_str resb 21
    output_str resb 21

section .text
    global _start

%macro write 2
    mov rax, 1             
    mov rdi, 1             
    mov rsi, %1             ; pointer to message
    mov rdx, %2             ; message length
    syscall
%endmacro

%macro exit 1
    mov rax, 60             ; syscall number for exit
    mov rdi, %1             ; exit code
    syscall
%endmacro

_start:
    ; Check if we have exactly one command-line argument
    pop rax                 ; Get argc (number of args)
    cmp rax, 2              ; We expect 2 (program name + 1 arg)
    jne .show_usage
    
    ; Get argv[1]
    pop rax                 ; Discard argv[0] (program name)
    pop rsi                 ; Get argv[1] (the number argument)
    
    ; Convert to integer
    call string_to_int
    cmp rax, 0
    jl .invalid_input
    cmp rax, 20
    jg .invalid_input
    
    ; Compute factorial
    mov rbx, rax
    mov rax, 1              ; Start with factorial = 1
    cmp rbx, 0
    je .store_result        ; Special case: 0! = 1
    
.factorial_loop:
    imul rax, rbx           ; Multiply by current number
    dec rbx                 ; Decrement
    jnz .factorial_loop     ; Continue until we reach 1
    
.store_result:
    mov rdi, output_str     ; Destination for result string
    call int_to_string
    mov rdx, rax            ; Length of result string
    
    write msg_result, msg_result_len
    write output_str, rdx
    write newline, 1
    exit 0

.show_usage:
.invalid_input:
    write msg_usage, msg_usage_len
    exit 1

; Convert string to int
; RSI: pointer to string
; RAX: result (-1 if invalid)
string_to_int:
    xor rax, rax            ; Clear result
    xor rcx, rcx            ; Clear counter
    
.next_char:
    movzx rdx, byte [rsi + rcx]
    test rdx, rdx           ; Check for null terminator
    jz .done
    
    cmp rdx, '0'
    jb .invalid
    cmp rdx, '9'
    ja .invalid
    
    sub rdx, '0'            ; Convert ASCII to number
    imul rax, 10            ; Multiply current result by 10
    add rax, rdx            ; Add new digit
    inc rcx                 ; Move to next character
    jmp .next_char
    
.invalid:
    mov rax, -1             ; Return -1 for invalid input
    
.done:
    ret

; Convert int to string
; RAX: number
; RDI: destination buffer
; Returns: RAX = length
int_to_string:
    push rdi                ; Save original buffer pointer
    mov r8, rdi             ; Store original buffer address
    
    ; Handle case when number is 0
    test rax, rax
    jnz .not_zero
    mov byte [rdi], '0'     ; Just write '0'
    mov byte [rdi+1], 0     ; Add null terminator
    mov rax, 1              ; Length is 1
    pop rdi                 ; Restore original pointer
    ret
    
.not_zero:
    add rdi, 20             ; Move to end of buffer
    mov byte [rdi], 0       ; Add null terminator
    mov rcx, 10             ; Divisor
    
.convert_loop:
    dec rdi                 ; Move buffer position back
    xor rdx, rdx            ; Clear remainder
    div rcx                 ; Divide by 10
    add dl, '0'             ; Convert to ASCII
    mov [rdi], dl           ; Store digit
    test rax, rax           ; Check if quotient is 0
    jnz .convert_loop       ; If not, continue loop
    
    ; Calculate string length
    mov rax, r8             ; Get original buffer address
    add rax, 20             ; Move to end of buffer
    sub rax, rdi            ; Calculate length
    
    ; Move result to beginning of buffer
    mov rcx, rax            ; Length to move
    mov rsi, rdi            ; Source address
    mov rdi, r8             ; Destination address
    cld                     ; Clear direction flag
    rep movsb               ; Move string
    
    pop rdi                 ; Restore original pointer
    ret
