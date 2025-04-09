section .data
    array dd 10, 20, 30, 40, 50   ;
    array_size equ ($ - array) / 4 ;
    sum_msg db 'Sum: ', 0         
    sum_len equ $ - sum_msg        
    newline db 10                 

section .bss
    sum_str resb 10                
section .text
    global _start

_start:
    
    mov ecx, array_size
    mov esi, 0
    mov eax, 0

sum_loop:
    add eax, [array + esi*4]
    inc esi
    loop sum_loop

   
    mov edi, sum_str + 9   
    mov byte [edi], 0     
    mov ebx, 10            

convert_loop:
    xor edx, edx           
    div ebx               
    add dl, '0'           
    dec edi                
    mov [edi], dl         
    test eax, eax         
    jnz convert_loop       

    
    mov eax, 4            
    mov ebx, 1           
    mov ecx, sum_msg       
    mov edx, sum_len       
    int 0x80

    mov eax, 4            
    mov ebx, 1             
    mov ecx, edi           
    mov edx, sum_str + 10 
    sub edx, edi
    int 0x80

    
    mov eax, 4            
    mov ebx, 1            
    mov ecx, newline       
    mov edx, 1             
    int 0x80

    
    mov eax, 1             
    mov ebx, 0             
    int 0x80
