section .data
    msg2 db "Elements of Array:",10,13
    lenmsg2 equ $ - msg2
    msg3 db "",10,13
    lenmsg3 equ $ - msg3

    msg4 db "Count Of Postive Numbers : ",10,13
    lenmsg4 equ $ - msg4
    msg5 db "Count of Negative Numbers : ",10,13
    lenmsg5 equ $ - msg5

    array dq -0000000000000002h,-0000000000000007h,000000000000000Ah,0000000000000003h,0000000000000001h

section .bss
    counter resb 01
    result resb 16
    pcount resb 01
    ncount resb 01
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
%macro write 2
    mov rax, 1                       
    mov rdi, 1                      
    mov rsi, %1                   
    mov rdx, %2                 
    syscall
%endmacro

global _start

section .text
_start:
    write msg2,lenmsg2

    mov byte[counter],05
    mov rsi,array
    back1: mov rax,[rsi]
    push rsi
    call display
    pop rsi
    add rsi,08
    dec byte[counter]
    jnz back1

mov byte[counter], 5
mov byte[pcount], 0
mov byte[ncount], 0
mov rsi, array

back2:
    mov rax, [rsi]
    test rax, rax         ; Check sign
    js is_negative        ; If negative (Sign bit = 1)

    inc byte[pcount]      ; Otherwise, it's positive
    jmp next_check

is_negative:
    inc byte[ncount]

next_check:
    add rsi, 8
    dec byte[counter]
    jnz back2


    write msg4,lenmsg4
    mov al,[pcount]
    call display
    write msg5,lenmsg5
    mov al,byte[ncount]
    call display



   mov rax, 60
   mov rdi,0
    syscall

    display: mov rbx,rax
    mov rcx,16
    mov rdi,result

    back:rol rbx,04H
    mov al,bl
    AND al,0fH
    cmp al,09
    jg b1
    add al,30H
    jmp b2

    b1:add al,37H

    b2:mov byte[rdi],al
    inc rdi
    dec rcx
    jnz back

    write result,16
    write msg3,lenmsg3
    ret

