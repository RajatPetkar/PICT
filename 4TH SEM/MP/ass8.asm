
%macro IO 4
    mov rax, %1
    mov rdi, %2
    mov rsi, %3
    mov rdx, %4
    Syscall
%endmacro

%macro hex_ascii 2
    mov rcx, 02                   
    mov rbp, %1                   
    mov bl, %2                    

    %%label1:                   
    rol bl, 04                 
    mov dl, bl                      
    and dl, 0Fh                  
    cmp dl, 09h                     
    jbe %%label2
    add dl, 07h                  
    
    %%label2:                      
    add dl, 30h        
    mov [rbp], dl                
    inc rbp                       
    dec rcx                         
    jnz %%label1                   
%endmacro

%macro printarray 2                 
    mov rsi, %1                    
    mov byte[counter], %2          
    %%label:                       
    mov al, [rsi]                 
    push rsi                     
    hex_ascii ans,al               
    IO 1,1,ans,2                  
    mov byte[ans] , 10         
    IO 1,1,ans,1               
    pop rsi                      
    inc rsi                       
    dec byte[counter]              
    jnz %%label                    
%endmacro

%macro exit 0
    mov rax, 60
    mov rdx, 00
    Syscall
%endmacro

section .data
srcblk db 01h , 02h , 03h , 04h , 05h
dstblk db 00h , 00h , 00h , 00h , 00h
M1 db "Enter choice..." ,10, "1 ---> Without string" ,10, "2 ---> With string" ,10
L1 equ $-M1
M2 db "The contents of source block is.." , 10
L2 equ $-M2
M3 db "The contents of destination block intially.." , 10
L3 equ $-M3
M4 db "The contents of destination block after block transfer are.." , 10
L4 equ $-M4



section .bss
ans resb 2
counter resb 1



section .text
global _start:
_start: 
    
    IO 1,1,M2,L2                   
    
    printarray srcblk , 5      

    IO 1,1,M3,L3                   
    
    printarray dstblk , 5          
    
    call blktsfwos                
    
    IO 1,1,M4,L4                
    
    printarray dstblk , 5       
    
    call blktsfws                 
    
    IO 1,1,M4,L4                    
    
    printarray dstblk , 5          
    
    exit



blktsfwos:                         
    mov rsi, srcblk                 
    mov rdi, dstblk                 
    mov byte[counter] ,05          
    
    again:
    mov bl, [rsi]                 
    mov [rdi], bl                  
    inc rsi                       
    inc rdi                        
    dec byte[counter]             
    jnz again                      
    ret                                                 
    
blktsfws:                         
    mov rsi, srcblk               
    mov rdi, dstblk             
    mov rcx, 05h                   
    
    cld                             
    rep movsb                       
    ret
