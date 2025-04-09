section .data
    prompt db "Enter a string: ", 0
    output db "Reversed string: ", 0
    buffer resb 100     
    reversed resb 100    

section .text
    global _start

_start:
    
    mov rax, 1         
    mov rdi, 1          
    mov rsi, prompt
    mov rdx, 15         
    syscall

    ; Read input
    mov rax, 0
    mov rdi, 0          
    mov rsi, buffer
    mov rdx, 100       
    syscall

    
    mov r8, rax         
    dec r8              
    mov rsi, buffer     
    add rsi, r8        
    dec rsi             

   
    mov rdi, reversed   
    mov rcx, r8       

reverse_loop:
    mov al, [rsi]       
    mov [rdi], al     
    dec rsi             
    inc rdi             
    loop reverse_loop   

    
    mov rax, 1          
    mov rdi, 1          
    mov rsi, output
    mov rdx, 17        
    syscall

   
    mov rax, 1          
    mov rdi, 1     
    mov rsi, reversed
    mov rdx, r8        
    syscall

 
    mov rax, 60        
    xor rdi, rdi       
    syscall
