section .data
    prompt db "1)HEX->BCD 2)BCD->HEX 3)EXIT: ", 0
    prompt_hex db "Hex(4 digits): ", 0
    prompt_bcd db "BCD(5 digits): ", 0
    err db "Invalid input!", 0xA, 0
    result_hex db "Hex=0x", 0
    result_bcd db "BCD=", 0
    nl db 0xA

section .bss
    choice resb 2
    input resb 6
    output resb 6

section .text
    global _start

; ======================
; Macros for Syscalls
; ======================
%macro sys_write 2
    mov eax,4
    mov ebx,1
    mov ecx,%1
    mov edx,%2
    int 0x80
%endmacro

%macro sys_read 2
    mov eax,3
    mov ebx,0
    mov ecx,%1
    mov edx,%2
    int 0x80
%endmacro

%macro sys_exit 1
    mov eax,1
    mov ebx,%1
    int 0x80
%endmacro

; ======================
; Program Start
; ======================
_start:
menu:
    sys_write prompt, 26
    sys_read choice, 2

    cmp byte [choice],'1'
    je hex_to_bcd
    cmp byte [choice],'2'
    je bcd_to_hex
    cmp byte [choice],'3'
    je bye
    jmp error

hex_to_bcd:
    sys_write prompt_hex, 15
    sys_read input, 5

    xor eax,eax
    mov esi,input
    mov ecx,4
h2b_loop:
    shl eax,4
    mov bl,[esi]
    sub bl,'0'
    cmp bl,9
    jbe h2b_ok
    sub bl,7
h2b_ok:
    or al,bl
    inc esi
    loop h2b_loop

    mov edi,output+4
    mov ecx,5
    mov ebx,10
bcd_loop:
    xor edx,edx
    div ebx
    add dl,'0'
    mov [edi],dl
    dec edi
    loop bcd_loop

    sys_write result_bcd, 4
    sys_write output, 5
    jmp newline

bcd_to_hex:
    sys_write prompt_bcd, 16
    sys_read input, 6

    xor eax,eax
    mov esi,input
    mov ecx,5
    mov ebx,10
b2h_loop:
    imul eax,ebx
    mov dl,[esi]
    sub dl,'0'
    add eax,edx
    inc esi
    loop b2h_loop

    mov edi,output+3
    mov ecx,4
hex_loop:
    mov edx,eax
    and edx,0xF
    cmp dl,9
    jbe hex_digit
    add dl,7
hex_digit:
    add dl,'0'
    mov [edi],dl
    shr eax,4
    dec edi
    loop hex_loop

    sys_write result_hex, 6
    sys_write output, 4
    jmp newline

error:
    sys_write err, 14
    jmp newline

newline:
    sys_write nl, 1
    jmp menu

bye:
    sys_exit 0
