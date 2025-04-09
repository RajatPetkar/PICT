section .data
    msg1 db "******************MENU****************",10
    lenmsg1 equ $ -msg1

    msg2 db "1. Addition",10
    lenmsg2 equ $ - msg2

    msg3 db "2. Subtraction",10
    lenmsg3 equ $ - msg3

    msg4 db "3. Multiplication",10
    lenmsg4 equ $ - msg4

    msg5 db "4. Exit ",10
    lenmsg5 equ $ - msg5

    msg6 db "Enter your choice (1-4): ",10
    lenmsg6 equ $ - msg6

    msg7 db "Enter first number: ",10
    lenmsg7 equ $ - msg7

    msg8 db "Enter second number: ",10
    lenmsg8 equ $ - msg8

    msg9 db "Result: ",10
    lenmsg9 equ $ - msg9

    msg10 db "  ",10
    lenmsg10 equ $ - msg10

section .bss
    inputBuffer resb 2
    num1 resb 2
    num2 resb 2
    result resb 2

%macro writeRead 4
    mov rax, %1                       
    mov rdi, %2                      
    mov rsi, %3                 
    mov rdx, %4                 
    syscall
%endmacro

global _start

section .text
_start:
    call DisplayMenu
    call ReadChoice
    call ProcessChoice
    jmp _start

DisplayMenu:
    writeRead 1, 1, msg1, lenmsg1
    writeRead 1, 1, msg2, lenmsg2
    writeRead 1, 1, msg3, lenmsg3
    writeRead 1, 1, msg4, lenmsg4
    writeRead 1, 1, msg5, lenmsg5
    writeRead 1, 1, msg6, lenmsg6
    ret

ReadChoice:
    writeRead 0, 0, inputBuffer, 2
    ret

ProcessChoice:
    cmp byte [inputBuffer], '1'
    je Addition
    cmp byte [inputBuffer], '2'
    je Subtraction
    cmp byte [inputBuffer], '3'
    je Multiplication
    cmp byte [inputBuffer], '4'
    je ExitProgram
    ret

Addition:
    call GetNumbers
    mov al, [num1]
    sub al, '0'
    mov bl, [num2]
    sub bl, '0'
    add al, bl
    add al, '0'
    mov [result], al
    call DisplayResult
    ret

Subtraction:
    call GetNumbers
    mov al, [num1]
    sub al, '0'
    mov bl, [num2]
    sub bl, '0'
    sub al, bl
    add al, '0'
    mov [result], al
    call DisplayResult
    ret

Multiplication:
    call GetNumbers
    mov al, [num1]
    sub al, '0'
    mov bl, [num2]
    sub bl, '0'
    mul bl
    add al, '0'
    mov [result], al
    call DisplayResult
    ret

GetNumbers:
    writeRead 1, 1, msg7, lenmsg7
    writeRead 0, 0, num1, 2
    writeRead 1, 1, msg8, lenmsg8
    writeRead 0, 0, num2, 2
    ret

DisplayResult:
    writeRead 1, 1, msg9, lenmsg9
    writeRead 1, 1, result, 1
    writeRead 1, 1, msg10, lenmsg10
    writeRead 1, 1, msg10, lenmsg10
    ret

ExitProgram:
    mov rax, 60          
    xor rdi, rdi          
    syscall
