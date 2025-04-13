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
    
    mov r8, 5                       
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
