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
    num resb 10                     

section .text
    global _start

_start:
    
    ;mov r8, 5   

; Get the first command-line argument (argv[1])
    pop rcx        ; Get argc
    cmp rcx, 2     ; Check if we have at least one argument
    jl no_argument
    
    pop rdi        ; Skip argv[0] (program name)
    pop rdi        ; Get argv[1] (the number string)
    
    ; Convert the string to integer
    xor r8, r8     ; Clear r8 for our result
    xor rax, rax   ; Clear rax
    xor rcx, rcx   ; Clear rcx
    
convert_loop:
    movzx rax, byte [rdi]  ; Get next character
    cmp al, 0             ; Check for null terminator
    je convert_done
    sub al, '0'           ; Convert from ASCII to digit
    imul r8, r8, 10       ; Multiply current result by 10
    add r8, rax           ; Add current digit
    inc rdi               ; Move to next character
    jmp convert_loop
    mov r9, r8                     

factorial_loop:
    dec r8                          
    cmp r8, 1                       
    jle factorial_end               
    imul r9, r8                    
    jmp factorial_loop              

factorial_end:
   
    print message, len


    mov rsi, num                  
    mov rax, r9                   
    call int_to_str                

    print num, 10                   

    exit

int_to_str:
    add rsi, 9                     
    mov rcx, 10                     

loop_convert:
    xor rdx, rdx                   
    div rcx                        
    add dl, '0'                   
    dec rsi                     
    mov [rsi], dl                   
    cmp rax, 0                      
    jne loop_convert              
    ret                        
