section .data
    prompt_choice db "Choose (1=HEX to BCD, 2=BCD to HEX, 3=EXIT): ", 0
    prompt_hex db "Enter 4-digit Hex (0x): ", 0
    prompt_bcd db "Enter 5-digit BCD: ", 0
    invalid_msg db "Invalid input!", 0xA, 0
    hex_result db "BCD result: ", 0
    bcd_result db "Hex result: 0x", 0
    newline db 0xA, 0

section .bss
    choice resb 2
    input resb 6
    output resb 6

section .text
    global _start

; Macro for system write
%macro sys_write 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

; Macro for system read
%macro sys_read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

; Macro for system exit
%macro sys_exit 1
    mov eax, 1
    mov ebx, %1
    int 0x80
%endmacro

_start:
    call show_menu
    jmp _start

show_menu:
    ; Display menu
    sys_write prompt_choice, 43

    ; Get choice
    sys_read choice, 2

    ; Process choice
    cmp byte [choice], '1'
    je do_hex_to_bcd
    cmp byte [choice], '2'
    je do_bcd_to_hex
    cmp byte [choice], '3'
    je exit
    call show_error
    ret

do_hex_to_bcd:
    ; Get hex input
    sys_write prompt_hex, 23
    sys_read input, 5

    ; Convert hex to binary
    call hex_to_binary
    
    ; Convert to BCD
    call binary_to_bcd
    
    ; Show result
    sys_write hex_result, 12
    sys_write output, 5
    call new_line
    ret

do_bcd_to_hex:
    ; Get BCD input
    sys_write prompt_bcd, 19
    sys_read input, 6

    ; Convert BCD to binary
    call bcd_to_binary
    
    ; Convert to hex string
    call binary_to_hex
    
    ; Show result
    sys_write bcd_result, 14
    sys_write output, 4
    call new_line
    ret

hex_to_binary:
    xor eax, eax
    mov ecx, 4
    mov esi, input
.hex_loop:
    shl eax, 4
    mov bl, [esi]
    cmp bl, '9'
    jbe .digit
    sub bl, 7
.digit:
    sub bl, '0'
    or al, bl
    inc esi
    loop .hex_loop
    ret

binary_to_bcd:
    xor edx, edx
    mov ebx, 10
    mov ecx, 5
    mov edi, output+4
.bcd_loop:
    xor edx, edx
    div ebx
    add dl, '0'
    mov [edi], dl
    dec edi
    loop .bcd_loop
    ret

bcd_to_binary:
    xor eax, eax
    mov ecx, 5
    mov esi, input
    mov ebx, 10
.num_loop:
    imul eax, ebx
    mov dl, [esi]
    sub dl, '0'
    add eax, edx
    inc esi
    loop .num_loop
    ret

binary_to_hex:
    mov ecx, 4
    mov edi, output+3
.hexstr_loop:
    mov edx, eax
    and edx, 0xF
    cmp dl, 9
    jbe .hexdigit
    add dl, 7
.hexdigit:
    add dl, '0'
    mov [edi], dl
    shr eax, 4
    dec edi
    loop .hexstr_loop
    ret

show_error:
    sys_write invalid_msg, 13
    ret

new_line:
    sys_write newline, 1
    ret

exit:
    sys_exit 0
